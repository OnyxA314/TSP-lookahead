//like distance calc but gets x distances from a file, then calcualtes how far each is
//file should have first line say how many points in the file, then each line after that has 2 numbers seperated by a space. first number is xcord of the point, second number is the ycord of the point



/*****************************import hell ********************************/
#include <iostream>
#include <fstream>
#include <cmath> 
#include <vector> //Vectors my beloved
#include <utility> //for ::pair to store 2D cords. first time using this
#include <algorithm> //for sort()

using namespace std; //NOTE THIS HAS TO GO BEFORE ALL FUNCTIONS, TOOK ME WAY TO LONG TO FIGURE THAT OUT
		


/**************************function hell *********************************/
void all_distance_calculation(vector<pair<double, double>> cords);
void calc_two_step (vector<pair<double, double>> cords);
void making_distance_matrix (vector <pair <double, double>> cords, vector<vector<double>> &distance_matrix, vector <vector <pair <double, int>>> &shortest_nodes);

//using namespace std;

int main (void)
{
	vector<pair<double, double>> cords; //creates a vector of pairs called cords of the form (double, double) 
	double x, y;	


	//creates a vector of bools to see if we visited a node. node 0 has pos 0. node 29 has pos 29, etc etc.
	vector<bool> visited_point;




	int total_points;

	ifstream point_file ("point_file.txt");

	
	point_file >> total_points; //gets total points from the first line in the input file
	


	//create a vector of nxn where n is the total amount of points
	vector <vector <double>> distance_matrix(total_points, vector<double>(total_points));



	//2D array to hold the k shortest nodes for every given point. used to make some calculation easier. overall will be an nxk array
	//NOTE: might make this nxn vector to hold all nodes in the sorted order. don't know how expensive it will be nor how benefitial it will be
	//this creates an nxn vector of shortest_nodes.
	//this vector has a pair of the shortest nodes and the distance that node has
	//
	//
	vector <vector <pair <double, int>>> shortest_nodes (total_points, vector <pair <double, int>>(total_points));;
	//vector <vector <double>> shortest_nodes(total_points, vector<double>(total_points));
	


/*
	//initializes distance matrix. point to itself is 0, otherwise set distance to virtual infinity
	for(int i = 0; i < total_points; i++)
	{
		for (int j = 0; j < total_points; j++)
		{
			if (i == j)
			{
				distance_matrix[i][j] = 0;
			}
			else
			{
				distance_matrix[i][j] = 999999999; //dont really need to do this but oh well
			}
		}
	}
*/


/*
	//testing out I made the 2D vector correct
	for (int i = 0; i < total_points; i++)
	{
		cout << "Node: " << i << endl;
		for (int j = 0; j < total_points; j++)
		{
			cout << distance_matrix[i][j] << endl;
		}

		cout << endl;
	}
*/



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
	//was a testingpoint until I got calc_two_step(cords) working
	//all_distance_calculation(cords);


	making_distance_matrix(cords, distance_matrix, shortest_nodes);



	//testing out I made the 2D vector correct
	for (int i = 0; i < total_points; i++)
	{
		cout << "Node: " << i << endl;
		for (int j = 0; j < total_points; j++)
		{
			cout << distance_matrix[i][j] << endl;
		}

		cout << endl;
	}





	//printing out the (hopefully) sorted shortest_node vectors
	for (int i = 0; i < total_points; i++)
	{
		cout << "Node: " << i << endl;
		for (int j = 1; j < total_points; j++) //doesn't check first point as first point is itself so it will always be the shortest
		{
			cout << shortest_nodes[i][j].second << " ";
		}
		
		cout << endl;
	}
	


	//NOTE: this right now has the majority of the code to use
	//calculate 2-step optimal.if this works i'll eat my sock
	//calc_two_step(cords);


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




void making_distance_matrix (vector <pair <double, double>> cords, vector<vector<double>> &distance_matrix, vector <vector <pair <double, int>>> &shortest_nodes)
//passes in cords and distance_matrix is passed by reference allowing changes in function without returning it. TODO: maybe change this to pass by value to make this more obvious?
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



			//updates the adjacency matrix
			distance_matrix[node_tracker][inner_node_tracker] = distance;

			//also temporary updates the shortest_node vector to sort later
			shortest_nodes[node_tracker][inner_node_tracker] = make_pair(distance, inner_node_tracker);


			//cout << "Node " << node_tracker << " to " << inner_node_tracker << " has distance: " << distance << endl;	//prints out the distance from every point
			inner_node_tracker++;
			
		}

		cout << "\nTHE SHORTEST DISTANCES FROM NODE " << node_tracker <<":\n";
		cout << "Node " << first_shortest_node << " with distance " << first_shortest << endl;
		cout << "Node " << second_shortest_node << " with distance " << second_shortest << endl;
		cout << "Node " << third_shortest_node << " with distance " << third_shortest << endl;

	
		//this sortes the nodes into a new vector based on distance. NOTE this only sorts the node number and must use distance_matrix to lookup the distance. 3D vector to hold x, y, distance? might be way to complicated
		//shortest_nodes[node_tracker] = distance_matrix[node_tracker];
		sort(shortest_nodes[node_tracker].begin(), shortest_nodes[node_tracker].end());


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
			else if (xinit == x3 && yinit == y3)
			{
				//makes sure we don't loop back to node currently on
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

		


		//calculate the shortest path given the first points
		double first_potential_path_dist = new_first_shortest + first_shortest;


		//even newer stuff

        	double new_xinit_2 = cords[second_shortest_node].first;
        	double new_yinit_2 = cords[second_shortest_node].second;
	

		//TODO: MAKE VARIABLES BETTER
		//	new_first/second/third_shortest_2 is the 3 closest nodes to the 2nd shortest path from node A. initially set to virtual infinity
		//	new_first/second/third_shortest_node_2 are the numbers of the 3 closest nodes to the 2nd shortest path from node A
		//	new_inner_tracker_2 is keeping track of the nodes closest to the second shortest path from node A
		//	x4 and y4 are the cordinates of the node being tested to the second shortest path from node A,,,, this calulates all the nodes from node C. (node B is the node resulting from shortest path)
		//

		cout << "\nCalculating 3 shortest distances from the second shortest node (Node " << second_shortest_node << "):\n";

		// Re-initialize shortest variables
		float new_first_shortest_2 = 999999999, new_second_shortest_2 = 999999999, new_third_shortest_2 = 999999999;
		int new_first_shortest_node_2, new_second_shortest_node_2, new_third_shortest_node_2;
		int new_inner_tracker_2 = 0;

		for (auto cord3 : cords) 
		{
			double x4 = cord3.first;
        		double y4 = cord3.second;
		
        		double new_distance_2 = sqrt(pow(x4 - new_xinit_2, 2) + pow(y4 - new_yinit_2, 2));  // Calculate distance from node 3

        		if (new_xinit_2 == x4 && new_yinit_2 == y4) 
			{
            			// Skip the current point
           		}

			else if (xinit == x4 && yinit == y4)
		       {
				//makes sure not looping back to first node
		       }

			else if (new_distance_2 < new_first_shortest_2) 
			{
                		new_third_shortest_2 = new_second_shortest_2;
                		new_third_shortest_node_2 = new_second_shortest_node_2;

                		new_second_shortest_2 = new_first_shortest_2;
               			new_second_shortest_node_2 = new_first_shortest_node_2;

                		new_first_shortest_2 = new_distance_2;
               			new_first_shortest_node_2 = new_inner_tracker_2;
			} 
			
			else if (new_distance_2 < new_second_shortest_2) 
			{
             			new_third_shortest_2 = new_second_shortest_2;
                		new_third_shortest_node_2 = new_second_shortest_node_2;

                		new_second_shortest_2 = new_distance_2;
                		new_second_shortest_node_2 = new_inner_tracker_2;
            		} 
			else if (new_distance_2 < new_third_shortest_2) 
			{
               			new_third_shortest_2 = new_distance_2;
                		new_third_shortest_node_2 = new_inner_tracker_2;
            		}
           
			new_inner_tracker_2++;
        
		}

        	// Display the 3 shortest distances from the second shortest node
        	cout << "Node " << new_first_shortest_node_2 << " with distance " << new_first_shortest_2 << endl;
        	cout << "Node " << new_second_shortest_node_2 << " with distance " << new_second_shortest_2 << endl;
        	cout << "Node " << new_third_shortest_node_2 << " with distance " << new_third_shortest_2 << endl;


		//calculate the shortest path given the second shortest initial node
		double second_potential_path_dist = new_first_shortest_2 + second_shortest;

		//even newer stuff
	

        	double new_xinit_3 = cords[third_shortest_node].first;
        	double new_yinit_3 = cords[third_shortest_node].second;





		//NEW STUFF AS PART OF THIS FUNCTION. 
	

		//TODO: MAKE VARIABLES BETTER
		

		cout << "\nCalculating 3 shortest distances from the third shortest node (Node " << third_shortest_node << "):\n";

		// Re-initialize shortest variables
		float new_first_shortest_3 = 999999999, new_second_shortest_3 = 999999999, new_third_shortest_3 = 999999999;
		int new_first_shortest_node_3, new_second_shortest_node_3, new_third_shortest_node_3;
		int new_inner_tracker_3 = 0;

		for (auto cord4 : cords) 
		{
			double x5 = cord4.first;
        		double y5 = cord4.second;
		
        		double new_distance_3 = sqrt(pow(x5 - new_xinit_3, 2) + pow(y5 - new_yinit_3, 2));  // Calculate distance from node 3

        		if (new_xinit_3 == x5 && new_yinit_3 == y5) 
			{
            			// Skip the current point
           		} 

			else if (xinit == x5 && yinit == y5)
			{
				//make sure not looping back to point on already
			}

			else if (new_distance_3 < new_first_shortest_3) 
			{
                		new_third_shortest_3 = new_second_shortest_3;
                		new_third_shortest_node_3 = new_second_shortest_node_3;

                		new_second_shortest_3 = new_first_shortest_3;
               			new_second_shortest_node_3 = new_first_shortest_node_3;

                		new_first_shortest_3 = new_distance_3;
               			new_first_shortest_node_3 = new_inner_tracker_3;
			} 
			
			else if (new_distance_3 < new_second_shortest_3) 
			{
             			new_third_shortest_3 = new_second_shortest_3;
                		new_third_shortest_node_3 = new_second_shortest_node_3;

                		new_second_shortest_3 = new_distance_3;
                		new_second_shortest_node_3 = new_inner_tracker_3;
            		} 
			else if (new_distance_3 < new_third_shortest_3) 
			{
               			new_third_shortest_3 = new_distance_3;
                		new_third_shortest_node_3 = new_inner_tracker_3;
            		}
           
			new_inner_tracker_3++;
        
		}

        	// Display the 3 shortest distances from the second shortest node
        	cout << "Node " << new_first_shortest_node_3 << " with distance " << new_first_shortest_3 << endl;
        	cout << "Node " << new_second_shortest_node_3 << " with distance " << new_second_shortest_3 << endl;
        	cout << "Node " << new_third_shortest_node_3 << " with distance " << new_third_shortest_3 << endl;



		//calculate the shortest path given the 3rd shortest initial node
		double third_potential_path_dist = new_first_shortest_3 + third_shortest;




		//print out the possible shortest paths
	
		cout << "\nDISTANCE OF THE 3 SHORTEST PATHS:\n";
		cout << "Path 1: " << first_potential_path_dist << endl;
		cout << "Path 2: " << second_potential_path_dist << endl;
		cout << "Path 3: " << third_potential_path_dist << endl;

		//NOTE: there could be a tie, in that case it does the lowest path in the heigharchy. this is to help resolve so many situations I don't want to code for
		//even though we calculate two steps ahead, we are only moving one step. this is to help prevent getting stuck in local traps and more potential to see better paths
		if (first_potential_path_dist <= second_potential_path_dist && first_potential_path_dist <= third_potential_path_dist)
		{
			cout << "\nFirst path is the most efficient\n";

			cout <<"We should go from Node " << node_tracker << " to Node " << first_shortest_node;
		}
		else if (second_potential_path_dist <= first_potential_path_dist && second_potential_path_dist <= third_potential_path_dist)
		{
			cout << "\nSecond path is most efficient\n";
	
			cout <<"We should go from Node " << node_tracker  << " to Node " << second_shortest_node;
		}
		else
		{
			cout << "\nThird path is most efficient\n";
	
			cout <<"We should go from Node " << node_tracker << " to Node " << third_shortest_node;
		}
	
	
		node_tracker++;
	
		cout << endl << endl;
	}


	return;
}
