// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ABCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ABCharacterControlData.h"
#include "Animation/AnimMontage.h"
#include "ABComboActionData.h"
#include "Physics/ABCollision.h"
#include "Engine/DamageEvents.h"
#include "CharacterStat/ABCharacterStatComponent.h"
#include "UI/ABWidgetComponent.h"
#include "UI/ABHpBarWidget.h"
#include "Item/ABWeaponItemData.h"

//�𸮾��� �����ϴ� �α� ��ũ��
DEFINE_LOG_CATEGORY(LogABCharacter);

// Sets default values
AABCharacterBase::AABCharacterBase()
{
	//���� �⺻ ����, ȸ�� ����
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	//ĸ���� ���� ����. ��Ʈ ������Ʈ.
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	//ĳ���͸� �����ϰ� �ִ� ĸ�� ������Ʈ�� ���̷�Ż �޽� ������Ʈ�� ���� �ݸ��� ������ ����
	//������Ͽ� �߰��� ĸ���� ���ؼ��� CPROFILE_ABCAPSULE�� ����. 
	GetCapsuleComponent()->SetCollisionProfileName(CPROFILE_ABCAPSULE);

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
	//�ݸ��� ���� ����
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	
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

	// Stat Component 
	Stat = CreateDefaultSubobject<UABCharacterStatComponent>(TEXT("Stat"));

	// Widget Component 
	HpBar = CreateDefaultSubobject<UABWidgetComponent>(TEXT("Widget"));
	HpBar->SetupAttachment(GetMesh());
	HpBar->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));
	static ConstructorHelpers::FClassFinder<UUserWidget> HpBarWidgetRef(TEXT("/Game/ArenaBattle/UI/WBP_HpBar.WBP_HpBar_C"));
	if (HpBarWidgetRef.Class)
	{
		HpBar->SetWidgetClass(HpBarWidgetRef.Class);
		HpBar->SetWidgetSpace(EWidgetSpace::Screen);
		HpBar->SetDrawSize(FVector2D(150.0f, 15.0f));
		HpBar->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	// Item Actions
	
	//���ڷ� ��������Ʈ�� CreateUObject�� �Ｎ���� ������ �־���.
	//3���� �Լ��� ���ε�����.
	TakeItemActions.Add(FTakeItemDelegateWrapper(FOnTakeItemDelegate::CreateUObject(this, &AABCharacterBase::EquipWeapon)));
	TakeItemActions.Add(FTakeItemDelegateWrapper(FOnTakeItemDelegate::CreateUObject(this, &AABCharacterBase::DrinkPotion)));
	TakeItemActions.Add(FTakeItemDelegateWrapper(FOnTakeItemDelegate::CreateUObject(this, &AABCharacterBase::ReadScroll)));

	// Weapon Component
	//������ ��, ĳ������ Ư�� ���� ���Ⱑ �׻� �����ǵ��� ���� �̸� ����.
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(), TEXT("hand_rSocket"));
}

void AABCharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//���� Ŭ������ �ִ� SetDead�� �����ǵ��� ��������Ʈ ����
	Stat->OnHpZero.AddUObject(this, &AABCharacterBase::SetDead);
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
	const float AttackSpeedRate = Stat->GetTotalStat().AttackSpeed;//��� �ӵ� ����. 
	
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

	NotifyComboActionEnd();
}

void AABCharacterBase::NotifyComboActionEnd()
{

}

//Ÿ�̸Ӹ� �ߵ���ų �Լ�
void AABCharacterBase::SetComboCheckTimer()
{
	//�迭�� ����Ǿ��ִ� Ÿ�̸� ����(������ ����)�� ��� ���� �ε��� �� ����
	int32 ComboIndex = CurrentCombo - 1;
	ensure(ComboActionData->EffectiveFrameCount.IsValidIndex(ComboIndex));//true���� ��

	const float AttackSpeedRate = Stat->GetTotalStat().AttackSpeed;
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

void AABCharacterBase::AttackHitCheck()
{
	//Ʈ���̽� ä���� Ȱ���Ͽ� ��ü�� ���� �浹�Ǵ��� �˻�
	FHitResult OutHitResult;

	//ù ��° ���ڴ� �ݸ����� �м��� �� �±� ������ �м��ϴµ�, �ĺ��� ������ ���Ǵ� ����
	//�� ��° ���ڴ� ������ ������ �浹ü, �� ĸ���̳� ���� ���� ���� ������� �浹�� �����ϸ� ������ ���� ����. 
	//�ö� ���� ������ ����. ������ �ݸ��� ����� ��쿡�� true ����
	//�� ��° ���ڴ� ������ �����ε�, �ڱ� �ڽſ��� �����ϸ� �ǹǷ� this ����
	//SCENE_QUERY_STAT�� �𸮾� ������ �����ϴ� �м� ����, Attack�̶�� �±׷� ������ �۾��� ���� ������ �� �ְ� �±� �߰�. 
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack), false, this);

	const float AttackRange = Stat->GetTotalStat().AttackRange;
	const float AttackRadius = Stat->GetAttackRadius();
	const float AttackDamage = Stat->GetTotalStat().Attack;

	//���� ������ ���, ���� ������ ��ġ�� ������ �ü� ���⿡ ĸ�� ������Ʈ�� ������ ���� �߰��ؼ� ���鿡 �ִ� ĸ���� ��ġ�������� �����ϵ��� ����
	const FVector Start = GetActorLocation() + GetActorForwardVector() * GetCapsuleComponent()->GetScaledCapsuleRadius();
	//�� ������ ���, ���� �������� 40cm��ŭ �տ��� �������� ����.
	const FVector End = Start + GetActorForwardVector() * AttackRange;

	//SweepSingleByChannel�� ���尡 �����ϴ� �����̹Ƿ� GetWorld �Լ��� ȣ���� ������ ����. 
	//��� ���� �޾ƿ� �� �ִ� FHitResult��� ����ü�� �־���.
	//���۰� ������, ��ü�� ����� �����ؾ� �ϴµ� ������ ���۰� �� ������ ��������.
	//��ü�� ��� MakeSphere�� ���� ��ü�� ������ ������ �� �ִµ�, �������� 50��ġ�� ��ü ����.
	//����� ä���� ��ó���⿡ �߰��� CCHANNEL_ABACTION���� ����. 
	bool HitDetected = GetWorld()->SweepSingleByChannel(OutHitResult, Start, End, FQuat::Identity, CCHANNEL_ABACTION, FCollisionShape::MakeSphere(AttackRadius), Params);

	if (HitDetected)//���� ������ ���
	{
		//������ ��Ʈ�� ��� ���濡�� ������ ����
		//������ ���� ����
		FDamageEvent DamageEvent;
		OutHitResult.GetActor()->TakeDamage(AttackDamage, DamageEvent, GetController(), this);
	}

#if ENABLE_DRAW_DEBUG

	//ĸ���� ������ ��쿡�� ���� ���� + (�� - ����)�� ����
	FVector CapsuleOrigin = Start + (End - Start) * 0.5f;

	//�߽����κ��� �������������� �Ÿ�
	float CapsuleHalfHeight = AttackRange * 0.5f;

	//�浹 -> ���, �浹 x -> ����
	FColor DrawColor = HitDetected ? FColor::Green : FColor::Red;

	//���忡�� �����ϴ� ����. �߽����κ��� �������������� �Ÿ��� ĸ���� �������� �־���. ĸ���� ������ �ϹǷ� �ü� �������� ���������� ȸ�� ������.
	//������ �� ���ڴ� ����ؼ� ������ ������, ����ؼ� �������� �ʴ´ٸ� �� �� ���� �׸� ������ ����. 5�ʵ��� �׸�.
	DrawDebugCapsule(GetWorld(), CapsuleOrigin, CapsuleHalfHeight, AttackRadius, FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(), DrawColor, false, 5.0f);

#endif
}
float AABCharacterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	//�����Լ� ȣ��. EventInstigator�� �������� �������̰�, DamageCauser�� ���ظ� ���� �����ڰ� ����� ���� �Ǵ� ������ ���� ���� �������� ����.
	//�������Լ� � ������ �޾Ҵ��� �ľ� ����.
	//���� ������ ������ ���� �ִ� DamageAmount�� ������ ���� DamageAmount�� ������ �� ����.
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Stat->ApplyDamage(DamageAmount);

	return DamageAmount;//���������� ���� ������ ���� ����
}

void AABCharacterBase::SetDead()//�״� ���� ���� �Լ�
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);//�̵��� ���Ѱ�
	PlayDeadAnimation();//�״� ��� ���
	SetActorEnableCollision(false);//�ݸ��� ��ü ��� ��. ���� NPC�� ĳ������ �̵��� �������� �ʰ� ��. 

	//�׾��� �� hp�ٰ� ������� �ϱ�
	HpBar->SetHiddenInGame(true);
}

void AABCharacterBase::PlayDeadAnimation()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->StopAllMontages(0.0f);//������ ���� ��� �����ϰ� ������ ��� ��Ÿ�� ������Ŵ. 
	AnimInstance->Montage_Play(DeadMontage, 1.0f);//�״� ��Ÿ�� �÷���, ����ӵ� ���
}

void AABCharacterBase::SetupCharacterWidget(UABUserWidget* InUserWidget)
{
	//������ ĳ�����ؼ� ����.
	UABHpBarWidget* HpBarWidget = Cast<UABHpBarWidget>(InUserWidget);

	if (HpBarWidget)//null�� �ƴ϶��
	{
		//���ȿ� �ִ� �� ����.
		HpBarWidget->SetMaxHp(Stat->GetTotalStat().MaxHp);
		//������ ���� hp ���� ��������. 
		HpBarWidget->UpdateHpBar(Stat->GetCurrentHp());
		//����� �� ���� UpdateHpBar�� ȣ��ǵ��� ������ ��������Ʈ�� �ش� �ν��Ͻ��� ��� �Լ��� ���. �� ������Ʈ ���� ������ ����
		Stat->OnHpChanged.AddUObject(HpBarWidget, &UABHpBarWidget::UpdateHpBar);
	}
}

void AABCharacterBase::TakeItem(UABItemData* InItemData)
{
	if (InItemData)//������ �����Ͱ� �ִٸ�
	{
		//3�� �� �ϳ��� Ÿ�԰��� int�� ��ȯ�� �迭�� �־��ָ�, ����ü�� ���� �����ϰ� ��.
		TakeItemActions[(uint8)InItemData->Type].ItemDelegate.ExecuteIfBound(InItemData);
	}
}

void AABCharacterBase::DrinkPotion(UABItemData* InItemData)
{
	UE_LOG(LogABCharacter, Log, TEXT("Drink Potion"));
}

void AABCharacterBase::EquipWeapon(UABItemData* InItemData)
{
	//���� ������ ������ Ÿ������ ����ȯ
	UABWeaponItemData* WeaponItemData = Cast<UABWeaponItemData>(InItemData);
	if (WeaponItemData)//���� ������ �����Ͱ� ������
	{
		if (WeaponItemData->WeaponMesh.IsPending())//�ε��� �� �Ǿ��ִ� ��Ȳ�̸�
		{
			WeaponItemData->WeaponMesh.LoadSynchronous();//���������� �ε���Ŵ.
		}
		
		UE_LOG(LogABCharacter, Log, TEXT("Weapon Setting"));
		//���� �޽� ����.
		Weapon->SetSkeletalMesh(WeaponItemData->WeaponMesh.Get());//Get�Լ��� ������
		Stat->SetModifierStat(WeaponItemData->ModifierStat);//���� ���� �� ���� �߰� �ο�
	}
}

void AABCharacterBase::ReadScroll(UABItemData* InItemData)
{
	UE_LOG(LogABCharacter, Log, TEXT("Read Scroll"));
}

int32 AABCharacterBase::GetLevel()
{
	return Stat->GetCurrentLevel();
}

void AABCharacterBase::SetLevel(int32 InNewLevel)
{
	Stat->SetLevelStat(InNewLevel);
}