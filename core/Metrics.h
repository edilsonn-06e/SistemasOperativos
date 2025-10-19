
#pragma once
#include "Process.h"
#include <vector>
#include <numeric>

struct Metrics {
    double avgWT = 0;
    double avgTAT = 0;
    double avgRT = 0;

    static Metrics from(const std::vector<Process>& v) {
        Metrics m;
        if (v.empty()) return m;
        double n = static_cast<double>(v.size());
        double sumWT = 0, sumTAT = 0, sumRT = 0;
        for (const auto& p : v) {
            sumWT  += p.waitingTime;
            sumTAT += p.turnaroundTime;
            sumRT  += p.responseTime;
        }
        m.avgWT = sumWT / n;
        m.avgTAT = sumTAT / n;
        m.avgRT = sumRT / n;
        return m;
    }
};
