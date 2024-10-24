#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <vector>

using std::vector;
using std::pair;

struct TileSet {
	const vector<pair<char, int>> tiles = {{'f', 3}, {'g', 1}, {'G', 2}, {'h', 4}, {'m', 7}, {'r', 5}};
	std::unique_ptr<std::mt19937> rand_gen;
	std::uniform_int_distribution<size_t> tile_distrib;

	TileSet();

	void print_tiles();
	char random_tile();
};

struct Grid {
	int N;

	TileSet tiles = TileSet();

	void generate();
	void print_grid();
	void print_path();
};

TileSet::TileSet() {
	// Seed RNG
	// ref https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
	std::random_device rd;
	rand_gen.reset(new std::mt19937(rd()));
	tile_distrib = std::uniform_int_distribution<size_t>(0, tiles.size() - 1);
}

void TileSet::print_tiles() {
	std::cout << tiles.size() << '\n';
	for (auto tile : tiles) {
		std::cout << tile.first << ' ' << tile.second << '\n';
	}
}

char TileSet::random_tile() {
	return tiles[tile_distrib(*rand_gen.get())].first;
}

int main (int argc, char *argv[]) {
	if (argc < 2) {
		std::cerr << "usage: ./generate_map {N}\n";
	}	
	Grid grid;
	grid.N = std::stoi(argv[1]);

	// Print tileset
	grid.tiles.print_tiles();
}
