// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ABWidgetComponent.h"
#include "ABUserWidget.h"

void UABWidgetComponent::InitWidget()
{
	//호출되었을 때는 위젯에 대한 인스턴스가 생성이 된 직후이며, 위젯에 대한 UI 요소들이 다 준비 완료되면 NativeConstruct 함수가 호출된다.
	Super::InitWidget();

	//현재 컴포넌트가 소유하고 있는 위젯을 가져오는데, InitWidget 함수가 호출되면 CreateWidget이 호출되며 인스턴스가 만들어짐.
	UABUserWidget* ABUserWidget = Cast<UABUserWidget>(GetWidget());

	if (ABUserWidget)//형변환 성공하면
	{
		//컴포넌트이므로 GetOwner로 자신을 소유하고 있는 액터 정보를 얻어옴.
		ABUserWidget->SetOwningActor(GetOwner());
	}
}