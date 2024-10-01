#ifndef GRAPH_CPP
#define GRAPH_CPP

#include "graph.hpp"

//////////////////////////////////////////
// START OF INDEXED PRIORITY QUEUE
//////////////////////////////////////////

// Implementation for the Indexed Min Priority Queue.

template<typename T>
bool MinIndexedPriorityQueue<T>::contain(int ki) const {
   if (ki < size && ki >= 0)
      return ((*pm)[ki] != -1);
   return false;
}

template<typename T>
void MinIndexedPriorityQueue<T>::insert(int ki, T value) {
   assert(!contain(ki));

   minHeap->push_back(value);
   (*pm)[ki] = minHeap->size() - 1;
   (*im)[minHeap->size() - 1] = ki;

   swim(minHeap->size() - 1);
}

template<typename T>
void MinIndexedPriorityQueue<T>::remove(int ki) {
   assert(contain(ki));

   int oldIndex = (*pm)[ki];
   swap(oldIndex, minHeap->size() - 1);
   (*pm)[ki] = -1;
   (*im)[minHeap->size() - 1] = -1;
   minHeap->pop_back();
   
   sink(oldIndex);
}

template<typename T>
void MinIndexedPriorityQueue<T>::update(int ki, T value) {
   if (value < (*minHeap)[(*pm)[ki]]) {
      (*minHeap)[(*pm)[ki]] = value;
      swim((*pm)[ki]);
   }
   else {
      (*minHeap)[(*pm)[ki]] = value;
      sink((*pm)[ki]);
   }
}

template<typename T>
T MinIndexedPriorityQueue<T>::pop() {
   T minValue = (*minHeap)[0];
   remove((*im)[0]);
   return minValue;
}

template<typename T>
void MinIndexedPriorityQueue<T>::swap(int i, int j) {
   T temp = (*minHeap)[i];
   (*minHeap)[i] = (*minHeap)[j];
   (*minHeap)[j] = temp;

   int tempIndex = (*pm)[(*im)[i]];
   (*pm)[(*im)[i]] = (*pm)[(*im)[j]];
   (*pm)[(*im)[j]] = tempIndex;

   tempIndex = (*im)[i];
   (*im)[i] = (*im)[j];
   (*im)[j] = tempIndex;
}

template<typename T>
int MinIndexedPriorityQueue<T>::parent(int index) {
   int result = (index - 1) / 2;
   if (result >= 0) 
      return result;
   return -1;
}

template<typename T>
int MinIndexedPriorityQueue<T>::minChild(int index) {
   int c1 = 2 * index + 1;
   int c2 = 2 * index + 2;
   if (c1 < minHeap->size()) {
      if (c2 < minHeap->size()) {
         if ((*minHeap)[c1] < (*minHeap)[c2])
            return c1;
         return c2;
      }
      return c1;
   }
   return -1;
}

template<typename T>
void MinIndexedPriorityQueue<T>::swim(int index) {
   while (parent(index) != -1 && (*minHeap)[parent(index)] > (*minHeap)[index]) {
      swap(index, parent(index));
      index = parent(index);
   }
}

template<typename T>
void MinIndexedPriorityQueue<T>::sink(int index) {
   while (minChild(index) != -1 && (*minHeap)[minChild(index)] < (*minHeap)[index]) {
      int newIndex = minChild(index);
      swap(index, newIndex);
      index = newIndex;
   }
}

//////////////////////////////////////////
// END OF INDEXED PRIORITY QUEUE
//////////////////////////////////////////

// Implementation for class 'graph'
template<typename T>
void graph::graph<T>::AddVertice(vertice<T>& newNode) {
   if (dataMap.find(newNode.GetId()) == dataMap.end()) {
      dataMap[newNode.GetId()] = &newNode;
      ++size;
   }
}

template<typename T>
graph::vertice<T>& graph::graph<T>::GetVertice(int id) {
   assert(dataMap.find(id) != dataMap.end());
   return (dataMap[id]);
}

//////////////////////////////////////////
// ALGORITHMS
//////////////////////////////////////////

/// <summary>
/// Depth first search algorithm.
/// </summary>
template<typename T>
void graph::graph<T>::dfs(std::vector<bool>& visited, int at) {
   assert(dataMap.find(at) != dataMap.end());

   visited[at] = true;

   if (adjList.find(at) != adjList.end()) {
      for (int i = 0; i < adjList[at].size(); ++i) {
         if (!visited[adjList[at][i].first])
            dfs(visited, adjList[at][i].first);
      }
   }
}

/// <summary>
/// Breadth first search algorithm.
/// </summary>
template<typename T>
void graph::graph<T>::bfs(std::vector<bool>& visited, int head) {
   assert(dataMap.find(head) != dataMap.end());

   std::queue<int> q;
   q.push(head);

   while (!q.empty()) {
      int at = q.front();
      q.pop();
      visited[at] = true;
      for (int i = 0; i < adjList[at].size(); ++i) {
         if (!visited[adjList[at][i].first]) {
            q.push(adjList[at][i].first);
         }
      }
   }
}

/// <summary>
/// Topological sort algorithm.
/// </summary>
/// <returns>A std::deque storing all vertices in topological order.</returns>
template<typename T>
std::deque<graph::vertice<T>> graph::graph<T>::topSort(std::vector<bool>& visited) {
   std::deque<vertice<T>> result;

   for (auto v : adjList) {
      if (!visited[v.first]) {
         dfs(v.first, result, visited);
      }
   }

   return result;
}

// Helper dfs for topological sort
template<typename T>
void graph::graph<T>::dfs(int v, std::deque<vertice<T>>& result, std::vector<bool>& visited) {
   visited[v] = true;

   for (int i = 0; i < adjList[v].size(); ++i) {
      if (!visited[adjList[v][i].first])
         dfs(adjList[v][i].first, result, visited);
   }

   result.push_front(*dataMap[v]);
}

/// <summary>
/// Single Source Shortest Path algorithm for a DAG.
/// </summary>
/// <returns> a vector containing the shortest distances, sorted in ascending order of the Ids of the vertices </returns>
template<typename T>
std::vector<int> graph::graph<T>::ssspOnDAG() {
   std::vector<bool> visited(this->GetSize(), false);
   std::vector<int> dist(this->GetSize(), INT16_MAX);
   std::deque<vertice<T>> order = this->topSort(visited);

   dist[0] = 0;
   for (int i = 0; i < this->GetSize(); i++) {
      for (auto& p : adjList[order[i].GetId()]) {
         if (p.second + dist[order[i].GetId()] < dist[p.first])
            dist[p.first] = p.second + dist[order[i].GetId()];
      }
   }

   return dist;
}

/// <summary>
/// Single Source Longest Path algorithm for a DAG.
/// </summary>
/// <returns> a vector containing the longest distances, sorted in ascending order of the Ids of the vertices </returns>
template<typename T>
std::vector<int> graph::graph<T>::sslpOnDAG() {
   std::vector<bool> visited(this->GetSize(), false);
   std::vector<int> dist(this->GetSize(), INT16_MAX);
   std::deque<vertice<T>> order = this->topSort(visited);

   dist[0] = 0;
   for (int i = 0; i < this->GetSize(); i++) {
      for (auto& p : adjList[order[i].GetId()]) {
         if ((p.second * -1) + dist[order[i].GetId()] < dist[p.first])
            dist[p.first] = (p.second * -1) + dist[order[i].GetId()];
      }
   }

   std::transform(dist.begin(), dist.end(), dist.begin(), [](int i) { return i * -1; });
   return dist;
}

/// <summary>
/// Dijkstra's algorithm. 
/// Eager variation which uses a min Indexed Priority Queue.
/// </summary>
/// <param name="s"> - Id of start node </param>
/// <returns>Distance vector containing the shortest distance from s. Indexed by Id</returns>
template<typename T>
std::vector<int> graph::graph<T>::dijkstra(int s) {
   std::vector<int> dist(GetSize(), INT_MAX);
   std::vector<bool> visited(GetSize(), false);
   MinIndexedPriorityQueue<distancePair> q(GetSize());

   dist[s] = 0;
   q.insert(s, distancePair(s, dist[s]));

   while (!q.isEmpty()) {
      distancePair top = q.pop();
      visited[top.first] = true;
      for (auto& p : adjList[top.first]) {
         if (!visited[p.first] && dist[top.first] + p.second < dist[p.first]) {
            dist[p.first] = dist[top.first] + p.second;
            distancePair t(p.first, dist[p.first]);
            if (!q.contain(p.first))
               q.insert(p.first, t);
            else q.update(p.first, t);
         }
      }
   } 

   return dist;
}

#endif