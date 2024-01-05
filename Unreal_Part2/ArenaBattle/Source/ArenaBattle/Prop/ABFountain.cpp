// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/ABFountain.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AABFountain::AABFountain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//�����ڿ� ������Ʈ�� �����͸� ���� �����Ͽ� �⺻ ������ ����
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Water = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Water"));//��ü ����

	//� ���� ��Ʈ ������Ʈ���� ���� -> Body�� ��Ʈ��, Water�� �ڽ����� ����
	RootComponent = Body;
	Water->SetupAttachment(Body);
	//���� Ʈ������ ����
	Water->SetRelativeLocation(FVector(0.0f, 0.0f, 132.0f));

	//������Ʈ ���� StaticMesh���� ���� ������ �־�� ��. ������ ���� �ڵ��̹Ƿ� ConstructorHelpers ���
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BodyMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/ArenaBattle/Environment/Props/SM_Plains_Castle_Fountain_01.SM_Plains_Castle_Fountain_01'"));
	if (BodyMeshRef.Object)//�ش� ��ο� ���� �ִٸ�
	{
		Body->SetStaticMesh(BodyMeshRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> WaterMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/ArenaBattle/Environment/Props/SM_Plains_Fountain_02.SM_Plains_Fountain_02'"));
	if (WaterMeshRef.Object)//�ش� ��ο� ���� �ִٸ�
	{
		Water->SetStaticMesh(WaterMeshRef.Object);
	}
}

// Called when the game starts or when spawned
void AABFountain::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AABFountain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

