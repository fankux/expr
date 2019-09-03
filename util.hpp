
#pragma once

#include <ostream>
#include <sstream>
#include <functional>
#include <vector>
#include <deque>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

static std::map<std::string, std::function<void()>> g_test_list;

#define FTEST(name)                                 \
void name();                                        \
class Test##name {                                  \
public:                                             \
    explicit Test##name(const std::string& n) {     \
        g_test_list.emplace(n, name);               \
    }                                               \
};                                                  \
static Test##name _test_clazz_##name(#name);        \
void name()

class LogStream {
public:
    explicit LogStream(int level) : _level(level) {
        if (_level == 1) {
            _level_str = "[INFO] ";
        } else if (_level == 2) {
            _level_str = "[WARN] ";
        } else if (_level == 3) {
            _level_str = "[FATAL] ";
        }
    }

    ~LogStream() {
        flush();
    }

    inline LogStream& operator<<(int16_t val) {
        _ss << val;
        return *this;
    }

    inline LogStream& operator<<(int val) {
        _ss << val;
        return *this;
    }

    inline LogStream& operator<<(int64_t val) {
        _ss << val;
        return *this;
    }

    inline LogStream& operator<<(uint16_t val) {
        _ss << val;
        return *this;
    }

    inline LogStream& operator<<(uint32_t val) {
        _ss << val;
        return *this;
    }

    inline LogStream& operator<<(uint64_t val) {
        _ss << val;
        return *this;
    }

    inline LogStream& operator<<(float val) {
        _ss << val;
        return *this;
    }

#ifdef __APPLE__

    inline LogStream& operator<<(size_t val) {
        _ss << val;
        return *this;
    }

    inline LogStream& operator<<(ssize_t val) {
        _ss << val;
        return *this;
    }

#endif

    inline LogStream& operator<<(double val) {
        _ss << val;
        return *this;
    }

    inline LogStream& operator<<(const std::string& val) {
        _ss << val;
        return *this;
    }

    template<typename T>
    inline LogStream& operator<<(const std::vector<T>& t) {
        iter_list(t);
        return *this;
    }

    template<typename T>
    inline LogStream& operator<<(const std::deque<T>& t) {
        iter_list(t);
        return *this;
    }

    template<typename T>
    inline LogStream& operator<<(const std::list<T>& t) {
        iter_list(t);
        return *this;
    }

    template<typename T>
    inline LogStream& operator<<(const std::set<T>& t) {
        iter_list(t);
        return *this;
    }

    template<typename T>
    inline LogStream& operator<<(const std::unordered_set<T>& t) {
        iter_list(t);
        return *this;
    }

    template<typename K, typename V>
    inline LogStream& operator<<(const std::map<K, V>& t) {
        iter_kv(t);
        return *this;
    }

    template<typename K, typename V>
    inline LogStream& operator<<(const std::unordered_map<K, V>& t) {
        iter_kv(t);
        return *this;
    }

    template<typename T>
    void iter_list(const T& t) {
        *this << "[";
        size_t i = 0;
        for (auto iter = t.begin(); iter != t.end(); ++iter) {
            *this << *iter;
            if (i++ != t.size() - 1) {
                *this << ",";
            }
        }
        *this << "]";
    }

    template<typename T>
    void iter_kv(const T& t) {
        *this << "{";
        size_t i = 0;
        for (auto iter = t.begin(); iter != t.end(); ++iter) {
            *this << "(" << iter->first << "," << iter->second << ")";
            if (i++ != t.size() - 1) {
                *this << ",";
            }
        }
        *this << "}";
    }

    void flush() {
        std::cout << _level_str << _ss.str() << std::endl;
        _ss.clear();
    }

private:
    std::stringstream _ss;
    int _level;
    std::string _level_str;
};

template<typename T>
class LogMessage {
public:
    explicit LogMessage(int line, int level) {
        if (_stream == nullptr) {
            _stream = new T(level);
        }
    }

    ~LogMessage() {
        if (_stream != nullptr) {
            _stream->flush();
        }
    }

    T& stream() {
        return *_stream;
    }

private:
    T* _stream = nullptr;
    int _level = 0;
};

#define LOG_INFO LogMessage<LogStream>(__LINE__, 1).stream()
#define LOG(level)  LOG_##level

FTEST(test_util) {
    LOG(INFO) << 9999;
    LOG(INFO) << std::vector<std::string>{"5", "8", "6", "4", "7"};
    LOG(INFO) << std::list<std::string>{"5", "8", "6", "4", "7"};
    LOG(INFO) << std::deque<std::string>{"5", "8", "6", "4", "7"};
    LOG(INFO) << std::set<std::string>{"5", "8", "6", "4", "7"};
    LOG(INFO) << std::unordered_set<std::string>{"5", "8", "6", "4", "7"};
    LOG(INFO) << std::map<int, std::string>{{10, "10"}, {20, "20"}};
    LOG(INFO) << std::unordered_map<int, std::string>{{10, "10"}, {20, "20"}};

    LOG(INFO) << 9999 << std::vector<std::string>{"5", "8", "6", "4", "7"}
            << std::list<std::string>{"5", "8", "6", "4", "7"}
            << std::deque<std::string>{"5", "8", "6", "4", "7"}
            << std::set<std::string>{"5", "8", "6", "4", "7"}
            << std::unordered_set<std::string>{"5", "8", "6", "4", "7"}
            << std::map<int, std::string>{{10, "10"}, {20, "20"}}
            << std::unordered_map<int, std::string>{{10, "10"}, {20, "20"}};

}