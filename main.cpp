
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

void backwardSelection(int numFeatures){
cout << "=== Backward Elimination Search Algorithm ===" << endl;
    set<int> allFeatures;
    for (int i = 1; i <= numFeatures; ++i) {
        allFeatures.insert(i);
    }
    double initialAccuracy = evaluate(allFeatures);
    cout << "Initial accuracy with no features and random evaluation, I get an accuracy of " << initialAccuracy << "%" << endl;
    cout << "== Beginning Search ==" << endl;

    double bestAccuracy = initialAccuracy;
    set<int> bestFeatureSet = allFeatures;  //initially has all features

    while (allFeatures.size() > 1) {        // Loop until only one feature remains
        double bestAccuracyInIteration = 0.0;
        set<int> bestSetInIteration;
        for (auto it = allFeatures.begin(); it != allFeatures.end(); ++it) {
            set<int> reducedSet = allFeatures;
            reducedSet.erase(*it); // Remove a single feature
            double accuracy = evaluate(reducedSet);
            cout << "Using features: ";
            for (const int& featureNumber : reducedSet) {
                cout << featureNumber << " ";
            }
            cout << " | Accuracy is " << accuracy << "%" << endl;
            if (accuracy > bestAccuracyInIteration) {
                bestSetInIteration = reducedSet;
                bestAccuracyInIteration = accuracy;
            }
        }
        allFeatures = bestSetInIteration;   //Evaluate the set with the best accuracy
        if (bestAccuracyInIteration > bestAccuracy) {
            bestFeatureSet = allFeatures;
            bestAccuracy = bestAccuracyInIteration;
        } 
        else {
            cout << "(Warning: Accuracy decreased!)" << endl;
        }

        cout << "Best feature set after this iteration: ";
        for (auto it = allFeatures.begin(); it != allFeatures.end(); ++it) {
            cout << *it << " ";
        }
        cout << " | Accuracy: " << bestAccuracyInIteration << "%" << endl;
    }

    cout << "=== Search Completed ===" << endl;
    
    cout << "Best feature subset: { ";
    for (auto it = bestFeatureSet.begin(); it != bestFeatureSet.end(); ++it) {
        cout << *it << " ";
    }
    cout << "} | Accuracy: " << bestAccuracy << "%" << endl;
}

void specialSelection(int numFeatures){
    cout<<"not implemented yet"<<endl; 
}

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
       // forwardSelection(numFeatures);
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
