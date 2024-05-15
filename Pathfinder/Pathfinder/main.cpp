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
}

void printMap();

chrono::steady_clock::time_point start;

int main() {
    vector<int> position = getChar('S');
    start = chrono::steady_clock::now();
beginning:
    paths = { {} };
    for (int y = 0; y < map.size(); y++) {
        for (int x = 0; x < map[y].size(); x++) {
            if (map[y].at(x) == '#') {
                paths[y].push_back(-1);
            }
            else if (map[y].at(x) == 'E') {
                paths[y].push_back(1);
            }
            else {
                paths[y].push_back(0);
            }
        }
        paths.push_back({});
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

                    // Set one higher than lowest neighbor
                    paths[y][x] = lowestNeighbor + 1;
                }
            }
        }
        goto zero_check;
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
    else {
        // OH NO
    }

    if (position == getChar('E')) {
        printMap();
    }

    map[position[0]][position[1]] = '*';

    goto beginning;
}

/*
int main() {
    cout << "Start" << endl;
    vector<int> pos0 = getChar('0');
    vector<int> pos1 = getChar('1');
    cout << "Making paths" << endl;
    for (int y = 0; y < map.size(); y++) {
        for (int x = 0; x < map[y].size(); x++) {
            if (map[y][x] == '#') {
                paths[y].push_back(-1);
            }
            else if (pos0 == vector<int>{y, x}) {
                paths[y].push_back(1);
            }
            else {
                paths[y].push_back(0);
            }
        }
        paths.push_back({});
    }
    cout << "Paths made" << endl;
    int layer{ 2 };
    int count{ 0 };
    while (true) {

        cout << "Checking neighbors 1" << endl;
        for (int i = 0; i < validityChecker; i++) {
            for (int y = 0; y < paths.size(); y++) {
                for (int x = 0; x < paths[y].size(); x++) {
                    cout << "Checking neighbors 2\t" << count << endl;
                    count++;
                    if (paths[y][x] != -1) {
                        cout << "Self not negative" << endl;
                        int up = paths[y - 1][x];
                        int down = paths[y + 1][x];
                        int left = paths[y][x - 1];
                        int right = paths[y][x + 1];
                        int lowestNeighbor{-1};
                        if (up != -1 && up != 0) {
                            lowestNeighbor = up;
                        }
                        if (down != -1 && down != 0) {
                            if (lowestNeighbor == -1) {
                                lowestNeighbor = down;
                            }
                            else if (down < lowestNeighbor) {
                                lowestNeighbor = down;
                            }
                        }
                        if (left != -1 && left != 0) {
                            if (lowestNeighbor == -1) {
                                lowestNeighbor = left;
                            }
                            if (left < lowestNeighbor) {
                                lowestNeighbor = left;
                            }
                        }
                        if (right != -1 && right != 0) {
                            if (lowestNeighbor == -1) {
                                lowestNeighbor = right;
                            }
                            if (right < lowestNeighbor) {
                                lowestNeighbor = right;
                            }
                        }
                        if (lowestNeighbor != -1) {
                            paths[y][x] = lowestNeighbor + 1;
                        }
                        cout << "Neighbors checked! Low num: " << lowestNeighbor << endl;
                    }
                }
            }
        }
        int y = pos1[0];
        int x = pos1[1];
        int up = paths[y - 1][x];
        int down = paths[y + 1][x];
        int left = paths[y][x - 1];
        int right = paths[y][x + 1];
        int lowestNeighbor{-1};
        char lowNeighDir{' '};
        cout << "Moving player" << endl;
        if (up != -1 && up != 0) {
            lowestNeighbor = up;
            lowNeighDir = 'u';
        }
        if (down != -1 && down != 0) {
            if (lowestNeighbor == -1) {
                lowestNeighbor = down;
                lowNeighDir = 'd';
            }
            if (down < lowestNeighbor) {
                lowestNeighbor = down;
                lowNeighDir = 'd';
            }
        }
        if (left != -1 && left != 0) {
            if (lowestNeighbor == -1) {
                lowestNeighbor = left;
                lowNeighDir = 'l';
            }
            if (left < lowestNeighbor) {
                lowestNeighbor = left;
                lowNeighDir = 'l';
            }
        }
        if (right != -1 && right != 0) {
            if (lowestNeighbor == -1) {
                lowestNeighbor = right;
                lowNeighDir = 'r';
            }
            if (right < lowestNeighbor) {
                lowestNeighbor = right;
                lowNeighDir = 'r';
            }
        }

        if (lowNeighDir != ' ') {
            if (lowNeighDir == 'u') {
                pos1 = { y - 1, x };
            }
            else if (lowNeighDir == 'd') {
                pos1 = { y + 1, x };
            }
            else if (lowNeighDir == 'l') {
                pos1 = { y, x - 1 };
            }
            else {
                pos1 = { y, x + 1 };
            }
        }
        else {
            cout << "OH NO OH NO OH NO OH NO OH NO OH NO OH NO OH NO OH NO" << endl;
            cout << lowestNeighbor << endl;
        }

        if (pos1 == pos0) {
            break;
        }

        map[pos1[0]][pos1[1]] = '*';
        cout << "Player moved" << endl;
        printMap();
    }

    printMap();
}
*/

void printMap() {
    auto end = chrono::steady_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
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

    string s{};
    cin >> s;
}