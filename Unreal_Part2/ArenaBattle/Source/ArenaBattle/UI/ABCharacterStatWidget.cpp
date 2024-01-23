// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ABCharacterStatWidget.h"
#include "Components/TextBlock.h"

void UABCharacterStatWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//������ �ʱ�ȭ�� �� FABCharacterStat�̶�� ����ü�� ������ �Ӽ����� ���� ��� �о ��Ī�Ǵ� �ؽ�Ʈ ����� �����͸� �������� ����
	//�ݺ��ڸ� ����� ����ü�� ���� �Ӽ����� �̾��ִ� for ����. ����ü�� StaticStruct�� �޾ƿ� �� �ִ�.
	for (TFieldIterator<FNumericProperty> PropIt(FABCharacterStat::StaticStruct()); PropIt; ++PropIt)
	{
		//�Ӽ��� ���� Ű ��
		const FName PropKey(PropIt->GetName());
		//���̽� ���� ���� �ش��ϴ� �ؽ�Ʈ ��Ʈ�� �̸�
		const FName TextBaseControlName = *FString::Printf(TEXT("Txt%sBase"), *PropIt->GetName());
		//������̾� ��Ʈ�ѿ� ���� ������ ��Ʈ���� �̸����� ��ȯ
		const FName TextModifierControlName = *FString::Printf(TEXT("Txt%sModifier"), *PropIt->GetName());

		//���̽� ��Ʈ�� �̸��� �޾ƿ� �ؽ�Ʈ ��Ͽ� ���� �����͸� ������
		UTextBlock* BaseTextBlock = Cast<UTextBlock>(GetWidgetFromName(TextBaseControlName));
		if (BaseTextBlock)//�����ϸ�
		{
			//��� ���̺��̶�� �ϴ� �� ������ ����� �߰�
			//Ű ���� �ؽ�Ʈ ����� ������ ����
			BaseLookup.Add(PropKey, BaseTextBlock);
		}
		//������̾ ������ ������� ������
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

