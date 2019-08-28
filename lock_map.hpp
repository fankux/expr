
#pragma once

#include <unistd.h>
#include <pthread.h>
#include <thread>
#include <ostream>
#include "util.hpp"

template<class T>
class FListNode {
public:
    template<class X> friend
    class FList;

    FListNode() = default;

    virtual ~FListNode() {
        _prev = nullptr;
        _next = nullptr;
    }

    explicit FListNode(const T& data) : _data(data) {}

    T& data() {
        return _data;
    }

    FListNode* next() {
        return _prev;
    };

    FListNode* prev() {
        return _prev;
    };

    friend LogStream& operator<<(LogStream& ls, const FListNode& lock) {
        ls << lock._data;
        return ls;
    }

private:
    FListNode* _prev = nullptr;
    FListNode* _next = nullptr;
    T _data;
};

template<class T>
class FList {

public:
    explicit FList(const size_t max_len = 0) {
        _max_len = max_len;
    }

    virtual ~FList() {
        clear();
    }

    inline void clear() {
        FListNode<T>* p = _head;
        FListNode<T>* q = p;
        for (size_t i = _len; i > 0; --i) {
            p = p->_next;
            free(q);
            q = p;
        }
        _len = 0;
    }

    inline size_t size() {
        return _len;
    }

    inline bool isfull() {
        return _max_len != 0 && _len >= _max_len;
    }

    inline bool isempty() {
        return _len == 0;
    }

    inline bool add_tail(const T& data) {
        if (isfull()) {
            return false;
        }

        FListNode<T>* node = new(std::nothrow) FListNode<T>(data);
        if (node == nullptr) {
            return false;
        }

        return add_tail(node);
    }

    inline bool add_tail(FListNode<T>* node) {
        if (isfull()) {
            return false;
        }

        if (isempty()) {
            node->_prev = nullptr;
            node->_next = nullptr;
            _tail = node;
            _head = _tail;
        } else {
            node->_next = nullptr;
            node->_prev = _tail;
            _tail->_next = node;
            _tail = _tail->_next;
        }
        ++_len;

        return true;
    }

    inline bool add_head(const T& data) {
        if (isfull()) {
            return false;
        }

        FListNode<T>* node = new(std::nothrow) FListNode<T>(data);
        if (node == nullptr) {
            return false;
        }

        return add_head(node);
    }

    inline bool add_head(FListNode<T>* node) {
        if (isfull()) {
            return false;
        }

        if (isempty()) {
            node->_prev = nullptr;
            node->_next = nullptr;
            _head = node;
            _tail = _head;
        } else {
            node->_prev = nullptr;
            node->_next = _head;
            _head->_prev = node;
            _head = _head->_prev;
        }
        ++_len;
    }

    inline bool insert_after(FListNode<T>* pos, const T& data) {
        if (isfull()) {
            return false;
        }

        FListNode<T>* node = new(std::nothrow) FListNode<T>(data);
        if (node == nullptr) {
            return false;
        }

        if (pos == nullptr) {
            return add_head(node);
        }

        if (pos->_next == nullptr) {
            return add_tail(node);
        }

        node->_prev = pos;
        node->_next = pos->_next;
        pos->_next->_prev = pos;
        pos->_next = pos;
        return true;
    }

    inline FListNode<T>* pop_head() {
        if (isempty()) {
            return nullptr;
        }

        FListNode<T>* p = nullptr;
        if (_len == 1) { /* last one node */
            p = _head;
            _head = nullptr;
            _tail = nullptr;
        } else {
            p = _head;
            _head = _head->_next;
            _head->_prev = nullptr;

        }
        --_len;
        return p;
    }

    inline void detach(FListNode<T>* p) {
        if (_len == 1) {
            _head = nullptr;
            _tail = nullptr;
        } else {
            if (p->_prev == nullptr) {
                _head = p->_next;
                p->_next->_prev = nullptr;
            } else if (p->_next == nullptr) {
                _tail = p->_prev;
                p->_prev->_next = nullptr;
            } else {
                p->_next->_prev = p->_prev;
                p->_prev->_next = p->_next;
            }
        }
        --_len;
    }

    inline FListNode<T>* head() {
        return _head;
    }

    inline FListNode<T>* tail() {
        return _tail;
    }

private:
    size_t _max_len = 0;
    size_t _len = 0;
    FListNode<T>* _head = nullptr;
    FListNode<T>* _tail = nullptr;
};

struct LruItem {
    std::string key;

    friend LogStream& operator<<(LogStream& ls, const LruItem& t) {
        ls << t.key;
        return ls;
    }
};

struct Lock {
    pthread_mutex_t mutex;
    FListNode<LruItem>* node_ref;

    friend LogStream& operator<<(LogStream& ls, const Lock& lock) {
        ls << " node_ref:" << *lock.node_ref;
        return ls;
    }
};

typedef std::unordered_map<std::string, Lock>::iterator LocKV;

class LockMap {
public:
    explicit LockMap(const uint32_t max_size) : _max_size(max_size) {}

    bool lock(const std::string& key) {
        pthread_mutex_lock(&_lock);

        Lock lck;
        LruItem item;
        item.key = key;
        LocKV kv = _map.find(key);
        if (kv == _map.end()) {
            // add new one
            if (!_lru.add_tail(item)) {
                pthread_mutex_unlock(&_lock);
                return false;
            }

            lck.mutex = PTHREAD_MUTEX_INITIALIZER;
            lck.node_ref = _lru.tail();

            _map[key] = lck;

            pthread_mutex_unlock(&_lock);
            pthread_mutex_lock(&_map[key].mutex);

        } else {
            _lru.detach(kv->second.node_ref);
            _lru.add_tail(kv->second.node_ref);

            pthread_mutex_unlock(&_lock);
            pthread_mutex_lock(&kv->second.mutex);
        }
        return true;
    }

    bool unlock(const std::string& key) {
        pthread_mutex_lock(&_lock);

        LocKV kv = _map.find(key);
        if (kv == _map.end()) {
            pthread_mutex_unlock(&_lock);
            return false;
        }

        pthread_mutex_unlock(&kv->second.mutex);

        if (_map.size() > _max_size) {
            if (_lru.head()->data().key == kv->first) {
                _map.erase(kv);
            }
            FListNode<LruItem>* node = _lru.pop_head();
            free(node);
        }

        pthread_mutex_unlock(&_lock);
        return true;
    }

public:
    uint32_t _max_size;
    pthread_mutex_t _lock = PTHREAD_MUTEX_INITIALIZER;
    FList<LruItem> _lru;
    std::unordered_map<std::string, Lock> _map;
};

//FTEST(test_lock_map) {
void test_lock_map() {
    LockMap lm(1000);

    volatile int count = 0;

    int size = 1001;
    for (int i = 0; i < size; ++i) {
        std::thread([i, &lm, &count] {
            std::string key = std::to_string(i);
            lm.lock(key);
            __sync_add_and_fetch(&count, 1);

            lm.lock(key);
            LOG(INFO) << i << " unlock";


        }).detach();
    }

    for (int i = 0; i < size; ++i) {
        std::thread([i, &lm] {
            std::string key = std::to_string(i);
            lm.unlock(key);
        }).detach();
    }

    while (count != size) {
        sleep(1);
    }
    LOG(INFO) << "lock map done" << lm._map;

    while (true) {
        sleep(5);
    }
}