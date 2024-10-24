// dijsktras.cpp
// Larry Wang - Proj4

#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <utility>
#include <queue>
#include <climits>

using std::cin;
using std::pair;
using std::unordered_map;
using std::vector;
using std::unique_ptr;

// A weight graph edge
// ref: my challenge06 implementation - KS
struct Edge {
	size_t from, to; // Vertice index the edge connects to
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
    size_t col = i % c;
    size_t i_row = i / c;
    // up
    if (i_row > 0) {
			size_t dst = ((i_row - 1) * c) + col;
      adj_list[i].push_back(Edge{
					.from = i, .to = ((i_row - 1) * c + col),
					.weight = tile_weights[i]});
		}
    // down
    if (i_row < r - 1) {
			adj_list[i].push_back(Edge{
					.from = i, .to = (i_row + 1) * c + col,
					.weight = tile_weights[i]
					});
		}
    // left
    if (col > 0) {
			adj_list[i].push_back(Edge{
					.from = i, .to = (i_row * c) + col - 1,
					.weight = tile_weights[i]
					});
		}
    // right
    if (col < c - 1) {
			adj_list[i].push_back(Edge{
					.from = i, .to = (i_row * c) + col + 1,
					.weight = tile_weights[i]
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
      printf("%zu ", j->to);
    printf("\n");
  }
}


// Dijkstra's
void Map::dijkstras(pair<int, int> start_coords, pair<int, int> end_coords) {
  int cost;
	int start = start_coords.first*c + start_coords.second;
	int end = end_coords.first*c + end_coords.second;

  // Score all current paths to take
  std::priority_queue<pair<int, int>, vector<pair<int, int>>, std::greater<pair<int, int>>> pq;
  // Stores all the distances from strt node
	vector<int> dists(r * c, INT_MAX);
	dists[start] = 0;
	// Stores adj edges associated with the shortest distance from strt node
	vector<int> ideal_edges(r * c, -1);
  // Visited;
  vector<int> visited(r * c, 0);
  // Paths taken to get to trgt
  std::map<int, int> paths;
  // initialize distances as infinity and strt as 0
  for (int i = 0; i < r * c; i++) {
		pq.push({dists[i], i});
	}
 
	// Process until the shortest known path is to the target node
  while (pq.top().second != end) {
		// Pop node w/ shortest path
    pair<int,int> cur = pq.top();
    pq.pop();

		// Don't proceed if we know a better path to this node
    if(cur.first > dists[cur.second])
      continue;
      
    auto neighbors = adj_list[cur.second];
		for (auto edge : adj_list[cur.second]) {
			int distance = cur.first + edge.weight;
			if (distance < dists[cur.second]) {
				dists[edge.to] = distance;
				ideal_edges[edge.to] = edge.from;
				pq.push({distance, cur.second});
			}
		}
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
  // m.display_g();
}
