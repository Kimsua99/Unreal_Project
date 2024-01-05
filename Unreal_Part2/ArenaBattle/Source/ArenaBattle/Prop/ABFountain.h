// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ABFountain.generated.h"

UCLASS()
class ARENABATTLE_API AABFountain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AABFountain();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//������ ����. ��üŸ��, �������Ʈ���� ��ӹ޾��� �� �а� �� �� �ֵ��� ����.
	//ī�װ��� �޽��� �����ϸ� �𸮾� ������� ���� ī�װ��� �м��� �Ǿ� �ڵ����� �޽��� ���� ī�װ��� Body�� ���� ���� ������ �� �ְ� UI�� ������.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
	//TObjectPtr�� ������Ʈ ������. ����� ���� ������ ���� Ư���� include ���� StaticMeshComponent�� ������ ����
	TObjectPtr<class UStaticMeshComponent> Body;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
	TObjectPtr<class UStaticMeshComponent> Water;
};
