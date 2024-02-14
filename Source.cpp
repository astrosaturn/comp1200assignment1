#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

// Eric P
// The purpose of the program is to create receipts for a private hospital

// Function prototypes

int getValidDays();
char validateReply();
double computeCharge(char, char);
double accumulateCharges(int, char, char);

int main()
{
	ofstream fout("charges.dat");

	//Validate that charges.dat has successfully opened.
	if (!fout.is_open())
	{
		cout << "Output file has failed to open. Terminating." << endl;
		system("pause");
		exit(1);
	}

	fout << setw(7) << " " << "CPA Private Hospital Room Charge" << endl;
	fout << setw(7) << " " << "********************************" << endl;
	fout << endl << left << setw(14) << "Patient Name" << setw(12) << "Room Type" << right << setw(12) << "# of Days" << setw(12) << "Room Charge" << endl;



	int daysStaying;
	string patientName, roomName;
	char hasTv, continueQuery, roomChoice;
	double totalCharge, overallTotal = 0;

	do
	{
		cout << "Enter the patient's name: ";
		getline(cin, patientName);

		daysStaying = getValidDays();

		cout << "Do you want a TV in your room? (y/n) ";
		hasTv = validateReply();


		cout << "What room will you be choosing?" << endl
			<< "Semi-Private (S) : $250.0 per night" << endl
			<< "Private (P) : $500.0 per night" << endl;
		if (hasTv == 'N') // Only display this if the ward room is available.
			cout << "Ward (W) : $100.0 per night" << endl;


		cin >> roomChoice;
		roomChoice = toupper(roomChoice);

		totalCharge = accumulateCharges(daysStaying, hasTv, roomChoice);

		cout << "The total charge for " << patientName << "'s stay is $" << totalCharge << endl;


		switch (roomChoice)
		{
			case 'S':
				roomName = "Semi-Private";
				break;
			case 'P':
				roomName = "Private";
				break;
			case 'W':
				roomName = "Ward";
				break;
		}

		overallTotal += totalCharge;
		fout << left << setw(14) << patientName << setw(12) << roomName << right << setw(12) << daysStaying << setw(12) << totalCharge << endl;

		cout << "Do you want to enter another patient? (y/n) ";
		continueQuery = validateReply();
		if (continueQuery == 'N')
			break;
		cin.ignore(80, '\n');
	} while (!cin.eof());
	fout << left << setw(38) << "Total Charges" << right << setw(12) << overallTotal << endl;



	system("type charges.dat");
	system("pause");
}

/// <summary>
/// Assigns a value to the chosen room.
/// </summary>
/// <param name="hasTv">If true, ward is not available.</param>
/// <returns>The value of the room for a night</returns>
double computeCharge(char hasTv, char roomChoice)
{
	// Ward $100/night, Semi-Private $250/night, Private $500/night

	double roomCharge;
	if (hasTv == 'N')
	{
		while (roomChoice != 'S' && roomChoice != 'P' && roomChoice != 'W')
		{
			cout << "Invalid choice. Please choose from the available options: (S/P/W) ";
			cin >> roomChoice;
			roomChoice = toupper(roomChoice);
		}
	}
	else
	{
		while (roomChoice != 'S' && roomChoice != 'P')
		{
			cout << "Invalid choice. Please choose from the available options: (S/P) ";
			cin >> roomChoice;
			roomChoice = toupper(roomChoice);
		}
	}

	switch (roomChoice)
	{
	case 'S':
		roomCharge = 250;
		break;
	case 'P':
		roomCharge = 500;
		break;
	case 'W':
		roomCharge = 100;
		break;
	}

	return roomCharge;
}

/// <summary>
/// Adds all charges together
/// </summary>
/// <param name="daysBooked">Days the patient is staying for</param>
/// <param name="hasTv">If they chose to have a TV</param>
/// <returns>The final total.</returns>
double accumulateCharges(int daysBooked, char hasTv, char chosenRoom)
{
	double roomCharge = computeCharge(hasTv, chosenRoom), totalCharge;

	totalCharge = roomCharge * daysBooked;
	if (hasTv == 'Y') // Charge for a TV
		totalCharge += (25 * daysBooked);

	return totalCharge;
}

/// <summary>
/// Checks to make sure the input is either a Y or a N
/// </summary>
/// <returns>Validated Reply</returns>
char validateReply()
{
	char letter;
	cin >> letter;
	letter = toupper(letter);
	while (cin.fail() || letter != 'Y' && letter != 'N')
	{
		cin.ignore(80, '\n');
		cin.clear();
		cout << "Error. Please enter Y or N: ";
		cin >> letter;
		letter = toupper(letter);
	}
	return letter;
}



/// <summary>
/// Validates a user's input for days entered
/// </summary>
/// <returns>Validated days</returns>
int getValidDays()
{
	int numDays;
	do
	{
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(80, '\n');
			cout << "Please enter a valid input: ";
		}
		else
			cout << "Please enter the number of days between wish to be staying (between 1 and 14): ";
		cin >> numDays;
	} while (numDays < 1 || numDays > 14 || cin.fail());
	return numDays;
}

/*
	   CPA Private Hospital Room Charge
	   ********************************
Patient Name  Room Type      # of Days Room Charge

Eric          Private               13        6825
Alex          Semi-Private           3         750
Anthony       Ward                   6         600
Total Charges                                 8175
*/