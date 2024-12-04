import random
import math
from typing import List
import csv


def evaluate(features):
    randomValue = random.randint(0, 9999)  
    randomAccuracy = randomValue / 100.0
    return randomAccuracy

def forwardSelection(numFeatures):
    print("=== Forward Selection Algorithm ===")
    features = set()  # empty set where we will select features
    bestFeatures = set()  # store the best features
    bestAccuracy = evaluate(features)

    print(f"Using no features and 'random' evaluation, I get an accuracy of {bestAccuracy:.2f}%\n")
    print("== Beginning search ==")

    for i in range(1, numFeatures + 1):
        curr = features.copy()  # current best for this search
        this_accuracy = 0.0

        for j in range(1, numFeatures + 1):
            if j in features:  # skip if the feature is already in the set
                continue

            tempFeatures = features.copy()
            tempFeatures.add(j)
            currAccuracy = evaluate(tempFeatures)

            print(f"Using feature(s) {' '.join(map(str, tempFeatures))} | Accuracy is {currAccuracy:.2f}%")

            if currAccuracy > this_accuracy:  # greedy search for the best accuracy
                this_accuracy = currAccuracy
                curr = tempFeatures

        features = curr  # select the best features for this iteration

        # Check if the current accuracy is better than the best so far
        if this_accuracy > bestAccuracy:
            bestAccuracy = this_accuracy
            bestFeatures = features.copy()
        else:
            print("(Warning: Accuracy decreased!)")

        # Trace the progress
        print(f"Feature set {' '.join(map(str, features))} was best, accuracy is {this_accuracy:.2f}%")

    # Final output
    print("=== Search Completed ===")
    if bestAccuracy > 0.0:
        print(f"Finished search!! The best feature subset is {{{' '.join(map(str, bestFeatures))}}}, "
              f"which has an accuracy of {bestAccuracy:.2f}%")

def backwardSelection(num_features):
    print("=== Backward Elimination Search Algorithm ===")
    all_features = set(range(1, num_features + 1))
    initial_accuracy = evaluate(all_features)
    print(f"Initial accuracy with all features: {initial_accuracy:.2f}%\n")
    print("== Beginning Search ==")
    bestAccuracy = initial_accuracy
    best_feature_set = all_features.copy()  # Initially, all features are included
    while len(all_features) > 1:  # Loop until only one feature remains
        bestAccuracy_in_iteration = 0.0
        best_set_in_iteration = set()
        for feature in all_features:
            reduced_set = all_features.copy()
            reduced_set.remove(feature)  # Remove a single feature
            accuracy = evaluate(reduced_set)

            print(f"Using features: {' '.join(map(str, reduced_set))} | Accuracy is {accuracy:.2f}%")
            if accuracy > bestAccuracy_in_iteration:
                best_set_in_iteration = reduced_set
                bestAccuracy_in_iteration = accuracy

        all_features = best_set_in_iteration  # Update to the set with the best accuracy

        if bestAccuracy_in_iteration > bestAccuracy:
            best_feature_set = all_features.copy()
            bestAccuracy = bestAccuracy_in_iteration
        else:
            print("(Warning: Accuracy decreased!)")

        print(f"Best feature set after this iteration: {' '.join(map(str, all_features))} "
              f"| Accuracy: {bestAccuracy_in_iteration:.2f}%")

    print("=== Search Completed ===")
    print(f"Best feature subset: {{ {' '.join(map(str, best_feature_set))} }} | Accuracy: {bestAccuracy:.2f}%")

def specialSelection(numFeatures):
    print("not implemented yet")


trainingData = []
classLabels = []

def euclidean_distance(point1: List[float], point2: List[float], feature_subset: List[int]) -> float:
    distance = 0.0
    for feature in feature_subset:
        distance = distance + (point1[feature] - point2[feature]) ** 2
    return math.sqrt(distance)

def train(data: List[List[float]], labels: List[int]):
    global trainingData, classLabels
    trainingData = data
    classLabels = labels


def test(training_data: List[List[float]], test_instance: List[float], selected_features: List[int]) -> int:
    """
    Predicts the label for a given test instance using the nearest neighbor algorithm.

    :param training_data: The training dataset (list of instances where the first element is the class label).
    :param test_instance: Feature values of the test instance to classify (first element excluded if it's a label).
    :param selected_features: A list of indices representing the features to use for comparison.
    :return: The class label of the nearest neighbor.
    """
    if not training_data or not selected_features:
        raise ValueError("Training data or feature subset is empty.")

    closest_neighbor_index = -1  # Initialize with an invalid index
    minimum_distance = float('inf')  # Start with an infinite distance

    # Iterate over the training data
    for idx, training_instance in enumerate(training_data):
        # Compute the distance using the specified feature subset
        distance = euclidean_distance(
            training_instance[1:],  # Exclude the class label from the training instance
            test_instance,
            selected_features
        )

        # Update the closest neighbor if a smaller distance is found
        if distance < minimum_distance:
            minimum_distance = distance
            closest_neighbor_index = idx

    if closest_neighbor_index == -1:
        raise RuntimeError("Failed to find a nearest neighbor. Check your data.")

    # Return the label of the closest neighbor
    return int(training_data[closest_neighbor_index][0])  # Class label is the first element



def one_out_validation(data, feature_subset, num_instances):
    """
    Performs leave-one-out cross-validation and returns the accuracy.
    """
    correct_predictions = 0

    for test_idx in range(num_instances):
        # Exclude the test instance
        training_data = [instance for i, instance in enumerate(data) if i != test_idx]

        # Predict the label for the test instance
        test_instance = data[test_idx][1:]  # Exclude the actual label
        actual_label = int(data[test_idx][0])  # Extract the actual label

        predicted_label = predict_label(training_data, test_instance, feature_subset)

        # Check if the prediction is correct
        if predicted_label == actual_label:
            correct_predictions += 1

    accuracy = (correct_predictions / num_instances) * 100
    return accuracy



def normalize_data(dataset, feature_count, instance_count):
    feature_means = []
    for feature_idx in range(1, feature_count + 1):
        feature_mean = sum(instance[feature_idx] for instance in dataset) / instance_count
        feature_means.append(feature_mean)

    # Calculate the standard deviation (std) for each feature
    feature_stds = []
    for feature_idx in range(1, feature_count + 1):
        variance = sum((instance[feature_idx] - feature_means[feature_idx - 1]) ** 2 for instance in dataset) / instance_count
        feature_stds.append(math.sqrt(variance))

    # Normalize the data in place
    for instance_idx in range(instance_count):
        for feature_idx in range(1, feature_count + 1):
            dataset[instance_idx][feature_idx] = (
                (dataset[instance_idx][feature_idx] - feature_means[feature_idx - 1]) / feature_stds[feature_idx - 1]
            )
    return dataset



def main():
    print("Welcome to Trisha-Shreya's Feature Selection Algorithm.")

   
    
    # Get file name from the user
    file = input("Type in the name of the file to test: ")

    # Try to open the file, raise an error if it doesn't exist
    try:
        with open(file, 'r') as data:
            # Read the first line to determine the number of features
            first_line = data.readline()
            num_features = len(first_line.split()) - 1

            # Read all lines to determine the number of instances
            data.seek(0)  # Reset file pointer
            num_instances = sum(1 for _ in data)

            # Reset file pointer to the start
            data.seek(0)

            # Store the data into a 2D array
            instances = [
                [float(value) for value in line.split()] for line in data
            ]
    except FileNotFoundError:
        print(f"The file '{file}' does not exist. Exiting program.")
        return

    # Display dataset details
    print(f"This dataset has {num_features} features (not including the class attribute), "
          f"with {num_instances} instances.")

    # Algorithm selection
    print("Type the number of the algorithm you want to run.")
    print("1. Forward Selection")
    print("2. Backward Elimination")
    print("3. Special algorithm (Not completed)")
    
    # Get and validate the user's choice
    while True:
        try:
            choice = int(input())
            if 1 <= choice <= 3:
                break
            else:
                print("Invalid choice, please try again.")
        except ValueError:
            print("Invalid input, please enter a number between 1 and 3.")

    # Normalize the data
    print("Please wait while I normalize the data... Done!")
    normalized_instances = normalize_data(instances, num_features, num_instances)

    # Run nearest neighbor with all features and perform leave-one-out validation
    all_features = list(range(1, num_features + 1))
    accuracy = one_out_validation(normalized_instances, all_features, num_instances)
    print(f"Running nearest neighbor with all {num_features} features, "
          f"using 'leave-one-out' evaluation, I get an accuracy of {accuracy:.2f}%.")

    print("Beginning search...\n")

    # Run the selected algorithm
    if choice == 1:
        forward_selection(normalized_instances, num_instances, num_features)
    elif choice == 2:
        backward_elimination(normalized_instances, num_instances, num_features, accuracy)
    elif choice == 3:
        print("Special algorithm not completed yet, exiting.")











    num_features = int(input("Please enter total number of features: "))
    
    print("Type the number of the algorithm you want to run.")
    print("1. Forward Selection")
    print("2. Backward Selection")
    print("3. Our Special Algorithm")
    
    try:
        alg_type = int(input("Enter your choice: "))
    except ValueError:
        print("Invalid input. Please enter a valid integer.")
        return

    if alg_type == 1:
        forwardSelection(num_features)
    elif alg_type == 2:
        backwardSelection(num_features)
    elif alg_type == 3:
        specialSelection(num_features)
    else:
        print("Invalid Entry")

if __name__ == "__main__":
    main()

