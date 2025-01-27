// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStat/ABCharacterStatComponent.h"
#include "GameData/ABGameSingleton.h"

// Sets default values for this component's properties
UABCharacterStatComponent::UABCharacterStatComponent()
{
	CurrentLevel = 1;
	AttackRadius = 50.0f;

	//해당 속성 값을 true로 설정해야지만 InitializeComponent 함수를 호출할 수 있다.
	bWantsInitializeComponent = true;
}

//기존의 BeginPlay 함수를 지우고 이 함수에서 컴포넌트가 가장 먼저 초기화되어 데이터가 확정된다.
void UABCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	SetLevelStat(CurrentLevel);//현재 레벨에 따라 스탯 설정
	SetHp(BaseStat.MaxHp);//HP를 꽉 채워줌
}

void UABCharacterStatComponent::SetLevelStat(int32 InNewLevel)
{
	//현재 값이 1보다 커야 하고, 게임 싱글톤에 선언된 맥스 레벨을 벗어나면 안됨
	CurrentLevel = FMath::Clamp(InNewLevel, 1, UABGameSingleton::Get().CharacterMaxLevel);
	//싱글톤으로부터 레벨 정보를 넘겨줌.
	SetBaseStat(UABGameSingleton::Get().GetCharacterStat(CurrentLevel));
	check(BaseStat.MaxHp > 0.0f);
}

float UABCharacterStatComponent::ApplyDamage(float InDamage)
{
	//이전의 hp 값을 변수에 저장
	const float PrevHp = CurrentHp;
	//들어온 데미지 값이 음수일 수도 있으므로 들어온 값이 예측 가능한 범위 내에 해당될 수 있도록 처리해줌.
	const float ActualDamage = FMath::Clamp<float>(InDamage, 0, InDamage);

	SetHp(PrevHp - ActualDamage);

	//만약 CurrentHp 값이 허용하는 가장 작은 값보다 작으면
	if (CurrentHp <= KINDA_SMALL_NUMBER)
	{
		//죽은 상태가 되었다고 판단
		OnHpZero.Broadcast();
	}
	return ActualDamage;
}

void UABCharacterStatComponent::SetHp(float NewHp)//내부적으로 hp 값이 변경되었을 때 실행할 함수
{
	//0보다 작지 않고, BaseStat.MaxHp 값을 넘어서지 않도록 조절
	CurrentHp = FMath::Clamp<float>(NewHp, 0.0f, BaseStat.MaxHp);

	//hp 값이 변동이 되었다면, 이 델리게이트에 등록한 함수에게 hp가 변경되었으니 처리하라고 신호. 멀티이므로 Broadcast
	//hp 변경될 때마다 푸시 알림이 자동으로 오게 됨.
	OnHpChanged.Broadcast(CurrentHp);
}


