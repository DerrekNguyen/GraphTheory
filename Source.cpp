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
   // current graph: example graph 3

   graph::vertice<int> a("0", 1);
   graph::vertice<int> b("1", 2);
   graph::vertice<int> c("2", 3);
   graph::vertice<int> d("3", 4);
   graph::vertice<int> e("4", 5);
   graph::vertice<int> f("5", 6);
   graph::vertice<int> g("6", 7);
   graph::vertice<int> h("7", 8);
   graph::vertice<int> i("8", 8);
   graph::vertice<int> j("9", 8);

   graph::dgraph<int> t;

   // optional
   t.AddVertice(a);
   t.AddVertice(b);
   t.AddVertice(c);
   t.AddVertice(d);
   t.AddVertice(e);
   t.AddVertice(f);
   t.AddVertice(g);
   t.AddVertice(h);
   t.AddVertice(i);
   t.AddVertice(j);

   t.AddEdge(a, b, 5);
   t.AddEdge(b, c, 20);
   t.AddEdge(c, d, 10);
   t.AddEdge(d, c, -15);
   t.AddEdge(c, e, 75);
   t.AddEdge(b, f, 30);
   t.AddEdge(b, g, 60);
   t.AddEdge(f, g, 5);
   t.AddEdge(g, h, -50);
   t.AddEdge(h, i, -10);
   t.AddEdge(f, i, 50);
   t.AddEdge(f, e, 25);
   t.AddEdge(e, j, 100);

   // END OF EXAMPLE GRAPH CODE

   for (const auto& v : t.bellmanFord(0)) std::cout << v << " ";
   
   return 0;
}