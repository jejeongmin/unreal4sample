// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PuzzlePlatforms : ModuleRules
{
	public PuzzlePlatforms(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]{ 
			"Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", 
			"UMG", 
			"OnlineSubsystem", "OnlineSubsystemUtils",
			"OnlineSubsystemSteam" });

        // Always include the module root directory ("./") in the include path
        PublicIncludePaths.Add(ModuleDirectory);
    }
}
