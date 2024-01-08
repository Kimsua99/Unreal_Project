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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UABComboActionData> ComboActionData;

	//입력을 통해 커맨드 지시가 나오면, 이를 통해 몽타주 재생.
	void ProcessComboCommand();
	
	void ComboActionBegin();//몽타주 시작 시 호출
	void ComboActionEnd(class UAnimMontage* TargetMontage, bool IsProperlyEnded);//몽타주 종료 시 호출. 몽타주에 설정된 델리게이트를 통해 바로 호출될 수 있도록 파라미터 맞춤.

	void SetComboCheckTimer();//타이머를 발동시킬 함수
	void ComboCheck();//타이머가 발동되면 입력이 들어왔는지 안 들어왔는지 체크하는 함수

	int32 CurrentCombo = 0;//현재 콤보가 어디까지 진행되는지를 저장하기 위한 변수.0 -> 시작 x, 1~4까지 콤보
	FTimerHandle ComboTimerHandle;//원하는 시간에 특정 함수 호출하도록 설정 가능.
	bool HasNextComboCommand = false;//발동한 타이머 이전에 입력 커맨드 들어왔는지 확인하는 변수. 
};
