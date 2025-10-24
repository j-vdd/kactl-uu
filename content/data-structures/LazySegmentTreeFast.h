/**
 * Author: Jelle van der Drift
 * Date: 2020-10-23
 * License: CC0
 * Source: me
 * Description: Segment tree with ability to add or set values of large intervals, and compute max of intervals.
 * Can be changed to other things.
 * Time: O(\log N).
 * Usage: Segtree tree(n, v);
 * Status: stress-tested a bit
 */
#pragma once

struct SegTree {
    typedef int T;
    const T id = INT_MAX;
    const T lzId = INT_MIN;
    T merge(T a, T b) {
        return max(a, b);
    }
    void lzUpdate(T& a, T lz, int sz) {
        if (lz != lzId)
            a = lz * sz;
    }

    int N = 1;
    vector<T> t, lz;
    SegTree(int n, vector<T> values) {
        while (N < n) N *= 2;

        t.resize(2 * N), lz.resize(2 * N, lzId);
        loop(i, n)
            t[N + i] = values[i];
        for (int i = N - 1; i >= 1; i--)
            t[i] = merge(t[2 * i], t[2 * i + 1]);
    }
    void push(int i, int sz) {
        lzUpdate(t[2 * i], lz[i], sz);
        lzUpdate(t[2 * i + 1], lz[i], sz);
        lzUpdate(lz[2 * i], lz[i], 1);
        lzUpdate(lz[2 * i + 1], lz[i], 1);
        lz[i] = lzId;
    }
    void update(int l, int r, T v, int i = 1, int tl = 0, int tr = -1) {
        if (tr == -1) tr = N;
        if (l >= tr || r <= tl) return;
        if (tl >= l && tr <= r)
            lzUpdate(lz[i], v, 1), lzUpdate(t[i], v, tr - tl);
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