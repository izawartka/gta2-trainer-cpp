#include "pch.h"
#include "HookHelper.h"

bool HookHelper::HookFunction(const DWORD originalFn, DWORD hookFn, size_t copyBytes) {
	DWORD OldProtection = { 0 };
	bool success = VirtualProtectEx(GetCurrentProcess(), (LPVOID)hookFn, copyBytes, PAGE_EXECUTE_READWRITE, &OldProtection);
	if (!success) {
		DWORD error = GetLastError();
		return false;
	}

	for (size_t i = 0; i < copyBytes; i++) {
		*(BYTE*)((LPBYTE)hookFn + i) = *(BYTE*)((LPBYTE)originalFn + i);
	}

	success = VirtualProtectEx(GetCurrentProcess(), (LPVOID)originalFn, copyBytes, PAGE_EXECUTE_READWRITE, &OldProtection);
	if (!success) {
		DWORD error = GetLastError();
		return false;
	}

	*(BYTE*)((LPBYTE)originalFn) = 0xE9; //JMP FAR
	DWORD offset = (((DWORD)hookFn) - ((DWORD)originalFn + 5)); //Offset math.
	*(DWORD*)((LPBYTE)originalFn + 1) = offset;

	for (size_t i = 5; i < copyBytes; i++) {
		*(BYTE*)((LPBYTE)originalFn + i) = 0x90; //JMP FAR
	}

	return true;
}

bool HookHelper::HookFunctionCall(const DWORD originalFnCall, DWORD hookFn, bool useCall) {
	DWORD OldProtection = { 0 };
	bool success = VirtualProtectEx(GetCurrentProcess(), (LPVOID)originalFnCall, 5, PAGE_EXECUTE_READWRITE, &OldProtection);
	if (!success) {
		DWORD error = GetLastError();
		return false;
	}

	*(BYTE*)((LPBYTE)originalFnCall) = useCall ? 0xE8 : 0xE9; //CALL FAR or JMP FAR
	DWORD offset = (((DWORD)hookFn) - ((DWORD)originalFnCall + 5)); //Offset math.
	*(DWORD*)((LPBYTE)originalFnCall + 1) = offset;

	return true;
}

bool HookHelper::HookLibraryFunctionCall(const DWORD originalFnPtrAddr, DWORD hookFn, DWORD& originalFnPtrStore) {
	if (*(DWORD*)originalFnPtrAddr == hookFn) return false; // already hooked

	originalFnPtrStore = *(DWORD*)originalFnPtrAddr;
	*(DWORD*)originalFnPtrAddr = hookFn;

	return true;
}
