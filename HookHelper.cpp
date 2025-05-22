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
		*(BYTE*)((LPBYTE)originalFn + i) = 0x90; //NOP
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

bool HookHelper::ReplaceWithNoOps(const DWORD address, size_t size)
{
	DWORD OldProtection = { 0 };
	bool success = VirtualProtectEx(GetCurrentProcess(), (LPVOID)address, size, PAGE_EXECUTE_READWRITE, &OldProtection);
	if (!success) {
		DWORD error = GetLastError();
		return false;
	}

	for (size_t i = 0; i < size; i++) {
		*(BYTE*)((LPBYTE)address + i) = 0x90; //NOP
	}

	return true;
}

bool HookHelper::ReplaceWithNoOps(HookStruct& hookStruct, bool revert)
{
	if ((hookStruct.originalStore == nullptr) == revert) return false;

	DWORD OldProtection = { 0 };
	bool success = VirtualProtectEx(GetCurrentProcess(), (LPVOID)hookStruct.address, hookStruct.size, PAGE_EXECUTE_READWRITE, &OldProtection);
	if (!success) {
		DWORD error = GetLastError();
		return false;
	}

	if (!revert) {
		hookStruct.originalStore = new BYTE[hookStruct.size];

		for (size_t i = 0; i < hookStruct.size; i++) {
			hookStruct.originalStore[i] = *(BYTE*)((LPBYTE)hookStruct.address + i);
			*(BYTE*)((LPBYTE)hookStruct.address + i) = 0x90; //NOP
		}
	}
	else {
		for (size_t i = 0; i < hookStruct.size; i++) {
			*(BYTE*)((LPBYTE)hookStruct.address + i) = hookStruct.originalStore[i];
		}

		delete[] hookStruct.originalStore;
		hookStruct.originalStore = nullptr;
	}

	return true;
}

bool HookHelper::ReplaceMultipleWithNoOps(HookStruct* hookStructs, size_t count, bool revert)
{
	bool allSuccess = true;

	for (size_t i = 0; i < count; i++) {
		if (!ReplaceWithNoOps(hookStructs[i], revert)) {
			allSuccess = false;
		}
	}

	return allSuccess;
}