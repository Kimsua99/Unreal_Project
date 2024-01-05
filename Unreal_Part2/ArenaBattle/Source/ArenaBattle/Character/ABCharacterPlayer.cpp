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
	//ī�޶� ���õ� ������Ʈ ����
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	//SpringArmComponent�� ��Ʈ ������Ʈ�� ����
	CameraBoom->SetupAttachment(RootComponent);
	//4���� ���̷� ����
	CameraBoom->TargetArmLength = 400.0f;
	//ȸ���� ���� ����
	CameraBoom->bUsePawnControlRotation = true;
	
	//ī�޶� �⺻�� ����
	//ī�޶� ����
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	//ī�޶� �������� SpringArmComponent�� ����. ���� �ÿ� �����̶�� Ư���� ������ �����ϸ� SpringArm���� �ڵ����� �޶�ٰ� ��,
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
	//���� � �� ���������� Ȯ���ϱ� ���� .h�� ������ ������ Ÿ���� ���� ���� ����. �⺻ ���� Quater�� �ʱ�ȭ.
	CurrentCharacterControlType = ECharacterControlType::Quater;
}
void AABCharacterPlayer::BeginPlay()//���� ���ؽ�Ʈ �߰�. �÷��̾ ������� ����� ���� Ŭ�����̹Ƿ� CastChecked�� ���.
{
	Super::BeginPlay();
	//SetCharacterControl �Լ� ȣ���ؼ� ���ͺ� ��Ʈ�ѷ� �ٲ�ġ���ϵ��� ����
	SetCharacterControl(CurrentCharacterControlType);
}
//���⼭ �Է��� ���� �� EnhancedInputComponent�� ����ϴµ�, ������ ���� ��쵵 �����Ƿ� ������ �߻��ϵ��� CastChecked �Լ��� ���. �ݵ�� EnhancedInputComponent�� ����ϰ� ����.
void AABCharacterPlayer::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	//���������� ĳ������ �� ���, �ռ� ������ �𸮾� ������Ʈ��� Move, Look �Լ��� ���� ���ε� ����.
	//������ ��� ���� ĳ���Ͱ� �����ϴ� Jump�� StopJumping �Լ��� ���� ������ ���� �׼� �����ϵ��� ����.
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	//PlayerInputComponent���� ������ ������ ������ �� ���õ� ���� ������
	EnhancedInputComponent->BindAction(ChangeControlAction, ETriggerEvent::Triggered, this, &AABCharacterPlayer::ChangeCharacterControl);
	EnhancedInputComponent->BindAction(ShoulderMoveAction, ETriggerEvent::Triggered, this, &AABCharacterPlayer::ShoulderMove);
	EnhancedInputComponent->BindAction(ShoulderLookAction, ETriggerEvent::Triggered, this, &AABCharacterPlayer::ShoulderLook);
	EnhancedInputComponent->BindAction(QuaterMoveAction, ETriggerEvent::Triggered, this, &AABCharacterPlayer::QuaterMove);
}

void AABCharacterPlayer::ChangeCharacterControl()//vŰ�� ���� ��Ʈ�ѷ� �������� ���
{
	//���� ĳ���� ��Ʈ�� Ÿ���� enum ���� ���� �ݴ��� enum ������ �����ϵ��� SetCharacterControl�Լ� ȣ��
	if (CurrentCharacterControlType == ECharacterControlType::Quater)
	{
		SetCharacterControl(ECharacterControlType::Shoulder);
	}
	else if (CurrentCharacterControlType == ECharacterControlType::Shoulder)
	{
		SetCharacterControl(ECharacterControlType::Quater);
	}
}

void AABCharacterPlayer::SetCharacterControl(ECharacterControlType NewCharacterControlType)//v ������ ��� ���� �����ϴ� �Լ�
{
	//���� Ŭ������ ����� ��Ʈ�� �Ŵ����� �ִ� ��Ʈ�� ������ ���� ������.
	UABCharacterControlData* NewCharacterControl = CharacterControlManager[NewCharacterControlType];
	check(NewCharacterControl);//��Ʈ�� ������ �ִ��� Ȯ��

	SetCharacterControlData(NewCharacterControl);//�Ʒ��� �⺻ �Ӽ��� ȣ��

	//��Ʈ�ѷ��� ������. �ݵ�� �����;� �ϹǷ� CastChecked ���.
	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	//���� ��ǲ �ý��ۿ��� ���� ��ǲ ���� ���ؽ�Ʈ�� ��ϴ� Subsystem�� ������.
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		//������ ��ǲ ���� ���ؽ�Ʈ�� ��� ����
		Subsystem->ClearAllMappings();

		//��Ʈ�� ������ ���¿� ����� ��ǲ ���� ���ؽ�Ʈ �߰�
		UInputMappingContext* NewMappingContext = NewCharacterControl->InputMappingContext;
		if (NewMappingContext)
		{
			Subsystem->AddMappingContext(NewMappingContext, 0);
		}
	}
	//���� ��Ʈ�� ������ Ÿ���� ���ο� ��Ʈ�� ������ Ÿ������ ����
	CurrentCharacterControlType = NewCharacterControlType;
}

void AABCharacterPlayer::SetCharacterControlData(const UABCharacterControlData* CharacterControlData)
{
	Super::SetCharacterControlData(CharacterControlData);//���� Ŭ���� �Լ� ȣ��

	//ī�޶� ������ �Ͽ� ���� ���� �߰�
	CameraBoom->TargetArmLength = CharacterControlData->TargetArmLength;
	CameraBoom->SetRelativeRotation(CharacterControlData->RelativeRotation);
	CameraBoom->bUsePawnControlRotation = CharacterControlData->bUsePawnControlRotation;
	CameraBoom->bInheritPitch = CharacterControlData->bInheritPitch;
	CameraBoom->bInheritYaw = CharacterControlData->bInheritYaw;
	CameraBoom->bInheritRoll = CharacterControlData->bInheritRoll;
	CameraBoom->bDoCollisionTest = CharacterControlData->bDoCollisionTest;
}

//FInputActionValue���� x,y���� ������ �Ŀ� �̰͵��� �����Ʈ ������Ʈ�� �����Ͽ� ���������� �̵��̳� ȸ���� ���������ν� SpringArm�� ��Ʈ�ѷ��� �ٶ󺸰� ����
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

	//���� MovementVector�� �޾� ũ�Ⱑ 1�� �ǵ��� ����
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

	//x,y ���� Modifiers�� ���� ����
	FVector MoveDirection = FVector(MovementVector.X, MovementVector.Y, 0.0f);
	//ControlRotation�� foward ������ ����ϵ��� ����. -> ĳ���Ͱ� �ڵ����� �̵��ϴ� �������� ȸ����.
	GetController()->SetControlRotation(FRotationMatrix::MakeFromX(MoveDirection).Rotator());
	AddMovementInput(MoveDirection, MovementVectorSize);
}