// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LyraCharacterPartTypes.h"
#include "Components/ControllerComponent.h"
#include "LyraControllerComponent_CharacterParts.generated.h"

class ULyraPawnComponent_CharacterParts;

/** ControllerComponent가 소유하는 Character Parts */
USTRUCT()
struct FLyraControllerCharacterPartEntry
{
	GENERATED_BODY()

	/** Character Part에 대한 정의(메타 데이터 == MetaData) */
	UPROPERTY(EditAnywhere)
	FLyraCharacterPart Part;

	/** Character Part 핸들 (고유값) - Controller가 Possess하고 있는 Pawn에서 생성한(인스턴스) Character Part 핸들값 */
	FLyraCharacterPartHandle Handle;
};

UCLASS(meta = (BlueprintSpawnableComponent))
class ULyraControllerComponent_CharacterParts : public UControllerComponent
{
	GENERATED_BODY()
public:
	ULyraControllerComponent_CharacterParts(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UPROPERTY(EditAnywhere, Category = Cosmetics)
	TArray<FLyraControllerCharacterPartEntry> CharacterParts;
};