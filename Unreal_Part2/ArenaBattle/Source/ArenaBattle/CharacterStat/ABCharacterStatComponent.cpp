// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStat/ABCharacterStatComponent.h"
#include "GameData/ABGameSingleton.h"

// Sets default values for this component's properties
UABCharacterStatComponent::UABCharacterStatComponent()
{
	CurrentLevel = 1;
	AttackRadius = 50.0f;
}


// Called when the game starts
void UABCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	SetLevelStat(CurrentLevel);//���� ������ ���� ���� ����
	SetHp(BaseStat.MaxHp);//HP�� �� ä����
}

void UABCharacterStatComponent::SetLevelStat(int32 InNewLevel)
{
	//���� ���� 1���� Ŀ�� �ϰ�, ���� �̱��濡 ����� �ƽ� ������ ����� �ȵ�
	CurrentLevel = FMath::Clamp(InNewLevel, 1, UABGameSingleton::Get().CharacterMaxLevel);
	//�̱������κ��� ���� ������ �Ѱ���.
	BaseStat = UABGameSingleton::Get().GetCharacterStat(CurrentLevel);
	check(BaseStat.MaxHp > 0.0f);
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
	//0���� ���� �ʰ�, BaseStat.MaxHp ���� �Ѿ�� �ʵ��� ����
	CurrentHp = FMath::Clamp<float>(NewHp, 0.0f, BaseStat.MaxHp);

	//hp ���� ������ �Ǿ��ٸ�, �� ��������Ʈ�� ����� �Լ����� hp�� ����Ǿ����� ó���϶�� ��ȣ. ��Ƽ�̹Ƿ� Broadcast
	//hp ����� ������ Ǫ�� �˸��� �ڵ����� ���� ��.
	OnHpChanged.Broadcast(CurrentHp);
}


