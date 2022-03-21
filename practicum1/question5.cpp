#include <iostream>
using namespace std; 
int main()
{

	int team; 
	cout << "Enter a team:" << endl; 
	cin >> team;
    
	if(team >= 2 && team <= 9){
		cout << "This team belongs to the North." << endl;
	}
	else if(team >= 10 && team <= 17){
		cout << "This team belongs to the East." << endl; 
	}
    else if (team >= 18 && team <= 25){
        cout << "This team belongs to the South." << endl; 
	} 
	else if (team >= 26 && team <= 32 || team == 1){
		cout << "This team belongs to the West." << endl; 
	}

	if(team < 1 || team > 32){
		cout << "Invalid" << endl; 
	}

	return 0;
}