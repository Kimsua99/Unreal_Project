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
	UPerson();//생성자

	UFUNCTION()//언리얼 엔진이 관리하기 위한 매크로
	virtual void DoLesson();//가상함수 선언 

	const FString GetName() const;//외부에서 프로퍼티의 코드로 접근할 수 있게 하기 위해 게터와 세터 함수 선언
	void SetName(const FString& InName);
protected:
	UPROPERTY()
	FString Name;

	UPROPERTY()
	int32 Year;
private:

};
