#ifndef ADJLIST_H
#define ADJLIST_H

#include<string.h>
#include<unordered_map>
#include<list>
#include<vector>

enum traversal {undiscovered, dicovered, explored};

class Vertex {
    private:
        Vertex* parent = nullptr;

        int id = -1;
        int choice = -1;
        std::string direction;

        traversal status = undiscovered;
        
    public:
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
};

class AdjList {
    private:
        int numvertices;
        std::vector<Vertex> vertices;
        std::unordered_map<int, std::list<Vertex>> adjlist;

    public:
        void addvertex(int id) {
            Vertex newvertex(id);
            vertices.push_back(newvertex);
        }
        void addedge(Vertex vertexA, Vertex vertexB) {
            adjlist[vertexA.getid()].push_back(vertexB);
            vertex
        }
        

        
};

#endif