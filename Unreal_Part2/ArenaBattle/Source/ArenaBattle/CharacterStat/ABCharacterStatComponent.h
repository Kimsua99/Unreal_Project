// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameData/ABCharacterStat.h"
#include "ABCharacterStatComponent.generated.h"

//스탯 컴포넌트가 델리게이트를 만들고 구독을 등록한 다른 객체한테 HP가 변경되었을 때 적합한 행동 처리하도록 하는 구조
//델리게이트 선언
DECLARE_MULTICAST_DELEGATE(FOnHpZeroDelegate);//MULTICAST -> 다수의 구독자를 받을 수 있도록 설정. 죽었다는 신호의 구조체 넣음
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHpChangedDelegate, float /*CurrentHp*/);//변경된 현재 hp 값을 구독한 객체에게 보낼 수 있도록 한 가지 인자 값을 설정
//스탯들이 수정될 때 마다 알림을 보내는 델리게이트 선언
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStatChangedDelegate, const FABCharacterStat& /*BaseStat*/, const FABCharacterStat& /*ModifierStat*/);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARENABATTLE_API UABCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UABCharacterStatComponent();

protected:
	virtual void InitializeComponent() override;

public:
	FOnHpZeroDelegate OnHpZero;
	FOnHpChangedDelegate OnHpChanged;
	FOnStatChangedDelegate OnStatChanged;

	//레벨을 설정해주는 함수
	void SetLevelStat(int32 InNewLevel);
	//레벨 정보에 대한 게터 함수
	FORCEINLINE float GetCurrentLevel() const { return CurrentLevel; }
	//무기 획득 시, 모디파이어 스탯 변경할 수 있도록 세터 함수 추가
	FORCEINLINE void SetBaseStat(const FABCharacterStat& InBaseStat) { BaseStat = InBaseStat; OnStatChanged.Broadcast(GetBaseStat(), GetModifierStat()); }
	FORCEINLINE void SetModifierStat(const FABCharacterStat& InModifierStat) { ModifierStat = InModifierStat; OnStatChanged.Broadcast(GetBaseStat(), GetModifierStat()); }

	FORCEINLINE const FABCharacterStat& GetBaseStat() const { return BaseStat; }
	FORCEINLINE const FABCharacterStat& GetModifierStat() const { return ModifierStat; }

	//캐릭터 전체 스탯 값 받아올 수 있도록 토탈 스탯 추가. 덧셈 오퍼레이터로 반환
	FORCEINLINE FABCharacterStat GetTotalStat() const { return BaseStat + ModifierStat; }

	FORCEINLINE float GetCurrentHp() const { return CurrentHp; }

	FORCEINLINE float GetAttackRadius() const { return AttackRadius; }
	
	//데미지를 받았을 경우
	float ApplyDamage(float InDamage);
protected:

	//내부적으로 hp 값이 변경되었을 때 실행할 함수
	void SetHp(float NewHp);


	//스탯 컴포넌트라는 오브젝트를 저장할 떄 속성들이 디스크에 저장되는데, 
	//현재 hp 값의 경우 게임을 할 때 마다 새롭게 지정되므로 디스크에 저장할 필요가 없다.
	//따라서 Transient라는 키워드를 붙여 디스크로부터 저장할 때 불필요한 공간이 낭비되지 않도록 지정 가능.
	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentHp;//현재 hp 값

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentLevel;//캐릭터 스탯은 현재 레벨 정보를 기반으로 해서 게임 싱글톤으로부터 스탯 정보를 제공받음. 이를 저장하기 위한 변수

	UPROPERTY(VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	float AttackRadius;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	FABCharacterStat BaseStat;//기본 스탯

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	FABCharacterStat ModifierStat;//모디파이어 스탯
};
