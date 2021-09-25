#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS
#include "DBHelper.h"
#include <ctime>    
#include <vector>
#include <iostream>
#include <string>
#include <limits>
#include "QLPhim.h"
#include "Movie.h"
#include "LichChieu.h"
#include "Customer.h"
using namespace std;

class Management
{
private:
	static Management* _Instance;
private:
	int n_lc; //so luong lich chieu
	vector<LichChieu> lichchieu;
	int n_phong; //so luong phong
	vector<Room> phong;
	QLPhim dsphim;
	int n_khach;
	vector<Customer> khach;
	vector<Ticket> ve;
	Management();
public:
	~Management();
	static Management* getInstance();
	void setRoom();
	void setLichChieu();
	void selectVe();
	void setCustomer();
	void DSphong(string); //In ra danh sach phong con trong tai thoi gian t
	//ql phim
	void UpdatePhim();
	void ThemPhim();
	void XemDSPhim(int);
	void XoaPhim(); //
	//ql lich chieu
	void XemLichChieu();
	void ThemLichChieu();
	void SuaLich(); // ok
	void XoaLich(); // ok
	//khach hang
	void InfoKH(const Customer&);
	void XemVe(Customer&);
	void DatVe(Customer&);
	void SuaThongTin(Customer&);
	void newKH(string);
	//----------------------
	int SearchPhong(string);
	Room& getPhongAt(int); //throw -1
	int SearchLich(string);
	LichChieu& getLichAt(int); //throw -1
	vector<Ticket> getTicket(int);
	int SearchCustomer(string);//theo email
	Customer& getCustomerAt(int); //throw -1
	bool checkMovieDelete(Movie&);
};

