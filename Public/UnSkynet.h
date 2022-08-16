// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WorkerRunnable.h"

//无锁队列
// TLockFreePointerListFIFO<T>：先进先出；
// TLockFreePointerListLIFO<T>：后进先出；
/*TLockFreePointerListUnordered<T>：看注释是说这个List内部元素是无序的，但效率比前面两个更高。*/

class UnSkynet
{
public:
	//单例
	static UnSkynet* inst;

	static UnSkynet* instance()
	{
		if (!inst)
		{
			inst = new UnSkynet();
		}
		return inst;
	}
public:
	//构造函数
	UnSkynet();

	void Start();
	void Stop();
	void WaitComplete();
private:
	//开启工作线程
	void StartWorker();
private:
	TArray<FWorkerRunable*> workers;
};