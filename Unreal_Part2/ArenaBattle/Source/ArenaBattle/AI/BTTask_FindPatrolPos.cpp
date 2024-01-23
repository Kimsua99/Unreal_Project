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

//�������̵� �� �Լ�
EBTNodeResult::Type UBTTask_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	//BT�� ������ ������Ʈ�� ���ʸ� GetAIOwner�� �������µ�, ���� ���Ǹ� �ϰ� �ִٸ� GetPawn�� �޾ƿ�
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)//��ȿ�� �˻�
	{
		return EBTNodeResult::Failed;//��ȿ���� ���� ���
	}

	//������̼� �ý��� �޾ƿ�. V1�̶�� Ŭ���� �̸��� �޾ƿ�. 
	//�������� ������ GetNavigationSystem�� ���� ���� �־��ִµ�, ���� ��ġ�� ���带 �������� �ȴ�.
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
	if (nullptr == NavSystem)//���� �ý����� ��ȿ���� üũ
	{
		return EBTNodeResult::Failed;//��ȿ���� ������
	}

	IABCharacterAIInterface* AIPawn = Cast<IABCharacterAIInterface>(ControllingPawn);
	if (nullptr == AIPawn)//ĳ��Ʈ ������ ���
	{
		return EBTNodeResult::Failed;
	}

	//������ �� ������. GetValueAsVector �Լ� ����� Ű�� �ѱ�. 
	FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(BBKEY_HOMEPOS);
	float PatrolRadius = AIPawn->GetAIPatrolRadius();//AI ������ ���� ������ ����
	
	FNavLocation NextPatrolPos;

	//�ش� ������ �ݰ� ���� ������ �������� ã���� �ش� �Լ��� ���� true�� ��,
	if (NavSystem->GetRandomPointInNavigableRadius(Origin, PatrolRadius, NextPatrolPos))
	{
		//ã�� ���� ��ġ�� Ű ���� �־���
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(BBKEY_PATROLPOS, NextPatrolPos.Location);
		return EBTNodeResult::Succeeded;//����
	}

	return EBTNodeResult::Failed;//�׷��� ������ ����
}