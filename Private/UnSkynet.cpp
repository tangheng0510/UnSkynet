#include "UnSkynet.h"
#include "WorkerRunnable.h"

UnSkynet* UnSkynet::inst;

UnSkynet::UnSkynet()
{
}

void UnSkynet::Start(StartSetting* setting)
{
	startSetting = setting;
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
	int workerNum = startSetting->workerNum;
	for (int i = 0; i < workerNum; i++)
	{
		// 调用FRunnableThread::Create来创建一个线程
		FWorkerRunable* worker = new FWorkerRunable(i);
		workers.Add(worker);
	}
}
