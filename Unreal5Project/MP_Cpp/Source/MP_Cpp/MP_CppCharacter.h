// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Interaction/MP_Player.h"
#include "MP_CppCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UMP_HealthComponent;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AMP_CppCharacter : public ACharacter, public IMP_Player
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** General Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* GeneralAction;

	/** Spawn Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SpawnAction;

	/** Server RPC Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ServerRPCAction;

public:
	AMP_CppCharacter();

	/** IMP_Player Interface */
	virtual USkeletalMeshComponent* GetPlayerMesh_Implementation() override;

	virtual void GrantArmor_Implementation(float ArmorAmount) override;

	virtual void IncementPickupCount_Implementation() override;

	virtual void IncreaseHealth_Implementation(float HealthAmount) override;
	

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for general input */
	void GeneralInput(const FInputActionValue& Value);

	/** Called for spawn input */
	void SpawnInput(const FInputActionValue& Value);

	/** Called for server rpc input */
	void ServerRpcInput(const FInputActionValue& Value);

	virtual void NotifyControllerChanged() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay() override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	//////////////// Crash Course /////////////////////
	// 1. Override GetLifetimeReplicatedProps to specify which properties should be replicated to clients
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreReplication(IRepChangedPropertyTracker& ChangedPropertyTracker) override;

private:

	// 2. Add the UPROPERTY macro with Replicated to the variable you want to replicate. This will ensure that the variable's value is sent from the server to all clients.
	UPROPERTY(Replicated)
	float	Armor;

	UPROPERTY(ReplicatedUsing=OnRep_PickupCount)
	int32	PickupCount = 0;

	UFUNCTION()
	void OnRep_PickupCount(int32 PreviousValue);

	bool	bReplicatedPickupCount = false;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UMP_HealthComponent> HealthComponent;

	// Remote Procedure Call (RPC) - Client, Server, and NetMulticast functions

	UFUNCTION(Client, Reliable)
	void Client_PrintMessage(const FString& Message);

	FTimerHandle RpcDelayTimer;
	void OnRpcDelayTimer();

	UFUNCTION(Server, Reliable)
	void Server_PrintMessage(const FString& Message);
};

