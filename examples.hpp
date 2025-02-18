/*
* THIS IS NOT A HEADER FILE AND IS NOT INCLUDED ANYWHERE ELSE.
* IT ONLY HOLDS CODE AND DOES NOT SERVE ANY FUNCTION.
* THE CODE WILL NEED TO BE COPIED INTO THE MAIN FILE WHENEVER USED.
*/

#ifndef EXAMPLES_HPP
#define EXAMPLES_HPP

#include "graph.hpp"

////////////////////////////////////////////
// Multiple example graphs
////////////////////////////////////////////

/// <summary>
/// Example graph 1, found at "examples/example graph 1.png"
/// </summary>
/// <returns>A directed graph that stores integers</returns>
void generateGraph1() {
   // example graph. Image in project folder
   graph::vertice<int> a("A", 1);
   graph::vertice<int> b("B", 2);
   graph::vertice<int> c("C", 3);
   graph::vertice<int> d("D", 4);
   graph::vertice<int> e("E", 5);
   graph::vertice<int> f("F", 6);
   graph::vertice<int> g("G", 7);
   graph::vertice<int> h("H", 8);
   graph::vertice<int> i("I", 9);
   graph::vertice<int> j("J", 10);
   graph::vertice<int> k("K", 11);
   graph::vertice<int> l("L", 12);
   graph::vertice<int> m("M", 13);

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
   t.AddVertice(k);
   t.AddVertice(l);
   t.AddVertice(m);

   t.AddEdge(a, d, 0);
   t.AddEdge(b, d, 0);
   t.AddEdge(c, a, 0);
   t.AddEdge(c, b, 0);
   t.AddEdge(d, g, 0);
   t.AddEdge(d, h, 0);
   t.AddEdge(e, a, 0);
   t.AddEdge(e, d, 0);
   t.AddEdge(e, f, 0);
   t.AddEdge(f, k, 0);
   t.AddEdge(f, j, 0);
   t.AddEdge(g, i, 0);
   t.AddEdge(h, j, 0);
   t.AddEdge(h, i, 0);
   t.AddEdge(i, l, 0);
   t.AddEdge(j, m, 0);
   t.AddEdge(j, l, 0);
   t.AddEdge(k, j, 0);
}

/// <summary>
/// Example graph 1, found at "example graph 2.png"
/// </summary>
/// <returns>A directed graph that stores integers</returns>
void generateGraph2() {
   graph::vertice<int> a("A", 1);
   graph::vertice<int> b("B", 2);
   graph::vertice<int> c("C", 3);
   graph::vertice<int> d("D", 4);
   graph::vertice<int> e("E", 5);
   graph::vertice<int> f("F", 6);
   graph::vertice<int> g("G", 7);
   graph::vertice<int> h("H", 8);

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
}

void generateGraph3() {
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
}

#endif