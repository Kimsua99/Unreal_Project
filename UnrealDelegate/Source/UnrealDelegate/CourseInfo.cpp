// Fill out your copyright notice in the Description page of Project Settings.


#include "CourseInfo.h"
//Student에 대한 헤더 없음 -> 각각이 개별적으로 존재. MyInstance가 이 둘을 컨트롤함.
UCourseInfo::UCourseInfo()
{
	Contents = TEXT("기본 학사 정보");
}

void UCourseInfo::ChangeCourseInfo(const FString& InSchoolName, const FString& InNewContents)
{
	//새로운 학사 정보가 들어오면 변경을 해줌
	Contents = InNewContents;

	UE_LOG(LogTemp, Log, TEXT("[CourseInfo] 학사 정보가 변경되어 알림을 발송합니다."));
	OnChanged.Broadcast(InSchoolName, Contents);//OnChanged에 연결된 모든 함수들에게 두 개의 인자 정보를 방송
}
