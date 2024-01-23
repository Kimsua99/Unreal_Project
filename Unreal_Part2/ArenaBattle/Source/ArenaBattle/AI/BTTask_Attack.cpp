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
	//AI 컨트롤러가 조종하고 있는 폰을 가져옴
	APawn* ControllingPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == ControllingPawn)
	{
		return EBTNodeResult::Failed;
	}
	//인터페이스를 통해 공격 명령 내리기 위해 받아옴
	IABCharacterAIInterface* AIPawn = Cast<IABCharacterAIInterface>(ControllingPawn);
	if (nullptr == AIPawn)
	{
		return EBTNodeResult::Failed;
	}


	FAICharacterAttackFinished OnAttackFinished;//델리게이트 선언
	OnAttackFinished.BindLambda(//원하는 함수 묶음
		[&]()
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);//InProgress로 리턴한 후에 마무리를 알려주는 함수 사용해서 성공했음을 리턴
		}
	);

	AIPawn->SetAIAttackDelegate(OnAttackFinished);//공격 끝나는 타이밍 캐치 위한 함수. 델리게이트 설정해줌.
	AIPawn->AttackByAI();
	return EBTNodeResult::InProgress;//진행 중으로 하고 공격 끝나야 Succeeded로 반환.
}