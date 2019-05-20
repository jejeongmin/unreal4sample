// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ShooterPickup.generated.h"

/*
	jejeongmin	2019-05-20

	레벨상에 pickup 을 배치하기 위한 blueprint 클래스들의 부모 클래스가 된다.
	NotifyActorBeginOverlap 를 이용해 touch 를 감지하지만,
	하위 클래스들이 GivePickupTo 를 상속해 처리할 수 있도록 설계되었다.

	pick 처리 설계를 위한 좋은 예제임.
*/
// Base class for pickup objects that can be placed in the world
UCLASS(abstract)
class AShooterPickup : public AActor
{
	GENERATED_UCLASS_BODY()

	/** pickup on touch */
	virtual void NotifyActorBeginOverlap(class AActor* Other) override;

	/** check if pawn can use this pickup */
	virtual bool CanBePickedUp(class AShooterCharacter* TestPawn) const;

protected:
	/** initial setup */
	virtual void BeginPlay() override;

private:
	/** FX component */
	UPROPERTY(VisibleDefaultsOnly, Category=Effects)
	UParticleSystemComponent* PickupPSC;

protected:
	/** FX of active pickup */
	UPROPERTY(EditDefaultsOnly, Category=Effects)
	UParticleSystem* ActiveFX;

	/** FX of pickup on respawn timer */
	UPROPERTY(EditDefaultsOnly, Category=Effects)
	UParticleSystem* RespawningFX;

	/** sound played when player picks it up */
	UPROPERTY(EditDefaultsOnly, Category=Effects)
	USoundCue* PickupSound;

	/** sound played on respawn */
	UPROPERTY(EditDefaultsOnly, Category=Effects)
	USoundCue* RespawnSound;

	/** how long it takes to respawn? */
	UPROPERTY(EditDefaultsOnly, Category=Pickup)
	float RespawnTime;

	/** is it ready for interactions? */
	/*
		jejeongmin	2019-05-19
		
		ReplicatedUsing=OnRep_IsActive 를 이용해 UE3 의 RefNotify 처럼 replication dirty 를
		함수 호출을 통해 확인할 수 있다.
	*/
	UPROPERTY(Transient, ReplicatedUsing=OnRep_IsActive)
	uint32 bIsActive:1;

	/* The character who has picked up this pickup */
	UPROPERTY(Transient, Replicated)
	AShooterCharacter* PickedUpBy;

	/** Handle for efficient management of RespawnPickup timer */
	FTimerHandle TimerHandle_RespawnPickup;

	UFUNCTION()
	void OnRep_IsActive();

	/** give pickup */
	virtual void GivePickupTo(class AShooterCharacter* Pawn);

	/** handle touches */
	void PickupOnTouch(class AShooterCharacter* Pawn);

	/** show and enable pickup */
	virtual void RespawnPickup();

	/** show effects when pickup disappears */
	virtual void OnPickedUp();

	/** show effects when pickup appears */
	virtual void OnRespawned();

	/*
		jejeongmin	2019-05-19

		픽업 아이템 리스폰 시, 픽업 시 호출되며, blueprint 로도 재정의할 수 있다.
		블루 프린트에서 event 를 구현할 수 있게 한 적절한 좋은 예시.
	*/
	/** blueprint event: pickup disappears */
	UFUNCTION(BlueprintImplementableEvent)
	void OnPickedUpEvent();

	/** blueprint event: pickup appears */
	UFUNCTION(BlueprintImplementableEvent)
	void OnRespawnEvent();

protected:
	/** Returns PickupPSC subobject **/
	FORCEINLINE UParticleSystemComponent* GetPickupPSC() const { return PickupPSC; }
};
