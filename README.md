*Writeup

Larry worked on the parsing and set up the adj_lists and functions of the Map struct

Keith worked on dijkstras and printing out the correct paths and total cost

1 - We used an adjacency list to store the map. The neighbors of a node would be the tiles up,
down, left, and right of it

2 -  O((V+E)log V).
Adjacency List: represents graph connections and weights. O(n)
Priority Queue: Manages nodes based on their shortest known distances using a min-heap. O(logv)
Distance Array: Tracks the shortest known distance to each node. O(n)
Ideal Edges Array: Records the shortest path’s predecessors for path reconstruction.

3 - 

| N             | Elapsed Time  | Memory Usage   |
|---------------|---------------|----------------|
| 10            | ...           | ...            |
| 20            | ...           | ...            |
| 50            | ...           | ...            |
| 100           | ...           | ...            |
| 200           | ...           | ...            |
| 500           | ...           | ...            |
| 1000          | ...           | ...            |
|---------------|---------------|----------------|
