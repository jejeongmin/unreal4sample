// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class HowTo_PlayerCameraEditorTarget : TargetRules
{
	public HowTo_PlayerCameraEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

        DefaultBuildSettings = BuildSettingsVersion.V5;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_5;

        ExtraModuleNames.AddRange( new string[] { "HowTo_PlayerCamera" } );
	}
}
