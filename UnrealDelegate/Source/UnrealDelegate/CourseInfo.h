// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CourseInfo.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FCourseInfoOnChangedSignature, const FString&, const FString&);//처음은 델리게이트 이름. F로 시작하고 클래스 이름, 이벤트 발생했다는 뜻의 ON, 학사 정보 변경되었음을 알리는 Changed, Signature라는 접미사

/**
 * 
 */
UCLASS()
class UNREALDELEGATE_API UCourseInfo : public UObject
{
	GENERATED_BODY()

public:
	UCourseInfo();//생성자

	FCourseInfoOnChangedSignature OnChanged;//델리게이트를 멤버 변수로 등록

	void ChangeCourseInfo(const FString& InSchoolName, const FString& InNewContents);//외부에서 학사 정보를 변경한다고 할 때 쓰는 함수. 

private:
	FString Contents;//학사 정보에 대한 내용
	
};
