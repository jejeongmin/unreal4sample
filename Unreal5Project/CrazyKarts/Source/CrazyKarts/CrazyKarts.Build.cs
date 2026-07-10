// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CrazyKarts : ModuleRules
{
	public CrazyKarts(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "ChaosVehicles", "PhysicsCore" });
	}
}
