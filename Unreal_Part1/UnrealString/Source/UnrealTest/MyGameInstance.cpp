// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

void UMyGameInstance::Init()
{
	Super::Init();

	TCHAR LogCharArray[] = TEXT("Hello Unreal");
	UE_LOG(LogTemp, Log, LogCharArray);

	FString LogCharString = LogCharArray;
	UE_LOG(LogTemp, Log, TEXT("%s"), *LogCharString);

	//포인터 연산자를 사용하여 FString으로 받은 문자열을 끄집어 내는 과정. const로 변하지 않게 참조하도록 선언.
	const TCHAR* LogCharPtr = *LogCharString;
	//const가 아닌 직접 포인터를 받아 고치고 싶을 경우 TArray에 첫번쨰 인자인 포인터를 가져와야 한다. 이 경우 CharArray를 직접 가져와서 GetData로 TCHAR의 포인터를 가져와 메모리 직접 접근해 사용 가능하다.
	TCHAR* LogCharDataPtr = LogCharString.GetCharArray().GetData();

	//배열로 가져오고 싶을 경우 배열 크기 선언해주고 저수준의 스트링 복사를 한다. strcpy는 FCString 에서 제공하는 함수이다. 이를 길이만큼 복사를 해주되 버퍼를 지정해준다. 
	TCHAR LogCharArrayWithSize[100];
	FCString::Strcpy(LogCharArrayWithSize, LogCharString.Len(), *LogCharString);

	//대소문자 구분 없이 문자열 찾는 함수, 몇번째 위치에 언리얼이라는 문자가 있는지 반환
	if (LogCharString.Contains(TEXT("unreal"), ESearchCase::IgnoreCase))
	{
		int32 Index = LogCharString.Find(TEXT("unreal"), ESearchCase::IgnoreCase);

		//언리얼이 시작되는 위치에서 끝까지 잘라주는 함수
		FString EndString = LogCharString.Mid(Index);
		UE_LOG(LogTemp, Log, TEXT("Find Test: %s"), *EndString);
	}

	//공백을 기준으로 문자열 나누기
	FString Left, Right;
	if (LogCharString.Split(TEXT(" "), &Left, &Right))
	{
		UE_LOG(LogTemp, Log, TEXT("Split Test: %s와 %s"), *Left, *Right);
	}

	//정수, float을 문자열로 변환해 출력하기
	int32 IntValue = 32;
	float FloatValue = 3.141592;

	FString FloatIntString = FString::Printf(TEXT("Int: %d Float: %f"), IntValue, FloatValue);
	FString FloatString = FString::SanitizeFloat(FloatValue);
	FString IntString = FString::FromInt(IntValue);

	UE_LOG(LogTemp, Log, TEXT("%s"), *FloatIntString);
	UE_LOG(LogTemp, Log, TEXT("Int: %s Float: %s"), *IntString, *FloatString);

	//문자열을 정수, float으로 변환하기
	int32 IntValueFromString = FCString::Atoi(*IntString);
	float FloatValueFromString = FCString::Atof(*FloatString);
	FString FloatIntString2 = FString::Printf(TEXT("Int: %d Float: %f"), IntValueFromString, FloatValueFromString);
	UE_LOG(LogTemp, Log, TEXT("%s"), *FloatIntString2);

	//FName에서 대소문자 구분이 없음을 보여주는 예제
	FName key1(TEXT("PELVIS"));
	FName key2(TEXT("pelvis"));
	UE_LOG(LogTemp, Log, TEXT("FName 비교 결과 : %s"), key1 == key2 ? TEXT("같음") : TEXT("다름"));

	for (int i = 0; i < 10000; i++)
	{
		//루프문에서 네임풀에 존재 여부를 계속 확인하게 되면 오버헤드 발생할 수 있음
		FName SearchInNamePool = FName(TEXT("pelvis"));
		//따라서 FName에 관련 키 값만 저장이 되면 되므로 const static으로 한 번만 처리해 줌.
		//초기화 할 때 데이터 저장하고 이후부터는 찾을 일이 없이 저장된 값을 쓰는 것이 효과적임.
		const static FName StaticOnlyOnce(TEXT("pelvis"));
	}
}
