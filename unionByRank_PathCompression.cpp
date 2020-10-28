/* 
   author: rishi_mohan
   created_at: Wed 28 Oct 2020 11:41 PM
*/

#include<bits/stdc++.h>
using namespace std;

// NOTES:
// 1. rank of one node is always increased if absolute parent is different of both nodes
// 2. while union always smaller rank parent is linked to higher rank parent 
// 3. instead of calling find function again and again recurssively we use path compression technique 

// structure is used to store rank and parent
// pair is also used in place of struct
struct node{
    int rank;
    int parent;
};

// vector storing rank of node and parent
vector<node> dsu;
// adjacency list
vector<pair<int,int>> adj;

// assigning initial value
void make_set(int vertices){
    for(int i=1; i<=vertices; i++){
            dsu[i].parent = -1;
            dsu[i].rank = 0;
    }
}

int find(int u){
    // if the node is parent of itself
    if(dsu[u].parent == -1) return u;
    return dsu[u].parent = find(dsu[u].parent); // PATH COMPRESSION : to directly link the node to its parent by removing middle man
}

void union1(int root_of_from, int root_of_to){
    // if from <---> to 
    // if from.rank > to.rank then parent of to is same as parent of from 
    // if from.ranl < to.rank then parent of from is same as parent of to
    // else we have two choice either from (to --> from) OR (from --> to) and because rank is same then rank is increased of parent 
    if(dsu[root_of_from].rank > dsu[root_of_to].rank)
        dsu[root_of_to].parent = root_of_from;
    else if(dsu[root_of_from].rank < dsu[root_of_to].rank)
        dsu[root_of_from].parent = root_of_to;
    else{
        dsu[root_of_from].parent = root_of_to;
        dsu[root_of_to].rank += 1;
    }
}
// isCycle function to check whether cycle is present or not
// same as O(vertices*edges) complexity
bool isCycle(){
    // traverse the adjacency list
    for(auto i: adj){
        // find the absolute parent of both node
        int root_of_from = find(i.first);
        int root_of_to = find(i.second);

        // if both parent is same then they belongs to the same set
        if(root_of_to == root_of_from) return true;

        // merge both the set
        union1(root_of_from, root_of_to);
    }
    return false;
}

void solve(){
    // taking input 
    int vertices, edges;
    cin >> vertices >> edges;
    
    dsu.resize(vertices+1);

    // to assign initial value
    make_set(vertices);

    // fill the adjacency list
    for(int i=0; i<edges; i++){
        int u, v;
        cin >> u >> v;
        adj.push_back({u,v});
    }

    // calling isCycle function to check cycle is present or not
    cout << (isCycle()? "YES" : "NO") << '\n';
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int t = 1;
	while(t--)
		solve();
}

