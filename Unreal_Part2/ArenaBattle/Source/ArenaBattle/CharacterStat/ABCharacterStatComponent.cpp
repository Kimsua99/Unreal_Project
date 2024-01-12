// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStat/ABCharacterStatComponent.h"

// Sets default values for this component's properties
UABCharacterStatComponent::UABCharacterStatComponent()
{
	MaxHp = 200.0f;
	CurrentHp = MaxHp;
}


// Called when the game starts
void UABCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	SetHp(MaxHp);
	
}

float UABCharacterStatComponent::ApplyDamage(float InDamage)
{
	//������ hp ���� ������ ����
	const float PrevHp = CurrentHp;
	//���� ������ ���� ������ ���� �����Ƿ� ���� ���� ���� ������ ���� ���� �ش�� �� �ֵ��� ó������.
	const float ActualDamage = FMath::Clamp<float>(InDamage, 0, InDamage);

	SetHp(PrevHp - ActualDamage);

	//���� CurrentHp ���� ����ϴ� ���� ���� ������ ������
	if (CurrentHp <= KINDA_SMALL_NUMBER)
	{
		//���� ���°� �Ǿ��ٰ� �Ǵ�
		OnHpZero.Broadcast();
	}
	return ActualDamage;
}

void UABCharacterStatComponent::SetHp(float NewHp)//���������� hp ���� ����Ǿ��� �� ������ �Լ�
{
	//0���� ���� �ʰ�, MaxHp ���� �Ѿ�� �ʵ��� ����
	CurrentHp = FMath::Clamp<float>(NewHp, 0.0f, MaxHp);

	//hp ���� ������ �Ǿ��ٸ�, �� ��������Ʈ�� ����� �Լ����� hp�� ����Ǿ����� ó���϶�� ��ȣ. ��Ƽ�̹Ƿ� Broadcast
	//hp ����� ������ Ǫ�� �˸��� �ڵ����� ���� ��.
	OnHpChanged.Broadcast(CurrentHp);
}


