// Fill out your copyright notice in the Description page of Project Settings.

#include "BMCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ABMCharacter::ABMCharacter()
{
	// 이 캐릭터가 Tick()을 매 프레임마다 부르도록 한다. 필요없다면 성능 향상을 위해 끌 수도 있다.
	PrimaryActorTick.bCanEverTick = true;

	// 콜리전 캡슐 크기 조절
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	// 캐릭터 회전 속도 조절
	BaseTurnRate = 45.0f;
	BaseLookUpRate = 45.0f;

	// CameraComponent 생성 
	FPCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	//FPCameraComponent->AttachParent = GetCapsuleComponent();	// deprecated
	FPCameraComponent->SetupAttachment(GetCapsuleComponent());	// SetupAttachment 는 AttachTo 와 달리 초기화에만사용해야 한다는 제약이 있다.

	// 카메라 위치 조절
	FPCameraComponent->RelativeLocation = FVector(0, 0, 64.f);
	FPCameraComponent->bUsePawnControlRotation = true;

	// 조종하는 폰에서만 볼 수 있는 메시 생성
	FPMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));

	FPMesh->SetOnlyOwnerSee(true);
	//FPMesh->AttachParent = FPCameraComponent;
	FPMesh->AttachTo(FPCameraComponent);
	FPMesh->bCastDynamicShadow = false;
	FPMesh->CastShadow = false;
	
	FPGunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FPGunMesh->SetOnlyOwnerSee(true);// 소유중인 플레이어만 메시를 볼 것이다
	FPGunMesh->bCastDynamicShadow = false;	// 벽에서 두 팔만 있는 그림자를 보고 싶지 않다면 그림자 끌 것.
	FPGunMesh->CastShadow = false;
	FPGunMesh->AttachTo(FPMesh, TEXT("GripPoint"), EAttachLocation::SnapToTargetIncludingScale, true);	// 이름에 해당하는 소켓이 없다면 (0,0,0) 에 부착

	ProjSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawn"));
	ProjSpawn->AttachTo(FPGunMesh);
}

// Called when the game starts or when spawned
void ABMCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABMCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABMCharacter::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	check(InputComponent);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	InputComponent->BindAxis("MoveForward", this, &ABMCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ABMCharacter::MoveRight);

	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &ABMCharacter::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &ABMCharacter::LookUpAtRate);
	
	InputComponent->BindAction("Fire", IE_Pressed, this, &ABMCharacter::OnFire);

	InputComponent->BindAction("Track", IE_Pressed, this, &ABMCharacter::OnTrack);
} // <-- SetupPlayerInputComponent() 닫기

void ABMCharacter::MoveForward(float Val)
{
	if (Val != 0.0f) {
		// 해당 위치로 이동 추가
		AddMovementInput(GetActorForwardVector(), Val);
	}
}

void ABMCharacter::MoveRight(float Val)
{
	if (Val != 0.0f)
	{
		// 해당 위치로 이동 추가
		AddMovementInput(GetActorRightVector(), Val);
	}
}

void ABMCharacter::TurnAtRate(float Rate)
{
	// 속도 정보에서 이 프레임의 델타를 계산한다.
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ABMCharacter::LookUpAtRate(float Rate)
{
	// 속도 정보에서 이 프레임의 델타를 계산한다.
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ABMCharacter::OnFire()
{
	// 발사체 발사 시도
	if (ProjectileClass != nullptr)
	{
		if (GetWorld() != nullptr)
		{
			ABMProjectile* ThisProjectile = GetWorld()->SpawnActor<ABMProjectile>(ProjectileClass, ProjSpawn->GetComponentLocation(), GetControlRotation());
			ThisProjectile->GetProjectileMovement()->HomingTargetComponent = TrackingSceneComponent;
		}
	}
}

void ABMCharacter::OnTrack()
{
	FVector MousePos;
	FVector MouseDir;
	FHitResult Hit;
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_GameTraceChannel2);
	APlayerController* playerController = Cast<APlayerController>(GetController());
	
	if (GEngine->GameViewport != nullptr && playerController != nullptr)
	{
		FVector2D ScreenPos = GEngine->GameViewport->Viewport->GetSizeXY();
		playerController->DeprojectScreenPositionToWorld(ScreenPos.X / 2.0f, ScreenPos.Y / 2.0f, MousePos, MouseDir);
		MouseDir *= 100000.0f;

		GetWorld()->LineTraceSingleByObjectType(Hit, MousePos, MouseDir, ObjectQueryParams);

		if (Hit.bBlockingHit)
		{
			UE_LOG(LogTemp, Warning, TEXT("TRACE HIT WITH %s"), *(Hit.GetActor()->GetName()));
			TrackingSceneComponent = Cast<USceneComponent>(Hit.GetActor()->GetComponentByClass(USceneComponent::StaticClass()));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No Trace"));
			TrackingSceneComponent = nullptr;
		}
	}// <--If(GEngine->GameViewport != nullptr...) 닫기
}// <--OnTrack() 닫기