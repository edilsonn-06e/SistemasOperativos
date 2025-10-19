
#pragma once
#include "ReplacementPolicy.h"
#include <queue>

class FIFO : public ReplacementPolicy {
    int ptr = 0;
public:
    int pickVictim(const std::vector<int>& frames,
                   const std::vector<int>&, int) override {
        int victim = ptr % (int)frames.size();
        ptr = (ptr + 1) % (int)frames.size();
        return victim;
    }
};
