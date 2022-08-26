// Copyright Epic Games, Inc. All Rights Reserved.
#include "CoreMinimal.h"
#include "UnSkynet.h"
#include "SocketSubsystem.h"
#include "IPAddress.h"
#include "Sockets.h"
#include "RequiredProgramMainCPPInclude.h"

DEFINE_LOG_CATEGORY_STATIC(LogUnSkynet, Log, All);

IMPLEMENT_APPLICATION(UnSkynet, "UnSkynet");

bool LoadStartSetting(FString& configPath, StartSetting& setting)
{
	FString s;
	bool ok = GConfig->GetString(TEXT("ServerSetting"), TEXT("workerNum"), s, *configPath);
	if (!ok)
	{
		UE_LOG(LogUnSkynet, Display, TEXT("not found setting workerNum"));
		return false;
	}

	int32 workerNum = FCString::Atoi(*s);
	if (workerNum < 0)
	{
		UE_LOG(LogUnSkynet, Display, TEXT("not found setting workerNum < 0"));
		return false;
	}

	setting.workerNum = workerNum;
	return true;
}


INT32_MAIN_INT32_ARGC_TCHAR_ARGV()
{
	FString CmdLine = FCommandLine::BuildFromArgV(nullptr, ArgC, ArgV,nullptr);
	GEngineLoop.PreInit(*CmdLine);
	UE_LOG(LogUnSkynet, Display, TEXT("CmdLine: %s"), *CmdLine);


	// 	FParse::Param用来解析形如 - xx的参数
	// 	FParse::Value用来解析形如key = value或 - key = value的	
	//FString param;
	//FParse::Value(*CmdLine, TEXT("-test="), param);
	//UE_LOG(LogUnSkynet, Display, TEXT("param: %s"), *param);
	//bool btest2 = FParse::Param(*CmdLine, TEXT("test"));
	//UE_LOG(LogUnSkynet, Display, TEXT("test: %d"), btest2);
	FString configPath;
	bool ok = FParse::Value(*CmdLine, TEXT("-config="), configPath);
	if (!ok)
	{
		UE_LOG(LogUnSkynet, Display, TEXT("not found -config="));
		return 0;
	}
	UE_LOG(LogUnSkynet, Display, TEXT("path :%s"), *configPath);
	
	StartSetting* setting = new StartSetting();
	ok = LoadStartSetting(configPath, *setting);
	if (!ok)
	{
		return 0;
	}

// 	ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get();
// 	TSharedRef<FInternetAddr> InternetAddress = SocketSubsystem->CreateInternetAddr();
// 	InternetAddress->SetAnyAddress();
// 	InternetAddress->SetPort(6666);
// 	FSocket* NewSocket = SocketSubsystem->CreateSocket(NAME_Stream, TEXT("testSocket"));
// 	NewSocket->SetNonBlocking(true);
// 	NewSocket->Bind(*InternetAddress);
// 	int32 ActualBufferSize;
// 	NewSocket->SetSendBufferSize(65535, ActualBufferSize);
// 	NewSocket->Listen(16);

	UnSkynet::instance()->Start(setting);
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
