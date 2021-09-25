#include "QLPhim.h"
string ConvertDate(int year, int month, int day)
{
	string s = "";
	s = s + to_string(year) + "-" + to_string(month) + "-" + to_string(day);
	return s;
}

QLPhim::QLPhim()
{
	this->soluong = 0;
}

QLPhim::~QLPhim()
{
	this->data.clear();
}

void QLPhim::Add(Movie& m)
{
	this->data.push_back(m);
	this->soluong++;
}

void QLPhim::ThemDS()
{
	DBHelper db;
	vector<Movie> m;
	db.init();
	m = db.SelectMovie();
	for (int i = 0; i < m.size(); i++)
	{
		this->Add(m[i]);
	}
}

void QLPhim::ThemPhim()
{
	DBHelper db;
	string id,ten, dir, cast, ngaychieu, dungchieu, des, genre;
	int thoiluong, giave;
	int ngay, thang, nam;
	cout << "Ten phim: ";
	cin.ignore();
	getline(cin, ten);
	cout << "Dao dien: "; 
	fflush(stdin);
	getline(cin, dir);
	cout << "Dien vien chinh: ";
	fflush(stdin);
	getline(cin, cast);
	cout << "Ngay phat hanh: "<<endl;
	cout << "Ngay: "; cin >> ngay;
	cout << "Thang: "; cin >> thang;
	cout << "Nam: "; cin >> nam;
	ngaychieu = ConvertDate(nam, thang, ngay);
		cout << " Ngay dung chieu: "; 
		cout << "Ngay: "; cin >> ngay;
		cout << "Thang: "; cin >> thang;
		cout << "Nam: "; cin >> nam;
		dungchieu = ConvertDate(nam, thang, ngay);
		cout << "Mo ta: ";
		cin.ignore();
		getline(cin, des);
		cout << "The loai: ";
		fflush(stdin);
		getline(cin, genre);
		cout << "Thoi luong: ";
		cin >> thoiluong;
		cout << "Gia ve: ";
		cin >> giave;
		id = "m" + to_string(this->soluong + 1);
		Movie m(id, ten, dir, cast, ngaychieu, dungchieu, des, genre, thoiluong, giave,0);
		this->Add(m);
		db.init();
		string s = "INSERT INTO movie VALUES ('" + id + "','" + ten + "','" + dir + "','" + cast +
			"','" + ngaychieu + "','" + dungchieu + "','" + des + "','" + genre + "'," + to_string(thoiluong) + "," + to_string(giave)+","+to_string(0) +")";
		const char* qr = s.c_str();
		db.ExecuteQuery(qr);
		db.close();
		cout << "Them phim thanh cong!" << endl;
		system("PAUSE");
}

void QLPhim::Xoa(int index)
{
	DBHelper db;
	if (index >= 0 && index < this->soluong)
	{
		this->data[index].setDeleted(1);
	}
	db.init();
	string s = "UPDATE movie SET [delete] = 1 WHERE movie_id ='"+this->data[index].getid()+"'";
	const char* qr = s.c_str();
	db.ExecuteQuery(qr);
	db.close();
	cout << "Xoa phim thanh cong!!" << endl;
	system("PAUSE");
}

void QLPhim::Update(int index)
{
	DBHelper db;
	string ten;
	string daodien;
	string dv;
	string ngayph;
	string ngaydung;
	string mota;
	string theloai;
	int thoiluong;
	int gia;
	int year, month, day;
	if (index >= 0 && index < this->soluong)
	{
		cout << "Ten phim: ";
		cin.ignore();
		getline(cin, ten);
		cout << "Dao dien: ";
		fflush(stdin);
		getline(cin, daodien);
		cout << "Dien vien chinh: ";
		fflush(stdin);
		getline(cin, dv);
		cout << "Ngay phat hanh: ";
		cout << "Nam: "; cin >> year;
		cout << "Thang: "; cin >> month;
		cout << "Ngay: "; cin >> day;
		ngayph = ConvertDate(year, month, day);
		cout << "Ngay dung chieu: ";
		cout << "Nam: "; cin >> year;
		cout << "Thang: "; cin >> month;
		cout << "Ngay: "; cin >> day;
		ngaydung = ConvertDate(year, month, day);
		cout << "Mo ta: ";
		cin.ignore();
		getline(cin, mota);
		cout << "The loai: ";
		fflush(stdin);
		getline(cin, theloai);
		cout << "Thoi Luong: "; cin >> thoiluong;
		cout << "Gia ve: "; cin >> gia;
		Movie tmp(this->data[index].getid(), ten, daodien, dv, ngayph, ngaydung,mota ,theloai ,thoiluong, gia);
		this->data[index] = tmp;
		string query = "UPDATE movie SET movie_name ='" +
			ten + "', director ='" + daodien + "', main_actor ='" +
			dv + "', release_date='" +
			ngayph + "', end_show='" + ngaydung + "', description='"
			+ mota + "', genre='" + theloai + "', running_time= " +
			to_string(thoiluong) + " , price=" + to_string(gia)
			+ "WHERE movie_id ='" + this->data[index].getid() + "'";
		const char* q = query.c_str();
		db.init();
		db.ExecuteQuery(q);
		db.close();
	}
}

void QLPhim::Display()
{
	cout << "DANH SACH PHIM: " << endl;
	for (int i = 0; i < this->soluong; i++)
	{
		if (this->data[i].getDeleted() == 0)
		{
			cout << this->data[i] << endl;
		}
	}
}

int QLPhim::Search(string id)
{
	for (int i = 0; i < this->soluong; i++)
	{
		if (id == this->data[i].getid())
		{
			return i;
		}
	}
	return -1;
}

Movie& QLPhim::getMovieAt(int index)
{
	if (index >= 0 && index < this->soluong)
	{
		return this->data[index];
	}
	else throw -1;
}

void QLPhim::SortByPrice(int l, int r, bool (*cmp)(Movie&, Movie&))
{
	//if (l <= r)
	//{
		srand(time(NULL));
		Movie key = this->data[l + rand() % (r - l + 1)];
		int i = l;
		int j = r;

		while (i <= j)
		{
			while (cmp(this->data[i],key))
				i++;
			while (cmp(key,this->data[j]))
				j--;
			if (i <= j)
			{
				if(i < j)
				swap(this->data[i], this->data[j]);
				i++; j--;
			}
		}

		if (l < j)
			SortByPrice(l, j, cmp);
		if (r > i)
			SortByPrice(i, r, cmp);
//	}
}

int QLPhim::getSoLuong()
{
	return this->soluong;
}
//
//bool inc(Movie& a, Movie& b)
//{
//	return (a < b);
//}
//
//bool dec(Movie& a, Movie& b)
//{
//	return (a > b);
//}