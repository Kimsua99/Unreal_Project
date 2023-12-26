// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Student.h"
#include "Teacher.h"
#include "Staff.h"
#include "Card.h"

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
		//사람마다 소유한 카드를 가져옴
		const UCard* OwnCard = Person->GetCard();
		check(OwnCard);
		ECardType CardType = OwnCard->GetCardType();
		//여기까지 실행하면 카드 이름이 1, 2, 3으로 나오는데, 각각 어떤 카드인지 문자로 보여주기 위해서 다음의 작업을 거침
		
		//열거형 정보를 가져옴. 두번째 인자로 절대 주소값 넣어 원하는 타입 정보 얻어옴. 
		const UEnum* CardEnumType = FindObject<UEnum>(nullptr, TEXT("/Script/UnrealComposition.ECardType"));
		if (CardEnumType)//있으면
		{
			//메타 데이터만 받아오고 텍스트를 string으로 변경함.
			FString CardMetaData = CardEnumType->GetDisplayNameTextByValue((int64)CardType).ToString();
			UE_LOG(LogTemp, Log, TEXT("%s님이 소유한 카드 종류 %s"), *Person->GetName(), *CardMetaData);
		}
	}

	UE_LOG(LogTemp, Log, TEXT("============================"));
}
