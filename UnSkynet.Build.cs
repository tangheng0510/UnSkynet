// Copyright Epic Games, Inc. All Rights Reserved.
using UnrealBuildTool;

public class UnSkynet : ModuleRules
{
	public UnSkynet(ReadOnlyTargetRules Target) : base(Target)
	{
		PublicIncludePaths.Add("Runtime/Launch/Public");
		PublicIncludePaths.Add("Runtime/Core/Public/Containers");
		PublicIncludePaths.Add("Runtime/Core/Public/Misc");
		PublicIncludePaths.Add("Runtime/Core/Public/HAL");

		PrivateIncludePaths.Add("Runtime/Launch/Private");      // For LaunchEngineLoop.cpp include

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"Projects",
			"Sockets",
			"Networking"
		});
	}
}
