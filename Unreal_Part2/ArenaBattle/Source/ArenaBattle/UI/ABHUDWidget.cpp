// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ABHUDWidget.h"
#include "Interface/ABCharacterHUDInterface.h"
#include "ABHpBarWidget.h"
#include "ABCharacterStatWidget.h"

UABHUDWidget::UABHUDWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UABHUDWidget::UpdateStat(const FABCharacterStat& BaseStat, const FABCharacterStat& ModifierStat)
{
	//������ ����Ǵ� ��쿡�� MaxHP ���� �ٲ�Ƿ� ���̽��� ������̾� ������ ���� ���� �������ش�.
	FABCharacterStat TotalStat = BaseStat + ModifierStat;
	HpBar->SetMaxHp(TotalStat.MaxHp);

	//ĳ���� ������ �� ������ ������ ������Ʈ �� �� �ֵ��� �Լ��� �߰��� �־�� �Ѵ�.
	CharacterStat->UpdateStat(BaseStat, ModifierStat);
}

void UABHUDWidget::UpdateHpBar(float NewCurrentHp)
{
	HpBar->UpdateHpBar(NewCurrentHp);
}

void UABHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//GetWidgetFromName�� ���� ������ ��� ������ �Ҵ�
	HpBar = Cast<UABHpBarWidget>(GetWidgetFromName(TEXT("WidgetHpBar")));
	ensure(HpBar);

	CharacterStat = Cast<UABCharacterStatWidget>(GetWidgetFromName(TEXT("WidgetCharacterStat")));
	ensure(CharacterStat);

	//�������̽��� ���� �� ������ ����ϰ� �ִ� ĳ���Ϳ��� ����� ����.
	//���� �����µ�, HUD�� ��� GetOwningPlayerPawn �Լ��� HUD�� �����ϰ� �ִ� ��Ʈ�ѷ��� �����ϰ� �ִ� ���� ������ �� �ִ�.
	IABCharacterHUDInterface* HUDPawn = Cast<IABCharacterHUDInterface>(GetOwningPlayerPawn());
	if (HUDPawn)//ĳ���� �Ϸ� ��
	{
		//�����κ��� ���� �¾��϶�� ���
		HUDPawn->SetupHUDWidget(this);
	}
	
}