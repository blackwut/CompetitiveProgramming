#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
using namespace std;

#define LEFT(i)     ((i << 1) + 1)
#define RIGHT(i)    ((i << 1) + 2)
#define PARENT(i)   ((i - 1) >> 1)


template<typename ValueType, typename BinaryOperation>
struct SegmentTree
{

public:

    struct STRange {
        size_t lo;
        size_t hi;
        size_t mid;

        STRange(size_t lo, size_t hi) :
            lo(lo),
            hi(hi),
            mid(lo + (hi - lo) / 2)
        {}

        STRange left() const { return STRange(lo, mid); }
        STRange right() const { return STRange(mid + 1, hi); }
    };


    SegmentTree(BinaryOperation binaryOperation,
                ValueType identityValue)
        : op(binaryOperation),
          identityValue(identityValue),
          _root(0, 0)
    {}

    ~SegmentTree(){}


    void build(const vector<ValueType> & leaves)
    {
        const size_t n = leaves.size();
        // round up to the next power of 2
        const size_t m = size_t(1) << static_cast<size_t>(ceil(log2(n)));
        tree.resize(2 * m - 1, identityValue);
        _root = STRange(0, n - 1);
        build(leaves, STRange(0, n - 1), 0);
    }

    size_t size() const
    {
        return tree.size() / 2 + 1;
    }

    STRange root() const
    {
        return _root;
    }

    void print() const
    {
        for (auto x : tree) {
            cout << x << " ";
        }
        cout << endl;
    }

    ValueType rmq(const STRange & query)
    {
        return rmqS(query, root(), 0);
    }

    ValueType rmqS(const STRange & query,
                   const STRange & segment,
                   const size_t pos)
    {
        // total overlap
        if (query.lo <= segment.lo && segment.hi <= query.hi) {
            return tree[pos];
        }

        // no overlap
        if (query.lo > segment.hi || query.hi < segment.lo) {
            return identityValue;
        }

        // partial overlap
        return op(
            rmqS(query, segment.left(),  LEFT(pos)),
            rmqS(query, segment.right(), RIGHT(pos))
        );
    }

    void update(const ValueType delta,
                const size_t i)
    {
        updateS(delta, i, root(), 0);
    }

    // increment the i-th leaf by delta
    void updateS(const size_t i,
                 const ValueType delta,
                 const STRange & segment,
                 const size_t pos)
    {
        // outside range
        if (i < segment.lo || i > segment.hi) {
            return;
        }

        // leaf
        if (segment.lo == segment.hi) {
            tree[pos] += delta;
            return;
        }

        updateS(i, delta, segment.left(),  LEFT(pos));
        updateS(i, delta, segment.right(), RIGHT(pos));
        tree[pos] = op(
            tree[LEFT(pos)],
            tree[RIGHT(pos)]
        );
    }

    // increment all leaves in the STRange [range.lo, range.hi] by delta
    void updateRange(const STRange & range,
                     const ValueType delta)
    {
        updateRangeS(range, delta, root(), 0);
    }

    void updateRangeS(const STRange range,
                      const ValueType delta,
                      const STRange segment,
                      const size_t pos)
    {
        // outside range
        if (range.hi < segment.lo || range.lo > segment.hi) {
            return;
        }

        // leaf
        if (segment.lo == segment.hi) {
            tree[pos] += delta;
            return;
        }

        updateRangeS(range, delta, segment.left(),  LEFT(pos));
        updateRangeS(range, delta, segment.right(), RIGHT(pos));
        tree[pos] = op(
            tree[LEFT(pos)],
            tree[RIGHT(pos)]
        );
    }


private:

    BinaryOperation op;
    ValueType identityValue;
    vector<ValueType> tree;
    STRange _root;

    void build(const vector<ValueType> & leaves,
               const STRange segment,
               const size_t pos)
    {
        if (segment.lo == segment.hi) {
            tree[pos] = leaves[segment.lo];
            return;
        }
        build(leaves, segment.left(),  LEFT(pos));
        build(leaves, segment.right(), RIGHT(pos));
        tree[pos] = op(
            tree[LEFT(pos)],
            tree[RIGHT(pos)]
        );
    }

};
