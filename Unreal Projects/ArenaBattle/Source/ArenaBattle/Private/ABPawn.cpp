// Fill out your copyright notice in the Description page of Project Settings.

#include "ABPawn.h"


// Sets default values
AABPawn::AABPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CAPSULE"));
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESH"));
	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MOVEMENT"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	RootComponent = Capsule;
	Mesh->SetupAttachment(Capsule);
	SpringArm->SetupAttachment(Capsule);
	Camera->SetupAttachment(SpringArm);

	Capsule->SetCapsuleHalfHeight(88.0f);
	Capsule->SetCapsuleRadius(34.0f);
	Mesh->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_CARDBOARD(TEXT("/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard"));

	if (SK_CARDBOARD.Succeeded())
	{
		Mesh->SetSkeletalMesh(SK_CARDBOARD.Object);
	}

	/*
		chapter 5

		언리얼 엔진은 체계적으로 애니메이션 시스템을 설계하도록 별도의 애니메이션 시스템을 제공하는데, 이를 애니메이션 블루프린트라고 한다.
		스켈레탈 메시 컴포넌트는 자신이 관리하는 캐릭터의 애니메이션을 이 애님 인스턴스에 위임하는 구조로 설계되어 있다.
		스켈레탈 메시 컴포넌트에 이 애니메이션 블루프린트의 클래스 정보를 등록하면, 컴포넌트는 인스턴스를 생성해 애니메이션을 관리하도록 동작한다.
		그래서 애셋의 경로에 _C 를 추가로 붙여 클래스 정보를 가져오는 경로를 생성하고, 이를 스켈레탈 메시 컴포넌트의 애니메이션 블루프린트 클래스에 등록한다.
	*/
	Mesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	
	static ConstructorHelpers::FClassFinder<UAnimInstance> WARRIOR_ANIM(TEXT("/Game/Animations/WarriorAnimBlueprint.WarriorAnimBlueprint_C"));

	if (WARRIOR_ANIM.Succeeded())
	{
		Mesh->SetAnimInstanceClass(WARRIOR_ANIM.Class);
	}
}

// Called when the game starts or when spawned
void AABPawn::BeginPlay()
{
	Super::BeginPlay();

	/*
		chapter 5

		아래와 같이 코드로 애니메이션을 지정하는 방법도 있지만, 게임의 규모가 커지면 이런 방법으로 애니메이션을 재생하는 것은 관리적인 한계에 부딪힌다.
		그래서 언리얼 엔진은 체계적으로 애니메이션 시스템을 설계하도록 별도의 애니메이션 시스템을 제공하는데, 이를 애니메이션 블루프린트라고 한다.
	
	Mesh->SetAnimationMode(EAnimationMode::AnimationSingleNode);
	UAnimationAsset* AnimAsset = LoadObject<UAnimationAsset>(nullptr, TEXT("/Game/Animations/WarriorRun.WarriorRun"));

	if (nullptr != AnimAsset)
	{
		Mesh->PlayAnimation(AnimAsset, true);
	}
	*/	
}

// Called every frame
void AABPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AABPawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ABLOG_S(Warning);
}

void AABPawn::PossessedBy(AController* NewController)
{
	ABLOG_S(Warning);
	Super::PossessedBy(NewController);
}

// Called to bind functionality to input
void AABPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AABPawn::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AABPawn::LeftRight);}

void AABPawn::UpDown(float NewAxisValue)
{
	AddMovementInput(GetActorForwardVector(), NewAxisValue);
}

void AABPawn::LeftRight(float NewAxisValue)
{
	AddMovementInput(GetActorRightVector(), NewAxisValue);
}