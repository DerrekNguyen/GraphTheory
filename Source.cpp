#include "graph.cpp"
#include <fstream>

////////////////////////////////////////////
// SIDE ALGORITHMS
////////////////////////////////////////////

/// <summary>
///  BFS to find shortest path in grids.
/// </summary>
/// <returns> Least amount of moves to reach the end from start. -1 if no path is available. </returns>
int bfsGrid() {
   std::ifstream inFile("input/bfsGrid.txt");

   // Input process
   int m, n;
   std::vector<std::vector<char>> matrix;
   char tempChar;
   std::vector<char> tempMatrix;

   inFile >> m;
   inFile >> n;
   for (int i = 0; i < m; ++i) {
      tempMatrix.clear();
      for (int j = 0; j < n; ++j) {
         inFile >> tempChar;
         tempMatrix.push_back(tempChar);
      }
      matrix.push_back(tempMatrix);
   }

   // Variables for the algorithm
   std::vector<std::vector<bool>> visited;
   std::vector<bool> t(n, false);
   for (int i = 0; i < m; ++i) {
      visited.push_back(t);
   }

   std::queue<int> rq;
   std::queue<int> cq;
   std::vector<int> dr = { -1, 1, 0, 0 };
   std::vector<int> dc = { 0, 0, -1, 1 };

   int move_count = 0;
   int nodes_left_in_layer = 1;
   int nodes_in_next_layer = 0;

   bool reached_end = false;

   // BFS
   int r, c;

   // Assuming starting point is (0, 0)
   rq.push(0);
   cq.push(0);
   visited[0][0] = true;

   // Navigate the matrix
   while (!rq.empty()) {
      r = rq.front();
      c = cq.front();
      rq.pop();
      cq.pop();

      if (matrix[r][c] == 'E') {
         reached_end = true;
         break;
      }

      for (int i = 0; i < 4; ++i) {
         int rr = r + dr[i];
         int cc = c + dc[i];

         if (rr < 0 || rr >= m) continue;
         if (cc < 0 || cc >= n) continue;
         if (visited[rr][cc]) continue;
         if (matrix[rr][cc] == '#') continue;

         rq.push(rr);
         cq.push(cc);
         visited[rr][cc] = true;
         nodes_in_next_layer++;
      }

      nodes_left_in_layer--;
      if (nodes_left_in_layer == 0) {
         nodes_left_in_layer = nodes_in_next_layer;
         nodes_in_next_layer = 0;
         move_count++;
      }
   }

   if (reached_end) return move_count;
   return -1;
}

int main() {
   // COPY EXAMPLE GRAPH CODE HERE
   // current graph: example graph 2

   graph::vertice<int> a("A", 1);
   graph::vertice<int> b("B", 2);
   graph::vertice<int> c("C", 3);
   graph::vertice<int> d("D", 4);
   graph::vertice<int> e("E", 5);
   graph::vertice<int> f("F", 6);
   graph::vertice<int> g("G", 7);
   graph::vertice<int> h("H", 8);

   graph::dgraph<int> t;

   t.AddVertice(a);
   t.AddVertice(b);
   t.AddVertice(c);
   t.AddVertice(d);
   t.AddVertice(e);
   t.AddVertice(f);
   t.AddVertice(g);
   t.AddVertice(h);

   t.AddEdge(a, b, 3);
   t.AddEdge(a, c, 6);
   t.AddEdge(b, c, 4);
   t.AddEdge(b, d, 4);
   t.AddEdge(b, e, 11);
   t.AddEdge(c, d, 8);
   t.AddEdge(c, g, 11);
   t.AddEdge(d, e, -4);
   t.AddEdge(d, f, 5);
   t.AddEdge(d, g, 2);
   t.AddEdge(e, h, 9);
   t.AddEdge(f, h, 1);
   t.AddEdge(g, h, 2);

   // END OF EXAMPLE GRAPH CODE
   
   for (auto i : t.dijkstra(0)) std::cout << i << " ";
   return 0;
}