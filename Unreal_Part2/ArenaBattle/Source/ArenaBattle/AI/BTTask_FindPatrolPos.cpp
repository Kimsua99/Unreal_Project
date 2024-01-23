// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_FindPatrolPos.h"
#include "ABAI.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interface/ABCharacterAIInterface.h"

UBTTask_FindPatrolPos::UBTTask_FindPatrolPos()
{
}

//오버라이드 한 함수
EBTNodeResult::Type UBTTask_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	//BT를 소유한 컴포넌트의 오너를 GetAIOwner로 가져오는데, 폰에 빙의를 하고 있다면 GetPawn로 받아옴
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)//유효성 검사
	{
		return EBTNodeResult::Failed;//유효하지 않을 경우
	}

	//내비게이션 시스템 받아옴. V1이라는 클래스 이름을 받아옴. 
	//전역으로 설정된 GetNavigationSystem에 월드 값을 넣어주는데, 폰이 위치한 월드를 가져오면 된다.
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
	if (nullptr == NavSystem)//내비 시스템이 유효한지 체크
	{
		return EBTNodeResult::Failed;//유효하지 않으면
	}

	IABCharacterAIInterface* AIPawn = Cast<IABCharacterAIInterface>(ControllingPawn);
	if (nullptr == AIPawn)//캐스트 실패할 경우
	{
		return EBTNodeResult::Failed;
	}

	//블랙보드 값 가져옴. GetValueAsVector 함수 사용해 키를 넘김. 
	FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(BBKEY_HOMEPOS);
	float PatrolRadius = AIPawn->GetAIPatrolRadius();//AI 폰으로 부터 반지름 얻어옴
	
	FNavLocation NextPatrolPos;

	//해당 반지름 반경 내에 적당한 포지션을 찾으면 해당 함수의 값이 true가 됨,
	if (NavSystem->GetRandomPointInNavigableRadius(Origin, PatrolRadius, NextPatrolPos))
	{
		//찾은 정찰 위치를 키 값에 넣어줌
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(BBKEY_PATROLPOS, NextPatrolPos.Location);
		return EBTNodeResult::Succeeded;//성공
	}

	return EBTNodeResult::Failed;//그렇지 않으면 실패
}