#pragma once
#include <iostream>
using namespace std;
class Seat
{
private:
	int seat_id;
	string room_id;
	int seat_no;
	int row;
	int status;
//	int col;
public:
    Seat();
	Seat(int,string,int,int,int);
	~Seat();
	void setRow(const int&);
	void setStatus(const int&);
	int getStatus();
	int getRow();
	void setSeat(const int&);
	int getseat();
	int getId();
	void print();
	friend ostream& operator<<(ostream&, const Seat&);
};

