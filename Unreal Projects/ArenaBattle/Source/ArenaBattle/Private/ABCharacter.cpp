// Fill out your copyright notice in the Description page of Project Settings.

#include "ABCharacter.h"
#include "ABAnimInstance.h"
#include "ABWeapon.h"
#include "ABCharacterStatComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/WidgetComponent.h"
#include "ABCharacterWidget.h"
#include "ABAIController.h"
#include "ABCharacterSetting.h"
#include "ABGameInstance.h"
//#include "Engine/AssetManager.h"
#include "ABPlayerController.h"
#include "ABPlayerState.h"
#include "ABHUDWidget.h"
#include "ABGameMode.h"
#include "VisualLogger/VisualLogger.h"

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
	AttackRange = 80.0f;
	AttackRadius = 50.0f;

	HPBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));
	HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);	// UI ������ �׻� �÷��̾ ���� ������ Screen ���� �����Ѵ�.
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HUD(TEXT("/Game/Book/UI/UI_HPBar.UI_HPBar_C"));
	if (UI_HUD.Succeeded())
	{
		HPBarWidget->SetWidgetClass(UI_HUD.Class);
		HPBarWidget->SetDrawSize(FVector2D(150.0f, 50.0f));
	}

	AIControllerClass = AABAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	AssetIndex = 4;

	SetActorHiddenInGame(true);
	HPBarWidget->SetHiddenInGame(true);
	bCanBeDamaged = false;

	DeadTimer = 5.0f;
}

float ABCharacter::GetFinalAttackRange() const
{
	return (nullptr != CurrentWeapon) ? CurrentWeapon->GetAttackRange() : AttackRange;
}

float ABCharacter::GetFinalAttackDamage() const
{
	float AttackDamage = (nullptr != CurrentWeapon) ? (CharacterStat->GetAttack() + CurrentWeapon->GetAttackDamage()) : CharacterStat->GetAttack();
	float AttackModifier = (nullptr != CurrentWeapon) ? CurrentWeapon->GetAttackModifier() : 1.0f;
	return AttackDamage * AttackModifier;
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
	chapter 1~13 
	--
		chapter 11

		ó���� �Ʒ� ����ڵ� ó���� �ȵǾ� �־ ũ���ð� ���ٰ� �����ߴµ�,
		������ ��ġ�� ABCharacter �� �����ٰ� �ٽ� �����ϴ� ũ���ð� �ȳ���.
		�𸮾� hot reload ���� �����ΰ� ����.
	--
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
	*/
}

/*
	chapter 14

	Called when the game starts or when spawned

	ĳ���ʹ� �ڽ��� ���ΰ����� NPC ������ �Ǻ��� �� �־�� �ϴµ�, �̸� Ȯ���� �ľ��� �� �ִ� ������ BeginPlay �̴�.
	���� ������ �÷��̾ ���� AI ��Ʈ�ѷ��� �ڵ����� �����ǹǷ� PossessedBy �Լ��� �� �� ȣ��Ǳ� �����̴�.

	���� �÷��̾ �����̴� ��/AI �� �����̴� �� �̷��� ��������� �� ������ ������ �����ڳ� Possess ���� �Ǻ��ص� ������,
	�밳 �׷��� �ʱ� ������ BeginPlay �� �������� ��� �� ����.

*/
void ABCharacter::BeginPlay()
{
	Super::BeginPlay();

	bIsPlayer = IsPlayerControlled();
	if (bIsPlayer)
	{
		ABPlayerController = Cast<AABPlayerController>(GetController());
		ABCHECK(nullptr != ABPlayerController);
	}
	else
	{
		ABAIController = Cast<AABAIController>(GetController());
		ABCHECK(nullptr != ABAIController);
	}

	auto DefaultSetting = GetDefault<UABCharacterSetting>();

	if (bIsPlayer)
	{
		auto ABPlayerState = Cast<AABPlayerState>(PlayerState);
		ABCHECK(nullptr != ABPlayerState);
		AssetIndex = ABPlayerState->GetCharacterIndex();
	}
	else
	{
		AssetIndex = FMath::RandRange(0, DefaultSetting->CharacterAssets.Num() - 1);
	}

	CharacterAssetToLoad = DefaultSetting->CharacterAssets[AssetIndex];
	auto ABGameInstance = Cast<UABGameInstance>(GetGameInstance());
	ABCHECK(nullptr != ABGameInstance);
	AssetStreamingHandle = ABGameInstance->StreamableManager.RequestAsyncLoad(CharacterAssetToLoad, FStreamableDelegate::CreateUObject(this, &ABCharacter::OnAssetLoadCompleted));
	SetCharacterState(ECharacterState::LOADING);

	/*
		chapter 1~13

	if (!IsPlayerControlled())
	{
		auto DefaultSetting = GetDefault<UABCharacterSetting>();
		int32 RandIndex = FMath::RandRange(0, DefaultSetting->CharacterAssets.Num() - 1);
		CharacterAssetToLoad = DefaultSetting->CharacterAssets[RandIndex];

		auto ABGameInstance = Cast<UABGameInstance>(GetGameInstance());
		if (nullptr != ABGameInstance)
		{
			// FStreamableDelegate �������� ��������Ʈ ����� �����ϰ� �Ѱ��� ���� ������,
			// ��������Ʈ���� �����ϴ� CreateUObject ����� ����� �Ｎ���� ��������Ʈ�� ���������ν� �Լ��� ������Ų �� �Ѱ��ִ� ����� �����Ѵ�.
			AssetStreamingHandle = ABGameInstance->StreamableManager.RequestAsyncLoad(CharacterAssetToLoad, FStreamableDelegate::CreateUObject(this, &ABCharacter::OnAssetLoadCompleted));
						
			--
				chapter 13

				�������� ����ϴ� StreamableManager �� ��� ���� ��� ���� �����ϴ� UAssetManager ��� ������Ʈ�� �̹� ����Ǿ� �ִ�.
				Engine/AssetManager.h ��� ������ ������ ��, UAssetManager::GetStreamableManager() �Լ��� ��� ����ص� �����ϴ�.

				AssetStreamingHandle = UAssetManager::GetStreamableManager().RequestAsyncLoad(CharacterAssetToLoad, FStreamableDelegate::CreateUObject(this, &AABCharacter::OnAssetLoadCompleted));
			--			
		}
	}

	FName WeaponSocket(TEXT("hand_rSocket"));
	
	auto CurWeapon = GetWorld()->SpawnActor<AABWeapon>(FVector::ZeroVector, FRotator::ZeroRotator);
	if (nullptr != CurWeapon)
	{
		CurWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
	}
	*/	
}

void ABCharacter::SetCharacterState(ECharacterState NewState)
{
	ABCHECK(CurrentState != NewState);
	CurrentState = NewState;

	switch (CurrentState)
	{
		case ECharacterState::LOADING:
		{
			if (bIsPlayer)
			{
				DisableInput(ABPlayerController);
				ABPlayerController->GetHUDWidget()->BindCharacterStat(CharacterStat);
				auto ABPlayerState = Cast<AABPlayerState>(PlayerState);
				ABCHECK(nullptr != ABPlayerState);
				CharacterStat->SetNewLevel(ABPlayerState->GetCharacterLevel());
			}
			else
			{
				auto ABGameMode = Cast<AABGameMode>(GetWorld()->GetAuthGameMode());
				ABCHECK(nullptr != ABGameMode);
				int32 TargetLevel = FMath::CeilToInt(((float)ABGameMode->GetScore() * 0.8f));
				int32 FinalLevel = FMath::Clamp<int32>(TargetLevel, 1, 20);
				ABLOG(Warning, TEXT("New NPC Level : %d"), FinalLevel);
				CharacterStat->SetNewLevel(FinalLevel);
			}

			SetActorHiddenInGame(true);
			HPBarWidget->SetHiddenInGame(true);
			bCanBeDamaged = false;
			break;
		}
		case ECharacterState::READY:
		{
			SetActorHiddenInGame(false);
			HPBarWidget->SetHiddenInGame(false);
			bCanBeDamaged = true;

			CharacterStat->OnHPIsZero.AddLambda([this]() -> void {
				SetCharacterState(ECharacterState::DEAD);
			});

			auto CharacterWidget = Cast<UABCharacterWidget>(HPBarWidget->GetUserWidgetObject());
			ABCHECK(nullptr != CharacterWidget);
			CharacterWidget->BindCharacterStat(CharacterStat);

			if (bIsPlayer)
			{
				SetControlMode(EControlMode::DIABLO);
				GetCharacterMovement()->MaxWalkSpeed = 600.0f;
				EnableInput(ABPlayerController);
			}
			else
			{
				SetControlMode(EControlMode::NPC);
				GetCharacterMovement()->MaxWalkSpeed = 400.0f;
				ABAIController->RunAI();
			}

			break;
		}
		case ECharacterState::DEAD:
		{
			SetActorEnableCollision(false);
			GetMesh()->SetHiddenInGame(false);
			HPBarWidget->SetHiddenInGame(true);
			ABAnim->SetDeadAnim();
			bCanBeDamaged = false;

			if (bIsPlayer)
			{
				DisableInput(ABPlayerController);
			}
			else
			{
				ABAIController->StopAI();
			}

			GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda([this]() -> void {
				if (bIsPlayer)
				{
					ABPlayerController->ShowResultUI();
				}
				else
				{
					Destroy();
				}

			}), DeadTimer, false);

			break;
		}
	}
}

ECharacterState ABCharacter::GetCharacterState() const
{
	return CurrentState;
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
	case EControlMode::NPC:
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bUseControllerDesiredRotation = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 480.0f, 0.0f);
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
	OnAttackEnd.Broadcast();
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
	float FinalAttackRange = GetFinalAttackRange();

	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * FinalAttackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(AttackRadius),
		Params);

#if ENABLE_DRAW_DEBUG

	FVector TraceVec = GetActorForwardVector() * FinalAttackRange;
	FVector Center = GetActorLocation() + TraceVec * 0.5f;
	float HalfHeight = FinalAttackRange * 0.5f + AttackRadius;
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

	UE_VLOG_LOCATION(this, ArenaBattle, Verbose, GetActorLocation(), 50.0f, FColor::Blue, TEXT("Attack Position"));
	UE_VLOG_CAPSULE(this, ArenaBattle, Verbose, GetActorLocation() - GetActorForwardVector() * AttackRadius, HalfHeight, AttackRadius, CapsuleRot, DrawColor, TEXT("Attack Area"));

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
			HitResult.Actor->TakeDamage(GetFinalAttackDamage(), DamageEvent, GetController(), this);
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

	CharacterStat->SetDamage(FinalDamage);
	if (CurrentState == ECharacterState::DEAD)
	{
		if (EventInstigator->IsPlayerController())
		{
			auto ABPlayerController = Cast<AABPlayerController>(EventInstigator);
			ABCHECK(nullptr != ABPlayerController, 0.0f);
			ABPlayerController->NPCKill(this);
		}
	}
	ABLOG(Warning, TEXT("Actor : %s took Damage : %f"), *GetName(), FinalDamage);

	return FinalDamage;
}

bool ABCharacter::CanSetWeapon()
{
	//return (nullptr == CurrentWeapon);
	return true;
}

void ABCharacter::SetWeapon(AABWeapon * NewWeapon)
{
	ABCHECK(nullptr != NewWeapon);

	if (nullptr != NewWeapon)
	{
		if (CurrentWeapon)
		{
			CurrentWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			CurrentWeapon->Destroy();
			CurrentWeapon = nullptr;
		}		
	}

	ABCHECK(nullptr != NewWeapon && nullptr == CurrentWeapon);
	FName WeaponSocket(TEXT("hand_rSocket"));
	if (nullptr != NewWeapon)
	{
		NewWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
		NewWeapon->SetOwner(this);
		CurrentWeapon = NewWeapon;
	}
}

/*
	chapter 14

	�÷��̾ ������ �� �߻��ϴ� ĳ������ PossessBy �Լ��� �����ϰ� ��� ĳ������ READY ������Ʈ���� �̸� �����Ѵ�.

void ABCharacter::PossessedBy(AController * NewController)
{
	Super::PossessedBy(NewController);

	if (IsPlayerControlled())
	{
		SetControlMode(EControlMode::DIABLO);
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	}
	else
	{
		SetControlMode(EControlMode::NPC);
		GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	}
}
*/

void ABCharacter::OnAssetLoadCompleted()
{
	AssetStreamingHandle->ReleaseHandle();
	TSoftObjectPtr<USkeletalMesh> LoadedAssetPath(CharacterAssetToLoad);
	ABCHECK(LoadedAssetPath.IsValid());
	
	GetMesh()->SetSkeletalMesh(LoadedAssetPath.Get());
	SetCharacterState(ECharacterState::READY);	
}

int32 ABCharacter::GetExp() const
{
	return CharacterStat->GetDropExp();
}