// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Card.generated.h"

UENUM()
enum class ECardType : uint8//카드의 분류를 위해 열거형 클래스 선언. 바이트 형태가 일반적임.
{
	//UMETA는 매크로로 열거형의 데이터마다 DisplayName이라는 메타 정보를 지정해 줌.
	Student = 1 UMETA(DisplayName = "For Student"),
	Teacher UMETA(DisplayName = "For Teacher"),
	Staff UMETA(DisplayName = "For Staff"),
	Invalid
};
/**
 * 
 */
UCLASS()
class UNREALDELEGATE_API UCard : public UObject
{
	GENERATED_BODY()
	
public:
	UCard();//생성자 코드

	ECardType GetCardType() const { return CardType; }//게터
	void SetCardType(ECardType InCardType) { CardType = InCardType; }//세터

private:
	UPROPERTY()
	ECardType CardType;

	UPROPERTY()
	uint32 Id;
};
