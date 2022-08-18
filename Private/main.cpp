// Copyright Epic Games, Inc. All Rights Reserved.
#include "CoreMinimal.h"
#include "UnSkynet.h"
#include "RequiredProgramMainCPPInclude.h"

DEFINE_LOG_CATEGORY_STATIC(LogUnSkynet, Log, All);

IMPLEMENT_APPLICATION(UnSkynet, "UnSkynet");

INT32_MAIN_INT32_ARGC_TCHAR_ARGV()
{
	FString CmdLine = FCommandLine::BuildFromArgV(nullptr, ArgC, ArgV,nullptr);
	GEngineLoop.PreInit(*CmdLine);
	UE_LOG(LogUnSkynet, Display, TEXT("Hello World"));
	UE_LOG(LogUnSkynet, Display, TEXT("CmdLine: %s"), *CmdLine);
	// 	FParse::Param用来解析形如 - xx的参数
	// 	FParse::Value用来解析形如key = value或 - key = value的	
	FString param;
	FParse::Value(*CmdLine, TEXT("-test="), param);
	UE_LOG(LogUnSkynet, Display, TEXT("param: %s"), *param);
	bool btest2 = FParse::Param(*CmdLine, TEXT("test"));
	UE_LOG(LogUnSkynet, Display, TEXT("test: %d"), btest2);

	UnSkynet::instance()->Start();
	while (!IsEngineExitRequested())
	{
		FPlatformProcess::Sleep(1.0f);
	}
	UnSkynet::instance()->Stop();
	UnSkynet::instance()->WaitComplete();

	FEngineLoop::AppPreExit();
	FModuleManager::Get().UnloadModulesAtShutdown();
	FEngineLoop::AppExit();

	return 0;
}
