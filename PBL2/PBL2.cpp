#include "Management.h"

void Quan_Ly_Lich_Chieu();
void Quan_Ly_Phim();
void Khach_hang();
void MenuKH(Customer&);
void Menu()
{
	do
	{
		system("CLS");
		char ch;
		cout << "=========================== QUAN LY RAP CHIEU PHIM ===============================" << endl << endl;
		cout << "Menu: " << endl
			<< "1. Quan ly lich chieu." << endl
			<< "2. Quan ly phim." << endl
			<< "3. Khach hang." << endl
			<< "0. Thoat." << endl
			<< "Nhap lua chon: ";
		fflush(stdin);
		cin >> ch;
		switch (ch)
		{
		case '1': Quan_Ly_Lich_Chieu(); break;
		case '2': Quan_Ly_Phim(); break;
		case '3': Khach_hang(); break;
		case '0': {
			system("CLS");
			cout << "Sinh vien thuc hien:" << endl
				<< "Duong Phu Ninh" << "  19TCLC_DT2" << endl
				<< "Ly Thanh Hai" << "  19TCLC_DT2" << endl;
			system("PAUSE");
			exit(1);
		}
		default: cout << "Lua chon khong hop le!" << endl; system("PAUSE");
		};
	} while (1);
}

void Quan_Ly_Lich_Chieu()
{
	char ch;
	do
	{
		system("CLS");
		cout << "--------------------------------- QUAN LY LICH CHIEU -----------------------------------" << endl<<endl;
		cout << "1. Xem lich chieu." << endl
			<< "2. Them lich chieu." << endl
			<< "3. Sua lich chieu." << endl
			<< "4. Xoa lich chieu." << endl
			<< "0. Tro ve."<< endl
			<< "Nhap lua chon: ";
		cin >> ch;
		switch (ch)
		{
		case '1': Management::getInstance()->XemLichChieu(); break;
		case '2':Management::getInstance()->ThemLichChieu(); break;
		case '3':Management::getInstance()->SuaLich(); break;
		case '4':Management::getInstance()->XoaLich(); break;
		case '0': return;
		default: cout << "Lua chon khong hop le!!" << endl;
		}
	} while (true);
}

void Quan_Ly_Phim()
{
	char ch;
	do
	{
		system("CLS");
		cout << "------------------------------- QUAN LY PHIM --------------------------------" << endl << endl;
		cout << "1. Xem danh sach phim dang chieu." << endl
			<< "2. Them phim moi." << endl
			<< "3. Sua thong tin phim." << endl
			<< "4. Xoa phim." << endl
			<< "0. Tro ve." << endl
			<< "Nhap lua chon: ";
		cin >> ch;
		switch (ch)
		{
		case '1': Management::getInstance()->XemDSPhim(0); break;
		case '2':Management::getInstance()->ThemPhim(); break;
		case '3':Management::getInstance()->UpdatePhim(); break;
		case '4':Management::getInstance()->XoaPhim(); break;
		case '0': return;
		default: cout << "Lua chon khong hop le!!" << endl;
		}
	} while (1);
}

void MenuKH(Customer& c)
{
	char ch;
	do
	{
		system("CLS");
		Management::getInstance()->InfoKH(c);
		cout << "---------------------------------- KHACH HANG ----------------------------------" << endl << endl;
		cout << "1. Dat ve." << endl
			<< "2. Xem lich su dat ve." << endl
			<< "3. Sua thong tin."<<endl
			<< "0. Tro ve." << endl
			<< "Nhap lua chon: ";
		cin >> ch;
		switch (ch)
		{
		case '1': Management::getInstance()->DatVe(c); break;
		case '2': Management::getInstance()->XemVe(c); break;
		case '3': Management::getInstance()->SuaThongTin(c); break;
		case '0': return; break;
		default: {
			cout << "Lua chon khong hop le!!" << endl;
			system("PAUSE");
		}
		}
	} while (true);
}

void Khach_hang()
{
	string email;
	int index;
	do
	{
		system("CLS");
		cout << "---------------------------------- KHACH HANG ----------------------------------" << endl << endl;
		cout << "Nhap email: ";
		cin.ignore();
		cin >> email;
		try
		{
			index = Management::getInstance()->SearchCustomer(email);
			Customer& c = Management::getInstance()->getCustomerAt(index);
			MenuKH(c);
			return;
		}
		catch (int)
		{
			char c;
			cout << "Email khong dung!!"<<endl;
			cout << "Tao moi? (Bam Y de tiep tuc.) ";
			cin >> c;
			switch (c)
			{
			case 'y': Management::getInstance()->newKH(email); break;
			case 'Y': Management::getInstance()->newKH(email); break;
			default: return;
			}
			system("Pause");
			return;
		}
	} while (1);
}

int main()
{
	Menu();
	system("PAUSE");
}