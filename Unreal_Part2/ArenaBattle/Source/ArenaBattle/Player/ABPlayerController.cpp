// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ABPlayerController.h"

void AABPlayerController::BeginPlay()
{
	Super::BeginPlay();//���

	FInputModeGameOnly GameOnlyInputMode; //����ü ����
	SetInputMode(GameOnlyInputMode);//����ü �Ѱ������μ� �������ڸ��� ��Ŀ���� ����Ʈ ������ ���� ��.
}
