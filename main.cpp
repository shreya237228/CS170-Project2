
#include <iostream>
#include <vector>
#include <set>
#include <cstdlib> // For rand()
#include <ctime>   // For seeding rand()

using namespace std;

double evaluate(const set<int>& features) {         // Dummy evaluation function 
    int randomValue = rand() % 10000;
    double randomAccuracy = static_cast<double>(randomValue) / 100.0;
    return randomAccuracy;
}

int main(){
    cout<< "Welcome to Trisha-Shreya's Feature Selection Algorithm."<<endl;
    cout<<"Please enter total number of features: "<<endl;
    int numFeatures;
    cin>> numFeatures;
    cout<<"Type the number of the algorithm you want to run."<<endl;
    cout<<"1. Forward Selection"<<endl;
    cout<<"2. Backward Selection"<<endl;
    cout<<"3. Our Special Algorithm"<<endl;
    int algType;
    cin>> algType;

    return 0; 
}
