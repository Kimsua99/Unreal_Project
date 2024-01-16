// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ABItemBox.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Physics/ABCollision.h"
#include "Interface/ABCharacterItemInterface.h"
#include "Engine/AssetManager.h"
#include "ABItemData.h"

// Sets default values
AABItemBox::AABItemBox()
{
	//3���� �����Ϳ� ���� ��ü ����
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Effect"));
	
	//���� ������ ���� �¾�
	RootComponent = Trigger;
	Mesh->SetupAttachment(Trigger);
	Effect->SetupAttachment(Trigger);

	//������ ���� ���� ����
	//Ʈ���ſ� ���� ������ ���
	Trigger->SetCollisionProfileName(CPROFILE_ABTRIGGER);
	//�ڽ� ������Ʈ�� ������ ����
	Trigger->SetBoxExtent(FVector(40.0f, 42.0f, 30.0f));
	//Ʈ���� ������Ʈ�� ��������Ʈ. �������Ʈ������ ��� �����ϵ��� AddDynamic ���. 
	//���� ��ü�� ���ؼ� ��� ������ AABItemBox Ŭ������ OnOverlapBegin �Լ��� ���ε�.
	//Ʈ���Ű� �ߵ��Ǹ� OnOverlapBegin�� ȣ���.
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AABItemBox::OnOverlapBegin);

	//�ڽ� �޽��� Props ������ ���ڿ� �ش�
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/ArenaBattle/Environment/Props/SM_Env_Breakables_Box1.SM_Env_Breakables_Box1'"));
	if (BoxMeshRef.Object)
	{
		Mesh->SetStaticMesh(BoxMeshRef.Object);
	}
	//������ ��ġ ���� ����
	Mesh->SetRelativeLocation(FVector(0.0f, -3.5f, -30.0f));
	//���ڿ� ĳ���Ͱ� �浹���� �ʵ��� ������ ����
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));

	//����Ʈ ������Ʈ�� ����Ʈ ������ P_Treasure Chest Open ����Ʈ ���
	static ConstructorHelpers::FObjectFinder<UParticleSystem> EffectRef(TEXT("/Script/Engine.ParticleSystem'/Game/ArenaBattle/Effect/P_TreasureChest_Open_Mesh.P_TreasureChest_Open_Mesh'"));
	if (EffectRef.Object)
	{
		//����Ʈ�� ����
		Effect->SetTemplate(EffectRef.Object);
		//ó������ �ٷ� �ߵ����� �ʵ��� ����.
		Effect->bAutoActivate = false;
	}
}

void AABItemBox::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//���� �Ŵ����� ������ �ʱ�ȭ�� �� �ε� ��������.
	UAssetManager& Manager = UAssetManager::Get();

	TArray<FPrimaryAssetId> Assets;
	//�Ŵ����κ��� ��� ������. ABItemData�� �±� ���� �Ѱ��ָ� ���¿� ���� �迭�� ��ȯ����.
	Manager.GetPrimaryAssetIdList(TEXT("ABItemData"), Assets);
	ensure(0 < Assets.Num());//�� �����ϴ��� üũ

	int32 RandomIndex = FMath::RandRange(0, Assets.Num() - 1);//��ü�� �ϳ� ����
	//������ �ɾ �ε� �ȵǾ� �ִٸ� �ε� �����ֵ��� ����
	FSoftObjectPtr AssetPtr(Manager.GetPrimaryAssetPath(Assets[RandomIndex]));
	if (AssetPtr.IsPending())
	{
		AssetPtr.LoadSynchronous();
	}
	//�ε� �Ϸ� �� ������ ������ �ε��� ���� �����ϰ�
	Item = Cast<UABItemData>(AssetPtr.Get());
	//�̰��� null���� �ƴ��� Ȯ��
	ensure(Item);
}

void AABItemBox::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	//ĳ���Ͱ� ������ �� ������ �����Ͱ� ������ (= ���̸�)
	if (nullptr == Item)
	{
		Destroy();//����Ʈ ���� ��������.
		return;
	}

	//����ȯ ����. 
	IABCharacterItemInterface* OverlappingPawn = Cast<IABCharacterItemInterface>(OtherActor);
	
	if (OverlappingPawn)//�ε��� ���Ͱ� �ش� �������̽��� �����ߴٸ� 
	{
		//�������� ȹ������ �� ȹ���� ���Ϳ��� TakeItem �Լ��� ȣ��
		OverlappingPawn->TakeItem(Item);//ĳ���Ͱ� ������ �� ������ �����Ͱ� �ִٸ� ���ڷ� Item �Ѱ���
	}
	
	//����Ʈ �ߵ�
	Effect->Activate(true);
	//�޽� ����
	Mesh->SetHiddenInGame(true);
	//���Ϳ� ���� �ݸ������� ��� ����
	SetActorEnableCollision(false);
	//�ߵ��� �̺�Ʈ ����� ��, �ߵ��Ǵ� ��������Ʈ. 
	Effect->OnSystemFinished.AddDynamic(this, &AABItemBox::OnEffectFinished);
}

void AABItemBox::OnEffectFinished(UParticleSystemComponent* ParticleSystem)
{
	//���Ͱ� ������ �������� ����.
	Destroy();
}


