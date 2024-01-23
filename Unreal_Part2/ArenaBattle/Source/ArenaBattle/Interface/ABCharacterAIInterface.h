// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ABCharacterAIInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UABCharacterAIInterface : public UInterface
{
	GENERATED_BODY()
};

DECLARE_DELEGATE(FAICharacterAttackFinished);//공격 끝남을 판단하는 델리게이트
/**
 *
 */
class ARENABATTLE_API IABCharacterAIInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//NPC가 의무적으로 가져야 할 기본적인 데이터를 얻어올 수 있게 네 가지의 함수를 의무적으로 구현하도록 인터페이스 선언.
	virtual float GetAIPatrolRadius() = 0;
	virtual float GetAIDetectRange() = 0;
	virtual float GetAIAttackRange() = 0;
	virtual float GetAITurnSpeed() = 0;

	//캐릭터에게 넘기기 위한 함수
	virtual void SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished) = 0;
	//공격의 경우 바로 끝나는 액션이 아니므로 몽타주가 끝나야 공격이 끝난 것임.
	virtual void AttackByAI() = 0;
};