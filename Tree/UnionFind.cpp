/* UnionFind */
struct UnionFind {
    vector<int> depths;
    vector<int> parents;
    UnionFind(int N=0): depths(N,-1), parents(N) {}
    UnionFind(int N=0) {
        for(int i=0; i<N; i++) {
            parents.at(i) = i;
        }
    }
};