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

	int node_tracker = 0; //keep track what node currently on
	
	char filler; //filler to make program temp pause until user presses enter

	ifstream point_file ("point_file.txt");

	
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

	

	//TODO: we can make this even faster. we can only check x and y points and see if those are greater than 3 shortest already known.
	//	if they x and y points are greater we know the distance is greater so we don't have to waste time doing the math to already figure out what we know.
	//	i.e. at point (0,0) we know point (5,1) is going to be closer than (6, 2) because the x and y is greater both greater. 
	
	//TODO: this can be simplified. right now it calculates every point when we can simplify this. we are assuming x -> y is the same as y -> x. we can create code to prevent recalculation
	for (auto cord : cords) //for every cordinate we have
	{
		double xinit = cord.first;	//initially set the x cordinate to current x cordinate we are at
		double yinit = cord.second;	//initially set the y cordinate to current y cordinate we are at
		
		//creates 3 shortest variables and sets them to virtual infinity for testing
		float first_shortest, second_shortest, third_shortest;
		first_shortest = 999999999;
		second_shortest = 999999999;
		third_shortest = 999999999;

		float first_shortest_node, second_shortest_node, third_shortest_node;
		int inner_node_tracker = 0;	
		
		cout << "Current Node: " << node_tracker << endl;

		for (auto cord2 : cords)
		{
			
			double x2 = cord2.first;	//gets new cordinates for every point
			double y2 = cord2.second;

			double distance = sqrt(pow(x2 - xinit, 2) + pow(y2 - yinit, 2));	//calculates distance from initial point to every other point
		
			
			if(xinit == x2 && yinit == y2)
			{
				//this is testing to see if we are on the point we are currently measuing. if we are skip testing to see if it's shorter as the distance from itself is 0
			}			
			else if (distance < first_shortest)
			{
				first_shortest = distance;
				first_shortest_node = inner_node_tracker;
			}
			else if (distance < second_shortest)
			{
				second_shortest = distance;
				second_shortest_node = inner_node_tracker;
			}
			else if (distance < third_shortest)
			{
				third_shortest = distance;
				third_shortest_node = inner_node_tracker;
			}


			cout << "Node " << node_tracker << " to " << inner_node_tracker << " has distance: " << distance << endl;	//prints out the distance from every point
			inner_node_tracker++;
			
		}

		cout << "\nTHE SHORTEST DISTANCES FROM NODE " << node_tracker <<":\n";
		cout << "Node " << first_shortest_node << " with distance " << first_shortest << endl;
		cout << "Node " << second_shortest_node << " with distance " << second_shortest << endl;
		cout << "Node " << third_shortest_node << " with distance " << third_shortest << endl;
		//cout << "Press enter to continue";
		//cin >> filler;

		node_tracker++;

		cout << endl << endl;
	}


	return 0;	
}
