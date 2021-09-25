#include "Customer.h"

#include<vector>
#include "Movie.h"

Customer::Customer()
{
    this->customer_id = 0 ;
    this->customer_name = "";
    this->address = "";
    this->email_id = "";
    this->phone_no= "";
}

Customer::Customer(int customer_id, string customer_name, string address, string email_id, string phone_no)
{
    this->customer_id = customer_id ;
    this->customer_name = customer_name;
    this->address = address;
    this->email_id = email_id;
    this->phone_no= phone_no;
}


void Customer::setCustomer_id(int customer_id)
{
    this->customer_id = customer_id ;
}

int Customer::getCustomer_id()
{
    return this->customer_id;
}

void Customer::setTicket(vector<Ticket> t)
{
    this->ticket = t;
}

string Customer::getEmail()
{
    return this->email_id;
}

int Customer::Search(int t_id)
{
    int n = this->ticket.size();
    for (int i = 0; i < n; i++)
    {
        if (this->ticket[i].getId() == t_id)
            return i;
    }
    return -1;
}

Ticket& Customer::getTicketAt(int index)
{
    if (index >= 0 && index < this->ticket.size()) {
        return this->ticket[index];
    }
    else throw - 1;
}

void Customer::setTen(string ten)
{
    this->customer_name = ten;
}

void Customer::setDiaChi(string dc)
{
    this->address = dc;
}

void Customer::setSDT(string sdt)
{
    this->phone_no = sdt;
}

void Customer::setEmail(string e)
{
    this->email_id = e;
}

void Customer::showTicket()
{
    int n = this->ticket.size();
    cout << "Cac ve da dat: " << endl;
    for (int i = n-1; i >= 0; i--)
    {
        cout << this->ticket[i];
        cout << "----------------------------------------------------------------------" << endl;
    }
}

vector<Ticket> Customer::getTicket()
{
    
}

void Customer::AddTicket(Ticket& t)
{
    this->ticket.push_back(t);
}

ostream& operator<<(ostream& o, const Customer& c)
{
    o << "Ten: " << c.customer_name << endl
        << "Dia chi: " << c.address << endl
        << "SDT: " << c.phone_no << endl
        << "Email: " << c.email_id << endl;
    return o;
}
