﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "ActorSpawnerComponent.h"


// Sets default values for this component's properties
UActorSpawnerComponent::UActorSpawnerComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    //bWantsBeginPlay = true;	4.14에서 DEPRECATED됨. 이제는 무조건 BeginPlay호출됨
    PrimaryComponentTick.bCanEverTick = true;

    // ...
}


// Called when the game starts
void UActorSpawnerComponent::BeginPlay()
{
    Super::BeginPlay();

    // ...

}


void UActorSpawnerComponent::Spawn()
{
    UWorld* TheWorld = GetWorld();
    if (TheWorld != nullptr)
    {
        FTransform ComponentTransform(this->GetComponentTransform());
        TheWorld->SpawnActor(ActorToSpawn, &ComponentTransform);
    }
}

// Called every frame
void UActorSpawnerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // ...
}

