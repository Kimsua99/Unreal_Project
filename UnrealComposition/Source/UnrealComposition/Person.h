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

	//const�� �Ἥ ���� ���ϰڴٰ� �ߴµ� ������ ���۷����� �޾Ƽ� ���� �����ϹǷ� const�� ���ǹ�����. ���� ��ȯ�� const�� �ؾ� �ùٸ��� ������.
	FORCEINLINE const FString& GetName() const { return Name; }
	FORCEINLINE void SetName(const FString& InName) { Name = InName; }

	FORCEINLINE class UCard* GetCard() const { return Card; }
	FORCEINLINE void SetCard(class UCard* InCard) { Card = InCard; }

protected:
	UPROPERTY()
	FString Name;
	
	UPROPERTY()
	TObjectPtr<class UCard> Card;
	//ī�� ��ü�� �����ϵ��� ����. �������� ������ ���� ���� ���� ����. ��� �������� �ʰ� ���� ���� ���� ������ ����.
	//���� ���� -> Ư�� Ŭ�������� �ٸ� Ŭ������ �����ͷ� ����� ��, �̸� �ش� Ŭ������ �ʿ��ϴٴ� ���� �˷���.
	//�����ͷ� ������ ���� TObjectPtr<T>�̶�� ���ø� Ŭ������ ���μ� ������ ��. 
};
