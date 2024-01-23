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
	//스탯이 변경되는 경우에는 MaxHP 값이 바뀌므로 베이스와 모디파이어 스탯을 더한 값을 설정해준다.
	FABCharacterStat TotalStat = BaseStat + ModifierStat;
	HpBar->SetMaxHp(TotalStat.MaxHp);

	//캐릭터 스탯은 두 가지의 스탯을 업데이트 할 수 있도록 함수를 추가해 주어야 한다.
	CharacterStat->UpdateStat(BaseStat, ModifierStat);
}

void UABHUDWidget::UpdateHpBar(float NewCurrentHp)
{
	HpBar->UpdateHpBar(NewCurrentHp);
}

void UABHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//GetWidgetFromName을 통해 선언한 멤버 변수에 할당
	HpBar = Cast<UABHpBarWidget>(GetWidgetFromName(TEXT("WidgetHpBar")));
	ensure(HpBar);

	CharacterStat = Cast<UABCharacterStatWidget>(GetWidgetFromName(TEXT("WidgetCharacterStat")));
	ensure(CharacterStat);

	//인터페이스를 통해 이 위젯을 사용하고 있는 캐릭터에게 명령을 보냄.
	//폰을 얻어오는데, HUD의 경우 GetOwningPlayerPawn 함수로 HUD를 소유하고 있는 컨트롤러가 빙의하고 있는 폰을 가져올 수 있다.
	IABCharacterHUDInterface* HUDPawn = Cast<IABCharacterHUDInterface>(GetOwningPlayerPawn());
	if (HUDPawn)//캐스팅 완료 시
	{
		//폰으로부터 위젯 셋업하라고 명령
		HUDPawn->SetupHUDWidget(this);
	}
	
}