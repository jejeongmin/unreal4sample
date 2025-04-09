// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class SolarSystemEditorTarget : TargetRules
{
	public SolarSystemEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		bOverrideBuildEnvironment = true;

        ExtraModuleNames.AddRange( new string[] { "SolarSystem" } );
	}
}
