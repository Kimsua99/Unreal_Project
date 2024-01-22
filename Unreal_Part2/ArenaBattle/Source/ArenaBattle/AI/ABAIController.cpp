// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ABAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

AABAIController::AABAIController()
{
	// �� ���� ���������� ����
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBAssetRef(TEXT("/Script/AIModule.BlackboardData'/Game/ArenaBattle/AI/BB_ABCharacter.BB_ABCharacter'"));
	if (nullptr != BBAssetRef.Object)
	{
		BBAsset = BBAssetRef.Object;
	}

	// �ൿ Ʈ�� ���������� ����
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTAssetRef(TEXT("/Script/AIModule.BehaviorTree'/Game/ArenaBattle/AI/BT_ABCharacter.BT_ABCharacter'"));
	if (nullptr != BTAssetRef.Object)
	{
		BTAsset = BTAssetRef.Object;
	}
}

void AABAIController::RunAI()//AI ����
{
	//������κ��� �� ���� ������Ʈ�� �����ͷ� ������
	UBlackboardComponent* BlackboardPtr = Blackboard.Get();

	//������ �⵿.������ �ʱ�ȭ ����
	if (UseBlackboard(BBAsset, BlackboardPtr))
	{
		//�ൿ Ʈ�� ����
		bool RunResult = RunBehaviorTree(BTAsset);
		ensure(RunResult);
	}
}

void AABAIController::StopAI()//AI ����
{
	//�����ϰ� �ִ� �ൿ Ʈ�� ������Ʈ�� �����ͷ� ������. 
	//BrainComponent��� �ϴ� ��������� ������ �Ǵµ�, �ൿ Ʈ�� ������Ʈ�� ĳ����
	UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BTComponent)//ĳ���� �����ߴٸ�
	{
		//�ൿ Ʈ�� ����
		BTComponent->StopTree();
	}
}

//���� �������� ��
void AABAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	RunAI();
}
