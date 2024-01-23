// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameData/ABCharacterStat.h"
#include "ABCharacterStatComponent.generated.h"

//���� ������Ʈ�� ��������Ʈ�� ����� ������ ����� �ٸ� ��ü���� HP�� ����Ǿ��� �� ������ �ൿ ó���ϵ��� �ϴ� ����
//��������Ʈ ����
DECLARE_MULTICAST_DELEGATE(FOnHpZeroDelegate);//MULTICAST -> �ټ��� �����ڸ� ���� �� �ֵ��� ����. �׾��ٴ� ��ȣ�� ����ü ����
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHpChangedDelegate, float /*CurrentHp*/);//����� ���� hp ���� ������ ��ü���� ���� �� �ֵ��� �� ���� ���� ���� ����
//���ȵ��� ������ �� ���� �˸��� ������ ��������Ʈ ����
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

	//������ �������ִ� �Լ�
	void SetLevelStat(int32 InNewLevel);
	//���� ������ ���� ���� �Լ�
	FORCEINLINE float GetCurrentLevel() const { return CurrentLevel; }
	//���� ȹ�� ��, ������̾� ���� ������ �� �ֵ��� ���� �Լ� �߰�
	FORCEINLINE void SetBaseStat(const FABCharacterStat& InBaseStat) { BaseStat = InBaseStat; OnStatChanged.Broadcast(GetBaseStat(), GetModifierStat()); }
	FORCEINLINE void SetModifierStat(const FABCharacterStat& InModifierStat) { ModifierStat = InModifierStat; OnStatChanged.Broadcast(GetBaseStat(), GetModifierStat()); }

	FORCEINLINE const FABCharacterStat& GetBaseStat() const { return BaseStat; }
	FORCEINLINE const FABCharacterStat& GetModifierStat() const { return ModifierStat; }

	//ĳ���� ��ü ���� �� �޾ƿ� �� �ֵ��� ��Ż ���� �߰�. ���� ���۷����ͷ� ��ȯ
	FORCEINLINE FABCharacterStat GetTotalStat() const { return BaseStat + ModifierStat; }

	FORCEINLINE float GetCurrentHp() const { return CurrentHp; }

	FORCEINLINE float GetAttackRadius() const { return AttackRadius; }
	
	//�������� �޾��� ���
	float ApplyDamage(float InDamage);
protected:

	//���������� hp ���� ����Ǿ��� �� ������ �Լ�
	void SetHp(float NewHp);


	//���� ������Ʈ��� ������Ʈ�� ������ �� �Ӽ����� ��ũ�� ����Ǵµ�, 
	//���� hp ���� ��� ������ �� �� ���� ���Ӱ� �����ǹǷ� ��ũ�� ������ �ʿ䰡 ����.
	//���� Transient��� Ű���带 �ٿ� ��ũ�κ��� ������ �� ���ʿ��� ������ ������� �ʵ��� ���� ����.
	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentHp;//���� hp ��

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentLevel;//ĳ���� ������ ���� ���� ������ ������� �ؼ� ���� �̱������κ��� ���� ������ ��������. �̸� �����ϱ� ���� ����

	UPROPERTY(VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	float AttackRadius;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	FABCharacterStat BaseStat;//�⺻ ����

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	FABCharacterStat ModifierStat;//������̾� ����
};
