#include "Room.h"

Room::Room()
{
	this->room_no = 0;
	this->SoGheTrong = 0;
	this->status = 0;
	this->time = "";
    this->room_id = "";
}

Room::Room(string room_id, int room_no, string time, int status)
	:room_no(room_no), room_id(room_id), time(time), status(status)
{
	this->SoGheTrong = 0;
}

Room::~Room()
{

}

void Room::showroom()
{
	int row = 0;
	char s[4] = { 'A','B','C','D' };
	cout << "Phong so: " << this->getSoPhong() << endl;
	cout << "---------------------------------- MAN HINH ------------------------------------" << endl << endl;
	for (int i = 0; i < this->seat.size(); i++)
	{
		if (i == 10 || i == 20 || i == 30)
		{
			cout << endl;
			row++;
		}
		cout <<s[row]<<this->seat[i].getseat() << " -> " << this->seat[i].getStatus() << " || ";
	}
	cout << endl;
}

void Room::setSeat()
{
	DBHelper db;
	vector<Seat> seatl;
	db.init();
	seatl = db.SelectSeat(this->getId());
	db.close();
	for(int i = 0 ; i < seatl.size(); i++)
	{
		(this->seat).push_back(seatl.at(i));
		if (seatl[i].getStatus() == 0)
		{
			this->SoGheTrong++;
		}
	}
}

//vector<Seat> Room::getSeat()
//{
//	for(int i = 0 ; i < (this->seat).size() ; i++)
//	{
//		cout << (this->seat).at(i) << endl;
//	}
//	return this->seat;
//}

string Room::getId()
{
	return this->room_id;
}

int Room::getSoPhong()
{
	return this->room_no;
}

string Room::getTime()
{
	return this->time;
}

void Room::setSoGheTrong(int n)
{
	this->SoGheTrong = n;
}

int Room::getSoGheTrong()
{
	return this->SoGheTrong;
}

void Room::setStatus(int s)
{
	if (s != 0 && s != 1) throw - 1;
	this->status = s;
}

int Room::getStatus()
{
	return this->status;
}

Seat& Room::getSeatAt(int seat_no, int row)
{
	for (int i = 0; i < this->seat.size(); i++)
	{
		if (this->seat[i].getRow() == row && this->seat[i].getseat() == seat_no)
		{
			return this->seat[i];
		}
	}
	throw string("Khong tim thay.\n");
}

Seat& Room::getSeat(int id)
{
	int n = this->seat.size();
	for (int i = 0; i < n; i++)
	{
		if (this->seat[i].getId() == id) return this->seat[i];
	}
	throw - 1;
}

ostream& operator<<(ostream& o, const Room& r)
{
	o << "Ma phong: " << r.room_id << endl
		<< "So phong: " << r.room_no << " So ghe trong: " << r.SoGheTrong << endl
		<< "-----------------------------------------------------------" << endl;
	return o;
}
