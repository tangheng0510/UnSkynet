// Copyright Epic Games, Inc. All Rights Reserved.
#include "CoreMinimal.h"
#include "UnSkynet.h"
#include "RequiredProgramMainCPPInclude.h"

DEFINE_LOG_CATEGORY_STATIC(LogUnSkynet, Log, All);

IMPLEMENT_APPLICATION(UnSkynet, "UnSkynet");

INT32_MAIN_INT32_ARGC_TCHAR_ARGV()
{
	GEngineLoop.PreInit(ArgC, ArgV);
	UE_LOG(LogUnSkynet, Display, TEXT("Hello World"));

	UnSkynet::instance()->Start();

	int count = 0;
	while (!IsEngineExitRequested())
	{
		count = count + 1;
		//UE_LOG(LogUnSkynet, Display, TEXT("%d"), count);
		FPlatformProcess::Sleep(0.03);
	}

	UnSkynet::instance()->Stop();
	UnSkynet::instance()->WaitComplete();

	return 0;
}
