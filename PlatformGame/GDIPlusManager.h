#pragma once
#include "EngineWin.h"

class GDIPlusManager
{
public:
	// when a gdipman is ctored when no others exist, it will init gdip
	GDIPlusManager();
	// when a gdipman is dtored and it is the last existing, it will cleanup gdip
	~GDIPlusManager();
private:
	// gdip creation token (for API calls)
	static ULONG_PTR token;
	// refcount to keep track of when necessary to init/cleanup
	static int refCount;
};