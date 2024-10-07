// Copyright Epic Games, Inc. All Rights Reserved.

#include "PickupsCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "PickupsPlayerState.h"
#include "PickupsGameState.h"
#include "GameFramework/GameMode.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// APickupsCharacter

APickupsCharacter::APickupsCharacter()
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
}

void APickupsCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}

void APickupsCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APickupsPlayerState* MyPlayerState = GetPlayerState<APickupsPlayerState>();
	APickupsGameState* GameState = Cast<APickupsGameState>(GetWorld()->GetGameState());

	if (MyPlayerState != nullptr && GameState != nullptr)
	{
		//  Make sure that we add 1 to A and B only when it's authority, which in this case is the server, because the pawn was spawned in the server. This logic won't run on the clients. 
		if (HasAuthority())
		{
			MyPlayerState->IncreasePlayerStateTick();
			GameState->IncreaseGameStateTick();
		}

		if (Tickable)
		{
			const FString Values = FString::Printf(TEXT("MyPlayerStateTick = %d, GameStateTick = %d"), MyPlayerState->GetPlayerStateTick(), GameState->GetGameStateTick());
			DrawDebugString(GetWorld(), GetActorLocation(), Values, nullptr, FColor::White, 0.0f, true);
		}		
	}	
}

void APickupsCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (EndPlayReason == EEndPlayReason::Destroyed)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), FallSound);
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void APickupsCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APickupsCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APickupsCharacter::Look);

		// Replication Action
		EnhancedInputComponent->BindAction(AnyRepAction, ETriggerEvent::Triggered, this, &APickupsCharacter::ToggleTickable);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void APickupsCharacter::ToggleTickable(const FInputActionValue& Value)
{
	Tickable = !Tickable;
}

void APickupsCharacter::Move(const FInputActionValue& Value)
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

void APickupsCharacter::Look(const FInputActionValue& Value)
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

void APickupsCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	UGameplayStatics::PlaySound2D(GetWorld(), LandSound);
}

void APickupsCharacter::FellOutOfWorld(const UDamageType& DmgType)
{
	AController* TempController = Controller;

	AddScore(-10);

	Destroy();

	AGameMode* GameMode = GetWorld()->GetAuthGameMode<AGameMode>();

	if (GameMode != nullptr)
	{
		GameMode->RestartPlayer(TempController);
	}
}

void APickupsCharacter::AddScore(const float Score) const
{
	APlayerState* MyPlayerState = GetPlayerState();

	if (MyPlayerState != nullptr)
	{
		const float CurrentScore = MyPlayerState->GetScore();
		MyPlayerState->SetScore(CurrentScore + Score);
	}
}

void APickupsCharacter::AddPickup() const
{
	APickupsPlayerState* MyPlayerState = GetPlayerState<APickupsPlayerState>();

	if (MyPlayerState != nullptr)
	{
		MyPlayerState->AddPickup();
	}
}

void APickupsCharacter::ClientPlaySound2D_Implementation(USoundBase* Sound)
{
	UGameplayStatics::PlaySound2D(GetWorld(), Sound);
}
