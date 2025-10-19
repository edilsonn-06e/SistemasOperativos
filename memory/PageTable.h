
#pragma once
#include <vector>
#include <optional>
#include "ReplacementPolicy.h"

struct PageEvent {
    int timeIndex;
    int page;
    bool hit;
    int victimIndex; // -1 if none
};

class PageTable {
public:
    PageTable(int framesCount, ReplacementPolicy* policy);
    ~PageTable();

    PageEvent access(const std::vector<int>& refs, int idx);
    const std::vector<int>& frames() const { return m_frames; }
    int faults() const { return m_faults; }
private:
    std::vector<int> m_frames; // -1 = empty
    ReplacementPolicy* m_policy;
    int m_faults = 0;
};
