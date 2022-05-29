#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;
bool onSegment(Point p, Point q, Point r)
{
	if (q.getX() <= max(p.getX(), r.getX()) && q.getX() >= min(p.getX(), r.getX()) &&
		q.getY() <= max(p.getY(), r.getY()) && q.getY() >= min(p.getY(), r.getY()))
		return true;

	return false;
}
int orientation(Point p, Point q, Point r)
{
	int val = (q.getY() - p.getY()) * (r.getX() - q.getX()) -
		(q.getX() - p.getX()) * (r.getY() - q.getY());

	if (val == 0) return 0;  // collinear

	return (val > 0) ? 1 : 2; // clock or counterclock wise
}
bool doIntersect(Point p1, Point q1, Point p2, Point q2)
{
	// Find the four orientations needed for general and
	// special cases
	int o1 = orientation(p1, q1, p2);
	int o2 = orientation(p1, q1, q2);
	int o3 = orientation(p2, q2, p1);
	int o4 = orientation(p2, q2, q1);

	// General case
	if (o1 != o2 && o3 != o4)
		return true;

	// Special Cases
	// p1, q1 and p2 are collinear and p2 lies on segment p1q1
	if (o1 == 0 && onSegment(p1, p2, q1)) return true;

	// p1, q1 and q2 are collinear and q2 lies on segment p1q1
	if (o2 == 0 && onSegment(p1, q2, q1)) return true;

	// p2, q2 and p1 are collinear and p1 lies on segment p2q2
	if (o3 == 0 && onSegment(p2, p1, q2)) return true;

	// p2, q2 and q1 are collinear and q1 lies on segment p2q2
	if (o4 == 0 && onSegment(p2, q1, q2)) return true;

	return false; // Doesn't fall in any of the above cases
}

class Figure
{
public:
	virtual void Input(istream&) = 0;
	virtual float Area() = 0;
	virtual bool Check_through(Line line) = 0;
};

class Point
{
private:
	float x, y;
public:
	Point(float a = 0, float b = 0): x(a), y(b) {};
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
	Line(){}
	Line(Point aa, Point bb):a(aa), b(bb) {
		A = a.getY() - b.getY();
		B = b.getX() - a.getX();
		C = a.getY() * b.getX() - a.getX() * b.getY();
	}
	Point getPointS() {
		return a;
	}
	Point getPointE() {
		return b;
	}
	float distance() {
		return sqrt(pow(b.getX() - a.getX(), 2) + pow(b.getY() - a.getY(), 2));
	}
};

// Circle
class Circle:public Figure 
{ 
protected:
	float R;
public:
	Point I;
	Circle(float Rx);
	virtual void Input(istream& inDevice);
	virtual float Area();
	virtual bool Check_through(Line line);
};

Circle::Circle(float Rx = 0) {
	R = Rx;
}

void Circle::Input(istream& inDevice) {
	cout << "Nhap ban kinh hinh tron: " << endl;
	inDevice >> R;
	cout << "Nhap toa do hinh tron: " << endl;
	I.Input(cin);
}

float Circle::Area() {
	return R * R * 3.14;
}

bool Circle::Check_through(Line line) {
	float LAB = line.distance();
	// compute the direction vector D from A to B
	float Dx = (line.getPointE().getX() - line.getPointS().getX()) / LAB;
	float Dy = (line.getPointE().getY() - line.getPointS().getY()) / LAB;
	// the equation of the line AB is x = Dx*t + Ax, y = Dy*t + Ay with 0 <= t <= LAB.
	// compute the distance between the points A and E, where
	// E is the point of AB closest the circle center (Cx, Cy)
	float t = Dx * (I.getX() - line.getPointS().getX()) + Dy*(I.getY() - line.getPointS().getY());
	// compute the coordinates of the point E
	float Ex = t * Dx + line.getPointS().getX();
	float Ey = t * Dy + line.getPointS().getY();
	// compute the euclidean distance between E and C
	Line temp({ Ex, Ey }, I);
	float LEC = temp.distance();
	if (LEC < R) return true;
	return false;
}
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
	virtual bool Check_through(Line line);
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

bool Elipse::Check_through(Line line)
{
	
}

// Triangle
class Triangle : public Figure
{
private:
	float x1, x2, x3;
public:
	Triangle() {};
	Point p1, p2, p3;
	Triangle(Point p1, Point p2, Point p3);
	void setTriangle(Point p1, Point p2, Point p3);
	virtual float Area();
	virtual void Input(istream& inDevice);
	virtual bool Check_through(Line line);
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
	cout << "(x1, y1): ";
	cin >> x >> y;
	p1.setX(x);
	p1.setY(y);
	cout << "(x2, y2): ";
	cin >> x >> y;
	p2.setX(x);
	p2.setY(y);
	cout << "(x3, y3): ";
	cin >> x >> y;
	p3.setX(x);
	p3.setY(y);
	Triangle t;
	t.setTriangle(p1, p2, p3);
}

bool Triangle::Check_through(Line line)
{
	bool AB = doIntersect(line.getPointS(), line.getPointE(), p1, p2);
	bool AC = doIntersect(line.getPointS(), line.getPointE(), p1, p3);
	bool BC = doIntersect(line.getPointS(), line.getPointE(), p2, p3);
	if (AB || AC || BC) {
		return true;
	}
	return false;
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
	virtual bool Check_through(Line line);
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

bool Rectangle::Check_through(Line line)
{	
	Point p1(LLower.getX(), LLower.getY() + height);
	Point p2 = LLower;
	Point p3(RUpper.getX(), RUpper.getY() - height);
	Point p4 = RUpper;
	bool left = doIntersect(line.getPointS(), line.getPointE(), p1, p2);
	bool right = doIntersect(line.getPointS(), line.getPointE(), p3, p4);
	bool top = doIntersect(line.getPointS(), line.getPointE(), p1, p4);
	bool bottom = doIntersect(line.getPointS(), line.getPointE(), p2, p3);
	if (left || right || top || bottom) {
		return true;
	}
	return false;
}

float CountHThrough(vector<Elipse> E, vector<Rectangle> R, vector<Triangle> T , Line line) {
	int count = 0;
	for (auto& n : E)
		count += n.Check_through(line);
	for (auto& n : R)
		count += n.Check_through(line);
	for (auto& n : T)
		count += n.Check_through(line);
	return count;
}

void main()
{	
	Line l;
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

	cout << "Hoanh do di qua " << CountHThrough(E, R, T, l) << " diem \n";
	system("pause");
	return;
}

