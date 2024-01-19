// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ABCharacterBase.h"
#include "Engine/StreamableManager.h"
#include "ABCharacterNonPlayer.generated.h"

/**
 *
 */
UCLASS(config = ArenaBattle)//ini 파일 불러오겠다는 것을 의미
class ARENABATTLE_API AABCharacterNonPlayer : public AABCharacterBase
{
	GENERATED_BODY()

public:
	AABCharacterNonPlayer();//생성자

protected:
	virtual void PostInitializeComponents() override;

protected:
	void SetDead() override;
	void NPCMeshLoadCompleted();//로딩 완료되면 신호 받음

	UPROPERTY(config)//해당 config 파일로부터 데이터를 불러오겠다는 의미
	TArray<FSoftObjectPath> NPCMeshes;//플젝 로딩되면 자동으로 NPCMeshes 값이 채워짐.

	TSharedPtr<FStreamableHandle> NPCMeshHandle;//비동기 방식으로 로딩하기 위해 구조체 선언
};
