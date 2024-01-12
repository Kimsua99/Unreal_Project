// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ABHpBarWidget.h"
#include "Components/ProgressBar.h"

UABHpBarWidget::UABHpBarWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MaxHp = -1.0f;//음수로 표시하지 않으면 설정에 문제가 생기므로 초기화 시에는 올바른 값으로 지정하도록 안내
}

void UABHpBarWidget::NativeConstruct()
{
	Super::NativeConstruct();//이 함수가 호출되면 UI에 관련된 모든 기능들이 초기화 완료된 상태

	HpProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PbHpBar")));//지정한 컨트롤에 대해 프로그레스 바를 이름으로 찾음
	ensure(HpProgressBar);
}

void UABHpBarWidget::UpdateHpBar(float NewCurrentHp)
{
	//확실히 체크하고 넘어감. 0보다 큰지
	ensure(MaxHp > 0.0f);

	if(HpProgressBar)//포인터로 선언한 객체가 있으면 
	{
		HpProgressBar->SetPercent(NewCurrentHp / MaxHp);
	}
}