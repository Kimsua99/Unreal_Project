// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Person.generated.h"

/**
 *
 */
UCLASS()
class UNREALCOMPOSITION_API UPerson : public UObject
{
	GENERATED_BODY()

	public:
	UPerson();

	//const를 써서 변경 안하겠다고 했는데 리턴을 레퍼런스로 받아서 변경 가능하므로 const가 무의미해짐. 따라서 반환도 const로 해야 올바르게 동작함.
	FORCEINLINE const FString& GetName() const { return Name; }
	FORCEINLINE void SetName(const FString& InName) { Name = InName; }

	FORCEINLINE class UCard* GetCard() const { return Card; }
	FORCEINLINE void SetCard(class UCard* InCard) { Card = InCard; }

protected:
	UPROPERTY()
	FString Name;
	
	UPROPERTY()
	TObjectPtr<class UCard> Card;
	//카드 객체를 소유하도록 지정. 컴포지션 관계일 때는 전방 선언 진행. 헤더 포함하지 않고 전방 선언 통해 의존성 없앰.
	//전방 선언 -> 특정 클래스에서 다른 클래스를 포인터로 사용할 때, 미리 해당 클래스가 필요하다는 것을 알려줌.
	//포인터로 선언한 것을 TObjectPtr<T>이라는 템플릿 클래스로 감싸서 선언해 줌. 
};
