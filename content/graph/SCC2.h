/**
 * Author: Jelle van der Drift
 * Date: 2025-09-07
 * License: CC0
 * Source: https://cp-algorithms.com/graph/strongly-connected-components.html
 * Description: Finds all biconnected components in an undirected graph, returns the components and
 * a new graph formed by them. Usage: vvi adj2; vvi components = stronglyConnected(adj, adj2); Time:
 * O(E + V) Status: tested by upsolve F from BAPC 2025
 */
#pragma once

vector<bool> vis;
void dfs(int v, const vvi& adj, vi& output)
{
    vis[v] = true;
    for (auto u : adj[v])
        if (!vis[u]) dfs(u, adj, output);
    output.push_back(v);
}

vvi stronglyConnected(const vvi& adj, vvi& adjCond)
{
    int n = adj.size();
    vvi comps, adjRev(n);
    vi order, roots(n);

    vis.assign(n, false);
    for (int i = 0; i < n; i++)
        if (!vis[i]) dfs(i, adj, order);

    for (int v = 0; v < n; v++)
        for (int u : adj[v]) adjRev[u].push_back(v);

    vis.assign(n, false);
    reverse(all(order));
    for (auto v : order)
        if (!vis[v])
        {
            vi comp;
            dfs(v, adjRev, comp);

            comps.push_back(comp);
            for (auto u : comp) roots[u] = comps.size() - 1;
        }

    adjCond.assign(comps.size(), {});
    for (int v = 0; v < n; v++)
        for (auto u : adj[v])
            if (roots[v] != roots[u]) adjCond[roots[v]].push_back(roots[u]);

    return comps;
}
