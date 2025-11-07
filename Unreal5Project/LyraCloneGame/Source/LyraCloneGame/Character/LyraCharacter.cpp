// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/LyraCharacter.h"
#include "Camera/LyraCameraComponent.h"
#include "LyraPawnExtensionComponent.h"

// Sets default values
ALyraCharacter::ALyraCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// PawnExtComponent 持失
	PawnExtComponent = CreateDefaultSubobject<ULyraPawnExtensionComponent>(TEXT("PawnExtensionComponent"));

	// CameraComponent 持失
	{
		CameraComponent = CreateDefaultSubobject<ULyraCameraComponent>(TEXT("CameraComponent"));
		CameraComponent->SetRelativeLocation(FVector(-300.0f, 0.0f, 75.0f));
	}
}

// Called when the game starts or when spawned
void ALyraCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALyraCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ALyraCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

