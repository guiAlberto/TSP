#pragma once
class City
{
private:
	int x;
	int y;
public:
	City(int, int);
	~City();

	int getX() const {
		return x;
	}

	int getY() const {
		return y;
	}
};

