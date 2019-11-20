#pragma once
#include <iostream>
#include <chrono>
#include <string>

struct Timer {

	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<float> duration;
	std::string name;

	Timer(std::string& name) : name(name) {
		start = std::chrono::high_resolution_clock::now();
	}

	~Timer() {
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;

		float ms = duration.count() * 1000.0f;
		std::cout << "Timer of " << name << " took " << ms << "ms" << std::endl;
	}
};