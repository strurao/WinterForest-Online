# 2D Online Sync
온라인 멀티플레이어 프로젝트로, IOCP Server 와 Dummy Client 프로젝트를 만들어서 움직임과 공격 기능을 동기화했습니다.

## 개발 환경 🛠
- C++
- Windows API
- Visual Studio 2022

## 기능 🕹
- 서버는 ``IOCP`` 모델을, 더미 클라이언트는 ``WSAEventSelect`` 모델을 채택했습니다.
  - ``IOCP Core`` 클래스에서 ``IOCP Queue`` 를 구현, ``IOCP Event (Session, Listener)`` 를 Register 등록해주고 워커스레드들이 Dispatch 하도록 비동기적으로 나눠주었습니다.
  - Session Service 

## 소개 링크 🎬
- [Youtube](https://youtu.be/iOhF693v0tQ?si=GSckKGGXk10lnnF2)
![image](https://github.com/strurao/WinterForest-Online/assets/126440235/c55b81cb-56ec-46c0-b619-b99e4a5a314f)
