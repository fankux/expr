
#include <ostream>
#include <sstream>
#include <vector>
#include <deque>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

class LogStream {
public:
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

    inline LogStream& operator<<(size_t val) {
        _ss << val;
        return *this;
    }

    inline LogStream& operator<<(ssize_t val) {
        _ss << val;
        return *this;
    }

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
        std::cout << _ss.str() << std::endl;
        _ss.clear();
    }

private:
    std::stringstream _ss;
};

template<typename T>
class LogMessage {
public:
    explicit LogMessage(int line) {
        if (_stream == nullptr) {
            _stream = new T();
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
};

#define LOG()  LogMessage<LogStream>(__LINE__).stream()

void test_util() {

    size_t idx = 9999;
    LOG() << idx;
    LOG() << std::vector<std::string>{"5", "8", "6", "4", "7"};
    LOG() << std::list<std::string>{"5", "8", "6", "4", "7"};
    LOG() << std::deque<std::string>{"5", "8", "6", "4", "7"};
    LOG() << std::set<std::string>{"5", "8", "6", "4", "7"};
    LOG() << std::unordered_set<std::string>{"5", "8", "6", "4", "7"};
    LOG() << std::map<int, std::string>{{10, "10"}, {20, "20"}};
    LOG() << std::unordered_map<int, std::string>{{10, "10"}, {20, "20"}};

    LOG() << idx << std::vector<std::string>{"5", "8", "6", "4", "7"}
            << std::list<std::string>{"5", "8", "6", "4", "7"}
            << std::deque<std::string>{"5", "8", "6", "4", "7"}
            << std::set<std::string>{"5", "8", "6", "4", "7"}
            << std::unordered_set<std::string>{"5", "8", "6", "4", "7"}
            << std::map<int, std::string>{{10, "10"}, {20, "20"}}
            << std::unordered_map<int, std::string>{{10, "10"}, {20, "20"}};

}