// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "PowerUpPlugin.h"

// ����� private ��� ������ ���⿡ include�ؾ� �Ѵ�. 
// ����� �ҽ� ������ ��κ��� ����ϴ� ����� ���Խ�Ű��

#include "CoreUObject.h" 

// �Ʒ� ������ �� ����� �������� �������ִ� ���忪���� �ϸ�, �÷����� �ڵ� ���̽��� ��򰡿��� �ٽ� �� ����� �������� �ʵ��� ���ش�.
#define LOCTEXT_NAMESPACE "FPowerUpPluginModule"

void FPowerUpPluginModule::StartupModule()
{
}

void FPowerUpPluginModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE
	
// ���ε��� ���� �غ��ϴ� �ڵ� �����̸�, �ι�° ���ڴ� uplugin �� ��õ� ��� �̸��� ���⿡ �����ϰ� �������ش�.
IMPLEMENT_MODULE(FPowerUpPluginModule, PowerUpPlugin)