#include <cstdlib>
#include <iostream>
#include <cstring>
#include "graph.hpp"
using namespace std;

class GraphMatrix : public Graph {
    
    int matrix[10][10];
    char s_vertices[10];
    int num_vert;
    int s_edges[100];
    int num_edge;

    void dfsRecursive(char v, bool visit[]) {
        int vInd;
        for(int i = 0; i < num_vert; i++) {
            if(s_vertices[i] == v) {
                vInd = i;
            }
        }

        visit[vInd] = true;
        cout << v << " ";

        for(int i  = 0; i < num_vert; i++) {
            if(matrix[vInd][i] != 0 && !visit[i]) {
                dfsRecursive(s_vertices[i], visit);
            }
        }
        return;
    }
    
    public:
    GraphMatrix() {
        num_edge = 0;
        num_vert = 0;
        memset(matrix, 0, sizeof(int));
    }
    
    int numVertices() {
        return num_vert;
    }

    char* vertices() {
        return s_vertices;
    }

    int numEdges() {
        return num_edge;
    }

    int* edges() {
        return s_edges;
    }

    int getEdge(char u, char v)  {
        int u_ind;
        int v_ind;

        for(int i  = 0; i < num_vert; i++) {
            if(s_vertices[i] == u) {
                u_ind = i;
            } 

            if(s_vertices[i] == v) {
                v_ind = i;
            }
        }

        int edge = matrix[u_ind][v_ind];
        return edge;
    }

    char* endVertices(int e) {
        char* verts = new char[2];
        for(int i = 0; i < num_vert; i++) {
            for(int j = 0; j < num_vert; j++) {
                if(matrix[i][j] == e) {
                    verts[0] = s_vertices[i];
                    verts[1] = s_vertices[j];
                    return verts;
                }
            }
        }

        verts[0] = '-';
        verts[1] = '-';
        return verts;
    }

    char opposite(char v, int e)  {
        char op = '-';
        
        for(int i = 0; i < num_vert; i++) {
            for(int j = 0; j < num_vert; j++) {
                if(matrix[i][j] == e) {
                    if(s_vertices[i] == v) {
                        op = s_vertices[j];
                    } else {
                        op = s_vertices[i];
                    }
                }
            }
        }

        return op;
    }

    int outDegree(char v)  {
        int out = 0;
        int v_ind;

        for(int i = 0; i < num_vert; i++) {
            if(s_vertices[i] == v) {
                v_ind = i;
            }
        }

        for(int i = 0; i < num_vert; i++) {
            if(matrix[v_ind][i] != 0) {
                out++;
            }
        }

        return out;
    }

    int inDegree(char v)  {
        int in = 0;
        int v_ind;

        for(int i = 0; i < num_vert; i++) {
            if(s_vertices[i] == v) {
                v_ind = i;
            }
        }

        for(int i = 0; i < num_vert; i++) {
            if(matrix[i][v_ind] != 0) {
                in++;
            }
        }

        return in;
    }

    int* outgoingEdges(char v) {
        int* out = new int[10];
        int v_ind;

        for(int i = 0; i < num_vert; i++) {
            if(s_vertices[i] == v) {
                v_ind = i;
            }
        }

        int ctr = 0;
        for(int i = 0; i < num_vert; i++) {
            if(matrix[v_ind][i] != 0) {
                out[ctr++] = matrix[v_ind][i];
            }
        }

        return out;
    }

    int* incomingEdges(char v) {
        int* in = new int[10];
        int v_ind;

        for(int i = 0; i < num_vert; i++) {
            if(s_vertices[i] == v) {
                v_ind = i;
            }
        }

        int ctr = 0;
        for(int i = 0; i < num_vert; i++) {
            if(matrix[i][v_ind] != 0) {
                in[ctr++] = matrix[i][v_ind];
            }
        }

        return in;
    }

    bool insertVertex(char x)  {
        if(num_vert >= 10) return false;

        s_vertices[num_vert++] = x;
        return true;
    }

    bool insertEdge(char u, char v, int x)  {
        int v_ind;
        int u_ind;

        for(int i = 0; i < num_vert; i++) {
            if(s_vertices[i] == u) {
                u_ind = u;
            }

            if(s_vertices[i] == v) {
                v_ind = v;
            }
        }

        if(matrix[u_ind][v_ind] != 0) {
            return false;
        }

        matrix[u_ind][v_ind] = x;
        s_edges[num_edge++] = x;
        return true;
    }

    int removeVertex(char v) {
        int ctr = 0;
        int v_ind;
        
        for(int i = 0; i < num_vert; i++) {
            if(s_vertices[i] == v) {
                v_ind = i;
            }
        }
        
        for(int i = 0; i < num_vert; i++) {
            if(matrix[v_ind][i] > 0) {
                removeEdge(matrix[v_ind][i]);
                ctr++;
            }
            if(matrix[i][v_ind] > 0) {
                removeEdge(matrix[i][v_ind]);
                ctr++;
            }
        }
        
        for(int j = 0; j < num_vert; j++) {
            for(int i = v_ind; i < num_vert; i++) {
                matrix[j][i] = matrix[j][i+1];
            }
            matrix[j][num_vert-1] = 0;
        }
        
        for(int j = 0; j < num_vert; j++) {
            for(int i = v_ind; i < num_vert; i++) {
                matrix[i][j] = matrix[i+1][j];
            }
            matrix[num_vert-1][j] = 0;
        }
        
        for(int i = v_ind; i < num_vert-1; i++) {
            s_vertices[i] = s_vertices[i+1];
        }
        
        return ctr;
    }

    bool removeEdge(int e)  {
        for(int i = 0; i < mum_vert; i++) {
            for(int j = 0; j < 0; j++) {
                if(matrix[i][j] == e) {
                    matrix[i][j] = 0;
                }
            }
        }

        for(int i = 0; i < num_edge; i++) {
            if(s_edges[i] == e) {
                for(int j = 0; j < num_edge-1; j++) {
                    s_edges[j] = s_edges[j+1];
                }
            }
        }
    }

    // ========== TRAVERSALS ========

    void depthFirstSearch(char start) {
        int ind = -1;
        bool visit[num_vert] = {false};

        for(int i = 0; i < num_vert; i++) {
            if(s_vertices[i] == start) {
                ind = i;
            }
        }

        if(ind == -1) return;

        cout << "DFS: ";
        dfsRecursive(start, visit);
        cout << endl;
    }
    
    void breadthFirstSearch(char start) {
        char curr = Q[num_vert];
        bool visit[num_vert] = {false};
        int push = 0, pop = 0;

        int ind = -1;
        for(int i = 0; i < num_vert; i++) {
            if(s_vertices[i] == curr) {
                ind = i;
            }
        }

        if(ind == -1) return;

        visit[ind] = true; 
        Q[push++] = start;
        cout << "BFS: ";

        while(pop < push) {
            char curr = Q[pop++];
            cout << curr << " ";

            int vInd = -1;
            for(int i = 0; i < num_vert; i++) {
                if(s_vertices[i] == start) {
                    vInd = i;
                }
            }

            for(int i = 0; i < num_vert; i++) {
                if(matrix[vInd][i] != 0 && !visit[i]) {
                    Q[push++] = s_vertices[i];
                    visit[i] = true;
                }
            }
        }
        cout << endl;
    }

    void print() {
        cout << "\t";
        for (int i = 0; i < num_vert; i++) {
            cout << s_vertices[i] << "\t";
        }
        cout << endl;
        for (int i = 0; i < num_vert; i++) {
            cout << s_vertices[i] << "\t";
            for (int j = 0; j < num_vert; j++) {
                if (matrix[i][j] != 0) {
                    cout << matrix[i][j];
                }
                cout << "\t";
            }
            cout << endl;
        }
    }
};