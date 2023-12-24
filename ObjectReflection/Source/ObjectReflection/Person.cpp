// Fill out your copyright notice in the Description page of Project Settings.


#include "Person.h"

UPerson::UPerson()
{
	Name = TEXT("김수아");
	Year = 1;
}

void UPerson::DoLesson()
{
	UE_LOG(LogTemp, Log, TEXT("%s님이 수업에 참여합니다."), *Name);
}

const FString UPerson::GetName() const//이름 정보를 받아옴
{
	return Name;
}

void UPerson::SetName(const FString& InName)//받아온 이름 정보를 갱신함
{
	Name = InName;
}
