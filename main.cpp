
#include <iostream>
#include <vector>
#include <set>
#include <cstdlib> 
#include <ctime>  
#include <iomanip>

using namespace std;

double evaluate(const set<int>& features) {         // Dummy evaluation function 
    int randomValue = rand() % 10000;
    double randomAccuracy = static_cast<double>(randomValue) / 100.0;
    return randomAccuracy;
}

void forwardSelection(int numFeatures)
{
    cout << "== Forward Selection Algorithm ==" << endl; 

    set<int> features; // empty set where we will select features and fill
    set<int> best_features; // store the best features 
    double best_accuracy = evaluate(features);

    cout << "Using no features and “random” evaluation, I get an accuracy of " 
         << fixed << setprecision(2) << best_accuracy << "%\n" << endl;

    cout << "Beginning search." << endl;
    for (int i = 1; i <= numFeatures; i++) {
        set<int> curr = features; // curr best for this search
        double bestAccuracyThisStep = 0.0;

        for (int j = 1; j <= numFeatures; j++) 
        {
            if (features.find(j) != features.end()) continue; 
            if (features.find(j) == features.end()) 
            {

                set<int> tempFeatures = features;
                tempFeatures.insert(j);

                double currAccuracy = evaluate(tempFeatures);
                cout << "Using feature(s) ";

                for (int f : tempFeatures) cout << f << " ";
                    cout << "accuracy is " << currAccuracy << "%" << endl;

                    if (currAccuracy > bestAccuracyThisStep) // greedy search finding the best accuracy
                    {
                        bestAccuracyThisStep = currAccuracy;
                        curr = tempFeatures;
                    }
            }
        }

        features = curr; // select the features 

// if better then all then change otherwise give a wanring
        if (bestAccuracyThisStep > best_accuracy) 
        {
            best_accuracy = bestAccuracyThisStep;
            best_features = features;

// trace 
        } 
        else 
        {
            cout << "(Warning: Accuracy decreased!)" << endl;
        }

        
        cout << "Feature set ";
        for (int f : features) cout << f << " ";
            cout << "was best, accuracy is " << bestAccuracyThisStep << "%" << endl;
    }
// cout final output

if (best_accuracy > 0.0)
{
    cout << "Finished search!! The best feature subset is {";
    for (int f : best_features) cout << f << " ";
    cout << "}, which has an accuracy of " << best_accuracy << "%" << endl;
}
}

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
