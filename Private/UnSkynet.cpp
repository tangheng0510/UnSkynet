#include "UnSkynet.h"
#include "WorkerRunnable.h"

UnSkynet* UnSkynet::inst;

UnSkynet::UnSkynet()
{
}

void UnSkynet::Start()
{
	this->StartWorker();
}

void UnSkynet::Stop()
{
	for (auto worker : workers)
	{
		worker->Stop();
	}
}

void UnSkynet::WaitComplete()
{
	for (auto worker : workers)
	{
		worker->WaitComplete();
	}
}

void UnSkynet::StartWorker()
{
	for (int i = 0; i < 8; i++) 
	{
		// 调用FRunnableThread::Create来创建一个线程
		FWorkerRunable* worker = new FWorkerRunable(i);
		workers.Add(worker);
	}
}
