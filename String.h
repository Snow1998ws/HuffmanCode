#pragma once
#include<cstdio>
#include<iostream>
#include<list>
#pragma warning(disable:4996)
class String
{
protected:
	char* Val;
	int length;
public:
	String() {};
	~String() {};
	String(const String& copy);
	String(const char* copy);
	int Length() const;
	String &operator= (const String& copy);
	const char* CStr() const;
	int Index(const String& a);
	char operator [](int pos) const;
	char* Concat(String& str);
};


String::String(const String & copy)
{
	length = strlen(copy.CStr());
	Val = new char[length + 1];
	strcpy(Val, copy.Val);
}

String::String(const char * copy)
{
	length = strlen(copy);
	Val = new char[length + 1];
	strcpy(Val, copy);
}

int String::Length() const
{
	return strlen(Val);
}

String & String::operator=(const String & copy)
{
	//delete[] Val;
	char* val;
	length = strlen(copy.CStr());
	val = new char[length + 1];
	strcpy(val, copy.CStr());
	Val = val;
	return *this;
}


const char * String::CStr() const
{
	return (const char*)Val;
}

int String::Index(const String& a)
{
	int i = 0, j = 0;
	while (i < this->Length() && j < a.Length())
	{
		if (this->CStr()[i] == a.CStr()[j])
		{
			i++;
			j++;
		}
		else
		{
			i = i - j + 1;
			j = 0;
		}
	}
	if (j >= a.Length())
		return i - j;
	else
		return -1;
}

char  String::operator[](int pos) const
{
	 return Val[pos];
}

char* String::Concat(String & str)
{
	char *a = new char[this->Length() + str.Length()];
	int i;
	for (i = 0; i < this->Length(); i++)
		a[i] = Val[i];
	for (i = this->Length(); i < this->Length() + str.Length(); i++)
		a[i] = str[i - this->Length()];
	a[i + 1] = '\0';
	return a;
}
