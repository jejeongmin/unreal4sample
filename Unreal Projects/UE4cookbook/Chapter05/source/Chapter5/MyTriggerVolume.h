// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MyTriggerVolume.generated.h"

DECLARE_EVENT(AMyTriggerVolume, FPlayerEntered)

UCLASS()
class CHAPTER5_API AMyTriggerVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyTriggerVolume();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY()
		UBoxComponent* TriggerZone;
	
	//UFUNCTION()
		//void OnTriggerOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	UFUNCTION()
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	/*
		사용자 정의 이벤트는 매우 유용하지만, 다른 서드파티 클래스에 의해 외부에서 브로드캐스트할 수 있다는 한계점이 있다.
		즉, Excute / Broadcast 메서드가 공개적으로 액세스할 수 있다는 것이다. 때로는 다른 클래스에 의해 외부에서 바인드는 할수는 있지만
		해당 클래스에 의해서만 브로드캐스트할 수 있는 델리게이트가 필요할 수 있다. 이것이 이벤트의 주목적이다.
	*/
	FPlayerEntered OnPlayerEntered;
};
