#ifndef Edge_H
#define Edge_H
#include<vector>
#include"vertex.h"
#include<sstream>
using namespace std;
class Edge
{
       Vertex start, end;
       int weight;
public:
       Edge()
       {
              weight = 0;
       }
       Edge(Vertex&s, Vertex &e, int w)
       {
              start = s;
              end = e;
              weight = w;
       }
       int getWeight()
       {
              return weight;
       }
       Vertex getStart()
       {
              return start;
       }
       Vertex getEnd()
       {
              return end;
       }
       void setWeight(int w)
       {
              weight = w;
       }
       void setStart(Vertex v)
       {
              start = v;
       }
       void setEnd(Vertex v)
       {
              end = v;
       }
       string toString()
       {
              stringstream s;
              s << start.toString() << "--" << weight << "-->" << end.toString();
              s << endl;
              return s.str();
       }
};
#endif