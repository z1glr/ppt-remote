#include <Arduino.h>

#include <USBKeyboard.h>

#include <debounce.h>

#define PIN_PREV 18
#define PIN_NEXT 19

// Default-Remote-Emulation
#define KEY_PREV keyboard.key_code(KEY_PAGE_UP, 0)
#define KEY_NEXT keyboard.key_code(KEY_PAGE_DOWN, 0)

// #define KEY_PREV keyboard.key_code('J', KEY_CTRL | KEY_SHIFT)
// #define KEY_NEXT keyboard.key_code('L', KEY_CTRL | KEY_SHIFT)

#define CYCLE_TIME 1000

void irpt_btn_prev();
void irpt_btn_next();

debounce i_bo_btn_prev;
debounce i_bo_btn_next;

bool _i_bo_btn_prev;
bool _i_bo_btn_next;

USBKeyboard keyboard;

void setup() {
	pinMode(PIN_PREV, INPUT);
	pinMode(PIN_NEXT, INPUT);

	attachInterrupt(digitalPinToInterrupt(PIN_PREV), irpt_btn_prev, CHANGE);
	attachInterrupt(digitalPinToInterrupt(PIN_NEXT), irpt_btn_next, CHANGE);
}

void loop() {
	unsigned long t_micros_start = micros();

	i_bo_btn_prev.process(_i_bo_btn_prev);
	i_bo_btn_next.process(_i_bo_btn_next);

	if (i_bo_btn_prev.rising_edge()) {
		KEY_PREV;
	}

	if (i_bo_btn_next.rising_edge()) {
		KEY_NEXT;
	}

	unsigned long sleep_delay = (micros() - t_micros_start);

	if (sleep_delay < CYCLE_TIME) {
		delay((CYCLE_TIME - sleep_delay) / 1000);
	}
}

void irpt_btn_prev() {
	_i_bo_btn_prev = !digitalRead(PIN_PREV);
}

void irpt_btn_next() {
	_i_bo_btn_next = !digitalRead(PIN_NEXT);	
}
