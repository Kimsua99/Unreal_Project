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
	virtual void NativeInitializeAnimation() override;//ó�� ������ �� �� �� ȣ���� ��.

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;//�����Ӹ��� ȣ���.

	//Anim �׷����� ������ ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	TObjectPtr<class ACharacter> Owner;

	//CharacterMovementComponent�� ���� ��ü �����͸� ��� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	TObjectPtr<class UCharacterMovementComponent> Movement;

	//�� ����
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	FVector Velocity;//ĳ���� �ӵ��� ������ �� �ִ� ����

	//�� ����
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	float GroundSpeed;//�������� �ӷ��� ������ �� �ִ� ����

	//�� ����
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bIsIdle : 1;//���� idle �������� �ľ�. 
	//bool Ÿ���� ����� ��� ���� ��Ȯ���� ����. ���� ��Ȯ�ϰ� �ϱ� ���� int�� �����ϵ�, �տ� b��� ���λ� ���̰� ��Ʈ �÷��� �޾���.

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	float MovingThreshould;//�����̰� �ִ��� ���� �ִ��� ���� ���� ����

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bIsFalling : 1; //�������� �ִ��� Ȯ��

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bIsJumping : 1; //�����ϰ� �ִ��� Ȯ��

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	float JumpingThreshould;//���� ���� �������� ��Ÿ���� ���� ����
};
