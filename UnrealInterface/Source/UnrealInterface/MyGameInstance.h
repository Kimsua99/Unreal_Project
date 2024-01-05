// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREALINTERFACE_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UMyGameInstance();//생성자 로직

	virtual void Init() override;

private:
	UPROPERTY()//이걸 붙여야 언리얼 엔진이 관리하게 됨
	FString SchoolName;
};
