// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_Attack.h"
#include "AIController.h"
#include "Interface/ABCharacterAIInterface.h"

UBTTask_Attack::UBTTask_Attack()
{
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
	//AI ��Ʈ�ѷ��� �����ϰ� �ִ� ���� ������
	APawn* ControllingPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == ControllingPawn)
	{
		return EBTNodeResult::Failed;
	}
	//�������̽��� ���� ���� ��� ������ ���� �޾ƿ�
	IABCharacterAIInterface* AIPawn = Cast<IABCharacterAIInterface>(ControllingPawn);
	if (nullptr == AIPawn)
	{
		return EBTNodeResult::Failed;
	}


	FAICharacterAttackFinished OnAttackFinished;//��������Ʈ ����
	OnAttackFinished.BindLambda(//���ϴ� �Լ� ����
		[&]()
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);//InProgress�� ������ �Ŀ� �������� �˷��ִ� �Լ� ����ؼ� ���������� ����
		}
	);

	AIPawn->SetAIAttackDelegate(OnAttackFinished);//���� ������ Ÿ�̹� ĳġ ���� �Լ�. ��������Ʈ ��������.
	AIPawn->AttackByAI();
	return EBTNodeResult::InProgress;//���� ������ �ϰ� ���� ������ Succeeded�� ��ȯ.
}