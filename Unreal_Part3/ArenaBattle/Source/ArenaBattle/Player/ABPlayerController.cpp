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

	Super::OnPossess(InPawn);//빙의 시작
	//빙의할 폰에 PossessedBy 함수가 호출되어 어떻게 오너가 변경되는지 확인 가능

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

//void AABPlayerController::PostInitializeComponents()//네트워크와 무관하게 액터를 초기화할 때 쓰는 함수 
//{
//	AB_LOG(LogABNetwork, Log, TEXT("%s %s"), TEXT("Begin"), *GetName());
//
//	Super::PostInitializeComponents();
//
//	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("End"));
//}

void AABPlayerController::PostNetInit()//원격 클라이언트에서 네트워크로 초기화에 필요한 정보를 전달받은 것이 모두 마무리 되면 호출됨. 서버가 아닌 클라에서만 호출됨.
{
	AB_LOG(LogABNetwork, Log, TEXT("%s %s"), TEXT("Begin"), *GetName());

	Super::PostNetInit();

	UNetDriver* NetDriver = GetNetDriver();
	if (NetDriver)//클라의 경우 무조건 넷 드라이버 존재.
	{
		AB_LOG(LogABNetwork, Log, TEXT("Server Connection : %s"), *NetDriver->ServerConnection->GetName());
	}
	else
	{
		AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("No NetDriver"));
	}

	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("End"));
}
