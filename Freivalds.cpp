#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

#include <thread>
#include <future>

#include <chrono>
#include <random>

int randomNumber(int min, int max) {
   static thread_local std::mt19937 generator(std::chrono::system_clock::now().time_since_epoch().count());
   std::uniform_int_distribution<int> distribution(min, max);
   return distribution(generator);
}

// Multiplies a matrix with a vector, and returns the vector result
std::vector<int> matrixVectorMultiplier(std::vector<std::vector<int>> matrix, std::vector<int> vector) {
    std::this_thread::sleep_for(std::chrono::seconds(3)); // DELETE THIS!!!!!
    // Calc matrix * vector and return it
    for (int i = 0; i < vector.size(); i++)
    {
        for (int j = 0; j < vector.size(); j++)
        {
            // TODO 
        }
        
    }
    
    return vector;
}

// Using the Freivalds method check if (a + b = c) is true
int checkMatrix(std::vector<std::vector<int>> aMatrix, std::vector<std::vector<int>> bMatrix, std::vector<std::vector<int>> cMatrix) {
    std::this_thread::sleep_for(std::chrono::seconds(3)); // DELETE THIS!!!!!
    
    std::vector<int> alpaV; //random {0,1} vector
    // std::cout << "Alpha: ";
    for (int i = 0; i < aMatrix.size(); i++) {
        int tempR = randomNumber(0,1);
        alpaV.push_back(tempR);
        // std::cout << tempR << " ";
    }
    // std::cout << "\n" << std::endl;
    std::vector<int> betaV = matrixVectorMultiplier( aMatrix, matrixVectorMultiplier(bMatrix, alpaV));
    std::vector<int> gammaV = matrixVectorMultiplier(cMatrix, alpaV);
    if (1 == 1) {
        return 0;
    } else {
        1;
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
        std::cout << "dim: " << vectorDim << " try: " << tryCount << std::endl;
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

    // Write vector to console
    {
        for (auto row : aMatrix) {
            for (auto el : row) {
                std::cout << el << ' ';
            }
            std::cout << "\n";
        }
        std::cout << "\n";
        for (auto row : bMatrix) {
            for (auto el : row) {
                std::cout << el << ' ';
            }
            std::cout << "\n";
        }
        std::cout << "\n";
        for (auto row : cMatrix) {
            for (auto el : row) {
                std::cout << el << ' ';
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    // Starting threads
    std::vector<std::future<int> > futureResults;
    for (int i = 0; i < tryCount; i++) {
        futureResults.push_back(std::async(std::launch::async, checkMatrix, aMatrix, bMatrix, cMatrix));
    }

    // Get the result from the threads
    for (int i = 0; i < tryCount; i++) {
        std::cout << futureResults[i].get() << "::";
    }
}