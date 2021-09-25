#pragma once
#include "Movie.h"
#include "Room.h"
#include <string>
#include <iostream>
using namespace std;
class Room;
class LichChieu
{
private:
	string id;
	string room_id;
	string movie_id;
	string thoigianchieu;
	string ngaychieu;
	Room* phongchieu;
	Movie* phimchieu;
	int deleted;
public:
	LichChieu(string = "",string = "",string ="",string ="",string ="",int = 0);
	~LichChieu();
	void setPhong(Room*);
	Room& getPhong(); //throw int
	void setPhim(Movie*);
	Movie& getPhim();
	void setId(string);
	string getId();
	void setThoiGian(string);
	string getThoiGian();
	void setNgayChieu(string);
	string getNgayChieu();
	string getMaPhong();
	string getMaPhim();
	void setDeleted(int);
	int getDeleted();
	friend ostream& operator<<(ostream&, const LichChieu&);
};

