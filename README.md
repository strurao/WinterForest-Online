# 2D Online Sync

## 개발 도구 🛠
- C++
- Windows API
- Visual Studio 2022

## 기능 🕹
- 서버는 IOCP 모델을, 더미 클라이언트는 WSAEventSelect 모델을 채택했습니다.
  - IOCP Core 클래스에서 IOCP Queue 를 구현, IOCP Event (Session, Listener) 를 Register 등록해주고 워커스레드들이 Dispatch 하도록 비동기적으로 나눠주었습니다.
  - Session Service 



## 소개 링크 🎬
- [Youtube](https://youtu.be/iOhF693v0tQ?si=GSckKGGXk10lnnF2)


C++, Windows API, Visual Studio 2022
![winterforest@4x](https://github.com/strurao/WinterForest-Online/assets/126440235/b858e08a-32f7-47d4-8753-1f52334b058a)
