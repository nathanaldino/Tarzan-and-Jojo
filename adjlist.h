#ifndef ADJLIST_H
#define ADJLIST_H

#include<string>
#include<unordered_map>
#include<list>
#include<vector>

enum traversal {undiscovered, discovered, explored};

class Vertex {
    private:
        Vertex *parent = NULL;

        int id = -1;
        int choice = -1;
        std::string direction = "X";

    public:  
        traversal status = undiscovered;
        
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
};

class AdjList {
    private:
        int numvertices = 0;
        
        //an int will be stored for easy lookup, the list will contain the Vertex
        //subsequent vertices represent the adjacent vertices
        std::unordered_map<int, std::list<Vertex> > adjlist;

    public:
        void discover(Vertex vertex) {
            adjlist[vertex.getid()].front().status = discovered;
        }

        void explore(Vertex vertex) {
            adjlist[vertex.getid()].front().status = explored;
        }

        void createVertex(Vertex vertex) {
            adjlist[vertex.getid()].push_back(vertex);
            numvertices++;
        }

        traversal vertexstatus(Vertex vertex) {
            return adjlist[vertex.getid()].front().status;
        }

        std::list<Vertex> getneighbors(Vertex vertex) {
            std::list<Vertex> neighbors = adjlist.at(vertex.getid());
            //pop the leading vertex which represents the vertex
            neighbors.pop_front();
            return neighbors;
        }

        void addedge(Vertex vertexA, Vertex vertexB, int newchoice) {
            if(vertexB.getid() != -1) {
                vertexB.setchoice(newchoice);
                adjlist[vertexA.getid()].push_back(vertexB);
            }
        }
        
        std::string display() {
            std::string graph;
            for(int i = 0; i<adjlist.size(); i++) {
                for(std::list<Vertex>::iterator vertex = adjlist[i].begin(); vertex != adjlist[i].end(); vertex++) {
                    if(vertex->getdirection().compare("J") == 0) {
                        graph += "V" + std::to_string(vertex->getid()) + "J ";
                        continue;
                    }
                    graph += "V" + std::to_string(vertex->getid()) + " ";
                }
                graph += "\n";
            }
            graph += "\n";
            return graph;
        }
};

#endif