#include"adjlist.h"
#include<iostream>
#include<fstream>

using namespace std;

//traversal algo using DFS
void DFStarzan(Vertex tarzan, AdjList &graph);
//prints the solution from jojo if found, otherwise returns an empty string
string printSolution(Vertex jojo, string &solution, AdjList &graph);

int main() {
    
    //intialize variables
    vector< vector<Vertex> > maze;  //DS to store input maze
    vector<Vertex> mazeinside;      //Will be used to store sentinel value
    int rows, cols;                 //save row/col size
    int tarzanrow, tarzancol;       //save tarzan's coordinates
    Vertex tarzanstart, jojo;       //save the vertex of tarzan and jojo for easy lookup
    int numvertices = 0;            //number of vertices in graph
    AdjList graph;                  //create graph

    //readfile
    fstream input;
    input.open("input.txt");
    input >> rows >> cols;
    input >> tarzanrow >> tarzancol;
    
    //fill 2D vector with default values
    Vertex defaultvertex;
    for(int i = 0; i<cols; i++) {
        mazeinside.push_back(defaultvertex);
    }
    for(int i = 0; i<rows; i++) {
        maze.push_back(mazeinside);
    }

    //fill 2D array with Vertex's
    for(int i=0; i<rows; i++) {
        for(int j=0; j<cols; j++) {
            string temp;
            input >> temp;
            Vertex newvertex;
            if (temp.compare("X") == 0) {
                maze[i][j] = newvertex;
            }
            else {
                //create vertex and set the direction of entry
                newvertex = Vertex(numvertices++);
                newvertex.setdirection(temp);
                //intialize adjlist graph's Vertices by creating upon finding a valid entry
                graph.createVertex(newvertex);

                //save to tarzan or jojo if found
                if(i==tarzanrow-1 && j==tarzancol-1)
                    tarzanstart = newvertex;
                else if(temp.compare("J") == 0)
                    jojo = newvertex;
                maze[i][j] = newvertex;
            }
        }
    }
    input.close();

    //rerun through 2D graph and populate adjlist graph Edges based on direction
    
    for(int i=0; i<rows; i++) {
        for(int j=0; j<cols; j++) {
            //if X
            if(maze[i][j].getid() == -1) 
                continue;
            //if jojo, dont add edges since he is finishing point
            else if(maze[i][j].getdirection().compare("J") == 0) {
                continue;
            }
            //if north, add edges. same case as ones below
            else if(maze[i][j].getdirection().compare("N") == 0) {
                if( (i-3)>=0 )
                    graph.addedge(maze[i][j],maze[i-3][j],3);
                if( (i-4)>=0 )
                    graph.addedge(maze[i][j],maze[i-4][j],4);
            }
            //if south
            else if(maze[i][j].getdirection().compare("S") == 0) {
                if( (i+3)<rows )
                    graph.addedge(maze[i][j],maze[i+3][j],3);
                if( (i+4)<rows )
                    graph.addedge(maze[i][j],maze[i+4][j],4);
            }
            //if east
            else if(maze[i][j].getdirection().compare("E") == 0) {
                if( (j+3)<cols)
                    graph.addedge(maze[i][j],maze[i][j+3],3);
                if( (j+4)<cols)
                    graph.addedge(maze[i][j],maze[i][j+4],4);
            }
            //if west
            else if(maze[i][j].getdirection().compare("W") == 0) {
                if( (j-3)>=0)
                    graph.addedge(maze[i][j],maze[i][j-3],3);
                if( (j-4)>=0)
                    graph.addedge(maze[i][j],maze[i][j-4],4);
            }
            //if northeast
            else if(maze[i][j].getdirection().compare("NE") == 0) {
                if( (i-3)>=0 && (j+3)<cols )
                    graph.addedge(maze[i][j],maze[i-3][j+3],3);
                if( (i-4)>=0 && (j+4)<cols )
                    graph.addedge(maze[i][j],maze[i-4][j+4],4);
            }
            //if northwest
            else if(maze[i][j].getdirection().compare("NW") == 0) {
                if( (i-3)>=0 && (j-3)>=0 )
                    graph.addedge(maze[i][j],maze[i-3][j+3],3);
                if( (i-4)>=0 && (j-4)>=0 )
                    graph.addedge(maze[i][j],maze[i-4][j+4],4);
            }
            //if southeast
            else if(maze[i][j].getdirection().compare("SE") == 0) {
                if( (i+3)<rows && (j+3)<cols )
                    graph.addedge(maze[i][j],maze[i-3][j+3],3);
                if( (i+4)<rows && (j+4)<cols )
                    graph.addedge(maze[i][j],maze[i-4][j+4],4);
            }
            //if southwest
            else if(maze[i][j].getdirection().compare("SW") == 0) {
                if( (i+3)<rows && (j-3)>=0 )
                    graph.addedge(maze[i][j],maze[i-3][j+3],3);
                if( (i+4)<rows && (j-4)>=0 )
                    graph.addedge(maze[i][j],maze[i-4][j+4],4);
            }
        }
    }
    
    //TESTING PURPOSES
    string displaystring;
    if(true) {
        displaystring = graph.display();
        cout << displaystring;
    }
    
    //run algorithm
    cout << "start tarzan: " << tarzanstart.getid() << endl;
    DFStarzan(tarzanstart,graph);
    cout << endl << graph.getparentid(7) <<graph.getvertexhead(7).getid() << graph.getvertexhead(7).status <<endl;
    cout << "dfs done" << endl;

    //print correct path to output
    string solution;
    printSolution(jojo, solution, graph);
    
    fstream output;
    output.open("output.txt",ios_base::out);
    if(solution.empty()) {
        output << "There is no way to reach Jojo!!!" << endl;
    }
    else {
        output << solution << endl;
    }
    output.close();

    return 1;
}

void DFStarzan(Vertex tarzan, AdjList &graph) {
    graph.discover(tarzan);
    
    if(graph.hasneighbors(tarzan)) {
        list<Vertex> neighbors = graph.getneighbors(tarzan);
        for(list<Vertex>::iterator neighbor = neighbors.begin(); neighbor != neighbors.end(); neighbor++) {
            if(graph.vertexstatus(*neighbor) == undiscovered) {
                //cout << graph.getvertexhead(neighbor->getid()).getid() << "-" << graph.getvertexhead(neighbor->getid()).status <<endl;
                graph.getvertexhead(neighbor->getid()).setparent(tarzan.getid());
                cout << neighbor->getid() << " parent is " << graph.getvertexhead(neighbor->getid()).getparent() << endl;
                DFStarzan(*neighbor,graph);
            }
        }
    }
    //cout << graph.getvertexhead(tarzan.getid()).getid() << "-" <<graph.getvertexhead(tarzan.getid()).status <<endl;
    graph.explore(tarzan);

}

string printSolution(Vertex jojo, string &solution, AdjList &graph) {
    if(graph.getparentid(jojo.getid()) != -1) {
        printSolution(graph.getvertexhead(graph.getparentid(jojo.getid())),solution,graph);
        graph.updatechoice(graph.getvertexhead(jojo.getid()));
        solution += graph.getvertexhead(graph.getparentid(jojo.getid())).getdirection() + "-" + to_string(graph.getvertexhead(jojo.getid()).getchoice()) + " ";
    }
    else {
        return solution;
    }
    
    //for unexpected errors
    return solution;
}
