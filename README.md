# Proj4 Keith and Larry

## Contributions

Keith worked on dijkstras(), created the edge struct, and printing out the correct paths and total cost
Larry worked on the reading in from stdin, creating the Map struct, and creating an adjacency list

## Questions

1 - We used an adjacency list to store the vertices and edges. The neighbors of a node would be the tiles up, down, left, and right of it.

2 -  O((V+E)log V).
Adjacency List: represents graph connections and weights. O(n)

Priority Queue: Manages nodes based on their shortest known distances using a min-heap. O(logn)

Distance Array: Tracks the shortest known distance to each node. O(n)

Ideal Edges Array: Records the shortest path’s predecessors for path reconstruction.

3 - Our implementation does not scale well. It uses a bunch of memory. I feel like the jump from 7MB to 173MB from size 200 to size 1000 is kinda crazy. The time also is 20x slower. If we had a queue with decrease_key operation, we could cut down on memory usage.

| N             | Elapsed Time  | Memory Usage   |
|---------------|---------------|----------------|
| 10            | 1.17s         | 96,295         |
| 20            | 1.29s         | 149,575        |
| 50            | 1.60s         | 560,223        |
| 100           | 2.53s         | 1,853,591      |
| 200           | 5.36s         | 7,200,695      |
| 500           | 25.58s        | 43,333,423     |
| 1000          | 98.62s        | 173,783,359    |
|---------------|---------------|----------------|
