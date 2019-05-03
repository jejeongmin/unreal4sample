// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "NSHUD.generated.h"

UCLASS()
class ANSHUD : public AHUD
{
	GENERATED_BODY()

public:
	ANSHUD();

	/** HUD�� ���� �� ��ο� �� */
	virtual void DrawHUD() override;

private:
	/** ũ�ν���� ���� ������ */
	class UTexture2D* CrosshairTex;

};

