#ifndef Vertix_H
#define Vertix_H
#include<vector>
#include<sstream>
using namespace std;
class Vertex
{
       int id, value;
       vector<Vertex> neighbors;
public:
       Vertex()
       {
              id = 0;
              value = 0;
       }
       Vertex(int i, int v)
       {
              id = i;
              value = v;
       }
       int getId()
       {
              return id;
       }
       int getValue()
       {
              return value;
       }
       void setId(int i)
       {
              id = i;
       }
       void setValue(int i)
       {
              value = i;
       }
       string toString()
       {
              stringstream s;
              s << "V(" << id << ", " << value << ")";
              return s.str();
       }
       void addNeighbors(Vertex v)
       {
              neighbors.push_back(v);
       }
       vector<Vertex> getNeighbors()
       {
              return neighbors;
       }
};
#endif