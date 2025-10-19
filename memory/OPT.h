
#pragma once
#include "ReplacementPolicy.h"

class OPT : public ReplacementPolicy {
public:
    int pickVictim(const std::vector<int>& frames,
                   const std::vector<int>& futureRefs,
                   int currentIndex) override {
        // look ahead to farthest future use (simplified)
        int farthest = -1, idx = 0, victim = 0;
        for (int i=0;i<(int)frames.size();++i){
            int f = frames[i];
            int j = currentIndex+1;
            for (; j<(int)futureRefs.size(); ++j) if (futureRefs[j]==f) break;
            if (j==(int)futureRefs.size()) return i; // never used again
            if (j > farthest){ farthest = j; victim = i; }
        }
        return victim;
    }
};
