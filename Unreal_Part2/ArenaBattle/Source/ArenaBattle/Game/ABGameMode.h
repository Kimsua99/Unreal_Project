// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "ABGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API AABGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AABGameMode();//생성자 추가

	UPROPERTY(EditDefaultsOnly , BlueprintReadWrite, Category = Game)
	int32 ClearScore;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly , Category = Game)
	int32 CurrentScore;

};
