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
	Stage = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Stage"));//스태틱 메쉬 컴포넌트
	RootComponent = Stage;//루트 컴포넌트 지정

	//준비된 스태틱 메쉬를 컨스트럭터 헬퍼를 사용해 로딩하고 지정해줌.
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StageMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/ArenaBattle/Environment/Stages/SM_SQUARE.SM_SQUARE'"));
	if (StageMeshRef.Object)
	{
		Stage->SetStaticMesh(StageMeshRef.Object);
	}

	//트리거 생성
	StageTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("StageTrigger"));
	StageTrigger->SetBoxExtent(FVector(775.0, 775.0f, 300.0f));
	StageTrigger->SetupAttachment(Stage);//루트에 부착
	StageTrigger->SetRelativeLocation(FVector(0.0f, 0.0f, 250.0f));
	StageTrigger->SetCollisionProfileName(CPROFILE_ABTRIGGER);//폰만 감지할 수 있는 특별한 프로필 지정
	StageTrigger->OnComponentBeginOverlap.AddDynamic(this, &AABStageGimmick::OnStageTriggerBeginOverlap);//액터와 오버랩 발생 시 처리해주는 함수와 연결

	// Gate Section
	//변하지 않는 값 지정. 배열로 4개의 소켓값 만들어줌. 동서남북 지정
	static FName GateSockets[] = { TEXT("+XGate"), TEXT("-XGate"), TEXT("+YGate"), TEXT("-YGate") };
	//문에 사용되는 메쉬는 하나로 동일함. 레퍼 가져옴.
	static ConstructorHelpers::FObjectFinder<UStaticMesh> GateMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/ArenaBattle/Environment/Props/SM_GATE.SM_GATE'"));

	//배열 순회하면서 4개의 문을 만들고, 트리거 볼륨 제작
	for (FName GateSocket : GateSockets)
	{
		//문 제작
		UStaticMeshComponent* Gate = CreateDefaultSubobject<UStaticMeshComponent>(GateSocket);
		Gate->SetStaticMesh(GateMeshRef.Object);//스태틱 메쉬 지정
		Gate->SetupAttachment(Stage, GateSocket);//스태틱 메쉬에 설정된 소켓에 부착을 시키도록 지정하면 레벨디자인 편리해짐.
		Gate->SetRelativeLocation(FVector(0.0f, -80.5f, 0.0f));//문 위치 조정
		Gate->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));//열러져 있는 상태로 둠
		Gates.Add(GateSocket, Gate);

		//소켓을 스트링으로 변환한 후에 트리거라는 접미사 붙임
		FName TriggerName = *GateSocket.ToString().Append(TEXT("Trigger"));
		//트리거 생성
		UBoxComponent* GateTrigger = CreateDefaultSubobject<UBoxComponent>(TriggerName);
		//트리거 크기 지정
		GateTrigger->SetBoxExtent(FVector(100.0f, 100.0f, 300.0f));
		//동일한 소켓에 붙임
		GateTrigger->SetupAttachment(Stage, GateSocket);
		//위치 조정
		GateTrigger->SetRelativeLocation(FVector(70.0f, 0.0f, 250.0f));
		//프로필을 설정. 
		GateTrigger->SetCollisionProfileName(CPROFILE_ABTRIGGER);
		//트리거의 캐릭터가 감지되어 오버랩 이벤트 발생하면 해당 함수로 연동되게 함
		GateTrigger->OnComponentBeginOverlap.AddDynamic(this, &AABStageGimmick::OnGateTriggerBeginOverlap);
		//캐릭터가 동서남북 중 어디에 들어갔는지 식별하기 위해 컴포넌트에 태그 부착. GateSocket이 동서남북에 대한 정보
		GateTrigger->ComponentTags.Add(GateSocket);
		//만들어지면 배열에 추가해줌
		GateTriggers.Add(GateTrigger);
	}

	// State Section
	CurrentState = EStageState::READY;//레디 상태로 초기화

	//시작할 때, 4개의 함수에 대해 지정한 상태 열거형 값에 따라 연동시킴. 
	StateChangeActions.Add(EStageState::READY, FStageChangedDelegateWrapper(FOnStageChangedDelegate::CreateUObject(this, &AABStageGimmick::SetReady)));
	StateChangeActions.Add(EStageState::FIGHT, FStageChangedDelegateWrapper(FOnStageChangedDelegate::CreateUObject(this, &AABStageGimmick::SetFight)));
	StateChangeActions.Add(EStageState::REWARD, FStageChangedDelegateWrapper(FOnStageChangedDelegate::CreateUObject(this, &AABStageGimmick::SetChooseReward)));
	StateChangeActions.Add(EStageState::NEXT, FStageChangedDelegateWrapper(FOnStageChangedDelegate::CreateUObject(this, &AABStageGimmick::SetChooseNext)));

	// Fight Section
	OpponentSpawnTime = 2.0f;//2초 뒤에 npc 스폰되도록
	//생성시킬 npc의 클래스 지정.
	OpponentClass = AABCharacterNonPlayer::StaticClass();

	// Reward Section
	//상자 클래스에 대해서는 아이템 박스로 지정
	RewardBoxClass = AABItemBox::StaticClass();
	//각각의 스폰될 위치는 게이트 소켓 위치를 통해 상자 스폰
	for (FName GateSocket : GateSockets)
	{
		FVector BoxLocation = Stage->GetSocketLocation(GateSocket) / 2;
		RewardBoxLocations.Add(GateSocket, BoxLocation);
	}

	// Stage Stat
	CurrentStageNum = 0;//처음 등장하는 기믹 스테이지는 0번의 스탯 값을 가지는데, 모두 클리어하고 새 스테이지 생성할 때마다 값 추가
}

//트랜스폼 뿐만 아니라 모든 속성이 변경될 때 호출되는 함수
void AABStageGimmick::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	SetState(CurrentState);//현재 상태 변경하면 SetState함수 호출하도록 구현
}

void AABStageGimmick::OnStageTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//중앙에 배치한 스테이지 트리거가 발동하면 대전 상태로 변경.
	SetState(EStageState::FIGHT);
}

//상자를 열고 다음 스테이지로 넘어갈 때 해당 게이트 트리거가 발동됨.
void AABStageGimmick::OnGateTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//게이트 소켓의 트리거가 되면 앞서 태그를 단 컴포넌트에는 태그가 설정이 하나 들어있어야 하므로 체크해서 오류 확인해줌.
	check(OverlappedComponent->ComponentTags.Num() == 1);
	//태그 정보 받아
	FName ComponentTag = OverlappedComponent->ComponentTags[0];
	//왼쪽 두개 자르면 +X, +Y, -X, -Y라는 이름이 생성됨.
	FName SocketName = FName(*ComponentTag.ToString().Left(2));
	//해당 이름의 소켓이 있는지 확인.없으면 안됨
	check(Stage->DoesSocketExist(SocketName));

	//소켓이름을 통해 위치 얻음
	FVector NewLocation = Stage->GetSocketLocation(SocketName);
	//해당 위치에 다른 스테이지가 설치되어있을 수도 있음. 따라서 오버랩을 통해 검사해줌. 
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(SCENE_QUERY_STAT(GateTrigger), false, this);
	//해당 위치에 무언가 있는지 검사해줌.
	bool bResult = GetWorld()->OverlapMultiByObjectType(
		OverlapResults,
		NewLocation,
		FQuat::Identity,
		//모든 오브젝트에 대해 자신을 제외한 상태에서 검사를 했을 때, 아무것도 없다는 판정이 나면 해당 위치에 기믹 액터 스폰
		FCollisionObjectQueryParams::InitType::AllObjects,
		//해당 위치에 구체를 생성
		FCollisionShape::MakeSphere(775.0f),
		CollisionQueryParam
	);

	if (!bResult)
	{
		FTransform NewTransform(NewLocation);
		AABStageGimmick* NewGimmick = GetWorld()->SpawnActorDeferred<AABStageGimmick>(AABStageGimmick::StaticClass(), NewTransform);
		if (NewGimmick)
		{
			NewGimmick->SetStageNum(CurrentStageNum + 1);
			NewGimmick->FinishSpawning(NewTransform);
		}
	}
}


void AABStageGimmick::OpenAllGates()//모든 문을 여는 함수
{
	//게이트를 돌면서
	for (auto Gate : Gates)
	{
		//모든 게이트의 로테이션 값을 -90으로 Yaw 값을 설정
		(Gate.Value)->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	}
}

void AABStageGimmick::CloseAllGates()//모든 문을 닫는 함수
{
	//게이트를 돌면서
	for (auto Gate : Gates)
	{
		//기본 로테이션 값을 지정
		(Gate.Value)->SetRelativeRotation(FRotator::ZeroRotator);
	}
}

void AABStageGimmick::SetState(EStageState InNewState)
{
	//델리게이트 어레이로 함수 포인터를 사용해 구현
	CurrentState = InNewState;

	if (StateChangeActions.Contains(InNewState))//해당 상태에 대한 키가 맵 안에 있다면
	{
		//해당 델리게이트가 바인딩되어있다면 실행하도록 처리
		StateChangeActions[CurrentState].StageDelegate.ExecuteIfBound();
	}
}

void AABStageGimmick::SetReady()//스테이지 준비 단계
{
	//가운데의 트리거 활성화. 입장 시 전투 시작해야 하므로 
	StageTrigger->SetCollisionProfileName(CPROFILE_ABTRIGGER);
	for (auto GateTrigger : GateTriggers)
	{
		//각각의 문에 대해서는 콜리전 비활성화
		GateTrigger->SetCollisionProfileName(TEXT("NoCollision"));
	}
	//플레이어가 빠져나가지 못하도록 모든 문 닫음
	OpenAllGates();
}

void AABStageGimmick::SetFight()//대전 시작
{
	//모든 트리거 비활성화
	StageTrigger->SetCollisionProfileName(TEXT("NoCollision"));
	for (auto GateTrigger : GateTriggers)
	{
		GateTrigger->SetCollisionProfileName(TEXT("NoCollision"));
	}
	//문 닫히도록 추가로 확인
	CloseAllGates();
	
	//npc 소환되도록 추가
	GetWorld()->GetTimerManager().SetTimer(OpponentTimerHandle, this, &AABStageGimmick::OnOpponentSpawn, OpponentSpawnTime, false);
}

void AABStageGimmick::SetChooseReward()//보상 선정
{
	StageTrigger->SetCollisionProfileName(TEXT("NoCollision"));
	for (auto GateTrigger : GateTriggers)
	{
		GateTrigger->SetCollisionProfileName(TEXT("NoCollision"));
	}
	//상자 선택하기 전까지는 모든 문이 닫혀있어야 함.
	CloseAllGates();
	//상자를 바로 열 수 있게 함수 추가
	SpawnRewardBoxes();
}

void AABStageGimmick::SetChooseNext()//다음 스테이지 지정
{
	StageTrigger->SetCollisionProfileName(TEXT("NoCollision"));
	for (auto GateTrigger : GateTriggers)
	{
		//게이트에 대한 트리거 활성화
		GateTrigger->SetCollisionProfileName(CPROFILE_ABTRIGGER);
	}
	//문 열어줌
	OpenAllGates();
}

//npc 죽었을 때
void AABStageGimmick::OnOpponentDestroyed(AActor* DestroyedActor)
{
	//다음 단계인 보상 선택 단계로 이동해줌.
	SetState(EStageState::REWARD);
}

//npc 스폰
void AABStageGimmick::OnOpponentSpawn()
{
	//스폰 위치 값 지정
	const FTransform SpawnTransform(GetActorLocation() + FVector::UpVector * 88.0f);;
	//캐스팅
	//SpawnActorDeferred를 사용해 지연처리. 
	AABCharacterNonPlayer* ABOpponentCharacter = GetWorld()->SpawnActorDeferred<AABCharacterNonPlayer>(OpponentClass, SpawnTransform);
	if (ABOpponentCharacter)
	{
		//해당 함수를 연동시킴.
		ABOpponentCharacter->OnDestroyed.AddDynamic(this, &AABStageGimmick::OnOpponentDestroyed);
		//현재 기믹이 가진 CurrentStageNum 지정
		ABOpponentCharacter->SetLevel(CurrentStageNum);
		//해당 함수 호출된 후에 BeginPlay 실행됨
		ABOpponentCharacter->FinishSpawning(SpawnTransform);
	}
}

void AABStageGimmick::OnRewardTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//약참조 배열 순회
	for (const auto& RewardBox : RewardBoxes)
	{
		if (RewardBox.IsValid())//유효성 확신할 수 없어 Isvalid로 살아있는지 확인
		{
			AABItemBox* ValidItemBox = RewardBox.Get();//살아있다면 Get 함수로 포인터 가져옴
			//약참조 배열에 들어가 있는 액터가 현재 이벤트 발생된 액터와 같으면, 아이템 박스에 맡기고 다르면 나머지 박스들 모두 소멸.(보상 하나만 선택해야 하므로)
			AActor* OverlappedBox = OverlappedComponent->GetOwner();
			if (OverlappedBox != ValidItemBox)
			{
				//보상 선택 시 나머지 상자 다 없앰
				ValidItemBox->Destroy();
			}
		}
	}
	//다음 상태로 넘어감
	SetState(EStageState::NEXT);
}

//상자를 여는 로직
void AABStageGimmick::SpawnRewardBoxes()
{
	for (const auto& RewardBoxLocation : RewardBoxLocations)
	{
		FTransform SpawnTransform(GetActorLocation() + RewardBoxLocation.Value + FVector(0.0f, 0.0f, 30.0f));
		//지연 실행
		AABItemBox* RewardBoxActor = GetWorld()->SpawnActorDeferred<AABItemBox>(RewardBoxClass, SpawnTransform);
		if (RewardBoxActor)
		{
			RewardBoxActor->Tags.Add(RewardBoxLocation.Key);
			//트리거 박스를 얻어온 후에 OnComponentBeginOverlap 함수 호출해 OnRewardTriggerBeginOverlap 멤버 함수와 연결해줌.
			RewardBoxActor->GetTrigger()->OnComponentBeginOverlap.AddDynamic(this, &AABStageGimmick::OnRewardTriggerBeginOverlap);
			
			//약참조로 선언된 배열에 해당 스폰된 액터를 추가
			RewardBoxes.Add(RewardBoxActor);
		}
	}
	//약포인터 값 들고와서 FinishSpawning 호출
	for (const auto& RewardBox : RewardBoxes)
	{
		if (RewardBox.IsValid())
		{
			RewardBox.Get()->FinishSpawning(RewardBox.Get()->GetActorTransform());
		}
	}
}