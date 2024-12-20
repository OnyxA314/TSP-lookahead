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
		for (int i = 1; i < total_points; i++) //start at i=1 so we don't check distance from itself
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
