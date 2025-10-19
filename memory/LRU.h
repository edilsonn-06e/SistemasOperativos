
#pragma once
#include "ReplacementPolicy.h"
#include <unordered_map>

class LRU : public ReplacementPolicy {
public:
    int pickVictim(const std::vector<int>& frames,
                   const std::vector<int>&, int) override {
        // naive: evict frame 0 (placeholder); real impl would track recency
        return 0;
    }
};
