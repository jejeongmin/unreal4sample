// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/*
	템플릿을 이용하면, 구현된 파생 클래스에 대한 헤더를 include 할 필요도 없고,
	재활용성도 높아진다.
*/
template<typename T>
T* GetCustomGameMode(UWorld* worldContext)
{
	return Cast<T>(worldContext->GetAuthGameMode());
}