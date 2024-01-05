// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ABCharacterPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "ABCharacterControlData.h"

AABCharacterPlayer::AABCharacterPlayer()
{
	//카메라 관련된 오브젝트 생성
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	//SpringArmComponent을 루트 컴포넌트에 부착
	CameraBoom->SetupAttachment(RootComponent);
	//4미터 길이로 설정
	CameraBoom->TargetArmLength = 400.0f;
	//회전에 대한 설정
	CameraBoom->bUsePawnControlRotation = true;
	
	//카메라 기본값 설정
	//카메라 생성
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	//카메라 지지대인 SpringArmComponent에 부착. 부착 시에 소켓이라는 특별한 지시자 지정하면 SpringArm끝에 자동으로 달라붙게 됨,
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// Input
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionJumpRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ArenaBattle/Input/Actions/IA_Jump.IA_Jump'"));
	if (nullptr != InputActionJumpRef.Object)
	{
		JumpAction = InputActionJumpRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputChangeActionControlRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ArenaBattle/Input/Actions/IA_ChangeControl.IA_ChangeControl'"));
	if (nullptr != InputChangeActionControlRef.Object)
	{
		ChangeControlAction = InputChangeActionControlRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionShoulderMoveRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ArenaBattle/Input/Actions/IA_ShoulderMove.IA_ShoulderMove'"));
	if (nullptr != InputActionShoulderMoveRef.Object)
	{
		ShoulderMoveAction = InputActionShoulderMoveRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionShoulderLookRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ArenaBattle/Input/Actions/IA_ShoulderLook.IA_ShoulderLook'"));
	if (nullptr != InputActionShoulderLookRef.Object)
	{
		ShoulderLookAction = InputActionShoulderLookRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionQuaterMoveRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ArenaBattle/Input/Actions/IA_QuaterMove.IA_QuaterMove'"));
	if (nullptr != InputActionQuaterMoveRef.Object)
	{
		QuaterMoveAction = InputActionQuaterMoveRef.Object;
	}
	//현재 어떤 뷰 상태인지를 확인하기 위해 .h에 선언한 열거형 타입을 통해 변수 선언. 기본 값을 Quater로 초기화.
	CurrentCharacterControlType = ECharacterControlType::Quater;
}
void AABCharacterPlayer::BeginPlay()//매핑 컨텍스트 추가. 플레이어를 대상으로 설계된 전용 클래스이므로 CastChecked를 사용.
{
	Super::BeginPlay();
	//SetCharacterControl 함수 호출해서 쿼터뷰 컨트롤로 바꿔치기하도록 변경
	SetCharacterControl(CurrentCharacterControlType);
}
//여기서 입력을 받을 때 EnhancedInputComponent를 사용하는데, 사용되지 않은 경우도 있으므로 에러를 발생하도록 CastChecked 함수를 사용. 반드시 EnhancedInputComponent를 사용하게 해줌.
void AABCharacterPlayer::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	//성공적으로 캐스팅이 된 경우, 앞서 지정한 언리얼 오브젝트들과 Move, Look 함수에 대해 바인딩 진행.
	//점프의 경우 실제 캐릭터가 제공하는 Jump와 StopJumping 함수를 직접 연결해 관련 액션 수행하도록 연결.
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	//PlayerInputComponent에서 사전에 매핑을 진행할 때 관련된 매핑 재조정
	EnhancedInputComponent->BindAction(ChangeControlAction, ETriggerEvent::Triggered, this, &AABCharacterPlayer::ChangeCharacterControl);
	EnhancedInputComponent->BindAction(ShoulderMoveAction, ETriggerEvent::Triggered, this, &AABCharacterPlayer::ShoulderMove);
	EnhancedInputComponent->BindAction(ShoulderLookAction, ETriggerEvent::Triggered, this, &AABCharacterPlayer::ShoulderLook);
	EnhancedInputComponent->BindAction(QuaterMoveAction, ETriggerEvent::Triggered, this, &AABCharacterPlayer::QuaterMove);
}

void AABCharacterPlayer::ChangeCharacterControl()//v키를 눌러 컨트롤러 변경했을 경우
{
	//현재 캐릭터 컨트롤 타입의 enum 값을 보고 반대쪽 enum 값으로 변경하도록 SetCharacterControl함수 호출
	if (CurrentCharacterControlType == ECharacterControlType::Quater)
	{
		SetCharacterControl(ECharacterControlType::Shoulder);
	}
	else if (CurrentCharacterControlType == ECharacterControlType::Shoulder)
	{
		SetCharacterControl(ECharacterControlType::Quater);
	}
}

void AABCharacterPlayer::SetCharacterControl(ECharacterControlType NewCharacterControlType)//v 눌렀을 경우 실제 동작하는 함수
{
	//상위 클래스에 선언된 컨트롤 매니저에 있는 컨트롤 데이터 에셋 가져옴.
	UABCharacterControlData* NewCharacterControl = CharacterControlManager[NewCharacterControlType];
	check(NewCharacterControl);//컨트롤 데이터 있는지 확인

	SetCharacterControlData(NewCharacterControl);//아래의 기본 속성들 호출

	//컨트롤러를 가져옴. 반드시 가져와야 하므로 CastChecked 사용.
	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	//향상된 인풋 시스템에서 실제 인풋 매핑 컨텍스트를 운영하는 Subsystem을 가져옴.
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		//기존의 인풋 매핑 컨텍스트를 모두 제거
		Subsystem->ClearAllMappings();

		//컨트롤 데이터 에셋에 선언된 인풋 매핑 컨텍스트 추가
		UInputMappingContext* NewMappingContext = NewCharacterControl->InputMappingContext;
		if (NewMappingContext)
		{
			Subsystem->AddMappingContext(NewMappingContext, 0);
		}
	}
	//현재 컨트롤 데이터 타입을 새로운 컨트롤 데이터 타입으로 변경
	CurrentCharacterControlType = NewCharacterControlType;
}

void AABCharacterPlayer::SetCharacterControlData(const UABCharacterControlData* CharacterControlData)
{
	Super::SetCharacterControlData(CharacterControlData);//상위 클래스 함수 호출

	//카메라 스프링 암에 대한 설정 추가
	CameraBoom->TargetArmLength = CharacterControlData->TargetArmLength;
	CameraBoom->SetRelativeRotation(CharacterControlData->RelativeRotation);
	CameraBoom->bUsePawnControlRotation = CharacterControlData->bUsePawnControlRotation;
	CameraBoom->bInheritPitch = CharacterControlData->bInheritPitch;
	CameraBoom->bInheritYaw = CharacterControlData->bInheritYaw;
	CameraBoom->bInheritRoll = CharacterControlData->bInheritRoll;
	CameraBoom->bDoCollisionTest = CharacterControlData->bDoCollisionTest;
}

//FInputActionValue에서 x,y값을 가져온 후에 이것들을 무브먼트 컴포넌트와 연결하여 실질적으로 이동이나 회전을 설정함으로써 SpringArm이 컨트롤러를 바라보게 설정
void AABCharacterPlayer::ShoulderMove(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.X);
	AddMovementInput(RightDirection, MovementVector.Y);
}

void AABCharacterPlayer::ShoulderLook(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

void AABCharacterPlayer::QuaterMove(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	//현재 MovementVector를 받아 크기가 1이 되도록 조정
	float InputSizeSquared = MovementVector.SquaredLength();
	float MovementVectorSize = 1.0f;
	float MovementVectorSizeSquared = MovementVector.SquaredLength();
	if (MovementVectorSizeSquared > 1.0f)
	{
		MovementVector.Normalize();
		MovementVectorSizeSquared = 1.0f;
	}
	else
	{
		MovementVectorSize = FMath::Sqrt(MovementVectorSizeSquared);
	}

	//x,y 값을 Modifiers를 통해 조절
	FVector MoveDirection = FVector(MovementVector.X, MovementVector.Y, 0.0f);
	//ControlRotation을 foward 방향을 사용하도록 지정. -> 캐릭터가 자동으로 이동하는 방향으로 회전함.
	GetController()->SetControlRotation(FRotationMatrix::MakeFromX(MoveDirection).Rotator());
	AddMovementInput(MoveDirection, MovementVectorSize);
}