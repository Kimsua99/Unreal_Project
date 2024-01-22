// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ABCharacterNonPlayer.h"
#include "Engine/AssetManager.h"
#include "AI/ABAIController.h"

AABCharacterNonPlayer::AABCharacterNonPlayer()
{
	//메쉬가 로딩될 때 까지 숨겨놓기
	GetMesh()->SetHiddenInGame(true);

	AIControllerClass = AABAIController::StaticClass();

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AABCharacterNonPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//NPCMeshes 값이 들어왔는지 체크
	ensure(NPCMeshes.Num() > 0);
	//NPCMeshes 중에서 랜덤으로 하나 선택
	int32 RandIndex = FMath::RandRange(0, NPCMeshes.Num() - 1);
	//이를 비동기 방식(AsyncLoad)으로 진행.
	NPCMeshHandle = UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(NPCMeshes[RandIndex], FStreamableDelegate::CreateUObject(this, &AABCharacterNonPlayer::NPCMeshLoadCompleted));
}

void AABCharacterNonPlayer::SetDead()
{
	Super::SetDead(); // 부모로부터 상속받은 함수

	FTimerHandle DeadTimerHandle;//지정한 5초 시간 뒤에 없어지기 위해 타이머 핸들 추가

	//월드로부터 서비스 받음. 함수를 지정하는데, 5초 뒤에 어떤 함수 호출할지 지정 가능.
	//액터를 없애는 함수를 지정하는데 간편히 만들기 위해 람다 함수 사용,
	//타이머 델리게이트에 부착시키고 이를 바로 넘기는 식으로 구현. FTimerDelegate 구조체 생성
	//
	GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda(
		[&]()
		{
			Destroy();
		}
	), DeadEventDelayTime, false);//매핑할 필요 없으므로 false
}

void AABCharacterNonPlayer::NPCMeshLoadCompleted()
{
	//핸들 유효하면
	if (NPCMeshHandle.IsValid())
	{
		USkeletalMesh* NPCMesh = Cast<USkeletalMesh>(NPCMeshHandle->GetLoadedAsset());
		if (NPCMesh)
		{
			//메쉬 지정
			GetMesh()->SetSkeletalMesh(NPCMesh);
			//메쉬 안 보이게 했다가 로딩이 되면 그 때 보여주도록 설정
			GetMesh()->SetHiddenInGame(false);
		}
	}
	//핸들 다 사용했으므로 해제
	NPCMeshHandle->ReleaseHandle();
}
