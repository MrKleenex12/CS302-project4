// dijsktras.cpp
// Larry Wang - Proj4

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <utility>

using std::cin;
using std::unordered_map;
using std::vector;

struct Map {
  int r, c;
  vector<char> map;
  unordered_map<int, int> titles;
  unordered_map<int, std::unordered_set<int> > adj_list;

  void create_g();
  void print();
  void display_g();
};

// Adds adjacent nodes of current to adj_list
void Map::create_g() {
  for(size_t i = 0; i < map.size(); i++) {
    int i_col = i % c;
    int i_row= i / c;
    // up
    if(i_row > 0)     adj_list[i].insert((i_row - 1) * c + i_col);
    // down 
    if(i_row < r-1)   adj_list[i].insert((i_row + 1) * c + i_col);
    // left
    if(i_col > 0)     adj_list[i].insert((i_row * c) + i_col - 1);
    // right
    if(i_col < c-1)   adj_list[i].insert((i_row * c) + i_col + 1);
  }
}

// Debugging
void Map::print() {
  for(size_t i = 0; i < map.size(); i++) {
    printf("%c ", map[i]);
    if((i + 1) % c == 0)    printf("\n");
  }
}

// Debugging
void Map::display_g() {
  for(size_t i = 0; i <map.size(); i++) {
    printf("%zu: ", i);
    for(auto j = adj_list[i].begin(); j != adj_list[i].end(); j++)
      printf("%i ", *j);
    printf("\n");
  }
}

// MAIN EXECUTION
int main(int argc, char *argv[]) {
  Map m;
  int titles_n, weight;
  char title_name;
  cin >> titles_n;
  for(int i = 0; i < titles_n; i++) {
    cin >> title_name >> weight;
    m.titles[title_name] = weight;
  }
  cin >> m.r >> m.c;
  char temp;
  for(int i = 0; i < m.r * m.c; i++) {
    cin >> temp;
    m.map.push_back(temp);
  }

  std::pair<int, int> start;
  std::pair<int, int> end;
  cin >> start.first >> start.second >> end.first >> end.second;

  // m.print();
  m.create_g();
  // m.display_g();
}

