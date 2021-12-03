#ifndef ADJLIST_H
#define ADJLIST_H

#include<string>
#include<unordered_map>
#include<list>
#include<vector>

enum traversal {undiscovered, discovered, explored};

class Vertex {
    private:
        Vertex *parent = nullptr;

        int id = -1;
        int choice = -1;
        std::string direction = "X";

        traversal status = undiscovered;
        
    public:  
        Vertex() {}
        Vertex(int newid) {
            setid(newid);
        }

        int getid() {return id;}
        void setid(int newid) {id = newid;}

        Vertex* getparent() {return parent;}
        void setparent(Vertex newparent) {*parent = newparent;}

        int getchoice() {return choice;}
        void setchoice(int newchoice) {choice = newchoice;}

        std::string getdirection() {return direction;}
        void setdirection(std::string newdirection) {direction = newdirection;}

        traversal getstatus() {return status;}
        void discover() {status = discovered;}
        void explore() {status = explored;}  
};

class AdjList {
    private:
        int numvertices = 0;
        
        //an int will be stored for easy lookup, the list will contain the Vertex
        //subsequent vertices represent the adjacent vertices
        std::unordered_map<int, std::list<Vertex> > adjlist;

    public:
        
        void createVertex(Vertex vertex) {
            adjlist[vertex.getid()].push_back(vertex);
            numvertices++;
        }

        std::list<Vertex> getneighbors(Vertex vertex) {
            std::list<Vertex> neighbors = adjlist.at(vertex.getid());
            //pop the leading vertex which represents the vertex
            neighbors.pop_front();
            return neighbors;
        }

        void addedge(Vertex vertexA, Vertex vertexB, int newchoice) {
            vertexB.setchoice(newchoice);
            adjlist[vertexA.getid()].push_back(vertexB);
        }
        
        std::string display() {
            std::string graph;
            for(int i = 0; i<adjlist.size(); i++) {
                for(std::list<Vertex>::iterator vertex = adjlist[i].begin(); vertex != adjlist[i].end(); vertex++)
                    graph += "V" + std::to_string(vertex->getid()) + " ";
                
                graph += "\n";
            }
            return graph;
        }
};

#endif