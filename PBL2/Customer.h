#pragma once
#include<iostream>
#include<string>
#include<vector>
#include "Ticket.h"
#include "DBHelper.h"
using namespace std;
class Ticket;
class Customer
{
private:
    int customer_id;
    string customer_name;
    string address;
    string phone_no;
    string email_id;
    vector<Ticket> ticket;
public:
    Customer();
    Customer(int, string, string, string, string);
    void setCustomer_id(int);
    int getCustomer_id();
    void setTicket(vector<Ticket>);
    int Search(int); //tim theo id
    Ticket& getTicketAt(int); //throw int
    void setTen(string);
    void setDiaChi(string);
    void setSDT(string);
    void setEmail(string);
    string getEmail();
    void showTicket();
    vector<Ticket> getTicket();
    void AddTicket(Ticket&);
    friend ostream& operator<<(ostream&, const Customer&);
};