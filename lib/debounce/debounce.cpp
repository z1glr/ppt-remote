#include "debounce.h"

debounce::debounce(): debounce(INPUT) {

}

debounce::debounce(int debounce_time): _debounce_time(debounce_time) {
}

bool debounce::process(bool state) {
	_rising_edge = false;
	_falling_edge = false;

	if (state != _state) {
		unsigned long this_input_change = millis();

		if (this_input_change - _last_input_change > _debounce_time) {
			_state = state;

			if (state) {
				_rising_edge = true;
			} else {
				_falling_edge = true;
			}

			_last_input_change = this_input_change;
		}
	}

	return state;
}

bool debounce::rising_edge() {
	return _rising_edge;
}

bool debounce::falling_edge() {
	return _falling_edge;
}

bool debounce::state() {
	return _state;
}