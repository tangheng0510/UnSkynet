#pragma once

#include "CoreMinimal.h"
#include "LockFreeList.h"
#include "Msg.h"

class Service 
{
public:
	Service(uint32 id, FString& name);
private:
	uint32 id;
	FString name;

	TLockFreePointerListFIFO<MsgBase, 0> msgQueue;
};