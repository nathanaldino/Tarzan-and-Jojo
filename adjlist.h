#ifndef ADJLIST_H
#define ADJLIST_H

#include<string>
#include<unordered_map>
#include<list>
#include<vector>

enum traversal {undiscovered, discovered, explored};

class Vertex {
    private:
        Vertex* parent = nullptr;

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

        Vertex getparent() {return *parent;}
        void setparent(Vertex newparent) {*parent = newparent;}

        int getchoice() {return choice;}
        void setchoice(int newchoice) {choice = newchoice;}

        std::string getdirection() {return direction;}
        void setdirection(std::string newdirection) {direction = newdirection;}

        void discover() {status = discovered;}
        void explore() {status = explored;}  
};

class AdjList {
    private:
        int numvertices;
        std::unordered_map<int, std::list<Vertex> > adjlist;

    public:
        AdjList(int vertices) {
            numvertices = vertices;
        }
        
        std::list<Vertex> getneighbors(Vertex vertex) {
            return adjlist.at(vertex.getid());
        }

        void addedge(Vertex vertexA, Vertex vertexB) {
            adjlist[vertexA.getid()].push_back(vertexB);
        }
        

        
};

#endif