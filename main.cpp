#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <iomanip>
/*
    Name: Emmanuel Giah
    NETID: ECG180001
    DATE: 3/3/2020
    PROFESSOR: JASON SMITH
    CLASS: 1337.007
*/

using namespace std;
string filename = "";

bool getMatrixDimensions(int &numRows,  int &arraySize) {
    //create file
    ifstream infile;
    infile.open(filename, ios::in|ios::out|ios::binary);
    char c;
    //error handling
    if(!infile.is_open()) {
        return false;
    }
    //end of line check
    while (infile.get(c)) {
        arraySize++;
        if(c=='\n') {
            numRows++;
        }
    }
    //end of line compensation
    arraySize--;
    numRows++;
    infile.close();
    return true;
}

void loadArray(char *arr, int arraySize){
    //create file
    char currentChar;
    ifstream infile;
    infile.open(filename, ios::in|ios::out|ios::binary);
    //error handling
    if(infile.is_open()){
         for(int i=0;i<=arraySize;i++){
            currentChar=(char)infile.get();
            (*(arr+i))=currentChar;
        }
    } else{
        cout<<"ERROR | FILE CAN NOT BE OPENED" <<endl;
    }

}

int getGenerations(){
    int generations=0;
    do {
        cout<<"ENTER NUMBER OF GENERATIONS (1-10) >>> "<<endl;
        cin>>generations;
        cin.clear();
        cin.ignore();
    } while ((generations<1)||(generations>10));
    return generations;
}

int main() {
    //initialize variables
    int sizeOfArr=0;
    int generations=0;
    int numRows=0;
    int numColumns;

    //prompt for the file name and do error handling
    do{
        cout << "ENTER FILE NAME >>> " << endl;
        cin >> filename;
    }while(!getMatrixDimensions(numRows,sizeOfArr));

    //create new world
    unique_ptr<char> world(new char[sizeOfArr]);
    cout << endl;
    //fill world with organisms
    loadArray(world.get(), sizeOfArr);
    //get number of generations;
    generations=getGenerations();
    //create neighbors and update variables
    numColumns=sizeOfArr/numRows;
    int neighbors=0;
    char n1,n2,n3,n4,n5,n6,n7,n8;
    unique_ptr<char> nextGen(new char[sizeOfArr]);
    numColumns++;
    //run simulation
    for(int i=0;i<generations;i++){
       for(int j=0;j<=sizeOfArr;j++){
           char current=(*(world.get()+j));
           if(current=='\n'){
               (*(nextGen.get()+j))= ('\n');
               continue;
           }
           //assign neighbors
           n1=(*(world.get()+j-numColumns-1));
           n2=(*(world.get()+j-numColumns));
           n3=(*(world.get()+j-numColumns+1));
           n4=(*(world.get()+j-1));
           n5=(*(world.get()+j+1));
           n6=(*(world.get()+j+numColumns-1));
           n7=(*(world.get()+j+numColumns));
           n8=(*(world.get()+j+numColumns+1));
           //border checking
           int test1=(0);
           if((n1=='*')&&(test1!=1)) {
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
           //update next generation
           if((current=='*')&&(neighbors<2)) {
               (*(nextGen.get() + j)) = (' ');
           } else if((current=='*')&&(neighbors>3)){
               (*(nextGen.get() + j)) = (' ');
           } else if ((current=='*')&&(neighbors==2||neighbors==3)){
               (*(nextGen.get() + j)) = ('*');
           } else if((current==' ')&&(neighbors==3)){
               (*(nextGen.get() + j)) = ('*');
           } else{
               (*(nextGen.get() + j)) = (' ');
           }
           neighbors=0;
       }
       //refresh array
       for(int x=0; x<=sizeOfArr; x++){
           if((*(nextGen)=='\n')||
              (*(nextGen)==' ')||
              (*(nextGen)=='*')){
               (*(world.get()+x))=(*(nextGen.get()+x));
           }
       }
       //print generation
        for (int i = 0; i < generations; i++) {
            cout<<"GENERATION "<<i+1<<endl;
            for(int y = 0; y <= sizeOfArr; y++){
                cout<< (*(world.get()+y));
            }
            cout<<endl<<endl;
        }
    }

    return 0;
}
