#include <iostream>
#include <thread>
#include <chrono>
#include <ncurses.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <unistd.h>

using namespace std;

// Struct to store pipe properties
struct Pipe {
    int x;        // Horizontal position of the pipe
    int gapY;     // Y position of the gap's top
    int gapSize;  // Size of the gap
    bool passed;  // Flag to check if the pipe has been passed
};

// Function to draw the screen
void drawScreen(int BirdX, int BirdY, const vector<Pipe>& pipes, int score) {
    const int screenHeight = 20;
    const int screenWidth = 80;
    const char empty = ' ';
    const char pipeChar = '|';
    const char floorChar = '-';

    // Bird drawing
    const string Bird[] = {
        "  ____  ",
        " /   0\\.",
        "(_____/",
        "              "
    };

    system("clear"); // Clear the screen

    for (int y = 0; y < screenHeight; ++y) {
        for (int x = 0; x < screenWidth; ++x) {
            bool isPipe = false;

            for (const auto& pipe : pipes) {
                if (x == pipe.x && (y < pipe.gapY || y >= pipe.gapY + pipe.gapSize)) {
                    cout << pipeChar;
                    isPipe = true;
                    break;
                }
            }

            if (!isPipe) {
                if (x >= BirdX && x < BirdX + 8 && y >= BirdY && y < BirdY + 4) {
                    cout << Bird[y - BirdY][x - BirdX];
                }
                else {
                    cout << empty;
                }
            }
        }
        cout << endl;
    }

    for (int x = 0; x < screenWidth; ++x) {
        cout << floorChar;
    }
    cout << endl;

    cout << "Score: " << score << endl;
}

int kbhit (void)
{
  struct timeval tv;
  fd_set rdfs;

  tv.tv_sec = 0;
  tv.tv_usec = 0;

  FD_ZERO(&rdfs);
  FD_SET (STDIN_FILENO, &rdfs);

  select(STDIN_FILENO+1, &rdfs, NULL, NULL, &tv);
  return FD_ISSET(STDIN_FILENO, &rdfs);

}

// Function to show the menu
int showMenu() {
    int choice;
    do {
        system("clear");
        cout << "=== Welcome to the FlappyBird ===\n";
        cout << "1. Start the game\n";
        cout << "2. Exit\n";
        cout << "3. Show ranking list\n";
        cout << "Enter your choice: ";
        cin >> choice;
    } while (choice < 1 || choice > 3);
    return choice;
}

// Bubble sort function to sort scores in descending order
void bubbleSort(vector<pair<string, int>>& rankings) {
    long n = rankings.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (rankings[j].second < rankings[j + 1].second) {
                swap(rankings[j], rankings[j + 1]);
            }
        }
    }
}

// Function to show the ranking list
void showRankingList() {
    system("clear");
    ifstream file("rankings.rtf");
    if (!file.is_open()) {
        cout << "No rankings available.\n";
    }
    else {
        vector<pair<string, int>> rankings;
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string name;
            int score;
            if (iss >> name >> score) {
                rankings.emplace_back(name, score);
            }
        }
        file.close();

        // Sort the rankings
        bubbleSort(rankings);

        cout << "=== Sorted Ranking List ===\n";
        for (size_t i = 0; i < rankings.size(); ++i) {
            cout << i + 1 << ". " << rankings[i].first << ": " << rankings[i].second << endl;
        }
    }
    cout << "Press any key to return to the menu...\n";
    getch(); // Wait for a key press
}

// Main game function
void startGame() {
    string playerName;
    cout << "Enter your name: ";
    cin >> playerName;

    const int screenHeight = 20;
    const int screenWidth = 80;
    const int floorY = screenHeight - 1;

    int BirdX = 10;
    int BirdY = 10;
    int verticalVelocity = 0;
    const int gravity = 1;

    vector<Pipe> pipes;
    const int pipeInterval = 15;
    const int pipeSpeed = 1;
    const int pipeGapSize = 9;
    const int initialPipeX = screenWidth;

    int score = 0;

    srand(time(0));

    while (true) {
        if (kbhit()) {
            char key = getch();
            if (key == ' ') {
                verticalVelocity = -3;
            }
        }

        verticalVelocity += gravity;
        BirdY += verticalVelocity;

        if (BirdY < 0) BirdY = 0;
        if (BirdY > floorY - 4) BirdY = floorY - 4;

        if (pipes.empty() || pipes.back().x < screenWidth - pipeInterval) {
            int gapY = rand() % (screenHeight - pipeGapSize - 1);
            pipes.push_back({ initialPipeX, gapY, pipeGapSize, false });
        }

        for (auto& pipe : pipes) {
            pipe.x -= pipeSpeed;
            if (!pipe.passed && pipe.x < BirdX) {
                pipe.passed = true;
                score++;
            }
        }

        if (!pipes.empty() && pipes.front().x < 0) {
            pipes.erase(pipes.begin());
        }

        drawScreen(BirdX, BirdY, pipes, score);

        for (const auto& pipe : pipes) {
            if (pipe.x == BirdX && (BirdY < pipe.gapY || BirdY >= pipe.gapY + pipe.gapSize)) {
                cout << "Game Over! Your score: " << score << endl;

                // Save the player's name and score to the rankings file
                ofstream file("rankings.rtf", ios::app);
                if (file.is_open()) {
                    file << playerName << " " << score << endl;
                }
                file.close();

                cout << "Press any key to return to the menu...\n";
                getch();
                return;
            }
        }

        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

int main(void) {
    while (true) {
        int choice = showMenu();
        if (choice == 1) {
            startGame();
        }
        else if (choice == 2) {
            cout << "Goodbye!\n";
            break;
        }
        else if (choice == 3) {
            showRankingList();
        }
    }
    return 0;
}
