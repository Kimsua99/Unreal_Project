// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/ABGameMode.h"
#include "ABGameMode.h"
#include "Player/ABPlayerController.h"

AABGameMode::AABGameMode()
{
	//static ConstructorHelpers::FClassFinder<APawn> ThirdPersonClassRef(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter.BP_ThirdPersonCharacter_C"));
	//if (ThirdPersonClassRef.Class)
	//{
	//	DefaultPawnClass = ThirdPersonClassRef.Class;//DefaultPawnClass를 ThirdPersonClassRef에 있는 Class로 지정해줌.
	//}
	//DefaultPawnClass

	//상속 받았으므로 직접 스폰
	//DefaultPawnClass를 만들어준 BP_ABCharacterPlayer로 변경
	static ConstructorHelpers::FClassFinder<APawn> DefaultPawnClassRef(TEXT("/Script/Engine.Blueprint'/Game/ArenaBattle/Blueprint/BP_ABCharacterPlayer.BP_ABCharacterPlayer_C'"));
	if (DefaultPawnClassRef.Class)
	{
		DefaultPawnClass = DefaultPawnClassRef.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Script/ArenaBattle.ABPlayerController"));
	if (PlayerControllerClassRef.Class)
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;//PlayerControllerClass를 PlayerControllerClassRef에 있는 Class로 지정해줌.
	}
	//하단의 코드가 아니라 경로로 클래스 지정해주는 이유는 의존성을 최소화하기 위함이다.
	//PlayerControllerClass = AABPlayerController::StaticClass();//클래스 설정해 줄 수 있음.
}
