// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ABCharacterNonPlayer.h"

AABCharacterNonPlayer::AABCharacterNonPlayer()
{
}

void AABCharacterNonPlayer::SetDead()
{
	Super::SetDead(); // 부모로부터 상속받은 함수

	FTimerHandle DeadTimerHandle;//지정한 5초 시간 뒤에 없어지기 위해 타이머 핸들 추가

	//월드로부터 서비스 받음. 함수를 지정하는데, 5초 뒤에 어떤 함수 호출할지 지정 가능.
	//액터를 없애는 함수를 지정하는데 간편히 만들기 위해 람다 함수 사용,
	//타이머 델리게이트에 부착시키고 이를 바로 넘기는 식으로 구현. FTimerDelegate 구조체 생성
	//
	GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda(
		[&]()
		{
			Destroy();
		}
	), DeadEventDelayTime, false);//매핑할 필요 없으므로 false
}
