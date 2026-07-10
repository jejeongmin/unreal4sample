// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CrazyKartsPawn.h"
#include "CrazyKartsSportsCar.generated.h"

/**
 *  Sports car wheeled vehicle implementation
 */
UCLASS(abstract)
class CRAZYKARTS_API ACrazyKartsSportsCar : public ACrazyKartsPawn
{
	GENERATED_BODY()
	
public:

	ACrazyKartsSportsCar();
};
