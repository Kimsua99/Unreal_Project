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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UABComboActionData> ComboActionData;

	//�Է��� ���� Ŀ�ǵ� ���ð� ������, �̸� ���� ��Ÿ�� ���.
	void ProcessComboCommand();
	
	void ComboActionBegin();//��Ÿ�� ���� �� ȣ��
	void ComboActionEnd(class UAnimMontage* TargetMontage, bool IsProperlyEnded);//��Ÿ�� ���� �� ȣ��. ��Ÿ�ֿ� ������ ��������Ʈ�� ���� �ٷ� ȣ��� �� �ֵ��� �Ķ���� ����.

	void SetComboCheckTimer();//Ÿ�̸Ӹ� �ߵ���ų �Լ�
	void ComboCheck();//Ÿ�̸Ӱ� �ߵ��Ǹ� �Է��� ���Դ��� �� ���Դ��� üũ�ϴ� �Լ�

	int32 CurrentCombo = 0;//���� �޺��� ������ ����Ǵ����� �����ϱ� ���� ����.0 -> ���� x, 1~4���� �޺�
	FTimerHandle ComboTimerHandle;//���ϴ� �ð��� Ư�� �Լ� ȣ���ϵ��� ���� ����.
	bool HasNextComboCommand = false;//�ߵ��� Ÿ�̸� ������ �Է� Ŀ�ǵ� ���Դ��� Ȯ���ϴ� ����. 
};
