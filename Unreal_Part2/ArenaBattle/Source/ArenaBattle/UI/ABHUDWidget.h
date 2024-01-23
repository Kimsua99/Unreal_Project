// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameData/ABCharacterStat.h"
#include "ABHUDWidget.generated.h"

/**
 *
 */
UCLASS()
class ARENABATTLE_API UABHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	//생성자 함수 지정. 위젯의 경우 인자 하나 들어감.
	UABHUDWidget(const FObjectInitializer& ObjectInitializer);

public:
	void UpdateStat(const FABCharacterStat& BaseStat, const FABCharacterStat& ModifierStat);
	void UpdateHpBar(float NewCurrentHp);

protected:
	//AddToViewPort 함수가 호출되면 해당 함수가 호출된다.
	virtual void NativeConstruct() override;

protected:
	//컨트롤 위젯을 담당하고 있는 두 개의 클래스 멤버변수 선언
	UPROPERTY()
	TObjectPtr<class UABHpBarWidget> HpBar;

	UPROPERTY()
	TObjectPtr<class UABCharacterStatWidget> CharacterStat;
};
