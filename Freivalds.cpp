#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

#include <thread>
#include <future>

#include <chrono>
#include <random>

void vectorToConsole(std::vector<int> vector) {
    for (auto el : vector) {
        std::cout << el << ' ';
    }
    std::cout << "\n";
}

int randomNumber(int min, int max) {
   static thread_local std::mt19937 generator(std::chrono::system_clock::now().time_since_epoch().count());
   std::uniform_int_distribution<int> distribution(min, max);
   return distribution(generator);
}

// Multiplies a matrix with a vector, and returns the vector result
std::vector<int> matrixVectorMultiplier(std::vector<std::vector<int>> const& matrix, std::vector<int> const& vector) {
    std::vector<int> tempVector;
    for (int i = 0; i < vector.size(); i++)
    {
        int tempRowSum = 0;
        for (int j = 0; j < vector.size(); j++)
        {
            tempRowSum = tempRowSum + matrix[i][j]*vector[j];
        }
        tempVector.push_back(tempRowSum);
        
    }

    return tempVector;
}

// Using the Freivalds method check if (a * b = c) is true
int checkMatrix(std::vector<std::vector<int>> const& aMatrix, std::vector<std::vector<int>> const& bMatrix, std::vector<std::vector<int>> const& cMatrix) {
    
    std::vector<int> alpaV; //random {0,1} vector
    for (int i = 0; i < aMatrix.size(); i++) {
        int tempR = randomNumber(0,1);
        alpaV.push_back(tempR);
    }
    std::vector<int> betaV = matrixVectorMultiplier( aMatrix, matrixVectorMultiplier(bMatrix, alpaV));
    std::vector<int> gammaV = matrixVectorMultiplier(cMatrix, alpaV);
    return betaV == gammaV;
}

int main() {
    std::vector<std::vector<int>> aMatrix;
    std::vector<std::vector<int>> bMatrix;
    std::vector<std::vector<int>> cMatrix;
    std::ifstream ifs("input.txt");
    std::string tempstr;
    int tempint;
    int vectorDim;
    int tryCount;
    int lineCounter = 0;

    {
        std::getline(ifs, tempstr);
        std::istringstream iss(tempstr);
        iss >> vectorDim;
        iss >> tryCount;
    }

    // Separating the matrixes
    while (std::getline(ifs, tempstr)) {
        std::istringstream iss(tempstr);
        std::vector<int> tempv;
        while (iss >> tempint) {
            tempv.push_back(tempint);
        }
        if (lineCounter < vectorDim) {
            aMatrix.push_back(tempv);
        } else if (lineCounter < 2*vectorDim) {
            bMatrix.push_back(tempv);
        } else {
            cMatrix.push_back(tempv);
        }
        lineCounter +=1;
    }

    // Starting threads
    std::vector<std::future<int> > futureResults;
    for (int i = 0; i < tryCount; i++) {
        futureResults.push_back(std::async(std::launch::async, checkMatrix, aMatrix, bMatrix, cMatrix));
    }

    int result = 1;
    // Getting the result from the threads
    for (int i = 0; i < tryCount; i++) {
        result *= futureResults[i].get();
    }

    std::ofstream out("output.txt");
    if (result == 1) {
        out << "accepted";
    } else {
        out << "rejected";
    }
    out.close();
}