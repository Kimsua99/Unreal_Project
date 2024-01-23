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
	//������ �Լ� ����. ������ ��� ���� �ϳ� ��.
	UABHUDWidget(const FObjectInitializer& ObjectInitializer);

public:
	void UpdateStat(const FABCharacterStat& BaseStat, const FABCharacterStat& ModifierStat);
	void UpdateHpBar(float NewCurrentHp);

protected:
	//AddToViewPort �Լ��� ȣ��Ǹ� �ش� �Լ��� ȣ��ȴ�.
	virtual void NativeConstruct() override;

protected:
	//��Ʈ�� ������ ����ϰ� �ִ� �� ���� Ŭ���� ������� ����
	UPROPERTY()
	TObjectPtr<class UABHpBarWidget> HpBar;

	UPROPERTY()
	TObjectPtr<class UABCharacterStatWidget> CharacterStat;
};
