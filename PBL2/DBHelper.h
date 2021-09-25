#pragma once
#include <windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "Movie.h"
#include "Room.h"
#include "Seat.h"
#include "LichChieu.h"
#include "Customer.h"
#include "Ticket.h"
#include<iomanip>
#include<conio.h>
#include <string>
using namespace std;
class Room;
class LichChieu;
class Customer;
class Ticket;
class DBHelper
{
#define SQL_RESULT_LEN 240
#define SQL_RETURN_CODE_LEN 1024
	//define handles and variables
	SQLHANDLE sqlConnHandle;
	SQLHANDLE sqlStmtHandle;
	SQLHANDLE sqlEnvHandle;
	SQLTCHAR retconstring[SQL_RETURN_CODE_LEN];
public:
	void init();
	void ExecuteQuery(const char*);
	vector<Movie> SelectMovie();
	vector<Seat> SelectSeat(string);
	vector<Room> SelectRoom();
	vector<Customer> SelectCustomer();
	vector<Ticket> SelectTicket();
	vector<LichChieu> SelectLich();
	void Update();
	void Delete(const char*);
	void ShowError(unsigned int, const SQLHANDLE&);
//	void ListMovie();
	void close();
};

