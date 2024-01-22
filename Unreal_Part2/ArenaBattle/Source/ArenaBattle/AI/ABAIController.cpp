// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ABAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

AABAIController::AABAIController()
{
	// 블랙 보드 고정적으로 배정
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBAssetRef(TEXT("/Script/AIModule.BlackboardData'/Game/ArenaBattle/AI/BB_ABCharacter.BB_ABCharacter'"));
	if (nullptr != BBAssetRef.Object)
	{
		BBAsset = BBAssetRef.Object;
	}

	// 행동 트리 고정적으로 배정
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTAssetRef(TEXT("/Script/AIModule.BehaviorTree'/Game/ArenaBattle/AI/BT_ABCharacter.BT_ABCharacter'"));
	if (nullptr != BTAssetRef.Object)
	{
		BTAsset = BTAssetRef.Object;
	}
}

void AABAIController::RunAI()//AI 구동
{
	//블랙보드로부터 블랙 보드 컴포넌트를 포인터로 가져옴
	UBlackboardComponent* BlackboardPtr = Blackboard.Get();

	//블랙보드 기동.블랙보드 초기화 진행
	if (UseBlackboard(BBAsset, BlackboardPtr))
	{
		//행동 트리 구동
		bool RunResult = RunBehaviorTree(BTAsset);
		ensure(RunResult);
	}
}

void AABAIController::StopAI()//AI 중지
{
	//동작하고 있는 행동 트리 컴포넌트를 포인터로 가져옴. 
	//BrainComponent라고 하는 멤버변수에 저장이 되는데, 행동 트리 컴포넌트로 캐스팅
	UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BTComponent)//캐스팅 성공했다면
	{
		//행동 트리 꺼줌
		BTComponent->StopTree();
	}
}

//폰에 빙의했을 때
void AABAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	RunAI();
}
