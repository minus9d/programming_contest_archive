#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int laps;
    cin >> laps; cin.ignore();
    int checkpointCount;
    cin >> checkpointCount; cin.ignore();
    for (int i = 0; i < checkpointCount; i++) {
        int checkpointX;
        int checkpointY;
        cin >> checkpointX >> checkpointY; cin.ignore();
    }

    // game loop
    while (1) {
        for (int i = 0; i < 2; i++) {
            int x;
            int y;
            int vx;
            int vy;
            int angle;
            int nextCheckPointId;
            cin >> x >> y >> vx >> vy >> angle >> nextCheckPointId; cin.ignore();
        }
        for (int i = 0; i < 2; i++) {
            int x;
            int y;
            int vx;
            int vy;
            int angle;
            int nextCheckPointId;
            cin >> x >> y >> vx >> vy >> angle >> nextCheckPointId; cin.ignore();
        }

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        cout << "8000 4500 100" << endl;
        cout << "8000 4500 100" << endl;
    }
}
