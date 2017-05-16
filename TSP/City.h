#pragma once
class City
{
private:
	int x;
	int y;
	int id;

public:
	City(int, int, int);
	~City();

	int getX() {
		return this->x;
	}

	int getY() {
		return this->y;
	}

	int getId() {
		return this->id;
	}
};

