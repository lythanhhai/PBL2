#pragma once
#include "DBHelper.h"
#include "Seat.h"
//#include <vector>
class Room
{
private:
	int room_no;
    string room_id;
	int SoGheTrong;
	string time;
	vector<Seat> seat;
	int status;
public:
	Room();
	Room(string,int,string,int);
	~Room();
	void showroom();
	void setSeat();
//	vector<Seat> getSeat();
	string getId();
	int getSoPhong();
	string getTime();
	void setSoGheTrong(int);
	int getSoGheTrong();
	void setStatus(int); //throw -1
	int getStatus();
	Seat& getSeatAt(int, int); //co throw
	Seat& getSeat(int); // throw int
	friend ostream& operator<<(ostream&, const Room&);
};

