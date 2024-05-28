#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <iomanip>

using namespace std;

vector<string> map{
    "##################################################",
    "#E                                               #",
    "#                                                #",
    "###############################################  #",
    "#       #   #   #   #                         #  #",
    "#     #   #   #   #   #                       #  #",
    "#  #####################  ##################  #  #",
    "#  #                      #                #  #  #",
    "#  #  #####################  ###############  #  #",
    "#  #  #                   #                #  #  #",
    "#  #  #  ################################  #  #  #",
    "#  #  #                   #                   #  #",
    "#  #  ##################  #  ###############  #  #",
    "#  #        #             #        #       #  #  #",
    "#  #  #     #      #      #        #       #  #  #",
    "#  #  #     #      #      #        #       #  #  #",
    "#  #  #            #                       #  #  #",
    "#  #################  #########################  #",
    "#  #               #                             #",
    "#  #                                             #",
    "#  ###############################################",
    "#                                                #",
    "#                                               S#",
    "##################################################"
};

vector<vector<int>> paths{ {} };

vector<int> getChar(char c) {
    for (int y = 0; y < map.size(); y++) {
        for (int x = 0; x < map[y].size(); x++) {
            if (map[y][x] == c) {
                return { y, x };
            }
        }
    }
    return { {} };
}

void printMap();

chrono::steady_clock::time_point start;
vector<double> times;
int loopCount{ 0 };

int main() {
start:
    vector<int> position = getChar('S');
    start = chrono::steady_clock::now();
beginning:
    paths.clear();
    paths.resize(map.size(), {});
    for (int y = 0; y < map.size(); y++) {
        paths[y].resize(map[y].size(), -1);
        for (int x = 0; x < map[y].size(); x++) {
            if (map[y].at(x) == '#') {
                paths[y][x] = -1;
            }
            else if (map[y].at(x) == 'E') {
                paths[y][x] = 1;
            }
            else {
                paths[y][x] = 0;
            }
        }
    }

    // Set distances
    //Check for 0s

zero_check:
    bool hasZero{ false };
    for (int y = 0; y < paths.size(); y++) {
        for (int x = 0; x < paths[y].size(); x++) {
            if (paths[y][x] == 0) {
                hasZero = true;
                break;
            }
            else {
                hasZero = false;
            }
        }
        if (hasZero) {
            break;
        }
    }

    bool foundGoal{ false };

    //Un needed calculations ignored if there are no zeros left
    if (hasZero) {
        for (int y = 0; y < paths.size(); y++) {
            for (int x = 0; x < paths[y].size(); x++) {
                if (paths[y][x] == 0) {
                    // Selected piece is not wall and not filled yet, check neighbors
                    int up = paths[y - 1][x];
                    int down = paths[y + 1][x];
                    int left = paths[y][x - 1];
                    int right = paths[y][x + 1];
                    // Lowest neighbor (used to set self later)
                    int lowestNeighbor{ -1 };
                    // Check neighbors to see what lowest is
                    if (up > 0) {
                        lowestNeighbor = up;
                    }
                    if (down > 0 && (lowestNeighbor == -1 || down < lowestNeighbor)) {
                        lowestNeighbor = down;
                    }
                    if (left > 0 && (lowestNeighbor == -1 || left < lowestNeighbor)) {
                        lowestNeighbor = left;
                    }
                    if (right > 0 && (lowestNeighbor == -1 || right < lowestNeighbor)) {
                        lowestNeighbor = right;
                    }

                    // No neighbors == no paths
                    if (lowestNeighbor == -1) {
                        // No paths
                    }
                    else {
                        if (vector<int>{y, x} == position && ((paths[y - 1][x] != 0 && paths[y - 1][x] != -1) || (paths[y + 1][x] != 0 && paths[y + 1][x] != -1) || (paths[y][x - 1] != 0 && paths[y][x - 1] != -1) || (paths[y][x + 1] != 0 && paths[y][x + 1] != -1))) {
                            // Found the goal, no need to keep looking(SHOULD always be shortest path)
                            foundGoal = true;
                            break;
                        }
                    }

                    // Set one higher than lowest neighbor
                    paths[y][x] = lowestNeighbor + 1;
                }
            }
            if (foundGoal) {
                break;
            }
        }

        if (!foundGoal) {
            goto zero_check;
        }
    }

    // 0s all gone, move out
    int up = paths[position[0] - 1][position[1]];
    int down = paths[position[0] + 1][position[1]];
    int left = paths[position[0]][position[1] - 1];
    int right = paths[position[0]][position[1] + 1];
    // Lowest neighbor (used to set self later)
    int lowestNeighbor{ -1 };
    char direc = ' ';
    // Check neighbors to see what lowest is
    if (up > 0) {
        lowestNeighbor = up;
        direc = 'u';
    }
    if (down > 0 && (lowestNeighbor == -1 || down < lowestNeighbor)) {
        lowestNeighbor = down;
        direc = 'd';
    }
    if (left > 0 && (lowestNeighbor == -1 || left < lowestNeighbor)) {
        lowestNeighbor = left;
        direc = 'l';
    }
    if (right > 0 && (lowestNeighbor == -1 || right < lowestNeighbor)) {
        lowestNeighbor = right;
        direc = 'r';
    }

    if (direc == 'u') {
        position[0]--;
    }
    else if (direc == 'd') {
        position[0]++;
    }
    else if (direc == 'l') {
        position[1]--;
    }
    else if (direc == 'r') {
        position[1]++;
    }

    if (position == getChar('E')) {
        printMap();
        loopCount++;
        if (loopCount < 100) {
            cout << "Done " << loopCount << endl;
            goto start;
        }
        else {
            double total{ 0 };
            for (int i = 0; i < times.size(); i++) {
                total += times[i];
            }
            cout << "Average time: " << total / times.size() << " milliseconds";
        }
    }
    else {
        map[position[0]][position[1]] = '*';
        goto beginning;
    }
}

void printMap() {
    auto end = chrono::steady_clock::now();
    times.push_back(chrono::duration_cast<chrono::milliseconds>(end - start).count());

    /*
    cout << "Printing map" << endl << endl;
    for (int y = 0; y < map.size(); y++) {
        cout << map[y] << endl;
    }
    cout << endl;
    for (int i = 0; i < paths.size(); i++) {
        for (int ii = 0; ii < paths[i].size(); ii++) {
            cout << setw(3) << setfill(' ') << paths[i][ii] << " ";
        }
        cout << endl << endl;
    }
    cout << endl << endl;

    cout << "Time taken: " << duration.count() << " milliseconds" << endl;
    */

    //string s{};
    //cin >> s;
}
