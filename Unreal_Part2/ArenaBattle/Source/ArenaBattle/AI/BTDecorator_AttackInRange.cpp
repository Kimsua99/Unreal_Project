// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTDecorator_AttackInRange.h"
#include "ABAI.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interface/ABCharacterAIInterface.h"

UBTDecorator_AttackInRange::UBTDecorator_AttackInRange()
{
	NodeName = TEXT("CanAttack");//노드 이름 붙여줌
}


bool UBTDecorator_AttackInRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);//상위 클래스 값 받아옴
	//폰 가져옴
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
	{
		return false;
	}
	//폰으로부터 인터페이스 가져오는지를 체크
	IABCharacterAIInterface* AIPawn = Cast<IABCharacterAIInterface>(ControllingPawn);
	if (nullptr == AIPawn)
	{
		return false;
	}
	//타겟값을 가져옴
	APawn* Target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BBKEY_TARGET));
	if (nullptr == Target)
	{
		return false;
	}
	//거리구하기
	float DistanceToTarget = ControllingPawn->GetDistanceTo(Target);
	//공격 범위
	float AttackRangeWithRadius = AIPawn->GetAIAttackRange();
	//AI에서 판단한 공격 범위 내에 거리가 들어오면 TRUE를 리턴해줌.
	bResult = (DistanceToTarget <= AttackRangeWithRadius);
	return bResult;
}