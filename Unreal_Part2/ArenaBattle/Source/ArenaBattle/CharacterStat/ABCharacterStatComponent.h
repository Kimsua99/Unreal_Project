// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ABCharacterStatComponent.generated.h"

//스탯 컴포넌트가 델리게이트를 만들고 구독을 등록한 다른 객체한테 HP가 변경되었을 때 적합한 행동 처리하도록 하는 구조
//델리게이트 선언
DECLARE_MULTICAST_DELEGATE(FOnHpZeroDelegate);//MULTICAST -> 다수의 구독자를 받을 수 있도록 설정. 죽었다는 신호의 구조체 넣음
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHpChangedDelegate, float /*CurrentHp*/);//변경된 현재 hp 값을 구독한 객체에게 보낼 수 있도록 한 가지 인자 값을 설정

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARENABATTLE_API UABCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UABCharacterStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	FOnHpZeroDelegate OnHpZero;
	FOnHpChangedDelegate OnHpChanged;

	FORCEINLINE float GetMaxHP() { return MaxHp; }
	FORCEINLINE float GetCurrentHP() { return CurrentHp; }
	
	//데미지를 받았을 경우
	float ApplyDamage(float InDamage);
protected:

	//내부적으로 hp 값이 변경되었을 때 실행할 함수
	void SetHp(float NewHp);

	UPROPERTY(VisibleInstanceOnly, Category = Stat)//VisibleInstanceOnly를 쓰면 배치된 캐릭터마다 다른 hp 값을 설정할 수 있게 된다.
	float MaxHp;//최대 hp 값

	//스탯 컴포넌트라는 오브젝트를 저장할 떄 속성들이 디스크에 저장되는데, 
	//현재 hp 값의 경우 게임을 할 때 마다 새롭게 지정되므로 디스크에 저장할 필요가 없다.
	//따라서 Transient라는 키워드를 붙여 디스크로부터 저장할 때 불필요한 공간이 낭비되지 않도록 지정 가능.
	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentHp;//현재 hp 값
};
