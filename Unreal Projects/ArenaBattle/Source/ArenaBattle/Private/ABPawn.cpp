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

		�𸮾� ������ ü�������� �ִϸ��̼� �ý����� �����ϵ��� ������ �ִϸ��̼� �ý����� �����ϴµ�, �̸� �ִϸ��̼� �������Ʈ��� �Ѵ�.
		���̷�Ż �޽� ������Ʈ�� �ڽ��� �����ϴ� ĳ������ �ִϸ��̼��� �� �ִ� �ν��Ͻ��� �����ϴ� ������ ����Ǿ� �ִ�.
		���̷�Ż �޽� ������Ʈ�� �� �ִϸ��̼� �������Ʈ�� Ŭ���� ������ ����ϸ�, ������Ʈ�� �ν��Ͻ��� ������ �ִϸ��̼��� �����ϵ��� �����Ѵ�.
		�׷��� �ּ��� ��ο� _C �� �߰��� �ٿ� Ŭ���� ������ �������� ��θ� �����ϰ�, �̸� ���̷�Ż �޽� ������Ʈ�� �ִϸ��̼� �������Ʈ Ŭ������ ����Ѵ�.
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

		�Ʒ��� ���� �ڵ�� �ִϸ��̼��� �����ϴ� ����� ������, ������ �Ը� Ŀ���� �̷� ������� �ִϸ��̼��� ����ϴ� ���� �������� �Ѱ迡 �ε�����.
		�׷��� �𸮾� ������ ü�������� �ִϸ��̼� �ý����� �����ϵ��� ������ �ִϸ��̼� �ý����� �����ϴµ�, �̸� �ִϸ��̼� �������Ʈ��� �Ѵ�.
	
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