# 2D Online Sync
온라인 멀티플레이어 프로젝트로, ``IOCP Server`` 와 간단한 ``2D Client`` 를 만들어서 움직임과 공격 기능을 동기화했습니다.

## 개발 환경 🛠
- C++
- Windows API
- Visual Studio 2022

## 프로젝트 설명 🗂
- DummyClient : 멀티스레드 연습용 Dummy 클라이언트 프로젝트
- Server : 서버 로직
- ServerCore : IOCP 서버 라이브러리
- Zelda2D : 클라이언트 로직

## 기능 🕹
- 2D TileMap Top-down 게임이며 플레이어와 몬스터는 공격 및 이동 기능이 가능하고, 플레이어를 쫓아오고 공격하는 뱀 몬스터에게 공격을 당하거나 가할 수 있습니다.
  - ``State Pattern`` 으로 ``Creature`` (Player, Monster) 의 ``State`` 정보 (IDLE, MOVE, SKILL) 와 ``Direction`` 정보 (UP, DOWN, LEFT, RIGHT) 에 따라 로직을 처리해주었습니다.
  - 뱀 몬스터는 ``A*`` 알고리즘으로 플레이어를 쫓아오는 길을 탐색하고 서버에서 연산하여 클라이언트에게 ``Broadcast`` 해줍니다.

- IOCP 모델 서버
  - ``IocpCore`` 클래스에서 ``IocpQueue`` (Completion Port) 를 구현하고, ``IocpObject`` (Session, Listener) 를 Register 하고 작업을 진행할 때 ``EventType`` (Accept, Connect, Disconnect, Recv, Send) 에 따라 비동기 함수로 처리할 수 있도록 해주었습니다.
  - 서버의 ``Session`` 클래스는 클라이언트에 대한 정보를 가지고 있으며, ``Session`` 은 클라이언트의 정보에 대한 스마트 포인터를 가지고 있어서 reference counting 을 하여, ``IocpQueue`` 에서 사라질 때 (접속이 끊기거나 게임을 종료하는 등의 상황에서) 발생 가능한 메모리 문제를 방지해줍니다.
  - 클라이언트는 ``ServerSession`` 으로 서버와의 통신을 할 수 있고, 서버는 ``GameSession`` 으로 클라이언트와 통신할 수 있습니다.

- 이동 동기화
  - 클라이언트가 이동한 후 서버에 통지하는 방식으로 작업했습니다.
  - 클라이언트의 ``State``, ``Direction``, ``CellPos``(X,Y좌표) 세 가지 중 하나라도 바뀌는 것을 매 프레임마다 확인해주고, 관련 패킷을 서버에 전송하면
  - 서버의 ``ServerPacketHandler`` 에서 처리 후 클라이언트들에게 ``Broadcast`` 해주고, 각 클라이언트는 ``Broadcast`` 받은 정보를 처리해줍니다.

- 패킷 관리
  - ``Google Protocol Buffers`` 를 사용하여 플레이어의 입장, 퇴장, 이동에 관한 프로토콜을 정의한 후 패킷의 직렬화/역직렬화를 해주고,
  - 서버와 클라이언트는 각각 ``ServerPacketHandler``, ``ClientPacketHandler`` 에서 분기처리와 파싱을 해줍니다.


## 소개 링크 🎬
- [Youtube](https://youtu.be/iOhF693v0tQ?si=GSckKGGXk10lnnF2)
![image](https://github.com/strurao/WinterForest-Online/assets/126440235/c55b81cb-56ec-46c0-b619-b99e4a5a314f)
