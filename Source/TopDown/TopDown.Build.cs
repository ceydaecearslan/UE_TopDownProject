// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TopDown : ModuleRules
{
	public TopDown(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
	        "Core", 
	        "CoreUObject", 
	        "Engine", 
	        "InputCore", 
	        "NavigationSystem",
	        "AIModule", 
	        "Niagara",
	        "EnhancedInput", 
	        "GameplayAbilities",
	        "GameplayTags",
	        "GameplayTasks",
	        "CommonUI",
	        "UMG",
	        "SlateCore",
        });
        
	}
}
