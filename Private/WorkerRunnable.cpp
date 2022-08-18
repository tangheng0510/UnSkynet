#include "WorkerRunnable.h"

FWorkerRunable::FWorkerRunable(int32 index)
{
	ThreadIndex = index;
	UE_LOG(TestLog, Display, TEXT("FWorkerRunable Contruct: ThreadIndex:%d tid:0x%x"), ThreadIndex, FPlatformTLS::GetCurrentThreadId());

	thread = MakeShareable(FRunnableThread::Create(this, *FString::Printf(TEXT("worker:%d"), index)));
}

// 放置线程运行的代码   【在线程上执行】
uint32 FWorkerRunable::Run()  
{
	while (!IsStop)
	{
		FPlatformProcess::Sleep(2.0f);
		UE_LOG(TestLog, Display, TEXT("FWorkerRunable Run ThreadIndex:%d tid:0x%x"), ThreadIndex, FPlatformTLS::GetCurrentThreadId());
	}
	
	return 0;
}

void FWorkerRunable::WaitComplete()
{
	thread->WaitForCompletion();
}
