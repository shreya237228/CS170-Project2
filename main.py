import random
import math
from typing import List
import time
from itertools import combinations

def evaluate(features):
    randomAccuracy=random.randint(0, 9999)/ 100.0 
    return randomAccuracy

def forwardSelection(numFeatures, data, featureSubset, totalInstances):
    print("=== Forward Selection Algorithm ===")
    features=set()  
    bestFeatures=set()  
    featureSet=[]
    bestAccuracy=leaveOneOut(data, featureSet, totalInstances)
    print(f"Running nearest neighbor with no features (default rate), using “leaving-one-out” evaluation, I get an accuracy of  {bestAccuracy:.2f}%\n")
    print("== Beginning search ==")
    for i in range(1, numFeatures + 1):
        curr = features.copy()  
        thisAccuracy = 0.0

        for j in range(1, numFeatures + 1):
            if j in features:  
                continue

            tempFeatures=features.copy()
            tempFeatures.add(j)
            currAccuracy=leaveOneOut(data, tempFeatures, totalInstances)

            print(f"Using feature(s) {' '.join(map(str, tempFeatures))} | Accuracy is {currAccuracy:.2f}%")

            if currAccuracy> thisAccuracy:  
                thisAccuracy= currAccuracy
                curr= tempFeatures
        features=curr  
        if thisAccuracy>bestAccuracy:
            bestAccuracy= thisAccuracy
            bestFeatures= features.copy()
        else:
            print("(Warning, Accuracy has decreased!)")

        print(f"Feature set {' '.join(map(str, features))} was best, accuracy is {thisAccuracy:.2f}%")
    print("=== Search Completed ===")
    if  0.0 < bestAccuracy:
        print(f"Finished search!! The best feature subset is {{{' '.join(map(str, bestFeatures))}}}, "
              f"which has an accuracy of {bestAccuracy:.2f}%")

def backwardSelection(numFeatures, data, featureSubset, totalInstances):
    print("=== Backward Elimination Search Algorithm ===")
    allFeatures = set(range(1, numFeatures + 1))
    featureSet=[]
    bestAccuracy=leaveOneOut(data, featureSet, totalInstances)
    print(f"Running nearest neighbor with no features (default rate), using “leaving-one-out” evaluation, I get an accuracy of  {bestAccuracy:.2f}%\n")
    print("== Beginning Search ==")
    bestSet= allFeatures.copy() 
    while 1<len(allFeatures):  
        bestFoundAcc= 0.0
        bestFoundSet= set()
        for feature in allFeatures:
            changedSet= allFeatures.copy()
            changedSet.remove(feature)  
            accuracy= leaveOneOut(data, changedSet, totalInstances)
            print(f"Using features: {' '.join(map(str, changedSet))} | Accuracy is {accuracy:.2f}%")
            if accuracy>bestFoundAcc:
                bestFoundSet=changedSet
                bestFoundAcc= accuracy
        allFeatures = bestFoundSet  

        if bestFoundAcc< bestAccuracy:
            print("(Warning: Accuracy decreased!)")
        else:
            bestSet= allFeatures.copy()
            bestAccuracy = bestFoundAcc
        print(f"Best feature set after this iteration: {' '.join(map(str, allFeatures))} "
              f"| Accuracy: {bestFoundAcc:.2f}%")
    print("=== Search Completed ===")
    print(f"Best feature subset: {{ {' '.join(map(str, bestSet))} }} | Accuracy: {bestAccuracy:.2f}%")

def ourAlg(data, total_features, total_instances):
    print("=== Working on it ===")
    pass

'''
trainingData = []
classLabels = []

def train(data: List[List[float]], labels: List[int]):
    global trainingData, classLabels
    trainingData = data
    classLabels = labels

'''

def euclideanDistance(data, currPoint,featureSubset, targetPoint):
    currDist=0
    for feature in featureSubset:
        currDiff= data[currPoint][feature] - data[targetPoint][feature]
        currDist += currDiff** 2

    return math.sqrt(currDist)


def test(data, targetPoint, featureSubset, numData):
    nnIndex = -1
    closestDistance = float('inf')  
    for currPoint in range(numData):
        if currPoint == targetPoint:
            continue
       
        currDistance =  euclideanDistance(data, currPoint,featureSubset, targetPoint)
        if currDistance<closestDistance:
            closestDistance= currDistance
            nnIndex= currPoint
    return nnIndex

 
def leaveOneOut(data, featureSubset, totalInstances):   #leaves one feature out and predits for that feature using remaining data
    correctPrediction = 0.0
    for currFeature in range(totalInstances):
        oneOut=currFeature
        nn=test(data, oneOut, featureSubset, totalInstances)
        if data[nn][0] == data[oneOut][0]:
            correctPrediction=correctPrediction + 1
    return (correctPrediction/totalInstances) * 100


def normalize_data(dataset, numFeatures, numInstances): #need to find mean and std
    means= [0]*numFeatures
    for featIndex in range(numFeatures):
        means[featIndex]= sum(row[featIndex+1] for row in dataset)/numInstances
    stDeviation= [0]*numFeatures
    for featIndex in range(numFeatures):
        sumOfSqrdDiff= sum((row[featIndex+1]- means[featIndex]) ** 2 for row in dataset )
        stDeviation[featIndex]= math.sqrt(sumOfSqrdDiff/numInstances)

    for row in dataset:
        for featIndex in range(numFeatures):
            row[featIndex+1]= (row[featIndex+ 1]- means[featIndex])/stDeviation[featIndex]
    return dataset


def ourAlg(normalizedData, numFeatures, num_instances):
    print("Working")
    pass

def main():
    print("Welcome to Trisha-Shreya's Feature Selection Algorithm.")
    '''
    smallDataset="small-test-dataset.txt"
    largeDataset="large-test-dataset.txt"
    #small file
    with open(smallDataset, 'r') as smallData:
        first_line = smallData.readline()
        num_smallFeatures = len(first_line.split())-1
        smallData.seek(0)
        num_small_instances=sum(1 for _ in smallData)
        smallData.seek(0)
        small_instances=[[float(value) for value in line.split()] for line in smallData]
        print("==== Starting the process of Normalising, Finding the Nearest Neighbour and Performing the Leave one out Validation =====")
        startTime=time.time()
        normalizeDataSmall= normalize_data(small_instances, num_smallFeatures, num_small_instances)
        smallFeatureSubset=[3, 5, 7]  
        accSmallData = leaveOneOut(normalizeDataSmall,  smallFeatureSubset, num_small_instances)
        endTime=time.time()
        timeTaken= endTime- startTime
        print(f"Accuracy for small dataset with features { smallFeatureSubset}: {accSmallData:.2f}%")
        print(f"Time taken: {timeTaken:.6f} seconds")
    #large file
    with open(largeDataset, 'r') as largeData:
        first_line= largeData.readline()
        num_large_features= len(first_line.split())-1
        largeData.seek(0)
        num_large_instances = sum(1 for _ in largeData)
        largeData.seek(0)
        large_instances = [[float(value) for value in line.split()] for line in largeData]
        print("==== Starting the process of Normalising, Finding the Nearest Neighbour and Performing the Leave one out Validation =====")
        startTime= time.time()
        normaliseLargeData=normalize_data(large_instances, num_large_features, num_large_instances)
        large_featureSubset=[1, 15, 27]  # Features to test for large dataset
        large_accuracy= leaveOneOut(normaliseLargeData, large_featureSubset, num_large_instances)
        endTime= time.time()
        timeTaken= endTime- startTime
        print(f"Accuracy for large dataset with features {large_featureSubset}: {large_accuracy:.2f}%")
        print(f"Time taken: {timeTaken:.6f} seconds")
'''

    fileName= (input("Type in the name of the file to test: "))
    
    print("Type the number of the algorithm you want to run.")
    print("1. Forward Selection")
    print("2. Backward Selection")
    print("3. Our Special Algorithm")
    algType = int(input("Enter your choice: "))

    with open(fileName, 'r') as fileData:
        first_line = fileData.readline()
        numFeatures = len(first_line.split())-1
        fileData.seek(0)
        num_instances=sum(1 for _ in fileData)
        fileData.seek(0)
        file_instances=[[float(value) for value in line.split()] for line in fileData]
        print(f"This dataset has {numFeatures} features (not including the class attribute), with {num_instances} instances.")
        print("==== Please wait while I normalize the data... Done! ====")
        normalizedData= normalize_data(file_instances,  numFeatures, num_instances)

        featureSubset=[]
        for i in range(1, numFeatures + 1):
            featureSubset.append(i)

        if algType == 1:
            forwardSelection(numFeatures, normalizedData, featureSubset, num_instances)
        elif algType == 2:
            backwardSelection(numFeatures, normalizedData, featureSubset, num_instances)
        elif algType == 3:
           ourAlg(normalizedData, numFeatures, num_instances)
        else:
            print("Invalid Entry")



if __name__ == "__main__":
    main()


