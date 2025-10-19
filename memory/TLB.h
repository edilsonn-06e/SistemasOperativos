
#pragma once
#include <unordered_map>
#include <list>

class TLB {
public:
    explicit TLB(size_t cap=8): cap(cap) {}
    bool find(int page){
        auto it = pos.find(page);
        if (it==pos.end()) return false;
        // move to front (LRU)
        l.erase(it->second);
        l.push_front(page);
        pos[page] = l.begin();
        return true;
    }
    void insert(int page){
        if (pos.count(page)) return;
        if (l.size()>=cap){
            int ev = l.back(); l.pop_back(); pos.erase(ev);
        }
        l.push_front(page); pos[page]=l.begin();
    }
private:
    size_t cap;
    std::list<int> l;
    std::unordered_map<int, std::list<int>::iterator> pos;
};
