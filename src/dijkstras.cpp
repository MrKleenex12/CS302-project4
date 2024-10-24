// dijsktras.cpp
// Larry Wang - Proj4

#include <cassert>
#include <iostream>
#include <limits>
#include <vector>
#include <unordered_map>
#include <map>
#include <utility>
#include <queue>
#include <climits>

using std::cin;
using std::pair;
using std::unordered_map;
using std::vector;

// A weight graph edge
// ref: my challenge06 implementation - KS
struct Edge {
	int from, to; // Vertice index the edge connects to
	int weight; // Weight of the edge
};

struct Map
{
  int r, c;
  vector<char> map;
  unordered_map<char, int> tile_weights;
  unordered_map<int, vector<Edge>> adj_list;

  void init_adj();
  void print();
  void display_g();
  void dijkstras(pair<int, int> strt, pair<int, int> trgt);
};

// Adds adjacent nodes of current to adj_list
void Map::init_adj()
{
  for (size_t i = 0; i < map.size(); i++)
  {
    int col = (int)i % c;
    int row = (int)i / c;
    // up
    if (row > 0) {
			int dst = (row - 1)*c + col;
      adj_list[i].push_back(Edge{
					.from = (int)i, .to = dst,
					.weight = tile_weights[map[i]]});
		}
    // down
    if (row < r - 1) {
			int dst = (row + 1) * c + col;
			adj_list[i].push_back(Edge{
					.from = (int)i, .to = dst,
					.weight = tile_weights[map[i]]
					});
		}
    // left
    if (col > 0) {
			int dst = (row * c) + col - 1;
			adj_list[i].push_back(Edge{
					.from = (int)i, .to = dst,
					.weight = tile_weights[map[i]]
					});
		}
    // right
    if (col < c - 1) {
			int dst = (row * c) + col + 1;
			adj_list[i].push_back(Edge{
					.from = (int)i, .to = dst,
					.weight = tile_weights[map[i]]
					});
		}
  }
}

// Debugging
void Map::print()
{
  for (size_t i = 0; i < map.size(); i++)
  {
    printf("%c ", map[i]);
    if ((i + 1) % c == 0)
      printf("\n");
  }
}
// Debugging
void Map::display_g()
{
  for (size_t i = 0; i < map.size(); i++)
  {
    printf("%zu: ", i);
    for (auto j = adj_list[i].begin(); j != adj_list[i].end(); j++)
      printf("%d ", j->weight);
    printf("\n");
  }
}


// Dijkstra's
void Map::dijkstras(pair<int, int> start_coords, pair<int, int> end_coords) {
	int start = start_coords.first*c + start_coords.second;
	int end = end_coords.first*c + end_coords.second;

  // Score all current paths to take
  std::priority_queue<pair<int, int>, vector<pair<int, int>>, std::greater<pair<int, int>>> pq;
  // Stores all the distances from strt node
	vector<int> dists(r * c);
	for (size_t i = 0; i < dists.size(); i++) {
		dists[i] = INT_MAX;
	}
	dists[start] = 0;
	// Stores adj edges associated with the shortest distance from strt node
	vector<int> ideal_edges(r * c);
	for (size_t i = 0; i < ideal_edges.size(); i++) {
		ideal_edges[i] = -1;
	}
  // Paths taken to get to trgt
  std::map<int, int> paths;
  // initialize distances as infinity and strt as 0
  for (int i = 0; i < r * c; i++) {
		pq.push({dists[i], i});
	}
 
	// Process until the shortest known path is to the target node
  while (!pq.empty()) {
		//first  Pop node w/ shortest path
    pair<int,int> cur = pq.top();
    pq.pop();

		// Don't proceed if we know a better path to this node
    if(cur.first > dists[cur.second])
      continue;
      
		for (auto edge : adj_list[cur.second]) {
			int distance = cur.first + edge.weight;
			if (distance < dists[edge.to]) {
				dists[edge.to] = distance;
				ideal_edges[edge.to] = cur.second;
				pq.push({distance, edge.to});
			}
		}
  }

	// Print total cost
	std::cout << dists[end] << '\n';
	// Construct the shortest route by backtracking
	vector<std::pair<int, int>> path;
	for (auto dst = end; dst != -1; dst = ideal_edges[dst]) {
		int row = dst / c;
		int col = dst % c;
		path.push_back({row, col});
	}
	for (auto it = path.rbegin(); it != path.rend(); it++) {
		std::cout << it->first << ' ' << it->second << '\n';
	}
}

// MAIN EXECUTION
int main(int argc, char *argv[])
{
  Map m;
  int n_tiles;
  cin >> n_tiles;

	char tile;
	int weight;
  for (int i = 0; i < n_tiles; i++)
  {
    cin >> tile >> weight;
    m.tile_weights[tile] = weight;
  }
  cin >> m.r >> m.c;
  char temp;
  for (int i = 0; i < m.r * m.c; i++)
  {
    cin >> temp;
    m.map.push_back(temp);
  }

  pair<int, int> start;
  pair<int, int> end;
  cin >> start.first >> start.second >> end.first >> end.second;

  // m.print();
  m.init_adj();
	m.dijkstras(start, end);
}
