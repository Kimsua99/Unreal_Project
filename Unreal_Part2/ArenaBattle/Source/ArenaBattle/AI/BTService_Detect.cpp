// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_Detect.h"
#include "ABAI.h"
#include "AIController.h"
#include "Interface/ABCharacterAIInterface.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Physics/ABCollision.h"
#include "DrawDebugHelpers.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");//��� �̸��� Detect��� ǥ�õ� �� �ֵ��� ����
	Interval = 1.0f;//Tick�� ���͹��� 1�� ������ �����ϵ��� ����
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	//AI�� ���� ���� �����ϰ� �ִ� ���� ������ ������
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)//���� �������� ���ϸ�
	{
		return;//�ش� �Լ� ����
	}

	FVector Center = ControllingPawn->GetActorLocation();//���� ��ġ
	UWorld* World = ControllingPawn->GetWorld();//���� ���� ������ ��
	if (nullptr == World)//���� �� �������� ���ϸ�
	{
		return;
	}
	//AI�������̽��� ����ȯ�ؼ� ������
	IABCharacterAIInterface* AIPawn = Cast<IABCharacterAIInterface>(ControllingPawn);
	if (nullptr == AIPawn)
	{
		return;
	}

	//�������̽��κ��� ������ ������ ���� ���� ������. �ݰ濡 �ش�
	float DetectRadius = AIPawn->GetAIDetectRange();

	TArray<FOverlapResult> OverlapResults;//������� �迭�� ����
	//�÷��̾� ����. �ټ��� �ִٴ� ������ Multi�� �������ؼ� �޾ƿ�
	FCollisionQueryParams CollisionQueryParam(SCENE_QUERY_STAT(Detect), false, ControllingPawn);
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		CCHANNEL_ABACTION,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQueryParam
	);

	if (bResult)//������ �Ǿ��ٸ�
	{
		for (auto const& OverlapResult : OverlapResults)//������ ��� ���� ���� �ݺ��� ����
		{
			APawn* Pawn = Cast<APawn>(OverlapResult.GetActor());
			//���� �����ϰ� �ִ� ���� �÷��̾� ��Ʈ�ѷ� �� ��쿡�� �����ߴٰ� ������ ��
			if (Pawn && Pawn->GetController()->IsPlayerController())
			{
				//BBKEY_TARGET�� ������ �ؼ� Ÿ�� ���� �����ϵ��� ���� ����
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(BBKEY_TARGET, Pawn);
				//������� �ش� ���� ǥ�õǵ��� ��
				DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);

				//�÷��̾���� ��ġ�� ���� ������ ǥ���ϵ��� ��� �߰�
				DrawDebugPoint(World, Pawn->GetActorLocation(), 10.0f, FColor::Green, false, 0.2f);
				DrawDebugLine(World, ControllingPawn->GetActorLocation(), Pawn->GetActorLocation(), FColor::Green, false, 0.27f);
				return;//�����ϸ� ����
			}
		}
	}

	//ã�� ������ ��쿡�� 
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(BBKEY_TARGET, nullptr);
	//������ ���� ǥ�ø� �ϵ��� ���� ����
	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
}