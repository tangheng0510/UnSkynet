#pragma once

#include "CoreMinimal.h"
#include "HAL\Runnable.h"

DEFINE_LOG_CATEGORY_STATIC(TestLog, Log, All);

class FTest1Runable : public FRunnable
{
public:
	FTest1Runable(int32 index)
	{
		ThreadIndex = index;
		UE_LOG(TestLog, Display, TEXT("FTest1Runable Contruct: ThreadIndex:%d tid:0x%x FrameIndex:%llu"), ThreadIndex, FPlatformTLS::GetCurrentThreadId(), GFrameCounter);
	}
	virtual ~FTest1Runable() override
	{
		UE_LOG(TestLog, Display, TEXT("FTest1Runable Destruct: ThreadIndex:%d tid:0x%x FrameIndex:%llu"), ThreadIndex, FPlatformTLS::GetCurrentThreadId(), GFrameCounter);
	}
	virtual bool Init() override   // 线程创建后，执行初始化工作   【在线程上执行】
	{
		UE_LOG(TestLog, Display, TEXT("FTest1Runable Init: ThreadIndex:%d tid:0x%x FrameIndex:%llu"), ThreadIndex, FPlatformTLS::GetCurrentThreadId(), GFrameCounter);
		return true;
	}
	virtual uint32 Run() override   // 放置线程运行的代码   【在线程上执行】
	{
		UE_LOG(TestLog, Display, TEXT("FTest1Runable Run: 111 ThreadIndex:%d tid:0x%x FrameIndex:%llu"), ThreadIndex, FPlatformTLS::GetCurrentThreadId(), GFrameCounter);
		FPlatformProcess::Sleep(2.0f);
		UE_LOG(TestLog, Display, TEXT("FTest1Runable Run: 222 ThreadIndex:%d tid:0x%x FrameIndex:%llu"), ThreadIndex, FPlatformTLS::GetCurrentThreadId(), GFrameCounter);
		return 0;
	}
	virtual void Stop() override
	{
	}

	virtual void Exit() override   // 线程退出之前，进行清理工作   【在线程上执行】
	{
		UE_LOG(TestLog, Display, TEXT("FTest1Runable Exit: ThreadIndex:%d tid:0x%x FrameIndex:%llu"), ThreadIndex, FPlatformTLS::GetCurrentThreadId(), GFrameCounter);
	}
private:
	int32 ThreadIndex;
};
