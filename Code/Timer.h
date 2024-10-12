/*
 * 这是计时用的计时类，单位为ms
 * */
#pragma once
#include <iostream>
#include <chrono>

using namespace std;

class Timer {
public:
    Timer();

    void start();

    void stop();

    double timeCost();

    void reset();

private:
    chrono::high_resolution_clock::time_point start_time;//开始时间
    chrono::high_resolution_clock::time_point end_time;//结束时间
    bool running;//是否正在运行
};
