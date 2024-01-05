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
	UMyGameInstance();//생성자 로직

	virtual void Init() override;

private:
	//학교가 학사 시스템을 소유해야 함. 학사 정보는 언리얼 오브젝트이고 포인터로 관리하므로 전방 선언 사용. 
	// 선언해서 언리얼 오브젝트의 포인터를 멤버 변수로 지정할 때는 TObjectPtr 사용
	UPROPERTY()
	TObjectPtr<class UCourseInfo> CourseInfo;

	UPROPERTY()//이걸 붙여야 언리얼 엔진이 관리하게 됨
	FString SchoolName;
};
