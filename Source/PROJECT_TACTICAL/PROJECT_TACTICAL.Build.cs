// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PROJECT_TACTICAL : ModuleRules
{
	public PROJECT_TACTICAL(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
