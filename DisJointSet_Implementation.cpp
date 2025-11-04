#include<bits/stdc++.h>
using namespace std;

class DisjointSet {
    vector<int> parent , rank , size;

public:
    DisjointSet(int n) {
        parent.resize(n+1);
        rank.resize(n+1);
        size.resize(n+1 , 1);
        for(int i=0; i<=n; i++) {
            parent[i] = i;
        }
    }

    int findParent(int u) {
        if(u == parent[u]) {
            return u;
        }

        return (parent[u] = findParent(parent[u])); //pathCompression
    }

    void UnionByRank(int u , int v) {
        int ultimateParent_u = findParent(u);
        int ultimateParent_v = findParent(v);

        if(ultimateParent_u == ultimateParent_v) return;
        int r_pu = rank[ultimateParent_u];
        int r_pv = rank[ultimateParent_v];

        if(r_pu != r_pv) {
            if(r_pu < r_pv) {
                parent[ultimateParent_u] = ultimateParent_v;
            } else {
                parent[ultimateParent_v] = ultimateParent_u;
            }
        } else {
            parent[ultimateParent_v] = ultimateParent_u;
            rank[ultimateParent_u]++;
        }
    }

    void UnionBySize(int u , int v) {
        int ultimateParent_u = findParent(u);
        int ultimateParent_v = findParent(v);

        if(ultimateParent_u == ultimateParent_v) return;
        int s_pu = size[ultimateParent_u];
        int s_pv = size[ultimateParent_v];

        if(s_pu != s_pv) {
            if(s_pu < s_pv) {
                parent[ultimateParent_u] = ultimateParent_v;
                size[ultimateParent_v] += size[ultimateParent_u];
            } else {
                parent[ultimateParent_v] = ultimateParent_u;
                size[ultimateParent_u] += size[ultimateParent_v];
            }
        } else {
            parent[ultimateParent_v] = ultimateParent_u;
            size[ultimateParent_u] += size[ultimateParent_v];
        }
    }
};

//In the program, use either of the one : rank or size 
//Size is more intuitive, rank :: distorted.

int main() {
    DisjointSet ds(7);
    ds.UnionBySize(1,2);
    ds.UnionBySize(2,3);
    ds.UnionBySize(4,5);
    ds.UnionBySize(6,7);
    ds.UnionBySize(5,6);

    //check if 3 , 7 are in the same component or not.
    if(ds.findParent(3) == ds.findParent(7)) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }

    ds.UnionBySize(3,7);

    //check if 3 , 7 are in the same component or not.
    if(ds.findParent(3) == ds.findParent(7)) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }

    return 0;
}
