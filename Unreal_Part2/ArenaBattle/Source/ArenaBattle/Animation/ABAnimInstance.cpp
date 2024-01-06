// Fill out your copyright notice in the Description page of Project Settings.


#include "ABAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UABAnimInstance::UABAnimInstance()
{
	MovingThreshould = 3.0f;//움직이고 있는지
	JumpingThreshould = 100.0f;//점프하고 있는지
}

void UABAnimInstance::NativeInitializeAnimation()//초기화, 오브젝트 포인터 값을 초기화하는 로직
{
	Super::NativeInitializeAnimation();

	Owner = Cast<ACharacter>(GetOwningActor());//현재 AnimInstance를 소유하고 있는 액터 정보를 얻어올 수 있는데, 액터 타입으로 반환되므로 어떤 캐릭터인지 확인 불가. 캐릭터로 형변환
	if (Owner)//형변환 성공적으로 되면
	{
		Movement = Owner->GetCharacterMovement();
	}
}

void UABAnimInstance::NativeUpdateAnimation(float DeltaSeconds)//무브먼트 객체가 있을 때 프레임마다 캐릭터 무브먼트 객체로부터 원하는 값 얻어옴.
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Movement)
	{
		Velocity = Movement->Velocity;
		GroundSpeed = Velocity.Size2D();//지면의 속력은 X,Y의 크기만 구함.
		bIsIdle = GroundSpeed < MovingThreshould;//움직이지 않는 상태의 확인은 지면 속력이 움직이는지 확인하는 값보다 작으면 idle로 판정
		bIsFalling = Movement->IsFalling();
		bIsJumping = bIsFalling & (Velocity.Z > JumpingThreshould);//bIsFalling이 만족되고, 속력의 Z 값이 JumpingThreshould보다 클 경우 점핑 상태임을 판정
		//이 다섯가지 속성들은 프레임마다 업데이트 됨.
	}
}

