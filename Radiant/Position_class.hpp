class BulletPosition {
public:
	bool active = true;

	int x;
	int y;

	BulletPosition(int value1, int value2) : x(value1), y(value2) {};
};

class ShipPosition {
public:
	int x;
	int y;

	ShipPosition(int value1, int value2) : x(value1), y(value2) {};
}ship_position(0, 0);

class EnemyPosition {
public:
	int tex;
	int x;
	int y;

	EnemyPosition(int value1, int value2) : x(value1), y(value2), tex(0) {};
};

class EnemyBulletPosition {
public:
	bool active = true;

	int x;
	int y;

	EnemyBulletPosition(int value1, int value2) : x(value1), y(value2) {};
};

class PowerUpsPositions {
public:
	bool active;

	int type = 0;

	//1 - Heart
	//2 - Rapid Fire
	//3 - Shield
	//4 - Squadron

	int x;
	int y;

	PowerUpsPositions(int value1, int value2, int value3) : x(value1), y(value2), type(value3), active(true) {};
};