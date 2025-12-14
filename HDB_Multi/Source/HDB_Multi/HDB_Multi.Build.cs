// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class HDB_Multi : ModuleRules
{
	public HDB_Multi(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"EnhancedInput",
			"GameplayTags",
            "GameplayTasks",
            "NavigationSystem",
            "AIModule",
			"UMG",
			"AnimGraphRuntime",
            "MotionWarping",
			"Niagara"
        });
	}
}
