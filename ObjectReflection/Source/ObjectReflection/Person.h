// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Person.generated.h"

/**
 * 
 */
UCLASS()
class OBJECTREFLECTION_API UPerson : public UObject
{
	GENERATED_BODY()
public:
	UPerson();//������

	UFUNCTION()//�𸮾� ������ �����ϱ� ���� ��ũ��
	virtual void DoLesson();//�����Լ� ���� 

	const FString GetName() const;//�ܺο��� ������Ƽ�� �ڵ�� ������ �� �ְ� �ϱ� ���� ���Ϳ� ���� �Լ� ����
	void SetName(const FString& InName);
protected:
	UPROPERTY()
	FString Name;

	UPROPERTY()
	int32 Year;
private:

};
