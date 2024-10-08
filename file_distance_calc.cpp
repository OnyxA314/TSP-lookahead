//like distance calc but gets x distances from a file, then calcualtes how far each is
//file should have first line say how many points in the file, then each line after that has 2 numbers seperated by a space. first number is xcord of the point, second number is the ycord of the point



/*****************************import hell ********************************/
#include <iostream>
#include <fstream>
#include <cmath> 
#include <vector> //Vectors my beloved
#include <utility> //for ::pair to store 2D cords. first time using this

using namespace std; //NOTE THIS HAS TO GO BEFORE ALL FUNCTIONS, TOOK ME WAY TO LONG TO FIGURE THAT OUT
		


/**************************function hell *********************************/
void all_distance_calculation(vector<pair<double, double>> cords);
void calc_two_step (vector<pair<double, double>> cords);


//using namespace std;

int main (void)
{
	vector<pair<double, double>> cords; //creates a vector of pairs called cords of the form (double, double) 
	double x, y;	

	int total_points;

	ifstream point_file ("point_file.txt");

	
	point_file >> total_points; //gets total points from the first line in the input file
	
	//cout << total_points << endl;


	for (int i = 0; i < total_points; i++) //as long as there are points to be calculated (gotten from first line of .txt file does the code)
	{
		//gets the x, y points for each point
		point_file >> x;
		point_file >> y;

		cords.push_back(make_pair(x, y)); //adds the cordinate pair to the vector 'cords'
	}




	//code to simply make sure all cords were gotten correctly. no longer needed uncommented, keeping incase future bugs
	/*	
	for (auto cord : cords) //prints out every single cordinate gotten from file. really just a trouble shooting step to make sure everything works
	{
		cout << "Cordinate: " << cord.first << ", " << cord.second << "\n";
	}
	cout << "\n\n\n"; //code to seperate making sure we got the points to the actual math
	*/



	//gets the distances between every point
	all_distance_calculation(cords);


	//calculate 2-step optimal.if this works i'll eat my sock
	calc_two_step(cords);


	return 0;	
}







void all_distance_calculation(vector<pair<double, double>> cords)
{
	int node_tracker = 0;


	//NOTE: we can make this even faster. we can only check x and y points and see if those are greater than 3 shortest already known.
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


			//cout << "Node " << node_tracker << " to " << inner_node_tracker << " has distance: " << distance << endl;	//prints out the distance from every point
			inner_node_tracker++;
			
		}

		cout << "\nTHE SHORTEST DISTANCES FROM NODE " << node_tracker <<":\n";
		cout << "Node " << first_shortest_node << " with distance " << first_shortest << endl;
		cout << "Node " << second_shortest_node << " with distance " << second_shortest << endl;
		cout << "Node " << third_shortest_node << " with distance " << third_shortest << endl;

		node_tracker++;

		cout << endl << endl;
	}


	return;
}





//I hope one day I can be forgiven for writting this code
void calc_two_step (vector<pair<double, double>> cords)
{

	//code to attempt to see the 2 step path
	//	i.e. node 0 says 3 optimal path. then from those 3 optimal nodes go 3 more out farther for a total 12 calculations
	
	
	int node_tracker = 0;

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


			//cout << "Node " << node_tracker << " to " << inner_node_tracker << " has distance: " << distance << endl;	//prints out the distance from every point
			inner_node_tracker++;
			
		}

		cout << "\nTHE SHORTEST DISTANCES FROM NODE " << node_tracker <<":\n";
		cout << "Node " << first_shortest_node << " with distance " << first_shortest << endl;
		cout << "Node " << second_shortest_node << " with distance " << second_shortest << endl;
		cout << "Node " << third_shortest_node << " with distance " << third_shortest << endl;



        	double new_xinit = cords[first_shortest_node].first;
        	double new_yinit = cords[first_shortest_node].second;





		//NEW STUFF AS PART OF THIS FUNCTION. 
	

		cout << "\nCalculating 3 shortest distances from the first shortest node (Node " << first_shortest_node << "):\n";

		// Re-initialize shortest variables
		float new_first_shortest = 999999999, new_second_shortest = 999999999, new_third_shortest = 999999999;
		int new_first_shortest_node, new_second_shortest_node, new_third_shortest_node;
		int new_inner_tracker = 0;

		for (auto cord3 : cords) 
		{
			double x3 = cord3.first;
        		double y3 = cord3.second;
		
        		double new_distance = sqrt(pow(x3 - new_xinit, 2) + pow(y3 - new_yinit, 2));  // Calculate distance from node 3

        		if (new_xinit == x3 && new_yinit == y3) 
			{
            			// Skip the current point
           		} 
			else if (new_distance < new_first_shortest) 
			{
                		new_third_shortest = new_second_shortest;
                		new_third_shortest_node = new_second_shortest_node;

                		new_second_shortest = new_first_shortest;
               			new_second_shortest_node = new_first_shortest_node;

                		new_first_shortest = new_distance;
               			new_first_shortest_node = new_inner_tracker;
			} 
			
			else if (new_distance < new_second_shortest) 
			{
             			new_third_shortest = new_second_shortest;
                		new_third_shortest_node = new_second_shortest_node;

                		new_second_shortest = new_distance;
                		new_second_shortest_node = new_inner_tracker;
            		} 
			else if (new_distance < new_third_shortest) 
			{
               			new_third_shortest = new_distance;
                		new_third_shortest_node = new_inner_tracker;
            		}
           
			new_inner_tracker++;
        
		}

        // Display the 3 shortest distances from the first shortest node
        cout << "Node " << new_first_shortest_node << " with distance " << new_first_shortest << endl;
        cout << "Node " << new_second_shortest_node << " with distance " << new_second_shortest << endl;
        cout << "Node " << new_third_shortest_node << " with distance " << new_third_shortest << endl;





		node_tracker++;

		cout << endl << endl;
	}





	return;
}
