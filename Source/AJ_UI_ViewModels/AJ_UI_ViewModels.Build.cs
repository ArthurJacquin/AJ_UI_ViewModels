// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AJ_UI_ViewModels : ModuleRules
{
	public AJ_UI_ViewModels(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"DeveloperSettings",
				"ModelViewViewModel",
			});
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"GameplayTags",
				"Slate",
				"SlateCore",
			});
	}
}
