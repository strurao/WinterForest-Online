#pragma once
#include "Session.h"
// ���� ���忡�� Ŭ���̾�Ʈ�� ������ ���Ӽ���
class GameSession : public PacketSession
{
public:
	~GameSession()
	{
		cout << "~GameSession" << endl;
	}
	int b = 0;
	virtual void OnConnected() override;
	virtual void OnDisconnected() override;
	virtual void OnRecvPacket(BYTE* buffer, int32 len) override;
	virtual void OnSend(int32 len) override;
};