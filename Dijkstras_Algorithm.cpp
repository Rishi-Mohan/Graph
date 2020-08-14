#include<bits/stdc++.h>
using namespace std;

const int m = 1e6+1;
const int INF = 1e9;

/* Example:
           [1] ----5---- [2]
            |\
           2| \6
            |  \
         [3]|-1--\ [4]
         /
       5/
    [5]/
        From 1 to: (2,5) (3,2) (4,6)
        From 2 to:
        From 3 to: (4,1) (5,5)
        From 4 to:
        From 5 to:
        // Dijkstra method processing
        node: 1 weight: 0
        node: 3 weight: 2
        node: 4 weight: 3
        node: 2 weight: 5
        node: 4 weight: 6
        node: 5 weight: 7

        Minimum Distance from source to each vertex
        from 1 to 2 : Distance is 5
        from 1 to 3 : Distance is 2
        from 1 to 4 : Distance is 3
        from 1 to 5 : Distance is 7
*/


vector<vector<pair<int,int>>> adj(m); // First is vertex; Second is Weight

int vertex , edges;
int v , u, dis;

// we set all node distance to be INfinity except source vertex
vector<int> dist(m,INF);
// set all False
vector<bool> vis(m,0); // it helps us to track which node is visited and if visited (means true) then continue

void dijkstra()
{
        // source vertex distance to be 0
        dist[1] = 0;
        // it is used because of min-priority queue How?
        // Multiset always sorted by first element
        // here we used thats property and insert weight of edge as first element and vertes as second
        multiset<pair<int,int>> s;
        // inserting the source vertex as 0 weight and vertex is 1
        s.insert({0,1}); // FIRST IS DISTANCE; SECOND IS NODE

        // while multiset is not empty
        while(!s.empty())
        {
                // take first pair because that contain minimum weight as required by algo
                pair<int,int> p = *s.begin();
                // delete that pair
                s.erase(s.begin());
                // second element is node and first element is weight
                int node = p.second;
                int weight = p.first;

                cout << "node: " << node << " " << "weight: " << weight << endl;

                // if that vertex is already processed then continue;
                if(vis[node]) continue;
                // else set as true (or processed)
                vis[node] = true;
                // Now traverse all node connected to that vertex
                for(auto i : adj[node])
                {
                // NOTE: In adj we insert pair as <node,weight> but in MULTISET <weight,node>(because of req.)
                        int cur_vertex = i.first;
                        int cur_weight = i.second;
                // if distance of node(means under processing vertex) + cur_weight(means distance from node to current_vertex)
                // is minimum then already present node then update the dist array
                        if(dist[node] + cur_weight < dist[cur_vertex])
                        {
                                dist[cur_vertex] = dist[node] + cur_weight;
                                // after updating insert the new vertex as updated_distance and cur_vertex
                                s.insert({dist[cur_vertex],cur_vertex});
                        }
                }
        }

}
int main()
{
        ios_base::sync_with_stdio(0);
        cin.tie(0);
        cout.tie(0);

        cin >> vertex >> edges;
        for (int i = 0; i < edges; ++i)
        {
                cin >> u >> v >> dis;
                // Here i construct a vector of vector of pair, In General case we construct
                // vector of vector of element
                // pair is used because we have to store the weight of the edges as well
                // so u -> v having weight "dis"
                // undirected graph
                adj[u].push_back({v,dis});

        }
        for(int i=1;i<=vertex;i++)
        {
                cout << "From " << i << " to: ";
                for(auto u : adj[i]) cout << "(" << u.first << "," << u.second << ")" << " ";
                cout << endl;
        }
        cout << endl;
        dijkstra(); // Calling the method
        cout << endl;
        cout << "Minimum Distance from source to each vertex" << endl;
        for(int i=2;i<=vertex;i++)
        {
                cout << "from 1 to " << i << " : Distance is ";
                cout << dist[i] << endl;
        }
        cout << endl;

}
