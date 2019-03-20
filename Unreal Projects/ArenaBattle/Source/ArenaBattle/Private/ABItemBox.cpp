// Fill out your copyright notice in the Description page of Project Settings.

#include "ABItemBox.h"
#include "ABWeapon.h"
#include "ABCharacter.h"


// Sets default values
AABItemBox::AABItemBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BOX"));
	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EFFECT"));

	RootComponent = Trigger;
	Box->SetupAttachment(RootComponent);
	Effect->SetupAttachment(RootComponent);

	Trigger->SetBoxExtent(FVector(40.0f, 42.0f, 30.0f));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_BOX(TEXT("/Game/InfinityBladeGrassLands/Environments/Breakables/StaticMesh/Box/SM_Env_Breakables_Box1.SM_Env_Breakables_Box1"));

	if (SM_BOX.Succeeded())
	{
		Box->SetStaticMesh(SM_BOX.Object);
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> P_CHESTOPEN(TEXT("/Game/InfinityBladeGrassLands/Effects/FX_Treasure/Chest/P_TreasureChest_Open_Mesh.P_TreasureChest_Open_Mesh"));

	if (P_CHESTOPEN.Succeeded())
	{
		Effect->SetTemplate(P_CHESTOPEN.Object);
		Effect->bAutoActivate = false;
	}

	Box->SetRelativeLocation(FVector(0.0f, -3.5f, -30.0f));

	Trigger->SetCollisionProfileName(TEXT("ItemBox"));
	Box->SetCollisionProfileName(TEXT("NoCollision"));

	// blueprint 클래스로 생성된 무기의 클래스 타입을 받아와서 weaponitemclass 에 적용
	static ConstructorHelpers::FClassFinder<AABWeapon> weapon(TEXT("/Game/Book/Blueprints/BP_WeaponAxe.BP_WeaponAxe_C"));
	if (weapon.Succeeded())
	{
		WeaponItemClass = weapon.Class;
		//WeaponItemClass = AABWeapon::StaticClass();
	}	
}

// Called when the game starts or when spawned
void AABItemBox::BeginPlay()
{
	Super::BeginPlay();
	
}

void AABItemBox::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AABItemBox::OnCharacterOverlap);
}

void AABItemBox::OnCharacterOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ABLOG_S(Warning);

	auto character = Cast<ABCharacter>(OtherActor);
	ABCHECK(nullptr != character);

	if (nullptr != character && nullptr != WeaponItemClass)
	{
		ABLOG(Warning, TEXT("%s can't equip weapon currently. WeaponItemClass"), *character->GetName());

		if (character->CanSetWeapon())
		{
			auto NewWeapon = GetWorld()->SpawnActor<AABWeapon>(WeaponItemClass, FVector::ZeroVector, FRotator::ZeroRotator);
			character->SetWeapon(NewWeapon);
			Effect->Activate(true);
			Box->SetHiddenInGame(true, true);	// SetVisibility 와 다르게 이 기능은, 에디터에서는 보이고, 게임에서는 보이지 않게 한다.
			SetActorEnableCollision(false);
			/*
				chapter 10
				
				OnSystemFinished 델리게이트는 다이나믹 형식이므로 바인딩할 대상 멤버 함수에 UFUNCTION 매크로를 선언해줘야 한다.
				다이나믹 델리게이트는 아쉽게도 C++ 람다식으로 표현한 함수는 바인딩할 수 없다
			*/
			Effect->OnSystemFinished.AddDynamic(this, &AABItemBox::OnEffectFinished);
		}
		else
		{
			ABLOG(Warning, TEXT("%s can't equip weapon currently."), *character->GetName());
		}
	}
}

void AABItemBox::OnEffectFinished(UParticleSystemComponent * PSystem)
{
	Destroy();
}
