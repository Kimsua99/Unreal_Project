// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Student.h"
#include "StudentManager.h"

void CheckObjectIsValid(const UObject* InObject, const FString& InTag)
{
	//유효성 판단. 정교하게 체크해주는 함수 사용
	if (InObject->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Log, TEXT("[%s] 유효한 언리얼 오브젝트"), *InTag);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("[%s] 유효하지 않은 언리얼 오브젝트"), *InTag);
	}
}

void CheckObjectIsNull(const UObject* InObject, const FString& InTag)
{
	//유효성 판단. 정교하게 체크해주는 함수 사용
	if (nullptr == InObject)
	{
		UE_LOG(LogTemp, Log, TEXT("[%s] 널 포인터 언리얼 오브젝트"), *InTag);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("[%s] 널 포인터가 아닌 언리얼 오브젝트"), *InTag);
	}
}

void UMyGameInstance::Init()
{
	Super::Init();

	NonPropStudent = NewObject<UStudent>();
	PropStudent = NewObject<UStudent>();

	NonPropStudents.Add(NewObject<UStudent>());
	PropStudents.Add(NewObject<UStudent>());

	StudentManager = new FStudentManager(NewObject<UStudent>());
}

void UMyGameInstance::Shutdown()
{
	Super::Shutdown();

	const UStudent* StudentInManager = StudentManager->GetStudent();

	delete StudentManager;
	StudentManager = nullptr;

	CheckObjectIsNull(StudentInManager, TEXT("StudentInManager"));
	CheckObjectIsValid(StudentInManager, TEXT("StudentInManager"));

	CheckObjectIsNull(NonPropStudent, TEXT("NonPropStudent"));
	CheckObjectIsValid(NonPropStudent, TEXT("NonPropStudent"));

	CheckObjectIsNull(PropStudent, TEXT("PropStudent"));
	CheckObjectIsValid(PropStudent, TEXT("PropStudent"));

	CheckObjectIsNull(NonPropStudents[0], TEXT("NonPropStudents"));
	CheckObjectIsValid(NonPropStudents[0], TEXT("NonPropStudents"));

	CheckObjectIsNull(PropStudents[0], TEXT("PropStudents"));
	CheckObjectIsValid(PropStudents[0], TEXT("PropStudents"));
}
