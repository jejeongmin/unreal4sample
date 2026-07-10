// Copyright Epic Games, Inc. All Rights Reserved.

#include "CrazyKartsWheelFront.h"
#include "UObject/ConstructorHelpers.h"

UCrazyKartsWheelFront::UCrazyKartsWheelFront()
{
	AxleType = EAxleType::Front;
	bAffectedBySteering = true;
	MaxSteerAngle = 40.f;
}