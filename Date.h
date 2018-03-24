#include<iostream>
using namespace std;

#include<assert.h>

class Date
{
private:
	int _year;
	int _month;
	int _day;
public:
	Date(int, int, int);
	Date(const Date& d);
	bool operator<(const Date& d);
	bool operator>(const Date& d);
	bool operator<=(const Date& d);
	bool operator>=(const Date& d);
	bool operator==(const Date& d);
	bool operator!=(const Date& d);
	Date operator+(int d);
	Date operator-(int d);
	int operator-(Date& d);
	void Show();
};
Date::Date(int year = 1990, int month = 1, int day = 1)
{
	_year = year;
	_month = month;
	_day = day;
}

Date::Date(const Date& d)
{
	_year = d._year;
	_month = d._month;
	_day = d._day;
}

void Date::Show()
{
	cout << _year << "-" << _month << "-" << _day << endl;
}

bool Date::operator<(const Date& d)
{
	if ((_year < d._year) ||
		(_year == d._year&&_month < d._month) ||
		(_year == d._year&&_month == d._month&&_day < d._day))
		return true;
	else
		return false;
}

bool Date::operator<=(const Date& d)
{
	return !(operator>(d));
}

bool Date::operator>(const Date& d)
{
	if ((_year > d._year) ||
		(_year == d._year&&_month > d._month) ||
		(_year == d._year&&_month == d._month&&_day > d._day))
		return true;
	else
		return false;
}

bool Date::operator>=(const Date& d)
{
	return !(operator<(d));
}

bool Date::operator==(const Date& d)
{
	if ((_year == d._year) && (_month == d._month) && (_day == d._day))
		return true;
	else
		return false;
}

bool Date::operator!=(const Date& d)
{
	return !(operator==(d));
}

int GetMonthDays(int year, int month)
{
	//1 3 5 7 8 10 12  31
	//4 6 9 11 30
	int _month[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
	{
		_month[2] += 1;
	}
	return month[_month];
}

Date Date::operator+(int d)
{
	Date ret(*this);
	ret._day = _day + d;
	while (ret._day > GetMonthDays(ret._year, ret._month))
	{
		ret._day -= GetMonthDays(ret._year, ret._month);
		ret._month++;
		if (ret._month > 12)
		{
			ret._year += 1;
			ret._month = 1;
		}
	}
	return ret;
}

Date Date::operator-(int d)
{
	Date ret(*this);
	ret._day -= d;
	while (ret._day < 0)
	{
		ret._day += GetMonthDays(ret._year, ret._month);
		ret._month--;
		if (ret._month == 0)
		{
			ret._year--;
			ret._month = 12;
		}
	}
	return ret;
}

int Date::operator-(Date& d)
{
	Date max = *this;
	Date min = d;
	if (operator<(d))//�ҳ��ϴ�����
	{
		max = d;
		min = *this;
	}
	int count = max._day-min._day;//�������֮���������㲻��ǣ��
	while ((max._year != min._year)||(max._month != min._month))//max��Ӧ���ꡢ�¼�����minһ��ʱ������ѭ��
	{
		int day = GetMonthDays(max._year, max._month);//����Ӧ�µ�����
		count=count+day;//���϶�Ӧ����
		max._month--;
		if (max._month == 0)
		{
			max._year--;
			max._month = 12;
		}
	}
	return count;
}


void Test()
{
	Date d1;
	Date d2(2018, 3, 24);
	Date d3(d2);
	Date d4(2023,7,16);
	cout << "d1: ";
	d1.Show();
	cout << "d2: ";
	d2.Show();
	cout << "d3: ";
	d3.Show();
	cout << "d4: ";
	d4.Show();
	cout << "------------------------" << endl;
	cout << "d1<d2? " << (d1 < d2) << endl;
	cout << "d1>=d2? " << (d1 >= d2) << endl;
	cout << "d1==d2? " << (d1 == d2) << endl;
	cout << "d1!=d2? " << (d1 != d2) << endl;
	cout << "d2>=d3? " << (d2 >= d3) << endl;
	cout << "d2<=d3? "<< (d2 <= d3) << endl;
	cout << "------------------------" << endl;
	Date ret = d3 + 100;
	cout << "d3+100��: ";
	ret.Show();
	ret = d3 - 100;
	cout << "d3-100��: ";
	ret.Show();
	cout << "d2-d4�� " << (d2 - d4)<<"��" << endl; 
}