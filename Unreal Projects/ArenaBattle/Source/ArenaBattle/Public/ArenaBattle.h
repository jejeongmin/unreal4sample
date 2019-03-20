// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"

// c++ 에서 선언한 열거형을 블루프린트에서 사용하기 위해서는 열거형 선언 윗줄에 UENUM(BlueprintType)을 선언하고 uint8 으로 기반 유형을 지정해야 한다.
UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	PREINIT,
	LOADING,
	READY,
	DEAD
};

DECLARE_LOG_CATEGORY_EXTERN(ArenaBattle, Log, All);
#define ABLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define ABLOG_S(Verbosity) UE_LOG(ArenaBattle, Verbosity, TEXT("%s"), *ABLOG_CALLINFO)
#define ABLOG(Verbosity, Format, ...) UE_LOG(ArenaBattle, Verbosity, TEXT("%s %s"), *ABLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

#define ABCHECK(Expr, ...) {if(!(Expr)) {ABLOG(Error, TEXT("ASSERTION : %s"), TEXT("'"#Expr"'")); return __VA_ARGS__;}}