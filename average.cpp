#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc,char *argv[]){
    double num,avr;
    double sum = 0;
    if(argc == 1){
        cout << "Please input numbers to find average.\n";
    }
    else{
    for(int i = 0;i < argc;i++){
        num = atof(argv[i]);
        sum += num;
        avr = sum/(argc-1);
    }
    cout << "---------------------------------\n";
    cout << "Average of " << argc-1 << " numbers = " << avr;
    cout << "\n---------------------------------\n";
    }


}