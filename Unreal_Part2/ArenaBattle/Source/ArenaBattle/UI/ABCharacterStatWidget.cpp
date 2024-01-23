// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ABCharacterStatWidget.h"
#include "Components/TextBlock.h"

void UABCharacterStatWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//위젯이 초기화될 때 FABCharacterStat이라는 구조체가 가지는 속성들의 값을 모두 읽어서 매칭되는 텍스트 블록의 포인터를 가져오는 과정
	//반복자를 사용해 구조체가 가진 속성들을 뽑아주는 for 구문. 구조체는 StaticStruct로 받아올 수 있다.
	for (TFieldIterator<FNumericProperty> PropIt(FABCharacterStat::StaticStruct()); PropIt; ++PropIt)
	{
		//속성에 대한 키 값
		const FName PropKey(PropIt->GetName());
		//베이스 스탯 값에 해당하는 텍스트 컨트롤 이름
		const FName TextBaseControlName = *FString::Printf(TEXT("Txt%sBase"), *PropIt->GetName());
		//모디파이어 컨트롤에 접근 가능한 스트링을 이름으로 변환
		const FName TextModifierControlName = *FString::Printf(TEXT("Txt%sModifier"), *PropIt->GetName());

		//베이스 컨트롤 이름을 받아와 텍스트 블록에 대한 포인터를 가져옴
		UTextBlock* BaseTextBlock = Cast<UTextBlock>(GetWidgetFromName(TextBaseControlName));
		if (BaseTextBlock)//존재하면
		{
			//룩업 테이블이라고 하는 맵 구조에 만들어 추가
			//키 값과 텍스트 블록의 포인터 지정
			BaseLookup.Add(PropKey, BaseTextBlock);
		}
		//모디파이어도 동일한 방법으로 가져옴
		UTextBlock* ModifierTextBlock = Cast<UTextBlock>(GetWidgetFromName(TextModifierControlName));
		if (ModifierTextBlock)
		{
			ModifierLookup.Add(PropKey, ModifierTextBlock);
		}
	}
}

void UABCharacterStatWidget::UpdateStat(const FABCharacterStat& BaseStat, const FABCharacterStat& ModifierStat)
{
	for (TFieldIterator<FNumericProperty> PropIt(FABCharacterStat::StaticStruct()); PropIt; ++PropIt)
	{
		const FName PropKey(PropIt->GetName());

		float BaseData = 0.0f;
		PropIt->GetValue_InContainer((const void*)&BaseStat, &BaseData);
		float ModifierData = 0.0f;
		PropIt->GetValue_InContainer((const void*)&ModifierStat, &ModifierData);

		UTextBlock** BaseTextBlockPtr = BaseLookup.Find(PropKey);
		if (BaseTextBlockPtr)
		{
			(*BaseTextBlockPtr)->SetText(FText::FromString(FString::SanitizeFloat(BaseData)));
		}

		UTextBlock** ModifierTextBlockPtr = ModifierLookup.Find(PropKey);
		if (ModifierTextBlockPtr)
		{
			(*ModifierTextBlockPtr)->SetText(FText::FromString(FString::SanitizeFloat(ModifierData)));
		}
	}
}

