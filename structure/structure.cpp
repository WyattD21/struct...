#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

// Program Overview:
//    
// This program reads data from an input file named "runners.txt", which contains information
// about each runner's name and the number of miles they run each day. The program then calculates
// the total miles and average miles run by each runner over the course of a week (7 days). Finally,
// it displays the results in a formatted table, including each runner's name, miles run each day,
// total miles for the week, and average miles run per day.
//
// Input:
// - Data file named "runners.txt" containing runner names and miles run each day.
//
// Output:
// - Formatted table displaying each runner's name, miles run each day, total miles for the week,
//   and average miles run per day.


const int NUM_RUNNERS = 5;
const int NUM_DAYS = 7;

struct Runner {
    std::string name;
    int dailyMiles[NUM_DAYS];
    double totalMiles;
    double averageMiles;
};

void readData(Runner runners[]); // Precondition: 'runners' array is allocated and contains enough space for NUM_RUNNERS runners.
// Postcondition: 'runners' array is populated with data read from the input file.

void calculateStats(Runner runners[]); // Precondition: 'runners' array is populated with valid data from readData().
// Postcondition: Total and average miles are calculated and stored in each runner's struct.

void displayResults(const Runner runners[]); // Precondition: 'runners' array is populated with valid data and total/average miles are calculated.
// Postcondition: Results are displayed to the console in a formatted table.


int main() {
    const int numRunners = NUM_RUNNERS;
    const int numDays = NUM_DAYS;
    Runner runners[numRunners];

    readData(runners);
    calculateStats(runners);
    displayResults(runners);

    return 0;
}

void readData(Runner runners[]) {
    std::ifstream inputFile("runners.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open input file 'runners.txt'. Make sure it exists in the correct location." << std::endl;
        exit(1);
    }

    for (int i = 0; i < NUM_RUNNERS; ++i) {
        inputFile >> runners[i].name;
        for (int j = 0; j < NUM_DAYS; ++j) {
            inputFile >> runners[i].dailyMiles[j];
        }
    }

    inputFile.close();
}

void calculateStats(Runner runners[]) {
    for (int i = 0; i < NUM_RUNNERS; ++i) {
        runners[i].totalMiles = 0;
        for (int j = 0; j < NUM_DAYS; ++j) {
            runners[i].totalMiles += runners[i].dailyMiles[j];
        }
        runners[i].averageMiles = runners[i].totalMiles / NUM_DAYS;
    }
}

void displayResults(const Runner runners[]) {
    std::cout << std::setw(15) << std::left << "Name";
    for (int i = 0; i < NUM_DAYS; ++i) {
        std::cout << std::setw(8) << std::right << "Day " << i + 1;
    }
    std::cout << std::setw(10) << std::right << "Total";
    std::cout << std::setw(12) << std::right << "Average" << std::endl;

    std::cout << std::setw(15) << std::left << "-------------";
    for (int i = 0; i < NUM_DAYS; ++i) {
        std::cout << std::setw(8) << std::right << "--------";
    }
    std::cout << std::setw(10) << std::right << "--------";
    std::cout << std::setw(12) << std::right << "----------" << std::endl;

    for (int i = 0; i < NUM_RUNNERS; ++i) {
        std::cout << std::setw(15) << std::left << runners[i].name;
        for (int j = 0; j < NUM_DAYS; ++j) {
            std::cout << std::setw(8) << std::right << runners[i].dailyMiles[j];
        }
        std::cout << std::setw(10) << std::right << std::fixed << std::setprecision(2) << runners[i].totalMiles;
        std::cout << std::setw(12) << std::right << std::fixed << std::setprecision(2) << runners[i].averageMiles << std::endl;
    }
}
