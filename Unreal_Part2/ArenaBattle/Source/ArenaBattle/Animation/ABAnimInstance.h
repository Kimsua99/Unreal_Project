// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ABAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API UABAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UABAnimInstance();

protected:
	virtual void NativeInitializeAnimation() override;//처음 생성될 때 한 번 호출이 됨.

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;//프레임마다 호출됨.

	//Anim 그래프가 참조할 변수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	TObjectPtr<class ACharacter> Owner;

	//CharacterMovementComponent에 대한 객체 포인터를 담는 변수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	TObjectPtr<class UCharacterMovementComponent> Movement;

	//값 변수
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	FVector Velocity;//캐릭터 속도를 보관할 수 있는 변수

	//값 변수
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	float GroundSpeed;//땅에서의 속력을 지정할 수 있는 변수

	//값 변수
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bIsIdle : 1;//현재 idle 상태인지 파악. 
	//bool 타입은 사이즈가 어떻게 될지 명확하지 않음. 따라서 명확하게 하기 위해 int로 선언하되, 앞에 b라는 접두사 붙이고 비트 플래그 달아줌.

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	float MovingThreshould;//움직이고 있는지 쉬고 있는지 점검 위한 변수

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bIsFalling : 1; //떨어지고 있는지 확인

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bIsJumping : 1; //점프하고 있는지 확인

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	float JumpingThreshould;//현재 점프 중인지를 나타내기 위한 변수
};
