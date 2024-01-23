// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ABAIController.generated.h"

/**
 *
 */
UCLASS()
class ARENABATTLE_API AABAIController : public AAIController
{
	GENERATED_BODY()

public:
	AABAIController();//������

	void RunAI();//AI�� ������Ű�� �Լ�
	void StopAI();//AI�� ������Ű�� �Լ�

protected:
	//��Ʈ�ѷ��� ���� �����ؼ� ������ �� �߻��ϴ� �̺�Ʈ �Լ�.
	virtual void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY()
	TObjectPtr<class UBlackboardData> BBAsset;//�������� ����

	UPROPERTY()
	TObjectPtr<class UBehaviorTree> BTAsset;//�ൿ Ʈ�� ����
};