#include <iostream>
#include <fstream>
#include <vector>
#include "Random.h"

void printUsage();

void parseArgs(int argc, char * argv[]);

std::vector<std::string> readFromFile();

std::vector<int> run(std::vector<std::string> vector1);

std::string in = "";

int numbilets = -1;
int parameter = -1;

int main(int argc, char * argv[]) {
    parseArgs(argc, argv);

    std::vector<std::string> students = readFromFile();

    std::vector<int> tickets = run(students);

    for (int i = 0; i < students.size(); i++) {
        std::cout << students[i] << " " << tickets[i] << "\n";
    }
}

std::vector<int> run(std::vector<std::string> students) {
    RandomState randomState(parameter);
    std::vector<int> tickets;
    for (auto name : students) {
        tickets.push_back(randomState.randint(numbilets, name));
    }
    return tickets;
}

std::vector<std::string> readFromFile() {
    std::ifstream infile;
    infile.open(in);

    std::vector<std::string> students;

    if (infile.is_open() ) {
        std::string tp;
        while(getline(infile, tp)){
            students.push_back(tp);
        }
    }
    return students;
}

void parseArgs(int argc, char * argv[]) {
    if (argc != 7) {
        printUsage();
        exit(1);
    }

    for (int i = 1; i <= 3; i++) {
        if (strcmp(argv[2 * i - 1], "--file") == 0) {
            in = argv[2 * i];
        } else if (strcmp(argv[2 * i - 1], "--numbilets") == 0) {
            numbilets = std::stoi(argv[2 * i]);
        } else if (strcmp(argv[2 * i - 1], "--parameter") == 0) {
            parameter = std::stoi(argv[2 * i]);
        } else {
            printUsage();
            exit(1);
        }
    }

    if (in.empty() || numbilets == -1 || parameter == -1) {
        printUsage();
        exit(1);
    }
}

void printUsage() {
    std::cout << "expected format: --file in.txt --numbilets 20 --parameter 42 \n";
}
