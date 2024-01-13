// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ABItemData.generated.h"

//아이템 종류를 지정할 수 있도록 열거형 생성
UENUM(BlueprintType)//블루프린트 호환 가능 지정자
enum class EItemType : uint8
{
	//3가지 아이템 세팅
	Weapon = 0,
	Potion,
	Scroll
};

/**
 *
 */
UCLASS()
class ARENABATTLE_API UABItemData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	//아이템 타입을 지정, 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Type)
	EItemType Type;
};
