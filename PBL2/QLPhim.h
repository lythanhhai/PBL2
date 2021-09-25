#pragma once
#include "Movie.h"
#include "DBHelper.h"
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;
class QLPhim
{
private:
	int soluong;
	vector<Movie> data;
public:
	QLPhim();
	~QLPhim();
	void Add(Movie&);
	void ThemDS();
	void ThemPhim();
	void Xoa(int);
	void Update(int);
	void Display();
	int Search(string);
	Movie& getMovieAt(int);
	void SortByPrice(int l, int r,bool (*cmp)(Movie&, Movie&));
	int getSoLuong();
//	void SortByDay();
};
