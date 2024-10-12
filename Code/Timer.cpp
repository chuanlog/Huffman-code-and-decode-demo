#include "Timer.h"

Timer::Timer() : start_time(), end_time(), running(false) {}

void Timer::start() {
    start_time = chrono::high_resolution_clock::now();
    running = true;
}

void Timer::stop() {
    if (running) {
        end_time = chrono::high_resolution_clock::now();
        running = false;
    }
}

double Timer::timeCost() {
    if (running) {
        stop(); // 如果计时器仍在运行，则先停止
    }
    return chrono::duration<double, milli>(end_time - start_time).count();
}

void Timer::reset() {
    start_time = chrono::high_resolution_clock::now();
    end_time = start_time;
    running = false;
}

