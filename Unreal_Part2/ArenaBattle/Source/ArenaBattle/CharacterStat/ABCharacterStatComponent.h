// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ABCharacterStatComponent.generated.h"

//���� ������Ʈ�� ��������Ʈ�� ����� ������ ����� �ٸ� ��ü���� HP�� ����Ǿ��� �� ������ �ൿ ó���ϵ��� �ϴ� ����
//��������Ʈ ����
DECLARE_MULTICAST_DELEGATE(FOnHpZeroDelegate);//MULTICAST -> �ټ��� �����ڸ� ���� �� �ֵ��� ����. �׾��ٴ� ��ȣ�� ����ü ����
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHpChangedDelegate, float /*CurrentHp*/);//����� ���� hp ���� ������ ��ü���� ���� �� �ֵ��� �� ���� ���� ���� ����

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
	
	//�������� �޾��� ���
	float ApplyDamage(float InDamage);
protected:

	//���������� hp ���� ����Ǿ��� �� ������ �Լ�
	void SetHp(float NewHp);

	UPROPERTY(VisibleInstanceOnly, Category = Stat)//VisibleInstanceOnly�� ���� ��ġ�� ĳ���͸��� �ٸ� hp ���� ������ �� �ְ� �ȴ�.
	float MaxHp;//�ִ� hp ��

	//���� ������Ʈ��� ������Ʈ�� ������ �� �Ӽ����� ��ũ�� ����Ǵµ�, 
	//���� hp ���� ��� ������ �� �� ���� ���Ӱ� �����ǹǷ� ��ũ�� ������ �ʿ䰡 ����.
	//���� Transient��� Ű���带 �ٿ� ��ũ�κ��� ������ �� ���ʿ��� ������ ������� �ʵ��� ���� ����.
	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentHp;//���� hp ��
};
