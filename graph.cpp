#include<iostream>
#include<vector>
#include<sstream>
#include<queue>
#include<sstream>
#include "Vertex.h"
#include "Edge.h"
using namespace std;

class Graph  //abstract class "Graph"
{
public:      //pure virtual functions
       Graph() {};
       virtual bool addVertex(Vertex& v) = 0;

       virtual bool removeVertex(Vertex& v) = 0;

       virtual bool addEdge(Edge& e) = 0;

       virtual bool remove(Edge& e) = 0;

       virtual bool searchvertexlead(const Vertex& v) = 0;

       virtual bool searchVertex(const Vertex& v) = 0;

       virtual bool searchEdge(const Edge& e) = 0;

       virtual void display(Vertex& v) const = 0;

       virtual void display(Edge& e) const = 0;

       virtual void display() = 0;

       virtual string toString() const = 0;

       virtual bool clean() = 0;
};

class UGraph : public Graph  //derived class
{
       vector<Vertex> vertices;
       int V, E;
       vector<Edge> edges;
public:
       UGraph() :Graph()
       {
              V = 0;
              E = 0;
              cout << "graph is empty\n";
       }

       bool addVertex(Vertex& ver)
       {
              vertices.push_back(ver);
              V++;
              return true;
       }

       bool addVertices(Vertex* vArray)
       {
              int size = sizeof(vArray);
              for (int i = 0; i < size; i++)
                     if (!addVertex(vArray[i]))
                            return false;
              return true;
       }

       bool removeVertex(Vertex& v)
       {
              vertices.pop_back();
              vector<Vertex> list = v.getNeighbors();
              for (Vertex vt : vertices)
              {
                     Edge e(v, vt, 0);
                     if (!remove(e))
                            return false;
              }
              return true;
       }

       bool addEdge(Edge& e)
       {
              edges.push_back(e);
              E++;
              return true;
       }

       bool addEdges(Edge* eArray)
       {
              int size = sizeof(eArray);
              for (int i = 0; i < size; i++)
                     if (!addEdge(eArray[i]))
                            return false;
              return true;
       }

       bool remove(Edge& e)
       {
              vector<Edge>::iterator it;
              Edge et = e;

              for (it = edges.begin(); it != edges.end(); it++) {

                     if (et.getStart().getId() == (*it).getStart().getId())
                     {
                            if (et.getEnd().getId() == (*it).getEnd().getId())
                            {
                                   edges.erase(it);
                                   return true;
                            }
                     }
              }
              return false;
       }
       bool searchvertexlead(const Vertex& v) {
              vector<Vertex>::iterator it;
              Vertex t = v;
              for (it = vertices.begin(); it != vertices.end(); it++) {

                     if (t.getId() == (*it).getId()) {
                            return true;
                     }
              }
              return false;

       }

       bool searchVertex(const Vertex& v)    //vertec quering
       {
              vector<Vertex>::iterator it;
              Vertex t = v;
              for (it = vertices.begin(); it != vertices.end(); it++) {

                     if (t.getId() == (*it).getId()) {
                            return true;
                     }
              }
              return false;

       }

       bool searchEdge(const Edge& e)        //edge quering
       {
              vector<Edge>::iterator it;
              Edge et = e;
              for (it = edges.begin(); it != edges.end(); it++) {

                     if (et.getStart().getId() == (*it).getStart().getId())
                     {
                            if (et.getEnd().getId() == (*it).getEnd().getId())
                                   return true;
                     }
              }
              return false;
       }

       bool isNotVisited(Vertex x, vector<Vertex> path)const  //checks if vertex was visitid
       {
              int size = path.size();
              for (int i = 0; i < size; i++)
                     if (path[i].getId() == x.getId())
                            return false;
              return true;
       }

       void display(Vertex& v) const       // querig and displaying path from vertex
       {

              Vertex s = vertices[0];
              Vertex d = vertices[V - 1];
              queue<vector<Vertex> > q;

              vector<Vertex> path;
              path.push_back(s);
              q.push(path);
              while (!q.empty()) {
                     path = q.front();
                     q.pop();
                     Vertex last = path[path.size() - 1];

                     if (last.getId() == d.getId())
                     {
                            int size = path.size();
                            int f = 0;
                            for (int i = 0; i < size; i++)
                                   if (path[i].getId() == v.getId())
                                          f = 1;
                            if (f == 1)
                            {
                                   for (int i = 0; i < size; i++)
                                          cout << path[i].getId() << " ";
                                   cout << endl;
                                   return;
                            }
                     }

                     vector<Vertex> adj = s.getNeighbors();
                     vector<Vertex>::iterator it;

                     for (it = adj.begin(); it != adj.end(); it++)
                     {
                            Vertex vert = (*it);

                            if (isNotVisited(vert, path) == true)
                            {
                                   vector<Vertex> newpath(path);
                                   newpath.push_back((*it));
                                   q.push(newpath);
                            }
                     }
              }
       }

       void display(Edge& e) const
       {
       }

       void display()
       {
              if (E == 0 & V == 0) {
                     cout << "graph is zero"; // graph can be zero

              }
              else {
                     vector<Edge>::iterator it;
                     for (it = edges.begin(); it != edges.end(); it++) {
                            cout << " source: " << (*it).getStart().getId();
                            cout << " end: " << (*it).getEnd().getId();
                            cout << " weight: " << (*it).getWeight();
                            cout << endl;
                     }
              }
       }


       string toString() const // detailed display of paths for every input
       {
              stringstream ss;

              Vertex s = vertices[0];
              Vertex d = vertices[V - 1];
              queue<vector<Vertex> > q;

              vector<Vertex> path;
              path.push_back(s);
              q.push(path);
              while (!q.empty()) {
                     path = q.front();
                     q.pop();
                     Vertex last = path[path.size() - 1];

                     if (last.getId() == d.getId())
                     {

                            int size = path.size();
                            int f = 0;
                            for (int i = 0; i < size; i++)
                            {
                                   for (int i = 0; i < size; i++)
                                          ss << path[i].getId() << "-";
                                   ss << "; ";
                            }
                     }

                     vector<Vertex> adj = s.getNeighbors();
                     vector<Vertex>::iterator it;
                     for (it = adj.begin(); it != adj.end(); it++)
                     {
                            Vertex vert = (*it);

                            if (isNotVisited(vert, path) == true)
                            {
                                   vector<Vertex> newpath(path);
                                   newpath.push_back((*it));
                                   q.push(newpath);
                            }
                     }
              }
              return ss.str();
       }

       bool clean() //clears graph data
       {
              vertices.clear();
              edges.clear();
              return true;
       }
};

int main()
{
       bool edgeexist;
       bool vertexexist;
       bool vertexleadexist;
       UGraph graph;

       cout << "\ntest case 1\n\n";

       Vertex v1(1, 20);
       cout << v1.toString() << endl;
       Vertex v11(5, 30);
       cout << v11.toString() << endl;
       Vertex v12(4, 7);
       cout << v11.toString() << endl;
       Edge e1(v11, v11, 30);
       cout << e1.toString() << endl;
       Edge e11(v11, v12, 10);
       cout << e1.toString() << endl;
       Edge e12(v11, v12, 50);
       cout << e12.toString() << endl;

       graph.addVertex(v1);
       graph.addVertex(v11);
       graph.addVertex(v12);

       graph.addEdge(e1);
       graph.addEdge(e11);
       graph.addEdge(e12);
       graph.display();

       graph.clean();

       cout << "\ntest case 2\n\n";


       Vertex v2(2, 10);
       cout << v2.toString() << endl;
       Vertex v21(3, 20);
       cout << v21.toString() << endl;
       Vertex v22(6, 8);
       cout << v21.toString() << endl;
       Edge e2(v2, v21, 60);
       cout << e2.toString() << endl;
       Edge e21(v2, v22, 70);
       cout << e1.toString() << endl;
       Edge e22(v21, v22, 90);
       cout << e2.toString() << endl;

       graph.addVertex(v2);
       graph.addVertex(v21);
       graph.addVertex(v22);

       graph.addEdge(e2);
       graph.addEdge(e21);
       graph.addEdge(e22);
       graph.display();

       graph.clean();

       cout << "\ntest case 3\n\n";



       Vertex v3(5, 45);
       cout << v3.toString() << endl;
       Vertex v31(23, 44);
       cout << v31.toString() << endl;
       Vertex v32(32, 69);
       cout << v31.toString() << endl;
       Edge e3(v3, v31, 54);
       cout << e2.toString() << endl;
       Edge e31(v3, v32, 78);
       cout << e1.toString() << endl;
       Edge e32(v31, v32, 99);
       cout << e3.toString() << endl;

       graph.addVertex(v3);
       graph.addVertex(v31);
       graph.addVertex(v32);

       graph.addEdge(e3);
       graph.addEdge(e31);
       graph.addEdge(e32);
       graph.display();

       graph.clean();




       //checking the existance of elements in graph

       // edgeexist = graph.searchEdge(e1);
       // vertexexist = graph.searchVertex(v1);
       // vertexleadexist = graph.searchvertexlead(v1);

       // if (edgeexist == true) {
       //        cout << "\nedge exists!\n";
       // }
       // else {
       //        cout << "\nedge does not exist!\n";
       // }

       // if (vertexexist == true) {
       //        cout << "\nvertex exists!\n";
       // }
       // else {
       //        cout << "\nvertex does not exist!\n";
       // }


       system("pause");
       return 0;
}