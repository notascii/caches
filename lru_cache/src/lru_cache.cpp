#include "lru_cache.hpp"


LRUCache::LRUCache(int capacity) : capacity_(capacity) {
    assert(capacity_ >= 2);
}


int LRUCache::get(int key) {
    // get iterator to element in the list
    CacheIterator it = map_key_lruiter_.find(key);

    if (it == map_key_lruiter_.end()) {
        return -1;
    }

    // move element 'it' to front of list
    lru_cache_.splice(
        lru_cache_.begin(), // pos
        lru_cache_,         // list from where elements are to be transferred
        it->second          // iterator to the element to be transferred
    );

    return it->second->second; // value
}


void LRUCache::put(int key, int value) {
    if ( map_key_lruiter_.find(key) != map_key_lruiter_.end() ) {
        // key already in the cache, update value and move to front
        auto it = map_key_lruiter_.find(key);
        LRUIterator key_value = it->second;

        key_value->second = value; // update value
        lru_cache_.splice(
            lru_cache_.begin(),
            lru_cache_,
            key_value
        ); // move to front
        return;
    }

    if ( (int)(lru_cache_.size()) == capacity_ ) {
        // evict last one in cache
        int key_last = lru_cache_.back().first;
        map_key_lruiter_.erase(key_last);
        lru_cache_.pop_back();
        assert((int)(lru_cache_.size()) == capacity_ - 1);
    }

    lru_cache_.push_front({ key, value });
    map_key_lruiter_[key] = lru_cache_.begin();

    return;
}


void LRUCache::print() {
    LRUIterator pair;

    std::cout << "{ ";
    for (pair = lru_cache_.begin() ; pair != lru_cache_.end() ; ) {
        std::cout << pair->first << "="  << pair->second << " ";
        if (++pair != lru_cache_.end()) {
            std::cout << ", ";
        }
    }
    std::cout << "}" << std::endl;
}
