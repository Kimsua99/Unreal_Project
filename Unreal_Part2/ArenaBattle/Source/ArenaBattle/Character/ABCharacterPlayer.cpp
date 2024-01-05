// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ABCharacterPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

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

	// Input. �Է��� ������Ʈ�鿡 ���� ��ü�� �����ͼ� ������ ������ ��.
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContextRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/ArenaBattle/Input/IMC_Default.IMC_Default'"));
	if (nullptr != InputMappingContextRef.Object)
	{
		DefaultMappingContext = InputMappingContextRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionMoveRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ArenaBattle/Input/Actions/IA_Move.IA_Move'"));
	if (nullptr != InputActionMoveRef.Object)
	{
		MoveAction = InputActionMoveRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionJumpRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ArenaBattle/Input/Actions/IA_Jump.IA_Jump'"));
	if (nullptr != InputActionJumpRef.Object)
	{
		JumpAction = InputActionJumpRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionLookRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ArenaBattle/Input/Actions/IA_Look.IA_Look'"));
	if (nullptr != InputActionLookRef.Object)
	{
		LookAction = InputActionLookRef.Object;
	}
}
void AABCharacterPlayer::BeginPlay()//���� ���ؽ�Ʈ �߰�. �÷��̾ ������� ����� ���� Ŭ�����̹Ƿ� CastChecked�� ���.
{
	Super::BeginPlay();

	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	//Subsystem�̶�� �ϴ� ��ǲ �ý����� �����ͼ� ���� ���ؽ�Ʈ ������ �߰�����.
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		//�켱������ �����ؼ� �پ��� �Էµ��� ���� ��ĥ ������ �켱������ ���� �Է¿� ���� �׼ǵ��� ���ε��Ǿ� ������ �� �ֵ��� ����.
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
		//Subsystem->RemoveMappingContext(DefaultMappingContext);
	}

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
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AABCharacterPlayer::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AABCharacterPlayer::Look);
}

//FInputActionValue���� x,y���� ������ �Ŀ� �̰͵��� �����Ʈ ������Ʈ�� �����Ͽ� ���������� �̵��̳� ȸ���� ���������ν� SpringArm�� ��Ʈ�ѷ��� �ٶ󺸰� ����
void AABCharacterPlayer::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.X);
	AddMovementInput(RightDirection, MovementVector.Y);
}

void AABCharacterPlayer::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}