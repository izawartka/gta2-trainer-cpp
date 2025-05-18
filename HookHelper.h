#pragma once

class HookHelper {
public:
	static bool HookFunction(const DWORD originalFn, DWORD hookFn, size_t copyBytes = 5);
	static bool HookFunctionCall(const DWORD originalFnCall, DWORD hookFn, bool useCall = false);
	static bool HookLibraryFunctionCall(const DWORD originalFnPtrAddr, DWORD hookFn, DWORD& originalFnPtrStore);
};