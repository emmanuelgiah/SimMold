#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <memory>

using namespace std;
string filename = "";

void getMatrixDimensions(int &numRows, int &arraySize) {
    //create file
    ifstream infile;
    infile.open(filename, ios::in|ios::out|ios::binary);
    //iterate through file
    char letter;
    if (infile) {
        while (infile.get(letter)) {
            arraySize++;
            //check if end of line
            if (letter == "\n") {
                numRows++;
            }
        }
    }
    //adjust for end of line
    arraySize--;
    numRows++;
}

void createWorld(char *arr, int arraySize) {
    //create file
    char current;
    ifstream infile;
    infile.open(filename, ios::in|ios::out|ios::binary);
    //iterate through file
    if (infile) {
        for (int i = 0; i <= arraySize; i++) {
            //write file elements to memory
            current = (char)infile.get();
            (*(arr+i)) = current;
        }
    } else {
        cout << "ERROR | FILE CAN NOT BE OPENED " << endl;
    }
}

void printWorld(string world[], int numRows, int numColumns) {
    //iterate through world array
    for (int i = 0; i <= (numRows * numColumns) + 3; i++) {
        //print new line once necessary
        if (((i % (numColumns + 1)) == 0) && (i != 0)) {
            cout << endl << *(world+i);
        } else {
            cout << *(world+i);
        }
    }
}
int getGenerations() {
    int generations = 0;
    do {
        cout << "ENTER NUMBER OF GENERATIONS (1-10) >>> " << endl;
        cin >> generations;
        cin.clear();
        cin.ignore();
    } while ((generations < 1) || (generations > 10));
    return generations;
}


int main() {
    //instance variables
    int arraySize = 0;
    int generations = 0;
    int numRows = 0;
    int numColumns = 0;
    //prompt for file name
    do {
        cout << "ENTER NUMBER OF GENERATIONS >>> " << endl;
        cin >> filename;
    } while (!getMatrixDimensions(numOfRows, arraySize));
    //create dynamic array;
    unique_ptr<char> world(new char[arraySize]);
    cout << endl;
    //fill the world with organisms
    createWorld(world.get(), arraySize);
    //ask the users for the number of generations they want to run
    generations = getGenerations();
    //update variables
    numColumns = arraySize / numRows;
    int neighbors = 0;
    char n1, n2, n3, n4, n5, n6, n7, n8;
    unique_ptr<char> nextGeneration(new char[arraySize]);
    //run simulation
    for (int i = 0; i < generations; i++) {
        for (int j=0; j <= sizeOfArr; j++) {
            char current = (*(world.get() + j));
            if (current == '\n') {
                (*(nextGeneration.get() + j)) = '\n';
                continue;
            }
            //create neighbors
            n1 = (*(world.get()+j-numColumns-1));
            n2 = (*(world.get()+j-numColumns));
            n3 = (*(world.get()+j-numColumns+1));
            n4 = (*(world.get()+j-1));
            n5 = (*(world.get()+j+1));
            n6 = (*(world.get()+j+numColumns-1));
            n7 = (*(world.get()+j+numColumns));
            n8 = (*(world.get()+j+numColumns+1));
            //check if j is in the first column or second to last column
            int test1 = 0;
            if ((n1 == '*') && (test1 != 1)) {
                neighbors++;
            } if(n2=='*') {
               neighbors++;
            } if(n3=='*') {
               neighbors++;
            } if((n4=='*')&&(test1!=1)) {
               neighbors++;
            } if(n5=='*') {
               neighbors++;
            } if((n6=='*')&&(test1!=1)) {
               neighbors++;
            } if(n7=='*') {
               neighbors++;
            } if(n8=='*') {
               neighbors++;
            }

            if ((current=='*') && (neighbors<2)) {
                (*(nextGeneration.get() + j)) = ' ';
            } else if ((current == '*') && (neighbors>3)) {
                (*(nextGeneration.get() + j)) = ' ';
            } else if ((current == '*') && (neighbors==2 || neighbors == 3)) {
                (*(nextGeneration.get() + j)) = '*';
            } else if ((current == ' ') && (neighbors == 3)) {
                (*(nextGenration.get() + j)) = ' ';
            } else {
                (*(.get() + j)) = ' ';
            }
            //reset neighbors
            neighbors = 0;
        }

        //reset world array to new gen
        for (int x = 0; x <= arraySize; x++) {
            if ((*(nextGenration) || (*(nextGenration) == ' ')) || (*(nextGenration) == '*')) {
                (*(world.get()+x)) = (*(nextGeneration.get() + x));
            }
        }
        //print out the new generation
        cout << "GENERATION " << i+1 << endl;
        for (int y = 0; y <= arraySize; y++) {
            cout << (*(world.get() + y));
        }
        cout << endl << endl;
    }
    return 0;
}
//////////////
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;
string filename = "";

void getMatrixDimensions(int &numRows, int &numColumns) {
    //create file
    ifstream infile;
    infile.open(filename);
    if (infile) {
        //iterate through file
        char l[1];
        while (infile.read(l, 1)) {
            //check if end of line
            string letter = "";
            letter += l[0];
            if (letter.compare("\n") == 0) {
                numRows++;
            }
            numColumns++;
        }
    }
    //adjust to columns to compensate for end line characters
    numColumns = (numColumns - 2) / numRows;
    infile.close();
}

void createWorld(string world[], int numRows, int numColumns) {
    //create file
    ifstream infile;
    infile.open(filename);
    //adjust numRows and numColumns
    int worldSize = ((numRows) * (numColumns))+2;
    if (infile) {
        //iterate through file
        for (int i = 0; i <= worldSize; i++) {
            //get organism at specific file position
            char l[1];
            infile.read(l, 1);
            string organism = "";
            organism += l[0];
            //assign organism to specific index in array
            if (organism.compare("\n") != 0) {
                *(world + i) = organism;
            }
        }
    }
    infile.close();
}

void runSimulation(string world[], int numRows, int numColumns) {
    //store birth and death locations
    int column = numColumns+1;
    int deadLocations[1000];
    int bornLocations[1000];
    int deathIndex = 0;
    int birthIndex = 0;
    for (int i = 0; i <= (numRows * numColumns) + 3; i++) {
    //print new line once necessary
        string organism = *(world + i);
        int neighbors = 0;

        //check top row
        //check vertical neighbors
        if ((i-column) >= 0) {
            string topNeighbor = *(world + (i-column));
            if (topNeighbor.compare("*") == 0) {
                neighbors++;
            }
        }

        if ((i+column) <= (numColumns * numRows) + 3) {
            string bottomNeighbor = *(world + (i+column));
            if (bottomNeighbor.compare("*") == 0) {
                neighbors++;
            }
        }
        //check horizontal neighbors
        if ((i-1) >= 0) {
            string leftNeighbor = *(world + (i-1));
            if (leftNeighbor.compare("*") == 0) {
                neighbors++;
            }
        }
        if ((i+1) <= (numRows * numColumns) + 3) {
            string rightNeighbor = *(world + (i+1));
            if (rightNeighbor.compare("*") == 0) {
                neighbors++;
            }
        }
        //check diagonal neighbors
        if (((i-column)-1) >= 0) {
            string topLeftNeighbor = *(world + ((i-column)-1));
            string topRightNeighbor = *(world + ((i-column)+1));

            if (topLeftNeighbor.compare("*") == 0) {
                neighbors++;
            } if (topRightNeighbor.compare("*") == 0) {
                neighbors++;
            }
        }

        if (((i+column)+1) <= (numRows*numColumns)+3) {
            string botLeftNeighbor = *(world + ((i+column)-1));
            string botRightNeighbor = *(world + ((i+column)+1));
            if (botLeftNeighbor.compare("*") == 0) {
                neighbors++;
            } if (botRightNeighbor.compare("*") == 0) {
                neighbors++;
            }
        }
        //store born and death locations
        if (organism.compare("*") == 0) {
            if (neighbors < 2) {
                deadLocations[deathIndex] = i;
                deathIndex++;
            }
            if (neighbors > 3) {
                deadLocations[deathIndex] = i;
                deathIndex++;
            }
            if (neighbors == 6) {
                deadLocations[deathIndex] = i;
                deathIndex++;
            }
        }
        if (organism.compare(" ") == 0) {
            if (neighbors == 3) {
                bornLocations[birthIndex] = i;
                birthIndex++;
            }
        }

    }
    //change the world
    for (int i = 0; i < deathIndex; i++) {
        *(world+deadLocations[i]) = " ";
    }

    for (int i = 0; i < birthIndex; i++) {
        *(world+bornLocations[i]) = "*";
    }
}

void printWorld(string world[], int numRows, int numColumns) {
    //iterate through world array
    for (int i = 0; i <= (numRows * numColumns) + 3; i++) {
        //print new line once necessary
        if (((i % (numColumns + 1)) == 0) && (i != 0)) {
            cout << endl << *(world+i);
        } else {
            cout << *(world+i);
        }
    }
}

int main() {
    int numRows = 1;
    int numColumns = 0;
    int generations = 0;

    cout << "Enter File Name >> " << endl;
    cin >> filename;
    //create an empty array with the new dimensions
    getMatrixDimensions(numRows, numColumns);
    string world[10000];
    //fill the array with the text file organisms
    createWorld(world, numRows, numColumns);
    //ask the users for the number of generations they want to run
    cout << "How Many Generations >> " << endl;
    cin >> generations;
    //run and print the simulation
    cout << endl;
    for (int i = 1; i <= generations; i++) {
        cout << "GENERATION " << i;
        runSimulation(world, numRows, numColumns);
        cout << "\n";
        printWorld(world, numRows, numColumns);
        cout << "\n";
    }
}
