
#include <algorithm>
#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
#include <map>
using namespace std;

unsigned int white_parts, black_parts, num_edges;
vector<unsigned int> graph_list[100000];
unsigned int matched[100000];

bool reverse_queue[100000];

typedef struct _vertex {
    char type;
    unsigned int id;
} vertex;



unsigned int tagging_nodes(vertex node) {
    return ((node.type == 'W') ? 0 : white_parts) + node.id;}

vertex uid_to_vertex(unsigned int indeces) {
                vertex ret;
                if (indeces < white_parts) {
                    ret = (vertex) { 'W', indeces };
                } else {
                    ret = (vertex) { 'B', indeces - white_parts };
                }
                ret.type = (indeces < white_parts) ? 'W' : 'B';
                ret.id = (indeces < white_parts) ? indeces : indeces - white_parts;
                return ret;
            }



bool augmentation(unsigned int indeces) {
    reverse_queue[indeces] = true;

    for (unsigned int i = 0; i < graph_list[indeces].size(); i++) {
        unsigned int nearest_node = graph_list[indeces][i];
        if (reverse_queue[nearest_node]) {
            continue;}
        if (matched[nearest_node] == 0xffffffff) {
            matched[nearest_node] = indeces;
            matched[indeces] = nearest_node;
            return true;
        } else if (matched[nearest_node] != indeces) {
            reverse_queue[nearest_node] = true;
            if (augmentation(matched[nearest_node])) {
                matched[indeces] = nearest_node;
                matched[nearest_node] = indeces;
                return true;}}}
    return false;}
int main() {
    fill(matched, matched + 100000, 0xffffffff);
    int m, n;
    cin >> m >> n;
    vector<int> odd(n, 0);
    vector<int> even(n,0);
    map<int, vector<int>> white_list;
    int black_size;
    black_size = 0;
    int previous_edge;
   
    int num_edges = 0;
   
    int connect = 1;
    unsigned int white_indeces;
    unsigned int black_indeces;
    unsigned int result = 0;
    
    for (int i = 0; i <= m*n; i++){
        white_list[i].size();
    }
    
    for (int i = 0; i < m; i++) {
        if (connect==1){
            connect = 0;
        }
        else{
            connect = 1;
        }
    
        vector<int>& white_vec = (i % 2 == 0)?  even : odd;
        vector<int>& black_vec = (i % 2 == 0)?  odd : even;
    
        white_vec.clear();
        previous_edge = 0;
        for (int j = 0; j < n; j++) {
            char input;
            int free_cell;
            cin >> input;
            if (input == '.'){
                free_cell = 1;}
            else{
                free_cell = 0;}
            white_vec.push_back(free_cell);
            if (free_cell == 1) {
                if ((connect + j) % 2 == 0) {
                    if (black_vec[j] == 1) {
                        white_list[((i * n)+ j )].push_back(((i-1)*n)+j );
                        num_edges++;}
                    if (previous_edge == 1) {
                        white_list[((i * n)+j )].push_back((i*n) + (j - 1));
                        num_edges++;}}
                else {
                    black_size++;
                    if (black_vec[j] == 1) {
                        white_list[((i-1) * n) +j].push_back((i * n) +j );
                        num_edges++;}
                    if (previous_edge == 1) {
                        white_list[(i * n)+ (j - 1)].push_back((i * n)+j );
                        num_edges++;}}}
            previous_edge = free_cell;}}
    int whitee_size;
    whitee_size = white_list.size();
    vector<vector<int>> tags_ids;
    for (auto& i: white_list){
        if (i.second.size() != 0){
            for (auto& z: i.second){
                tags_ids.push_back({i.first, z});}}}
    white_parts = whitee_size;
    black_parts = black_size;
    num_edges = num_edges;
    vertex white_vertices, black_vertices;
    for (unsigned int i = 0; i < num_edges; i++) {
        white_vertices.type = 'W';
        black_vertices.type = 'B';
        white_vertices.id = tags_ids[i][0];
        black_vertices.id = tags_ids[i][1];
        white_indeces = tagging_nodes(white_vertices);
        black_indeces = tagging_nodes(black_vertices);
        graph_list[white_indeces].push_back(black_indeces);
        graph_list[black_indeces].push_back(white_indeces);}
    for (unsigned int i = 0; i < white_parts; i++) {
        if (matched[i] == 0xffffffff) {
            fill(reverse_queue, reverse_queue + 100000, false);
            if (augmentation(i)) {
                result++;}}}
    cout <<result<<endl;
   
    return 0;
}

