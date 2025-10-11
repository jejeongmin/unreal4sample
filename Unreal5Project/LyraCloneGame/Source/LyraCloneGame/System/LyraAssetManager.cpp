// Fill out your copyright notice in the Description page of Project Settings.


#include "LyraAssetManager.h"
#include "LyraLog.h"

ULyraAssetManager::ULyraAssetManager()
{
}

ULyraAssetManager& ULyraAssetManager::Get()
{
	check(GEngine);

	// �츮�� AssetManager�� UEngine�� GEngine�� AssetManager�� Class�� �������̵� �߱� ������, GEngine�� Asset Manager�� ����
	if (ULyraAssetManager* Singleton = Cast<ULyraAssetManager>(GEngine->AssetManager))
	{
		return *Singleton;
	}

	UE_LOG(LyraLog, Fatal, TEXT("invalid AssetManagerClassname in DefaultEngine.ini(project settings); it must be LyraAssetManager"));

	// ���� UE_LOG�� Fatal�� ����, Crash ���� ������ �������� ������ �������� ���� ���̷� ����
	return *NewObject<ULyraAssetManager>();
}

UE_DISABLE_OPTIMIZATION
void ULyraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
}
UE_ENABLE_OPTIMIZATION

bool ULyraAssetManager::ShouldLogAssetLoads()
{
	const TCHAR* CommandLineContent = FCommandLine::Get();
	static bool bLogAssetLoads = FParse::Param(CommandLineContent, TEXT("LogAssetLoads"));
	return bLogAssetLoads;
}

UObject* ULyraAssetManager::SynchronousLoadAsset(const FSoftObjectPath& AssetPath)
{
	// �ش� �Լ��� ���� ���� ������ 'synchronous load asset�� ���ʿ��ϰ� �ϴ� ���� ������ Ȯ���ϱ� ����'
	if (AssetPath.IsValid())
	{
		// FScopeLogTime�� Ȯ���غ���:
		TUniquePtr<FScopeLogTime> LogTimePtr;
		if (ShouldLogAssetLoads())
		{
			// �ܼ��� �α��ϸ鼭, �ʴ����� �α� ����
			LogTimePtr = MakeUnique<FScopeLogTime>(*FString::Printf(TEXT("synchronous loaded assets [%s]"), *AssetPath.ToString()), nullptr, FScopeLogTime::ScopeLog_Seconds);
		}

		// ���⼭ �ΰ��� �б�:
		// 1. AssetManager�� ������, AssetManager�� StreamableManager�� ���� ���� �ε�
		// 2. �ƴϸ�, FSoftObjectPath�� ���� �ٷ� ���� �ε�
		if (UAssetManager::IsInitialized())
		{
			return UAssetManager::GetStreamableManager().LoadSynchronous(AssetPath);
		}

		// if asset manager is not ready, use LoadObject()
		// - �� ����, StaticLoadObject�� ���δ�: 
		// - �����, �׻� StaticLoadObject�ϱ� ���� StaticFindObject�� ���� Ȯ���ϰ� �����ϸ� ��¥ �ε���
		return AssetPath.TryLoad();
	}

	return nullptr;
}

void ULyraAssetManager::AddLoadedAsset(const UObject* Asset)
{
	if (ensureAlways(Asset))
	{
		FScopeLock Lock(&SyncObject);
		LoadedAssets.Add(Asset);
	}
}
