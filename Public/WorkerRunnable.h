#pragma once

#include "CoreMinimal.h"
#include "HAL\Runnable.h"

DEFINE_LOG_CATEGORY_STATIC(TestLog, Log, All);

class FWorkerRunable : public FRunnable
{
public:
	FWorkerRunable(int32 index);
	virtual ~FWorkerRunable() override
	{
		UE_LOG(TestLog, Display, TEXT("FWorkerRunable Destruct: ThreadIndex:%d tid:0x%x"), ThreadIndex, FPlatformTLS::GetCurrentThreadId());
	}
	virtual bool Init() override   // 线程创建后，执行初始化工作   【在线程上执行】
	{
		UE_LOG(TestLog, Display, TEXT("FWorkerRunable Init: ThreadIndex:%d tid:0x%x"), ThreadIndex, FPlatformTLS::GetCurrentThreadId());
		return true;
	}
	virtual uint32 Run() override;  // 放置线程运行的代码   【在线程上执行】
	
	virtual void Stop() override
	{
		IsStop = true;
	}

	virtual void Exit() override   // 线程退出之前，进行清理工作   【在线程上执行】
	{
		UE_LOG(TestLog, Display, TEXT("FWorkerRunable Exit: ThreadIndex:%d tid:0x%x"), ThreadIndex, FPlatformTLS::GetCurrentThreadId());
	}

	void WaitComplete();
private:
	int32 ThreadIndex;

	TSharedPtr<FRunnableThread> thread;

	bool IsStop = false;
};
