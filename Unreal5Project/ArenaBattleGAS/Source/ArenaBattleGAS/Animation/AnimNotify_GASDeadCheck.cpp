// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_GASDeadCheck.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "Tag/ABGameplayTag.h"

UAnimNotify_GASDeadCheck::UAnimNotify_GASDeadCheck()
{
}

FString UAnimNotify_GASDeadCheck::GetNotifyName_Implementation() const
{
    return TEXT("DeadCheck");
}

void UAnimNotify_GASDeadCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Super::Notify(MeshComp, Animation, EventReference);

    if (MeshComp)
    {
        AActor* OwnerActor = MeshComp->GetOwner();
        if (OwnerActor)
        {
            UAbilitySystemComponent* ASC = nullptr;
            if (OwnerActor->GetClass()->ImplementsInterface(UAbilitySystemInterface::StaticClass()))
            {
                ASC = Cast<IAbilitySystemInterface>(OwnerActor)->GetAbilitySystemComponent();
            }

            if (ASC)
            {
                FGameplayCueParameters CueParam;

                ASC->ExecuteGameplayCue(ABTAG_GAMEPLAYCUE_CHARACTER_DEADSINK, CueParam);
            }
        }
    }
}