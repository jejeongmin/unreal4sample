// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/LyraGameState.h"
#include "GameModes/LyraExperienceManagerComponent.h"

ALyraGameState::ALyraGameState()
{
	ExperienceManagerComponent = CreateDefaultSubobject<ULyraExperienceManagerComponent>(TEXT("ExperienceManagerComponent"));
}
