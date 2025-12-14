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
        int v_ind = -1;
        for(int i = 0; i < num_vert; i++) {
            if(s_vertices[i] == v) {
                v_ind = i;
                break;
            }
        }

        if(v_ind == -1) return;
        visit[v_ind] = true;
        cout << v << " ";

        for(int i = 0; i < num_vert; i++) {
            if(matrix[v_ind][i] != 0 && !visit[i]) {
                dfsRecursive(s_vertices[i], visit);
            }
        }
    }
    
    public:
    GraphMatrix() {
        num_vert = 0;
        num_edge = 0;
        memset(matrix, 0, sizeof(matrix));
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
        int dest;
        int ori;
        
        for(int i = 0; i < num_vert; i++) {
            if(s_vertices[i] == u) {
                ori = i;
            }
        }
        
        for(int i = 0; i < num_vert; i++) {
            if(s_vertices[i] == v) {
                dest = i;
            }
        }
        
        int edge = matrix[ori][dest];
        return edge;
    }

    char* endVertices(int e) {
        char* end = new char[2];
        
        for(int i = 0; i < num_vert; i++) {
            for(int j = 0; j < num_vert; j++) {
                if(matrix[i][j] == e) {
                    end[0] = s_vertices[i];
                    end[1] = s_vertices[j];
                    return end;
                }
            }
        }
        
        end[0] = '-';
        end[1] = '-';
        return end;
    }

    char opposite(char v, int e)  {
        char op = '-';
        
        for(int i = 0; i < num_vert; i++) {
            for(int j = 0; j < num_vert; j++) {
                if(matrix[i][j] == e) {
                    if(s_vertices[i] == v) {
                        op = s_vertices[j];
                    } else if(s_vertices[j] == v) {
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
        int* outG = new int[10];
        int v_ind, ctr = 0;
        
        for(int i = 0; i < num_vert; i++) {
            if(s_vertices[i] == v) {
                v_ind = i;
            }
        }
        
        for(int i = 0; i < num_vert; i++) {
            if(matrix[v_ind][i] != 0) {
                outG[ctr++] = matrix[v_ind][i];
            } 
        }
        
        return outG;
    }

    int* incomingEdges(char v) {
        int* inC = new int[10];
        int v_ind, ctr = 0;
        
        for(int i = 0; i < num_vert; i++) {
            if(s_vertices[i] == v) {
                v_ind = i;
            }
        }
        
        for(int i = 0; i < num_vert; i++) {
            if(matrix[i][v_ind] != 0) {
                inC[ctr++] = matrix[i][v_ind];
            } 
        }
        
        return inC;
    }

    bool insertVertex(char x)  {
        s_vertices[num_vert++] = x;
        return true;
    }

    bool insertEdge(char u, char v, int x)  {
        int u_ind;
        int v_ind;
               
        for(int i = 0; i < num_vert; i++) {
            if(s_vertices[i] == u) {
                u_ind = i;
            }
            
            if(s_vertices[i] == v) {
                v_ind = i;
            }
        }
        
        if(matrix[u_ind][v_ind] != 0) {
            cout << "Not null" << endl;
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
        for(int i = 0; i < num_edge; i++) {
            for(int j = 0; j < num_edge; j++) {
                if(matrix[i][j] == e) {
                    matrix[i][j] = 0;
                }
            }
        }
        
        for(int i = 0; i < num_edge; i++) {
            if(s_edges[i] == e) {
                for(int j = i; j < num_edge-1; j++) {
                    s_edges[j] = s_edges[j+1];
                }
                
                num_edge--;
                return true;
            }
        }
        
        return false;
    }

    // ========== TRAVERSALS ========

    void depthFirstSearch(char start) {
        bool visit[10] = {false};
        
        int ind = -1;
        for(int i = 0; i < num_vert; i++) {
            if(s_vertices[i] == start) {
                ind = i;
                break;
            }
        }

        if(ind == -1) {
            cout << "Vertex not found" << endl;
            return;
        }

        cout << "DFS: ";
        dfsRecursive(start, visit);
        cout << endl;
        return;
    }
    
    void breadthFirstSearch(char start) {
        char Q[10];
        int push = 0;
        int pop = 0;

        bool visit[10] = {false};

        int ind = -1;
        for(int i = 0; i < num_vert; i++) {
            if(s_vertices[i] == start) {
                ind = i;
                break;
            }
        }

        if(ind == -1) {
            cout << "Vertex not found" << endl;
            return;
        }

        visit[ind] = true;
        Q[push++] = start;
        cout << "BFS: ";

        while(pop < push) {
            char v = Q[pop++];
            cout << v << " ";

            int v_ind = -1;
            for(int i = 0; i < num_vert; i++) {
                if(s_vertices[i] == v) {
                    v_ind = i;
                    break;
                }
            }

            for(int i = 0; i < num_vert; i++) {
                if(matrix[v_ind][i] != 0 && !visit[i]) {
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