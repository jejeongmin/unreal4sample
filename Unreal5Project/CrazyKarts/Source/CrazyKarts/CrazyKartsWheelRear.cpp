// Copyright Epic Games, Inc. All Rights Reserved.

#include "CrazyKartsWheelRear.h"
#include "UObject/ConstructorHelpers.h"

UCrazyKartsWheelRear::UCrazyKartsWheelRear()
{
	AxleType = EAxleType::Rear;
	bAffectedByHandbrake = true;
	bAffectedByEngine = true;
}