// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CommonSessionSubsystem.generated.h"


/** A request object that stores the parameters used when hosting a gameplay session */
UCLASS(BlueprintType)
class COMMONUSER_API UCommonSession_HostSessionRequest : public UObject
{
	GENERATED_BODY()

public:
	/** MapID -> Text 변환 */
	virtual FString GetMapName() const;

	/** Server Travel 에 전달할 최종 URL 을 생성한다. */
	virtual FString ConstructTravelURL() const;

public:
	/** 준비할 MapID (맵 경로) */
	UPROPERTY(BlueprintReadWrite, Category = Session, meta = (AllowedTypes = "World"))
	FPrimaryAssetId MapID;

	/** 전달할 CmdArg (Experience 이름을 전달함) -> 곧 UserFacingExperienceDefinition 에서 보게 될 것임 */
	UPROPERTY(BlueprintReadWrite, Category = Session)
	TMap<FString, FString> ExtraArgs;
};

/**
 * 
 */
UCLASS()
class COMMONUSER_API UCommonSessionSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UCommonSessionSubsystem() {}

	/** Creates a new online game using the session request information, if successful this will start a hard map transfer */
	UFUNCTION(BlueprintCallable, Category = Session)
	virtual void HostSession(APlayerController* HostingPlayer, UCommonSession_HostSessionRequest* Request);

protected:
	/** PendingTravelURL 은 흔히 맵의 경로로 생각하면 된다 */
	FString PendingTravelURL;
	
};
