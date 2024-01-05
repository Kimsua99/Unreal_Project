// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ABCharacterBase.h"
#include "InputActionValue.h"
#include "ABCharacterPlayer.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API AABCharacterPlayer : public AABCharacterBase
{
	GENERATED_BODY()
	
public:
	AABCharacterPlayer();

protected://�Է� ���� ���ؽ�Ʈ�� �Ҵ��ϴ� ����
	virtual void BeginPlay() override;

public://�𸮾� ������ InputSystem���� �Է� �׼ǰ� ������ Move, Look �Լ��� ���� ���ν����ִ� ���� �̸� �Ϸ�����.
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

//ī�޶� ���� ����. 
protected:
	//�𸮾� ������Ʈ ����.
	//ī�޶� �������ִ� ������ ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> CameraBoom;

	//���� ī�޶� ������Ʈ. Meta�� �߰� �����ڷ�, private ��ü�� �������Ʈ������ ���� �����ϰ� �ϴ� ������.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> FollowCamera;

//Input ����
protected:
	//�ش� ������ ��� �ٸ� �������� ���� �����ϰ� �����ϱ� ���� �����ڸ� EditAnywhere�� ����
	//���� ���ؽ�Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	//�׼�
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> JumpAction;
	//�׼�
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> MoveAction;
	//�׼�
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> LookAction;

	//�� �׼ǿ� ���� ���ε� �Լ��� ���� ����
	void Move(const FInputActionValue& Value);//����ü�� �����Ƿ� InputActionValue.h ����� �߰��ؾ� ��.
	void Look(const FInputActionValue& Value);
};
