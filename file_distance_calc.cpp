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
//void all_distance_calculation(vector<pair<double, double>> cords);
//void calc_two_step (vector<pair<double, double>> cords);
void making_distance_matrix (vector <pair <double, double>> cords, vector <vector <pair <double, int>>> &shortest_nodes);
void two_step_with_matrix  (vector<vector<pair<double, int>>> &shortest_nodes);
void traveling_through_points(vector<vector<pair<double, int>>> &shortest_nodes, int total_points);

int main (void)
{
	vector<pair<double, double>> cords; //creates a vector of pairs called cords of the form (double, double) 
	double x, y;	


	//creates a vector of bools to see if we visited a node. node 0 has pos 0. node 29 has pos 29, etc etc.
	vector<bool> visited_point;



	//opens the point_file.txt and inserts the first line into total_points. first line has to say how many total coordinates there are
	int total_points;
	ifstream point_file ("point_file.txt");
	point_file >> total_points; //gets total points from the first line in the input file
	


	//TODO: check if we still need this with shortest_nodes. NOTE: WE DO NOT HOWEVER STILL NEEDED FOR 'calc_two_step'
	//create a vector of nxn where n is the total amount of points
	vector <vector <double>> distance_matrix(total_points, vector<double>(total_points));



	//2D array to hold the k shortest nodes for every given point. used to make some calculation easier. overall will be an nxn array
	//this creates an nxn vector of shortest_nodes.
	//this vector has a pair of the shortest nodes and the distance that node has. very nice to have all data compacted like this
	vector <vector <pair <double, int>>> shortest_nodes (total_points, vector <pair <double, int>>(total_points));;

	


	//reads in the points from the .txt file
	for (int i = 0; i < total_points; i++) //as long as there are points to be calculated (gotten from first line of .txt file does the code)
	{
		//gets the x, y points for each point
		point_file >> x;
		point_file >> y;

		cords.push_back(make_pair(x, y)); //adds the cordinate pair to the vector 'cords'
	}


	//creates the matrix array and sorts it based off the shortest distance from node A. shortest_nodes stores distance and node so all information needed is there. 
	making_distance_matrix(cords, shortest_nodes);



	//NOTE: this is useful debugging, remove comment block if errors to help testing what all the values from node A -> B is
/*
	//printing out the (hopefully) sorted shortest_node vectors
	//NOTE: printing is so computationally expensive comment this out in final. this is good though for testing
	cout << "\n\n";
	for (int i = 0; i < total_points; i++)
	{
		cout << "From Node " << i <<": " << endl;
		for (int j = 1; j < total_points; j++) //doesn't check first point as first point is itself so it will always be the shortest
		{
			cout <<shortest_nodes[i][j].second << " has a distance of " << shortest_nodes[i][j].first << endl;
		}
		
		cout << endl << endl;
	}
*/	

	//two_step_with_matrix(shortest_nodes);


	traveling_through_points(shortest_nodes, total_points);

	return 0;	
}






/*
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
*/



void making_distance_matrix (vector <pair <double, double>> cords, vector <vector <pair <double, int>>> &shortest_nodes)
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
		
		//cout << "Current Node: " << node_tracker << endl;

		for (auto cord2 : cords)
		{
			
			double x2 = cord2.first;	//gets new cordinates for every point
			double y2 = cord2.second;

			double distance = sqrt(pow(x2 - xinit, 2) + pow(y2 - yinit, 2));	//calculates distance from initial point to every other point
		
		

/*	
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

*/
			
			//TODO: if this runs with this commented out then delete
			//updates the adjacency matrix
			//distance_matrix[node_tracker][inner_node_tracker] = distance; //is this even needed anymore

			//also temporary updates the shortest_node vector to sort later
			shortest_nodes[node_tracker][inner_node_tracker] = make_pair(distance, inner_node_tracker);


			//cout << "Node " << node_tracker << " to " << inner_node_tracker << " has distance: " << distance << endl;	//prints out the distance from every point
			inner_node_tracker++;
			
		}


/*
		cout << "\nTHE SHORTEST DISTANCES FROM NODE " << node_tracker <<":\n";
		cout << "Node " << first_shortest_node << " with distance " << first_shortest << endl;
		cout << "Node " << second_shortest_node << " with distance " << second_shortest << endl;
		cout << "Node " << third_shortest_node << " with distance " << third_shortest << endl;
*/
	
		//this sortes the nodes into a new vector based on distance. shortest_nodes[i][j].first gives out the distance while shortest_nodes[i][j].second gives out the node itself. With this most data needed is in this vector it's very nice :)
		sort(shortest_nodes[node_tracker].begin(), shortest_nodes[node_tracker].end());

		node_tracker++;

		//cout << endl << endl;
	}


	return;
}





/*
//TODO: NOTE: WHATEVER: THIS DOES NOT CALCULATE THE OPTIMAL FIRST 3 NODES. SOMETHING WRONG WITH MY CODE. I THINKIN THE FIRST INNER FOR LOOP IS WHERE THE CODE IS FUCKED DUE TO NOT MOVING THINGS AFTER FINDING A MORE EFFICIENT PATH!!!!!!!!!!!!!
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
*/



//TODO: FIX; right now this calculates things like node 0 to first node in node 2 then node 2 to first node in 3. then it calculates node 0 to second node in 3 then node 3 to second node in 4. I want it to calculate node 0 to first node in node 2, then node to to first node in 3 and node 0 to first node in 2, then node 2 to first node in 4, or whatever the first and second shortest distances are from node 0 -> 2 -> x
//
//TODO: Add code to prevent doubling back to a point previously visited, then go back to the starting node after all points have been visited.

/*
void two_step_with_matrix  (vector<vector<pair<double, int>>> &shortest_nodes)
{
	int k_branches = 3; //lets k_branches to 3. in future we will let users enter the value for k

	double total_dist = 0; //base total_dist;
	double total_dist_1 = 0;
	double total_dist_2 = 0;
	double total_dist_3 = 0;

	int base_node;
	int node_1;
	int node_2;
	int node_3;

	int node_tracker = 0; //keeps track of nodes
	
	bool already_visited = false;
						  


	//The TSP part of this problem. keeps track of 'visited nodes'
	vector <int> visited_nodes;
	
	visited_nodes.push_back(0); //we start at node 0, so we can just push it back

	for (auto nodes : shortest_nodes) //goes through every node in shortest_nodes
	{
		//resets already_visited flag
		already_visited = false;
		
		//vector<pair<double, int>> path_info; //now that I discovered what pair does I feel like I'll use them constantly. similar to what I did with vectors
		vector<pair<double, int>> path_info;
		for (int i = 1; i <= k_branches; i++) //start at i=1 so we don't check distance from itself
		{

			
			//resets distance for new head node
			total_dist_1 = 0;
			total_dist_2 = 0;
			total_dist_3 = 0;
			total_dist = 0;

			int second_node;
			int third_node;

			total_dist += shortest_nodes[node_tracker][i].first; //adds node currently on to next node distance //THIS WORKS PROPERLY
			//node_1 = shortest_nodes[node_tracker][i].second;

			//total_dist += shortest_nodes[node_1][i].first;
		
			//cout << total_dist << endl;
			//cout << "node_1 contains value: " << node_1 << endl;

			//total_dist_1 += shortest_nodes[node_1][i].first;
			//node_2 = shortest_nodes[node_1][i].second;

			second_node = shortest_nodes[node_tracker][i].second;	//gets second node	//THIS WORKS PROPERLY

			total_dist += shortest_nodes[second_node][1].first;	//adds distance from second node to the distance from the first node	 
										//Because at this moment we are only doing 1-step we only have to check the 1st position. with n-step
										//this code is going have to change

			third_node = shortest_nodes[second_node][1].second;	//gets the third node (node both distances are leading to) 
										//because at this moment we are only doing 1-step we only have to check the 1st potition. with n-step 
										//this code will have to change. maybe with another tracker that adds 1 each time then gets reset at 
										//the top of the loop


			cout << "***************************************** Total Distance For This Path ***************************************\n";
			//cout << total_dist_1 << endl;
			//cout << "For Node: " << node_tracker << "\n";
			cout << "Node " << node_tracker << " to Node " << second_node << " to Node " << third_node << " has distance " << total_dist << endl;
			path_info.push_back(make_pair(total_dist, second_node)); //puts the total_dist and the second node leading to that dist into a vector called path_info


		}

		
       		pair<double, int> shortest_path = path_info[0]; // Creates new pair to store shortest distance and it's node. We assume the first path is the shortest initially
        	for (int i = 1; i < path_info.size(); i++) // Compare each path
        	{
            		if (path_info[i].first < shortest_path.first) // If a shorter path is found, update
            		{
                		shortest_path = path_info[i];
            		}
        	}

		cout << "\nThe shortest path has length " << shortest_path.first << " with the second node being " << shortest_path.second << endl;

		//already_visited = false;

		for (int nodes : visited_nodes)
		{
			//already_visited = false; //resets flag
			if (shortest_path.second == nodes)
			{
				already_visited = true;
				//NOTE: can do 'break' here but that creates messy code, can be an optimization but for while still creating it's fine....
			}
		}


		if (!already_visited)
		{
			visited_nodes.push_back(shortest_path.second);
		}
		else
		{
			visited_nodes.push_back(-1); //for now pushes -1 if the optimal path visites a node we already went to, TODO: create code later that checks second optimal path
		}



		node_tracker++;
		cout << endl << endl;

	}



	//viewing all the 'visited' nodes
	
	cout << "Here are all then nodes we visited: ";
	for (int nodes : visited_nodes)
	{
		cout << nodes << " ";
	}
	cout << endl << endl;




	return;
}
*/


//Code to properly step through the nearest nodes based off the k-branch n-step lookahead
//NOTE: THE LAST NODE ISN'T BEING CALCULATED CORRECTLY. I HAVE NO IDEA AS OF 11/15/4:32PM WHY THIS IS BUT IT DOESN'T SEEM TO FOLLOW THE RULES. THIS IS THE LAST NODE BEFORE GOING BACK TO 0
//IT'S DISTANCE ALSO ISN'T BEING ADDED TO THE TOTAL_DIST, THIS PROBABLY INDICATES A OFF BY 1 ERROR

void traveling_through_points(vector<vector<pair<double, int>>> &shortest_nodes, int total_points)
{
	int k_branches = 3; //lets k_branches to 3. in future we will let users enter the value for k

	double total_dist = 0; //base total_dist;
	double total_dist_1 = 0;
	double total_dist_2 = 0;
	double total_dist_3 = 0;
	double distance_traveled = 0;

	int base_node;
	int node_1;
	int node_2;
	int node_3;

	int node_tracker = 0; //keeps track of nodes
	
	bool already_visited = false;
						  


	//The TSP part of this problem. keeps track of 'visited nodes'
	vector <int> visited_nodes;
	
	visited_nodes.push_back(0); //we start at node 0, so we can just push it back





	
	for (auto nodes : shortest_nodes) //goes through every node in shortest_nodes
	{
		//resets already_visited flag
		already_visited = false;
		
		//vector<pair<double, int>> path_info; //now that I discovered what pair does I feel like I'll use them constantly. similar to what I did with vectors
		vector<pair<double, int>> path_info;
		for (int i = 1; i <= total_points - 1; i++) //start at i=1 so we don't check distance from itself
		{

			
			//resets distance for new head node
			total_dist_1 = 0;
			total_dist_2 = 0;
			total_dist_3 = 0;
			total_dist = 0;

			int second_node;
			int third_node;

			total_dist += shortest_nodes[node_tracker][i].first; //adds node currently on to next node distance //THIS WORKS PROPERLY

			second_node = shortest_nodes[node_tracker][i].second;	//gets second node	//THIS WORKS PROPERLY

			total_dist += shortest_nodes[second_node][1].first;	//adds distance from second node to the distance from the first node	 
										//Because at this moment we are only doing 1-step we only have to check the 1st position. with n-step
										//this code is going have to change



			//NOTE: THIS ONLY MAKES SURE WE DON'T DO A -> B -> A BY CHECKING IF THE THIRD NODE IS THE SAME AS THE FIRST NODE. IF IT IS THEN USE THE SECOND NODE	
			//I HAVE TO DOUBLE CHECK THAT THIS IS ACTUALLY WORKING PROPERLY
			if (node_tracker == shortest_nodes[second_node][1].second) //checks if first node is same as third done
			{
				second_node = shortest_nodes[node_tracker][2].second;
			}


			third_node = shortest_nodes[second_node][1].second;	//gets the third node (node both distances are leading to) //NOTE: THIS HAS NO CHANGE IF I CHANGE '1' TO 'i' 
										//because at this moment we are only doing 1-step we only have to check the 1st potition. with n-step 
										//this code will have to change. maybe with another tracker that adds 1 each time then gets reset at 
										//the top of the loop


			//TODO: UNCOMMENT BELOW CODE TO SEE ALL THE PATHS AND DISTANCES FROM ALL PATHS

			cout << "***************************************** Total Distance For This Path ***************************************\n";
			//cout << total_dist_1 << endl;
			//cout << "For Node: " << node_tracker << "\n";
			cout << "Node " << node_tracker << " to Node " << second_node << " to Node " << third_node << " has distance " << total_dist << endl;

			path_info.push_back(make_pair(total_dist, second_node)); //puts the total_dist and the second node leading to that dist into a vector called path_info


		}




		pair<double, int> shortest_path = path_info[0]; // Create a new pair to store shortest distance and its node

		//BELOW IS CHATGPT GENERATED CODE

		// Loop through each node in path_info to find the shortest unvisited path
		for (int i = 0; i < path_info.size(); i++) // Ensure we check all nodes
		{
			bool already_visited = false;
			for (int node : visited_nodes)
			{
				if (path_info[i].second == node)
				{
					already_visited = true;
					break; // If visited, stop checking and move to the next node
				}
			}

			if (!already_visited)
			{
				shortest_path = path_info[i]; // Choose this path if it's not visited
				break; // Stop after finding the first unvisited path
			}
		}


		//TODO: unncomment below code to see the shortest valid paths with what node should be visited next
		cout << "\nThe shortest valid path has length " << shortest_path.first << " with the second node being " << shortest_path.second << endl;




		//*****************************************NEW CODE, PROBABLY DOESN'T WORK AT FUCKING ALL*********************************
		
		//finds the correct index of where the shortest node is
		int correct_index = -1;
		for (int i = 0; i < shortest_nodes[node_tracker].size(); i++) 
		{
			if (shortest_nodes[node_tracker][i].second == shortest_path.second) 
			{
  				correct_index = i; // Get the index where node matches
  				break;
  			}
		}

	
/*
		// Now add the distance from node_tracker to the next node (second node)
		if (correct_index != -1) 
		{
			distance_traveled += shortest_nodes[node_tracker][correct_index].first; 
			cout << "Current Path Length: " << distance_traveled << endl << endl;
		} 
		//NOTE: this else statement should never be executed, probably can remove
		else 
		{
			cout << "Error: Could not find a matching node in shortest_nodes.\n";
		}
*/
		//**********************************************END NEW CODE THAT PROBABLY DOESN'T WORK





		if (find(visited_nodes.begin(), visited_nodes.end(), shortest_path.second) == visited_nodes.end()) 
		{
			visited_nodes.push_back(shortest_path.second); // Add to visited nodes if not already visited

			distance_traveled += shortest_nodes[node_tracker][correct_index].first;
			cout << "Current Path Length: " << distance_traveled << endl << endl;
		}		 

		node_tracker++;
	
		//TODO:uncomment below for better formatting
		cout << endl << endl;

	}


	//special case to handle the last node back to the starting node. 
	int last_node = visited_nodes.back();
        for (auto end_to_start : shortest_nodes[last_node]) 
        {
                if (end_to_start.second == 0) // finding the distance back to node 0
                {
                        double last_travel = end_to_start.first;
                        distance_traveled += last_travel;
                        cout << "\nThe last node to the starting node has a distance of " << last_travel << endl << endl;
			visited_nodes.push_back(0); //pushes back 0 to show we return to the start
                        break;
                }
        }

	
	//STOPPING THE CHATGPT CODE


	//viewing all the 'visited' nodes
	
	cout << "Here are all then nodes we visited: ";
	for (int nodes : visited_nodes)
	{
		cout << nodes << " ";
	}

	cout << "\nWe traveled a total distance of: " << distance_traveled;
	cout << endl << endl;

	return;
}
