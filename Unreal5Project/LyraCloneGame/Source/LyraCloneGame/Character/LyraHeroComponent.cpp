// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/LyraHeroComponent.h"
#include "Components/GameFrameworkComponentManager.h"
#include <Player/LyraPlayerState.h>
#include "LyraGameplayTags.h"
#include "LyraLog.h"
#include "LyraPawnExtensionComponent.h"
#include "Character/LyraPawnData.h"


/** FeatureName 정의: static member variable 초기화 */
const FName ULyraHeroComponent::NAME_ActorFeatureName("Hero");

ULyraHeroComponent::ULyraHeroComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = false;
}

void ULyraHeroComponent::OnRegister()
{
	Super::OnRegister();

	// 올바른 Actor에 등록되었는지 확인:
	{
		if (!GetPawn<APawn>())
		{
			UE_LOG(LyraLog, Error, TEXT("this component has been added to a BP whose base class is not a Pawn!"));
			return;
		}
	}

	RegisterInitStateFeature();
}

void ULyraHeroComponent::BeginPlay()
{
	Super::BeginPlay();

	// PawnExtensionComponent에 대해서 (PawnExtension Feature) OnActorInitStateChanged() 관찰하도록 (Observing)
	BindOnActorInitStateChanged(ULyraPawnExtensionComponent::NAME_ActorFeatureName, FGameplayTag(), false);

	// InitState_Spawned로 초기화
	ensure(TryToChangeInitState(FLyraGameplayTags::Get().InitState_Spawned));

	// ForceUpdate 진행
	CheckDefaultInitialization();
}

void ULyraHeroComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UnregisterInitStateFeature();

	Super::EndPlay(EndPlayReason);
}


void ULyraHeroComponent::OnActorInitStateChanged(const FActorInitStateChangedParams& Params)
{
	const FLyraGameplayTags& InitTags = FLyraGameplayTags::Get();

	if (Params.FeatureName == ULyraPawnExtensionComponent::NAME_ActorFeatureName)
	{
		// HakPawnExtensionComponent의 DataInitialized 상태 변화 관찰 후, HakHeroComponent도 DataInitialized 상태로 변경
		// - CanChangeInitState 확인
		if (Params.FeatureState == InitTags.InitState_DataInitialized)
		{
			CheckDefaultInitialization();
		}
	}
}

bool ULyraHeroComponent::CanChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState) const
{
	check(Manager);

	const FLyraGameplayTags& InitTags = FLyraGameplayTags::Get();
	APawn* Pawn = GetPawn<APawn>();
	ALyraPlayerState* LyraPS = GetPlayerState<ALyraPlayerState>();

	// Spawned 초기화
	if (!CurrentState.IsValid() && DesiredState == InitTags.InitState_Spawned)
	{
		if (Pawn)
		{
			return true;
		}
	}

	// Spawned -> DataAvailable
	if (CurrentState == InitTags.InitState_Spawned && DesiredState == InitTags.InitState_DataAvailable)
	{
		if (!LyraPS)
		{
			return false;
		}

		return true;
	}

	// DataAvailable -> DataInitialized
	if (CurrentState == InitTags.InitState_DataAvailable && DesiredState == InitTags.InitState_DataInitialized)
	{
		// PawnExtensionComponent가 DataInitialized될 때까지 기다림 (== 모든 Feature Component가 DataAvailable인 상태)
		return LyraPS && Manager->HasFeatureReachedInitState(Pawn, ULyraPawnExtensionComponent::NAME_ActorFeatureName, InitTags.InitState_DataInitialized);
	}

	// DataInitialized -> GameplayReady
	if (CurrentState == InitTags.InitState_DataInitialized && DesiredState == InitTags.InitState_GameplayReady)
	{
		return true;
	}

	return false;
}

void ULyraHeroComponent::HandleChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState)
{
	const FLyraGameplayTags& InitTags = FLyraGameplayTags::Get();

	// DataAvailable -> DataInitialized 단계
	if (CurrentState == InitTags.InitState_DataAvailable && DesiredState == InitTags.InitState_DataInitialized)
	{
		APawn* Pawn = GetPawn<APawn>();
		ALyraPlayerState* LyraPS = GetPlayerState<ALyraPlayerState>();
		if (!ensure(Pawn && LyraPS))
		{
			return;
		}

		// Input과 Camera에 대한 핸들링... (TODO)

		const bool bIsLocallyControlled = Pawn->IsLocallyControlled();
		const ULyraPawnData* PawnData = nullptr;
		if (ULyraPawnExtensionComponent* PawnExtComp = ULyraPawnExtensionComponent::FindPawnExtensionComponent(Pawn))
		{
			PawnData = PawnExtComp->GetPawnData<ULyraPawnData>();
		}

		//if (bIsLocallyControlled && PawnData)
		//{
		//	// 현재 HakCharacter에 Attach된 CameraComponent를 찾음
		//	if (UHakCameraComponent* CameraComponent = UHakCameraComponent::FindCameraComponent(Pawn))
		//	{
		//		CameraComponent->DetermineCameraModeDelegate.BindUObject(this, &ThisClass::DetermineCameraMode);
		//	}
		//}
	}
}

void ULyraHeroComponent::CheckDefaultInitialization()
{
	// 앞서 BindOnActorInitStateChanged에서 보았듯이 Hero Feature는 Pawn Extension Feature에 종속되어 있으므로, CheckDefaultInitializationForImplementers 호출하지 않음:

	// ContinueInitStateChain은 앞서 PawnExtComponent와 같음
	const FLyraGameplayTags& InitTags = FLyraGameplayTags::Get();
	static const TArray<FGameplayTag> StateChain = { InitTags.InitState_Spawned, InitTags.InitState_DataAvailable, InitTags.InitState_DataInitialized, InitTags.InitState_GameplayReady };
	ContinueInitStateChain(StateChain);
}