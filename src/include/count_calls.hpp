#pragma once

#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

template<unsigned id, unsigned duration_ms>
static void count_calls(string label = "") {
    static auto     time1 = system_clock::now();
    static auto     dur1  = duration<unsigned, milli>(duration_ms);
    static unsigned calls = 0;
    auto        time2 = system_clock::now();
    auto        dur2  = time2 - time1;
    ++calls;
    if (dur2 >= dur1) {
        cerr << label << "\t" << calls
             << "\t(count calls " << id << ")"
             << endl;
        calls = 0;
        time1 = time2;
    }
}
