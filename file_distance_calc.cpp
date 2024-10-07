//like distance calc but gets x distances from a file, then calcualtes how far each is
//file should have first line say how many points in the file, then each line after that has 2 numbers seperated by a space. first number is xcord of the point, second number is the ycord of the point


#include <iostream>
#include <fstream>
#include <cmath> 
#include <vector> //Vectors my beloved
#include <utility> //for ::pair to store 2D cords. first time using this


using namespace std;

int main (void)
{
	vector<pair<double, double>> cords; //creates a vector of pairs called cords of the form (double, double) 
	double x, y;	

	int total_points;


	//TODO: ask for userinput on what file to use. user enters number, such as 2, and then the program uses point_file_x.txt with x being the userinput. allows easier testing
	ifstream point_file ("point_file_1.txt");

	
	point_file >> total_points; //gets total points from the first line in the input file
	
	cout << total_points << endl;


	for (int i = 0; i < total_points; i++) //as long as there are points to be calculated (gotten from first line of .txt file does the code)
	{
		//gets the x, y points for each point
		point_file >> x;
		point_file >> y;

		cords.push_back(make_pair(x, y)); //adds the cordinate pair to the vector 'cords'
	}
	
	for (auto cord : cords) //prints out every single cordinate gotten from file. really just a trouble shooting step to make sure everything works
	{
		cout << "Cordinate: " << cord.first << ", " << cord.second << "\n";
	}
	cout << "\n\n\n"; //code to seperate making sure we got the points to the actual math


	//TODO: this can be simplified. right now it calculates every point when we can simplify this. we are assuming x -> y is the same as y -> x. we can create code to prevent recalculation
	for (auto cord : cords) //for every cordinate we have
	{
		double xinit = cord.first;	//initially set the x cordinate to current x cordinate we are at
		double yinit = cord.second;	//initially set the y cordinate to current y cordinate we are at

		for (auto cord2 : cords)
		{
			double x2 = cord2.first;	//gets new cordinates for every point
			double y2 = cord2.second;

			double distance = sqrt(pow(x2 - xinit, 2) + pow(y2 - yinit, 2));	//calculates distance from initial point to every other point

			cout << distance << endl;	//prints out the distance from every point
		}
		
		cout << endl << endl;
	}


	return 0;	
}
