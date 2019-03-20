// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class ArenaBattle : ModuleRules
{
	public ArenaBattle(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "AIModule", "GamePlayTasks" });

        /*
         *  chapter 13
         *  
         *  구현부가 모여 있는 Private 폴더에서만 ArenaBattleSetting 모듈을 사용할 예정이므로 PrivateDependencyModule 항목에 이를 추가한다.
         *  만약 header 에 멤버 변수로 추가된다면, PulbicDependencyMoudle 에 추가해야 한다.
         */
		PrivateDependencyModuleNames.AddRange(new string[] { "ArenaBattleSetting"  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
