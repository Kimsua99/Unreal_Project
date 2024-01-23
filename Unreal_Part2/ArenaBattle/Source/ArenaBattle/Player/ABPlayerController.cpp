// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ABPlayerController.h"
#include "UI/ABHUDWidget.h"

AABPlayerController::AABPlayerController()
{
	//위젯에 대한 클래스 정보 불러와서 저장
	static ConstructorHelpers::FClassFinder<UABHUDWidget> ABHUDWidgetRef(TEXT("/Game/ArenaBattle/UI/WBP_ABHUD.WBP_ABHUD_C"));
	if (ABHUDWidgetRef.Class)
	{
		ABHUDWidgetClass = ABHUDWidgetRef.Class;
	}
}


void AABPlayerController::BeginPlay()
{
	Super::BeginPlay();//상속

	FInputModeGameOnly GameOnlyInputMode; //구조체 선언
	SetInputMode(GameOnlyInputMode);//구조체 넘겨줌으로서 시작하자마자 포커스가 뷰포트 안으로 들어가게 됨.

	//생성된 위젯을 저장
	ABHUDWidget = CreateWidget<UABHUDWidget>(this, ABHUDWidgetClass);
	if (ABHUDWidget)//생성이 완료되면
	{
		//위젯을 초기화해서 화면에 띄우도록 명령 내림
		ABHUDWidget->AddToViewport();
	}
}
