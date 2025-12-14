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
        int* edges = new int[num_vert];

        for(int i = 0; i < num_vert; i++) {
            edges[i] = s_edges[i];
        }
        return verts;
    }

    int getEdge(char u, char v)  {
        int u_ind, v_ind;

        for(u_ind = 0; u_ind < num_vert; u_ind++) {
            if(s_vertices[u_ind]->getName() == u) {
                break;
            }
        }

        for(v_ind = 0; v_ind < num_vert; v_ind++) {
            if(s_vertices[v_ind]->getName() == v) {
                break;
            }
        }

        int* outEdge = s_vertices[u_ind]->getOutEdges();
        int outCount = s_vertices[u_ind]->getOutCount();
        int edgeFound = 0;

        for(int i = 0; i < outCount; i++) {
            if(s_vertices[v_ind]->findIn(outEdge[i])) {
                edgeFound = outEdge[i];
                break;
            }
        }

        delete[] outEdge;
        return edgeFound;
    }

    char* endVertices(int e)  {
        char* endV = new char[2];
        endV[0] = endV[1] = '-';

        for(int i = 0; i < num_vert; i++) {
            if(s_vertices[i]->findOut(e)) {
                endV[0] = s_vertices[i]->getName();
                break;
            }
        }

        for(int i = 0; i < num_vert; i++) {
            if(s_vertices[i]->findIn(e)) {
                endV[0] = s_vertices[i]->getName();
                break;
            }
        }

        return endV;
    }

    //opposite algorthm shortcut!
    char opposite(char v, int e)  {
        for(int i = 0; i < num_vert; i++) {
            if(s_vertices[i]->findIn(e) || s_vertices[i]->findOut(e) && s_vertices[i]->getName() != v) {
                return s_vertices[i]->getName();
            }
        }
        return '-';
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
        return true;
    }

    bool insertEdge(char u, char v, int x)  {
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
        } 

        cout << "Not Null" << endl;
        return false;
    }

    int removeVertex(char v) {
        int vInd = -1;

        for(int i = 0; i < num_vert; i++) {
            if(s_vertices[i]->getName() == v) {
                vInd = i;
            }
        }

        if(vInd == -1) return 0;

        int inCount = s_vertices[vInd]->getInCount();
        int outCount = s_vertices[vInd]->getOutCount();

        int* inEdges = s_vertices[vInd]->getInEdges();
        int* outEdges = s_vertices[vInd]->getOutEdges();

        int removed = 0;

        for(int i = 0; i < inCount; i++) {
            int e = inEdges[i];

            char* ends = endVertices(e);
            char u = ends[0];
            char vrtx = ends[1];

            delete[] ends;

            for(int j = 0; j < inCount; j++) {
                if(s_vertices[j]->getName() == u) {
                    s_vertices[j]->removeOutEdge(e);
                }
            }

            removeEdge(e);
            removed++;
        }

        for(int i = 0; i < outCount; i++) {
            int e = outEdges[i];

            char* ends = endVertices(e);
            char u = ends[0];
            char vrtx = ends[1];

            delete[] ends;

            for(int j = 0; j < outCount; j++) {
                if(s_vertices[j]->getName() == u) {
                    s_vertices[j]->removeInEdge(e);
                }
            }

            removeEdge(e);
            removed++;
        }

        delete[] outEdges;
        delete[] inEdges;

        for(int i = vInd; i < num_vert; i++) {
            s_vertices[i] = s_vertices[i+1];
        }

        num_vert--;
        return removed;
    }

    bool removeEdge(int e) {
        bool found = false;

        for(int i = 0; i < num_vert; i++) {
            if(s_vertices[i]->removeInEdge(e)) {
                found = true;
            } 
            if(s_vertices[i]->removeOutEdge(e)) {
                found = true;
            }
        }

        if(!found) return false;

        for(int i = 0; i < num_edge; i++) {
            if(s_edges[i] == e) {
                for(int j = i; j < num_edge; j++) {
                    s_edges[j] = s_edges[j+1];
                }
                num_edge--;
                break;
            }
        }

        return true;
    }

    void print() {
        for (int i = 0; i < num_vert; i++) {
            s_vertices[i]->toString();
            cout << endl;
        }
    }
};