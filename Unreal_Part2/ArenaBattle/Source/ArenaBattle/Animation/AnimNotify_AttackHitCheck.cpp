// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_AttackHitCheck.h"
#include "Interface/ABAnimationAttackInterface.h"//�������̽� ����
//��Ƽ������ ��� �������� ���� ĳ���Ͱ� ���� �� ���� ����ϴ� ���� ������, 
//�� ������ ��� �߰��ϴ� ���� �������� �������Ƿ� �������̽��� �����ϴ� ���� ����.

void UAnimNotify_AttackHitCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)//�޽�������Ʈ�� �ִٸ�
	{
		//�޽� ������Ʈ�� �����ϰ� �ִ� Owner�� ������. 
		//�� Owner�� Character���� Ȯ���ϰ�, ĳ������ ��쿡�� ������ �����϶�� ����� ����.
		//�޾ƿ� �޽� ������Ʈ�� Owner�� �������̽��� �����ߴ��� üũ
		IABAnimationAttackInterface* AttackPawn = Cast<IABAnimationAttackInterface>(MeshComp->GetOwner());
		
		if (AttackPawn)//�ش� Owner�� �������̽��� �����ߴٸ�
		{
			AttackPawn->AttackHitCheck();//��������
		}
	}
}