#pragma once
#include "CorePch.h"
#include "Types.h"
#include "Values.h"
#include "Defines.h"
#include "Enums.h"
#include "Utils.h"

#include "Protocol.pb.h"
#include "Enum.pb.h"
#include "Struct.pb.h"
#include <assert.h>
#include "ClientPacketHandler.h"

// C++ 20
#include <format>
#include <filesystem>
namespace fs = std::filesystem;

// 메모리 릭을 확인해준다
#define _CRTDEBG_MAP_ALLOC 
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
// 현재 실행되고 있는 파일이름, 몇번째줄인지 추적 가능
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__) 
#endif

#pragma comment(lib, "msimg32.lib")

// Sound
#include <MMSystem.h>
#include <dsound.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")


#ifdef _DEBUG
#pragma comment(lib, "ServerCore\\Debug\\ServerCore.lib")
#pragma comment(lib, "Protobuf\\Debug\\libprotobufd.lib")
#else
#pragma comment(lib, "ServerCore\\Release\\ServerCore.lib")
#pragma comment(lib, "Protobuf\\Release\\libprotobuf.lib")
#endif

#include <windows.h>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <string>
#include <algorithm>
#include <functional>

#include <queue>
using namespace std;










