// Fill out your copyright notice in the Description page of Project Settings.


#include "Student.h"
#include "Card.h"
//CourseInfo에 대한 헤더 없음 -> 개별적으로 존재 MyInstance가 이 둘을 컨트롤함.
 
UStudent::UStudent()
{
	Name = TEXT("이학생");
	Card->SetCardType(ECardType::Student);
}

void UStudent::DoLesson()
{
	//LessonInterface.cpp의 로그와 하단의 로그를 둘 다 띄우기 위해서 보통 Super을 사용하여 DoLesson을 상속받아 사용할 수 있는데
	//이미 Student.h가 Person을 상속받았고, 언리얼의 경우 단일 상속만 지원하기 떄문에 해당 클래스에서 함수를 입력해 둘 다 띄우도록 변경
	ILessonInterface::DoLesson();
	UE_LOG(LogTemp, Log, TEXT("%s님은 공부합니다."), *Name);
}

void UStudent::GetNotification(const FString& School, const FString& NewCourseInfo)
{
	UE_LOG(LogTemp, Log, TEXT("[Student] %s님이 %s로부터 받은 메시지 : %s"), *Name, *School, *NewCourseInfo);
}
