#pragma once
#include <chrono>
using namespace std::chrono;
// ∫¡√Î ±÷”
typedef time_point<system_clock, milliseconds> millisecClock_type;

class DateFormatter
{
public:
	static time_t now_s() {
		return system_clock::to_time_t(system_clock::now());
	}
	static time_t now_ms() {
		return time_point_cast<milliseconds>(system_clock::now()).time_since_epoch().count();
		// return system_clock::to_time_t(time_point_cast<milliseconds>(system_clock::now()));
	}
};

#include <thread>
typedef std::thread Thread;

#include <chrono>
// –›√ﬂ∫¡√Î
#define msleep(millsec) std::this_thread::sleep_for(std::chrono::milliseconds(millsec));
// –›√ﬂ√Î
#define ssleep(sec) std::this_thread::sleep_for(std::chrono::seconds(sec));

// Ãıº˛–›√ﬂ,µ•Œª√Î
static inline void sleep_if(volatile bool& condition, int sec) {
	auto t0 = DateFormatter::now_s();
	while (condition && (DateFormatter::now_s() - t0) < sec)
	{
		msleep(20);
	}
}
// Ãıº˛–›√ﬂ,µ•Œª∫¡√Î
static inline void usleep_if(volatile bool& condition, int millsec) {
	auto t0 = DateFormatter::now_ms();
	while (condition && (DateFormatter::now_ms() - t0) < millsec)
	{
		msleep(20);
	}
}