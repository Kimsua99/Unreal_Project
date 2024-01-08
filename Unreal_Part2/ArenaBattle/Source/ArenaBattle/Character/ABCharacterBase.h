// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ABCharacterBase.generated.h"

UENUM()
enum class ECharacterControlType : uint8//숄더뷰와 쿼터뷰를 관리할 수 있는 열거형 선언
{
	Shoulder,
	Quater
};

UCLASS()
class ARENABATTLE_API AABCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AABCharacterBase();

protected:
	virtual void SetCharacterControlData(const class UABCharacterControlData* CharacterControlData);

	//enum을 바탕으로 두 가지 에셋 오브젝트를 바로 얻어올 수 있도록 map으로 데이터 선언
	UPROPERTY(EditAnywhere, Category = CharacterControl, Meta = (AllowPrivateAccess = "true"))
	TMap<ECharacterControlType, class UABCharacterControlData*> CharacterControlManager;

	//몽타주에 관련된 콤보 액션 섹션
protected:
	//몽타주 입력 받도록 설정
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> ComboActionMontage;

	//입력을 통해 커맨드 지시가 나오면, 이를 통해 몽타주 재생.
	void ProcessComboCommand();
		
};
