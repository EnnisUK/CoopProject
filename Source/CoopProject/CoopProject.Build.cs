// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CoopProject : ModuleRules
{
	public CoopProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG" });
        
        PrivateDependencyModuleNames.AddRange(new string[] { "OnlineSubsystem", "OnlineSubsystemUtils", "OnlineSubsystemSteam" });
        
        
	}
}
