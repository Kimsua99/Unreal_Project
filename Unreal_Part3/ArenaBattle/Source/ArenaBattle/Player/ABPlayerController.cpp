// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ABPlayerController.h"
#include "UI/ABHUDWidget.h"
#include "Kismet/GameplayStatics.h"
#include "ABSaveGame.h"
#include "ArenaBattle.h"

DEFINE_LOG_CATEGORY(LogABPlayerController);

AABPlayerController::AABPlayerController()
{
	static ConstructorHelpers::FClassFinder<UABHUDWidget> ABHUDWidgetRef(TEXT("/Game/ArenaBattle/UI/WBP_ABHUD.WBP_ABHUD_C"));
	if (ABHUDWidgetRef.Class)
	{
		ABHUDWidgetClass = ABHUDWidgetRef.Class;
	}
}

void AABPlayerController::OnPossess(APawn* InPawn)
{
	AB_LOG(LogABNetwork, Log, TEXT("%s %s"), TEXT("Begin"), *GetName());

	Super::OnPossess(InPawn);//���� ����
	//������ ���� PossessedBy �Լ��� ȣ��Ǿ� ��� ���ʰ� ����Ǵ��� Ȯ�� ����

	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("End"));
}

//void AABPlayerController::SetPawn(APawn* InPawn)
//{
//	AB_LOG(LogABNetwork, Log, TEXT("%s %s"), TEXT("Begin"), *GetName());
//	if (InPawn)
//	{
//		AActor* PawnOwner = InPawn->GetOwner();
//		if (PawnOwner)
//		{
//			AB_LOG(LogABNetwork, Log, TEXT("%s Pawn's Owner : %s"), *GetName(), *PawnOwner->GetName());
//		}
//		else
//		{
//			AB_LOG(LogABNetwork, Log, TEXT("%s %s"), *GetName(), TEXT("Pawn has no Owner"));
//		}
//	}
//	else
//	{
//		AB_LOG(LogABNetwork, Log, TEXT("%s %s"), *GetName(), TEXT("No Pawn"));
//	}
//
//	Super::SetPawn(InPawn);
//
//	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("End"));
//}

void AABPlayerController::BeginPlay()
{
	AB_LOG(LogABNetwork, Log, TEXT("%s %s"), TEXT("Begin"), *GetName());

	Super::BeginPlay();

	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("End"));

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);
}

//void AABPlayerController::PostInitializeComponents()//��Ʈ��ũ�� �����ϰ� ���͸� �ʱ�ȭ�� �� ���� �Լ� 
//{
//	AB_LOG(LogABNetwork, Log, TEXT("%s %s"), TEXT("Begin"), *GetName());
//
//	Super::PostInitializeComponents();
//
//	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("End"));
//}

void AABPlayerController::PostNetInit()//���� Ŭ���̾�Ʈ���� ��Ʈ��ũ�� �ʱ�ȭ�� �ʿ��� ������ ���޹��� ���� ��� ������ �Ǹ� ȣ���. ������ �ƴ� Ŭ�󿡼��� ȣ���.
{
	AB_LOG(LogABNetwork, Log, TEXT("%s %s"), TEXT("Begin"), *GetName());

	Super::PostNetInit();

	UNetDriver* NetDriver = GetNetDriver();
	if (NetDriver)//Ŭ���� ��� ������ �� ����̹� ����.
	{
		AB_LOG(LogABNetwork, Log, TEXT("Server Connection : %s"), *NetDriver->ServerConnection->GetName());
	}
	else
	{
		AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("No NetDriver"));
	}

	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("End"));
}
