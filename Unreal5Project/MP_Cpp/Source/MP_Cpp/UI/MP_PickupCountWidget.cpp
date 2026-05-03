// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MP_PickupCountWidget.h"
#include "Components/TextBlock.h"

void UMP_PickupCountWidget::SetPickupCount(int32 Count) const
{
	if (Text_PickupCount)
	{
		Text_PickupCount->SetText(FText::FromString(FString::FromInt(Count)));
	}
}
