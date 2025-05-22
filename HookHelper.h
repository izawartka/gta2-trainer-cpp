#pragma once

class HookHelper {
public:
	struct HookStruct {
		~HookStruct() {
			if (originalStore != nullptr) delete[] originalStore;
		}

		const DWORD address;
		const size_t size;
		BYTE* originalStore = nullptr;
	};

	static bool HookFunction(const DWORD originalFn, DWORD hookFn, size_t copyBytes = 5);
	static bool HookFunctionCall(const DWORD originalFnCall, DWORD hookFn, bool useCall = false);
	static bool HookLibraryFunctionCall(const DWORD originalFnPtrAddr, DWORD hookFn, DWORD& originalFnPtrStore);
	static bool ReplaceWithNoOps(const DWORD address, size_t size);
	static bool ReplaceWithNoOps(HookStruct& hookStruct, bool revert = false);
	static bool ReplaceMultipleWithNoOps(HookStruct* hookStructs, size_t count, bool revert = false);
};