#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char* argv[])
{
	if(argc < 3){
		cerr << "Please provide an input and output file." << endl;
		return 1;
	}
	ifstream input(argv[1]);
	ofstream output(argv[2]);

	int floors; //number for floors
	int *floorsizes; //array of size of floors, index = floor #, value = size
	string ***trojans; //possesions of students, possesion, student, floor
	string curr; //for handleing input

	input >> floors;
	trojans = new string**[floors];

	//you will need to keep track of how many people are on each floor.
	floorsizes = new int[floors];

	for (int i = 0; i < floors; i++) {
		floorsizes[i] = 0;
		trojans[i] = NULL;
	}
	while(getline(input, curr)) {
		stringstream ss;
		ss << curr;
		ss >> curr;
		if (curr == "MOVEIN") {
			int i,k;
			ss >> i; //floor number
			ss >> k; //size of floor
			if (ss.fail()) {
				output << "Error - incorrect command" << endl;
			}else{
				if(i >= floors){
					output << "Error - floor i does not exist" << endl;
				}else if(floorsizes[i] > 0){
					output << "Error - floor i is not empty" << endl;
				}else{
					floorsizes[i] = k; //record the size of the floor
					trojans[i] = new string*[k]; //allocate the space for it
				}
			}
		}
		else if (curr == "MOVEOUT") {
			int i;
			ss >> i; //floor number
			if (ss.fail()) {
				output << "Error - incorrect command" << endl;
			
			//if the floor has stuff to delete
			}else if(i < floors && floorsizes[i] > 0){
				
				//dealocate student posetions
				for(int index = 0; index < floorsizes[i]; index++){
					delete[] trojans[i][index];
					trojans[i][index] = NULL;
				}
				
				//dealocate the floor
				delete[] trojans[i];
				trojans[i] = NULL;
				floorsizes[i] = 0;
				
			}else{
				output << "Error - floor is empty or does not exist" << endl;
			}
		}
		else if (curr == "OBTAIN") { //set the possesions of a student
			int i,j,k;
			ss >> i; //floor number
			ss >> j; //student number
			ss >> k; //size of contents
			if (ss.fail()) {
				output << "Error - incorrect command" << endl;
				
			//if the address is valid and this student has not been assinged yet
			}else if(i < floors && j < floorsizes[i]){ // && trojans[i][j] == 0){
			
				trojans[i][j] = new string[k]; //allocate the space
				for(int index = 0; index < k; index++){
					ss >> trojans[i][j][index]; //assign the list
				}
				
			}else{
				output << "Error - not a valid student" << endl;
			}
			
		}
		else if (curr == "OUTPUT") {
			int i,j;
			ss >> i; //floor number
			ss >> j; //student number
			if (ss.fail()) {
				output << "Error - incorrect command" << endl;
				
			//if the address is valid and this student has been assigned
			}else if(i < floors && j < floorsizes[i] && trojans[i][j] != 0){
			
				output << *trojans[i][j] << endl; //print array of stuff
				
			}else{
				output << "Error - not a valid student" << endl;
			}
			
		}
		else {

		}
	}
	
	//Deallocate
	for(int i = 0; i < floors; i++){
		
		//dealocate student posetions
		for(int j = 0; j < floorsizes[i]; j++){
			if(trojans[i][j] != 0){
				delete[] trojans[i][j];
				trojans[i][j] = NULL;
			}
		}
		
		//dealocate the floor
		delete[] trojans[i];
		trojans[i] = NULL;
		floorsizes[i] = 0;
	}
	
	delete[] trojans;
	trojans = NULL;
	delete[] floorsizes;
	floorsizes = NULL;
	
	return 0;
}
