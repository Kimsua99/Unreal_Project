// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Algo/Accumulate.h"

void UMyGameInstance::Init()
{
	Super::Init();

	const int32 ArrayNum = 10;
	TArray<int32> Int32Array;

	//1���� 10������ ������ ��̿� ����
	for (int32 ix = 1; ix <= ArrayNum; ++ix)
	{
		Int32Array.Add(ix);
	}

	//���ٽ��� �̿��� ¦���� ���� ��.
	Int32Array.RemoveAll(
		[](int32 Val)
		{
			return Val % 2 == 0;
		}
	);

	//¦�� �ٽ� ä��
	Int32Array += {2, 4, 6, 8, 10};

	//�ٷ� �޸𸮿� ����
	TArray<int32> Int32ArrayCompare;
	int32 CArray[] = { 1,3,5,7,9,2,4,6,8,10 };
	//�ʱ�ȭ���� ���� ������ 10���� �־���. 
	Int32ArrayCompare.AddUninitialized(ArrayNum);
	//�޸𸮸� ���� �����ϴµ� �����͸� ���� �����ؾ� �ϹǷ� Int32ArrayCompare�� �����͸� ������. 
	FMemory::Memcpy(Int32ArrayCompare.GetData(), CArray, sizeof(int32) * ArrayNum);

	//�� ��̰� ������ ��
	ensure(Int32Array == Int32ArrayCompare);

	//�Ϲ����� ���հ� ��� ���
	int Sum = 0;
	for (const int32& Int32Elem : Int32Array)
	{
		Sum += Int32Elem;
	}
	ensure(Sum == 55);

	//Algo�� Accumulate �Լ��� �̿��� ���հ�. 0�� ���۰�
	int32 SumByAlgo = Algo::Accumulate(Int32Array, 0);

	ensure(Sum == SumByAlgo);

	//TSet ���� �� ��� �߰�
	TSet<int32>Int32Set;
	for (int32 ix = 1; ix <= ArrayNum; ++ix)
	{
		Int32Set.Add(ix);
	}
	//TSet ��� ����. RemoveAll���� �Լ��� �����Ƿ� �ϳ��� ������.
	Int32Set.Remove(2);
	Int32Set.Remove(4);
	Int32Set.Remove(6);
	Int32Set.Remove(8);
	Int32Set.Remove(10);

	//�ٽ� ��� �߰�
	Int32Set.Add(2);
	Int32Set.Add(4);
	Int32Set.Add(6);
	Int32Set.Add(8);
	Int32Set.Add(10);


}
