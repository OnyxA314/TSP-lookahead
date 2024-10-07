//the code to calculate distance from points, the core of the TSP

#include <iostream>
#include <cmath>

using namespace std;

int main (void)
{
	double pointax, pointay;
	double pointbx, pointby;

	double distance;


	cout << "Enter the X cordinate of the first point: ";
	cin >> pointax;
	cout << "Enter the Y cordinate of the first point: ";
	cin >> pointay;

	cout << "Enter the X cordinate of the second point: ";
	cin >> pointbx;
	cout << "Enter the Y cordinate of the second point: ";
	cin >> pointby;

	cout << "X: " << pointax << ", " << pointay << endl;
	cout << "Y: " << pointbx << ", " << pointby << endl;


	distance = sqrt(pow(pointbx - pointax, 2) + pow(pointby - pointay, 2));

	cout << "Distance: " << distance << endl;

	return 0;
}
