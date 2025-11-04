//KrusKal's Algorithm :: given the vertices are from 0 - V-1 , works for both directed and un-directed graph.

class DisjointSet {
    vector<int> size , parent;
public:
    DisjointSet(int n) {
        size.resize(n , 1);
        parent.resize(n);
        for(int i=0; i<n; i++) {
            parent[i] = i;
        }
    }
    
    int findParent(int node) {
        if(node == parent[node]) {
            return node;
        }
        
        return (parent[node] = findParent(parent[node]));
    }
    
    void UnionBySize(int u , int v) {
        int pu = findParent(u) , pv = findParent(v);
        int s_pu = size[pu] , s_pv = size[pv];
        
        if(s_pu != s_pv) {
            if(s_pu < s_pv) {
                parent[pu] = parent[pv];
                size[pv] += size[pu]; 
            } else {
                parent[pv] = parent[pu];
                size[pu] += size[pv];
            }
        } else {
            parent[pv] = parent[pu];
            size[pu] += size[pv];
        }
    }
};

class Solution { // tc = nlogn + n*4*alpha(*2 if undirected) , sp = n + V
  public:
    int kruskalsMST(int V, vector<vector<int>> &edges) {

        vector<vector<int>> sorted_Edges = edges; // we can also use a min_heap instead , but that would take more space.
        sort(sorted_Edges.begin() , sorted_Edges.end() , [](auto &a , auto &b) { // say edgesCount = n :: tc = nlogn
            return a[2] < b[2];
        });
        
        DisjointSet ds(V);
        int mstSum = 0;
        vector<vector<int>> mst_EdgeList; 
        
        for(auto &e : sorted_Edges) { //e
            int wt = e[2] , u = e[0] , v = e[1];
            
            if(ds.findParent(u) != ds.findParent(v)) { // 4*alpha
                mstSum += wt;
                mst_EdgeList.push_back({u , v , wt});
                
                ds.UnionBySize(u , v);
            }
        }
        
        return mstSum;
    }
};
