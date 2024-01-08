// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ABCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ABCharacterControlData.h"
#include "Animation/AnimMontage.h"
#include "ABComboActionData.h"

// Sets default values
AABCharacterBase::AABCharacterBase()
{
	//���� �⺻ ����, ȸ�� ����
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	//ĸ���� ���� ����. ��Ʈ ������Ʈ.
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));

	//�����ӿ� �ش�Ǵ� ����. ������ ũ��, �̵� �ӵ� �� ����.
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	//�޽��� ���� ����. ĳ���� �𵨸� ������ ���� ���⿡ ���� ����� ��ġ�� ȸ���� ������.
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -100.0f), FRotator(0.0f, -90.0f, 0.0f));
	//�ִϸ��̼� ��� ����.
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	//������ ���̷�Ż �޽� ������Ʈ�� ���� ���� ����. 
	GetMesh()->SetCollisionProfileName(TEXT("CharacterMesh"));
	
	//ThirdPersonCharacter���� �����ϴ� �޽��� Ŭ�������� ���.
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard'"));
	if (CharacterMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClassRef(TEXT("/Game/ArenaBattle/Animation/ABP_ABCharacter.ABP_ABCharacter_C"));
	if (AnimInstanceClassRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(AnimInstanceClassRef.Class);//Ŭ���� ���� �����ͼ� �ش� Ŭ���� ���� ����
	}

	//����信 ���õ� ���� ������ ���۷��� �߰�
	static ConstructorHelpers::FObjectFinder<UABCharacterControlData> ShoulderDataRef(TEXT("/Script/ArenaBattle.ABCharacterControlData'/Game/ArenaBattle/CharacterControl/ABC_Shoulder.ABC_Shoulder'"));
	if (ShoulderDataRef.Object)//������Ʈ�� ������
	{
		//CharacterControlManager �ʿ� ������Ʈ �߰�
		CharacterControlManager.Add(ECharacterControlType::Shoulder, ShoulderDataRef.Object);
	}

	//���ͺ信 ���õ� ���� ������ ���۷��� �߰�
	static ConstructorHelpers::FObjectFinder<UABCharacterControlData> QuaterDataRef(TEXT("/Script/ArenaBattle.ABCharacterControlData'/Game/ArenaBattle/CharacterControl/ABC_Quater.ABC_Quater'"));
	if (QuaterDataRef.Object)//������Ʈ�� ������
	{
		//CharacterControlManager �ʿ� ������Ʈ �߰�
		CharacterControlManager.Add(ECharacterControlType::Quater, QuaterDataRef.Object);
	}
}
void AABCharacterBase::SetCharacterControlData(const UABCharacterControlData* CharacterControlData)
{
	// Pawn ���ǿ� ���õ� ������ ���� ����
	bUseControllerRotationYaw = CharacterControlData->bUseControllerRotationYaw;

	// CharacterMovement ���ǿ� ���õ� ������ ���� ����
	GetCharacterMovement()->bOrientRotationToMovement = CharacterControlData->bOrientRotationToMovement;
	GetCharacterMovement()->bUseControllerDesiredRotation = CharacterControlData->bUseControllerDesiredRotation;
	GetCharacterMovement()->RotationRate = CharacterControlData->RotationRate;
}

void AABCharacterBase::ProcessComboCommand()//�Է��� ���� Ŀ�ǵ� ���ð� ������, �̸� ���� ��Ÿ�� ���.
{
	if (CurrentCombo == 0)//�÷��̰� ���� �� ���� ���
	{
		ComboActionBegin();
		return;
	}

	//�Է��� ���� ���� �߰� ó��
	//Ÿ�̸Ӱ� ������ �� �Ǿ����� �� �Է��� ������ ��Ȳ = Ÿ�̸Ӱ� �̹� �ߵ��� �Ǿ� �ñ⸦ ���ưų�, �� �̻� ������ �ʿ䰡 ���� ���
	if (!ComboTimerHandle.IsValid())
	{
		HasNextComboCommand = false;
	}
	else//Ÿ�̸Ӱ� ��ȿ�ϴٸ�
	{
		//üũ�ϱ� ������ ���� �������� �̵���ų Ŀ�ǵ尡 �ߵ��ߴٴ� ���̹Ƿ� true ����
		HasNextComboCommand = true;
	}
}

void AABCharacterBase::ComboActionBegin()//��Ÿ�� ���� �� ȣ��
{
	CurrentCombo = 1;//������ �Ǿ����Ƿ� �޺� 1

	//�޺� ���� �� �����Ʈ ����
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);//MOVE_None�̸� �̵� ����� ������. ������ �޺� ���� ����.

	//�ִϸ��̼� �߰�
	const float AttackSpeedRate = 1.0f;//��� �ӵ� ����. 
	
	//��Ÿ�� �÷���
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(ComboActionMontage, AttackSpeedRate);//������ �����ؼ� � Ư�� ��Ÿ�ָ� ����ϵ��� ���� ����. 

	//��Ÿ�ְ� ����� �� ComboActionEnd�Լ��� ȣ��ǵ��� ��.
	FOnMontageEnded EndDelegate;//����üó�� �����ϰ� ���õ� �Լ� ������ ����.
	EndDelegate.BindUObject(this, &AABCharacterBase::ComboActionEnd);//�� ����ü�� ���� ���ε��� ���� �߰�. ���� �ν��Ͻ��� ComboActionEnd �Լ��� ���εǾ�� ��.
	AnimInstance->Montage_SetEndDelegate(EndDelegate, ComboActionMontage);//���ε� ��Ų ����ü�� �Ѱ��ְ�, �� ���� ���ڷ� ��Ÿ�� ����, ��Ÿ�� ���� �� �Լ� ȣ��ǰ� ����.
	
	//�޺� ���� �� Ÿ�̸� ȣ��
	ComboTimerHandle.Invalidate();//��ȿȭ�ϵ��� �ʱ�ȭ
	SetComboCheckTimer();
}

//��Ÿ�� ���� �� ȣ��. ��Ÿ�ֿ� ������ ��������Ʈ�� ���� �ٷ� ȣ��� �� �ֵ��� �Ķ���� ����.
void AABCharacterBase::ComboActionEnd(UAnimMontage* TargetMontage, bool IsProperlyEnded)
{
	ensure(CurrentCombo != 0);//�޺��� 0�� ������ �ȵǹǷ� 0�� �ƴ��� �������־�� ��. 0�̸� ��� �α׿� ���� ����

	CurrentCombo = 0;//�ʱ�ȭ
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);//ĳ���� �̵� ����
}

//Ÿ�̸Ӹ� �ߵ���ų �Լ�
void AABCharacterBase::SetComboCheckTimer()
{
	//�迭�� ����Ǿ��ִ� Ÿ�̸� ����(������ ����)�� ��� ���� �ε��� �� ����
	int32 ComboIndex = CurrentCombo - 1;
	ensure(ComboActionData->EffectiveFrameCount.IsValidIndex(ComboIndex));//true���� ��

	const float AttackSpeedRate = 1.0f;
	//���� �ӵ��� �������� �� �ҿ�� �ð� ���. �ߵ��� �ð� ���� ��.
	float ComboEffectiveTime = (ComboActionData->EffectiveFrameCount[ComboIndex] / ComboActionData->FrameRate) / AttackSpeedRate;

	if (ComboEffectiveTime > 0.0f)//0���� ������ �ߵ���ų �ʿ䰡 ����.
	{
		//����κ��� �ð� ���񽺸� ����. �� ���� �ߵ��ϵ��� ��
		GetWorld()->GetTimerManager().SetTimer(ComboTimerHandle, this, &AABCharacterBase::ComboCheck, ComboEffectiveTime, false);
	}
}

//Ÿ�̸Ӱ� �ߵ��Ǹ� �Է��� ���Դ��� �� ���Դ��� üũ�ϴ� �Լ�
void AABCharacterBase::ComboCheck()
{
	//Ÿ�̸Ӱ� �ߵ��Ǹ� ComboTimerHandle �ʱ�ȭ
	ComboTimerHandle.Invalidate();
	if (HasNextComboCommand)//���� Ŀ�ǵ� ��������(Ÿ�̸� �ߵ� ���� �Է��� ���� true�� �Ǿ��ٸ�)
	{
		//���� �������� �Ѱ���.
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

		//���� �޺� �� �ϳ� �߰�. ������ �޺� ���� ����� �ȵǹǷ� MaxComboCount�� ����� �ʵ��� Clamp�� �ɾ���.
		CurrentCombo = FMath::Clamp(CurrentCombo + 1, 1, ComboActionData->MaxComboCount);
		//���� ���ǿ� ���� �̸� ������ ������,
		//���λ� ������ ��������, �޺� ���� �����ؼ� ��Ʈ������ ����� �̰��� �������� ��ȯ�� ���� �̸��� ����
		FName NextSection = *FString::Printf(TEXT("%s%d"), *ComboActionData->MontageSectionNamePrefix, CurrentCombo);
		//�ش� �������� ����� �ٷ� ������.
		AnimInstance->Montage_JumpToSection(NextSection, ComboActionMontage);
		//Ÿ�̸� �ɾ���.
		SetComboCheckTimer();
		//�Է°� �ʱ�ȭ
		HasNextComboCommand = false;
	}
}