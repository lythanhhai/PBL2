#include "Management.h"
bool inc(Movie& a, Movie& b);
bool dec(Movie& a, Movie& b);
bool has_only_digits(const string s);

string getCurrentDate()
{
	time_t t = time(0);   // get time now
	tm* now = localtime(&t);
	return (to_string(now->tm_year + 1900) + "-" + to_string(now->tm_mon + 1) + "-" + to_string(now->tm_mday));
}
string currentDate = getCurrentDate();
string ConvertDate1(int year, int month, int day)
{
	string s = "";
	s = s + to_string(year) + "-" + to_string(month) + "-" + to_string(day);
	return s;
}

Management* Management::_Instance = nullptr;

Management::Management()
{
	this->n_lc = 0;
	this->n_phong = 0;
	this->n_khach = 0;
	this->dsphim.ThemDS();
	this->setRoom();
	this->setLichChieu();
	this->selectVe();
	this->setCustomer();
}

Management::~Management()
{
	this->lichchieu.clear();
	this->phong.clear();
}

Management* Management::getInstance()
{
	if (Management::_Instance == nullptr)
	{
		Management::_Instance = new Management;
	}
	return Management::_Instance;
}

void Management::setRoom()
{
	DBHelper db;
	vector<Room> rl;
	db.init();
	rl = db.SelectRoom();
	for (int i = 0; i < rl.size(); i++)
	{
		this->phong.push_back(rl[i]);
		this->n_phong++;
	}
	db.close();
	for (int i = 0; i < this->n_phong; i++)
	{
		this->phong[i].setSeat();
	}
}

void Management::setLichChieu()
{
	vector<LichChieu> lc;
	DBHelper db;
	db.init();
	lc = db.SelectLich();
	db.close();
	for (int i = 0; i < lc.size(); i++)
	{
		this->lichchieu.push_back(lc[i]);
		this->n_lc++;
	}
	for (int i = 0; i < this->n_lc; i++)
	{
		int index = this->SearchPhong(this->lichchieu[i].getMaPhong());
		if (index != -1)
		{
			this->lichchieu[i].setPhong(&getPhongAt(index));
		}
		index = this->dsphim.Search(this->lichchieu[i].getMaPhim());
		if (index != -1)
		{
			this->lichchieu[i].setPhim(&this->dsphim.getMovieAt(index));
		}
	}
}

void Management::selectVe()
{
	DBHelper db;
	int n;
	db.init();
	vector<Ticket> t = db.SelectTicket();
	db.close();
	n = t.size();
	for (int i = 0; i < n; i++)
	{
		this->ve.push_back(t[i]);
	}
	for (int i = 0; i < n; i++)
	{
		LichChieu& lc = getLichAt(SearchLich(ve[i].getMaChieu()));
		ve[i].setLichChieu(&lc);
		try
		{
			Room& r = lc.getPhong();
			Seat& s = r.getSeat(ve[i].getMaGhe());
			ve[i].setGhe(&s);
		}
		catch (int)
		{
			cout << "Error." << endl;
			system("PAUSE");
			return;
		}
	}
}

void Management::setCustomer()
{
	vector<Customer> c;
	DBHelper db;
	int n;
	db.init();
	c = db.SelectCustomer();
	db.close();
	n = c.size();
	for (int i = 0; i < n; i++)
	{
		this->khach.push_back(c[i]);
		this->n_khach++;
		this->khach[i].setTicket(this->getTicket(this->khach[i].getCustomer_id()));
	}
}

void Management::ThemLichChieu()
{
	DBHelper db;
	char ch;
	int k = 1;
	int nam, thang, ngay;
	string id,m_id,r_id,time,date;
	string qr;
	this->dsphim.Display();
	try
	{
		do
		{
			cout << "Nhap id phim can them: ";
			fflush(stdin);
			cin >> m_id;
			Movie& m = this->dsphim.getMovieAt(this->dsphim.Search(m_id));
			int k = m.checkDate(currentDate);
			if (!k)
			{
				cout << "Phim nay da dung chieu!" << endl;
				system("PAUSE");
				return;
			}
		} while (!k);
		Movie& m = this->dsphim.getMovieAt(this->dsphim.Search(m_id));
		system("PAUSE");
		system("CLS");
		cout << "Phim da chon:\n" << m << endl;
		cout << "Chon gio chieu:" << endl;
		cout << "1. 7h30." << endl
			<< "2. 9h." << endl
			<< "3. 13h30." << endl
			<< "4. 15h30." << endl
			<< "5. 17h." << endl
			<< "6. 19h." << endl
			<< "7. 21h" << endl << endl;
		cin >> ch;
		switch (ch)
		{
		case '1': time = "07:30:00"; break;
		case '2': time = "09:00:00"; break;
		case '3': time = "13:30:00"; break;
		case '4': time = "15:30:00"; break;
		case '5': time = "17:00:00"; break;
		case '6': time = "19:00:00"; break;
		case '7': time = "21:00:00"; break;
		default: {
			cout << "Khong hop le!" << endl;
			system("PAUSE");
			return;
		}
		}
		cout << "Thoi gian da chon: " << time;
		cout << endl;
		this->DSphong(time);
		cout << "Nhap id phong: ";
		do
		{
			try
			{
				k = 1;
				cin.ignore();
				cin >> r_id;
				Room& r = this->getPhongAt(this->SearchPhong(r_id));
			}
			catch (int)
			{
				k = 0;
				cout << "Id khong dung! Nhap lai." << endl;
			}
		} while (k == 0);
		int tmp = this->n_lc + 1;
		id = ("lc" + to_string(tmp));
		LichChieu lc(id, r_id, m_id, currentDate, time, 0);
		Room& r = this->getPhongAt(this->SearchPhong(r_id));
		lc.setPhong(&r);
		r.setStatus(1);
		lc.setPhim(&this->dsphim.getMovieAt(this->dsphim.Search(m_id)));
		this->lichchieu.push_back(lc);
		this->n_lc++;
		// Query start
		db.init();
		qr = "INSERT INTO lichchieu VALUES('" + id + "','" + r_id + "','" + m_id + "','" + time
			+ "','" + currentDate + "'," + to_string(0) + ")";
		const char* sqr = qr.c_str();
		db.ExecuteQuery(sqr);
		db.close();
		cout << "Them lich thanh cong!" << endl;
		system("PAUSE");
	}
	catch (int)
	{
		cout << "Ma chieu khong dung!" << endl;
		system("PAUSE");
	}
}

void Management::DSphong(string time)
{
	cout << "Danh sach phong dang trong: "<< endl;
	for (int i = 0; i < this->n_phong; i++)
	{
		if (this->phong[i].getTime() == time && this->phong[i].getStatus() == 0) {
			cout << this->phong[i] <<endl;
		}
	}
}

void Management::UpdatePhim()
{
	string id;
	cout << "Nhap id phim: ";
	fflush(stdin);
	cin >> id;
	system("CLS");
	cout << "-------------------------------SUA THONG TIN PHIM----------------------------------" << endl << endl;
	int index = this->dsphim.Search(id);
	cout << this->dsphim.getMovieAt(index)<<endl;
	this->dsphim.Update(index);
	system("PAUSE");
}

void Management::ThemPhim()
{
	system("CLS");
	cout << "Them phim: " << endl<<endl;
	this->dsphim.ThemPhim();
}

void Management::XemDSPhim(int k)
{
	if (k == 1)
	{
		this->dsphim.SortByPrice(0,this->dsphim.getSoLuong() - 1,inc);
	}
	else this->dsphim.SortByPrice(0, this->dsphim.getSoLuong() - 1, dec);
	this->dsphim.Display();
	system("PAUSE");
}

void Management::XoaPhim()
{
	string id;
	this->XemDSPhim(1);
	cout << "Nhap id phim can xoa: ";
	cin.ignore();
	cin >> id;
	int index = this->dsphim.Search(id);
	if (index != -1)
	{
		Movie& m = this->dsphim.getMovieAt(index);
		if (this->checkMovieDelete(m))
		{
			this->dsphim.Xoa(index);
			cout << "Xoa thanh cong!!"<<endl;
			system("PAUSE");
		}
		else
		{
			cout << "Phim nay dang co lich chieu. Khong the xoa!" << endl;
			system("PAUSE");
		}
	}
	else
	{
		cout << "Id khong dung!!";
		system("PAUSE");
		return;
	}
}

void Management::XemLichChieu()
{
	system("CLS");
	cout << "Lich chieu:" << endl;
	//if (k == 1)
	//{
	//	this->dsphim.SortByPrice(0,this->dsphim.getSoLuong() - 1 , inc);
	//}
	//else this->dsphim.SortByPrice(0, this->dsphim.getSoLuong() - 1, dec);

	for (int i = 0; i < n_lc; i++)
	{
		if(this->lichchieu[i].getDeleted()==0)
		cout << this->lichchieu[i]<<endl;
	}
	system("PAUSE");
}

void Management::SuaLich()
{
	DBHelper db;
	int k, index, ngay,thang,nam;
	char ch;
	string id,m_id,r_id;
	string gio;
	this->XemLichChieu();
	try
	{
		k = 1;
		cout << "Nhap ma chieu: ";
		cin.ignore();
		cin >> id;
		index = this->SearchLich(id);
		gio = getLichAt(index).getThoiGian();
		LichChieu& lc = getLichAt(index);
		//Kiem tra da co nguoi dat ghe cua lich nay chua??
		if (lc.getPhong().getSoGheTrong() < 30)
		{
			cout << "Lich da co nguoi dat. Khong the thay doi!!" << endl;
			return;
		}
	}
	catch (int)
	{
		k = 0;
		cout << "Ma chieu khong hop le!" << endl;
		system("PAUSE");
		return;
	};
	cout << "Thong tin: "<< endl;
	cout << this->getLichAt(index);
	cout << "1. Sua phim." << endl
		<< "2. Sua phong." << endl
		<< "3. Sua thoi gian." << endl
		<< "Nhap lua chon: ";
	cin >> ch;
	switch (ch)
	{
	case '1': {
		system("CLS");
		XemDSPhim(0);
		try
		{
			cout << "Nhap ma phim: ";
			cin.ignore();
			cin >> m_id;
			Movie& m = this->dsphim.getMovieAt(this->dsphim.Search(m_id));
			this->getLichAt(index).setPhim(&m);
			string tmp = "UPDATE lichchieu SET movie_id ='" + m_id + "' WHERE ma_chieu='" + id + "'";
			const char* qr = tmp.c_str();
			db.init();
			db.ExecuteQuery(qr);
			db.close();
			cout << "Sua thanh cong!" << endl;
			system("PAUSE");
		}
		catch (int)
		{
			cout << "Ma phim khong hop le!" << endl;
			system("PAUSE");
			return;
		}
	} break;
	case '2': {
		system("CLS");
		this->DSphong(gio);
		try
		{
			k = 1;
			cout << "Nhap ma phong: ";
			cin.ignore();
			cin >> r_id;
			db.init();
			Room& r = this->getPhongAt(this->SearchPhong(r_id));
			this->getLichAt(index).getPhong().setStatus(0); //Thay doi trang thai phong cu -> 0
			this->getLichAt(index).setPhong(&r);
			string tmp = "UPDATE lichchieu SET room_id ='" + r_id + "' WHERE ma_chieu ='" + id + "'";
			const char* qr = tmp.c_str();
			db.ExecuteQuery(qr);

			db.close();
			system("CLS");
			cout << "Sua thanh cong!" << endl;
			system("PAUSE");
		}
		catch (int)
		{
			k = 0;
			cout << "Ma phong khong hop le!" << endl;
			system("PAUSE");
			return;
		}
	} break;
	case '3': {
		system("CLS");
		string time;
		cout << "Chon gio chieu:" << endl;
		cout << "1. 7h30." << endl
			<< "2. 9h." << endl
			<< "3. 13h30." << endl
			<< "4. 15h30." << endl
			<< "5. 17h." << endl
			<< "6. 19h." << endl
			<< "7. 21h" << endl << endl;
		cin >> ch;
		switch (ch)
		{
		case '1': time = "07:30:00"; break;
		case '2': time = "09:00:00"; break;
		case '3': time = "13:30:00"; break;
		case '4': time = "15:30:00"; break;
		case '5': time = "17:00:00"; break;
		case '6': time = "19:00:00"; break;
		case '7': time = "21:00:00"; break;
		default: {
			cout << "Khong hop le!" << endl;
			system("PAUSE");
			return;
		}
		}
		cout << "Thoi gian da chon: " << time;
		if (time != this->getLichAt(index).getThoiGian()) // neu khac th gian cu moi thuc hien
		{
			this->getLichAt(index).setThoiGian(time);
			this->DSphong(time);
			try
			{
				k = 1;
				cout << "Nhap ma phong: ";
				cin.ignore();
				cin >> r_id;
				Room& r = this->getPhongAt(this->SearchPhong(r_id));
				this->getLichAt(index).getPhong().setStatus(0); //Thay doi trang thai phong cu -> 0
				this->getLichAt(index).setPhong(&r);
				db.init();
				string tmp = "UPDATE lichchieu SET thoigianchieu ='" + time + "', room_id ='" + r_id + "' WHERE ma_chieu ='" + id + "'";
				const char* qr = tmp.c_str();
				db.ExecuteQuery(qr);
				db.close();
				system("CLS");
				cout << "Sua thanh cong!" << endl;
				system("PAUSE");
			}
			catch (int)
			{
				k = 0;
				cout << "Ma phong khong hop le!" << endl;
				system("PAUSE");
				return;
			}
		}
	} break;
	};
}

void Management::XoaLich()
{
	DBHelper db;
	string id;
	int index;
	system("CLS");
	this->XemLichChieu();
	cout << "Nhap ma chieu: ";
	cin.ignore();
	cin >> id;
	try
	{
		string r_id;
		index = SearchLich(id);
		LichChieu& lc = getLichAt(index);
		Room& r = getPhongAt(SearchPhong(lc.getMaPhong()));
		r.setStatus(0);
		lc.setDeleted(1);
		db.init();
		string tmp = "UPDATE lichchieu SET [delete] = 1 WHERE ma_chieu ='" + id + "'";
		const char* s = tmp.c_str();
		db.ExecuteQuery(s);	
		db.close();
		cout << "Xoa lich chieu thanh cong!!" << endl;
	}
	catch (int)
	{
		cout << "Ma chieu khong hop le!!" << endl;
		system("PAUSE");
		return;
	}
}

void Management::InfoKH(const Customer& c)
{
	system("CLS");
	cout << "Thong tin khach hang: " << endl;
	cout << c;
}

void Management::XemVe(Customer& c)
{
	c.showTicket();
	system("PAUSE");
}

void Management::DatVe(Customer& c)
{
	DBHelper db;
	string mc;
	int seat_no,r_val;
	int soluong;
	int tongtien = 0;
	char row;
//	system("CLS");
	cout << "Dat ve: " << endl;
	this->XemLichChieu();
	cout << "Chon ma chieu: ";
	cin.ignore();
	cin >> mc;
	try
	{
		LichChieu& lc = this->getLichAt(this->SearchLich(mc));
		Movie& m = lc.getPhim();
		Room& r = lc.getPhong();
		r.showroom();
		//Chon so luong ve
		cout << "Nhap so luong ve: "; cin >> soluong;
		if (soluong >= r.getSoGheTrong())
		{
			cout << "Phong khong du ghe trong." << endl;
			system("PAUSE"); return;
		}
		//Mang de luu tam thoi cac ve da mua
		Ticket *tk = new Ticket[soluong];
		for (int i = 0; i < soluong; i++)
		{
			cout << "Vui long chon ghe: " << endl
				<< "Hang: ";
			cin >> row;
			do
			{
				switch (row)
				{
				case 'A': r_val = 1; break;
				case 'a': r_val = 1; break;
				case 'B': r_val = 2; break;
				case 'b': r_val = 2; break;
				case 'C': r_val = 3; break;
				case 'c': r_val = 3; break;
				default: cout << "Hang khong hop le!!" << endl; return;
				}
				cout << "So ghe: "; cin >> seat_no;
				cout << r_val << " " << seat_no << endl;
				if (r.getSeatAt(seat_no, r_val).getStatus() == 1) cout << "Ghe da duoc dat. Vui long chon ghe khac!" << endl;
				else break;
			} while (1);
			Seat& s = r.getSeatAt(seat_no, r_val);
			int t_id = this->ve.size() + 1;
			Ticket t(t_id, c.getCustomer_id(), lc.getId(), s.getId());
			t.setGhe(&s);
			t.setLichChieu(&lc);
			c.AddTicket(t);
			s.setStatus(1);
			r.setSoGheTrong(r.getSoGheTrong() - 1);
			db.init();
			string tmp = "INSERT INTO ticket VALUES('" + lc.getId() + "'," + to_string(c.getCustomer_id())
				+ ", " + to_string(s.getId()) + ")";
			const char* qr = tmp.c_str();
			db.ExecuteQuery(qr);
			db.close();
			tk[i] = t;
		}
		for (int i = 0; i < soluong; i++)
		{
			tongtien += tk[i].getPrice();
		}
			cout << "Dat ve thanh cong!" << endl;
			cout << "Tong tien: " << tongtien << endl;
			system("PAUSE");
		}
	catch (int)
	{
		cout << "Ma chieu khong hop le!!" << endl;
		system("PAUSE");
		return;
	}
	catch (string s)
	{
		cout << s;
		system("PAUSE");
		return;
	}
}

void Management::SuaThongTin(Customer& c)
{
	DBHelper db;
	string ten, diachi, sdt, email;
	system("CLS");
	cout << "------------------------------------ SUA THONG TIN ----------------------------------------" << endl << endl;
	cout << c <<endl;
	cout << "Nhap thong tin moi: " << endl;
	cout << "Ten: ";
	cin.ignore();
	getline(cin, ten);
	cout << "Dia chi: ";
	fflush(stdin);
	getline(cin, diachi);
	do
	{
		cout << "So dien thoai: ";
		fflush(stdin);
		getline(cin, sdt);
		if (sdt.length() != 10) cout << "So dien thoai phai la 10 chu so."<<endl;
		else
		{
			if (!has_only_digits(sdt)) cout << "So dien thoai phai la 10 chu so." << endl;
			else break;
		}
	} while (1);
	cout << "Email: ";
	fflush(stdin);
	cin >> email;
	c.setTen(ten);
	c.setDiaChi(diachi);
	c.setSDT(sdt);
	c.setEmail(email);
	db.init();
	string s = "UPDATE Customer SET customer_name ='" + ten + "', address ='" + diachi + "', phone_no ='" + sdt + "', email_id ='" + email
		+ "' WHERE customer_id = " + to_string(c.getCustomer_id());
	const char* qr = s.c_str();
	db.ExecuteQuery(qr);
	db.close();
	cout << "Sua thong tin thanh cong!" << endl;
	system("PAUSE");
}

void Management::newKH(string email)
{
	DBHelper db;
	string ten, add, sdt;
	int id;
	cout << "Nhap ten: ";
	cin.ignore();
	getline(cin, ten);
	cout << "Dia chi: ";
	fflush(stdin);
	getline(cin, add);
	/*cout << "Sdt: ";
	cin.ignore();
	cin >> sdt;*/
	do
	{
		cout << "So dien thoai: ";
		fflush(stdin);
		getline(cin, sdt);
		if (sdt.length() != 10) cout << "So dien thoai phai la 10 chu so." << endl;
		else
		{
			if (!has_only_digits(sdt)) cout << "So dien thoai phai la 10 chu so." << endl;
			else break;
		}
	} while (1);
	id = this->n_khach + 1;
	Customer c(id, ten, add, email, sdt);
	this->khach.push_back(c);
	this->n_khach++;
	db.init();
	string s = "INSERT INTO Customer VALUES ('" + ten + "','" + add + "','" + sdt + "','" + email + "')";
	const char* qr = s.c_str();
	db.ExecuteQuery(qr);
	db.close();
}

int Management::SearchPhong(string id)
{
	for (int i = 0; i < this->n_phong; i++)
	{
		if (this->phong[i].getId() == id)
			return i;
	}
	return -1;
}

Room& Management::getPhongAt(int index)
{
	if (index >= 0 && index < this->n_phong)
	{
		return this->phong[index];
	}
	else throw - 1;
}

int Management::SearchLich(string id)
{
	for (int i = 0; i < this->lichchieu.size(); i++)
	{
		if (this->lichchieu[i].getId() == id)
		{
			return i;
		}
	}
	return -1;
}

LichChieu& Management::getLichAt(int index)
{
	if (index >= 0 && index < this->n_lc)
	{
		return this->lichchieu[index];
	}
	else throw - 1;
}

vector<Ticket> Management::getTicket(int id)
{
	int n = this->ve.size();
	vector<Ticket> v;
	for (int i = 0; i < n; i++)
	{
		if (this->ve[i].getId() == id)
		{
			v.push_back(this->ve[i]);
		}
	}
	return v;
}

int Management::SearchCustomer(string email)
{
	for (int i = 0; i < n_khach; i++)
	{
		if (this->khach[i].getEmail() == email)
		{
			return i;
		}
	}
	return -1;
}

Customer& Management::getCustomerAt(int index)
{
	if (index >= 0 && index < this->n_khach)
	{
		return this->khach[index];
	}
	else throw - 1;
}

bool Management::checkMovieDelete(Movie& m)
{
	string id;
	id = m.getid();
	for (int i = 0; i < this->n_lc; i++)
	{
		if (this->lichchieu[i].getMaPhim() == id && this->lichchieu[i].getDeleted() == 0)
		{
			return false;
		}
	}
	return true;
}

bool inc(Movie& a, Movie& b)
{
	return (a < b);
}

bool dec(Movie& a, Movie& b)
{
	return (a > b);
}

bool has_only_digits(const string s) {
	return s.find_first_not_of("0123456789") == string::npos;
}