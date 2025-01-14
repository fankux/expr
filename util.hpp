
#pragma once

#include <iostream>
#include <sstream>
#include <functional>
#include <vector>
#include <deque>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <sys/time.h>

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

#define FEXP(cond, expect) do {                     \
auto c = (cond);                                    \
if (c != (expect)) {                                \
    LOG(FATAL) << "\nError Condition: "             \
              << (#cond) << "\n Real: " << c        \
              << "\n Expected: " << expect;         \
    throw std::exception();                         \
}} while (0)

class LogStream {
public:
    explicit LogStream(int level, const std::string& file, uint32_t line) : _level(level) {
        if (_level == 1) {
            _level_str = "[INFO][" + file + ":" + std::to_string(line) + "]";
        } else if (_level == 2) {
            _level_str = "[WARN][" + file + ":" + std::to_string(line) + "]";
        } else if (_level == 3) {
            _level_str = "[FATAL][" + file + ":" + std::to_string(line) + "]";
        }
    }

    ~LogStream() {
        flush();
    }

    inline LogStream& operator<<(char val) {
        _ss << val;
        return *this;
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

    template<typename K, typename V>
    inline LogStream& operator<<(const std::pair<K, V>& t) {
        *this << "<" << t.first << "," << t.second << ">";
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
    explicit LogMessage(int level, const std::string& file, uint32_t line) {
        if (_stream == nullptr) {
            _stream = new T(level, file, line);
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

#define LOG_INFO LogMessage<LogStream>(1, __FILE__, __LINE__).stream()
#define LOG_WARN LogMessage<LogStream>(2, __FILE__, __LINE__).stream()
#define LOG_FATAL LogMessage<LogStream>(3, __FILE__, __LINE__).stream()
#define LOG(level) LOG_##level

class Timer {
public:
    Timer() {
        reset();
    }

    inline void reset() {
        struct timeval tm;
        gettimeofday(&tm, nullptr);
        _start_time = tm.tv_sec * 1000000 + tm.tv_usec;
    }

    inline uint64_t start_time() {
        return _start_time;
    }

    static inline uint64_t now() {
        struct timeval tm;
        gettimeofday(&tm, nullptr);
        return (tm.tv_sec * 1000000 + tm.tv_usec);
    }

    inline int64_t elapsed() {
        return now() - _start_time;
    }

private:
    uint64_t _start_time = 0;
};

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


class LineReader {
public:
    // trim from start (in place)
    static inline void ltrim(std::string& s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                std::not1(std::ptr_fun<int, int>(std::isspace))));
    }

    // trim from end (in place)
    static inline void rtrim(std::string& s) {
        s.erase(std::find_if(s.rbegin(), s.rend(),
                std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    }

    // trim from both ends (in place)
    static inline void trim(std::string& s) {
        ltrim(s);
        rtrim(s);
    }

    // trim from start (copying)
    static inline std::string ltrim_copy(std::string s) {
        ltrim(s);
        return s;
    }

    // trim from end (copying)
    static inline std::string rtrim_copy(std::string s) {
        rtrim(s);
        return s;
    }

    // trim from both ends (copying)
    static inline std::string trim_copy(std::string s) {
        trim(s);
        return s;
    }

    static int line_int() {
        std::string line;
        std::getline(std::cin, line);
        ltrim(line);
        try {
            return std::stoi(line);
        } catch (...) {
            return 0;
        }
    }

    static uint32_t line_uint() {
        std::string line;
        std::getline(std::cin, line);
        ltrim(line);
        try {
            return std::stoul(line);
        } catch (...) {
            return 0;
        }
    }

    static int64_t line_int64() {
        std::string line;
        std::getline(std::cin, line);
        ltrim(line);
        try {
            return std::stoll(line);
        } catch (...) {
            return 0;
        }
    }

    static uint64_t line_uint64() {
        std::string line;
        std::getline(std::cin, line);
        ltrim(line);
        try {
            return std::stoull(line);
        } catch (...) {
            return 0;
        }
    }

    static std::string line_str() {
        std::string line;
        std::getline(std::cin, line);
        trim(line);
        return line;
    }

    static void split(const std::string& str, std::vector<std::string>& cont,
            const std::string& delims = " ") {
        std::size_t current;
        std::size_t previous = 0;
        current = str.find(delims);
        while (current != std::string::npos) {
            if (previous < current) {
                cont.emplace_back(str.substr(previous, current - previous));
            }
            previous = current + 1;
            current = str.find(delims, previous);
        }
        if (previous < str.size()) {
            cont.emplace_back(str.substr(previous, current - previous));
        }
    }

    static std::vector<std::string> line_strs() {
        std::string line;
        std::getline(std::cin, line);
        trim(line);
        std::vector<std::string> res;
        split(line, res);
        return res;
    }

    static std::vector<int> line_ints() {
        std::vector<std::string> strs = line_strs();
        std::vector<int> res(strs.size());
        for (size_t i = 0; i < strs.size(); ++i) {
            res[i] = std::stoi(strs[i]);
        }
        return res;
    }
};

FTEST(test_LineReader) {
    LOG(INFO) << "str:" << LineReader::line_str();
    LOG(INFO) << "int:" << LineReader::line_int();
    LOG(INFO) << "uint:" << LineReader::line_uint();
    LOG(INFO) << "int64:" << LineReader::line_int64();
    LOG(INFO) << "uint64:" << LineReader::line_uint64();
    LOG(INFO) << "str array:" << LineReader::line_strs();
}
