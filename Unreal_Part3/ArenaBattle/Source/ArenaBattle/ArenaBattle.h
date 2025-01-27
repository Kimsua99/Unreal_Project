// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

//열거형 중에 ENetRole이라는 열거형 사용. 관련된 문자열 얻어 옴.액터에 선언된 로컬 역할을 열거형으로 반환해주는데 이를 함수를 사용해 문자열로 바꿔줌.
#define LOG_LOCALROLEINFO *(UEnum::GetValueAsString(TEXT("Engine.ENetRole"), GetLocalRole()))
#define LOG_REMOTEROLEINFO *(UEnum::GetValueAsString(TEXT("Engine.ENetRole"), GetRemoteRole()))
//로그에서 네트워크 모드 정보를 출력하도록 하는 매크로 선언
//3항 연산자를 사용. 클라이언트인지 아닌지 확인을 먼저 하고 맞다면 몇 번째 클라이언트인지 출력. 다음으로 StandAlone 모드인지 확인.아니라면 리슨 서버.
#define LOG_NETMODEINFO ((GetNetMode() == ENetMode::NM_Client) ? *FString::Printf(TEXT("CLIENT%d"), GPlayInEditorID) : ((GetNetMode() == ENetMode::NM_Standalone) ? TEXT("STANDALONE") : TEXT("SERVER"))) 
//로그를 콜한 시점에서 어떤 함수의 몇 번째 줄인지 알아올 수 있는 FUNCTION이라는 예약어 입력
#define LOG_CALLINFO ANSI_TO_TCHAR(__FUNCTION__)
//사용자가 지정한 로그
#define AB_LOG(LogCat, Verbosity, Format, ...) UE_LOG(LogCat, Verbosity, TEXT("[%s][%s/%s] %s %s"), LOG_NETMODEINFO, LOG_LOCALROLEINFO, LOG_REMOTEROLEINFO, LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

DECLARE_LOG_CATEGORY_EXTERN(LogABNetwork, Log, All);
