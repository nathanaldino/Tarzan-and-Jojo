#include<adjlist.h>
#include<iostream>
#include<fstream>

using namespace std;

//helper function on checking if neighbor has a direction
bool validdirection(Vertex vertex);
void DFStarzan(Vertex tarzan, AdjList &graph);
string printSolution(Vertex jojo, string &solution);

int main() {
    
    //intialize variables
    vector< vector<Vertex> > maze;
    int rows, cols;
    int tarzanrow, tarzancol;
    Vertex tarzanstart, jojo;
    int numvertices = 1;

    //readfile
    fstream input;
    input.open("input.txt");
    input >> rows >> cols;
    input >> tarzanrow >> tarzancol;
    
    //test
    cout << rows << cols << endl;
    cout << tarzanrow << tarzancol << endl;
    
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
                newvertex = Vertex(numvertices++);
                newvertex.setdirection(temp);
                if(i==tarzanrow && j==tarzancol)
                    tarzanstart = newvertex;
                else if(temp.compare("J") == 0)
                    jojo = newvertex;
                maze[i][j] = newvertex;
            }
        }
    }
    input.close();

    //create graph
    AdjList graph(numvertices);

    //rerun through 2D graph and populate adjlist graph based on direction
    for(int i=0; i<rows; i++) {
        for(int j=0; j<cols; j++) {
            if(maze[i][j].getid() == -1) 
                continue;
            else if(maze[i][j].getdirection().compare("J") == 0) {
                continue;
            }
            else if(maze[i][j].getdirection().compare("N") == 0) {
                if(validdirection(maze[i-3][j]) && (i-3)<=0 )
                    graph.addedge(maze[i][j],maze[i-3][j],3);
                if(validdirection(maze[i-4][j]) && (i-4)<=0 )
                    graph.addedge(maze[i][j],maze[i-4][j],4);
            }
            else if(maze[i][j].getdirection().compare("S") == 0) {
                if(validdirection(maze[i+3][j]) && (i+3)>=rows )
                    graph.addedge(maze[i][j],maze[i+3][j],3);
                if(validdirection(maze[i+4][j]) && (i+3)>=rows )
                    graph.addedge(maze[i][j],maze[i+4][j],4);
            }
            else if(maze[i][j].getdirection().compare("E") == 0) {
                if(validdirection(maze[i][j+3]) && (j+3)>=cols)
                    graph.addedge(maze[i][j],maze[i][j+3],3);
                if(validdirection(maze[i][j+4]) && (j+4)>=cols)
                    graph.addedge(maze[i][j],maze[i][j+4],4);
            }
            else if(maze[i][j].getdirection().compare("W") == 0) {
                if(validdirection(maze[i][j-3]) && (j-3)<=0)
                    graph.addedge(maze[i][j],maze[i][j-3],3);
                if(validdirection(maze[i][j-4]) && (j-4)<=0)
                    graph.addedge(maze[i][j],maze[i][j-4],4);
            }
            else if(maze[i][j].getdirection().compare("NE") == 0) {
                if(validdirection(maze[i-3][j+3]) && (i-3)<=0 && (j+3)>=cols )
                    graph.addedge(maze[i][j],maze[i-3][j+3],3);
                if(validdirection(maze[i-4][j+4]) && (i-4)<=0 && (j+4)>=cols )
                    graph.addedge(maze[i][j],maze[i-4][j+4],4);
            }
            else if(maze[i][j].getdirection().compare("NW") == 0) {
                if(validdirection(maze[i-3][j-3]) && (i-3)<=0 && (j-3)<=0 )
                    graph.addedge(maze[i][j],maze[i-3][j+3],3);
                if(validdirection(maze[i-4][j+4]) && (i-4)<=0 && (j-4)<=0 )
                    graph.addedge(maze[i][j],maze[i-4][j+4],4);
            }
            else if(maze[i][j].getdirection().compare("SE") == 0) {
                if(validdirection(maze[i+3][j+3]) && (i+3)>=rows && (j+3)>=cols )
                    graph.addedge(maze[i][j],maze[i-3][j+3],3);
                if(validdirection(maze[i+4][j+4]) && (i+4)>=rows && (j+4)>=cols )
                    graph.addedge(maze[i][j],maze[i-4][j+4],4);
            }
            else if(maze[i][j].getdirection().compare("SW") == 0) {
                if(validdirection(maze[i+3][j-3]) && (i+3)>=rows && (j-3)<=0 )
                    graph.addedge(maze[i][j],maze[i-3][j+3],3);
                if(validdirection(maze[i+4][j+4]) && (i+4)>=rows && (j-4)<=0 )
                    graph.addedge(maze[i][j],maze[i-4][j+4],4);
            }

            
        }
    }

    //run algorithm
    DFStarzan(tarzanstart,graph);

    //print correct path to output
    string solution;
    printSolution(jojo, solution);
    
    fstream output;
    output.open("output.txt",ios_base::out);
    if(solution.empty()) {
        output << "There is no way to reach Jojo!!!" << endl;
    }
    else {
        output << solution << endl;
    }
    output.close();

}

bool validdirection(Vertex vertex) {
    if(vertex.getdirection().compare("X") == 0)
        return false;
    else
        return true;
}

void DFStarzan(Vertex tarzan, AdjList &graph) {
    tarzan.discover();
    list<Vertex> neighbors = graph.getneighbors(tarzan);
    for(list<Vertex>::iterator neighbor = neighbors.begin(); neighbor != neighbors.end(); neighbor++) {
        if(neighbor->getstatus() == undiscovered) {
            neighbor->setparent(tarzan);
            DFStarzan(*neighbor,graph);
        }
    }
    tarzan.explore();
}

string printSolution(Vertex jojo, string &solution) {
    if(jojo.getparent() != nullptr) {
            printSolution(*jojo.getparent(),solution);
            solution += jojo.getparent()->getdirection() + "-" + to_string(jojo.getchoice());
    }
    else {
        return solution;
    }

}