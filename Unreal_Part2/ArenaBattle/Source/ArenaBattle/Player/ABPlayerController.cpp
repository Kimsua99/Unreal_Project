// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ABPlayerController.h"
#include "UI/ABHUDWidget.h"

AABPlayerController::AABPlayerController()
{
	//������ ���� Ŭ���� ���� �ҷ��ͼ� ����
	static ConstructorHelpers::FClassFinder<UABHUDWidget> ABHUDWidgetRef(TEXT("/Game/ArenaBattle/UI/WBP_ABHUD.WBP_ABHUD_C"));
	if (ABHUDWidgetRef.Class)
	{
		ABHUDWidgetClass = ABHUDWidgetRef.Class;
	}
}


void AABPlayerController::BeginPlay()
{
	Super::BeginPlay();//���

	FInputModeGameOnly GameOnlyInputMode; //����ü ����
	SetInputMode(GameOnlyInputMode);//����ü �Ѱ������μ� �������ڸ��� ��Ŀ���� ����Ʈ ������ ���� ��.

	//������ ������ ����
	ABHUDWidget = CreateWidget<UABHUDWidget>(this, ABHUDWidgetClass);
	if (ABHUDWidget)//������ �Ϸ�Ǹ�
	{
		//������ �ʱ�ȭ�ؼ� ȭ�鿡 ��쵵�� ��� ����
		ABHUDWidget->AddToViewport();
	}
}
