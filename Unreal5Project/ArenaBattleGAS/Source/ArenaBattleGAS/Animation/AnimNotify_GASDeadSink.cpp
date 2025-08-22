// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_GASDeadSink.h"
#include "AbilitySystemBlueprintLibrary.h"

UAnimNotify_GASDeadSink::UAnimNotify_GASDeadSink()
{
}

FString UAnimNotify_GASDeadSink::GetNotifyName_Implementation() const
{
	return TEXT("GASDeadSink");
}

void UAnimNotify_GASDeadSink::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		AActor* OwnerActor = MeshComp->GetOwner();
		if (OwnerActor)
		{
			FGameplayEventData PayloadData;
			PayloadData.EventMagnitude = 1.0f; // You can set this to a specific value if needed
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OwnerActor, FGameplayTag::RequestGameplayTag(FName("GameplayCue.Character.DeadSink")), PayloadData);
		}
	}
}

