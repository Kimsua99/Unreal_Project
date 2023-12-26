// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CourseInfo.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FCourseInfoOnChangedSignature, const FString&, const FString&);//ó���� ��������Ʈ �̸�. F�� �����ϰ� Ŭ���� �̸�, �̺�Ʈ �߻��ߴٴ� ���� ON, �л� ���� ����Ǿ����� �˸��� Changed, Signature��� ���̻�

/**
 * 
 */
UCLASS()
class UNREALDELEGATE_API UCourseInfo : public UObject
{
	GENERATED_BODY()

public:
	UCourseInfo();//������

	FCourseInfoOnChangedSignature OnChanged;//��������Ʈ�� ��� ������ ���

	void ChangeCourseInfo(const FString& InSchoolName, const FString& InNewContents);//�ܺο��� �л� ������ �����Ѵٰ� �� �� ���� �Լ�. 

private:
	FString Contents;//�л� ������ ���� ����
	
};
