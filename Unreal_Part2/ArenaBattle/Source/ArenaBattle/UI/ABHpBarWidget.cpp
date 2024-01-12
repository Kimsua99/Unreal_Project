// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ABHpBarWidget.h"
#include "Components/ProgressBar.h"
#include "Interface/ABCharacterWidgetInterface.h"

UABHpBarWidget::UABHpBarWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MaxHp = -1.0f;//������ ǥ������ ������ ������ ������ ����Ƿ� �ʱ�ȭ �ÿ��� �ùٸ� ������ �����ϵ��� �ȳ�
}

void UABHpBarWidget::NativeConstruct()
{
	Super::NativeConstruct();//�� �Լ��� ȣ��Ǹ� UI�� ���õ� ��� ��ɵ��� �ʱ�ȭ �Ϸ�� ����

	HpProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PbHpBar")));//������ ��Ʈ�ѿ� ���� ���α׷��� �ٸ� �̸����� ã��
	ensure(HpProgressBar);

	//���� �������ٰ� ���� ���� ������ UpdateHpBar��� �Լ� ������ �����Ͽ� ��������Ʈ�� ��Ͻ�Ű�� ������ ������ ������Ʈ �� ������ �Լ��� ȣ��Ǹ鼭 HpBar�� ���ϰ� �ȴ�.
	//OwningActor�� ����ȯ �Ǵ����� ����
	IABCharacterWidgetInterface* CharacterWidget = Cast<IABCharacterWidgetInterface>(OwningActor);
	
	if (CharacterWidget)//����ȯ �� �Ǿ��ٸ�
	{
		//���ε�
		CharacterWidget->SetupCharacterWidget(this);
	}
}

void UABHpBarWidget::UpdateHpBar(float NewCurrentHp)
{
	//Ȯ���� üũ�ϰ� �Ѿ. 0���� ū��
	ensure(MaxHp > 0.0f);

	if(HpProgressBar)//�����ͷ� ������ ��ü�� ������ 
	{
		HpProgressBar->SetPercent(NewCurrentHp / MaxHp);
	}
}