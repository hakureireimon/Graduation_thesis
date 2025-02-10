// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UGCItemFramework : ModuleRules
{
	public UGCItemFramework(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UnLua" });
	}
}
