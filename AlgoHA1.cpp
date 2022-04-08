#include <iostream>
#include <unordered_map>
#include <vector>
#include <set>

using namespace std;
struct Node {
public:
     long long edge;
     long long node ;
    Node( long long num,  long long distance) : node(num), edge(distance) {}
    bool operator<(const Node &other) const {
        if (edge == other.edge) return node < other.node;
        return edge < other.edge;
    }
};
class Func_create_DirGr {
private:
     long long n_s, s_val, t_val;
    unordered_map< long long, unordered_map< long long,  long long>> fsearch;
    unordered_map< long long, unordered_map< long long,  long long>> bsearch;
public:
    bool connected = false;
    Func_create_DirGr( long long n) {
        n_s = n;
    }
    void add_path( long long begining,  long long ending,  long long w) {
        fsearch[begining][ending] = w;
        bsearch[ending][begining] = w;
    }
    void source_target( long long s,  long long t) {
        s_val = s;
        t_val = t;
    }
    vector< long long> search_algo_vector( long long d,bool direction) {
        vector< long long> distance(n_s, d+10);
        set<Node> queue;
        vector< long long> number_of_ways_to_insert_edge;
        //initializes the distances of source and target
        (direction ? distance[s_val] = 0 : distance[t_val] = 0);
        (direction ? queue.insert(Node(s_val, 0)) : queue.insert(Node(t_val, 0)));
        while (!queue.empty()) {
            //withdraw an element from queue
            Node shortest_node = *queue.begin();
            queue.erase(queue.begin());
            //takes name of the node with shortest distance
             long long where_i_am = shortest_node.node;
            //takes length of the edge to the node with shortest
             long long nearest_node_path = shortest_node.edge;
            number_of_ways_to_insert_edge.push_back(nearest_node_path);
            if ((where_i_am == t_val) && direction && nearest_node_path <= d) {
                // checks if the source and target are connected with distance <=d
                connected = true;
                break;
            }
            //Applies single-source search to find shortest path from source to any node
            for (auto connected_nodes : (direction ? fsearch[where_i_am] : bsearch[where_i_am])) {
                // gets the name of the nearest node
                 long long connected_node = connected_nodes.first;
                //gets the distance of the nearst node
                 long long connected_node_w = connected_nodes.second;
                //relaxes the existing distance to a new one
                if (distance[connected_node] > connected_node_w + nearest_node_path  ) {
                    // deletes previous value of distance
                    queue.erase(Node(connected_node, distance[connected_node]));
                    //puts new value of distance to the nearest node
                    distance[connected_node] = nearest_node_path + connected_node_w;
                    //assigns new value of the distance to the nearest node in queue
                    queue.insert(Node(connected_node, distance[connected_node]));
                }
            }
        }
        return number_of_ways_to_insert_edge;
    }
};

// Now we have introduced the functions:
//1) that created a node
//2) combines the node in the graph
//3) applies single-source search for both source and target nodes

int main () {
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

     long long number_of_ways_to_insert_edge = 0;
     long long begining, ending;
     long long n, m, w, s, t, d;
    cin >> n;
    cin >> m;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // initialize the graph
    Func_create_DirGr func_create_DirGr(n);
    for ( long long i = 0; i != m; ++i) {
        cin >> begining >> ending >> w;
        func_create_DirGr.add_path(begining - 1, ending - 1, w);
    }
    cin >> s;
    cin >> t;
    cin >> d;
    func_create_DirGr.source_target(s - 1, t - 1);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Apply bidirectional search on the input graph
    vector< long long> direct_search;
    direct_search = func_create_DirGr.search_algo_vector(d,true);
    vector< long long> back_search;
    back_search = func_create_DirGr.search_algo_vector(d,false);
    

    
    if  (func_create_DirGr.connected) {
        cout << n * (n - 1) << endl;
        return 0;
    }
     long long i = direct_search.size() - 1;
        for ( long long j = 0; j < back_search.size(); ++j) {
            while ((i>-1) && (d-1 < direct_search[i] + back_search[j]) ) {
                i=--i;
            }
            number_of_ways_to_insert_edge += i+1 ;
        }
    cout<<number_of_ways_to_insert_edge;
    ///end
}
