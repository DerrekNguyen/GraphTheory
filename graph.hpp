/*
   Graph Theory algorithms.
*/

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <cassert>
#include <unordered_map>
#include <vector>
#include <set>
#include <iostream>
#include <queue>

/*
Indexed Priority Queue. Uses binary min heap
*/
template<typename T>
class MinIndexedPriorityQueue { 
public:
   MinIndexedPriorityQueue(int size_) {
      size = size_;
      pm = new std::vector<int>(size_, -1);
      im = new std::vector<int>(size_, -1);
      minHeap = new std::vector<T>;
   };

   T getMin() { return (*minHeap)[0]; }
   int getSize() const { return minHeap->size(); }
   bool isEmpty() const { return minHeap->size() == 0; }

   bool contain(int) const;
   void insert(int, T);
   void remove(int);
   void update(int, T);
   T pop();

   // Helper functions
   void swap(int, int);
   int parent(int);
   int minChild(int);
   void swim(int);
   void sink(int);
private:

   /*
   The size of ALL potential elements, not just the ones contained in the heap.
   */
   int size;

   /* 
   The Position Map (pm) maps Key Indexes (ki) to where the position of that
   key is represented in the priority queue in the domain [0, size).
   */
   std::vector<int>* pm;

   /* 
   The Inverse Map (im) stores the indexes of the keys in the range
   [0, size) which make up the priority queue. It should be noted that
   "im" and "pm" are inverses of each other, so: pm[im[i]] = im[pm[i]] = i
   */
   std::vector<int>* im;

   /*
   The Min Heap that stores the content of the priority queue.
   The first element is always the smallest
   */
   std::vector<T>* minHeap;
};

/*
Helper object for dijkstra
*/
class distancePair {
public:
   distancePair() : first(-1), second(-1) {};
   distancePair(int first_, int second_) : distancePair() {
      first = first_;
      second = second_;
   }
   distancePair(const distancePair &obj) {
      first = obj.first;
      second = obj.second;
   }

   bool operator< (const distancePair& rhs) {
      return (second < rhs.second);
   }

   bool operator> (const distancePair& rhs) {
      return (second > rhs.second);
   }

   bool operator== (const distancePair& rhs) {
      return (second == rhs.second);
   }

   bool operator!= (const distancePair& rhs) {
      return !(*this == rhs);
   }

   distancePair& operator= (distancePair rhs) {
      if (this != &rhs)
         swap(rhs);
      return *this;
   }

   void swap(distancePair& rhs) {
      int t = first;
      first = rhs.first;
      rhs.first = t;

      t = second;
      second = rhs.second;
      rhs.second = t;
   }

   int first;
   int second;
};

namespace graph {
   template<typename T>
   class graph;
   template<typename T>
   class dgraph;
   template<typename T>
   class ugraph;
   template<typename T>
   class algorithm;

   typedef std::size_t id;
   static id baseId = 0;

   // REQUIRES: name of all vertices are unique.
   template<typename T>
   class vertice {
   public:
      vertice() { Id = baseId++; };
      vertice(std::string Name) : vertice() { name = Name; };
      vertice(std::string Name, T Data) : vertice() { name = Name; data = Data; };
      vertice(const vertice<T>& actual) { Id = actual.Id; name = actual.name; data = actual.data; };

      id GetId() const { return Id; };
      std::string GetName() const { return name; }

      bool operator==(const vertice<T>& rhs) const { return ((name == rhs.name) && (data == rhs.data)); };

      friend class graph<T>;
      friend class dgraph<T>;
      friend class ugraph<T>;

   private:
      id Id;
      std::string name;
      T data;
   };

   template<typename T>
   class graph {
   public:
      graph() : size(0) {};
      graph(const graph<T>& actual) { dataMap = actual.dataMap; adjList = actual.adjList; size = actual.size; };

      void AddVertice(vertice<T>&);
      vertice<T>& GetVertice(int);
      int GetSize() const { return size; };
      bool InGraph(const vertice<T>& v) { return adjList.find(v) != adjList.end(); }

      virtual void AddEdge(vertice<T>&, vertice<T>&, int) = 0;

      friend class algorithm<T>;

      // Algorithms

      void dfs(std::vector<bool>&, int);
      void bfs(std::vector<bool>&, int);

      std::deque<vertice<T>> topSort(std::vector<bool>& visited);
      void dfs(int v, std::deque<vertice<T>>&, std::vector<bool>&); // different dfs for topological sort

      std::vector<int> ssspOnDAG();
      std::vector<int> sslpOnDAG();
      std::vector<int> dijkstra(int);

   protected:
      std::unordered_map<int, vertice<T>*> dataMap;
      std::unordered_map<int, std::vector<std::pair<int, int>>> adjList;
      int size;
   };

   template<typename T>
   class dgraph : public graph<T> {
   public:
      typedef graph<T> g;

      dgraph() : g::graph() {};
      dgraph(const dgraph<T>& actual) { g::dataMap = actual.g::dataMap; g::adjList = actual.g::adjList; g::size = actual.g::size; };

      virtual void AddEdge(vertice<T>& from, vertice<T>& to, int weight) {
         if (g::dataMap.find(from.GetId()) == g::dataMap.end()) g::AddVertice(from);
         if (g::dataMap.find(to.GetId()) == g::dataMap.end()) g::AddVertice(to);

         std::pair<int, int> p = { to.GetId(), weight};
         if (g::adjList.find(from.GetId()) == g::adjList.end()) {
            std::vector<std::pair<int, int>> v;
            v.push_back(p);
            g::adjList[from.GetId()] = v;
         }
         else {
            g::adjList[from.GetId()].push_back(p);
         }
      }
   };

   template<typename T>
   class ugraph : public dgraph<T> {
   public:
      typedef graph<T> g;
      typedef dgraph<T> dg;

      ugraph() : dg::dgraph() {};
      ugraph(const ugraph<T>& actual) { g::dataMap = actual.g::dataMap; g::adjList = actual.g::adjList; g::size = actual.g::size; };
      void AddEdge(vertice<T>& from, vertice<T>& to, int weight) {
         dg::AddEdge(from, to, weight);
         dg::AddEdge(to, from, weight);
      }
   };

}

// Overide hash function of a vertice for maps
namespace std {
   using namespace graph;

   template <typename T>
   struct hash<vertice<T>>
   {
      std::size_t operator()(const vertice<T>& t) const {
         return t.GetId();
      };
   };
}

#endif