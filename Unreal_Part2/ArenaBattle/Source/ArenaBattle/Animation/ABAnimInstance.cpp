// Fill out your copyright notice in the Description page of Project Settings.


#include "ABAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UABAnimInstance::UABAnimInstance()
{
	MovingThreshould = 3.0f;//�����̰� �ִ���
	JumpingThreshould = 100.0f;//�����ϰ� �ִ���
}

void UABAnimInstance::NativeInitializeAnimation()//�ʱ�ȭ, ������Ʈ ������ ���� �ʱ�ȭ�ϴ� ����
{
	Super::NativeInitializeAnimation();

	Owner = Cast<ACharacter>(GetOwningActor());//���� AnimInstance�� �����ϰ� �ִ� ���� ������ ���� �� �ִµ�, ���� Ÿ������ ��ȯ�ǹǷ� � ĳ�������� Ȯ�� �Ұ�. ĳ���ͷ� ����ȯ
	if (Owner)//����ȯ ���������� �Ǹ�
	{
		Movement = Owner->GetCharacterMovement();
	}
}

void UABAnimInstance::NativeUpdateAnimation(float DeltaSeconds)//�����Ʈ ��ü�� ���� �� �����Ӹ��� ĳ���� �����Ʈ ��ü�κ��� ���ϴ� �� ����.
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Movement)
	{
		Velocity = Movement->Velocity;
		GroundSpeed = Velocity.Size2D();//������ �ӷ��� X,Y�� ũ�⸸ ����.
		bIsIdle = GroundSpeed < MovingThreshould;//�������� �ʴ� ������ Ȯ���� ���� �ӷ��� �����̴��� Ȯ���ϴ� ������ ������ idle�� ����
		bIsFalling = Movement->IsFalling();
		bIsJumping = bIsFalling & (Velocity.Z > JumpingThreshould);//bIsFalling�� �����ǰ�, �ӷ��� Z ���� JumpingThreshould���� Ŭ ��� ���� �������� ����
		//�� �ټ����� �Ӽ����� �����Ӹ��� ������Ʈ ��.
	}
}

