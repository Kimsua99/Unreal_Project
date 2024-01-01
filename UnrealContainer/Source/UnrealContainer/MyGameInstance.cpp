// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Algo/Accumulate.h"

void UMyGameInstance::Init()
{
	Super::Init();

	const int32 ArrayNum = 10;
	TArray<int32> Int32Array;

	//1부터 10까지의 정수를 어레이에 삽입
	for (int32 ix = 1; ix <= ArrayNum; ++ix)
	{
		Int32Array.Add(ix);
	}

	//람다식을 이용해 짝수만 남게 함.
	Int32Array.RemoveAll(
		[](int32 Val)
		{
			return Val % 2 == 0;
		}
	);

	//짝수 다시 채움
	Int32Array += {2, 4, 6, 8, 10};

	//바로 메모리에 접근
	TArray<int32> Int32ArrayCompare;
	int32 CArray[] = { 1,3,5,7,9,2,4,6,8,10 };
	//초기화되지 않은 데이터 10개를 넣어줌. 
	Int32ArrayCompare.AddUninitialized(ArrayNum);
	//메모리를 통해 복제하는데 포인터를 통해 복제해야 하므로 Int32ArrayCompare의 데이터를 가져옴. 
	FMemory::Memcpy(Int32ArrayCompare.GetData(), CArray, sizeof(int32) * ArrayNum);

	//두 어레이가 같은지 비교
	ensure(Int32Array == Int32ArrayCompare);

	//일반적인 총합값 계산 방법
	int Sum = 0;
	for (const int32& Int32Elem : Int32Array)
	{
		Sum += Int32Elem;
	}
	ensure(Sum == 55);

	//Algo의 Accumulate 함수를 이용한 총합값. 0은 시작값
	int32 SumByAlgo = Algo::Accumulate(Int32Array, 0);

	ensure(Sum == SumByAlgo);

	//TSet 선언 및 요소 추가
	TSet<int32>Int32Set;
	for (int32 ix = 1; ix <= ArrayNum; ++ix)
	{
		Int32Set.Add(ix);
	}
	//TSet 요소 제거. RemoveAll같은 함수가 없으므로 하나씩 제거함.
	Int32Set.Remove(2);
	Int32Set.Remove(4);
	Int32Set.Remove(6);
	Int32Set.Remove(8);
	Int32Set.Remove(10);

	//다시 요소 추가
	Int32Set.Add(2);
	Int32Set.Add(4);
	Int32Set.Add(6);
	Int32Set.Add(8);
	Int32Set.Add(10);


}
