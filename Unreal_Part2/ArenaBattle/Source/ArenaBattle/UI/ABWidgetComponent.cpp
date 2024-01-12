// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ABWidgetComponent.h"
#include "ABUserWidget.h"

void UABWidgetComponent::InitWidget()
{
	//ȣ��Ǿ��� ���� ������ ���� �ν��Ͻ��� ������ �� �����̸�, ������ ���� UI ��ҵ��� �� �غ� �Ϸ�Ǹ� NativeConstruct �Լ��� ȣ��ȴ�.
	Super::InitWidget();

	//���� ������Ʈ�� �����ϰ� �ִ� ������ �������µ�, InitWidget �Լ��� ȣ��Ǹ� CreateWidget�� ȣ��Ǹ� �ν��Ͻ��� �������.
	UABUserWidget* ABUserWidget = Cast<UABUserWidget>(GetWidget());

	if (ABUserWidget)//����ȯ �����ϸ�
	{
		//������Ʈ�̹Ƿ� GetOwner�� �ڽ��� �����ϰ� �ִ� ���� ������ ����.
		ABUserWidget->SetOwningActor(GetOwner());
	}
}