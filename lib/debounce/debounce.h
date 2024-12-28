// #pragma once

#include <Arduino.h>

class debounce
{
	public:
		debounce();
		debounce(int debounce_time);
		bool process(bool state);

		bool rising_edge();
		bool falling_edge();
		bool state();
	private:
		const unsigned long _debounce_time = 10;
		unsigned long _last_input_change;

		bool _state;

		bool _rising_edge;
		bool _falling_edge;
};