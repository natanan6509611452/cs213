/*
	Name: Natanan Phopradit
	Student ID: 6509611452
*/

#include <iostream>
#include <string>
#include <queue>
#include <functional>
#include <cmath>

using namespace std;

class ArmyAdvancement {
public:
	struct Position {
		int X;
		int Y;
		float height;
		bool seen;
		float shortestFromOrigin;
		Position(int x = 0, int y = 0, float height = 0, bool seen = false, float shortestFromOrigin = INFINITY) : X(x), Y(y), height(height), seen(seen), shortestFromOrigin(shortestFromOrigin) {}
		
		bool operator>(Position a) const{
			return shortestFromOrigin > a.shortestFromOrigin;
		}

		bool operator==(const Position& other) const
		{
			return X == other.X && Y == other.Y && height == other.height && seen == other.seen && shortestFromOrigin == other.shortestFromOrigin;
		}
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
		priority_queue<Position, std::vector<Position>, std::greater<Position>>* warZoneQueue = new priority_queue<Position, std::vector<Position>, std::greater<Position>>;
		warZoneQueue->push(*warZones[origin->X][origin->Y]);
		advance(warZoneQueue);
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
	}

	void setUp() {
		origin = new Position;
		cin >> warZoneSize >> targetNumber >> knownHeightNumber >> origin->X >> origin->Y >> origin->height;
		(origin->X)--;
		(origin->Y)--;

		int X;
		int Y;
		float height;

		for (int i = 0; i < targetNumber; i++) {
			cin >> X;
			cin >> Y;
			X--;
			Y--;
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

		origin->shortestFromOrigin = 0;
		warZones[origin->X][origin->Y] = origin;
	}

	void advance(priority_queue<Position, std::vector<Position>, std::greater<Position>>* warZoneQueue) {
		if (!warZoneQueue->empty()) {
			Position currentPosition = warZoneQueue->top();
			warZoneQueue->pop();
			if (currentPosition.seen != true) {
				warZones[currentPosition.X][currentPosition.Y]->seen = true;
				Position* leftPosition;
				Position* topPosition;
				Position* rightPosition;
				Position* bottomPosition;

				if ((currentPosition.X - 1) >= 0) {
					topPosition = warZones[currentPosition.X - 1][currentPosition.Y];
					if (topPosition->height != -1 && topPosition->shortestFromOrigin != 0) {
						topPosition->shortestFromOrigin = min(currentPosition.shortestFromOrigin + abs(currentPosition.height - topPosition->height) + 1, topPosition->shortestFromOrigin);
						warZoneQueue->push(*topPosition);
					}
				}
				if ((currentPosition.Y - 1) >= 0) {
					leftPosition = warZones[currentPosition.X][currentPosition.Y - 1];
					if (leftPosition->height != -1 && leftPosition->shortestFromOrigin != 0) {
						leftPosition->shortestFromOrigin = min(currentPosition.shortestFromOrigin + abs(currentPosition.height - leftPosition->height) + 1, leftPosition->shortestFromOrigin);
						warZoneQueue->push(*leftPosition);
					}
				}
				if ((currentPosition.X + 1) < warZoneSize) {
					bottomPosition = warZones[currentPosition.X + 1][currentPosition.Y];
					if (bottomPosition->height != -1 && bottomPosition->shortestFromOrigin != 0) {
						bottomPosition->shortestFromOrigin = min(currentPosition.shortestFromOrigin + abs(currentPosition.height - bottomPosition->height) + 1, bottomPosition->shortestFromOrigin);
						warZoneQueue->push(*bottomPosition);
					}
				}
				if ((currentPosition.Y + 1) < warZoneSize) {
					rightPosition = warZones[currentPosition.X][currentPosition.Y + 1];
					if (rightPosition->height != -1 && rightPosition->shortestFromOrigin != 0) {
						rightPosition->shortestFromOrigin = min(currentPosition.shortestFromOrigin + abs(currentPosition.height - rightPosition->height) + 1, rightPosition->shortestFromOrigin);
						warZoneQueue->push(*rightPosition);
					}
				}
			}
			advance(warZoneQueue);
		}
		for (int i = 0; i < targetNumber; i++) {
			targets[i]->shortestFromOrigin = warZones[targets[i]->X][targets[i]->Y]->shortestFromOrigin;
		}
	}

	int findFailed() {
		for (int i = 0; i < targetNumber; i++) {
			if (targets[i]->shortestFromOrigin >= INFINITY) {
				failedCount++;
			}
		}
		return failedCount;
	}

	Position* findFastest() {
		float fastestDay = INFINITY;
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
		float longestDay = -INFINITY;
		Position* slowestTroops = NULL;
		for (int i = 0; i < targetNumber; i++) {
			if (targets[i]->shortestFromOrigin > longestDay && targets[i]->shortestFromOrigin != INFINITY) {
				longestDay = targets[i]->shortestFromOrigin;
				slowestTroops = targets[i];
			}
		}
		return slowestTroops;
	}

	void printDay() {
		cout << "========== " << "Day(s) Required From Base" << " ==========" << endl;
		for (int i = 0; i < warZoneSize; i++) {
			for (int j = 0; j < warZoneSize; j++) {
				cout << warZones[i][j]->shortestFromOrigin << " ";
			}
			cout << endl;
		}
	}

	void printHeightMap() {
		cout << "========== " << "War Zone Heights" << " ==========" << endl;
		for (int i = 0; i < warZoneSize; i++) {
			for (int j = 0; j < warZoneSize; j++) {
				cout << warZones[i][j]->height << " ";
			}
			cout << endl;
		}
	}

	void printTargets() {
		cout << "========== " << "Targets" << " ==========" << endl;
		for (int i = 0; i < targetNumber; i++) {
			cout << "Targets at (" << targets[i]->X << ", " << targets[i]->Y << ") Height: " << targets[i]->height << endl;
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
	ArmyAdvancement* strategy = new ArmyAdvancement();
	int failedCount = strategy->findFailed();

	if (failedCount > 0) {
		cout << failedCount << endl;
	}
	else {
		ArmyAdvancement::Position* slowestTroops = strategy->findSlowest();
		cout << slowestTroops->shortestFromOrigin << endl;
		ArmyAdvancement::Position* fastestTroop = strategy->findFastest();
		cout << fastestTroop->shortestFromOrigin << endl;
	}
}