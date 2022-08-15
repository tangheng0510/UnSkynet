// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnSkynet.h"

#include "TestRunnable.h"
#include "RequiredProgramMainCPPInclude.h"

DEFINE_LOG_CATEGORY_STATIC(LogUnSkynet, Log, All);

IMPLEMENT_APPLICATION(UnSkynet, "UnSkynet");

INT32_MAIN_INT32_ARGC_TCHAR_ARGV()
{
	GEngineLoop.PreInit(ArgC, ArgV);
	UE_LOG(LogUnSkynet, Display, TEXT("Hello World"));

	UE_LOG(TestLog, Log, TEXT("RunTest Begin tid:0x%x FrameIndex:%llu"), FPlatformTLS::GetCurrentThreadId(), GFrameCounter);

	// 调用FRunnableThread::Create来创建一个线程
	FRunnableThread* Test1Thread0 = FRunnableThread::Create(new FTest1Runable(0), TEXT("Test1Thread0"));  // Test1Thread0为线程名
	FRunnableThread* Test1Thread1 = FRunnableThread::Create(new FTest1Runable(1), TEXT("Test1Thread1"));
	FRunnableThread* Test1Thread2 = FRunnableThread::Create(new FTest1Runable(2), TEXT("Test1Thread2"));

	int count = 0;
	while (!IsEngineExitRequested())
	{
		count = count + 1;
		//UE_LOG(LogUnSkynet, Display, TEXT("%d"), count);
		FPlatformProcess::Sleep(0.03);
	}

	return 0;
}
