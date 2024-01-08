// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ABCharacterBase.generated.h"

UENUM()
enum class ECharacterControlType : uint8//������ ���ͺ並 ������ �� �ִ� ������ ����
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

	//enum�� �������� �� ���� ���� ������Ʈ�� �ٷ� ���� �� �ֵ��� map���� ������ ����
	UPROPERTY(EditAnywhere, Category = CharacterControl, Meta = (AllowPrivateAccess = "true"))
	TMap<ECharacterControlType, class UABCharacterControlData*> CharacterControlManager;

	//��Ÿ�ֿ� ���õ� �޺� �׼� ����
protected:
	//��Ÿ�� �Է� �޵��� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> ComboActionMontage;

	//�Է��� ���� Ŀ�ǵ� ���ð� ������, �̸� ���� ��Ÿ�� ���.
	void ProcessComboCommand();
		
};