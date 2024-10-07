//simple program to generate point files to use in the file_distance_calc.cpp program 

#include <iostream>
#include <fstream>
using namespace std;

int main (void)
{
	int total_cords;

	srand(time(NULL)); //sets seed

	cout << "Enter how many cordinates you want: ";
	cin >> total_cords;

	//cout << total_cords;

	ofstream cordfile ("point_file.txt");

	cordfile << total_cords << endl;

	for (int i = 0; i < total_cords; i++)
	{
		cordfile << rand() % 500 << " " << rand() % 500 << "\n";
	}

	return 0;
}
