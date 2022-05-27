#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;
class Figure
{
public:
	virtual void Input(istream&) = 0;
	virtual float Area() = 0;
	virtual bool Check_through() = 0;
};

class Point
{
private:
	float x, y;
public:
	Point(float a = 0, float b = 0): x(a),y(b) {};
	void Input(istream& inDevice) {
		inDevice >> x;	inDevice >> y;
	}
	float getX() {
		return x;
	}
	float getY() {
		return y;
	}
	void setX(float a) {
		x = a;
	}
	void setY(float b) {
		y = b;
	}
	friend Point& operator+(Point, Point) {};
	friend Point& operator-(Point, Point) {};
	friend float& operator*(Point, Point) {};
};
Point& operator +(Point a, Point b) {
	Point c;
	c.setX(a.getX() + b.getX());
	c.setY(a.getY() + b.getY());
	return c;
}
Point& operator -(Point a, Point b) {
	Point c;
	c.setX(a.getX() - b.getX());
	c.setY(a.getY() - b.getY());
	return c;
}
float& operator*(Point a, Point b) {
	float c = a.getX() * b.getX() - a.getY() * b.getY();
	return c;
}

// Line ax + by = c
class Line {
protected:
	Point a, b;
public:
	float A, B, C;
	Line(Point aa, Point bb):a(aa), b(bb) {
		A = a.getY() - b.getY();
		B = b.getX() - a.getX();
		C = a.getY() * b.getX() - a.getX() * b.getY();
	}
};
// Elipse
class Elipse : public Figure
{
protected:
	float Ra, Rb;
public:
	Point Center;
	Elipse(float a, float b);
	virtual void Input(istream& inDevice);
	virtual float Area();
	virtual bool Horizontal_through();
};

Elipse::Elipse(float a = 0, float b = 0)
{
	Ra = a;		Rb = b;
}

void Elipse::Input(istream& inDevice)
{
	cout << "Nhap kich thuoc: " << endl;
	inDevice >> Ra;		inDevice >> Rb;
	cout << "Nhap toa do: " << endl;
	Center.Input(cin);
}

float Elipse::Area()
{
	return 3.14 * Ra * Rb;
}

bool Elipse::Horizontal_through()
{
	return (abs(this->Center.getY()) - this->Rb <= 0);
}

// Triangle
class Triangle : public Figure
{
private:
	float x1, x2, x3;
public:
	Triangle() {}
	Point p1, p2, p3;
	Triangle(Point p1, Point p2, Point p3);
	void setTriangle(Point p1, Point p2, Point p3);
	virtual float Area();
	virtual void Input(istream& inDevice);
	virtual bool Horizontal_through();
};

Triangle::Triangle(Point p1, Point p2, Point p3)
{
	setTriangle(p1, p2, p3);
}

void Triangle::setTriangle(Point p1, Point p2, Point p3) {
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
	x1 = sqrt(pow(p1.getX() - p2.getX(), 2) + pow(p1.getY() - p2.getY(), 2));
	x2 = sqrt(pow(p1.getX() - p3.getX(), 2) + pow(p1.getY() - p3.getY(), 2));
	x3 = sqrt(pow(p2.getX() - p3.getX(), 2) + pow(p2.getY() - p3.getY(), 2));
}

float Triangle::Area()
{
	float p = x1 + x2 + x3;
	return sqrt(p * (p - x1) * (p - x2) * (p - x3));
}

void Triangle::Input(istream& inDevice)
{
	float x, y;
	cout << "Nhap toa do: " << endl;
	cout << "(x1, ý): ";
	cin >> x >> y;
	p1.SetPoint(x, y);
	cout << "(x2, y2): ";
	cin >> x >> y;
	p2.SetPoint(x, y);
	cout << "(x3, y3): ";
	cin >> x >> y;
	p3.SetPoint(x, y);
	Triangle(p1, p2, p3);
}

bool Triangle::Horizontal_through()
{
	return (p1.getY() <= 0 || p2.getY() <= 0 || p3.getY() <= 0);
}


// Rectangle
class Rectangle : public Figure
{
private:
	float width, height;
public:
	Rectangle() {}
	Point RUpper, LLower;
	Rectangle(Point rUpper, Point lLower);
	void setRectangle(Point rUpper, Point lLower);
	virtual float Area();
	virtual void Input(istream& inDevice);
	virtual bool Horizontal_through();
};

void Rectangle::setRectangle(Point rUpper, Point lLower) {
	RUpper = rUpper;
	LLower = lLower;
	width = abs(RUpper.getX() - LLower.getX());
	height = abs(RUpper.getY() - LLower.getY());
}

Rectangle::Rectangle(Point rUpper, Point lLower)
{
	setRectangle(rUpper, lLower);
}



float Rectangle::Area()
{
	return width * height;
}

void Rectangle::Input(istream& inDevice)
{
	cout << "Nhap toa do: " << endl;
	cout << "Righ upper (x1, y1): ";
	RUpper.Input(cin);
	cout << "Left lower (x2, y2): ";
	LLower.Input(cin);
}

bool Rectangle::Horizontal_through()
{
	return LLower.getY() <= 0;
}

float CountHThrough(vector<Elipse> E, vector<Rectangle> R, vector<Triangle> T) {
	int count = 0;
	for (auto& n : E)
		count += n.Horizontal_through();
	for (auto& n : R)
		count += n.Horizontal_through();
	for (auto& n : E)
		count += n.Horizontal_through();
	return count;
}

void main()
{
	vector<Elipse> E;
	vector<Rectangle> R;
	vector<Triangle> T;
	int choose = -1;
	Elipse etempt;
	Rectangle rtempt;
	Triangle ttempt;
	cout << "Select option create figure below: " << endl;
	cout << "1. Elipse " << endl;
	cout << "2. Rectangle " << endl;
	cout << "3. Triangle " << endl;
	cout << "0. Stop " << endl;
	while (choose != 0) {
		cout << "Your select -> ";
		cin >> choose;
		switch (choose) {
		case 1: {
			etempt.Input(cin);
			E.push_back(etempt);
		}
			  break;
		case 2: {
			rtempt.Input(cin);
			R.push_back(rtempt);
		}
			  break;
		case 3: {
			ttempt.Input(cin);
			T.push_back(ttempt);
		}
			  break;

		}
	}
	cout << "Hoanh do di qua " << CountHThrough(E, R, T) << " diem \n";
	system("pause");
	return;
}

