// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ABPlayerController.h"

void AABPlayerController::BeginPlay()
{
	Super::BeginPlay();//상속

	FInputModeGameOnly GameOnlyInputMode; //구조체 선언
	SetInputMode(GameOnlyInputMode);//구조체 넘겨줌으로서 시작하자마자 포커스가 뷰포트 안으로 들어가게 됨.
}
