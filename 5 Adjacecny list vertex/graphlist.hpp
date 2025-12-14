#include <cstdlib>
#include <iostream>
#include "graph.hpp"
#include "vertex.hpp"
using namespace std;

class GraphList : public Graph {
    Vertex** s_vertices;
    int num_vert;
    int s_edges[100];
    int num_edge;

public:
    GraphList() {
        s_vertices = (Vertex**) malloc( 10 * sizeof(Vertex*) );
        num_vert = 0;
        num_edge = 0;
    }

    int numVertices() {
        return num_vert;
    }

    char* vertices() {
        char* verts = new char[num_vert];

        for(int i = 0; i < num_vert; i++) {
            verts[i] = s_vertices[i]->getName();
        }

        return verts;
    }

    int numEdges() {
        return num_edge;
    }

    int* edges() {
        int* edges = new int[num_edge];

        for(int i = 0; i < num_edge; i++) {
            edges = s_edges[i];
        }

        return edges;
    }

    int getEdge(char u, char v)  {
        int uInd, vInd;

        for(uInd = 0; uInd < num_vert; uInd++) {
            if(s_vertices[uInd]->getName() == u) {
                break;
            }
        }

        for(vInd = 0; vInd < num_vert; vInd++) {
            if(s_vertices[vInd]->getName() == v) {
                break;
            }
        }

        int* outEdges = s_vertices[uInd]->getOutEdges();
        int outCount = s_vertices[uInd]->getOutCount();
        int found = 0;

        for(int i = 0; i < outCount; i++) {
            if(s_vertices[vInd]->findIn(outEdges[i])) {
                found = outEdges[i];
                break;
            }
        }

        delete[] outEdges;
        return found;
    }

    char* endVertices(int e)  {
        char* endV = new char[2];
        endV[0] = endV[1] = '-';

        for(int i = 0; i < num_vert; i++) {
            if(s_vertices[i]->findOut(e)) {
                endV[0] = s_vertices[i]->getName();
            }
        }

        for(int i = 0; i < num_vert; i++) {
            if(s_vertices[i]->findIn(e)) {
                endV[1] = s_vertices[i]->getName();
            }
        }

        return endV;
    }

    //opposite algorthm shortcut!
    char opposite(char v, int e)  {
        for(int i = 0; i < num_vert; i++) {
            if(s_vertices[i]->findIn(e) || s_vertices[i]->findOut(e)  && s_vertices[i]->getName() != v) {
                return s_vertices[i]->getName();
            }
        }
    }


    int outDegree(char v)  {
        for(int i = 0; i < num_vert; i++) {
            if(s_vertices[i]->getName() == v) {
                return s_vertices[i]->getOutCount();
            } 
        }
        return 0;
    }

    int inDegree(char v)  {
        for(int i = 0; i < num_vert; i++) {
            if(s_vertices[i]->getName() == v) {
                return s_vertices[i]->getInCount();
            } 
        }
        return 0;
    }

    int* outgoingEdges(char v) {
        for(int i = 0; i < num_vert; i++) {
            if(s_vertices[i]->getName() == v) {
                return s_vertices[i]->getOutEdges();
            } 
        }
        return nullptr;
    }


    int* incomingEdges(char v) {
        for(int i = 0; i < num_vert; i++) {
            if(s_vertices[i]->getName() == v) {
                return s_vertices[i]->getInEdges();
            } 
        }
        return nullptr;
    }

    bool insertVertex(char x)  {
        if(num_vert >= 10) return false;

        s_vertices[num_vert++] = new Vertex(x);
        true;
    }

    bool insertEdge(char u, char v, int x) {
        int uInd, vInd;

        for(uInd = 0; uInd < num_vert; uInd++) {
            if(s_vertices[uInd]->getName() == u) {
                break;
            }
        }

        for(vInd = 0; vInd < num_vert; vInd++) {
            if(s_vertices[vInd]->getName() == u) {
                break;
            }
        }

        if(getEdge(u, v) == 0) {
            s_vertices[uInd]->addOutEdge(x);
            s_vertices[vInd]->addInEdge(x);
            s_edges[num_edge++] = x;
            return true;
        } else {
            return false;
        }
    }

    int removeVertex(char v) {
        int v_ind = -1;
        int removed = 0;

        for(int i = 0; i < num_vert; i++) {
            if(s_vertices[i]->getName() == u) {
                v_ind = i;
                break;
            }
        }

        if(v_ind == -1) return 0;

        int* outEdge = s_vertices[v_ind]->getOutEdges();
        int* inEdge = s_vertices[v_ind]->getInEdges();

        int inCount = s_vertices[vInd]->getInCount();
        int outCount = s_vertices[vInd]->getOutCount();

        for(int i = 0; i < inCount; i++) {
            int e = inEdge[i];

            char* ends = endVertices(e);
            char u = ends[0];
            char vrtx = ends[1];
            delete[] ends;

            for(int j = 0; j < num_vert; j++) {
                if(s_vertices[j]->getName() == u) {
                    s_vertices[j]->removeOutEdgea(e);
                }
            }
            removeEdge(e);
            removed++;
        }

        for(int i = 0; i < outCount; i++) {
            int e = outEdge[i];

            char* ends = endVertices(e);
            char u = ends[0];
            char vrtx = ends[1];
            delete[] ends;

            for(int j = 0; j < num_vert; j++) {
                if(s_vertices[j]->getName() == vrtx) {
                    s_vertices[j]->removeOutEdgea(e);
                }
            }
            removeEdge(e);
            removed++;
        }

        delete[] outEdge;
        delete[] inEdge;

        for(int i = v_ind; i < num_vert-1; i++) {
            s_vertices[i] = s_vertices[i+1];
        }

        num_vert--;
        return removed;
    }

    bool removeEdge(int e) {
        
    }

    void print() {
        for (int i = 0; i < num_vert; i++) {
            s_vertices[i]->toString();
            cout << endl;
        }
    }
};