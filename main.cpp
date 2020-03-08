#include "sums.hpp"
#include "tree.hpp"
#include "heap.hpp"
#include "sort.hpp"
#include "skiplist.hpp"
#include "subs.hpp"

#include "idx0.hpp"
#include "idx1.hpp"
#include "idx2.hpp"
#include "idx3.hpp"
#include "idx4.hpp"
#include "idx5.hpp"
#include "idx6.hpp"
#include "idx7.hpp"
#include "idx8.hpp"
#include "idx9.hpp"
#include "idx10.hpp"
#include "idx11.hpp"
#include "idx12.hpp"
#include "idx13.hpp"
#include "idx14.hpp"
#include "idx15.hpp"
#include "idx16.hpp"
#include "idx17.hpp"
#include "idx18.hpp"
#include "idx19.hpp"
#include "idx20.hpp"
#include "idx21.hpp"
#include "idx22.hpp"
#include "idx23.hpp"
#include "idx24.hpp"
#include "idx25.hpp"
#include "idx26.hpp"
#include "idx27.hpp"
#include "idx28.hpp"
#include "idx29.hpp"
#include "idx30.hpp"
#include "idx31.hpp"
#include "idx32.hpp"
#include "idx33.hpp"
#include "idx34.hpp"
#include "idx35.hpp"
#include "idx36.hpp"
#include "idx37.hpp"
#include "idx38.hpp"
#include "idx39.hpp"
#include "idx40.hpp"
#include "idx41.hpp"
#include "idx43.hpp"
#include "idx44.hpp"
#include "idx45.hpp"
#include "idx49.hpp"
#include "idx54.hpp"
#include "idx55.hpp"
#include "idx56.hpp"
#include "idx58.hpp"
#include "idx61.hpp"
#include "idx62.hpp"
#include "idx64.hpp"
#include "idx73.hpp"

using namespace LCIndex0;
using namespace LCIndex1;
using namespace LCIndex2;
using namespace LCIndex3;
using namespace LCIndex4;
using namespace LCIndex5;
using namespace LCIndex6;
using namespace LCIndex7;
using namespace LCIndex8;
using namespace LCIndex9;
using namespace LCIndex10;
using namespace LCIndex11;
using namespace LCIndex12;
using namespace LCIndex13;
using namespace LCIndex14;
using namespace LCIndex15;
using namespace LCIndex16;
using namespace LCIndex17;
using namespace LCIndex18;
using namespace LCIndex19;
using namespace LCIndex20;
using namespace LCIndex21;
using namespace LCIndex22;
using namespace LCIndex23;
using namespace LCIndex24;
using namespace LCIndex25;
using namespace LCIndex26;
using namespace LCIndex27;
using namespace LCIndex28;
using namespace LCIndex29;
using namespace LCIndex30;
using namespace LCIndex31;
using namespace LCIndex32;
using namespace LCIndex33;
using namespace LCIndex34;
using namespace LCIndex35;
using namespace LCIndex36;
using namespace LCIndex37;
using namespace LCIndex38;
using namespace LCIndex39;
using namespace LCIndex40;
using namespace LCIndex41;
using namespace LCIndex43;
using namespace LCIndex44;
using namespace LCIndex45;
using namespace LCIndex49;
using namespace LCIndex54;
using namespace LCIndex55;
using namespace LCIndex56;
using namespace LCIndex58;
using namespace LCIndex61;
using namespace LCIndex62;
using namespace LCIndex64;
using namespace LCIndex73;

using namespace std;

vector<int> roundPricesToMatchTarget(const vector<float>& prices, int target) {
    size_t len = prices.size();
    std::vector<std::pair<int, int>> collect(len);
    for (std::size_t i = 0; i < len; ++i) {
        collect.emplace_back(std::pair<int, int>{std::floor(prices[i]), std::ceil(prices[i])});
    }

    vector<int> res;

    float min_diff = (float) target + 1;
    vector<int> re;
    std::function<void(int, int)> r_func;
    r_func = [&](int sum, int start) {
        if (start >= len) {
            if (sum == 0) {
                float diff = 0;
                for (size_t k = 0; k < len; ++k) {
                    diff += std::abs((float) re[k] - prices[k]);
                }
                if (diff < min_diff) {
                    res = re;
                    min_diff = diff;
                }
            }
            return;
        }
        re.emplace_back(collect[start].first);
        r_func(sum - re.back(), start + 1);
        re.pop_back();

        re.emplace_back(collect[start].second);
        r_func(sum - re.back(), start + 1);
        re.pop_back();
    };
    r_func(target, 0);
    return res;
}

FTEST(test_roundPricesToMatchTarget) {
    LOG(INFO) << roundPricesToMatchTarget({0.7, 2.8, 4.9}, 8);
}

int consecutiveNumber(int n) {
    int res = 0;
    for (int i = 1; n > 0; n -= i, ++i) {
        res = (n % i == 0) ? i : res;
    }
    return res;
}

/**
 * max step whih
 * @param n
 * @param k
 * @return
 */
int maxStep(int n, int k) {
    std::vector<int> state(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        state[i] = state[i - 1] + ((state[i - 1] + i == k) ? 0 : i);
    }
    return state.back();
}

string validate_xml(string xml) {
    typedef enum {
        TEXT = 0,
        TAG_START_LEFT,
        TOKEN_START_LEFT,
        TAG_END_LEFT,
        TOKEN_START_RIGHT,
        TAG_END_RIGHT,
    } STATE;

    std::set<char> tokens = {'<', '>', '/'};

    STATE st = TEXT;
    std::stack<std::string> tq;

    std::string tag;
    size_t len = xml.size();
    for (size_t i = 0; i < len; ++i) {
        char c = xml[i];
        if (st == TEXT || st == TAG_END_LEFT || st == TAG_END_RIGHT) {
            if (c == '<') {
                st = TAG_START_LEFT;
            } else if (st == TEXT && c == '/') {
                // skip
            } else if (tokens.count(c) != 0) {
                return "parse error";
            } else {
                st = TEXT;
            }
        } else if (st == TAG_START_LEFT) {
            if (c == '>') {
                if (tag.empty()) {
                    // no empty tag
                    return "empty open tag";
                }
                tq.emplace(tag);
                tag.clear();
                st = TAG_END_LEFT;
            } else if (c == '/') { // current must be a close tag
                st = TOKEN_START_RIGHT;
            } else if (tokens.count(c) != 0) {
                return "parse error";
            } else {
                tag += c;
            }
        } else if (st == TOKEN_START_RIGHT) {
            if (c == '>') {
                if (tag.empty()) {
                    // no empty tag
                    return "empty closing tag";
                }
                if (tq.empty() || tag != tq.top()) {
                    return "encountered closing tag without matching open tag for </" + tag + ">";
                }
                tq.pop();
                tag.clear();
                st = TAG_END_RIGHT;
            } else {
                tag += c;
            }
        }
    }

    if ((st == TEXT || st == TAG_END_RIGHT) && tq.empty()) {
        return "valid";
    }
    if ((st == TEXT || st == TAG_END_LEFT) && !tq.empty()) {
        return "missing closing tag for <" + tq.top() + ">";
    }
    if (st == TAG_END_RIGHT) {
        return "encountered closing tag without matching open tag for </" + tq.top() + ">";
    }
    return "parse error";
}

FTEST(test_validate_xml) {
    auto t = [&](const std::string& s) {
        auto re = validate_xml(s);
        LOG(INFO) << s << ": " << re;
        return re;
    };

    FEXP(t("/"), "valid");
    FEXP(t("/>"), "parse error");
    FEXP(t(">"), "parse error");
    FEXP(t("a>"), "parse error");
    FEXP(t("a/>"), "parse error");
    FEXP(t("<<a>sss"), "parse error");
    FEXP(t("<a>sss"), "missing closing tag for <a>");
    FEXP(t("</a>"), "encountered closing tag without matching open tag for </a>");
    FEXP(t("sss</a>"), "encountered closing tag without matching open tag for </a>");
    FEXP(t("<a>sss</b>"), "encountered closing tag without matching open tag for </b>");
    FEXP(t("<a></a>"), "valid");
    FEXP(t("<a>sss</a>"), "valid");
    FEXP(t("<a>ss/s</a>"), "valid");
    FEXP(t("<a>ss<s</a>"), "parse error");
    FEXP(t("<a>ss>s</a>"), "parse error");
    FEXP(t("<a>ss<>s</a>"), "empty open tag");
    FEXP(t("<a>ss</>s</a>"), "empty closing tag");
    FEXP(t("<a><c></c></a>"), "valid");
    FEXP(t("<a>sss<c></c></a>"), "valid");
    FEXP(t("<a><c>sss</c></a>"), "valid");
    FEXP(t("<a><c></c>sss</a>"), "valid");
    FEXP(t("<a>sss<c>sss</c></a>"), "valid");
    FEXP(t("<a><c>sss</c>sss</a>"), "valid");
    FEXP(t("<a>sss<c></c>sss</a>"), "valid");
    FEXP(t("<a>sss<c>sss</c>sss</a>"), "valid");
    FEXP(t("<a>d/d<c></c></a>"), "valid");
    FEXP(t("<a><c>d/d</c></a>"), "valid");
    FEXP(t("<a><c></c>d/d</a>"), "valid");
    FEXP(t("<a>d/d<c>d/d</c></a>"), "valid");
    FEXP(t("<a><c>d/d</c>d/d</a>"), "valid");
    FEXP(t("<a>d/d<c></c>d/d</a>"), "valid");
    FEXP(t("<a>d/d<c>d/d</c>d/d</a>"), "valid");
    FEXP(t("<a>d/d<c><c>d/d</c></c>d/d</a>"), "valid");

}

int main() {

//    for (auto& test : g_test_list) {
//        LOG(INFO) << "==== start: " << test.first << " ====";
//        try {
//            test.second();
//        } catch (std::exception& e) {
//            LOG(INFO) << "== exception: " << test.first << " ==\n";
//            continue;
//        }
//        LOG(INFO) << "======== end ========\n";
//    }

//  ↑↓←→↗↘↖↙≠∞
//  ┌ └ ┐ ┘ ─ │ ├ ┤ ┬ ┴ ┼
    test_minSubArrayLen();

    // TODO... Manacher's palindrome
    // TODO... LSM tree
    return 0;
}