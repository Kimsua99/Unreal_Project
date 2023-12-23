// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h" 

UMyGameInstance::UMyGameInstance()//생성자 코드
{
	SchoolName = TEXT("기본학교");//기본값 설정. 
}
void UMyGameInstance::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Log, TEXT("=========================="));
	UClass* ClassRunTime = GetClass();//UMyGameInstance에 대한 클래스 정보를 런타임에서 얻어오기
	UClass* ClassCompile = UMyGameInstance::StaticClass();//UMyGameInstance에 대한 클래스 정보를 클래스 컴파일 타임에서 얻어오기
	
	//check(ClassRunTime == ClassCompile);//반드시 같은지 검증하고 넘어가야 하는 상황에서는 check라는 어설션(Assertion)함수를 사용함.
	//ensure(ClassRunTime != ClassCompile);
	//ensureMsgf(ClassRunTime != ClassCompile, TEXT("일부러 오류를 발생시킨 코드"));

	UE_LOG(LogTemp, Log, TEXT("학교를 담당하는 클래스 이름 : %s"), *ClassRunTime->GetName());//체크를 통과하면 이 로그를 볼 수 있음. 클래스 런타임에서 클래스 이름을 가져옴.

	SchoolName = TEXT("덕성여자대학교");//클래스의 인스턴스에 SchoolName을 바꿈

	UE_LOG(LogTemp, Log, TEXT("학교 이름: %s"), *SchoolName);
	//SchoolName이 Class Default Object라는 템플릿 객체에 저장되어 있기 때문에 UMyGameInstance를 바꾸더라도 기본값 호출 시 설정해둔 값이 출력됨.
	UE_LOG(LogTemp, Log, TEXT("학교 이름 기본값: %s"), *GetClass()->GetDefaultObject<UMyGameInstance>()->SchoolName);

	UE_LOG(LogTemp, Log, TEXT("=========================="));
}
