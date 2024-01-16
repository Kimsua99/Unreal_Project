// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/ABStageGimmick.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Physics/ABCollision.h"
#include "Character/ABCharacterNonPlayer.h"
#include "Item/ABItemBox.h"

// Sets default values
AABStageGimmick::AABStageGimmick()
{
	// Stage Section
	Stage = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Stage"));//����ƽ �޽� ������Ʈ
	RootComponent = Stage;//��Ʈ ������Ʈ ����

	//�غ�� ����ƽ �޽��� ����Ʈ���� ���۸� ����� �ε��ϰ� ��������.
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StageMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/ArenaBattle/Environment/Stages/SM_SQUARE.SM_SQUARE'"));
	if (StageMeshRef.Object)
	{
		Stage->SetStaticMesh(StageMeshRef.Object);
	}

	//Ʈ���� ����
	StageTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("StageTrigger"));
	StageTrigger->SetBoxExtent(FVector(775.0, 775.0f, 300.0f));
	StageTrigger->SetupAttachment(Stage);//��Ʈ�� ����
	StageTrigger->SetRelativeLocation(FVector(0.0f, 0.0f, 250.0f));
	StageTrigger->SetCollisionProfileName(CPROFILE_ABTRIGGER);//���� ������ �� �ִ� Ư���� ������ ����
	StageTrigger->OnComponentBeginOverlap.AddDynamic(this, &AABStageGimmick::OnStageTriggerBeginOverlap);//���Ϳ� ������ �߻� �� ó�����ִ� �Լ��� ����

	// Gate Section
	//������ �ʴ� �� ����. �迭�� 4���� ���ϰ� �������. �������� ����
	static FName GateSockets[] = { TEXT("+XGate"), TEXT("-XGate"), TEXT("+YGate"), TEXT("-YGate") };
	//���� ���Ǵ� �޽��� �ϳ��� ������. ���� ������.
	static ConstructorHelpers::FObjectFinder<UStaticMesh> GateMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/ArenaBattle/Environment/Props/SM_GATE.SM_GATE'"));

	//�迭 ��ȸ�ϸ鼭 4���� ���� �����, Ʈ���� ���� ����
	for (FName GateSocket : GateSockets)
	{
		//�� ����
		UStaticMeshComponent* Gate = CreateDefaultSubobject<UStaticMeshComponent>(GateSocket);
		Gate->SetStaticMesh(GateMeshRef.Object);//����ƽ �޽� ����
		Gate->SetupAttachment(Stage, GateSocket);//����ƽ �޽��� ������ ���Ͽ� ������ ��Ű���� �����ϸ� ���������� ������.
		Gate->SetRelativeLocation(FVector(0.0f, -80.5f, 0.0f));//�� ��ġ ����
		Gate->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));//������ �ִ� ���·� ��
		Gates.Add(GateSocket, Gate);

		//������ ��Ʈ������ ��ȯ�� �Ŀ� Ʈ���Ŷ�� ���̻� ����
		FName TriggerName = *GateSocket.ToString().Append(TEXT("Trigger"));
		//Ʈ���� ����
		UBoxComponent* GateTrigger = CreateDefaultSubobject<UBoxComponent>(TriggerName);
		//Ʈ���� ũ�� ����
		GateTrigger->SetBoxExtent(FVector(100.0f, 100.0f, 300.0f));
		//������ ���Ͽ� ����
		GateTrigger->SetupAttachment(Stage, GateSocket);
		//��ġ ����
		GateTrigger->SetRelativeLocation(FVector(70.0f, 0.0f, 250.0f));
		//�������� ����. 
		GateTrigger->SetCollisionProfileName(CPROFILE_ABTRIGGER);
		//Ʈ������ ĳ���Ͱ� �����Ǿ� ������ �̺�Ʈ �߻��ϸ� �ش� �Լ��� �����ǰ� ��
		GateTrigger->OnComponentBeginOverlap.AddDynamic(this, &AABStageGimmick::OnGateTriggerBeginOverlap);
		//ĳ���Ͱ� �������� �� ��� ������ �ĺ��ϱ� ���� ������Ʈ�� �±� ����. GateSocket�� �������Ͽ� ���� ����
		GateTrigger->ComponentTags.Add(GateSocket);
		//��������� �迭�� �߰�����
		GateTriggers.Add(GateTrigger);
	}

	// State Section
	CurrentState = EStageState::READY;//���� ���·� �ʱ�ȭ

	//������ ��, 4���� �Լ��� ���� ������ ���� ������ ���� ���� ������Ŵ. 
	StateChangeActions.Add(EStageState::READY, FStageChangedDelegateWrapper(FOnStageChangedDelegate::CreateUObject(this, &AABStageGimmick::SetReady)));
	StateChangeActions.Add(EStageState::FIGHT, FStageChangedDelegateWrapper(FOnStageChangedDelegate::CreateUObject(this, &AABStageGimmick::SetFight)));
	StateChangeActions.Add(EStageState::REWARD, FStageChangedDelegateWrapper(FOnStageChangedDelegate::CreateUObject(this, &AABStageGimmick::SetChooseReward)));
	StateChangeActions.Add(EStageState::NEXT, FStageChangedDelegateWrapper(FOnStageChangedDelegate::CreateUObject(this, &AABStageGimmick::SetChooseNext)));

	// Fight Section
	OpponentSpawnTime = 2.0f;//2�� �ڿ� npc �����ǵ���
	//������ų npc�� Ŭ���� ����.
	OpponentClass = AABCharacterNonPlayer::StaticClass();

	// Reward Section
	//���� Ŭ������ ���ؼ��� ������ �ڽ��� ����
	RewardBoxClass = AABItemBox::StaticClass();
	//������ ������ ��ġ�� ����Ʈ ���� ��ġ�� ���� ���� ����
	for (FName GateSocket : GateSockets)
	{
		FVector BoxLocation = Stage->GetSocketLocation(GateSocket) / 2;
		RewardBoxLocations.Add(GateSocket, BoxLocation);
	}
}

//Ʈ������ �Ӹ� �ƴ϶� ��� �Ӽ��� ����� �� ȣ��Ǵ� �Լ�
void AABStageGimmick::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	SetState(CurrentState);//���� ���� �����ϸ� SetState�Լ� ȣ���ϵ��� ����
}

void AABStageGimmick::OnStageTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//�߾ӿ� ��ġ�� �������� Ʈ���Ű� �ߵ��ϸ� ���� ���·� ����.
	SetState(EStageState::FIGHT);
}

//���ڸ� ���� ���� ���������� �Ѿ �� �ش� ����Ʈ Ʈ���Ű� �ߵ���.
void AABStageGimmick::OnGateTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//����Ʈ ������ Ʈ���Ű� �Ǹ� �ռ� �±׸� �� ������Ʈ���� �±װ� ������ �ϳ� ����־�� �ϹǷ� üũ�ؼ� ���� Ȯ������.
	check(OverlappedComponent->ComponentTags.Num() == 1);
	//�±� ���� �޾�
	FName ComponentTag = OverlappedComponent->ComponentTags[0];
	//���� �ΰ� �ڸ��� +X, +Y, -X, -Y��� �̸��� ������.
	FName SocketName = FName(*ComponentTag.ToString().Left(2));
	//�ش� �̸��� ������ �ִ��� Ȯ��.������ �ȵ�
	check(Stage->DoesSocketExist(SocketName));

	//�����̸��� ���� ��ġ ����
	FVector NewLocation = Stage->GetSocketLocation(SocketName);
	//�ش� ��ġ�� �ٸ� ���������� ��ġ�Ǿ����� ���� ����. ���� �������� ���� �˻�����. 
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(SCENE_QUERY_STAT(GateTrigger), false, this);
	//�ش� ��ġ�� ���� �ִ��� �˻�����.
	bool bResult = GetWorld()->OverlapMultiByObjectType(
		OverlapResults,
		NewLocation,
		FQuat::Identity,
		//��� ������Ʈ�� ���� �ڽ��� ������ ���¿��� �˻縦 ���� ��, �ƹ��͵� ���ٴ� ������ ���� �ش� ��ġ�� ��� ���� ����
		FCollisionObjectQueryParams::InitType::AllObjects,
		//�ش� ��ġ�� ��ü�� ����
		FCollisionShape::MakeSphere(775.0f),
		CollisionQueryParam
	);

	if (!bResult)
	{
		GetWorld()->SpawnActor<AABStageGimmick>(NewLocation, FRotator::ZeroRotator);
	}
}

void AABStageGimmick::OpenAllGates()//��� ���� ���� �Լ�
{
	//����Ʈ�� ���鼭
	for (auto Gate : Gates)
	{
		//��� ����Ʈ�� �����̼� ���� -90���� Yaw ���� ����
		(Gate.Value)->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	}
}

void AABStageGimmick::CloseAllGates()//��� ���� �ݴ� �Լ�
{
	//����Ʈ�� ���鼭
	for (auto Gate : Gates)
	{
		//�⺻ �����̼� ���� ����
		(Gate.Value)->SetRelativeRotation(FRotator::ZeroRotator);
	}
}

void AABStageGimmick::SetState(EStageState InNewState)
{
	//��������Ʈ ��̷� �Լ� �����͸� ����� ����
	CurrentState = InNewState;

	if (StateChangeActions.Contains(InNewState))//�ش� ���¿� ���� Ű�� �� �ȿ� �ִٸ�
	{
		//�ش� ��������Ʈ�� ���ε��Ǿ��ִٸ� �����ϵ��� ó��
		StateChangeActions[CurrentState].StageDelegate.ExecuteIfBound();
	}
}

void AABStageGimmick::SetReady()//�������� �غ� �ܰ�
{
	//����� Ʈ���� Ȱ��ȭ. ���� �� ���� �����ؾ� �ϹǷ� 
	StageTrigger->SetCollisionProfileName(CPROFILE_ABTRIGGER);
	for (auto GateTrigger : GateTriggers)
	{
		//������ ���� ���ؼ��� �ݸ��� ��Ȱ��ȭ
		GateTrigger->SetCollisionProfileName(TEXT("NoCollision"));
	}
	//�÷��̾ ���������� ���ϵ��� ��� �� ����
	OpenAllGates();
}

void AABStageGimmick::SetFight()//���� ����
{
	//��� Ʈ���� ��Ȱ��ȭ
	StageTrigger->SetCollisionProfileName(TEXT("NoCollision"));
	for (auto GateTrigger : GateTriggers)
	{
		GateTrigger->SetCollisionProfileName(TEXT("NoCollision"));
	}
	//�� �������� �߰��� Ȯ��
	CloseAllGates();
	
	//npc ��ȯ�ǵ��� �߰�
	GetWorld()->GetTimerManager().SetTimer(OpponentTimerHandle, this, &AABStageGimmick::OnOpponentSpawn, OpponentSpawnTime, false);
}

void AABStageGimmick::SetChooseReward()//���� ����
{
	StageTrigger->SetCollisionProfileName(TEXT("NoCollision"));
	for (auto GateTrigger : GateTriggers)
	{
		GateTrigger->SetCollisionProfileName(TEXT("NoCollision"));
	}
	//���� �����ϱ� �������� ��� ���� �����־�� ��.
	CloseAllGates();
	//���ڸ� �ٷ� �� �� �ְ� �Լ� �߰�
	SpawnRewardBoxes();
}

void AABStageGimmick::SetChooseNext()//���� �������� ����
{
	StageTrigger->SetCollisionProfileName(TEXT("NoCollision"));
	for (auto GateTrigger : GateTriggers)
	{
		//����Ʈ�� ���� Ʈ���� Ȱ��ȭ
		GateTrigger->SetCollisionProfileName(CPROFILE_ABTRIGGER);
	}
	//�� ������
	OpenAllGates();
}

//npc �׾��� ��
void AABStageGimmick::OnOpponentDestroyed(AActor* DestroyedActor)
{
	//���� �ܰ��� ���� ���� �ܰ�� �̵�����.
	SetState(EStageState::REWARD);
}

void AABStageGimmick::OnOpponentSpawn()
{
	//���� ��ġ �� ����
	const FVector SpawnLocation = GetActorLocation() + FVector::UpVector * 88.0f;
	//Ŭ������ �����ؼ� �ѱ�� Actor�� �����Ǵµ�, ������ Ŭ����(AABCharacterNonPlayer)�� ��ӹ��� ĳ���Ϳ� �����ؼ��� ���� ������Ŵ.
	AActor* OpponentActor = GetWorld()->SpawnActor(OpponentClass, &SpawnLocation, &FRotator::ZeroRotator);
	//ĳ����
	AABCharacterNonPlayer* ABOpponentCharacter = Cast<AABCharacterNonPlayer>(OpponentActor);
	if (ABOpponentCharacter)
	{
		//�ش� �Լ��� ������Ŵ.
		ABOpponentCharacter->OnDestroyed.AddDynamic(this, &AABStageGimmick::OnOpponentDestroyed);
	}
}

void AABStageGimmick::OnRewardTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//������ �迭 ��ȸ
	for (const auto& RewardBox : RewardBoxes)
	{
		if (RewardBox.IsValid())//��ȿ�� Ȯ���� �� ���� Isvalid�� ����ִ��� Ȯ��
		{
			AABItemBox* ValidItemBox = RewardBox.Get();//����ִٸ� Get �Լ��� ������ ������
			//������ �迭�� �� �ִ� ���Ͱ� ���� �̺�Ʈ �߻��� ���Ϳ� ������, ������ �ڽ��� �ñ�� �ٸ��� ������ �ڽ��� ��� �Ҹ�.(���� �ϳ��� �����ؾ� �ϹǷ�)
			AActor* OverlappedBox = OverlappedComponent->GetOwner();
			if (OverlappedBox != ValidItemBox)
			{
				//���� ���� �� ������ ���� �� ����
				ValidItemBox->Destroy();
			}
		}
	}
	//���� ���·� �Ѿ
	SetState(EStageState::NEXT);
}

//���ڸ� ���� ����
void AABStageGimmick::SpawnRewardBoxes()
{
	for (const auto& RewardBoxLocation : RewardBoxLocations)
	{
		FVector WorldSpawnLocation = GetActorLocation() + RewardBoxLocation.Value + FVector(0.0f, 0.0f, 30.0f);
		AActor* ItemActor = GetWorld()->SpawnActor(RewardBoxClass, &WorldSpawnLocation, &FRotator::ZeroRotator);
		AABItemBox* RewardBoxActor = Cast<AABItemBox>(ItemActor);
		if (RewardBoxActor)
		{
			RewardBoxActor->Tags.Add(RewardBoxLocation.Key);
			//Ʈ���� �ڽ��� ���� �Ŀ� OnComponentBeginOverlap �Լ� ȣ���� OnRewardTriggerBeginOverlap ��� �Լ��� ��������.
			RewardBoxActor->GetTrigger()->OnComponentBeginOverlap.AddDynamic(this, &AABStageGimmick::OnRewardTriggerBeginOverlap);
			
			//�������� ����� �迭�� �ش� ������ ���͸� �߰�
			RewardBoxes.Add(RewardBoxActor);
		}
	}
}