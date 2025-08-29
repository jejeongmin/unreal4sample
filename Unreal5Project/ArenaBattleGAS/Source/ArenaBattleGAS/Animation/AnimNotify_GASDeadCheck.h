// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_GASDeadCheck.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLEGAS_API UAnimNotify_GASDeadCheck : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	UAnimNotify_GASDeadCheck();

protected:
	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
