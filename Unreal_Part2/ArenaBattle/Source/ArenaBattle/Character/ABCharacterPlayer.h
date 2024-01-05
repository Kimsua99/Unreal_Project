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

protected://입력 매핑 컨텍스트를 할당하는 역할
	virtual void BeginPlay() override;

public://언리얼 엔진의 InputSystem에서 입력 액션과 선언한 Move, Look 함수를 서로 매핑시켜주는 것을 미리 완료해줌.
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

//카메라 관련 세팅. 
protected:
	//언리얼 오브젝트 선언.
	//카메라를 지탱해주는 지지대 역할
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> CameraBoom;

	//실제 카메라 컴포넌트. Meta는 추가 지정자로, private 객체를 블루프린트에서도 접근 가능하게 하는 지시자.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> FollowCamera;

//Input 섹션
protected:
	//해당 에셋의 경우 다른 에셋으로 변경 가능하게 설계하기 위해 지정자를 EditAnywhere로 선언
	//매핑 컨텍스트
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	//액션
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> JumpAction;
	//액션
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> MoveAction;
	//액션
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> LookAction;

	//각 액션에 대해 매핑된 함수들 직접 구현
	void Move(const FInputActionValue& Value);//구조체를 받으므로 InputActionValue.h 헤더를 추가해야 함.
	void Look(const FInputActionValue& Value);
};
