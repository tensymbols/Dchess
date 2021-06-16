#pragma once

struct Pos {
	int x;
	int y;
	Pos operator + (Pos const& obj);
	Pos operator - (Pos const& obj);
	Pos operator +=(Pos const& obj);
	bool operator ==(Pos const& obj);
	Pos operator = (Pos const& obj);
	Pos operator * (int );

};

inline Pos Pos::operator + (Pos const& obj){
	this->x += obj.x;
	this->y += obj.y;
	return *this;
}
inline Pos Pos::operator - (Pos const& obj) {
	this->x -= obj.x;
	this->y -= obj.y;
	return *this;
}

inline Pos Pos::operator +=(Pos const& obj) {
	Pos temp = *this + obj;
	return temp;
}
inline Pos Pos::operator = (Pos const& obj) {
	this->x = obj.x;
	this->y = obj.y;
	return *this;
}
inline Pos Pos::operator *(int num)
{
	this->x *= num;
	this->y *= num;
	return *this;
}

inline bool Pos::operator==(Pos const& obj)
{ 
	return this->x == obj.x && this->y == obj.y;
}
