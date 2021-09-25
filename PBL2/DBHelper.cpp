#include "DBHelper.h"
void DBHelper::init()
{
	//initializations
	sqlConnHandle = NULL;
	sqlStmtHandle = NULL;
	//allocations
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlEnvHandle))
		close();

	if (SQL_SUCCESS != SQLSetEnvAttr(sqlEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
		close();

	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, sqlEnvHandle, &sqlConnHandle))
		close();

	//output
//	cout << "Attempting connection to SQL Server...";
//	cout << "\n";
	switch (SQLDriverConnect(sqlConnHandle, NULL,(SQLTCHAR*)"DRIVER={SQL Server};SERVER=LAPTOP-OUG389DS;DATABASE=bookTicket2;trusted = true;",
		SQL_NTS,
		retconstring,
		1024,
		NULL,
		SQL_DRIVER_NOPROMPT)) {

	case SQL_SUCCESS:
//		cout << "Successfully connected to SQL Server";
//		cout << "\n";
		break;

	case SQL_SUCCESS_WITH_INFO:
//		cout << "Successfully connected to SQL Server";
//		cout << "\n";
		break;

	case SQL_INVALID_HANDLE:
		cout << "Could not connect to SQL Server";
		cout << "\n";
		close();
		break;

	case SQL_ERROR:
		cout << "Could not connect to SQL Server";
		ShowError(SQL_HANDLE_DBC, sqlConnHandle);
		cout << "\n";
		close();
		break;

	default:
		break;
	}
	//if there is a problem connecting then exit application
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle))
		close();
}

//void DBHelper::Select(Movie& m, const int& id) 
//{
//	
//	//output
//	cout << "\n";
//	cout << "Executing T-SQL query...";
//	cout << "\n";
//    string s = "SELECT * FROM movie WHERE movie_id = ";
//	string s1 = to_string(id);
//	string s2;
//	s2 = s + s1;
//	cout << s2;
//	const char* n = s2.c_str();
//	/*for (int i = 0; i < 50; i++)
//	{
//		n[i] = s2[i];
//	}*/
//	//if there is a problem executing the query then exit application
//	//else display query resultS
//	if (SQL_SUCCESS != SQLExecDirectA(sqlStmtHandle, (SQLCHAR*)n, SQL_NTS)) {
//		ShowError(SQL_HANDLE_DBC, sqlStmtHandle);
//		cout << "Error querying SQL Server";
//		cout << "\n";
//		close();
//	}
//	else {
//		//declare output variable and pointer
//		SQLINTEGER ptrSqlVersion;
//		char m_id[5];
//		char name[30];
//		char dir[30];
//		char cast[30];
//		char release_date[20];
//		char end_show[20];
//		char des[100];
//		char genre[50];
//		int running_time;
//		int price;
//		if (SQLFetch(sqlStmtHandle) == SQL_SUCCESS) {
//			SQLGetData(sqlStmtHandle, 1, SQL_CHAR, m_id, SQL_RESULT_LEN, &ptrSqlVersion);
//			SQLGetData(sqlStmtHandle, 2, SQL_CHAR, name, SQL_RESULT_LEN, &ptrSqlVersion);
//			SQLGetData(sqlStmtHandle, 3, SQL_CHAR, dir, SQL_RESULT_LEN, &ptrSqlVersion);
//			SQLGetData(sqlStmtHandle, 4, SQL_CHAR, cast, SQL_RESULT_LEN, &ptrSqlVersion);
//			SQLGetData(sqlStmtHandle, 5, SQL_CHAR, release_date, SQL_RESULT_LEN, &ptrSqlVersion);
//			SQLGetData(sqlStmtHandle, 6, SQL_CHAR, end_show, SQL_RESULT_LEN, &ptrSqlVersion);
//			SQLGetData(sqlStmtHandle, 7, SQL_CHAR, des, SQL_RESULT_LEN, &ptrSqlVersion);
//			SQLGetData(sqlStmtHandle, 8, SQL_CHAR, genre, SQL_RESULT_LEN, &ptrSqlVersion);
//			SQLGetData(sqlStmtHandle, 9, SQL_INTEGER, &running_time, 1, &ptrSqlVersion);
//			SQLGetData(sqlStmtHandle, 10, SQL_INTEGER, &price, 1, &ptrSqlVersion);
//			
//	/*		string sname(name);
//			string sdir(dir);
//			string scast(cast);
//			string sdate(release_date);
//			string sdes(des);
//			string sgenre(genre);*/
// 			Movie tmp(string(m_id), string(name), string(dir), string(cast), string(release_date),string(end_show) , string(des), string(genre), running_time, price);
//			m = tmp;
//		}
//	}
//	SQLCancel(sqlStmtHandle);
//}

vector<Movie> DBHelper::SelectMovie()
{
	vector<Movie> m;
	Movie list[100];
	int count = 0;
	if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLTCHAR*)"SELECT * FROM movie", SQL_NTS)) {
		ShowError(SQL_HANDLE_DBC, sqlStmtHandle);
		cout << "Error querying SQL Server";
		cout << "\n";
		close();
	}
	else {
		//declare output variable and pointer
		SQLINTEGER ptrSqlVersion;
		char m_id[5];
		char name[30];
		char dir[30];
		char cast[30];
		char release_date[20];
		char end[30];
		char des[100];
		char genre[50];
		int running_time;
		int price;
		int deleted;
		while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS) {
			SQLGetData(sqlStmtHandle, 1, SQL_CHAR, m_id, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 2, SQL_CHAR, name, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 3, SQL_CHAR, dir, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 4, SQL_CHAR, cast, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 5, SQL_CHAR, release_date, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 6, SQL_CHAR, end, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 7, SQL_CHAR, des, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 8, SQL_CHAR, genre, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 9, SQL_INTEGER, &running_time, 1, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 10, SQL_INTEGER, &price, 1, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 11, SQL_INTEGER, &deleted, 1, &ptrSqlVersion);
			list[count] = Movie(string(m_id), string(name), string(dir), string(cast), string(release_date),string(end), string(des), string(genre), running_time, price, deleted);
			++count;
		}
		for (int i = 0; i < count; i++)
		{
			m.push_back(list[i]);
		}
		
	}
	SQLCancel(sqlStmtHandle);
	return m;
}

vector<Seat> DBHelper::SelectSeat(string room_id)
{
	vector<Seat> s;
	Seat list[1000];
	int count = 0;
	//cout << "\n";
	//cout << "Executing T-SQL query... movie";
	//cout << "\n";
	string str = "SELECT * FROM seat WHERE room_id = '";
	string s1 = "'";
	string strqr = str + room_id + s1;
	const char* ss = strqr.c_str();
	if (SQL_SUCCESS != SQLExecDirectA(sqlStmtHandle, (SQLCHAR*)ss, SQL_NTS)) {
		ShowError(SQL_HANDLE_DBC, sqlStmtHandle);
		cout << "Error querying SQL Server";
		cout << "\n";
		close();
	}
	else {
		//declare output variable and pointer
		SQLINTEGER ptrSqlVersion;
		int id;
		int no;
		char roomid[5];
		int row;
		int status;
		while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS) {
			SQLGetData(sqlStmtHandle, 1, SQL_INTEGER, &id, 1, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 2, SQL_INTEGER, &no, 1, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 3, SQL_CHAR, roomid, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 4, SQL_INTEGER, &row, 1, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 5, SQL_INTEGER, &status, 1, &ptrSqlVersion);
			list[count] = Seat(id,string(roomid),row,no,status);
			++count;
		}
		for (int i = 0; i < count; i++)
		{
			s.push_back(list[i]);
		}
		
	}
	SQLCancel(sqlStmtHandle);
	return s;

}

vector<Room> DBHelper::SelectRoom()
{
	vector<Room> r;
	Room list[1000];
	int count = 0;
	if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLTCHAR*)"SELECT * FROM room", SQL_NTS)) {
		ShowError(SQL_HANDLE_DBC, sqlStmtHandle);
		cout << "Error querying SQL Server";
		cout << "\n";
		close();
	}
	else {
		//declare output variable and pointer
		SQLINTEGER ptrSqlVersion;
		char id[10];
		int no;
		char time[20];
		int status;
		while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS) {
			SQLGetData(sqlStmtHandle, 1, SQL_CHAR, id, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 2, SQL_INTEGER, &no, 1, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 3, SQL_CHAR, time, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 4, SQL_INTEGER, &status, 1, &ptrSqlVersion);
			list[count] = Room(string(id),no,string(time),status);
			++count;
		}
		for (int i = 0; i < count; i++)
		{
			r.push_back(list[i]);
		}
		
	}
	SQLCancel(sqlStmtHandle);
	return r;
}

vector<Customer> DBHelper::SelectCustomer()
{
	vector<Customer> c;
	Customer list[1000];
	int count = 0;
	if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLTCHAR*)"SELECT * FROM Customer", SQL_NTS)) {
		ShowError(SQL_HANDLE_DBC, sqlStmtHandle);
		cout << "Error querying SQL Server";
		cout << "\n";
		close();
	}
	else {
		//declare output variable and pointer
		SQLINTEGER ptrSqlVersion;
		int id;
		char ten[50];
		char add[150];
		char phone[20];
		char email[60];
		while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS) {
			SQLGetData(sqlStmtHandle, 1, SQL_INTEGER, &id,1, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 2, SQL_CHAR, ten, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 3, SQL_CHAR, add, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 4, SQL_CHAR, phone, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 5, SQL_CHAR, email, SQL_RESULT_LEN, &ptrSqlVersion);
			list[count] = Customer(id, ten, add, email, phone);
			++count;
		}
		for (int i = 0; i < count; i++)
		{
			c.push_back(list[i]);
		}
		
	}
	SQLCancel(sqlStmtHandle);
	return c;
}

vector<Ticket> DBHelper::SelectTicket()
{
	vector<Ticket> t;
	Ticket List[1000];
	int count = 0;
	if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLTCHAR*)"SELECT * FROM ticket", SQL_NTS)) {
		ShowError(SQL_HANDLE_DBC, sqlStmtHandle);
		cout << "Error querying SQL Server";
		cout << "\n";
		close();
	}
	else {
		//declare output variable and pointer
		SQLINTEGER ptrSqlVersion;
		int id;
		char machieu[10];
		int c_id;
		int s_id;
		while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS) {
			SQLGetData(sqlStmtHandle, 1, SQL_INTEGER, &id, 1, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 2, SQL_CHAR, machieu, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 3, SQL_INTEGER, &c_id, 1, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 4, SQL_INTEGER, &s_id, 1, &ptrSqlVersion);
			List[count] = Ticket(id, c_id, string(machieu),s_id);
			++count;
		}
		for (int i = 0; i < count; i++)
		{
			t.push_back(List[i]);
		}
		
	}
	SQLCancel(sqlStmtHandle);
	return t;
}

vector<LichChieu> DBHelper::SelectLich()
{
	vector<LichChieu> lc;
	LichChieu list[1000];
	int count = 0;
//	cout << "\n";
//	cout << "Executing T-SQL query... movie";
//	cout << "\n";
	if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLTCHAR*)"SELECT * FROM lichchieu", SQL_NTS)) {
		ShowError(SQL_HANDLE_DBC, sqlStmtHandle);
		cout << "Error querying SQL Server";
		cout << "\n";
		close();
	}
	else {
		//declare output variable and pointer
		SQLINTEGER ptrSqlVersion;
		char id[10];
		char r_id[10];
		char m_id[10];
		char time[30];
		char date[50];
		int deleted;
		while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS) {
			SQLGetData(sqlStmtHandle, 1, SQL_CHAR, id, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 2, SQL_CHAR, r_id, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 3, SQL_CHAR, m_id, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 4, SQL_CHAR, time, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 5, SQL_CHAR, date, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 6, SQL_INTEGER, &deleted, 1, &ptrSqlVersion);
			list[count] = LichChieu(string(id),string(r_id), string(m_id), string(date), string(time), deleted);
			++count;
		}
		for (int i = 0; i < count; i++)
		{
			lc.push_back(list[i]);
		}
		
	}
	SQLCancel(sqlStmtHandle);
	return lc;
}

void DBHelper::ExecuteQuery(const char* str)
{
//	cout << str << endl;
	if (SQL_SUCCESS != SQLExecDirectA(sqlStmtHandle, (SQLCHAR*)str, SQL_NTS)) {
		cout << "\n";
		cout << SQLExecDirectA(sqlStmtHandle, (SQLCHAR*)str, SQL_NTS) << endl;
		cout << SQL_SUCCESS << endl;
		cout << "Error querying SQL Server";
		cout << "\n";
		close();
	}
	else {
//		cout << "\nINSERT SUCCESS\n";
		return;
	}
}

void DBHelper::Update()
{
	if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLTCHAR*)"UPDATE Student SET Id = 'hs1' where Id = 'hs1'", SQL_NTS)) {
		cout << "\n";
		cout << "Error querying SQL Server";
		cout << "\n";
		close();
	}
	else {

		cout << "\nUPDATE SUCCESS";
		return;
	}
}

void DBHelper::Delete(const char* str)
{
	if (SQL_SUCCESS != SQLExecDirectA(sqlStmtHandle, (SQLCHAR*)str, SQL_NTS)) {
		cout << "\n";
		cout << "Error querying SQL Server";
		cout << "\n";
		close();
	}
	else {

		cout << "\nDELETE SUCCESS";
		return;
	}
}

void DBHelper::close()
{
	SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
	SQLDisconnect(sqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, sqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);
//	system("pause");
//	exit(0);
}

void DBHelper::ShowError(unsigned int HandleType, const SQLHANDLE& handle)
{
	SQLTCHAR SQLState[1024];
	SQLTCHAR Message[1024];
	if (SQL_SUCCESS == SQLGetDiagRec(HandleType, handle, 1, SQLState,NULL, Message, 1024,NULL))
	{
		cout << "SQL Driver Message: " << Message << "\nSQL State: " << SQLState << "." << endl;
	}
}

//SQLCHAR							SalesPerson[11];
//SQLINTEGER				SalesPersonLenOrInd, CustIDInd;
//SQLUINTEGER			CustID;
////	Bind	SalesPerson	to	the	parameter	for	the	SalesPerson	column	and
////	CustID	to	the	parameter	for	the	CustID	column.
//SQLBindParameter(hstmt1, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 10, 0, SalesPerson, sizeof(SalesPerson), &SalesPersonLenOrInd);
//SQLBindParameter(hstmt1, 2, SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER, 10, 0, 	&CustID, 0, &CustIDInd);
////	Set	values	of	salesperson	and	customer	ID	and	length/indicators.
//strcpy_s((char*)SalesPerson, _countof(SalesPerson), "Garcia");
//SalesPersonLenOrInd = SQL_NTS;
//CustID = 1331;
//CustIDInd = 0;
////	Execute	a	statement	to	get	data	for	all	orders	made	to	the	specified
////	customer	by	the	specified	salesperson.
//SQLExecDirect(hstmt1, "SELECT	*	FROM	Orders	WHERE	SalesPerson=?	AND	CustID=?", SQL_NTS);
////	Prepare	the	procedure	invocation	statement.
//SQLPrepare(hstmt, "{call	test(?)}", SQL_NTS);
////	Populate	record	1	of	ipd.
//SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,
//	30, 0, szQuote, 0, &cbValue);
////	Get	ipd	handle	and	set	the	SQL_DESC_NAMED	and	SQL_DESC_UNNAMED	fields
////	for	record	#1.
//SQLGetStmtAttr(hstmt, SQL_ATTR_IMP_PARAM_DESC, &hIpd, 0, 0);
//SQLSetDescField(hIpd, 1, SQL_DESC_NAME, "@quote", SQL_NTS);
////	Assuming	that	szQuote	has	been	appropriately	initialized,
////	execute.
//SQLExecute(hstmt);
