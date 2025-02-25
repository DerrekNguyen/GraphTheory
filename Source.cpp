#include "graph.cpp"
#include "examples.hpp"
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
   // GRAPH GENERATION HERE
   // current graph: example graph 3

   graph::dgraph<int> t;
   generateGraph4(t);

   // END OF GRAPH GENERATION

   graph::dgraph<int>::floydWarshall dp(t);

   for (const auto& v : dp.getDistance()) {
      for (const auto& i : v) std::cout << i << " ";
      std::cout << std::endl;
   }
   
   return 0;
}