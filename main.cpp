#include <windows.h>
#include <Xinput.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <winuser.h>

int main() {

	INPUT input;
	KEYBDINPUT keyIn;

	input.type = INPUT_KEYBOARD;
	keyIn.wVk = VK_MEDIA_NEXT_TRACK;
	keyIn.wScan = 0;
	keyIn.dwFlags = 0;
	keyIn.dwExtraInfo = 0;
	input.ki = keyIn;

	XINPUT_STATE gamepadState;
	WORD buttonState;

	ZeroMemory(&gamepadState, sizeof(XINPUT_STATE));

	bool pressed = false;
	int doubleCount = 0;

	while (1) {

		XInputGetState(0, &gamepadState);
		buttonState = gamepadState.Gamepad.wButtons;
		if (buttonState & XINPUT_GAMEPAD_BACK) {

			if (doubleCount) {

				SendInput(1, &input, sizeof(INPUT));
				pressed = false;
				doubleCount = 0;
				std::this_thread::sleep_for(std::chrono::seconds(1));

			}else {

				pressed = true;

			}

		}else {

			if (pressed) {

				if (!doubleCount) {

					pressed = false;
					doubleCount += 1;

				}

			}else {

				if (doubleCount > 0 && doubleCount < 7) {

					doubleCount += 1;

				}else {

					doubleCount = 0;

				}

			}

			std::this_thread::sleep_for(std::chrono::milliseconds(30));

		}

	}

}
