/**
 * Author: Jelle van der Drift
 * Date: 2020-10-23
 * License: CC0
 * Source: me
 * Description: Segment tree with ability to set values of intervals, and compute sums of intervals.
 * Can be changed to other things.
 * Time: O(\log N).
 * Usage: Segtree tree(n, v);
 * Status: stress-tested a bit with max queries + range set and add queries + range set
 */
#pragma once

struct SegTree {
    typedef int T;
    const T id = 0;
    const T lzId = INT_MIN;
    T merge(T a, T b) {
        return a + b;
    }
    void mergelz(T& a, T lz, int sz) {
        if (lz != lzId)
            a = lz * sz;
    }

    int N = 1;
    vector<T> t, lz;
    SegTree(int n, vector<T> values) {
        while (N < n) N *= 2;

        t.resize(2 * N), lz.resize(2 * N, lzId);
        for (int i = 0; i < n; i++)
            t[N + i] = values[i];
        for (int i = N - 1; i >= 1; i--)
            t[i] = merge(t[2 * i], t[2 * i + 1]);
    }
    void push(int i, int sz) {
        mergelz(t[2 * i], lz[i], sz);
        mergelz(t[2 * i + 1], lz[i], sz);
        mergelz(lz[2 * i], lz[i], 1);
        mergelz(lz[2 * i + 1], lz[i], 1);
        lz[i] = lzId;
    }
    void update(int l, int r, T v, int i = 1, int tl = 0, int tr = -1) {
        if (tr == -1) tr = N;
        if (l >= tr || r <= tl) return;
        if (tl >= l && tr <= r)
            mergelz(lz[i], v, 1), mergelz(t[i], v, tr - tl);
        else {
            int tm = (tl + tr) / 2;
            push(i, tm - tl);
            update(l, r, v, 2 * i, tl, tm);
            update(l, r, v, 2 * i + 1, tm, tr);
            t[i] = merge(t[2 * i], t[2 * i + 1]);
        }
    }
    T query(int l, int r, int i = 1, int tl = 0, int tr = -1) {
        if (tr == -1) tr = N;
        if (l >= tr || r <= tl) return id;
        if (tl >= l && tr <= r) return t[i];
        int tm = (tl + tr) / 2;
        push(i, tm - tl);
        return merge(query(l, r, 2 * i, tl, tm), query(l, r, 2 * i + 1, tm, tr));
    }
};