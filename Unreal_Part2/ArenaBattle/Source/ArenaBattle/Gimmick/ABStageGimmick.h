// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ABStageGimmick.generated.h"

DECLARE_DELEGATE(FOnStageChangedDelegate);
USTRUCT(BlueprintType)
struct FStageChangedDelegateWrapper//델리게이트를 감싸는 래퍼 구조체
{
	GENERATED_BODY()
	FStageChangedDelegateWrapper() { }
	FStageChangedDelegateWrapper(const FOnStageChangedDelegate& InDelegate) : StageDelegate(InDelegate) {}
	FOnStageChangedDelegate StageDelegate;
};

UENUM(BlueprintType)
enum class EStageState : uint8//상태를 보관할 수 있는 열거형
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
	//속성의 변화를 알려주는 함수
	//트랜스폼의 변경된 값을 인자로 받음
	virtual void OnConstruction(const FTransform& Transform) override;

	// Stage Section
protected:
	UPROPERTY(VisibleAnywhere, Category = Stage, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> Stage;//루트 컴포넌트

	UPROPERTY(VisibleAnywhere, Category = Stage, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UBoxComponent> StageTrigger;//플레이어가 들어왔을 떄 감지할 수 있는 트리거 생성

	UFUNCTION()
	void OnStageTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//플레이어와 스테이지 트리거의 오버랩 이벤트가 발동되면 받아줄 함수 처리
	
	// Gate Section, 4개의 문에 대한 설정
protected:
	UPROPERTY(VisibleAnywhere, Category = Gate, Meta = (AllowPrivateAccess = "true"))
	TMap<FName, TObjectPtr<class UStaticMeshComponent>> Gates;
	//게이트가 4개가 필요하므로 Map으로 구성하고 게이트에는 각각의 고유한 키가 있는데, 동서남북 4개의 키를 전달하면 해당하는 문에 대한 스태틱 메쉬 얻을 수 있게 설정

	UPROPERTY(VisibleAnywhere, Category = Gate, Meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<class UBoxComponent>> GateTriggers;
	//각각의 문마다 트리거를 배치해서 배열로 관리

	UFUNCTION()
	void OnGateTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//모든 문을 여는 함수
	void OpenAllGates();
	//모든 문을 닫는 함수
	void CloseAllGates();


	// State Section
protected:
	UPROPERTY(EditAnywhere, Category = Stage, Meta = (AllowPrivateAccess = "true"))
	EStageState CurrentState;

	//상태 변경은 항상 해당 함수 호출을 통해 이루어지도록 내부 규칙 정함.
	void SetState(EStageState InNewState);

	UPROPERTY()//래퍼 구조체들의 자료구조
	TMap<EStageState, FStageChangedDelegateWrapper> StateChangeActions;

	//각각의 상태에 대해 바인딩할 함수들을 별도로 선언
	void SetReady();
	void SetFight();
	void SetChooseReward();
	void SetChooseNext();

	// Fight Section
protected:
	//대전할 NPC를 호출해야 하는데, NPC를 생성하기 위해 먼저 클래스 지정하도록 클래스 정보 넣도록 변수 추가.
	//TSubclassOf 템플릿 클래스의 경우, 지정한 클래스로부터 상속받은 클래스 목록만 표시되도록 한정해 지정 기능 제공
	UPROPERTY(EditAnywhere, Category = Fight, Meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AABCharacterNonPlayer> OpponentClass;

	//스폰 딜레이 걸어줌
	UPROPERTY(EditAnywhere, Category = Fight, Meta = (AllowPrivateAccess = "true"))
	float OpponentSpawnTime;

	//npc 죽으면 보상 단계로 이동해야 하므로 이것을 위한 함수 지정
	UFUNCTION()
	void OnOpponentDestroyed(AActor* DestroyedActor);

	FTimerHandle OpponentTimerHandle;
	void OnOpponentSpawn();

	// Reward Section
protected:
	//보상 박스에 대해 스폰할 수 있게 클래스 지정.
	//AABItemBox를 상속받은 것만 한정할 수 있도록 TSubclassOf 템플릿으로 타입 지정
	UPROPERTY(VisibleAnywhere, Category = Reward, Meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AABItemBox> RewardBoxClass;

	//배열 변수.
	//TWeakObjectPtr라는 템플릿 클래스로 선언했는데, 이를 약참조라고 한다.
	//RewardBoxes는 스폰된 상자를 관리하기 위해 선언된 것인데, 스폰된 상자들은 작업하고 있는 스테이지 기믹 액터와는 무관하게
	//스스로 동작을 하게 된다.따라서 외부 영향을 받거나 내부 로직에 의해 스스로 소멸될 수 있는데, 이를 관리할 떄, 기존처럼 TObjectPtr(강참조)로 걸게 되면
	//언리얼이 이를 보고 아직도 사용하고 있다고 판단해 메모리에서 소멸시키지 않을 수 있다. 따라서 무관하지만 관리함을 보여줄 수 있게 약참조로 선언해주는 것이 좋다.
	UPROPERTY(VisibleAnywhere, Category = Reward, Meta = (AllowPrivateAccess = "true"))
	TArray<TWeakObjectPtr<class AABItemBox>> RewardBoxes;

	//리워드 박스를 스폰시킬 위치에 대해 키로 관리할 수 있도록 MAP으로 선언
	TMap<FName, FVector> RewardBoxLocations;

	//생성된 상자에 대해 오버랩 이벤트 발동 시 실행시키는 함수 선언
	UFUNCTION()
	void OnRewardTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//상자 스폰 함수 선언
	void SpawnRewardBoxes();

	// Stage Stat
protected:
	UPROPERTY(VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	int32 CurrentStageNum;//기믹에서 스테이지를 클리어 할 때마다 NPC의 레벨이 하나씩 올라가서 더 높은 스탯 가지도록 설정
};
