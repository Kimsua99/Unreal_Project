// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ABStageGimmick.generated.h"

DECLARE_DELEGATE(FOnStageChangedDelegate);
USTRUCT(BlueprintType)
struct FStageChangedDelegateWrapper//��������Ʈ�� ���δ� ���� ����ü
{
	GENERATED_BODY()
	FStageChangedDelegateWrapper() { }
	FStageChangedDelegateWrapper(const FOnStageChangedDelegate& InDelegate) : StageDelegate(InDelegate) {}
	FOnStageChangedDelegate StageDelegate;
};

UENUM(BlueprintType)
enum class EStageState : uint8//���¸� ������ �� �ִ� ������
{
	READY = 0,
	FIGHT,
	REWARD,
	NEXT
};

UCLASS()
class ARENABATTLE_API AABStageGimmick : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AABStageGimmick();

public:
	FORCEINLINE int32 GetStageNum() const { return CurrentStageNum; }
	FORCEINLINE void SetStageNum(int32 NewStageNum) { CurrentStageNum = NewStageNum; }

protected:
	//�Ӽ��� ��ȭ�� �˷��ִ� �Լ�
	//Ʈ�������� ����� ���� ���ڷ� ����
	virtual void OnConstruction(const FTransform& Transform) override;

	// Stage Section
protected:
	UPROPERTY(VisibleAnywhere, Category = Stage, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> Stage;//��Ʈ ������Ʈ

	UPROPERTY(VisibleAnywhere, Category = Stage, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UBoxComponent> StageTrigger;//�÷��̾ ������ �� ������ �� �ִ� Ʈ���� ����

	UFUNCTION()
	void OnStageTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//�÷��̾�� �������� Ʈ������ ������ �̺�Ʈ�� �ߵ��Ǹ� �޾��� �Լ� ó��
	
	// Gate Section, 4���� ���� ���� ����
protected:
	UPROPERTY(VisibleAnywhere, Category = Gate, Meta = (AllowPrivateAccess = "true"))
	TMap<FName, TObjectPtr<class UStaticMeshComponent>> Gates;
	//����Ʈ�� 4���� �ʿ��ϹǷ� Map���� �����ϰ� ����Ʈ���� ������ ������ Ű�� �ִµ�, �������� 4���� Ű�� �����ϸ� �ش��ϴ� ���� ���� ����ƽ �޽� ���� �� �ְ� ����

	UPROPERTY(VisibleAnywhere, Category = Gate, Meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<class UBoxComponent>> GateTriggers;
	//������ ������ Ʈ���Ÿ� ��ġ�ؼ� �迭�� ����

	UFUNCTION()
	void OnGateTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//��� ���� ���� �Լ�
	void OpenAllGates();
	//��� ���� �ݴ� �Լ�
	void CloseAllGates();


	// State Section
protected:
	UPROPERTY(EditAnywhere, Category = Stage, Meta = (AllowPrivateAccess = "true"))
	EStageState CurrentState;

	//���� ������ �׻� �ش� �Լ� ȣ���� ���� �̷�������� ���� ��Ģ ����.
	void SetState(EStageState InNewState);

	UPROPERTY()//���� ����ü���� �ڷᱸ��
	TMap<EStageState, FStageChangedDelegateWrapper> StateChangeActions;

	//������ ���¿� ���� ���ε��� �Լ����� ������ ����
	void SetReady();
	void SetFight();
	void SetChooseReward();
	void SetChooseNext();

	// Fight Section
protected:
	//������ NPC�� ȣ���ؾ� �ϴµ�, NPC�� �����ϱ� ���� ���� Ŭ���� �����ϵ��� Ŭ���� ���� �ֵ��� ���� �߰�.
	//TSubclassOf ���ø� Ŭ������ ���, ������ Ŭ�����κ��� ��ӹ��� Ŭ���� ��ϸ� ǥ�õǵ��� ������ ���� ��� ����
	UPROPERTY(EditAnywhere, Category = Fight, Meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AABCharacterNonPlayer> OpponentClass;

	//���� ������ �ɾ���
	UPROPERTY(EditAnywhere, Category = Fight, Meta = (AllowPrivateAccess = "true"))
	float OpponentSpawnTime;

	//npc ������ ���� �ܰ�� �̵��ؾ� �ϹǷ� �̰��� ���� �Լ� ����
	UFUNCTION()
	void OnOpponentDestroyed(AActor* DestroyedActor);

	FTimerHandle OpponentTimerHandle;
	void OnOpponentSpawn();

	// Reward Section
protected:
	//���� �ڽ��� ���� ������ �� �ְ� Ŭ���� ����.
	//AABItemBox�� ��ӹ��� �͸� ������ �� �ֵ��� TSubclassOf ���ø����� Ÿ�� ����
	UPROPERTY(VisibleAnywhere, Category = Reward, Meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AABItemBox> RewardBoxClass;

	//�迭 ����.
	//TWeakObjectPtr��� ���ø� Ŭ������ �����ߴµ�, �̸� ��������� �Ѵ�.
	//RewardBoxes�� ������ ���ڸ� �����ϱ� ���� ����� ���ε�, ������ ���ڵ��� �۾��ϰ� �ִ� �������� ��� ���Ϳʹ� �����ϰ�
	//������ ������ �ϰ� �ȴ�.���� �ܺ� ������ �ްų� ���� ������ ���� ������ �Ҹ�� �� �ִµ�, �̸� ������ ��, ����ó�� TObjectPtr(������)�� �ɰ� �Ǹ�
	//�𸮾��� �̸� ���� ������ ����ϰ� �ִٰ� �Ǵ��� �޸𸮿��� �Ҹ��Ű�� ���� �� �ִ�. ���� ���������� �������� ������ �� �ְ� �������� �������ִ� ���� ����.
	UPROPERTY(VisibleAnywhere, Category = Reward, Meta = (AllowPrivateAccess = "true"))
	TArray<TWeakObjectPtr<class AABItemBox>> RewardBoxes;

	//������ �ڽ��� ������ų ��ġ�� ���� Ű�� ������ �� �ֵ��� MAP���� ����
	TMap<FName, FVector> RewardBoxLocations;

	//������ ���ڿ� ���� ������ �̺�Ʈ �ߵ� �� �����Ű�� �Լ� ����
	UFUNCTION()
	void OnRewardTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//���� ���� �Լ� ����
	void SpawnRewardBoxes();

	// Stage Stat
protected:
	UPROPERTY(VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	int32 CurrentStageNum;//��Ϳ��� ���������� Ŭ���� �� ������ NPC�� ������ �ϳ��� �ö󰡼� �� ���� ���� �������� ����
};
