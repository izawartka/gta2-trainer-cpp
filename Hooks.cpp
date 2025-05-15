#include "pch.h"
#include "hooks.h"
#include "MainWindow.h"

__declspec(naked) void Hooks::gameTick(void) {
	// this will be replaced by original 5 bytes
	__asm {
		NOP
		NOP
		NOP
		NOP
		NOP
		NOP
		NOP
		NOP
	}

	// OutputDebugStringA("gameTick\n");
	MainWindow::m_instance->OnGTAGameTick((Game*)*(DWORD*)ptrToGame);

	__asm {
		MOV EAX, pGameTick
		add eax, 5
		JMP EAX
	}

}

__declspec(naked) void Hooks::drawChat(void) {
	// this will be replaced by original 5 bytes
	__asm {
		NOP
		NOP
		NOP
		NOP
		NOP
		NOP
		NOP
		NOP
	}

	// OutputDebugStringA("draw\n");
	MainWindow::m_instance->OnGTADraw();

	__asm {
		mov eax, pDrawChat
		add eax, 5
		jmp eax
	}

}

__declspec(naked) void Hooks::afterDebugFlags(LPCSTR stringVal) {
	// this will be replaced by original 5 bytes
	__asm {
		NOP
		NOP
		NOP
		NOP
		NOP
		NOP
		NOP
		NOP
	}

	MainWindow::m_instance->OnGTAAfterDebugFlags();

	__asm {
		MOV EAX, pAfterDebugFlags
		add eax, 5
		JMP EAX
	}

}
