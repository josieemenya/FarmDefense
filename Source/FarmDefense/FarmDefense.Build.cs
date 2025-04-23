// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FarmDefense : ModuleRules
{
	public FarmDefense(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG", "Landscape" });
	}
}
