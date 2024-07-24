#include<iostream>
#include<vector>
using namespace std;

int find(vector<int> &parent, int x){
    // timecomplexity O(log*(n))
    // this method returns which group/cluster x bellongs to
    return parent[x] = (parent[x] == x ? x : find(parent, parent[x])); // path compression method by union by rank
}

void Union(vector<int> &parent, vector<int> &sz, vector<int> &minimal, vector<int> &maximal, vector<int> &rank, int a, int b){
    // timecomplexity : O(log*(n))
    a = find(parent, a);
    b = find(parent, b);
    if(a == b){ // if a and b are in same sets
        return;
    }
    if(rank[a] >= rank[b]){
        rank[a]++;
        parent[b] = a; 
        sz[a] += sz[b];
        maximal[a] = max(maximal[a], maximal[b]);
        minimal[a] = min(minimal[a], minimal[b]);
    }
    else{
        rank[b]++;
        parent[a] = b;
        sz[b] += sz[a];
        maximal[b] = max(maximal[a], maximal[b]);
        minimal[b] = max(minimal[a], minimal[b]);
    }
}

int main(){

    int n,m;
    cin>>n>>m;
    // n element, m no of queries
    vector<int> parent(n+1);
    vector<int> rank(n+1, 0);
    vector<int> sz(n+1, 1);
    vector<int> minimal(n+1);
    vector<int> maximal(n+1);
    
    for(int i=0;i<=n;i++){
        parent[i] = minimal[i] = maximal[i] = i;
    }

    while(m--){
        string str;
        cin>>str;
        if(str == "union"){
            int x, y;
            cin>>x>>y;
            Union(parent, sz, minimal, maximal, rank, x, y);
        }
        else{
            int x;
            cin>>x;
            x = find(parent, x);
            cout<<minimal[x]<<" "<<maximal[x]<<" "<<sz[x]<<"\n";
        }
    }
    return 0;
}