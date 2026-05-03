// Copyright Epic Games, Inc. All Rights Reserved.

#include "MP_CppCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Net/UnrealNetwork.h"
#include "Components/MP_HealthComponent.h"
#include <Actors/MP_Actor.h>
#include <Kismet/GameplayStatics.h>
#include <Game/MP_GameState.h>
#include <Player/MP_PlayerState.h>

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AMP_CppCharacter

AMP_CppCharacter::AMP_CppCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
	HealthComponent = CreateDefaultSubobject<UMP_HealthComponent>(TEXT("HealthComponent"));
	HealthComponent->SetIsReplicated(true);
}

USkeletalMeshComponent* AMP_CppCharacter::GetPlayerMesh_Implementation()
{
	return GetMesh();
}

void AMP_CppCharacter::GrantArmor_Implementation(float ArmorAmount)
{
	Armor += ArmorAmount;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Granted %f armor. Current armor: %f"), ArmorAmount, Armor));
}

void AMP_CppCharacter::IncementPickupCount_Implementation()
{
	++PickupCount;
}

void AMP_CppCharacter::IncreaseHealth_Implementation(float HealthAmount)
{
	if (IsValid(HealthComponent))
	{
		float CurrentHealth = HealthComponent->GetHealth();
		HealthComponent->SetHealth(CurrentHealth + HealthAmount);
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AMP_CppCharacter::ServerTravelInput()
{
	if (HasAuthority())
	{
		GetWorld()->ServerTravel("DestinationMap");
	}
}

void AMP_CppCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AMP_CppCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMP_CppCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMP_CppCharacter::Look);

		// General input example
		EnhancedInputComponent->BindAction(GeneralAction, ETriggerEvent::Triggered, this, &AMP_CppCharacter::GeneralInput);

		// Spawn input example
		EnhancedInputComponent->BindAction(SpawnAction, ETriggerEvent::Triggered, this, &AMP_CppCharacter::SpawnInput);

		// Server Rpc input
		EnhancedInputComponent->BindAction(ServerRPCAction, ETriggerEvent::Triggered, this, &AMP_CppCharacter::ServerRpcInput);

		// Team input example
		EnhancedInputComponent->BindAction(TeamAction, ETriggerEvent::Triggered, this, &AMP_CppCharacter::TeamInput);

		// Pickup input example
		EnhancedInputComponent->BindAction(PickupAction, ETriggerEvent::Triggered, this, &AMP_CppCharacter::PickupInput);

		// Server Travel input example
		EnhancedInputComponent->BindAction(ServerTravelAction, ETriggerEvent::Triggered, this, &AMP_CppCharacter::ServerTravelInput);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AMP_CppCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(RpcDelayTimer, this, &AMP_CppCharacter::OnRpcDelayTimer, 3.f, false);
	GetWorldTimerManager().SetTimer(MultiCastDelayTimer, this, &AMP_CppCharacter::OnMultiCastDelayTimer, 6.f, false);
}

void AMP_CppCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	// 3. Call the DOREPLIFETIME macro for each replicated variable, specifying the class and variable name.
	//DOREPLIFETIME(ThisClass, Armor);
	DOREPLIFETIME_CONDITION(ThisClass, Armor, COND_InitialOnly);		// Condition 다양하게 바꿔가면서 테스트해보기
	//DOREPLIFETIME(ThisClass, PickupCount);
	DOREPLIFETIME_CONDITION(ThisClass, PickupCount, COND_Custom);
}

void AMP_CppCharacter::PreReplication(IRepChangedPropertyTracker& ChangedPropertyTracker)
{
	Super::PreReplication(ChangedPropertyTracker);

	// 4. Override PreReplication and use the SetCustomIsActiveOverride function to specify when the variable should be replicated.
	// In this example, PickupCount will only replicate when it's value is greater than 0.
	DOREPLIFETIME_ACTIVE_OVERRIDE(ThisClass, PickupCount, bReplicatedPickupCount);
}

void AMP_CppCharacter::OnRep_PickupCount(int32 PreviousValue)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Current pickup count: %d -> %d"), PreviousValue, PickupCount));
}

void AMP_CppCharacter::OnRpcDelayTimer()
{
	if (HasAuthority())
	{
		Client_PrintMessage(FString("This should run on the owning client"));
	}
}

void AMP_CppCharacter::OnMultiCastDelayTimer()
{
	Multicast_PrintMessage(FString("Print this on the server and all relevant clients"));
}

bool AMP_CppCharacter::Server_PrintMessage_Validate(const FString& Message)
{
	return !Message.IsEmpty();
}

void AMP_CppCharacter::Multicast_PrintMessage_Implementation(const FString& Message)
{
	FString	MessageString = HasAuthority() ? FString::Printf(TEXT("Server: %s"), *Message) : FString::Printf(TEXT("Client: %s"), *Message);

	GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Cyan, MessageString);
}

void AMP_CppCharacter::Server_PrintMessage_Implementation(const FString& Message)
{
	FString	MessageString = HasAuthority() ? FString::Printf(TEXT("Server: %s"), *Message) : FString::Printf(TEXT("Client: %s"), *Message);

	GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Purple, MessageString);
}

void AMP_CppCharacter::Client_PrintMessage_Implementation(const FString& Message)
{
	FString	MessageString = HasAuthority() ? FString::Printf(TEXT("Server: %s"), *Message) : FString::Printf(TEXT("Client: %s"), *Message);

	GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Yellow, MessageString);
}

void AMP_CppCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AMP_CppCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AMP_CppCharacter::GeneralInput(const FInputActionValue& Value)
{
	bReplicatedPickupCount = !bReplicatedPickupCount;		// This will toggle the replication of PickupCount, allowing us to test the replication condition

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Current armor: %f, bReplicatedPickupCount: %s"), Armor, bReplicatedPickupCount ? TEXT("true") : TEXT("false")));
}

void AMP_CppCharacter::SpawnInput(const FInputActionValue& Value)
{
	if(false == HasAuthority())
	{
		return;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this; //Cast<APlayerController>(GetController());

	// Example: Spawn an actor of class AMP_Actor at the character's location
	if (UWorld* World = GetWorld())
	{
		FVector SpawnLocation = GetActorLocation();
		FRotator SpawnRotation = GetActorRotation();
		AMP_Actor* NewActor = World->SpawnActor<AMP_Actor>(AMP_Actor::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);

		UE_LOG(LogTemplateCharacter, Log, TEXT("Owner name: %s, NetRole: %s, NetRemoteRole: %s"), *GetOwner()->GetName(), *UEnum::GetValueAsString(GetLocalRole()), *UEnum::GetValueAsString(GetRemoteRole()));

		//if (NewActor)
		//{
		//	NewActor->SetOwner(Cast<APlayerController>(GetController()));
		//}
	}
}

void AMP_CppCharacter::ServerRpcInput(const FInputActionValue& Value)
{
	//Server_PrintMessage("");	// kick off a server RPC by validation, Server_PrintMessage_Validate
	Server_PrintMessage("Please run this on the server");
}

void AMP_CppCharacter::TeamInput(const FInputActionValue& Value)
{
	AMP_GameState* MPGameState = Cast<AMP_GameState>(UGameplayStatics::GetGameState(this));
	APlayerController* PC = Cast<APlayerController>(GetController());

	if (IsValid(MPGameState) && IsValid(PC))
	{
		if (MPGameState->IsTeamOne(PC))
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Player is on Team One")));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Player is on Team Two")));
		}
	}
}

void AMP_CppCharacter::PickupInput(const FInputActionValue& Value)
{
	AMP_PlayerState* MPPlayerState = Cast<AMP_PlayerState>(GetPlayerState());
	if (!IsValid(MPPlayerState))
		return;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange,\
		FString::Printf(TEXT("%s pickup count : %d"), *MPPlayerState->GetPlayerName(), MPPlayerState->GetNumPickups()));
}
