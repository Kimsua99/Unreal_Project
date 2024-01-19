// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/ABItemData.h"
#include "GameData/ABCharacterStat.h"
#include "ABWeaponItemData.generated.h"

/**
 *
 */
UCLASS()
class ARENABATTLE_API UABWeaponItemData : public UABItemData
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
	//아이템 데이터가 가진 정보들을 가지고 있음.
	UPROPERTY(EditAnywhere, Category = Weapon)
	TSoftObjectPtr<USkeletalMesh> WeaponMesh;//무기에 대한 스켈레탈 메쉬 지정

	UPROPERTY(EditAnywhere, Category = Stat)
	FABCharacterStat ModifierStat;
};
