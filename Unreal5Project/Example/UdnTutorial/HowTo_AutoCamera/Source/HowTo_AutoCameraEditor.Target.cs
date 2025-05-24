// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class HowTo_AutoCameraEditorTarget : TargetRules
{
	public HowTo_AutoCameraEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		bOverrideBuildEnvironment = true;

        ExtraModuleNames.AddRange( new string[] { "HowTo_AutoCamera" } );
	}
}
