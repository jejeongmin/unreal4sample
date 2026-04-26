// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "M_MultiplayerUtils.generated.h"

/**
 * 
 */
UCLASS()
class MP_CPP_API UM_MultiplayerUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable, Category = "Multiplayer Utils")
	static void PrintLocalNetRole(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category = "Multiplayer Utils")
	static void PrintRemoteNetRole(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category = "Multiplayer Utils")
	static void PrintRole(AActor* Actor);
};
