#include "Seat.h"

Seat::Seat()
{
	this->room_id = "" ;
	this->row = 0 ;
	this->seat_no = 0;
	this->status = 0;
//	this->col = 0;
}

Seat::Seat(int id,string room, int row, int seat, int status)
	:seat_id(id),room_id(room), row(row), seat_no(seat), status(status)
{

}

Seat::~Seat()
{

}


void Seat::setSeat(const int& seat)
{
	this->seat_no = seat;
}

int Seat::getRow()
{
	return this->row;
}

int Seat::getseat()
{
	return this->seat_no;
}

int Seat::getId()
{
	return this->seat_id;
}

int Seat::getStatus()
{
	return this->status;
}

//int Seat::getCol()
//{
//	return this->col;
//}

//void Seat::setCol(const int& col)
//{
//	this->col = col;
//}

void Seat::setRow(const int& row)
{
	this->row = row;
}

void Seat::setStatus(const int& status)
{
	this->status = status;
}


ostream& operator<<(ostream& o, const Seat& s)
{
	o << " Row: " << s.row << " Status: " << s.status << " || ";
	return o;
}
void Seat::print()
{
	cout << "Row " << this->row << endl;
}