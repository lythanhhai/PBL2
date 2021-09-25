#include "ticket.h"

Ticket::Ticket(int id, int c_id, string mc, int s_id)
	: ticket_id(id),customer_id(c_id),ma_chieu(mc),seat_id(s_id)
{
	this->lichchieu = nullptr;
	this->ghe = nullptr;
}

Ticket::~Ticket()
{

}

void Ticket::setLichChieu(LichChieu* lc)
{
	this->lichchieu = lc;
}

LichChieu& Ticket::getLichChieu()
{
	if (this->lichchieu != nullptr)
	{
		return *(this->lichchieu);
	}
}

void Ticket::setGhe(Seat* s)
{
	this->ghe = s;
}

Seat& Ticket::getGhe()
{
	if (this->ghe != nullptr)
	{
		return *(this->ghe);
	}
}

int Ticket::getId()
{
	return this->ticket_id;
}

int Ticket::getCustomerId()
{
	return this->customer_id;
}

string Ticket::getMaChieu()
{
	return this->ma_chieu;
}

int Ticket::getMaGhe()
{
	return this->seat_id;
}

int Ticket::getPrice()
{
	return this->lichchieu->getPhim().getPrice();
}

ostream& operator<<(ostream& o, const Ticket& t)
{
	char c[4] = { 'A','B','C','D' };
	o << "Thong tin ve: " << endl
		<< "Ten phim: " << t.lichchieu->getPhim().getName() << endl
		<< "The loai: " << t.lichchieu->getPhim().getGenre() << endl
		<< "Gia ve: " << t.lichchieu->getPhim().getPrice() << endl
		<< "Phong: " << t.lichchieu->getPhong().getSoPhong() << ", "
		<< "Ghe: " << t.ghe->getseat() << ", " << "Hang: " << c[t.ghe->getRow()] << endl;
	return o;
}
