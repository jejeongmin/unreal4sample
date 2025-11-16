#pragma once

#include "LyraMappableConfigPair.generated.h"

/** forward declaration */
class UPlayerMappableInputConfig;

USTRUCT()
struct FLyraMappableConfigPair
{
	GENERATED_BODY()
public:
	FLyraMappableConfigPair() = default;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UPlayerMappableInputConfig> Config;

	UPROPERTY(EditAnywhere)
	bool bShouldActivateAutomatically = true;
};