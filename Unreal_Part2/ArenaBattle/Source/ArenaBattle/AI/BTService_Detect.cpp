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
	NodeName = TEXT("Detect");//노드 이름을 Detect라고 표시될 수 있도록 지정
	Interval = 1.0f;//Tick의 인터벌을 1초 단위로 수행하도록 지정
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	//AI로 부터 현재 제어하고 있는 폰의 정보를 가져옴
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)//폰을 가져오지 못하면
	{
		return;//해당 함수 리턴
	}

	FVector Center = ControllingPawn->GetActorLocation();//폰의 위치
	UWorld* World = ControllingPawn->GetWorld();//폰이 속한 월드의 값
	if (nullptr == World)//월드 값 가져오지 못하면
	{
		return;
	}
	//AI인터페이스를 형변환해서 가져옴
	IABCharacterAIInterface* AIPawn = Cast<IABCharacterAIInterface>(ControllingPawn);
	if (nullptr == AIPawn)
	{
		return;
	}

	//인터페이스로부터 감지할 영역에 대한 값을 가져옴. 반경에 해당
	float DetectRadius = AIPawn->GetAIDetectRange();

	TArray<FOverlapResult> OverlapResults;//결과물이 배열로 들어옴
	//플레이어 감지. 다수가 있다는 가정에 Multi로 오버랩해서 받아옴
	FCollisionQueryParams CollisionQueryParam(SCENE_QUERY_STAT(Detect), false, ControllingPawn);
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		CCHANNEL_ABACTION,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQueryParam
	);

	if (bResult)//감지가 되었다면
	{
		for (auto const& OverlapResult : OverlapResults)//감지된 모든 폰에 대해 반복문 실행
		{
			APawn* Pawn = Cast<APawn>(OverlapResult.GetActor());
			//폰을 조종하고 있는 것이 플레이어 컨트롤러 일 경우에만 감지했다고 가정을 함
			if (Pawn && Pawn->GetController()->IsPlayerController())
			{
				//BBKEY_TARGET를 폰으로 해서 타겟 값을 저장하도록 로직 지정
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(BBKEY_TARGET, Pawn);
				//녹색으로 해당 영역 표시되도록 함
				DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);

				//플레이어와의 위치를 선과 점으로 표현하도록 기능 추가
				DrawDebugPoint(World, Pawn->GetActorLocation(), 10.0f, FColor::Green, false, 0.2f);
				DrawDebugLine(World, ControllingPawn->GetActorLocation(), Pawn->GetActorLocation(), FColor::Green, false, 0.27f);
				return;//성공하면 리턴
			}
		}
	}

	//찾지 못했을 경우에는 
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(BBKEY_TARGET, nullptr);
	//붉은색 구로 표시를 하도록 로직 구성
	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
}