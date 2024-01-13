// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ABItemBox.generated.h"

UCLASS()
class ARENABATTLE_API AABItemBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AABItemBox();

protected:
	UPROPERTY(VisibleAnywhere, Category = Box)
	TObjectPtr<class UBoxComponent> Trigger;//루트 컴포넌트에 해당하는 박스 컴포넌트

	UPROPERTY(VisibleAnywhere, Category = Box)
	TObjectPtr<class UStaticMeshComponent> Mesh;//스태틱 메쉬를 보여주는 컴포넌트

	UPROPERTY(VisibleAnywhere, Category = Effect)
	TObjectPtr<class UParticleSystemComponent> Effect;//이펙트 재생할 컴포넌트

	//오버랩 이벤트를 사용할 트리거 컴포넌트에는 이미 오버랩 이벤트를 감지하기 위한 델리게이트가 선언되어있다.
	//여기에 연결될 함수를 액터에 선언
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult);

	//UParticleSystemComponent를 인자로 가지는 함수. 
	UFUNCTION()
	void OnEffectFinished(class UParticleSystemComponent* ParticleSystem);
};
