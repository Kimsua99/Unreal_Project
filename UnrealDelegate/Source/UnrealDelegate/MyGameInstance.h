// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREALDELEGATE_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UMyGameInstance();//������ ����

	virtual void Init() override;

private:
	//�б��� �л� �ý����� �����ؾ� ��. �л� ������ �𸮾� ������Ʈ�̰� �����ͷ� �����ϹǷ� ���� ���� ���. 
	// �����ؼ� �𸮾� ������Ʈ�� �����͸� ��� ������ ������ ���� TObjectPtr ���
	UPROPERTY()
	TObjectPtr<class UCourseInfo> CourseInfo;

	UPROPERTY()//�̰� �ٿ��� �𸮾� ������ �����ϰ� ��
	FString SchoolName;
};
