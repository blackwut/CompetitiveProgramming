/**
    Author:  Alberto Ottimo
    Problem: 

    Solution Description
    

    Time  Complexity: O()
    Space Complexity: O()
*/

#include <iostream>
#include <vector>
#include <limits>
#include "Structures/SegmentTree.hpp"
using namespace std;


template<typename T>
inline void do_not_optimize_away(T&& datum) {
    asm volatile("" : "+r" (datum));
}

template<typename ValueType>
struct min_operator {
    ValueType operator()(ValueType x, ValueType y) {
        return std::min<ValueType>(x, y);
    }
};

int main()
{
    std::ios_base::sync_with_stdio(false);

    uint64_t n = 0; // number of leaves in the tree
    std::cin >> n;

    typedef std::chrono::high_resolution_clock clock_type;

    auto start = clock_type::now();
    std::vector<int> leaves;
    leaves.reserve(n);
    for (uint64_t i = 0; i < n; ++i) {
        int x = 0;
        std::cin >> x;
        leaves.push_back(x);
    }
    auto end = clock_type::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "parsing the input took: " << elapsed.count() << " [sec]" << std::endl;
    typedef SegmentTree<int, min_operator<int>> segment_tree_type;


    int max = numeric_limits<int>::max();

    std::cout << "building tree with " << n << " leaves" << std::endl;
    start = clock_type::now();
    SegmentTree<int, min_operator<int>> min_seg_tree(min_operator<int>(), max);
    min_seg_tree.build(leaves);
    end = clock_type::now();
    elapsed = end - start;
    std::cout << "building took: " << elapsed.count() << " [sec]" << std::endl;

    uint64_t m = 0; // number of queries
    std::cin >> m;

    std::vector<segment_tree_type::STRange> queries;
    queries.reserve(m);

    for (uint64_t i = 0; i < m; ++i) {
        size_t lo, hi;
        std::cin >> lo >> hi;
        queries.emplace_back(lo, hi);
    }

    std::cout << "executing " << m << " range queries" << std::endl;
    auto root = min_seg_tree.root();
    start = clock_type::now();
    for (int run = 0; run < 5; ++run) {
        for (uint64_t i = 0; i < m; ++i) {
            auto x = min_seg_tree.rmq(queries[i]);
            // auto x = min_seg_tree.rmqS(queries[i], root, 0);
            // std::cout << "rmq in [" << queries[i].lo << ", "
            //                         << queries[i].hi << "]: " << x << "\n";
            do_not_optimize_away(x);
        }
    }
    end = clock_type::now();
    elapsed = end - start;

    std::cout << "average query time: "
              << static_cast<double>(elapsed.count()) / (5 * m) * 1000000
              << " [musec]" << std::endl;

    uint64_t k = 0; // number of updates
    std::cin >> k;

    typedef std::pair<segment_tree_type::STRange, int> update_query;
    std::vector<update_query> updates;
    updates.reserve(k);

    for (uint64_t i = 0; i < k; ++i) {
        size_t lo, hi;
        int delta;
        std::cin >> lo >> hi >> delta;
        segment_tree_type::STRange r(lo, hi);
        updates.emplace_back(r, delta);
    }

    std::cout << "executing " << k << " updates" << std::endl;
    start = clock_type::now();
    for (uint64_t i = 0; i < k; ++i) {
        auto const& range = updates[i].first;
        int delta = updates[i].second;
        min_seg_tree.update(range.lo, delta);
        // min_seg_tree.updateS(range.lo, delta, root, 0);
    }
    end = clock_type::now();
    elapsed = end - start;

    std::cout << "average update time: "
              << static_cast<double>(elapsed.count()) / k * 1000000
              << " [musec]" << std::endl;

    std::cout << "executing " << k << " range updates" << std::endl;
    start = clock_type::now();
    for (uint64_t i = 0; i < k; ++i) {
        auto const& range = updates[i].first;
        int delta = updates[i].second;
        min_seg_tree.updateRange(range, delta);
        // min_seg_tree.updateRangeS(range, delta, root, 0);
    }
    end = clock_type::now();
    elapsed = end - start;

    std::cout << "average range update time: "
              << static_cast<double>(elapsed.count()) / k * 1000000
              << " [musec]" << std::endl;

    // min_seg_tree.print();

    return 0;
}
