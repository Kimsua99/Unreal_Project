// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ABCharacterNonPlayer.h"
#include "Engine/AssetManager.h"
#include "AI/ABAIController.h"

AABCharacterNonPlayer::AABCharacterNonPlayer()
{
	//�޽��� �ε��� �� ���� ���ܳ���
	GetMesh()->SetHiddenInGame(true);

	AIControllerClass = AABAIController::StaticClass();

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AABCharacterNonPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//NPCMeshes ���� ���Դ��� üũ
	ensure(NPCMeshes.Num() > 0);
	//NPCMeshes �߿��� �������� �ϳ� ����
	int32 RandIndex = FMath::RandRange(0, NPCMeshes.Num() - 1);
	//�̸� �񵿱� ���(AsyncLoad)���� ����.
	NPCMeshHandle = UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(NPCMeshes[RandIndex], FStreamableDelegate::CreateUObject(this, &AABCharacterNonPlayer::NPCMeshLoadCompleted));
}

void AABCharacterNonPlayer::SetDead()
{
	Super::SetDead(); // �θ�κ��� ��ӹ��� �Լ�

	FTimerHandle DeadTimerHandle;//������ 5�� �ð� �ڿ� �������� ���� Ÿ�̸� �ڵ� �߰�

	//����κ��� ���� ����. �Լ��� �����ϴµ�, 5�� �ڿ� � �Լ� ȣ������ ���� ����.
	//���͸� ���ִ� �Լ��� �����ϴµ� ������ ����� ���� ���� �Լ� ���,
	//Ÿ�̸� ��������Ʈ�� ������Ű�� �̸� �ٷ� �ѱ�� ������ ����. FTimerDelegate ����ü ����
	//
	GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda(
		[&]()
		{
			Destroy();
		}
	), DeadEventDelayTime, false);//������ �ʿ� �����Ƿ� false
}

void AABCharacterNonPlayer::NPCMeshLoadCompleted()
{
	//�ڵ� ��ȿ�ϸ�
	if (NPCMeshHandle.IsValid())
	{
		USkeletalMesh* NPCMesh = Cast<USkeletalMesh>(NPCMeshHandle->GetLoadedAsset());
		if (NPCMesh)
		{
			//�޽� ����
			GetMesh()->SetSkeletalMesh(NPCMesh);
			//�޽� �� ���̰� �ߴٰ� �ε��� �Ǹ� �� �� �����ֵ��� ����
			GetMesh()->SetHiddenInGame(false);
		}
	}
	//�ڵ� �� ��������Ƿ� ����
	NPCMeshHandle->ReleaseHandle();
}
