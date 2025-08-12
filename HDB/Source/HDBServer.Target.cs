// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class HDBServerTarget : TargetRules
{
	public HDBServerTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Server;
		DefaultBuildSettings = BuildSettingsVersion.V5;
        ExtraModuleNames.AddRange( new string[] { "HDB" } );
	}
}
