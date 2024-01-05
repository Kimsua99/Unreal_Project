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

	//지정자 설정. 객체타입, 블루프린트에서 상속받았을 때 읽고 쓸 수 있도록 지정.
	//카테고리를 메쉬로 지정하면 언리얼 헤더툴에 의해 카테고리가 분석이 되어 자동으로 메쉬에 대한 카테고리에 Body에 대한 값을 편집할 수 있게 UI가 제공됨.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
	//TObjectPtr로 컴포넌트 감싸줌. 헤더에 전방 선언을 통해 특별한 include 없이 StaticMeshComponent의 포인터 지정
	TObjectPtr<class UStaticMeshComponent> Body;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
	TObjectPtr<class UStaticMeshComponent> Water;
};
