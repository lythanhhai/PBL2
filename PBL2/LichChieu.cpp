#include "LichChieu.h"

LichChieu::LichChieu(string id, string r_id,string m_id, string ngaychieu, string tg,int deleted)
	:id(id),room_id(r_id),movie_id(m_id),ngaychieu(ngaychieu), thoigianchieu(tg),deleted(deleted)
{
	this->phimchieu = nullptr;
	this->phongchieu = nullptr;
}

LichChieu::~LichChieu()
{
	
}

void LichChieu::setPhong(Room* r)
{
	this->phongchieu = r;
}

Room& LichChieu::getPhong()
{
	if (this->phongchieu != nullptr)
	{
		return *(this->phongchieu);
	}
	else throw - 1;
}

//void LichChieu::setPhong(Room* r)
//{
//	if (this->phongchieu == nullptr)
//	{
//		this->phongchieu = r;
//	}
//	else cout << "Da co phong chieu." << endl;
//}
//
//Room& LichChieu::getPhong()
//{
//	return *(this->phongchieu);
//}

void LichChieu::setPhim(Movie* m)
{
	this->phimchieu = m;
}

Movie& LichChieu::getPhim()
{
	return *(this->phimchieu);
}

void LichChieu::setId(string s)
{
	this->id = s;
}

string LichChieu::getId()
{
	return this->id;
}

void LichChieu::setThoiGian(string s)
{
	this->thoigianchieu = s;
}

string LichChieu::getThoiGian()
{
	return this->thoigianchieu;
}

void LichChieu::setNgayChieu(string date)
{
	this->ngaychieu = date;
}

string LichChieu::getNgayChieu()
{
	return this->ngaychieu;
}

string LichChieu::getMaPhong()
{
	return this->room_id;
}

string LichChieu::getMaPhim()
{
	return this->movie_id;
}

void LichChieu::setDeleted(int i)
{
	this->deleted = i;
}

int LichChieu::getDeleted()
{
	return this->deleted;
}

ostream& operator<<(ostream& o, const LichChieu& lc)
{
	o << "Ma lich chieu: " << lc.id << endl
		<< "Phong chieu: " << lc.phongchieu->getSoPhong()
		<< ", So ghe trong: " << lc.phongchieu->getSoGheTrong() << endl
		<< "Phim dang chieu: " << lc.phimchieu->getName() << endl
		<< "Thoi gian: " << lc.thoigianchieu << endl
		<< "Ngay chieu: " << lc.ngaychieu << endl;
	return o;
}
