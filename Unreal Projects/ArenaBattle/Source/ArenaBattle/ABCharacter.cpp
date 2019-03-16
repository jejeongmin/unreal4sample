// Fill out your copyright notice in the Description page of Project Settings.

#include "ABCharacter.h"
#include "ABAnimInstance.h"
#include "ABWeapon.h"
#include "ABCharacterStatComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/WidgetComponent.h"
#include "ABCharacterWidget.h"

// Sets default values
ABCharacter::ABCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	CharacterStat = CreateDefaultSubobject<UABCharacterStatComponent>(TEXT("CHARACTERSTAT"));
	HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBARWIDGET"));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);
	HPBarWidget->SetupAttachment(GetMesh());

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_CARDBOARD(TEXT("/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard"));

	if (SK_CARDBOARD.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_CARDBOARD.Object);
	}

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> WARRIOR_ANIM(TEXT("/Game/Animations/WarriorAnimBlueprint.WarriorAnimBlueprint_C"));

	if (WARRIOR_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(WARRIOR_ANIM.Class);
	}

	SetControlMode(EControlMode::DIABLO);

	ArmLengthSpeed = 3.0f;
	ArmRotationSpeed = 10.0f;
	GetCharacterMovement()->JumpZVelocity = 800.0f;	// �� �� ���� �ۼ� �ֵ��� �⺻��(420.0f)���� ���� ����

	IsAttacking = false;
	MaxCombo = 4;
	AttackEndComboState();

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("ABCharacter"));
	AttackRange = 200.0f;
	AttackRadius = 50.0f;

	HPBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));
	HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);	// UI ������ �׻� �÷��̾ ���� ������ Screen ���� �����Ѵ�.
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HUD(TEXT("/Game/Book/UI/UI_HPBar.UI_HPBar_C"));
	if (UI_HUD.Succeeded())
	{
		HPBarWidget->SetWidgetClass(UI_HUD.Class);
		HPBarWidget->SetDrawSize(FVector2D(150.0f, 50.0f));
	}
}

void ABCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ABAnim = Cast<UABAnimInstance>(GetMesh()->GetAnimInstance());
	ABCHECK(nullptr != ABAnim);

	/*
		chapter 8

		�ִ� �ν��Ͻ����� �ִϸ��̼� ��Ÿ�� ����� ������ �ߵ��ϴ� OnMontageEnded ��� ��������Ʈ�� �����Ѵ�.

		�Ʒ��� ���� ���� ��������Ʈ�� ���ÿ� ���ε��ϰ� �ൿ�� ������ ��ϵ� �Լ��� ��� �˷��ִ� ��������Ʈ�� Multicast Delegate ��� �Ѵ�.
	*/
	ABAnim->OnMontageEnded.AddDynamic(this, &ABCharacter::OnAttackMontageEnded);

	ABAnim->OnNextAttackCheck.AddLambda([this]() -> void {

		ABLOG(Warning, TEXT("OnNextAttackCheck"));
		CanNextCombo = false;

		if (IsComboInputOn)
		{
			AttackStartComboState();
			ABAnim->JumpToAttackMontageSection(CurrentCombo);
		}
	});

	ABAnim->OnAttackHitCheck.AddUObject(this, &ABCharacter::AttackCheck);

	/*
		chapter 11

		ó���� �Ʒ� ����ڵ� ó���� �ȵǾ� �־ ũ���ð� ���ٰ� �����ߴµ�,
		������ ��ġ�� ABCharacter �� �����ٰ� �ٽ� �����ϴ� ũ���ð� �ȳ���.
		�𸮾� hot reload ���� �����ΰ� ����.
	*/
	//if (nullptr != CharacterStat)
	{
		CharacterStat->OnHPIsZero.AddLambda([this]() -> void {
			ABLOG(Warning, TEXT("OnHPIsZero"));
			ABAnim->SetDeadAnim();
			SetActorEnableCollision(false);
		});
	}

	// ĳ���� ������Ʈ�� ������ ����
	auto CharacterWidget = Cast<UABCharacterWidget>(HPBarWidget->GetUserWidgetObject());
	if (nullptr != CharacterWidget)
	{
		CharacterWidget->BindCharacterStat(CharacterStat);
	}
}

// Called when the game starts or when spawned
void ABCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	FName WeaponSocket(TEXT("hand_rSocket"));
	
	auto CurWeapon = GetWorld()->SpawnActor<AABWeapon>(FVector::ZeroVector, FRotator::ZeroRotator);
	if (nullptr != CurWeapon)
	{
		CurWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
	}
}

// Called every frame
void ABCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ī�޶� �̵� tick
	SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, ArmLengthTo, DeltaTime, ArmLengthSpeed);
	switch (CurrentControlMode)
	{
	case EControlMode::DIABLO:
		SpringArm->RelativeRotation = FMath::RInterpTo(SpringArm->RelativeRotation, ArmRotationTo, DeltaTime, ArmRotationSpeed);
		break;
	}

	// ĳ���� �̵� tick
	switch (CurrentControlMode)
	{
	case EControlMode::DIABLO:
		if (DirectionToMove.SizeSquared() > 0.0f)
		{
			/*
				chapter 6

				�𸮾� ������ FRotationMatrix �� ȸ���� ��ǥ�� ������ �����ϴ� ����̴�.
				�ռ� ���캻 GTA ��Ŀ����� FRotator ������ ȸ�� ����� �����ϰ�, �̸� ���� ��ȯ�� X, Y �� ������ �����Դ�.
				�̹� ��ƺ�� ��Ŀ����� �Ųٷ� �ϳ��� ���� ���� �̿� �����ϴ� ������ �� ���� ���� ȸ�� ����� �����ϰ�,
				�̿� ��ġ�ϴ� FRotator ���� ������ ����� ����ߴ�. �ϳ��� ���ͷκ��� ȸ�� ����� �����ϴ� ����� MakeFromX, Y, Z �� �ִµ�,
				�� ���� �Է��� �ջ��� ���� ���� ����� ĳ������ �ü� ����(X��)�� ��ġ�ؾ� �ϹǷ� �� �߿��� MakeFromX �� ���ƴ�.
			*/
			GetController()->SetControlRotation(FRotationMatrix::MakeFromX(DirectionToMove).Rotator());
			AddMovementInput(DirectionToMove);
		}
		break;
	}

	/*
		chapter 7

		pawn �� tick ���� anim instance �� speed �� write ���ִ� ����� ������, �ǰ����� �ʴ� ����̴�.

		#include "ABAnimInstance.h"

		auto ABAnimInstace = Cast<UABAnimInstance>(GetMesh()->GetAnimInstance());
		if(nullptr != ABAnimInstance)
		{
			ABAnimInstance->SetPawnSpeed(GetVelocity().Size());
		}
	*/
}

// Called to bind functionality to input
void ABCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("ViewChange"), EInputEvent::IE_Pressed, this, &ABCharacter::ViewChange);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &ABCharacter::Attack);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &ABCharacter::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &ABCharacter::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ABCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ABCharacter::LookUp);
}

void ABCharacter::UpDown(float NewAxisValue)
{
	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		//AddMovementInput(GetActorForwardVector(), NewAxisValue);
		// ī�޶�(���⼭�� ī�޶� �޸� ��������) �������� ĳ���� ������ ������ ���Ѵ�
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), NewAxisValue);
		break;
	case EControlMode::DIABLO:
		DirectionToMove.X = NewAxisValue;
		break;
	}
	
}

void ABCharacter::LeftRight(float NewAxisValue)
{
	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		//AddMovementInput(GetActorRightVector(), NewAxisValue);
		// ī�޶�(���⼭�� ī�޶� �޸� ��������) �������� ĳ���� ������ ������ ���Ѵ�
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), NewAxisValue);
		break;
	case EControlMode::DIABLO:
		DirectionToMove.Y = NewAxisValue;
		break;
	}
}

void ABCharacter::LookUp(float NewAxisValue)
{
	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		AddControllerPitchInput(NewAxisValue);
		break;
	}
}

void ABCharacter::Turn(float NewAxisValue)
{
	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		AddControllerYawInput(NewAxisValue);
		break;
	}
}

void ABCharacter::SetControlMode(EControlMode NewControlMode)
{
	CurrentControlMode = NewControlMode;

	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		//SpringArm->TargetArmLength = 450.0f;
		//SpringArm->SetRelativeRotation(FRotator::ZeroRotator);
		ArmLengthTo = 450.0f;
		SpringArm->bUsePawnControlRotation = true;
		SpringArm->bInheritPitch = true;
		SpringArm->bInheritRoll = true;
		SpringArm->bInheritYaw = true;
		SpringArm->bDoCollisionTest = true;
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->bUseControllerDesiredRotation = false;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
		break;
	case EControlMode::DIABLO:
		//SpringArm->TargetArmLength = 800.0f;
		//SpringArm->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
		ArmLengthTo = 800.0f;
		ArmRotationTo = FRotator(-45.0f, 0.0f, 0.0f);
		SpringArm->bUsePawnControlRotation = false;
		SpringArm->bInheritPitch = false;
		SpringArm->bInheritRoll = false;
		SpringArm->bInheritYaw = false;
		SpringArm->bDoCollisionTest = false;
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = false;
		// bUseControllerDesiredRotation �� üũ�ϸ� 45�� ������  �Ҷ� ���� ȸ���ϴ� ���� �ε巴�� ȸ���Ѵ�.
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
		break;
	}
}

void ABCharacter::ViewChange()
{
	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		GetController()->SetControlRotation(GetActorRotation());
		SetControlMode(EControlMode::DIABLO);
		break;
	case EControlMode::DIABLO:
		GetController()->SetControlRotation(SpringArm->RelativeRotation);
		SetControlMode(EControlMode::GTA);
		break;
	}
}

void ABCharacter::Attack()
{
	if (IsAttacking)
	{
		ABCHECK(FMath::IsWithinInclusive<int32>(CurrentCombo, 1, MaxCombo));
		if (CanNextCombo)
		{
			IsComboInputOn = true;
		}
	}
	else
	{
		ABCHECK(CurrentCombo == 0);
		AttackStartComboState();
		ABAnim->PlayAttackMontage();
		ABAnim->JumpToAttackMontageSection(CurrentCombo);
		IsAttacking = true;
	}
}

void ABCharacter::OnAttackMontageEnded(UAnimMontage * Montage, bool bInterrupted)
{
	ABCHECK(IsAttacking);
	ABCHECK(CurrentCombo > 0);
	IsAttacking = false;
	AttackEndComboState();
}

void ABCharacter::AttackStartComboState()
{
	CanNextCombo = true;
	IsComboInputOn = false;
	ABCHECK(FMath::IsWithinInclusive<int32>(CurrentCombo, 0, MaxCombo - 1));
	CurrentCombo = FMath::Clamp<int32>(CurrentCombo + 1, 1, MaxCombo);
}

void ABCharacter::AttackEndComboState()
{
	IsComboInputOn = false;
	CanNextCombo = false;
	CurrentCombo = 0;
}

void ABCharacter::AttackCheck()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * AttackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(AttackRadius),
		Params);

#if ENABLE_DRAW_DEBUG

	FVector TraceVec = GetActorForwardVector() * AttackRange;
	FVector Center = GetActorLocation() + TraceVec * 0.5f;
	float HalfHeight = AttackRange * 0.5f + AttackRadius;
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	float DebugLifeTime = 5.0f;

	DrawDebugCapsule(GetWorld(),
		Center,
		HalfHeight,
		AttackRadius,
		CapsuleRot,
		DrawColor,
		false,
		DebugLifeTime);

#endif

	if (bResult)
	{
		/*
			chapter 9

			�𸮾� ���� ȯ���� �޸𸮿� ���ִ� �𸮾� ������Ʈ�� ��� ������ �ƴ����� �ֱ������� �˻��ϰ�, ������� �ʴ� ��ü�� �߰��ϸ� �޸𸮿��� �ڵ����� �����Ѵ�.
			�̸� GC ��� �Ѵ�. �𸮾� ������Ʈ�� ��������� ���δ� �ٸ� �𸮾� ������Ʈ�� �ش� ������Ʈ�� �����ϴ����� �Ǵ��ϴµ�,
			FHitResult �� �⺭ ���� Actor �� ������ �Ϲ� ������ ����ȴٸ� �ش� �Լ������� ������ ���� �����ؾ� �� ���Ͱ� �޸𸮿� �״�� �����ִ� ������ �߻��� �� �ִ�.
			�̷� ������ �����ϱ� ���� FHitResult �� �����κ��� �����Ӱ� ������ ������ �������ִ� TWeakObjectPtr ������� ��� ������ �����ߴ�.
			�� �����ͷ� ������ ���Ϳ� �����Ϸ��� IsValid �Լ��� ����� ����Ϸ��� ���Ͱ� ��ȿ���� ���� �����ϰ� ����ؾ� �Ѵ�.
		*/
		if (HitResult.Actor.IsValid())
		{
			ABLOG(Warning, TEXT("Hit Actor Name : %s"), *HitResult.Actor->GetName());

			FDamageEvent DamageEvent;
			HitResult.Actor->TakeDamage(CharacterStat->GetAttack(), DamageEvent, GetController(), this);
		}
	}
}

/*
	chapter 9

	�𸮾� ������ Actor Ŭ������ TakeDamage ��� �Լ��� �����Ǿ� �ִ�.
	�� �Լ��� ����ϸ� �ս��� ���Ϳ� ������� ������ �� �ִ�.

	DamageAmount : ������ ������� ����
	DamageEvent : ����� ����
	EventInstigator : ���� ����� ���� ������, �����ڴ� ���� �ƴ϶� ������ ����� ���� �÷��̾� ��Ʈ�ѷ���� �� �� �ִ�.
	DamageCauser : ����� ������ ���� ����� ����, �� ��� �츮�� ������ ���� �÷��̾ ����� ������ ���� ����� ������� �ؼ��� �� �ִ�.
*/
float ABCharacter::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	ABLOG(Warning, TEXT("Actor : %s took Damage : %f"), *GetName(), FinalDamage);

	CharacterStat->SetDamage(FinalDamage);
	return FinalDamage;
}

bool ABCharacter::CanSetWeapon()
{
	return (nullptr == CurrentWeapon);
}

void ABCharacter::SetWeapon(AABWeapon * NewWeapon)
{
	ABCHECK(nullptr != NewWeapon && nullptr == CurrentWeapon);
	FName WeaponSocket(TEXT("hand_rSocket"));
	if (nullptr != NewWeapon)
	{
		NewWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
		NewWeapon->SetOwner(this);
		CurrentWeapon = NewWeapon;
	}
}