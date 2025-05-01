#pragma once

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.


#include <windows.h>

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include <assert.h>

#include <objidl.h>						// Gdiplus 제외 되는거 막기 용
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")
