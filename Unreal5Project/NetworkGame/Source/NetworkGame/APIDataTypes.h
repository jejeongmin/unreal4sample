// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "APIDataTypes.generated.h"

class NETWORKGAME_API APIDataTypes
{
public:
};



USTRUCT(BlueprintType)
struct NETWORKGAME_API FData
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Number;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int64 Begin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int64 End;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Text;
};

USTRUCT(BlueprintType)
struct NETWORKGAME_API FSampleRequestBody
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Data;
};


USTRUCT(BlueprintType)
struct NETWORKGAME_API FSampleResponseBody
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FData> DataList;
};