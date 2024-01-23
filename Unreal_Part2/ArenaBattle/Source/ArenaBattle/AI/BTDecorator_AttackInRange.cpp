// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTDecorator_AttackInRange.h"
#include "ABAI.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interface/ABCharacterAIInterface.h"

UBTDecorator_AttackInRange::UBTDecorator_AttackInRange()
{
	NodeName = TEXT("CanAttack");//��� �̸� �ٿ���
}


bool UBTDecorator_AttackInRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);//���� Ŭ���� �� �޾ƿ�
	//�� ������
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
	{
		return false;
	}
	//�����κ��� �������̽� ������������ üũ
	IABCharacterAIInterface* AIPawn = Cast<IABCharacterAIInterface>(ControllingPawn);
	if (nullptr == AIPawn)
	{
		return false;
	}
	//Ÿ�ٰ��� ������
	APawn* Target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BBKEY_TARGET));
	if (nullptr == Target)
	{
		return false;
	}
	//�Ÿ����ϱ�
	float DistanceToTarget = ControllingPawn->GetDistanceTo(Target);
	//���� ����
	float AttackRangeWithRadius = AIPawn->GetAIAttackRange();
	//AI���� �Ǵ��� ���� ���� ���� �Ÿ��� ������ TRUE�� ��������.
	bResult = (DistanceToTarget <= AttackRangeWithRadius);
	return bResult;
}