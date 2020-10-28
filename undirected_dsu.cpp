/* 
   author: rishi_mohan
   created_at: Wed 28 Oct 2020 05:56 PM
*/

#include<bits/stdc++.h>
using namespace std;

const int mxn = 1e5+1;
vector<pair<int,int>> adj;
vector<int> v;

// assign -1 to the whole node value
void make_set(int n){
    for(int i=1; i<=n; i++){
        v[i] = -1;
    }
}

// recurssive code for finding root of the node
// if value is -1 then it means we get the root then return that value
int find(int u){
    if(v[u]==-1) return u;
    return find(v[u]);
}

// first find the absolute root of both node and then assign one root to the other
void union1(int to, int from){
    if(to!=from) v[to] = from;
}

bool isCycle(){
    // traverse the adjacency list of pair
    // here every edge is taken as pair
    for(auto i: adj){
        // finding the absolute root of the first node and second node
        int root_of_to = find(i.first);
        int root_of_from = find(i.second);

        // if absolute root of both node is same then it means they both belongs to the same set 
        // it is only possible when graph contains cycle
        if(root_of_to == root_of_from) {
            return true;
        }

        // if not then merge both set
        union1(root_of_to, root_of_from);
    }
    return false;
}

void solve(){
    int vertices, edges;
    cin >> vertices >> edges;
    
    // this is also done at the time of declaration
    v.resize(vertices+1);
    make_set(vertices);

    for(int i=0; i<edges; i++){
        int u, v;
        cin >> u >> v;
        adj.push_back({u,v});
    }

    if(isCycle()) cout << "YES" << '\n';
    else cout << "NO" << '\n';
    
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int t = 1;
    while(t--)
		solve();
}

