// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_AttackHitCheck.h"
#include "Interface/ABAnimationAttackInterface.h"//인터페이스 참조
//노티파이의 경우 공용으로 여러 캐릭터가 있을 떄 같이 사용하는 것이 좋은데, 
//이 때마다 헤더 추가하는 것은 의존성이 높아지므로 인터페이스를 구현하는 것이 좋음.

void UAnimNotify_AttackHitCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)//메시컴포넌트가 있다면
	{
		//메시 컴포넌트가 소유하고 있는 Owner를 가져옴. 
		//이 Owner가 Character인지 확인하고, 캐릭터인 경우에는 공격을 판정하라고 명령을 내림.
		//받아온 메쉬 컴포넌트의 Owner가 인터페이스를 구현했는지 체크
		IABAnimationAttackInterface* AttackPawn = Cast<IABAnimationAttackInterface>(MeshComp->GetOwner());
		
		if (AttackPawn)//해당 Owner가 인터페이스를 구현했다면
		{
			AttackPawn->AttackHitCheck();//공격판정
		}
	}
}