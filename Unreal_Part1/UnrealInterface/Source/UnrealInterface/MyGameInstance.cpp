// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Student.h"
#include "Teacher.h"
#include "Staff.h"

UMyGameInstance::UMyGameInstance()
{
	SchoolName = TEXT("기본학교");
}

void UMyGameInstance::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Log, TEXT("============================"));
	TArray<UPerson*> Persons = { NewObject<UStudent>(), NewObject<UTeacher>(), NewObject<UStaff>() };
	for (const auto Person : Persons)
	{
		UE_LOG(LogTemp, Log, TEXT("구성원 이름 : %s"), *Person->GetName());
	}
	UE_LOG(LogTemp, Log, TEXT("============================"));

	for (const auto Person : Persons)
	{
		//형변환 실패 여부를 통해 ILessonInterface을 구현했는지 안 구현했는지를 알 수 있다.
		ILessonInterface* LessonInterface = Cast<ILessonInterface>(Person);
		if (LessonInterface)//ILessonInterface을 상속 받은 경우
		{
			UE_LOG(LogTemp, Log, TEXT("%s님은 수업에 참여할 수 있습니다."), *Person->GetName());
			LessonInterface->DoLesson();
		}
		else//ILessonInterface을 상속 받지 않은 경우 -> Null 값 반환되어 실패 확인
		{
			UE_LOG(LogTemp, Log, TEXT("%s님은 수업에 참여할 수 없습니다."), *Person->GetName());
		}
	}
	UE_LOG(LogTemp, Log, TEXT("============================"));

}
