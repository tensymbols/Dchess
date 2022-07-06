#pragma once

struct Pos {
	int x;
	int y;
	Pos operator + (Pos const& obj);
	Pos operator - (Pos const& obj);
	Pos operator +=(Pos const& obj);
	Pos operator -=(Pos const& obj);
	bool operator ==(Pos const& obj);
	Pos operator = (Pos const& obj);
	Pos operator * (int);
	Pos operator / (int k);
	Pos operator /= (int k);
	Pos opposite() {
		return { -x, -y };
	}
	Pos opposite(Pos pos) {
		return { -pos.x, -pos.y };
	}
};

inline Pos Pos::operator + (Pos const& obj) {
	Pos temp;
	temp.x = this->x + obj.x;
	temp.y = this->y + obj.y;
	return temp;

}
inline Pos Pos::operator - (Pos const& obj) {
	Pos temp;
	temp.x= this->x - obj.x;
	temp.y= this->y - obj.y;
	return temp;
}

inline Pos Pos::operator +=(Pos const& obj) {
	*this = *this + obj;
	return *this;
}

inline Pos Pos::operator -=(Pos const& obj) {
	*this = *this - obj;
	return *this;
}

inline Pos Pos::operator = (Pos const& obj) {
	this->x = obj.x;
	this->y = obj.y;
	return *this;
}
inline Pos Pos::operator *(int num)
{
	this->x = x * num;
	this->y = y * num;
	return *this;
}

inline Pos Pos::operator/(int k)
{
	this->x = x / k;
	this->y = y / k;
	return *this;
}

inline Pos Pos::operator/=(int k)
{
	int x_ = x / k;
	int y_ = y / k;
	Pos temp = { x_,y_ };
	return temp;
}

inline bool Pos::operator==(Pos const& obj)
{
	return this->x == obj.x && this->y == obj.y;
}
