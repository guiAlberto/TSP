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

	int getX();
	int getY();
	int getId();
	
	bool equals(City);
};

