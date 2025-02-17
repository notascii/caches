#pragma once

#include <iostream>
#include <list>
#include <unordered_map>
#include <assert.h>


class LRUCache {
private:
    using KeyValuePair = std::pair<int, int>;
    using LRUList = std::list<KeyValuePair>;
    using LRUIterator = LRUList::iterator;
    using Cache = std::unordered_map<int, LRUIterator>;
    using CacheIterator = Cache::iterator;

    int capacity_;

    // map key to iterator in the list
    // (to have O(1) access to the pair in the list,
    // just by knowing the key)
    std::unordered_map<int, LRUIterator> map_key_lruiter_;
    //     ┌──────────┬─────────────┐
    //     │ int: key │ LRUIterator │──────────────┐
    //     ├──────────┼─────────────┤              │
    //     │ int: key │ LRUIterator │              │
    //     └──────────┴─────────────┘              │
    //                      │                      │
    //                      │                      │
    //                      🡳                      🡳
    //              ┌────────────────┐     ┌────────────────┐
    //     CACHE    │  KeyValuePair  │ ──🡲 │  KeyValuePair  │ ──🡲 ...
    //  (std::list) └────────────────┘     └────────────────┘
    LRUList lru_cache_;

public:
    LRUCache(int capacity);
    int get(int key);
    void put(int key, int value);

    void print();
};
