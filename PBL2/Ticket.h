#pragma once
//#include"Movie.h"
#include<string>
#include<iostream>
#include "LichChieu.h"
#include "Seat.h"
using namespace std;
class LichChieu;
class Ticket
{
private:
    int ticket_id;
    int customer_id;
    string ma_chieu;
    LichChieu* lichchieu;
    int seat_id;
    Seat* ghe;
public:
    Ticket(int =0, int=0, string="", int=0);
    ~Ticket();
    void setLichChieu(LichChieu*);
    LichChieu& getLichChieu();
    void setGhe(Seat*);
    Seat& getGhe();
    int getId();
    int getCustomerId();
    string getMaChieu();
    int getMaGhe();
    int getPrice();
    friend ostream& operator<<(ostream&, const Ticket&);
};