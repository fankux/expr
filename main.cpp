#include <iostream>
#include <limits.h>
#include <string.h>

#include "util.hpp"

void reverse_stack_put(std::vector<int>& stack, int value) {
    if (stack.empty()) {
        stack.push_back(value);
        return;
    }

    int top = stack.back();
    stack.pop_back();

    reverse_stack_put(stack, value);
    stack.push_back(top);
}

void reverse_stack(std::vector<int>& stack) {
    if (stack.size() <= 1) {
        return;
    }

    int top = stack.back();
    stack.pop_back();

    reverse_stack(stack);
    reverse_stack_put(stack, top);
}

void test_reverse_stack() {
    std::vector<int> s{1, 2, 3, 4, 5};
    for (int i : s) {
        std::cout << i << ",";
    }
    std::cout << std::endl;

    reverse_stack(s);
    for (int i : s) {
        std::cout << i << ",";
    }
    std::cout << std::endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void sort(std::vector<int>& nums);

void premute(std::vector<int>& nums, int start, std::vector<std::vector<int>>& res) {
    if (start >= nums.size()) {
        res.push_back(nums);
        return;
    }
    for (int i = start; i < nums.size(); ++i) {
        int j = i - 1;
        while (j >= start && nums[j] != nums[i]) {
            --j;
        }
        if (j != start - 1) {
            continue;
        }

        std::swap(nums[start], nums[i]);
        premute(nums, start + 1, res);
        std::swap(nums[start], nums[i]);
    }
}

void premute2(std::vector<int>& nums, size_t level, std::vector<size_t>& visit,
        std::vector<size_t>& out, std::vector<std::vector<size_t>>& res) {
    if (level >= nums.size()) {
        res.push_back(out);
        return;
    }

    for (size_t i = 0; i < nums.size(); ++i) {
        if (visit[i] == 1) {
            continue;
        }
        if (i > 0 && nums[i] == nums[i - 1] && visit[i - 1] == 0) {
            continue;
        }
        visit[i] = 1;
        out.emplace_back(nums[i]);
        premute2(nums, level + 1, visit, out, res);
        out.pop_back();
        visit[i] = 0;
    }
}

void do_premutation(std::vector<int> nums) {
    std::vector<std::vector<int>> res;
    premute(nums, 0, res);

    for (auto& r : res) {
        for (int n : r) {
            std::cout << n << ",";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void do_premutation2(std::vector<int> nums) {
    std::vector<size_t> visit(nums.size(), 0);
    std::vector<std::vector<size_t>> res;
    std::vector<size_t> out;
    sort(nums);
    premute2(nums, 0, visit, out, res);

    for (auto& r : res) {
        for (int n : r) {
            std::cout << n << ",";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void test_premutation() {
    do_premutation({4, 5, 6});
    do_premutation({7, 7, 8});

    do_premutation2({6, 5, 4});
    do_premutation2({7, 8, 7});
}

///////////////////////////////////////////////////////////////////////////////////////////////////

int partition(std::vector<int>& nums, int left, int right) {
    int pivot = nums[left];

    while (left < right) {
        while (right > left && nums[right] >= pivot) {
            --right;
        }
        nums[left] = nums[right];
        while (left < right && nums[left] <= pivot) {
            ++left;
        }
        nums[right] = nums[left];
    }
    nums[left] = pivot;

    return left;
}

void qsort(std::vector<int>& nums, int start, int end) {
    if (nums.empty() || start >= end) {
        return;
    }

    int m = partition(nums, start, end);
    qsort(nums, start, m - 1);
    qsort(nums, m + 1, end);
}

void sort(std::vector<int>& nums) {
    qsort(nums, 0, nums.size() - 1);
}

void test_qsort_item(std::vector<int> nums) {
    sort(nums);
    for (int num : nums) {
        std::cout << num << ",";
    }
    std::cout << std::endl;
}

void test_qsort() {
    test_qsort_item({});
    test_qsort_item({1});
    test_qsort_item({1, 2});
    test_qsort_item({1, 2, 3});
    test_qsort_item({1, 2, 3, 4});
    test_qsort_item({1, 1});
    test_qsort_item({1, 1, 2});
    test_qsort_item({1, 2, 2});
    test_qsort_item({2, 1, 2});
    test_qsort_item({2, 1});
    test_qsort_item({2, 2, 1});
    test_qsort_item({2, 1, 1});
    test_qsort_item({1, 2, 1});
    test_qsort_item({3, 2, 1});
    test_qsort_item({4, 2, 1});
    test_qsort_item({-1, -1, 0});
    test_qsort_item({0, -1, -1});
    test_qsort_item({1, 0, -1});
    test_qsort_item({-1, 0, 1});
    test_qsort_item({6, 2, 8, 1, 5, 7});
    test_qsort_item({-6, -2, -8, -1, -5, -7});
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void min_heap_fixup(int a[], int i) {
    int j;
    int temp = a[i];
    j = (i - 1) / 2;      //父结点
    while (j >= 0 && i != 0) {
        if (a[j] <= temp) {
            break;
        }

        a[i] = a[j];     //把较大的子结点往下移动,替换它的子结点
        i = j;
        j = (i - 1) / 2;
    }
    a[i] = temp;
}

void min_heap_fixdown(int a[], int i, int n) {
    int j, temp;

    temp = a[i];
    j = 2 * i + 1;
    while (j < n) {
        if (j + 1 < n && a[j + 1] < a[j]) { //在左右孩子中找最小的
            j++;
        }

        if (a[j] >= temp) {
            break;
        }

        a[i] = a[j];     //把较小的子结点往上移动,替换它的父结点
        i = j;
        j = 2 * i + 1;
    }
    a[i] = temp;
}

void min_heap_add(int a[], int n, int nNum) {
    a[n] = nNum;
    min_heap_fixup(a, n);
}

void min_heap_delete(int a[], int n) {
    std::swap(a[0], a[n - 1]);
    min_heap_fixdown(a, 0, n - 1);
}

void create_min_heap(int a[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        min_heap_fixdown(a, i, n);
    }
}

void min_heap_sort(int a[], int n) {
    for (int i = n - 1; i >= 1; i--) {
        std::swap(a[i], a[0]);
        min_heap_fixdown(a, 0, i);
    }
}

void test_heap() {
    int nums[] = {2, 5, 1, 7, 8, 4, 3, 6};
    int len = sizeof(nums) / sizeof(nums[0]);
    create_min_heap(nums, len);
    min_heap_sort(nums, len);
    for (int num : nums) {
        std::cout << num << ",";
    }
    std::cout << std::endl;

    min_heap_add(nums, len, 9);
    min_heap_sort(nums, len);
    for (int num : nums) {
        std::cout << num << ",";
    }
    std::cout << std::endl;

    min_heap_delete(nums, len);
    min_heap_sort(nums, len);
    for (int num : nums) {
        std::cout << num << ",";
    }
    std::cout << std::endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

class SkipList {
private:
    struct Node {
        int k;
        std::string v;
        std::vector<Node*> nexts;
    };

public:
    void add(int k, const std::string& v) {
        size_t level = rand_level();
        if (level >= _head.nexts.size()) {
            _head.nexts.push_back(nullptr);
            level = _head.nexts.size() - 1;
        }

        std::vector<Node*> pres(level + 1, &_head);
        Node* n = nullptr;
        for (int i = level; i >= 0; --i) {
            if (n == nullptr) {
                n = _head.nexts[i];
            }
            Node* pre = pres[i];
            while (n != nullptr) {
                if (k == n->k) {
                    n->v = v;
                    return;
                }
                if (k < n->k) {
                    pres[i] = pre;
                    n = pre;
                    break;
                }

                pre = n;
                pres[i] = pre;
                n = n->nexts[i];
            }
        }

        Node* c = new Node();
        c->k = k;
        c->v = v;
        c->nexts.resize(pres.size(), nullptr);

        for (int i = pres.size() - 1; i >= 0; --i) {
            c->nexts[i] = pres[i]->nexts[i];
            pres[i]->nexts[i] = c;
        }
    }

    std::string get(int k) {
        Node* pre = nullptr;
        Node* n = get_node(k, pre);
        return n == nullptr ? "no key" : n->v;
    }

    void earse(int k) {
        if (_head.nexts.empty()) {
            return;
        }

        size_t level = _head.nexts.size() - 1;
        Node* n = nullptr;
        Node* pre = nullptr;
        for (int i = level; i >= 0; --i) {
            if (n == nullptr) {
                n = _head.nexts[i];
                pre = &_head;
            }
            while (n != nullptr) {
                if (k == n->k) {
                    pre->nexts[i] = n->nexts[i];
                    n = pre;
                    continue;
                }
                if (k < n->k) {
                    n = pre;
                    break;
                }

                pre = n;
                n = n->nexts[i];
            }
        }

        if (!_head.nexts.empty()) {
            if (_head.nexts[_head.nexts.size() - 1] == nullptr) {
                _head.nexts.pop_back();
            }
        }
    }

    void debug_structure() {
        std::cout << "=========" << std::endl;
        if (_head.nexts.empty()) {
            std::cout << "null\n=========" << std::endl;
            return;
        }

        size_t max_len = 0;
        for (int i = 0; i >= 0; --i) {
            size_t len = 0;
            Node* n = _head.nexts[0];
            while (n != nullptr) {
                ++len;
                n = n->nexts[i];
            }

            if (len > max_len) {
                max_len = len;
            }
        }

        std::map<int, size_t> key_pos;
        Node* n = _head.nexts[0];
        size_t idx = 0;
        while (n != nullptr) {
            key_pos.emplace(n->k, idx);
            n = n->nexts[0];
            ++idx;
        }

        for (int i = _head.nexts.size() - 1; i >= 0; --i) {
            n = _head.nexts[i];
            std::cout << "[" << i << "]->";

            idx = 0;
            while (n != nullptr) {
                if (idx != key_pos[n->k]) {
                    std::cout << "->->-->";
                } else {
                    std::cout << "(" << n->k << ":" << n->v << ")->";
                    n = n->nexts[i];
                }
                ++idx;
            }
            while (idx < max_len) {
                std::cout << "->->-->";
                ++idx;
            }
            std::cout << "null" << std::endl;
        }
        std::cout << "=========" << std::endl;
    }

private:
    Node* get_node(int k, Node*& pre) {
        if (_head.nexts.empty()) {
            pre = nullptr;
            return nullptr;
        }

        size_t level = _head.nexts.size() - 1;
        Node* n = _head.nexts[level];
        pre = &_head;
        while (n != nullptr && level >= 0) {
            if (k == n->k) {
                return n;
            }
            if (k < n->k) {
                n = pre->nexts[--level];
                continue;
            }

            pre = n;
            n = n->nexts[level];
        }

        return nullptr;
    }

    size_t rand_level() {
//        srand(time(nullptr));
//        size_t level = 0;
//        while (rand() % 2 == 0) {
//            ++level;
//        }
//        return level;
        return _head.nexts.size();
    }

private:
    Node _head;
};

void test_skiplist() {
    SkipList sl;
    std::cout << sl.get(0) << std::endl;

    sl.add(0, "a");
    sl.debug_structure();
    std::cout << sl.get(0) << std::endl;

    sl.add(1, "b");
    sl.debug_structure();

    sl.add(5, "f");
    sl.debug_structure();

    sl.add(3, "d");
    sl.debug_structure();

    std::cout << sl.get(0) << std::endl;
    std::cout << sl.get(1) << std::endl;
    std::cout << sl.get(3) << std::endl;
    std::cout << sl.get(5) << std::endl;

    sl.add(2, "c");
    sl.debug_structure();

    sl.earse(2);
    sl.debug_structure();

    sl.earse(1);
    sl.debug_structure();

    sl.earse(3);
    sl.debug_structure();
}

///////////////////////////////////////////////////////////////////////////////////////////////////

size_t edit_distance_recusive_handle(const std::string& s1, const std::string& s2, size_t i,
        size_t j, std::vector<std::vector<size_t>>& counts) {
    if (i == s1.size()) {
        return s2.size() - j;
    }
    if (j == s2.size()) {
        return s1.size() - i;
    }
    if (counts[i][j] > 0) {
        return counts[i][j];
    }

    if (s1[i] == s2[j]) {
        return edit_distance_recusive_handle(s1, s2, i + 1, j + 1, counts);
    }

    size_t insert_count = edit_distance_recusive_handle(s1, s2, i, j + 1, counts);
    size_t delete_count = edit_distance_recusive_handle(s1, s2, i + 1, j, counts);
    size_t update_count = edit_distance_recusive_handle(s1, s2, i + 1, j + 1, counts);
    size_t count = std::min(insert_count, std::min(delete_count, update_count)) + 1;
    counts[i][j] = count;
    return count;
}

size_t edit_distance_recusive(const std::string& s1, const std::string& s2) {
    std::cout << s1 << "<->" << s2 << " distance: ";
    std::vector<std::vector<size_t>> counts(s1.size(), std::vector<size_t>(s2.size()));
    return edit_distance_recusive_handle(s1, s2, 0, 0, counts);
}

size_t edit_distance_dp(const std::string& s1, const std::string& s2) {
    std::cout << s1 << "<->" << s2 << " distance: ";

    std::vector<std::vector<size_t>> counts(s1.size() + 1, std::vector<size_t>(s2.size() + 1));
    for (size_t i = 0; i <= s1.size(); ++i) {
        counts[i][0] = i;
    }
    for (size_t i = 0; i <= s2.size(); ++i) {
        counts[0][i] = i;
    }

    for (size_t i = 1; i <= s1.size(); ++i) {
        for (size_t j = 1; j <= s2.size(); ++j) {
            if (s1[i - 1] == s2[j - 1]) {
                counts[i][j] = counts[i - 1][j - 1];
            } else {
                counts[i][j] = std::min(counts[i - 1][j - 1],
                        std::min(counts[i - 1][j], counts[i][j - 1])) + 1;
            }
        }
    }
    return counts[s1.size()][s2.size()];
}

void test_edit_distance() {
    std::cout << edit_distance_recusive("", "1") << std::endl;
    std::cout << edit_distance_recusive("1", "") << std::endl;
    std::cout << edit_distance_recusive("", "") << std::endl;
    std::cout << edit_distance_recusive("1", "1") << std::endl;
    std::cout << edit_distance_recusive("1", "2") << std::endl;
    std::cout << edit_distance_recusive("2", "1") << std::endl;
    std::cout << edit_distance_recusive("1", "11") << std::endl;
    std::cout << edit_distance_recusive("1", "12") << std::endl;
    std::cout << edit_distance_recusive("11", "1") << std::endl;
    std::cout << edit_distance_recusive("12", "1") << std::endl;
    std::cout << edit_distance_recusive("11", "12") << std::endl;
    std::cout << edit_distance_recusive("11", "22") << std::endl;

    std::cout << std::endl;

    std::cout << edit_distance_dp("", "1") << std::endl;
    std::cout << edit_distance_dp("1", "") << std::endl;
    std::cout << edit_distance_dp("", "") << std::endl;
    std::cout << edit_distance_dp("1", "1") << std::endl;
    std::cout << edit_distance_dp("1", "2") << std::endl;
    std::cout << edit_distance_dp("2", "1") << std::endl;
    std::cout << edit_distance_dp("1", "11") << std::endl;
    std::cout << edit_distance_dp("1", "12") << std::endl;
    std::cout << edit_distance_dp("11", "1") << std::endl;
    std::cout << edit_distance_dp("12", "1") << std::endl;
    std::cout << edit_distance_dp("11", "12") << std::endl;
    std::cout << edit_distance_dp("11", "22") << std::endl;

}

///////////////////////////////////////////////////////////////////////////////////////////////////

ssize_t bin_search(const std::vector<int>& nums, int target) {
    std::cout << "[";
    for (auto num : nums) {
        std::cout << num << " ";
    }
    std::cout << "] find " << target << ": ";

    if (nums.empty()) {
        return -1;
    }

    ssize_t l = 0;
    ssize_t h = nums.size() - 1;
    while (l <= h) {
        size_t mid = (l + h) / 2;
        if (nums[mid] == target) {
            return mid;
        }
        if (nums[mid] < target) {
            l = mid + 1;
        } else {
            h = mid - 1;
        }
    }
    return -1;
}

ssize_t bin_search_1st_great_equal(const std::vector<int>& nums, int target) {
    std::cout << "[";
    for (auto num : nums) {
        std::cout << num << " ";
    }
    std::cout << "] 1st great equal " << target << ": ";

    if (nums.empty()) {
        return -1;
    }

    ssize_t l = 0;
    ssize_t h = nums.size() - 1;
    while (l <= h) {
        size_t mid = (l + h) / 2;
        if (nums[mid] < target) {
            l = mid + 1;
        } else {
            h = mid - 1;
        }
    }
    return h + 1 >= nums.size() ? -1 : h + 1;
}

ssize_t bin_search_1st_great(const std::vector<int>& nums, int target) {
    std::cout << "[";
    for (auto num : nums) {
        std::cout << num << " ";
    }
    std::cout << "] 1st great " << target << ": ";

    if (nums.empty()) {
        return -1;
    }

    ssize_t l = 0;
    ssize_t h = nums.size() - 1;
    while (l <= h) {
        size_t mid = (l + h) / 2;
        if (nums[mid] <= target) {
            l = mid + 1;
        } else {
            h = mid - 1;
        }
    }
    return h + 1 >= nums.size() ? -1 : h + 1;
}

void test_bin_search() {
    std::cout << "binary search" << std::endl;
    std::cout << bin_search({}, 1) << std::endl;
    std::cout << bin_search({1}, 0) << std::endl;
    std::cout << bin_search({1}, 2) << std::endl;
    std::cout << bin_search({1}, 1) << std::endl;
    std::cout << bin_search({1, 2}, 0) << std::endl;
    std::cout << bin_search({1, 2}, 3) << std::endl;
    std::cout << bin_search({1, 2}, 1) << std::endl;
    std::cout << bin_search({1, 2}, 2) << std::endl;
    std::cout << bin_search({1, 2, 3}, 0) << std::endl;
    std::cout << bin_search({1, 2, 3}, 1) << std::endl;
    std::cout << bin_search({1, 2, 3}, 2) << std::endl;
    std::cout << bin_search({1, 2, 3}, 3) << std::endl;
    std::cout << bin_search({1, 2, 3}, 4) << std::endl;
    std::cout << bin_search({1, 2, 3, 4}, 1) << std::endl;
    std::cout << bin_search({1, 2, 3, 4}, 2) << std::endl;
    std::cout << bin_search({1, 2, 3, 4}, 3) << std::endl;
    std::cout << bin_search({1, 2, 3, 4}, 4) << std::endl;
    std::cout << bin_search({1, 2, 3, 4, 5}, 1) << std::endl;
    std::cout << bin_search({1, 2, 3, 4, 5}, 2) << std::endl;
    std::cout << bin_search({1, 2, 3, 4, 5}, 3) << std::endl;
    std::cout << bin_search({1, 2, 3, 4, 5}, 4) << std::endl;
    std::cout << bin_search({1, 2, 3, 4, 5}, 5) << std::endl;
    std::cout << bin_search({1, 2, 2, 4, 5}, 2) << std::endl;
    std::cout << bin_search({1, 2, 3, 3, 5}, 3) << std::endl;

    std::cout << "\nbinary search 1st greater equal" << std::endl;
    std::cout << bin_search_1st_great_equal({}, 1) << std::endl;
    std::cout << bin_search_1st_great_equal({1}, 0) << std::endl;
    std::cout << bin_search_1st_great_equal({1}, 2) << std::endl;
    std::cout << bin_search_1st_great_equal({1}, 1) << std::endl;
    std::cout << bin_search_1st_great_equal({1, 2}, 0) << std::endl;
    std::cout << bin_search_1st_great_equal({1, 2}, 3) << std::endl;
    std::cout << bin_search_1st_great_equal({1, 2}, 1) << std::endl;
    std::cout << bin_search_1st_great_equal({1, 2}, 2) << std::endl;
    std::cout << bin_search_1st_great_equal({1, 2, 3}, 0) << std::endl;
    std::cout << bin_search_1st_great_equal({1, 2, 3}, 1) << std::endl;
    std::cout << bin_search_1st_great_equal({1, 2, 3}, 2) << std::endl;
    std::cout << bin_search_1st_great_equal({1, 2, 3}, 3) << std::endl;
    std::cout << bin_search_1st_great_equal({1, 2, 3}, 4) << std::endl;
    std::cout << bin_search_1st_great_equal({1, 2, 3, 4}, 1) << std::endl;
    std::cout << bin_search_1st_great_equal({1, 2, 3, 4}, 2) << std::endl;
    std::cout << bin_search_1st_great_equal({1, 2, 3, 4}, 3) << std::endl;
    std::cout << bin_search_1st_great_equal({1, 2, 3, 4}, 4) << std::endl;
    std::cout << bin_search_1st_great_equal({1, 2, 3, 4, 5}, 1) << std::endl;
    std::cout << bin_search_1st_great_equal({1, 2, 3, 4, 5}, 2) << std::endl;
    std::cout << bin_search_1st_great_equal({1, 2, 3, 4, 5}, 3) << std::endl;
    std::cout << bin_search_1st_great_equal({1, 2, 3, 4, 5}, 4) << std::endl;
    std::cout << bin_search_1st_great_equal({1, 2, 3, 4, 5}, 5) << std::endl;
    std::cout << bin_search_1st_great_equal({1, 2, 2, 4, 5}, 2) << std::endl;
    std::cout << bin_search_1st_great_equal({1, 2, 3, 3, 5}, 3) << std::endl;

    std::cout << "\nbinary search 1st greater " << std::endl;
    std::cout << bin_search_1st_great({}, 1) << std::endl;
    std::cout << bin_search_1st_great({1}, 0) << std::endl;
    std::cout << bin_search_1st_great({1}, 2) << std::endl;
    std::cout << bin_search_1st_great({1}, 1) << std::endl;
    std::cout << bin_search_1st_great({1, 2}, 0) << std::endl;
    std::cout << bin_search_1st_great({1, 2}, 3) << std::endl;
    std::cout << bin_search_1st_great({1, 2}, 1) << std::endl;
    std::cout << bin_search_1st_great({1, 2}, 2) << std::endl;
    std::cout << bin_search_1st_great({1, 2, 3}, 0) << std::endl;
    std::cout << bin_search_1st_great({1, 2, 3}, 1) << std::endl;
    std::cout << bin_search_1st_great({1, 2, 3}, 2) << std::endl;
    std::cout << bin_search_1st_great({1, 2, 3}, 3) << std::endl;
    std::cout << bin_search_1st_great({1, 2, 3}, 4) << std::endl;
    std::cout << bin_search_1st_great({1, 2, 3, 4}, 1) << std::endl;
    std::cout << bin_search_1st_great({1, 2, 3, 4}, 2) << std::endl;
    std::cout << bin_search_1st_great({1, 2, 3, 4}, 3) << std::endl;
    std::cout << bin_search_1st_great({1, 2, 3, 4}, 4) << std::endl;
    std::cout << bin_search_1st_great({1, 2, 3, 4, 5}, 1) << std::endl;
    std::cout << bin_search_1st_great({1, 2, 3, 4, 5}, 2) << std::endl;
    std::cout << bin_search_1st_great({1, 2, 3, 4, 5}, 3) << std::endl;
    std::cout << bin_search_1st_great({1, 2, 3, 4, 5}, 4) << std::endl;
    std::cout << bin_search_1st_great({1, 2, 3, 4, 5}, 5) << std::endl;
    std::cout << bin_search_1st_great({1, 2, 2, 4, 5}, 2) << std::endl;
    std::cout << bin_search_1st_great({1, 2, 3, 3, 5}, 3) << std::endl;
}

ssize_t bin_search_rotate(const std::vector<int>& nums, int target) {
    std::cout << "[";
    for (auto num : nums) {
        std::cout << num << " ";
    }
    std::cout << "] find rotate " << target << ": ";

    if (nums.empty()) {
        return -1;
    }

    ssize_t l = 0;
    ssize_t h = nums.size() - 1;
    while (l <= h) {
        size_t mid = (l + h) / 2;
        if (nums[mid] == target) {
            return mid;
        }
        if (nums[mid] < nums[h]) {
            if (nums[mid] < target && nums[h] >= target) {
                // right sorted and target in range
                l = mid + 1;
            } else {
                h = mid - 1;
            }
        } else {
            if (nums[mid] > target && nums[l] <= target) {
                // left sorted and target in range
                h = mid - 1;
            } else {
                l = mid + 1;
            }
        }
    }
    return -1;
}

void test_bin_search_rotate() {
    std::cout << "binary search rotate" << std::endl;
    std::cout << bin_search_rotate({}, 1) << std::endl;
    std::cout << bin_search_rotate({1}, 0) << std::endl;
    std::cout << bin_search_rotate({1}, 2) << std::endl;
    std::cout << bin_search_rotate({1}, 1) << std::endl;
    std::cout << bin_search_rotate({1, 2}, 0) << std::endl;
    std::cout << bin_search_rotate({1, 2}, 3) << std::endl;
    std::cout << bin_search_rotate({1, 2}, 1) << std::endl;
    std::cout << bin_search_rotate({1, 2}, 2) << std::endl;
    std::cout << bin_search_rotate({1, 2, 3}, 0) << std::endl;
    std::cout << bin_search_rotate({1, 2, 3}, 1) << std::endl;
    std::cout << bin_search_rotate({1, 2, 3}, 2) << std::endl;
    std::cout << bin_search_rotate({1, 2, 3}, 3) << std::endl;
    std::cout << bin_search_rotate({1, 2, 3}, 4) << std::endl;
    std::cout << bin_search_rotate({1, 2, 3, 4}, 1) << std::endl;
    std::cout << bin_search_rotate({1, 2, 3, 4}, 2) << std::endl;
    std::cout << bin_search_rotate({1, 2, 3, 4}, 3) << std::endl;
    std::cout << bin_search_rotate({1, 2, 3, 4}, 4) << std::endl;
    std::cout << bin_search_rotate({1, 2, 3, 4, 5}, 1) << std::endl;
    std::cout << bin_search_rotate({1, 2, 3, 4, 5}, 2) << std::endl;
    std::cout << bin_search_rotate({1, 2, 3, 4, 5}, 3) << std::endl;
    std::cout << bin_search_rotate({1, 2, 3, 4, 5}, 4) << std::endl;
    std::cout << bin_search_rotate({1, 2, 3, 4, 5}, 5) << std::endl;
    std::cout << bin_search_rotate({1, 2, 2, 4, 5}, 2) << std::endl;
    std::cout << bin_search_rotate({1, 2, 3, 3, 5}, 3) << std::endl;
    std::cout << bin_search_rotate({}, 1) << std::endl;
    std::cout << bin_search_rotate({1}, 0) << std::endl;
    std::cout << bin_search_rotate({1}, 2) << std::endl;
    std::cout << bin_search_rotate({1}, 1) << std::endl;
    std::cout << bin_search_rotate({2, 1}, 0) << std::endl;
    std::cout << bin_search_rotate({2, 1}, 3) << std::endl;
    std::cout << bin_search_rotate({2, 1}, 1) << std::endl;
    std::cout << bin_search_rotate({2, 1}, 2) << std::endl;
    std::cout << bin_search_rotate({3, 1, 2}, 0) << std::endl;
    std::cout << bin_search_rotate({3, 1, 2}, 1) << std::endl;
    std::cout << bin_search_rotate({3, 1, 2}, 2) << std::endl;
    std::cout << bin_search_rotate({3, 1, 2}, 3) << std::endl;
    std::cout << bin_search_rotate({3, 1, 2}, 4) << std::endl;
    std::cout << bin_search_rotate({3, 2, 1}, 0) << std::endl;
    std::cout << bin_search_rotate({3, 2, 1}, 1) << std::endl;
    std::cout << bin_search_rotate({3, 2, 1}, 2) << std::endl;
    std::cout << bin_search_rotate({3, 2, 1}, 3) << std::endl;
    std::cout << bin_search_rotate({3, 2, 1}, 4) << std::endl;
    std::cout << bin_search_rotate({3, 4, 1, 2}, 1) << std::endl;
    std::cout << bin_search_rotate({3, 4, 1, 2}, 2) << std::endl;
    std::cout << bin_search_rotate({3, 4, 1, 2}, 3) << std::endl;
    std::cout << bin_search_rotate({3, 4, 1, 2}, 4) << std::endl;
    std::cout << bin_search_rotate({4, 1, 2, 3}, 1) << std::endl;
    std::cout << bin_search_rotate({4, 1, 2, 3}, 2) << std::endl;
    std::cout << bin_search_rotate({4, 1, 2, 3}, 3) << std::endl;
    std::cout << bin_search_rotate({4, 1, 2, 3}, 4) << std::endl;
    std::cout << bin_search_rotate({4, 5, 1, 2, 3}, 1) << std::endl;
    std::cout << bin_search_rotate({4, 5, 1, 2, 3}, 2) << std::endl;
    std::cout << bin_search_rotate({4, 5, 1, 2, 3}, 3) << std::endl;
    std::cout << bin_search_rotate({4, 5, 1, 2, 3}, 4) << std::endl;
    std::cout << bin_search_rotate({4, 5, 1, 2, 3}, 5) << std::endl;
    std::cout << bin_search_rotate({4, 5, 1, 2, 2}, 2) << std::endl;
    std::cout << bin_search_rotate({3, 5, 1, 2, 3}, 3) << std::endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void rb_tree() {

}

///////////////////////////////////////////////////////////////////////////////////////////////////
void b_tree() {}

///////////////////////////////////////////////////////////////////////////////////////////////////

void avl_tree() {}

///////////////////////////////////////////////////////////////////////////////////////////////////

#include "list.hpp"
#include "sums.hpp"
#include "tree.hpp"
#include "strs.hpp"
#include "idx0.hpp"
#include "idx1.hpp"
#include "idx2.hpp"
#include "idx3.hpp"

int main() {

//    for (auto& test : g_test_list) {
//        LOG(INFO) << "==== start: " << test.first << " ====";
//        test.second();
//        LOG(INFO) << "======== end ========\n";
//    }

    test_strStr();

    return 0;
}