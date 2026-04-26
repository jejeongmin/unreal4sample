// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class MP_Cpp : ModuleRules
{
	public MP_Cpp(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput",
			"UMG", "NetCore",
		});

        PrivateIncludePaths.AddRange(new string[]
        {
            "MP_CPP/",
        });
    }
}
