#include <iostream>
#include <thread>
#include <chrono>
#include <conio.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;


// Pipe related struct
struct Pipe {
    int x;        // Horizontal position of the pipe
    int gapy;     // position of the very last tip of the above pipe
    int gapsize;  // Size of the gap
    bool passed;  // Flag to check if the pipe has been passed
};

//drawing the Screen
void drawscreen(int birdX, int birdY, const vector<Pipe>& pipes, int score) {
    const int screenheight = 20;
    const int screenwidth = 80;
    const char empty = ' ';
    const char pipeunit = '|';
    const char floorunit = '-';

    // Bird drawing
    const string bird[] = {
        "  __  ",
        " /   0\\.",
        "(___/",
        "       "
    };

    system("cls"); // Clear the screen

    for (int y = 0; y < screenheight; ++y) {
        for (int x = 0; x < screenwidth; ++x) {
            bool isPipe = false;

            for (const auto& pipe : pipes) {
                if (x == pipe.x && (y < pipe.gapy || y >= pipe.gapy + pipe.gapsize)) {
                    cout << pipeunit;
                    isPipe = true;
                    break;
                }
            }

            if (!isPipe) {
                if (x >= birdX && x < birdX + 8 && y >= birdY && y < birdY + 4) {
                    cout << bird[y - birdY][x - birdX];
                }
                else {
                    cout << empty;
                }
            }
        }
        cout << endl;
    }

    for (int x = 0; x < screenwidth; ++x) {
        cout << floorunit;
    }
    cout << endl;

    cout << "Score: " << score << endl;
}

// Displaying Main Menu
int showMenu() {
    int choice;
    do {
        system("cls");
        cout << "=== Welcome to the FlappyBird ===\n";
        cout << "1. Start the game\n";
        cout << "2. Exit\n";
        cout << "3. Show ranking list\n";
        cout << "Enter your choice: ";
        cin >> choice;
    } while (choice < 1 || choice > 3);
    return choice;
}

// sorting in desending order using bubble sort
void bubblesort(vector<pair<string, int>>& rankings) {
    int n = rankings.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (rankings[j].second < rankings[j + 1].second) {
                std::swap(rankings[j], rankings[j + 1]);
            }
        }
    }
}

// displaying ranking
void showrankinglist() {
    system("cls");
    ifstream file("rankings.txt");
    if (!file.is_open()) {
        cout << "No rankings available.\n";
    }
    else {
        vector<pair<string, int>> rankings;
        string line;
        while (std::getline(file, line)) {
            istringstream iss(line);
            string name;
            int score;
            if (iss >> name >> score) {
                rankings.emplace_back(name, score);
            }
        }
        file.close();

        // Sort the rankings
        bubblesort(rankings);

        cout << "=== Sorted Ranking List ===\n";
        for (size_t i = 0; i < rankings.size(); ++i) {
            cout << i + 1 << ". " << rankings[i].first << ": " << rankings[i].second << endl;
        }
    }
    cout << "Press any key to return to the menu...\n";
    _getch(); // Wait for a key press
}

void startgame() {
    string playerName;
    cout << "Enter your name: ";
    cin >> playerName;

    const int screenheight = 20;
    const int screenwidth = 80;
    const int floory = screenheight - 1;

    int birdX = 10;
    int birdY = 10;
    int verticalVelocity = 0;
    const int gravity = 1;

    vector<Pipe> pipes;
    const int pipeInterval = 15;
    const int pipeSpeed = 1;
    const int pipeGapSize = 8;
    const int initialPipeX = screenwidth;

    int score = 0;

    srand(time(0));

    while (true) {
        if (_kbhit()) {
            char key = _getch();
            if (key == ' ') {
                verticalVelocity = -3;
            }
        }

        verticalVelocity += gravity;
        birdY += verticalVelocity;

        // Check if the bird touches the ground or flies out of bounds
        if (birdY < 0 || birdY > floory - 0) {
            cout << "Game Over! Your score: " << score << endl;

            // Save the player's name and score to the rankings file
            ofstream file("rankings.txt", ios::app);
            if (file.is_open()) {
                file << playerName << " " << score << endl;
            }
            file.close();

            char retryChoice;
            cout << "Do you want to retry? (y/n): ";
            cin >> retryChoice;

            if (retryChoice == 'y' || retryChoice == 'Y') {
                birdY = 10; // Reset bird position
                verticalVelocity = 0; // Reset velocity
                pipes.clear(); // Clear the pipes
                score = 0; // Reset score
                continue; // Restart the game loop
            }

            cout << "Press any key to return to the menu...\n";
            _getch();
            return;
        }

        if (pipes.empty() || pipes.back().x < screenwidth - pipeInterval) {
            int gapY = std::rand() % (screenheight - pipeGapSize - 1);
            pipes.push_back({ initialPipeX, gapY, pipeGapSize, false });
        }

        for (auto& pipe : pipes) {
            pipe.x -= pipeSpeed;
            if (!pipe.passed && pipe.x < birdX) {
                pipe.passed = true;
                score++;
            }
        }

        if (!pipes.empty() && pipes.front().x < 0) {
            pipes.erase(pipes.begin());
        }

        drawscreen(birdX, birdY, pipes, score);

        for (const auto& pipe : pipes) {
            if (pipe.x == birdX && (birdY < pipe.gapy || birdY >= pipe.gapy + pipe.gapsize)) {
                cout << "Game Over! Your score: " << score << endl;

                // Save the player's name and score to the rankings file
                ofstream file("rankings.txt", std::ios::app);
                if (file.is_open()) {
                    file << playerName << " " << score << std::endl;
                }
                file.close();

                char retryChoice;
                cout << "Do you want to retry? (y/n): ";
                cin >> retryChoice;

                if (retryChoice == 'y' || retryChoice == 'Y') {
                    birdY = 10; // Reset bird position
                    verticalVelocity = 0; // Reset velocity
                    pipes.clear(); // Clear the pipes
                    score = 0; // Reset score
                    continue; // Restart the game loop
                }

                cout << "Press any key to return to the menu...\n";
                _getch();
                return;
            }
        }

        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

int main() {
    while (true) {
        int choice = showMenu();
        if (choice == 1) {
            startgame();
        }
        else if (choice == 2) {
            cout << "Goodbye!\n";
            break;
        }
        else if (choice == 3) {
            showrankinglist();
        }
    }
    return 0;
}
