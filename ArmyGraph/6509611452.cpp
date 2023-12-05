#include <iostream>
#include <string>
using namespace std;


class ArmyAdvancement {
public:
	struct Position {
		int X;
		int Y;
		int height;
		bool seen;
		int shortestFromOrigin;
		Position(int x = 0, int y = 0, int height = 0, bool seen = false, int shortestFromOrigin = INFINITY) : X(x), Y(y), height(height), seen(seen), shortestFromOrigin(shortestFromOrigin) {}
	};

	ArmyAdvancement(int warZoneSize = 4, int targetNumber = 1, int knownHeightNumber = 0) : warZoneSize(warZoneSize), targetNumber(targetNumber), knownHeightNumber(knownHeightNumber) {
		warZones = new Position * *[warZoneSize];
		for (int i = 0; i < warZoneSize; i++) {
			warZones[i] = new Position * [warZoneSize];
			for (int j = 0; j < warZoneSize; j++) {
				warZones[i][j] = new Position(i, j, -1);
			}
		}
		targets = new Position * [targetNumber];
		setUp();
		advance(origin->X, origin->Y);
	}

	~ArmyAdvancement()
	{
		for (int i = 0; i < warZoneSize; i++) {
			for (int j = 0; j < warZoneSize; j++) {
				delete warZones[i][j];
			}
			delete[] warZones[i];
		}
		delete[] warZones;

		for (int i = 0; i < targetNumber; i++) {
			delete targets[i];
		}
		delete[] targets;

		delete origin;
		cout << "ArmyAdvancement destructed";
	}

	void setUp() {
		cout << "Enter war zone size, target number, known height number, origin position, and origin height (?,?,?,?,?,?)." << endl;
		origin = new Position;
		cin >> warZoneSize >> targetNumber >> knownHeightNumber >> origin->X >> origin->Y >> origin->height;
		cout << "Origin: " << origin->X << " " << origin->Y << endl;

		int X;
		int Y;
		int height;
		for (int i = 0; i < targetNumber; i++) {
			cin >> X;
			cin >> Y;
			cin >> height;
			targets[i] = new Position(X, Y, height);
		}

		for (int i = 0; i < knownHeightNumber; i++) {
			cin >> X;
			cin >> Y;
			X--;
			Y--;
			cin >> height;
			warZones[X][Y] = new Position(X, Y, height);
		}
	}

	void advance(int startX, int startY, int previousHeight = 0, int previousDay = 0) {
		if (warZones[startX][startY]->seen != true) {
			warZones[startX][startY]->seen = true;
			if (warZones[startX][startY]->height != -1) {
				if (previousHeight != 0) {
					int caculatedDay = previousDay + abs(previousHeight - warZones[startX][startY]->height) + 1;
					if (caculatedDay < warZones[startX][startY]->shortestFromOrigin) {
						warZones[startX][startY]->shortestFromOrigin = caculatedDay;
					}
				}
				else {
					warZones[startX][startY]->shortestFromOrigin = 0;
				}

				if ((startX - 1) >= 0) {
					advance(startX - 1, startY, warZones[startX][startY]->height, warZones[startX][startY]->shortestFromOrigin);
				}
				if ((startY - 1) >= 0) {
					advance(startX, startY - 1, warZones[startX][startY]->height, warZones[startX][startY]->shortestFromOrigin);
				}
				if ((startX + 1) < warZoneSize) {
					advance(startX + 1, startY, warZones[startX][startY]->height, warZones[startX][startY]->shortestFromOrigin);
				}
				if ((startY + 1) < warZoneSize) {
					advance(startX, startY + 1, warZones[startX][startY]->height, warZones[startX][startY]->shortestFromOrigin);
				}
			}
		}
	}

	int findFailed() {
		for (int i = 0; i < targetNumber; i++) {
			if (targets[i]->height == -1) {
				failedCount++;
			}
		}
		return failedCount;
	}

	Position* findFastest() {
		int fastestDay = INT16_MAX;
		Position* fastestTroops = NULL;
		for (int i = 0; i < targetNumber; i++) {
			if (targets[i]->shortestFromOrigin < fastestDay) {
				fastestDay = targets[i]->shortestFromOrigin;
				fastestTroops = targets[i];
			}
		}
		return fastestTroops;
	}

	Position* findSlowest() {
		int longestDay = INT16_MIN;
		Position* slowestTroops = NULL;
		for (int i = 0; i < targetNumber; i++) {
			if (targets[i]->shortestFromOrigin > longestDay) {
				longestDay = targets[i]->shortestFromOrigin;
				slowestTroops = targets[i];
			}
		}
		return slowestTroops;
	}

	void printDay() {
		for (int i = 0; i < warZoneSize; i++) {
			for (int j = 0; j < warZoneSize; j++) {
				cout << warZones[i][j]->shortestFromOrigin << " ";
			}
			cout << endl;
		}
	}

private:
	int warZoneSize;
	Position*** warZones;
	int targetNumber;
	Position** targets;
	int knownHeightNumber;
	Position* origin;
	int failedCount = 0;
};

int main(int argc, char** argv) {
	ArmyAdvancement* firstStrategy = new ArmyAdvancement();
	int failedCount = firstStrategy->findFailed();
	firstStrategy->printDay();
	if (failedCount > 0) {
		cout << failedCount << endl;
	}
	else {
		ArmyAdvancement::Position* slowestTroops = firstStrategy->findSlowest();
		cout << slowestTroops->shortestFromOrigin << endl;
		ArmyAdvancement::Position* fastestTroop = firstStrategy->findFastest();
		cout << fastestTroop->shortestFromOrigin << endl;
	}
}