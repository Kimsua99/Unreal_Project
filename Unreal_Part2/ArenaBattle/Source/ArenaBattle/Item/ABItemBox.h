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
	//������ �ڽ��� ��� Ʈ���� ������Ʈ�� protected�� �ۿ��� ���� �Ұ�
	FORCEINLINE class UBoxComponent* GetTrigger() { return Trigger; }

	//������ �ڽ��� �ʱ�ȭ �Ǿ��� ��, ���� �Ŵ����� �����ϴ� ��ϵ��� ���� �� �� �ϳ��� �������� �Ҵ��ϴ� ���� �߰�
	//�̸� ���� ���� ���� ������ �Ǿ��� �� ȣ��Ǵ� �Լ� ����
protected:
	virtual void PostInitializeComponents() override;


protected:
	UPROPERTY(VisibleAnywhere, Category = Box)
	TObjectPtr<class UBoxComponent> Trigger;//��Ʈ ������Ʈ�� �ش��ϴ� �ڽ� ������Ʈ

	UPROPERTY(VisibleAnywhere, Category = Box)
	TObjectPtr<class UStaticMeshComponent> Mesh;//����ƽ �޽��� �����ִ� ������Ʈ

	UPROPERTY(VisibleAnywhere, Category = Effect)
	TObjectPtr<class UParticleSystemComponent> Effect;//����Ʈ ����� ������Ʈ

	UPROPERTY(EditAnywhere, Category = Item)
	TObjectPtr<class UABItemData> Item;//������ ���� �߰�. �θ� Ŭ�������� ���������Ƿ� ����, ����, ��ũ�� �� �ϳ��� ������.

	//������ �̺�Ʈ�� ����� Ʈ���� ������Ʈ���� �̹� ������ �̺�Ʈ�� �����ϱ� ���� ��������Ʈ�� ����Ǿ��ִ�.
	//���⿡ ����� �Լ��� ���Ϳ� ����
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult);

	//UParticleSystemComponent�� ���ڷ� ������ �Լ�. 
	UFUNCTION()
	void OnEffectFinished(class UParticleSystemComponent* ParticleSystem);
};
