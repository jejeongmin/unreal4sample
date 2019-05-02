// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/*
	���ø��� �̿��ϸ�, ������ �Ļ� Ŭ������ ���� ����� include �� �ʿ䵵 ����,
	��Ȱ�뼺�� ��������.
*/
template<typename T>
T* GetCustomGameMode(UWorld* worldContext)
{
	return Cast<T>(worldContext->GetAuthGameMode());
}