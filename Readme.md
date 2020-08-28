# Path Visualizer
It is application made using c++ and SFML(Simple and fast multimedia library). Aim of this project was to visualize various step taken to find a Path from Start to End node using different alogorithms.

### Links
-[GithubProfile](https://github.com/KrShivanshu)

-[GithubProject](https://github.com/KrShivanshu/PathVisualizer) 

### Algorithms Used are
* A-Star (A*) Algorithm
* Dijkstra's Algorithm
* Breadth First Search (BFS) Algorithm
* Depth First Search (DFS) Algorithm
* Bi-Directional BFS Algorithm

### Node Symbols

![Not Visited](Assets/textures/Cell.png) - Unvisited Node \
![Visited](Assets/textures/visited1().PNG) - Visited Node \
![Visited](Assets/textures/visited2().PNG) - Visited Node \
![Wall](Assets/textures/block().PNG) - Wall Node \
![Path](Assets/textures/path0().PNG) - Path Node \
![Start](Assets/textures/start().PNG) - Start Node \
![End](Assets/textures/end().PNG) - End Node 



**1. A-Star is an informed search algorithm, or a best-first search, meaning that it is formulated in terms of weighted graphs: starting from a specific starting node of a graph, it aims to find a path to the given goal node having the smallest cost (least distance travelled, shortest time, etc.). It does this by maintaining a tree of paths originating at the start node and extending those paths one edge at a time until its termination criterion is satisfied.**

   **At each iteration of its main loop, A* needs to determine which of its paths to extend. It does so based on the cost of the path and an estimate of the cost required to extend the path all the way to the goal. Specifically, A* selects the path that minimizes  {displaystyle f(n)=g(n)+h(n)}**

   **f(n)=g(n)+h(n)**
   
   **where n is the next node on the path, g(n) is the cost of the path from the start node to n, and h(n) is a heuristic function that estimates the cost of the cheapest path from n to the goal. A* terminates when the path it chooses to extend is a path from start to goal or if there are no paths eligible to be extended. The heuristic function is problem-specific. If the heuristic function is admissible, meaning that it never overestimates the actual cost to get to the goal, A* is guaranteed to return a least-cost path from start to goal.**


![A-Star](ScreenShot/Astar.png)
![A-Star](ScreenShot/Astar(2).png)

#

**2. Dijkstra's algorithm (or Dijkstra's Shortest Path First algorithm, SPF algorithm)[2] is an algorithm for finding the shortest paths between nodes in a graph, which may represent, for example, road networks.**
   
   The algorithm exists in many variants. Dijkstra's original algorithm found the shortest path between two given nodes,but a more common variant fixes a single node as the "source" node and finds shortest paths from the source to all other nodes in the graph, producing a shortest-path tree.

   For a given source node in the graph, the algorithm finds the shortest path between that node and every other. It can also be used for finding the shortest paths from a single node to a single destination node by stopping the algorithm once the shortest path to the destination node has been determined.


![Dijkstra](ScreenShot/Dijkstra.png)

#

**3. Breadth-first search (BFS) is an algorithm for traversing or searching tree or graph data structures. It starts at the tree root (or some arbitrary node of a graph, sometimes referred to as a 'search key'), and explores all of the neighbor nodes at the present depth prior to moving on to the nodes at the next depth level.**

   It uses the opposite strategy as depth-first search, which instead explores the node branch as far as possible before being forced to backtrack and expand other nodes.


![BFS](ScreenShot/BFS.png)

#

**4. Depth-first search (DFS) is an algorithm for traversing or searching tree or graph data structures. The algorithm starts at the root node (selecting some arbitrary node as the root node in the case of a graph) and explores as far as possible along each branch before backtracking.**


![DFS](ScreenShot/DFS.png)

#

**5. Bi-Directional BFS is just like BFS with one exception that we start finding for the path from both the ends at the same time.**


![Bi-Directional BFS](ScreenShot/Bi-Directional.png)

#


## Magic Visualizing

![StepByStepVisualizing](ScreenShot/MagicVisualizer.gif)

## Iterative Visualizing

![StepByStepVisualizing](ScreenShot/StepVisualizer.gif)


