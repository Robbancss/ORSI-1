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
                // std::cout << el << ' ';
            }
            // std::cout << "\n";
}

int randomNumber(int min, int max) {
   static thread_local std::mt19937 generator(std::chrono::system_clock::now().time_since_epoch().count());
   std::uniform_int_distribution<int> distribution(min, max);
   return distribution(generator);
}

// Multiplies a matrix with a vector, and returns the vector result
std::vector<int> matrixVectorMultiplier(std::vector<std::vector<int>> matrix, std::vector<int> vector) {
    // std::this_thread::sleep_for(std::chrono::seconds(3)); // DELETE THIS!!!!!
    // Calc matrix * vector and return it
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
    
    { // Write matrix * vector to console
        // // std::cout << "The matrix: ";
        // for (auto row : matrix) {
        //     vectorToConsole(row);
        //     // std::cout << "\n";
        // }
        // // std::cout << "Random vector: ";
        // vectorToConsole(vector);
        // // std::cout << "CalcVector: ";
        // vectorToConsole(tempVector);
        // // std::cout << "___" << std::endl;
    }

    return tempVector;
}

// Using the Freivalds method check if (a + b = c) is true
int checkMatrix(std::vector<std::vector<int>> aMatrix, std::vector<std::vector<int>> bMatrix, std::vector<std::vector<int>> cMatrix) {
    // std::this_thread::sleep_for(std::chrono::seconds(3)); // DELETE THIS!!!!!
    
    std::vector<int> alpaV; //random {0,1} vector
    for (int i = 0; i < aMatrix.size(); i++) {
        int tempR = randomNumber(0,1);
        alpaV.push_back(tempR);
    }
    // std::cout << "ALPAV: \n" << std::endl;
    vectorToConsole(alpaV);
    std::vector<int> betaV = matrixVectorMultiplier( aMatrix, matrixVectorMultiplier(bMatrix, alpaV));
    std::vector<int> gammaV = matrixVectorMultiplier(cMatrix, alpaV);
    if (betaV == gammaV) {
        return 0;
    } else {
        return 1;
    }
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
        // std::cout << "dim: " << vectorDim << " try: " << tryCount << std::endl;
    }
    while (std::getline(ifs, tempstr)) {
        std::istringstream iss(tempstr);
        std::vector<int> tempv;
        while (iss >> tempint) {
            tempv.push_back(tempint);
        }
        if (lineCounter < 3) {
            aMatrix.push_back(tempv);
        } else if (lineCounter < 6) {
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

    int result = 0;
    // Get the result from the threads
    for (int i = 0; i < tryCount; i++) {
        result = result + futureResults[i].get();
    }

    std::ofstream out("output.txt");
    if (result == 0) {
        out << "accepted";
        // // std::cout << "accepted" << std::endl;
    } else {
        out << "rejected";
        // // std::cout << "rejected" << std::endl;
    }
    out.close();
}