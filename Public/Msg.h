#pragma once


class MsgBase
{
public:

private:
	uint8 type;
	TSharedPtr<char> buff;
	uint64 size;
};