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
	FPrimaryAssetId GetPrimaryAssetId() const override
	{
		//태그 이름 ABItemData. 이름을 GetFName으로 에셋 이름으로 지정. 
		//두 가지 정보를 사용해 식별자 아이디 값을 만들어 냄.
		return FPrimaryAssetId("ABItemData", GetFName());
	}

public:
	//아이템 타입을 지정, 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Type)
	EItemType Type;
};
