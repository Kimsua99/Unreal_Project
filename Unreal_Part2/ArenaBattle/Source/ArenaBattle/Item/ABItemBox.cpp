// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ABItemBox.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Physics/ABCollision.h"

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
	//Ʈ���� ������Ʈ�� ��������Ʈ. ��������Ʈ������ ��� �����ϵ��� AddDynamic ���. 
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

void AABItemBox::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	/*
	if (nullptr == Item)
	{
		Destroy();
		return;
	}

	IABCharacterItemInterface* OverlappingPawn = Cast<IABCharacterItemInterface>(OtherActor);
	if (OverlappingPawn)
	{
		OverlappingPawn->TakeItem(Item);
	}
	*/
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

