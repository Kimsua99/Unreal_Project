// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ABCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ABCharacterControlData.h"
#include "Animation/AnimMontage.h"
#include "ABComboActionData.h"
#include "Physics/ABCollision.h"
#include "Engine/DamageEvents.h"

// Sets default values
AABCharacterBase::AABCharacterBase()
{
	//폰의 기본 설정, 회전 지정
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	//캡슐에 대한 설정. 루트 컴포넌트.
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	//캐릭터를 구성하고 있는 캡슐 컴포넌트와 스켈레탈 메쉬 컴포넌트에 대한 콜리전 프로필 설정
	//헤더파일에 추가한 캡슐에 대해서는 CPROFILE_ABCAPSULE로 변경. 
	GetCapsuleComponent()->SetCollisionProfileName(CPROFILE_ABCAPSULE);

	//움직임에 해당되는 설정. 점프의 크기, 이동 속도 등 지정.
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	//메쉬에 대한 선언. 캐릭터 모델링 파일을 진행 방향에 맞춰 상대의 위치와 회전을 지정함.
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -100.0f), FRotator(0.0f, -90.0f, 0.0f));
	//애니메이션 모드 지정.
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	//생성된 스켈레탈 메쉬 컴포넌트에 실제 에셋 부착. 
	//콜리전 설정 변경
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	
	//ThirdPersonCharacter에서 제공하는 메쉬와 클래스들을 사용.
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard'"));
	if (CharacterMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClassRef(TEXT("/Game/ArenaBattle/Animation/ABP_ABCharacter.ABP_ABCharacter_C"));
	if (AnimInstanceClassRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(AnimInstanceClassRef.Class);//클래스 정보 가져와서 해당 클래스 값을 설정
	}

	//숄더뷰에 관련된 숄터 데이터 레퍼런스 추가
	static ConstructorHelpers::FObjectFinder<UABCharacterControlData> ShoulderDataRef(TEXT("/Script/ArenaBattle.ABCharacterControlData'/Game/ArenaBattle/CharacterControl/ABC_Shoulder.ABC_Shoulder'"));
	if (ShoulderDataRef.Object)//오브젝트가 있으면
	{
		//CharacterControlManager 맵에 오브젝트 추가
		CharacterControlManager.Add(ECharacterControlType::Shoulder, ShoulderDataRef.Object);
	}

	//쿼터뷰에 관련된 쿼터 데이터 레퍼런스 추가
	static ConstructorHelpers::FObjectFinder<UABCharacterControlData> QuaterDataRef(TEXT("/Script/ArenaBattle.ABCharacterControlData'/Game/ArenaBattle/CharacterControl/ABC_Quater.ABC_Quater'"));
	if (QuaterDataRef.Object)//오브젝트가 있으면
	{
		//CharacterControlManager 맵에 오브젝트 추가
		CharacterControlManager.Add(ECharacterControlType::Quater, QuaterDataRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ComboActionMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/ArenaBattle/Animation/AM_ComboAttack.AM_ComboAttack'"));
	if (ComboActionMontageRef.Object)
	{
		ComboActionMontage = ComboActionMontageRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UABComboActionData> ComboActionDataRef(TEXT("/Script/ArenaBattle.ABComboActionData'/Game/ArenaBattle/CharacterAction/ABA_ComboAttack.ABA_ComboAttack'"));
	if (ComboActionDataRef.Object)
	{
		ComboActionData = ComboActionDataRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> DeadMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/ArenaBattle/Animation/AM_Dead.AM_Dead'"));
	if (DeadMontageRef.Object)
	{
		DeadMontage = DeadMontageRef.Object;
	}

}
void AABCharacterBase::SetCharacterControlData(const UABCharacterControlData* CharacterControlData)
{
	// Pawn 섹션에 관련된 데이터 설정 지시
	bUseControllerRotationYaw = CharacterControlData->bUseControllerRotationYaw;

	// CharacterMovement 섹션에 관련된 데이터 설정 지시
	GetCharacterMovement()->bOrientRotationToMovement = CharacterControlData->bOrientRotationToMovement;
	GetCharacterMovement()->bUseControllerDesiredRotation = CharacterControlData->bUseControllerDesiredRotation;
	GetCharacterMovement()->RotationRate = CharacterControlData->RotationRate;
}

void AABCharacterBase::ProcessComboCommand()//입력을 통해 커맨드 지시가 나오면, 이를 통해 몽타주 재생.
{
	if (CurrentCombo == 0)//플레이가 시작 안 했을 경우
	{
		ComboActionBegin();
		return;
	}

	//입력이 들어올 때를 추가 처리
	//타이머가 설정이 안 되어있을 때 입력이 들어오는 상황 = 타이머가 이미 발동이 되어 시기를 놓쳤거나, 더 이상 진행할 필요가 없는 경우
	if (!ComboTimerHandle.IsValid())
	{
		HasNextComboCommand = false;
	}
	else//타이머가 유효하다면
	{
		//체크하기 이전에 다음 섹션으로 이동시킬 커맨드가 발동했다는 뜻이므로 true 설정
		HasNextComboCommand = true;
	}
}

void AABCharacterBase::ComboActionBegin()//몽타주 시작 시 호출
{
	CurrentCombo = 1;//시작이 되었으므로 콤보 1

	//콤보 시작 시 무브먼트 지정
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);//MOVE_None이면 이동 기능이 없어짐. 온전히 콤보 구현 가능.

	//애니메이션 추가
	const float AttackSpeedRate = 1.0f;//재생 속도 지정. 
	
	//몽타주 플레이
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(ComboActionMontage, AttackSpeedRate);//에셋을 지정해서 어떤 특정 몽타주를 재생하도록 설정 가능. 

	//몽타주가 종료될 때 ComboActionEnd함수가 호출되도록 함.
	FOnMontageEnded EndDelegate;//구조체처럼 선언하고 관련된 함수 정보를 넣음.
	EndDelegate.BindUObject(this, &AABCharacterBase::ComboActionEnd);//이 구조체에 내가 바인딩할 정보 추가. 현재 인스턴스의 ComboActionEnd 함수가 맵핑되어야 함.
	AnimInstance->Montage_SetEndDelegate(EndDelegate, ComboActionMontage);//바인드 시킨 구조체를 넘겨주고, 두 번쨰 인자로 몽타주 지정, 몽타주 종료 시 함수 호출되게 선언.
	
	//콤보 시작 시 타이머 호출
	ComboTimerHandle.Invalidate();//무효화하도록 초기화
	SetComboCheckTimer();
}

//몽타주 종료 시 호출. 몽타주에 설정된 델리게이트를 통해 바로 호출될 수 있도록 파라미터 맞춤.
void AABCharacterBase::ComboActionEnd(UAnimMontage* TargetMontage, bool IsProperlyEnded)
{
	ensure(CurrentCombo != 0);//콤보가 0이 나오면 안되므로 0이 아닌지 검증해주어야 함. 0이면 출력 로그에 에러 생김

	CurrentCombo = 0;//초기화
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);//캐릭터 이동 복원
}

//타이머를 발동시킬 함수
void AABCharacterBase::SetComboCheckTimer()
{
	//배열에 선언되어있는 타이머 정보(프레임 정보)를 얻기 위해 인덱스 값 조정
	int32 ComboIndex = CurrentCombo - 1;
	ensure(ComboActionData->EffectiveFrameCount.IsValidIndex(ComboIndex));//true여야 함

	const float AttackSpeedRate = 1.0f;
	//정상 속도로 진행했을 때 소요된 시간 계산. 발동할 시간 정보 얻어냄.
	float ComboEffectiveTime = (ComboActionData->EffectiveFrameCount[ComboIndex] / ComboActionData->FrameRate) / AttackSpeedRate;

	if (ComboEffectiveTime > 0.0f)//0보다 작으면 발동시킬 필요가 없음.
	{
		//월드로부터 시간 서비스를 받음. 한 번만 발동하도록 함
		GetWorld()->GetTimerManager().SetTimer(ComboTimerHandle, this, &AABCharacterBase::ComboCheck, ComboEffectiveTime, false);
	}
}

//타이머가 발동되면 입력이 들어왔는지 안 들어왔는지 체크하는 함수
void AABCharacterBase::ComboCheck()
{
	//타이머가 발동되면 ComboTimerHandle 초기화
	ComboTimerHandle.Invalidate();
	if (HasNextComboCommand)//다음 커맨드 들어왔으면(타이머 발동 전에 입력이 들어와 true가 되었다면)
	{
		//다음 섹션으로 넘겨줌.
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

		//현재 콤보 값 하나 추가. 지정한 콤보 값을 벗어나면 안되므로 MaxComboCount를 벗어나지 않도록 Clamp를 걸어줌.
		CurrentCombo = FMath::Clamp(CurrentCombo + 1, 1, ComboActionData->MaxComboCount);
		//다음 섹션에 대한 이름 정보를 가져옴,
		//접두사 정보를 가져오고, 콤보 값을 조합해서 스트링으로 만들고 이것을 네임으로 변환해 섹션 이름을 지정
		FName NextSection = *FString::Printf(TEXT("%s%d"), *ComboActionData->MontageSectionNamePrefix, CurrentCombo);
		//해당 섹션으로 재생이 바로 점프됨.
		AnimInstance->Montage_JumpToSection(NextSection, ComboActionMontage);
		//타이머 걸어줌.
		SetComboCheckTimer();
		//입력값 초기화
		HasNextComboCommand = false;
	}
}

void AABCharacterBase::AttackHitCheck()
{
	//트레이스 채널을 활용하여 물체가 서로 충돌되는지 검사
	FHitResult OutHitResult;

	//첫 번째 인자는 콜리전을 분석할 때 태그 정보로 분석하는데, 식별자 정보로 사용되는 인자
	//두 번째 인자는 복잡한 형태의 충돌체, 즉 캡슐이나 구와 같은 볼륨 대상으로 충돌을 감지하면 빠르게 지정 가능. 
	//올라 서는 행위만 가능. 복잡한 콜리전 사용할 경우에만 true 지정
	//세 번째 인자는 무시할 액터인데, 자기 자신에만 무시하면 되므로 this 설정
	//SCENE_QUERY_STAT는 언리얼 엔진이 제공하는 분석 툴로, Attack이라는 태그로 수행한 작업에 대해 조사할 수 있게 태그 추가. 
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack), false, this);

	const float AttackRange = 40.0f;
	const float AttackRadius = 50.0f;
	const float AttackDamage = 30.0f;

	//시작 지점의 경우, 현재 액터의 위치와 액터의 시선 방향에 캡슐 컴포넌트의 반지름 값을 추가해서 정면에 있는 캡슐의 위치에서부터 시작하도록 설정
	const FVector Start = GetActorLocation() + GetActorForwardVector() * GetCapsuleComponent()->GetScaledCapsuleRadius();
	//끝 지점의 경우, 시작 지점에서 40cm만큼 앞에서 끝나도록 설정.
	const FVector End = Start + GetActorForwardVector() * AttackRange;

	//SweepSingleByChannel는 월드가 제공하는 서비스이므로 GetWorld 함수를 호출해 포인터 얻어옴. 
	//결과 값을 받아올 수 있는 FHitResult라는 구조체를 넣어줌.
	//시작과 끝지점, 구체를 만들어 투사해야 하는데 투사의 시작과 끝 지점을 지정해줌.
	//구체의 경우 MakeSphere을 통해 구체의 영역을 지정할 수 있는데, 반지름이 50센치인 구체 생성.
	//사용할 채널은 전처리기에 추가한 CCHANNEL_ABACTION으로 지정. 
	bool HitDetected = GetWorld()->SweepSingleByChannel(OutHitResult, Start, End, FQuat::Identity, CCHANNEL_ABACTION, FCollisionShape::MakeSphere(AttackRadius), Params);

	if (HitDetected)//무언가 감지된 경우
	{
		//공격이 히트된 경우 상대방에게 데미지 전달
		//데미지 종류 지정
		FDamageEvent DamageEvent;
		OutHitResult.GetActor()->TakeDamage(AttackDamage, DamageEvent, GetController(), this);
	}

#if ENABLE_DRAW_DEBUG

	//캡슐의 원점의 경우에는 시작 지점 + (끝 - 시작)의 절반
	FVector CapsuleOrigin = Start + (End - Start) * 0.5f;

	//중심으로부터 시작지점까지의 거리
	float CapsuleHalfHeight = AttackRange * 0.5f;

	//충돌 -> 녹색, 충돌 x -> 적색
	FColor DrawColor = HitDetected ? FColor::Green : FColor::Red;

	//월드에서 제공하는 서비스. 중심으로부터 시작지점까지의 거리와 캡슐의 반지름을 넣어줌. 캡슐을 눕혀야 하므로 시선 방향으로 눕혀지도록 회전 가해줌.
	//마지막 두 인자는 계속해서 유지할 것인지, 계속해서 유지하지 않는다면 몇 초 동안 그릴 것인지 지정. 5초동안 그림.
	DrawDebugCapsule(GetWorld(), CapsuleOrigin, CapsuleHalfHeight, AttackRadius, FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(), DrawColor, false, 5.0f);

#endif
}
float AABCharacterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	//상위함수 호출. EventInstigator는 피해입힌 가해자이고, DamageCauser는 피해를 입힌 가해자가 사용한 무기 또는 빙의한 폰의 액터 정보들이 들어옴.
	//누구에게서 어떤 공격을 받았는지 파악 가능.
	//만약 방어력이 있으면 여기 있는 DamageAmount를 조정해 최종 DamageAmount를 리턴할 수 있음.
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	SetDead();

	return DamageAmount;//최종적으로 받은 데미지 양을 리턴
}

void AABCharacterBase::SetDead()//죽는 상태 구현 함수
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);//이동을 제한걺
	PlayDeadAnimation();//죽는 모션 재생
	SetActorEnableCollision(false);//콜리전 자체 기능 끔. 죽은 NPC는 캐릭터의 이동을 방해하지 않게 됨. 
}

void AABCharacterBase::PlayDeadAnimation()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->StopAllMontages(0.0f);//기존의 공격 모션 진행하고 있으면 모든 몽타주 중지시킴. 
	AnimInstance->Montage_Play(DeadMontage, 1.0f);//죽는 몽타주 플레이, 정상속도 재생
}