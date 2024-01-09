// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ABCharacterNonPlayer.h"

AABCharacterNonPlayer::AABCharacterNonPlayer()
{
}

void AABCharacterNonPlayer::SetDead()
{
	Super::SetDead(); // �θ�κ��� ��ӹ��� �Լ�

	FTimerHandle DeadTimerHandle;//������ 5�� �ð� �ڿ� �������� ���� Ÿ�̸� �ڵ� �߰�

	//����κ��� ���� ����. �Լ��� �����ϴµ�, 5�� �ڿ� � �Լ� ȣ������ ���� ����.
	//���͸� ���ִ� �Լ��� �����ϴµ� ������ ����� ���� ���� �Լ� ���,
	//Ÿ�̸� ��������Ʈ�� ������Ű�� �̸� �ٷ� �ѱ�� ������ ����. FTimerDelegate ����ü ����
	//
	GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda(
		[&]()
		{
			Destroy();
		}
	), DeadEventDelayTime, false);//������ �ʿ� �����Ƿ� false
}
