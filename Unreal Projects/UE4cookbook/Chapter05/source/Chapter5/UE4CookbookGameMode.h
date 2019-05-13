// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "UE4CookbookGameMode.generated.h"

DECLARE_DELEGATE(FStandardDelegateSignature)
DECLARE_DELEGATE_OneParam(FParamDelegateSignature, FLinearColor)
DECLARE_MULTICAST_DELEGATE(FMulticastDelegateSignature)
/**
 * 
 */
UCLASS()
class CHAPTER5_API AUE4CookbookGameMode : public AGameMode
{
	GENERATED_BODY()

public:
		AUE4CookbookGameMode();

		virtual void BeginPlay() override;

		// delegate 는 할당된 기능을 모른 채 호출할 수 있다.
		FStandardDelegateSignature MyStandardDelegate;

		FParamDelegateSignature MyParameterDelegate;

		FMulticastDelegateSignature MyMulticastDelegate;

};
