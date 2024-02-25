#include "fileexists.h"

#include <windows.h>

#if defined(_MSC_VER)
int fileExists(const wchar_t *file)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE handle = FindFirstFile((LPCSTR) file, &FindFileData);
	int found = handle != INVALID_HANDLE_VALUE;
	if (found)
	{
		//FindClose(&handle); this will crash
		FindClose(handle);
	}
	return found;
}
#endif