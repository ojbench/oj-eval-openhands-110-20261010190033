#include <bits/stdc++.h>
using namespace std;

static const int month_days_norm[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

bool isLeap(int y){
    return (y%400==0) || (y%4==0 && y%100!=0);
}

int daysInMonth(int y,int m){
    if(m==2) return isLeap(y)?29:28;
    return month_days_norm[m];
}

// Convert date to days since 1900-01-01 (day 0)
long long dateToDays(int y,int m,int d){
    long long days=0;
    for(int year=1900; year<y; ++year){
        days += isLeap(year)?366:365;
    }
    for(int month=1; month<m; ++month){
        days += daysInMonth(y, month);
    }
    days += d-1; // days offset
    return days;
}

void daysToDate(long long days, int &y,int &m,int &d){
    y=1900;
    while(true){
        int yearDays = isLeap(y)?366:365;
        if(days>=yearDays){
            days-=yearDays;
            ++y;
        }else break;
    }
    m=1;
    while(true){
        int md = daysInMonth(y,m);
        if(days>=md){
            days-=md;
            ++m;
        }else break;
    }
    d = (int)days + 1;
}

class Date{
private:
    int _year,_month,_day;
    void normalize(){
        // ensure valid date; if invalid set to default 1900-1-1
        if(_year<1900 || _year>2030){
            _year=1900; _month=1; _day=1; return;
        }
        if(_month<1 || _month>12){
            _year=1900; _month=1; _day=1; return;
        }
        int dim = daysInMonth(_year,_month);
        if(_day<1 || _day>dim){
            _year=1900; _month=1; _day=1; return;
        }
    }
public:
    Date():_year(1900),_month(1),_day(1){}
    Date(int y,int m,int d):_year(y),_month(m),_day(d){ normalize(); }
    // pre ++
    Date& operator++(){
        long long days = dateToDays(_year,_month,_day);
        ++days;
        daysToDate(days,_year,_month,_day);
        return *this;
    }
    // post ++
    Date operator++(int){
        Date tmp=*this;
        ++(*this);
        return tmp;
    }
    // pre --
    Date& operator--(){
        long long days = dateToDays(_year,_month,_day);
        --days;
        daysToDate(days,_year,_month,_day);
        return *this;
    }
    // post --
    Date operator--(int){
        Date tmp=*this;
        --(*this);
        return tmp;
    }
    // + days
    Date operator+(int add) const{
        long long days = dateToDays(_year,_month,_day);
        days += add;
        int y,m,d; daysToDate(days,y,m,d);
        return Date(y,m,d);
    }
    // - days
    Date operator-(int sub) const{
        long long days = dateToDays(_year,_month,_day);
        days -= sub;
        int y,m,d; daysToDate(days,y,m,d);
        return Date(y,m,d);
    }
    // date - date => days difference absolute
    long long operator-(const Date& other) const{
        long long a = dateToDays(_year,_month,_day);
        long long b = dateToDays(other._year, other._month, other._day);
        return llabs(a-b);
    }
    // less than
    bool operator<(const Date& other) const{
        if(_year!=other._year) return _year<other._year;
        if(_month!=other._month) return _month<other._month;
        return _day<other._day;
    }
    // output
    friend ostream& operator<<(ostream& os, const Date& dt){
        os<<dt._year<<"-"<<dt._month<<"-"<<dt._day;
        return os;
    }
    // optional out() function
    void out() const{ cout<<_year<<"-"<<_month<<"-"<<_day<<"\n"; }
};

void Test(){
    int op; if(!(cin>>op)) return; // no input
    int yy,mm,dd;
    if(op==1 || op==0){
        Date d0;
        Date d1(2000,2,29);
        Date d2(1900,2,29);
        cout<<d0<<"\n"<<d1<<"\n"<<d2<<"\n";
    }
    if(op==2 || op==0){
        cin>>yy>>mm>>dd;
        Date d0(yy,mm,dd);
        for(int i=0;i<5;++i) cout<<++d0<<"\n";
        for(int i=0;i<5;++i) cout<<d0++<<"\n";
        for(int i=0;i<5;++i) cout<<d0--<<"\n";
        for(int i=0;i<2;++i) cout<<--d0<<"\n";
        cout<<d0<<"\n";
    }
    if(op==3 || op==0){
        cin>>yy>>mm>>dd;
        Date d0(yy,mm,dd);
        cout<<d0+100<<"\n";
        cout<<d0-1000<<"\n";
    }
    if(op==4 || op==0){
        cin>>yy>>mm>>dd;
        Date d0(yy,mm,dd);
        Date d1(2020,12,21);
        cout<<(d0<d1)<<"\n";
    }
    if(op==5 || op==0){
        cin>>yy>>mm>>dd;
        Date d0(yy,mm,dd);
        Date d1(1912,6,23);
        cout<<d0-d1<<"\n";
    }
}

int main(){
    Test();
    return 0;
}
