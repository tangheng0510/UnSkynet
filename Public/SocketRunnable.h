#pragma once
#include "CoreMinimal.h"
#include "SocketSubsystem.h"
#include "IPAddress.h"
#include "Sockets.h"

struct TCPSocketServer
{
	FSocket* ListenSocket;
	TMap<uint32, FSocket*> ConnectionSockets;
};