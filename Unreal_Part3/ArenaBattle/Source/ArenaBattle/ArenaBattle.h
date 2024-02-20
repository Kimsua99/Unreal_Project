// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

//������ �߿� ENetRole�̶�� ������ ���. ���õ� ���ڿ� ��� ��.���Ϳ� ����� ���� ������ ���������� ��ȯ���ִµ� �̸� �Լ��� ����� ���ڿ��� �ٲ���.
#define LOG_LOCALROLEINFO *(UEnum::GetValueAsString(TEXT("Engine.ENetRole"), GetLocalRole()))
#define LOG_REMOTEROLEINFO *(UEnum::GetValueAsString(TEXT("Engine.ENetRole"), GetRemoteRole()))
//�α׿��� ��Ʈ��ũ ��� ������ ����ϵ��� �ϴ� ��ũ�� ����
//3�� �����ڸ� ���. Ŭ���̾�Ʈ���� �ƴ��� Ȯ���� ���� �ϰ� �´ٸ� �� ��° Ŭ���̾�Ʈ���� ���. �������� StandAlone ������� Ȯ��.�ƴ϶�� ���� ����.
#define LOG_NETMODEINFO ((GetNetMode() == ENetMode::NM_Client) ? *FString::Printf(TEXT("CLIENT%d"), GPlayInEditorID) : ((GetNetMode() == ENetMode::NM_Standalone) ? TEXT("STANDALONE") : TEXT("SERVER"))) 
//�α׸� ���� �������� � �Լ��� �� ��° ������ �˾ƿ� �� �ִ� FUNCTION�̶�� ����� �Է�
#define LOG_CALLINFO ANSI_TO_TCHAR(__FUNCTION__)
//����ڰ� ������ �α�
#define AB_LOG(LogCat, Verbosity, Format, ...) UE_LOG(LogCat, Verbosity, TEXT("[%s][%s/%s] %s %s"), LOG_NETMODEINFO, LOG_LOCALROLEINFO, LOG_REMOTEROLEINFO, LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

DECLARE_LOG_CATEGORY_EXTERN(LogABNetwork, Log, All);
