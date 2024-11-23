
#include <iostream>
#include <vector>
#include <set>
#include <cstdlib> 
#include <ctime>  

using namespace std;

double evaluate(const set<int>& features) {         // Dummy evaluation function 
    int randomValue = rand() % 10000;
    double randomAccuracy = static_cast<double>(randomValue) / 100.0;
    return randomAccuracy;
}

void forwardSelection(int numFeatures);

void backwardSelection(int numFeatures); 

void specialSelection(int numFeatures);

int main() {
    cout << "Welcome to Trisha-Shreya's Feature Selection Algorithm." << endl;

    cout << "Please enter total number of features: " << endl;
    int numFeatures;
    cin >> numFeatures;

    cout << "Type the number of the algorithm you want to run." << endl;
    cout << "1. Forward Selection" << endl;
    cout << "2. Backward Selection" << endl;
    cout << "3. Our Special Algorithm" << endl;
    int algType;
    cin >> algType;

    if (algType == 1)
    {
        forwardSelection(numFeatures);
    }

    else if (algType == 2)
    {
        backwardSelection(numFeatures); 
    }

    else if (algType == 3)
    {
        specialSelection(numFeatures);
    }

    else 
    {
        cout << "Invalid Entry" << endl; 
    }

    return 0; 
}
