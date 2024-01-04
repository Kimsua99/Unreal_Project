// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h" //해당 언리얼 오브젝트에 선언된 헤더가 가장 위에 있어야 하는 규칙 
#include "Student.h"
#include "Teacher.h"

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

	UStudent* Student = NewObject<UStudent>();
	UTeacher* Teacher = NewObject<UTeacher>();

	//getter와 setter를 사용하여 학생의 이름을 변경하는 방법
	Student->SetName(TEXT("학생1"));
	UE_LOG(LogTemp, Log, TEXT("새로운 학생 이름 %s"), *Student->GetName());

	//언리얼의 리플렉션을 사용하여 선생의 이름을 변경하는 방법
	FString CurrentTeacherName;
	//선생님 이름 변경 위한 새로운 이름 값
	FString NewTeacherName(TEXT("이득우"));
	//속성 이름을 검색해서 프로퍼티에 대한 포인터를 가져옴. 
	FProperty* NameProp = UTeacher::StaticClass()->FindPropertyByName(TEXT("Name"));
	//만약 있는 경우 Null이 아니게 됨
	if (NameProp)
	{
		//클래스의 속성에 대해 지정한 인스턴스의 값을 빼올 수 있음. 선생님의 객체 속성 중에 이름 속성 값을 가져옴.
		NameProp->GetValue_InContainer(Teacher, &CurrentTeacherName);
		UE_LOG(LogTemp, Log, TEXT("현재 선생님 이름 %s"), *CurrentTeacherName);

		NameProp->SetValue_InContainer(Teacher, &NewTeacherName);
		UE_LOG(LogTemp, Log, TEXT("새로운 선생님 이름 %s"), *Teacher->GetName());
	}

	UE_LOG(LogTemp, Log, TEXT("=========================="));

	Student->DoLesson();
	//리플렉션을 사용하여 특정 함수 출력
	//UFunction에 대한 포인터 값을 알아야 함. 런타임의 클래스 정보를 받아오는데 DoLesson함수 이름으로 검색하여 Func에 대한 객체를 받아옴.
	UFunction* DoLessonFunc = Teacher->GetClass()->FindFunctionByName(TEXT("DoLesson"));
	//찾은 경우
	if (DoLessonFunc)
	{
		//인스턴스 지정. ProcessEvent함수 사용하여 함수 포인터를 넘겨줌. 인자가 없으므로 두번째 인자는 nullptr
		Teacher->ProcessEvent(DoLessonFunc, nullptr);
	}

	UE_LOG(LogTemp, Log, TEXT("=========================="));
}
