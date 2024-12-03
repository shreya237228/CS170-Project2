
#include <iostream>
#include <vector>
#include <set>
#include <cstdlib> 
#include <ctime>  
#include <iomanip>
#include <cmath>
#include <vector>
#include <limits>
#include <fstream>
#include <sstream>
#include <stdexcept>


using namespace std;

double evaluate(const set<int>& features) {         // Dummy evaluation function 
    int randomValue = rand() % 10000;
    double randomAccuracy = static_cast<double>(randomValue) / 100.0;
    return randomAccuracy;
}

void forwardSelection(int numFeatures)
{
    cout << "=== Forward Selection Algorithm ===" << endl; 

    set<int> features; // empty set where we will select features and fill
    set<int> best_features; // store the best features 
    double best_accuracy = evaluate(features);

    cout << "Using no features and “random” evaluation, I get an accuracy of " 
         << fixed << setprecision(2) << best_accuracy << "%\n" << endl;

    cout << "== Beginning search ==" << endl;
    for (int i = 1; i <= numFeatures; i++) 
    {
        set<int> curr = features; // curr best for this search
        double this_accuracy = 0.0;

        for (int j = 1; j <= numFeatures; j++) 
        {
            if (features.find(j) != features.end()) continue; 

            if (features.find(j) == features.end()) 
            {

                set<int> temp_features = features;
                temp_features.insert(j);
                double curr_accuracy = evaluate(temp_features);
                cout << "Using feature(s) ";

                for (int f : temp_features) cout << f << " ";
                    cout << "| Accuracy is " << curr_accuracy << "%" << endl;

                    if (curr_accuracy > this_accuracy) // greedy search finding the best accuracy
                    {
                        this_accuracy = curr_accuracy;
                        curr = temp_features;
                    }
            }
        }

        features = curr; // select the features 

    // if better then all then change otherwise give a wanring
        if (this_accuracy > best_accuracy) 
        {
            best_accuracy = this_accuracy;
            best_features = features;
        } 
        else 
        {
            cout << "(Warning: Accuracy decreased!)" << endl;
        }

    // trace 
        cout << "Feature set ";
        for (int f : features) cout << f << " ";
            cout << "was best, accuracy is " << this_accuracy << "%" << endl;
    }

    // cout final output
    cout << "=== Search Completed ===" << endl;
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


class Classifier {
private:
    vector<vector<double>> trainingData;
    vector<int> classLabels;
    int euclideanDistance(const vector<double>& point1, const vector<double>& point2, const vector<int>& featureSubset) {
        double distance=0.0;
        for (int feature:featureSubset){
            distance=distance+pow(point1[feature]-point2[feature], 2);
        }
        return sqrt(distance);
    }

public:
    void Train(const vector<vector<double>>& data, const vector<int>& labels) {
        trainingData=data;
        classLabels=labels;
    }

    int Test(const vector<double>& testVal, const vector<int>& featureSubset) {
        int nearestNeighbor = -1;
        double shortestDistance=numeric_limits<double>::infinity();
        for (size_t i=0; i < trainingData.size(); ++i) {
            double distance=euclideanDistance(trainingData[i], testVal, featureSubset);
            if (distance<shortestDistance) {
                shortestDistance=distance;
                nearestNeighbor=i;
            }
        }
        return classLabels[nearestNeighbor];
    }
};

class Validator {
public:
    double leaveOneOutValidator(const vector<vector<double>>& data, const vector<int>& classLabels, const vector<int>& featureSubset){
        size_t numValues
=data.size();
        Classifier classifier;
        int correct=0;
        for(size_t i=0; i<numValues
; ++i) {
            vector<vector<double>> trainingData;
            vector<int> trainingLabels;
            for (size_t j=0; j<numValues
    ;++j) {
                if (j!=i) {
                    trainingData.push_back(data[j]);
                    trainingLabels.push_back(classLabels[j]);
                }
            }
            classifier.Train(trainingData, trainingLabels);
            int predictedLabel=classifier.Test(data[i], featureSubset);      // Test the classifier on the left-out instance
            if (predictedLabel==classLabels[i]) {
                correct=correct+1;
            }
        }
        double accuracy= (static_cast<double>(correct)/numValues
) * 100.0;
        return accuracy;
    }
};

vector<vector<double>> normalize(vector<vector<double>>& data, int numFeatures, int numValues){
    vector<double> mean(numFeatures, 0.0);
    vector<double> stdDev(numFeatures, 0.0);
    for (int j=1; j<numFeatures; ++j) {
        for (int i=0; i<numValues; ++i) {
            mean[j-1]=mean[j-1]+data[i][j];
        }
        mean[j-1]=mean[j-1]/numValues;
    }
    for (int j = 1; j < numFeatures; ++j) {
        double variance=0.0;
        for (int i=0; i<numValues; ++i) {
            variance += pow(data[i][j]-mean[j-1], 2);
        }
        variance=variance/ numValues;
        stdDev[j-1]=sqrt(variance);
    }
    for (int i=0; i<numValues; ++i) {
        for (int j=1; j<=numFeatures; ++j) {
            data[i][j]=(data[i][j]-mean[j-1])/stdDev[j-1];
        }
    }
    return data;
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
};