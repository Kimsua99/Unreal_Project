// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ABComboActionData.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API UABComboActionData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UABComboActionData();

	//액션 데이터에 설정할 속성 값 지정

	//몽타주 섹션 이름
	UPROPERTY(EditAnywhere, Category = Name)
	FString MontageSectionNamePrefix;

	//총 몇 개의 콤보 액션이 있는지
	UPROPERTY(EditAnywhere, Category = Name)
	uint8 MaxComboCount;

	//프레임의 기준 재생 속도를 지정해 정확한 타이밍에 체크 일어나게 설정
	UPROPERTY(EditAnywhere, Category = Name)
	float FrameRate;

	//입력이 사전에 입력되었는지를 감지하는 프레임들 지정
	UPROPERTY(EditAnywhere, Category = Name)
	TArray<float> EffectiveFrameCount;
};
