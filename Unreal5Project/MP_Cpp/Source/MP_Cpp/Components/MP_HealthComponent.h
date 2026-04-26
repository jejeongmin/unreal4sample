// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MP_HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MP_CPP_API UMP_HealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMP_HealthComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void SetHealth(float NewHealth) { Health = NewHealth; }
	float GetHealth() const { return Health; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(ReplicatedUsing=OnRep_Health)
	float Health;

	UFUNCTION()
	void OnRep_Health();
};
