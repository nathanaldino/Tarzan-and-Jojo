#ifndef ADJLIST_H
#define ADJLIST_H

#include<string>
#include<unordered_map>
#include<list>
#include<vector>

//enum to represent traversal status
enum traversal {undiscovered, discovered, explored};

class Vertex {
    //variables, traversal status is public for ease of us
    private:
        int parentid = -1;
        int id = -1;
        int choice = -1;
        std::string direction = "X";
    public:  
        traversal status = undiscovered;
        
        //constructors
        Vertex() {}
        Vertex(int newid) {
            setid(newid);
        }

        //getters and setters for variables
        int getid() {return id;}
        void setid(int newid) {id = newid;}

        int getparent() {return parentid;}
        void setparent(int newid) {parentid = newid;}

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
        //set enum to discovered
        void discover(Vertex vertex) {
            adjlist[vertex.getid()].front().status = discovered;
        }

        //set enum to explored
        void explore(Vertex vertex) {
            adjlist[vertex.getid()].front().status = explored;
        }

        //create vertex and initialize list with vertex head
        void createVertex(Vertex vertex) {
            adjlist[vertex.getid()].push_back(vertex);
            numvertices++;
        }
        
        //update choice for the vertex based on their parent
        void updatechoice(Vertex &vertex) {
            //choice value
            int newchoice = 3;

            //get parent neighbors
            std::list<Vertex> parentneighbors = adjlist[getparentid(vertex.getid())];
            for(std::list<Vertex>::iterator neighbor = ++parentneighbors.begin(); neighbor != parentneighbors.end(); neighbor++) {
                if(vertex.getid() == neighbor->getid()) {
                    break;
                }
                newchoice++;
            }
            //set choice depending on if it equals the first or second edge (3 or 4)
            vertex.setchoice(newchoice);
        }

        //get parentid
        int getparentid(int id) {
            return getvertexhead(id).getparent();
        }

        //get vertex head but as reference so it will edit the passed vertex
        Vertex &getvertexhead(int id) {
            return adjlist[id].front();
        }
        
        //get vertex status
        traversal vertexstatus(Vertex vertex) {
            return adjlist[vertex.getid()].front().status;
        }

        //return true if vertex has neighbors
        bool hasneighbors(Vertex vertex) {
            if (adjlist[vertex.getid()].size() > 1)
                return true;
            else
                return false;
        }

        //get neighbors
        std::list<Vertex> getneighbors(Vertex vertex) {
            std::list<Vertex> neighbors = adjlist.at(vertex.getid());
            //pop the leading vertex which represents the vertex
            neighbors.pop_front();
            return neighbors;
        }
        
        //add edge 
        void addedge(Vertex vertexA, Vertex vertexB) {
            if(vertexB.getid() != -1) {
                adjlist[vertexA.getid()].push_back(vertexB);
            }
        }
        
        //display adjacency list - used for testing
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