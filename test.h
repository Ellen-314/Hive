#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

#include <iostream>
#include <stack>
#include <fstream>
#include <stdexcept>
#include <string>
#include "Board.h"
#include "Insect.h"
#include "ant.h"
#include "queenbee.h"
#include "Controleur.h"

// Helper function to serialize a BoardSpot to a file
void serializeBoardSpot(const BoardSpot& spot, std::ofstream& outFile) {
    // Write coordinates (x, y)
    auto coordinates = spot.getCoordinates();
    outFile << coordinates.first << " " << coordinates.second << " ";

    // Write insect type if present
    if (spot.hasInsect()) {
        Insect* insect = spot.getInsect();
        outFile << insect->getType() << " " << insect->getColor() << "\n"; // Save insect type and color
    } else {
        outFile << "none\n";  // Indicate no insect present
    }
}

// Helper function to deserialize a BoardSpot from a file
BoardSpot deserializeBoardSpot(std::ifstream& inFile) {
    int x, y;
    inFile >> x >> y;  // Read coordinates
    std::cout<<"x="<<x<<"\n";
    std::cout<<"y="<<y<<"\n";
    BoardSpot spot(x, y);

    std::string insectType;
    inFile >> insectType;  // Read insect type

    if (insectType != "none") {
        int color;
        inFile >> color;  // Read insect color

        // You would need to properly reconstruct the insect based on its type and color
        Insect* insect = nullptr;
        if (insectType == "ant") {
            insect = new Ant(); // Example, you'd need to handle creating the correct insect type
        } else if (insectType == "queenbee") {
            std::cout<<"inside queenbee\n";
            insect = new QueenBee();  // Similarly for QueenBee or other types
        }

        spot.setInsect(insect);
    }

    return spot;
}

// Function to save a stack of Boards to a file
void saveStackToFile(std::stack<Board>& boardStack, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile) {
        throw std::runtime_error("Failed to open file for writing.");
    }

    while (!boardStack.empty()) {
        Board board = boardStack.top();
        boardStack.pop();

        // Save the board
        outFile << board.getNb() << "\n";  // Write the number of spots
        for (size_t i = 0; i < board.getNb(); ++i) {
            BoardSpot spot = board.getSpotIndex(i);
            serializeBoardSpot(spot, outFile);  // Serialize each spot
        }
    }

    outFile.close();
}

// Function to load a stack of Boards from a file
std::stack<Board> loadStackFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        throw std::runtime_error("Failed to open file for reading.");
    }

    std::stack<Board> boardStack;
    while (inFile.peek() != EOF) {  // Loop until the end of the file
        size_t nb;
        inFile >> nb;  // Read the number of spots for this board

        Board board;
        for (size_t i = 0; i < nb; ++i) {
            BoardSpot spot = deserializeBoardSpot(inFile);  // Deserialize each spot
            board.addSpot(spot.getCoordinates().first, spot.getCoordinates().second);  // Add to the board
            if (spot.hasInsect()) {
                board.addInsectToSpot(spot.getCoordinates().first, spot.getCoordinates().second, spot.getInsect());
            }
        }

        boardStack.push(board);  // Push the board to the stack
    }

    inFile.close();
    return boardStack;
}

int test() {
    // Create a stack of boards
    std::stack<Board> boardStack;

    // Add a sample board to the stack (Example, adjust this as needed)
    Board board1;
    board1.addSpot(0, 0);
    board1.addSpot(1, 0);
    board1.addSpot(0, 1);
    board1.addSpot(1, 1);

    Board board2;
    board2.addSpot(0, 0);
    board2.addSpot(2, 0);
    board2.addSpot(0, 2);
    board2.addSpot(2, 2);

    QueenBee* insect = new QueenBee();
    board1.addInsectToSpot(0,1,insect);

    Ant* insect2 = new Ant();
    board2.addInsectToSpot(2,2,insect2);
    // You'd also add insects to these spots as necessary
    boardStack.push(board1);
    boardStack.push(board2);
    std::cout<<"Board 1 avant\:n";
    board1.print(std::cout);
    std::cout<<"Board 2 avant\:n";
    board2.print(std::cout);

    // Save the stack of boards to a file
    try {
        saveStackToFile(boardStack, "boards.dat");
    } catch (const std::exception& e) {
        std::cerr << "Error saving boards: " << e.what() << std::endl;
    }

    // Load the stack of boards back from the file
    try {
        std::stack<Board> loadedBoardStack = loadStackFromFile("boards.dat");
        std::cout<<"Board 1 apres\:n";
        loadedBoardStack.pop();
        loadedBoardStack.top().print(std::cout);
        std::cout<<"Board 2 apres\:n";
        loadedBoardStack.pop();
        loadedBoardStack.top().print(std::cout);
        std::cout << "Boards loaded successfully!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error loading boards: " << e.what() << std::endl;
    }

    return 0;
}


#endif // TEST_H_INCLUDED
