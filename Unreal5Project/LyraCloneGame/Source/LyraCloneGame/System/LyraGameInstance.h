// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CommonGameInstance.h"
#include "LyraGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class LYRACLONEGAME_API ULyraGameInstance : public UCommonGameInstance
{
	GENERATED_BODY()
	
	/**
	 * UGameInstance's interfaces
	 */
	virtual void Init() override;
	virtual void Shutdown() override;
};
