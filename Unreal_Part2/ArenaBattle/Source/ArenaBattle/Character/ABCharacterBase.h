// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/ABAnimationAttackInterface.h"
#include "Interface/ABCharacterWidgetInterface.h"
#include "Interface/ABCharacterItemInterface.h"
#include "ABCharacterBase.generated.h"

//언리얼이 제공하는 로그 매크로
DECLARE_LOG_CATEGORY_EXTERN(LogABCharacter, Log, All);

UENUM()
enum class ECharacterControlType : uint8//숄더뷰와 쿼터뷰를 관리할 수 있는 열거형 선언
{
	Shoulder,
	Quater
};

//아이템을 처리할 수 있는 델리게이트 선언
//다수를 배열로 관리하는데, 자체를 인자로 쓸 수 없으므로 관리하기 위한 쉬운 방법은 이를 감싸는 구조체를 하나 만드는 것이다.
DECLARE_DELEGATE_OneParam(FOnTakeItemDelegate, class UABItemData* /*InItemData*/);

//구조체 생성
USTRUCT(BlueprintType)
struct FTakeItemDelegateWrapper
{
	GENERATED_BODY()
	FTakeItemDelegateWrapper() {}//기본 생성자 구축
	FTakeItemDelegateWrapper(const FOnTakeItemDelegate& InItemDelegate) : ItemDelegate(InItemDelegate) {}//인자를 받는 생성자 구축
	FOnTakeItemDelegate ItemDelegate;//인자로 선언
};

UCLASS()
class ARENABATTLE_API AABCharacterBase : public ACharacter, public IABAnimationAttackInterface, public IABCharacterWidgetInterface, public IABCharacterItemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AABCharacterBase();

	//셋업을 종료하는 시점, BeginPlay가 실행되기전에 스탯의 델리게이트를 등록해서 죽는 모션 수행하도록 처리
	virtual void PostInitializeComponents() override;

protected:
	virtual void SetCharacterControlData(const class UABCharacterControlData* CharacterControlData);

	//enum을 바탕으로 두 가지 에셋 오브젝트를 바로 얻어올 수 있도록 map으로 데이터 선언
	UPROPERTY(EditAnywhere, Category = CharacterControl, Meta = (AllowPrivateAccess = "true"))
	TMap<ECharacterControlType, class UABCharacterControlData*> CharacterControlManager;

	//몽타주에 관련된 콤보 액션 섹션
protected:
	//몽타주 입력 받도록 설정
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> ComboActionMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UABComboActionData> ComboActionData;

	//입력을 통해 커맨드 지시가 나오면, 이를 통해 몽타주 재생.
	void ProcessComboCommand();
	
	void ComboActionBegin();//몽타주 시작 시 호출
	void ComboActionEnd(class UAnimMontage* TargetMontage, bool IsProperlyEnded);//몽타주 종료 시 호출. 몽타주에 설정된 델리게이트를 통해 바로 호출될 수 있도록 파라미터 맞춤.

	void SetComboCheckTimer();//타이머를 발동시킬 함수
	void ComboCheck();//타이머가 발동되면 입력이 들어왔는지 안 들어왔는지 체크하는 함수

	int32 CurrentCombo = 0;//현재 콤보가 어디까지 진행되는지를 저장하기 위한 변수.0 -> 시작 x, 1~4까지 콤보
	FTimerHandle ComboTimerHandle;//원하는 시간에 특정 함수 호출하도록 설정 가능.
	bool HasNextComboCommand = false;//발동한 타이머 이전에 입력 커맨드 들어왔는지 확인하는 변수. 

	//Attack Hit Section
protected:
	virtual void AttackHitCheck() override;
	
	//액터에 구현되어있으므로 오버라이드만 해줌.
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	// Dead Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> DeadMontage;//죽는 몽타주 선언

	virtual void SetDead();//죽는 상태 구현 함수
	void PlayDeadAnimation();//죽는 몽타주 재생 함수

	//npc 죽음을 위한 변수, 죽고 나서 충분한 시간 지나고 무언가 일어나도록 하기 위함.
	float DeadEventDelayTime = 5.0f;

	// Stat Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UABCharacterStatComponent> Stat;

	// UI Widget Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UABWidgetComponent> HpBar;

	virtual void SetupCharacterWidget(class UABUserWidget* InUserWidget) override;
	
	// Item Section
protected:
	//무기를 담을 스켈레탈 메쉬 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Equipment, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USkeletalMeshComponent> Weapon;

	UPROPERTY()
	TArray<FTakeItemDelegateWrapper> TakeItemActions;//구조체를 관리할 수 있는 배열 선언

	virtual void TakeItem(class UABItemData* InItemData) override;//인터페이스에서 구현한 함수 선언

	//3가지 함수 바인딩. 
	virtual void DrinkPotion(class UABItemData* InItemData);
	virtual void EquipWeapon(class UABItemData* InItemData);
	virtual void ReadScroll(class UABItemData* InItemData);
};
