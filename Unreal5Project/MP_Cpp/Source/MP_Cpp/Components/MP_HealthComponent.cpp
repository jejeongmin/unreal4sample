// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/MP_HealthComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UMP_HealthComponent::UMP_HealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	SetIsReplicatedByDefault(true);
}


// Called when the game starts
void UMP_HealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UMP_HealthComponent::OnRep_Health()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Health updated: %f"), Health));
}


// Called every frame
void UMP_HealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMP_HealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UMP_HealthComponent, Health);
}

