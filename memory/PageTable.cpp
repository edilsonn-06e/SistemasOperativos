
#include "PageTable.h"
#include <algorithm>

PageTable::PageTable(int framesCount, ReplacementPolicy* policy)
    : m_frames(framesCount, -1), m_policy(policy) {}

PageTable::~PageTable(){}

PageEvent PageTable::access(const std::vector<int>& refs, int idx){
    int page = refs[idx];
    // hit?
    for (int i=0;i<(int)m_frames.size();++i){
        if (m_frames[i]==page){
            return {idx, page, true, -1};
        }
    }
    // free?
    for (int i=0;i<(int)m_frames.size();++i){
        if (m_frames[i]==-1){
            m_frames[i]=page; m_faults++;
            return {idx, page, false, i};
        }
    }
    int victim = m_policy->pickVictim(m_frames, refs, idx);
    m_frames[victim] = page; m_faults++;
    return {idx, page, false, victim};
}
