#pragma once

#include <unordered_map>

static inline const char* keys[] =
{
	"[none]",
	"[LMB]",
	"[RMB]",
	"[Control-break]",
	"[MMB]",
	"[X1 mouse]",
	"[X2 mouse]",
	"[unknown]",
	"[BACKSPACE]",
	"[TAB]",
	"[unknown]",
	"[unknown]",
	"[CLEAR]",
	"[ENTER]",
	"[unknown]",
	"[unknown]",
	"[SHIFT]",
	"[CTRL]",
	"[ALT]",
	"[PAUSE]",
	"[CAPS LOCK]",
	"[IME Kana]",
	"[unknown]",
	"[IME Junja]",
	"[IME final]",
	"[IME Hanja kanji]",
	"[unknown]",
	"[ESC]",
	"[IME]",
	"[IME]",
	"[IME]",
	"[IME mode change]",
	"[Space bar]",
	"[PAGE UP]",
	"[PAGE DOWN]",
	"[END]",
	"[HOME]",
	"[LEFT ARROW]",
	"[UP ARROW]",
	"[RIGHT ARROW]",
	"[DOWN ARROW]",
	"[SELECT]",
	"[PRINT]",
	"[EXECUTE]",
	"[PRINT SCREEN]",
	"[INS]",
	"[DEL]",
	"[HELP]",
	"[0]",
	"[1]",
	"[2]",
	"[3]",
	"[4]",
	"[5]",
	"[6]",
	"[7]",
	"[8]",
	"[9]",
	"[unknown]",
	"[unknown]",
	"[unknown]",
	"[unknown]",
	"[unknown]",
	"[unknown]",
	"[unknown]",
	"[A]",
	"[B]",
	"[C]",
	"[D]",
	"[E]",
	"[F]",
	"[G]",
	"[H]",
	"[I]",
	"[J]",
	"[K]",
	"[L]",
	"[M]",
	"[N]",
	"[O]",
	"[P]",
	"[Q]",
	"[R]",
	"[S]",
	"[T]",
	"[U]",
	"[V]",
	"[W]",
	"[X]",
	"[Y]",
	"[Z]",
	"[Left Windows]",
	"[Right Windows]",
	"[Applications]",
	"[Reserved]",
	"[Computer Sleep]",
	"[NumPad 0]",
	"[NumPad 1]",
	"[NumPad 2]",
	"[NumPad 3]",
	"[NumPad 4]",
	"[NumPad 5]",
	"[NumPad 6]",
	"[NumPad 7]",
	"[NumPad 8]",
	"[NumPad 9]",
	"[Multiply]",
	"[ADD]",
	"[Separator]",
	"[Subtract]",
	"[Decimal]",
	"[Divide]",
	"[F1]",
	"[F2]",
	"[F3]",
	"[F4]",
	"[F5]",
	"[F6]",
	"[F7]",
	"[F8]",
	"[F9]",
	"[F10]",
	"[F11]",
	"[F12]",
	"[F13]",
	"[F14]",
	"[F15]",
	"[F16]",
	"[F17]",
	"[F18]",
	"[F19]",
	"[F20]",
	"[F21]",
	"[F22]",
	"[F23]",
	"[F24]",
	"[unassigned]",
	"[unassigned]",
	"[unassigned]",
	"[unassigned]",
	"[unassigned]",
	"[unassigned]",
	"[unassigned]",
	"[unassigned]",
	"[NUM LOCK]",
	"[SCROLL LOCK]",
	"[OEM specific]",
	"[OEM specific]",
	"[OEM specific]",
	"[OEM specific]",
	"[OEM specific]",
	"[unassigned]",
	"[unassigned]",
	"[unassigned]",
	"[unassigned]",
	"[unassigned]",
	"[unassigned]",
	"[unassigned]",
	"[unassigned]",
	"[unassigned]",
	"[LSHIFT]",
	"[RSHIFT]",
	"[LCONTROL]",
	"[RCONTROL]",
	"[LMENU]",
	"[RMENU]",
	"[Back]",
	"[Forward]",
	"[Refresh]",
	"[Stop]",
	"[Search]",
	"[Favorites]",
	"[Start]",
	"[Volume Down]",
	"[Volume Mute]",
	"[Volume Up]",
	"[Next Track]",
	"[Previous Track]",
	"[Stop Media]",
	"[Play/Pause]",
	"[Start Mail]",
	"[Select Media]",
	"[Application 1]",
	"[Application 2]",
	"[reserved]",
	"[reserved]",
	"[;]",
	"[=]",
	"[,]",
	"[-]",
	"[']",
	"[/]",
	"[`]",
	"[Reserved]",
	"[Reserved]",
	"[Reserved]",
	"[Reserved]",
	"[Reserved]",
	"[Reserved]",
	"[Reserved]",
	"[Reserved]",
	"[Reserved]",
	"[Reserved]",
	"[Reserved]",
	"[Reserved]",
	"[Reserved]",
	"[Reserved]",
	"[Reserved]",
	"[Reserved]",
	"[Reserved]",
	"[Reserved]",
	"[Reserved]",
	"[Reserved]",
	"[Reserved]",
	"[Reserved]",
	"[Unassigned]",
	"[Unassigned]",
	"[Unassigned]",
	"[Unassigned]",
	"[[]",
	"[\\]",
	"[]]",
	"[']",
	"[OEM8]",
	"[Reserved]",
	"[OEM specific]",
	"[\\]",
	"[OEM specific]",
	"[OEM specific]",
	"[PROCESS]",
	"[OEM specific]",
	"[packet]",
	"[Unassigned]",
	"[OEM specific]",
	"[OEM specific]",
	"[OEM specific]",
	"[OEM specific]",
	"[OEM specific]",
	"[OEM specific]",
	"[OEM specific]",
	"[OEM specific]",
	"[OEM specific]",
	"[OEM specific"
	"[Attn]",
	"[CrSel]",
	"[ExSel]",
	"[Erase EOF]",
	"[Play]",
	"[Zoom]",
	"[reserved]",
	"[PA1 key]",
	"[clear]",
};

struct Keys
{
	static inline std::unordered_map<int, bool> keyStates;
	static bool IsKeyPressed(int key)
	{
		bool currentState = GetAsyncKeyState(key) & 0x8000;
		keyStates[key] = currentState;

		return currentState;
	}

	static bool IsKeyReleased(int key)
	{
		bool currentState = GetAsyncKeyState(key) & 0x8000;
		keyStates[key] = currentState;

		return !currentState;
	}

	static bool IsKeyPressedOnce(int key)
	{
		bool currentState = GetAsyncKeyState(key) & 0x8000;
		bool prevState = keyStates[key];
		keyStates[key] = currentState;

		return currentState && !prevState;
	}

	static bool IsKeyReleasedOnce(int key)
	{
		bool currentState = GetAsyncKeyState(key) & 0x8000;
		bool prevState = keyStates[key];
		keyStates[key] = currentState;

		return prevState && !currentState;
	}

	static bool IsKeyHeld(int key)
	{
		bool currentState = GetAsyncKeyState(key) & 0x8000;
		bool prevState = keyStates[key];
		keyStates[key] = currentState;

		return currentState && prevState;
	}

	static bool IsKeyNotHeld(int key)
	{
		bool currentState = GetAsyncKeyState(key) & 0x8000;
		bool prevState = keyStates[key];
		keyStates[key] = currentState;

		return !currentState && !prevState;
	}

	static const char* GetKeyName(int key)
	{
		if (key < 0 || key >= sizeof(keys) / sizeof(keys[0]))
			return "[unknown]";

		return keys[key];
	}

	static bool IsMouseButtonUp(UINT msg)
	{
		return msg == WM_LBUTTONUP || msg == WM_RBUTTONUP || msg == WM_MBUTTONUP || msg == WM_XBUTTONUP;
	}

	static bool IsMouseMoving()
	{
		static POINT lastMousePos;
		POINT currentMousePos;
		GetCursorPos(&currentMousePos);

		if (lastMousePos.x == currentMousePos.x && lastMousePos.y == currentMousePos.y)
		{
			return false;
		}

		lastMousePos = currentMousePos;
		return true;
	}

	inline static void SendKey(WORD vkKey, bool sendDown = true)
	{
		static INPUT ip{ INPUT_KEYBOARD };

		ip.ki.wScan = 0;
		ip.ki.time = 0;
		ip.ki.dwExtraInfo = 0;
		ip.ki.wVk = vkKey;
		ip.ki.dwFlags = sendDown ? 0 : KEYEVENTF_KEYUP;

		SendInput(1, &ip, sizeof(INPUT));
	}

	static void SendKey(HWND hWnd, WORD vkKey, bool sendDown = true)
	{
		if (sendDown)
		{
			PostMessage(hWnd, WM_KEYDOWN, vkKey, static_cast<LPARAM>(MapVirtualKey(vkKey, 0) << 16));
		}
		else
		{
			PostMessage(hWnd, WM_KEYUP, vkKey, (static_cast<LPARAM>(MapVirtualKey(vkKey, 0)) << 16) | (static_cast<long long>(1) << 30) | (static_cast<long long>(1) << 31));
		}
	}
};