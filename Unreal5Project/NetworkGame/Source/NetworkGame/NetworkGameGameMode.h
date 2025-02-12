// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "APIDataTypes.h"
#include "APIHandler.h"
#include "NetworkGameGameMode.generated.h"

UCLASS(minimalapi)
class ANetworkGameGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ANetworkGameGameMode();

#pragma region httpCallImplementation1
	FHttpModule* Http;
	
	UFUNCTION(BlueprintCallable)
	void HttpCall(const FString& InURL, const FString& InVerb);

	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
#pragma endregion

#pragma region httpCallImplementation2
	virtual void StartPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(BlueprintCallable)
	void TestRequest(const FSampleRequestBody& InRequestBody);
	void OnResponse(const FSampleResponseBody& InResponseBody);

private:
	FAPIHandler APIHandler;
	FDelegateHandle ResponseHandle;
#pragma endregion
};