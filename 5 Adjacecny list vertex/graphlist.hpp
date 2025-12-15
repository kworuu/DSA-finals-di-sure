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
            edges[i] = s_edges[i];
        }

        return edges;
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

        if(u_ind >= num_vert || v_ind >= num_vert) return 0;

        int* outEdges = s_vertices[u_ind]->getOutEdges();
        int outCount = s_vertices[u_ind]->getOutCount();
        int found = 0;

        for(int i = 0; i < outCount; i++) {
            if(s_vertices[v_ind]->findIn(outEdges[i])) {
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
            if(s_vertices[i]->findIn(e)) {
                endV[1] = s_vertices[i]->getName();
            }
        }

        for(int i = 0; i < num_vert; i++) {
            if(s_vertices[i]->findOut(e)) {
                endV[0] = s_vertices[i]->getName();
            }
        }

        return endV;
    }

    //opposite algorthm shortcut!
    char opposite(char v, int e)  {
        for(int i = 0; i < num_vert; i++) {
            if((s_vertices[i]->findIn(e) || s_vertices[i]->findOut(e)) && s_vertices[i]->getName() != v) {
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

    bool insertEdge(char u, char v, int x) {
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
    for(int i = 0; i < num_vert; i++) {
        if(s_vertices[i]->getName() == v) {
            v_ind = i;
            break;
        }
    }
    
    if(v_ind == -1) return 0;
    
    int removed = 0;
    
    // Get edge counts before deletion
    int outCount = s_vertices[v_ind]->getOutCount();
    int inCount = s_vertices[v_ind]->getInCount();
    removed = outCount + inCount;
    
    // Remove all edges connected to this vertex
    for(int i = 0; i < num_edge; ) {
        char* ends = endVertices(s_edges[i]);
        if(ends[0] == v || ends[1] == v) {
            removeEdge(s_edges[i]);  // This handles everything
            delete[] ends;
        } else {
            delete[] ends;
            i++;
        }
    }
    
    // Delete vertex
    delete s_vertices[v_ind];
    
    // Shift array
    for(int i = v_ind; i < num_vert-1; i++) {
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
        }

        for(int i = 0; i < num_vert; i++) {
            if(s_vertices[i]->removeOutEdge(e)) {
                found = true;
            }
        }

        if(!found) return false;

        for(int i = 0; i < num_edge; i++) {
            if(s_edges[i] == e) {
                for(int j = i; j < num_edge-1; j++) {
                    s_edges[j] = s_edges[j+1];
                }
                num_edge--;
                return true;

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