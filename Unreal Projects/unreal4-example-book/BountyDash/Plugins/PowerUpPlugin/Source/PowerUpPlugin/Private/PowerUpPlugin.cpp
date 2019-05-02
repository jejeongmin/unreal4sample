// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "PowerUpPlugin.h"

// 모듈의 private 헤더 파일을 여기에 include해야 한다. 
// 모듈의 소스 파일의 대부분이 사용하는 헤더를 포함시키자

#include "CoreUObject.h" 

// 아래 선언은 이 모듈의 고유성을 보장해주는 가드역할을 하며, 플러그인 코드 베이스의 어딘가에서 다시 이 모듈이 구현되지 않도록 해준다.
#define LOCTEXT_NAMESPACE "FPowerUpPluginModule"

void FPowerUpPluginModule::StartupModule()
{
}

void FPowerUpPluginModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE
	
// 모듈로딩을 위해 준비하는 코드 라인이며, 두번째 인자는 uplugin 에 명시된 모듈 이름을 여기에 동일하게 적시해준다.
IMPLEMENT_MODULE(FPowerUpPluginModule, PowerUpPlugin)