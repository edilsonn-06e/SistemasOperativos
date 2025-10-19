
#pragma once
#include <vector>
#include <optional>

class ReplacementPolicy {
public:
    virtual ~ReplacementPolicy() = default;
    virtual int pickVictim(const std::vector<int>& frames,
                           const std::vector<int>& futureRefs,
                           int currentIndex) = 0;
};
