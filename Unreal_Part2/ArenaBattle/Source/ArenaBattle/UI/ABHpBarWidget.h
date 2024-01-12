// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ABHpBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API UABHpBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UABHpBarWidget(const FObjectInitializer& ObjectInitializer);//������ ��� FObjectInitializer ��� ������ ���

protected:
	//������ �ʱ�ȭ�� �� HpProgressBar�� �����ͼ� �����͸� �������� ��� �߰�.
	virtual void NativeConstruct() override;//�θ� �Լ� �������̵�

public:
	FORCEINLINE void SetMaxHp(float NewMaxHp) { MaxHp = NewMaxHp; }
	//���� hp ���¿� ���� hp ���� ���� ����� ������Ʈ �ϴ� �Լ�
	void UpdateHpBar(float NewCurrentHp);

protected:
	UPROPERTY()
	TObjectPtr<class UProgressBar> HpProgressBar;//hp�ٸ� ǥ���ϴµ� ����� ���α׷��� �� ��Ʈ�ѿ� ���� ������Ʈ ������ ����

	UPROPERTY()
	float MaxHp;
};
