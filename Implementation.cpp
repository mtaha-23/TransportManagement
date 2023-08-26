//22F-3277 and 22F-8803
#include"Interface.h"
using namespace std;

bool checkNumbersInCNIC(string cnic)
{
	return regex_match(cnic, regex("^[0-9]+$"));
}
bool checkCharacters(string STRING)
{
	return regex_match(STRING, regex("^[a-z A-Z]+$"));
}
bool checkNumber(string STRING)
{
	return regex_match(STRING, regex("^[1-9]+$"));
}
void sortRankingInDescending(float rankings[], int size)
{
	// Selection sort in descending order
	for (int i = 0; i < size - 1; ++i)
	{
		int maxIndex = i;
		for (int j = i + 1; j < size; ++j)
		{
			if (rankings[j] > rankings[maxIndex])
			{
				maxIndex = j;
			}
		}
		// Swap elements
		float temp = rankings[i];
		rankings[i] = rankings[maxIndex];
		rankings[maxIndex] = temp;
	}
}
int generate4digitID()
{
	srand(time(0));
	ifstream getfromFile;
	ofstream writeInFile;
	bool generateNewID = true;
	int idFromFile, ID = 0;

	// Open file to read
	getfromFile.open("All Unique IDs.txt", ios::in);
	if (getfromFile.is_open())
	{
		//keeps generating a new random ID until it's not unique
		while (generateNewID)
		{
			//generating 4 digit random ID
			ID = rand() % 9000 + 1000;

			bool found = false;
			while (getfromFile >> idFromFile)
			{
				//gets all previously assigned ID's from file and matches to see if it is unique
				if (ID == idFromFile)
				{
					found = true;
					break;
				}
			}

			//if same ID is not found in file than breaks the loop
			if (!found)
			{
				generateNewID = false;
			}
			else
			{
				//if same ID is found in file than the cursor in File is moved again to start of File to check Uniqueness of New ID
				getfromFile.clear();
				getfromFile.seekg(0, ios::beg);
			}

		}

		getfromFile.close();
	}
	else
		cout << "All Unique IDs file cannot be opened for viewing." << endl;

	//write the ID to the file
	writeInFile.open("All Unique IDs.txt", ios::app);
	if (writeInFile.is_open())
	{
		writeInFile << ID << endl;
		writeInFile.close();
	}
	else
		cout << "All Unique IDs file cannot be opened for writing." << endl;
	
	return ID;
}
void deleteFromFile(const string& filePath, int deleteLineNo)
{
	ifstream readFile(filePath);
	ofstream writeTempFile("temp.txt");
	string line;
	int currentLineNo = 0;

	while (getline(readFile, line))
	{
		++currentLineNo;

		if (currentLineNo != deleteLineNo)
		{
			writeTempFile << line << endl;
		}
	}

	readFile.close();
	writeTempFile.close();

	//remove the original file
	if (remove(filePath.c_str()) != 0)
	{
		cout << "Error deleting the " << filePath << " file." << endl;
		return;
	}

	//rename the temp file to the original file name
	if (rename("temp.txt", filePath.c_str()) != 0)
	{
		cerr << "Error renaming the " << filePath << " file." << endl;
	}

}
bool isValidID(int ID, User loginAs)
{
	//if id is not 4 digit
	if (ID > 9999 || ID < 1000)
	{
		cout << "Wrong ID, Enter 4 Digit ID ";
		return false;
	}
	
	fstream readingLOGIN;
	//LOGIN Details
	readingLOGIN.open("LOGIN DETAILS.txt");
	if (readingLOGIN.is_open())
	{
		int fileID;
		int fileLogin;
		string temp;

		while (readingLOGIN >> temp >> temp >> fileLogin >> fileID)
		{
			//checks if the input ID is actually an ID of driver or not
			if (fileLogin == loginAs && ID == fileID)
			{
				//when ID is found return true
				return true;
				readingLOGIN.close();
			}
		}
	}
	else
		cout << "LOGIN FILE can't be opened for checking Valid ID";
	readingLOGIN.close();

	//when ID is not found return false
	return false;
}

//-----------------------------------Time Class definition-------------------------------------

Time::Time()
{
	currentTime = std::time(nullptr);
	localtime_s(&timeInfo, &currentTime);
}
Time::Time(const std::string& timeInString)
{
	// Parse the timeString and extract hour, minute, and second values
	int hour = 0, minute = 0, second = 0;

	// Assuming the timeString is in HH:MM:SS format
	sscanf_s(timeInString.c_str(), "%d:%d:%d", &hour, &minute, &second);

	// Create a Time object with the parsed values
	Time convertedTime;
	convertedTime.timeInfo.tm_hour = hour;
	convertedTime.timeInfo.tm_min = minute;
	convertedTime.timeInfo.tm_sec = second;
//	convertedTime.currentTime = std::mktime(&(convertedTime.timeInfo));

	// Assign the convertedTime values to the current object
	this->timeInfo.tm_hour = hour;
	this->timeInfo.tm_min = minute;
	this->timeInfo.tm_sec = second;
//	this->currentTime = convertedTime.currentTime;
	
}
//getter
int Time::getCurrentYear()
{
	return timeInfo.tm_year + 1900;
}
int Time::getCurrentMonth()
{

	return timeInfo.tm_mon + 1;

}
int Time::getCurrentDay()
{
	return timeInfo.tm_mday;
}
time_t Time::getCurrentTime() const
{
	return currentTime;
}
string Time::getCurrentTimeString() const
{
	char buffer[80];
	//print in Hr:Min:Sec -> %H:%M:%S"
	//if to print date in DD-MM-YY format also than write -> %d-%m-%y "
	std::strftime(buffer, 80, "%H:%M:%S", &timeInfo);
	return std::string(buffer);
}
ostream& operator << (ostream& out, const Time& t)
{
	out << t.getCurrentTimeString();

	return out;
}

Time::~Time() {}

//-----------------------------------Date class definition-------------------------------------

Date::Date(int day = 0, int month = 0, int  year = 0) : day(day), month(month), year(year) {}
//setter
void Date::setDay(int day)
{
	this->day = day;
}
void Date::setMonth(int month)
{
	this->month = month;
}
void Date::setYear(int year)
{
	this->year = year;
}
//getter
int Date::getDay()
{
	return day;
}
int Date::getMonth()
{
	return month;
}
int Date::getYear()
{
	return year;
}
//operator overload
ostream& operator << (ostream& out, const Date& d)
{
	out << left << setw(2) << d.day << " " << setw(2) << d.month << " " << setw(4) << d.year <<" ";

	return out;
}
istream& operator >> (istream& in, Date& d)
{
	/*cout << "DOB : ";
	cout << "Enter Day : ";
	in >> d.day;
	cout << "Enter Month : ";
	in >> d.month;
	cout << "Enter Year : ";
	in >> d.year;*/

	bool isleapYear = true;
	bool again = true;
	cout << "DOB : ";
	while (again) {
		try {
			cout << "Enter Year : ";
			in >> d.year;

			if (in.fail()) 
			{
				in.clear();
				while (in.get() != '\n')
					continue;
				throw runtime_error("Invalid input. Please enter year in integer.");
			}
			if (d.year < 1923 || d.year>2023)
				throw string("Enter year between 1923-2023 ");
			
			again = false;
		}
		catch (const exception& e) 
		{
			in.clear();
			in.ignore();
			cerr << e.what() << endl;
		}
		catch (string error)
		{

			in.clear();
			in.ignore();
			cout << error;
		}
	}
	//invalid input check
	if (d.year % 4 == 0)
	{
		isleapYear = true;
	}
	else
	{
		isleapYear = false;
	}

	//-----------------------------------------
	again = true;
	//MONTH EXCEPTION AND INPUT
	while (again) 
	{
		try 
		{
			cout << "Enter Month : ";
			in >> d.month;

			if (in.fail()) 
			{
				in.clear();
				while (in.get() != '\n')
					continue;
				throw runtime_error("Invalid input. Please enter Month in integer.");
			}
			if (d.month < 1 || d.month > 12)
				throw string("Enter again : ");
			// Input is valid, break out of the loop
			again = false;
		}
		catch (const exception& e)
		{
			in.clear();
			in.ignore();
			cerr << e.what() << endl;
		}
		catch (string error)
		{
			in.clear();
			in.ignore();
			cout << error;
		}
	}
	//------------------------------------------

	again = true;
	//DAY EXCEPTION AND INPUT
	while (again) 
	{
		try 
		{
			cout << "Enter Day : ";
			in >> d.day;

			if (in.fail()) 
			{
				in.clear();
				while (in.get() != '\n')
					continue;
				throw runtime_error("Invalid input. Please enter Month in integer.");
			}
			if ((d.day < 1 || d.day > 31 || isleapYear == true && d.month == 2 && d.day > 29 || isleapYear == false && d.month == 2 && d.day > 28) ||
				(d.day > 30 && d.month == 4) || (d.day > 30 && d.month == 6) || (d.day > 30 && d.month == 9) || (d.day > 30 && d.month == 11))
				throw string ("Invalid Day, Enter Again: ");
				
			// Input is valid, break out of the loop
			again = false;
		}
		catch (const exception& e) 
		{
			in.clear();
			in.ignore();
			cerr << e.what() << endl;
		}
		catch (string error)
		{
			in.clear();
			in.ignore();
			cout << error;
		}
	}

	return in;
}
bool Date::operator== (const Date& date) const 
{
	if (this->day == date.day && this->month == date.month && this->year == date.year)
		return true;
	else
		return false;
}

Date::~Date() {}

//-----------------------------------Name class definition-------------------------------------

Name::Name(string fN, string lN) : fName(fN), lName(lN) {}
//setter
void Name::setFirstName(string fName)
{
	this->fName = fName;
}
void Name::setLastName(string lName)
{
	this->lName = lName;
}
//getter
string Name::getFirstName()
{
	return fName;
}
string Name::getLastName()
{
	return lName;
}
//operator overload
istream& operator >> (istream& in, Name& n)
{
	bool tryAgain = true;
	cout << "Enter First Name : ";
	while (tryAgain)
	{
		try
		{
			in >> n.fName;

			if (checkCharacters(n.fName) == false)
				throw string("Name should contain only letters ");

			tryAgain = false;

		}
		catch (string error)
		{
			cout << error;
		}
	}

	tryAgain = true;
	
	cout << "Enter Last Name : ";
	while (tryAgain)
	{
		try
		{
			in >> n.lName;

			if (checkCharacters(n.lName) == false)
				throw string("Name should contain only letters ");

			tryAgain = false;

		}
		catch (string error)
		{
			cout << error;
		}
	}

	return in;
}
ostream& operator << (ostream& out, const Name& n)
{
	out << left << setw(15) << n.fName << setw(15) << n.lName;
	return out;
}

Name::~Name() {}

//-----------------------------------Person class definition-------------------------------------

Person::Person() : personName("", ""), DOB(0, 0, 0), age(0), CNIC("") {}
Person::Person(string fName, string lName, int day, int month, int year, string cnic)
	: personName(fName, lName), DOB(day, month, year), CNIC(cnic)
{
	//sets Age automatically from DOB by calling the function setAge
	setAge(DOB);
}
Person::Person(string fName, string lName, Date date, string cnic)
	: personName(fName, lName), DOB(date), CNIC(cnic)
{
	setAge(DOB);
}
Person::Person(const Person& other)
{
	this->personName = other.personName;
	this->DOB = other.DOB;
	this->age = other.age;
	this->CNIC = other.CNIC;
}
//setter
void Person::setName()
{
	cin >> personName;
}
void Person::setName(string fName, string lName)
{
	this->personName = Name(fName, lName);
}
void Person::setDOB()
{
	cin >> this->DOB;
	//sets Age automatically from DOB by calling the function setAge
	setAge(DOB);
}
void Person::setDOB(int day, int month, int year)
{
	Date date(day, month, year);
	this->DOB = date;
}
void Person::setAge(Date dob)
{
	Time now;

	this->age = now.getCurrentYear() - dob.getYear();
	if (dob.getMonth() > now.getCurrentMonth())
		this->age--;

	else if (dob.getMonth() == now.getCurrentMonth())
	{
		if (dob.getDay() > now.getCurrentDay())
			this->age++;
	}

}
void Person::setCNIC()
{
	bool onlyInteger = false, tryAgain = true;
	char checkArray[10] = { '0' ,'1','2','3','4','5','6','7','8','9' };

	cout << "Enter a 13-Digit CNIC without Dashes : ";
	while (tryAgain)
	{
		try
		{
			getline(cin, CNIC);

			if (CNIC.length() != 13)
				throw string("Enter 13 Digits : ");
			//else if (checkNumbersInCNIC(CNIC))
			else
				for (int i = 0; i < 13; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						if (CNIC[i] != checkArray[j])
							onlyInteger = false;
						else
						{
							onlyInteger = true;
							break;
						}
					}
					if (onlyInteger == false)
						throw string("Enter only Integer : ");

				}
			tryAgain = false;
		}
		catch (string error)
		{
			cout << error;
		}
	}

	//formatting CNIC in form of 12345-1234567-1 by inserting dash at 5 and 13 index
	CNIC.insert(5, "-");
	CNIC.insert(13, "-");

}
void Person::setCNIC(string cnic)
{
	this->CNIC = cnic;
}
//getter
Name Person::getName() const
{
	return personName;
}
Date Person::getDOB() const
{
	return DOB;
}
int Person::getAge() const
{
	return age;
}
string Person::getCNIC() const
{
	return CNIC;
}
//operator overload
ostream& operator << (ostream& out, const Person& p)
{
	out << "Name : " << p.personName << endl;
	out << "DOB : " << p.DOB << endl;
	out << "Age : " << p.age << endl;
	out << "CNIN : " << p.CNIC;

	return out;
}
istream& operator >> (istream& in, Person& p)
{
	Date date;
	cout << "Name : ";
	in >> p.personName;
	p.setDOB();
	cout << "CNIC : ";
	p.setCNIC();

	return in;
}

Person::~Person() {}

//-----------------------------------Customer class definition-------------------------------------

Customer::Customer() : customerID(0), totalBookings(0) {};
Customer::Customer(string fName, string lName, Date dob, string cnic, int CustomerID, int totalBooking)
	: Person(fName, lName, dob, cnic), totalBookings(totalBooking), customerID(CustomerID)
{	
	//if customerId is not greater than zero means it has not been generated
	if (!(this->customerID > 0))
		this->customerID = generate4digitID();
}
//copy constructor
Customer::Customer(const Customer& c) 
{
	this->personName = c.personName;
	this->DOB = c.DOB;
	this->age = c.age;
	this->CNIC = c.CNIC;
	this->customerID = c.customerID;
	this->totalBookings = c.totalBookings;
}
//setter
void Customer::setCustomerID(int ID)
{
	this->customerID = ID;
}
void Customer::setTotalBookings(int add)
{
	this->totalBookings += add;
}
//getter
int Customer::getCustomerID() const
{
	return customerID;
}
int Customer::getTotalBookings() const
{
	return totalBookings;
}

//out of city option
void Customer::selectIntercityOptions(int choice, string& source, string& destination, float& distance)
{
	float allDistance[12] = { 182.9f , 324.0f , 1115.3f , 462.7f , 182.9f , 382.3f ,
							1210.8f, 520.9f, 324.0f , 382.3f , 1415.6f, 192.6f };
	
	//distance from FSD at index 0-3
	if (choice == 1)
	{
		cout << "1. FSD - LHR";
		cout << "\n2. FSD - ISB";
		cout << "\n3. FSD - KAR";
		cout << "\n4. FSD - PES";
	}
	//distance from LHR at index 4-7
	else if (choice == 2)
	{
		cout << "1. LHR - FSD";
		cout << "\n3. LHR - ISB";
		cout << "\n3. LHR - KAR";
		cout << "\n4. LHR - PES";

	}
	//distance from ISB at index 8-11
	else
	{
		cout << "1. ISB - FSD";
		cout << "\n3. ISB - LHR";
		cout << "\n3. ISB - KAR";
		cout << "\n4. ISB - PES";
	}
	int select;
	bool tryAgain = true;

	cout << "Select : ";
	while (tryAgain) 
	{
		try
		{
			cin >> select;

			if (select < 1 || select > 4)
				throw string("Select from 1-4 ");
			if (!cin)
				throw string("Integers only ");

			tryAgain = false;
		}
		catch (string error)
		{
			cin.clear();
			cin.ignore();
			cout << error << "Try Again : ";
		}
	}
	
	//FSD
	if (choice == 1)
	{
			source = "FSD";
		switch (select)
		{
		case 1:
			destination = "LHR";
			distance = allDistance[0];
			break;
		case 2:
			destination = "ISB";
			distance = allDistance[1];
			break;
		case 3:
			destination = "KAR";
			distance = allDistance[2];
			break;
		case 4:
			destination = "PES";
			distance = allDistance[3];
			break;

		}
	}
	//LHR
	else if (choice == 2)
	{
			source = "LHR";
		switch (select)
		{
		case 1:
			destination = "FSD";
			distance = allDistance[4];
			break;
		case 2:
			destination = "ISB";
			distance = allDistance[5];
			break;
		case 3:
			destination = "KAR";
			distance = allDistance[6];
			break;
		case 4:
			destination = "PES";
			distance = allDistance[7];
			break;

		}
	}
	//ISB
	else
	{
		source = "ISB";
		switch (select)
		{
		case 1:
			destination = "FSD";
			distance = allDistance[8];
			break;
		case 2:
			destination = "LHR";
			distance = allDistance[9];
			break;
		case 3:
			destination = "KAR";
			distance = allDistance[10];
			break;
		case 4:
			destination = "PES";
			distance = allDistance[11];
			break;

		}
	}

}
void Customer::selectIntracityOptions(string& source, string& destination, float& distance)
{
	int choice; 
	bool again = true;	

	cout << "1. D-Ground - GTS";                    
	cout << "\n2. D-Ground - Daewoo";
	cout << "\n3. D-Ground - Kohinoor";
	cout << "\n4. Layllpur Galleria - Kohinoor";
	cout << "\n5. Layllpur Galleria - D-Ground";
	cout << "\n6. Daewoo - FAST NUCES";
	cout << "\n7. kohinoor - Clock Tower";
	cout << "\n8. GTS - Railway Station";
	cout << "\n9. Daewoo - University of Agriculture";
	cout << "\nEnter your Choice: ";
	while (again)
	{
		try
		{
			cin >> choice;

			if (choice < 1 || choice > 9)
				throw string("Enter between 1-9 : ");
			if (!cin)
				throw string("Enter a number :");

			again = false;
		}
		catch (string error)
		{
			cin.clear();
			cin.ignore();
			cout << error;
		}
	}
	switch (choice) 
	{
	case 1:
		source = "D-Ground";
		destination = "GTS";
		distance = 3.1f;
		break;
	case 2:
		source = "D-Ground";
		destination = "Daewoo";
		distance = 7.2f;
		break;
	case 3:
		source = "D-Ground";
		destination = "Kohinoor";
		distance = 1.6f;
		break;
	case 4:
		source = "Layllpur Galleria";
		destination = "Kohinoor";
		distance = 4.2f;
		break;
	case 5:
		source = "Layllpur Galleria";
		destination = "D-Ground";
		distance = 5.4f;
		break;
	case 6:
		source = "Daewoo";
		destination = "FAST-NUCES";
		distance = 18.4f;
		break;
	case 7:
		source = "Kohinoor";
		destination = "Clock-Tower";
		distance = 4.7f;
		break;
	case 8:
		source = "GTS";
		destination = "Railway-Station";
		distance = 5.0f;
		break;
	case 9:
		source = "Daewoo";
		destination = "University-of-Agriculture";
		distance = 5.0f;
		break;
	}
}
void Customer::writeCustomerInFile()
{
	ofstream writeInFile;	//used to write in file

	writeInFile.open("Customer.txt", ios::app);
	if (writeInFile.is_open())
	{
		writeInFile << getCustomerID() << "\t" << getName() << "\t" << getDOB() << "\t" << getAge() << "\t" 
			<< getCNIC() << "\t" << getTotalBookings() << endl;
	}
	else
		cout << "Cusotmer File can't be opened for Writing";
	writeInFile.close();

}
void Customer::getCustomerFromFile(int customerID)
{
	fstream readingCustomer;
	readingCustomer.open("Customer.txt");

	if (readingCustomer.is_open())
	{
		int fileCustomerID, day, month, year, age, totalBooking;
		string fileFName, fileLName, fileCNIC;

		while (readingCustomer >> fileCustomerID >> fileFName >> fileLName >> day >> month >> year >> age >> fileCNIC >> totalBooking)
		{
			if (customerID == fileCustomerID)
			{
				this->personName = Name(fileFName, fileLName);
				this->DOB = Date(day, month, year);
				this->age = age;
				this->CNIC = fileCNIC;
				this->customerID = fileCustomerID;
				this->totalBookings = totalBooking;

				//closes the file after the customer has been copied
				readingCustomer.close();
			}
		}
	}
	else
		cout << "Customer File can't be opened for copying Data from File";
	readingCustomer.close();
}
void Customer::deleteCustomerFromFile()
{
	int customerToDeleteLineNo = 0;

	fstream readingCustomer;
	readingCustomer.open("Customer.txt");

	if (readingCustomer.is_open())
	{
		int fileCustomerID, day, month, year, age, totalBooking;
		string fileFName, fileLName, fileCNIC;

		while (readingCustomer >> fileCustomerID >> fileFName >> fileLName >> day >> month >> year >> age >> fileCNIC >> totalBooking)
		{
			//counting on which line the customer is that is to be deleted
			++customerToDeleteLineNo;
			if (this->customerID == fileCustomerID)
			{
				//if the driver is found that is to be deleted than close the file now we have the line number to delete
				readingCustomer.close();
			}
		}
	}
	else
		cout << "Customer File can't be opened for Deleting";
	readingCustomer.close();

	string file = "Customer.txt";
	//removing Customer by removing the line
	deleteFromFile(file, customerToDeleteLineNo);
}
void Customer::addNewCustomer()
{
	cin >> personName;
	cin >> DOB;
	setAge(DOB);			
	if (age < 12)
	{
		cout << "You need atleast to be 12, You can't register as a Customer";
		return;
	}
	setCNIC();

	int save;
	cout << "Do you want to save data? No(0) Yes(1) ";
	cin >> save;
	while (save != 1 && save != 0)
	{
		cin.clear();
		cin.ignore();
		cout << "Enter 1 or 0 : ";
		cin >> save;
	}
	if (save == 1)
	{
		//generating ID and saving Data in File
		setCustomerID(generate4digitID());
		writeCustomerInFile();


		//writing Customer ID in file LOGIN DETAILS every time a new customer is registered
		fstream writeInFile;
		writeInFile.open("LOGIN DETAILS.txt", ios::app);
		if (writeInFile.is_open())
		{
			writeInFile << getCustomerID() << endl;
		}
		else
			cout << "All Unique File IDs File can't be opened for wrting Sign In";
		writeInFile.close();
	}
}
//operator overload
ostream& operator << (ostream& out, Customer& c)
{
	out << "\nCustomer ID : " << c.customerID;
	out << "\nFirst Name : " << c.personName.getFirstName();
	out << "\nLast Name : " << c.personName.getLastName();
	out << "\nDOB : " << c.DOB.getDay() << "-" << c.DOB.getMonth() << "-" << c.DOB.getYear();
	out << "\nAge : " << c.age;
	out << "\nCNIC : " << c.CNIC;
	out << "\nTotal Bookings : " << c.totalBookings;
	out << "\n\n-----------------------------------------------\n";
	return out;
}

Customer::~Customer() {}

//-----------------------------------Driver class definition-------------------------------------

Driver::Driver() : driverId(0), experience(0), driverLicence(""),
vehicle(), driverOverallRanking(0), totalIncome(0), driverStatus(1), totalCompletedServices(0) {}
Driver::Driver(string fName, string lName, Date dob,
	string cnic, float experience, string drivingLicense,
	Vehicle vehicle, float driverOverallRanking, int status) : Person(fName,lName,dob,cnic)
{
	this->experience = experience;
	this->driverLicence = drivingLicense;
	this->vehicle = vehicle;
	this->driverOverallRanking = driverOverallRanking;
	this->driverStatus = status;
}
Driver::Driver(int driverID, int vehicleID, string fName, string lName, int day, int month, int year,
	string cnic, float experience, string drivingLicense,
	float driverOverallRanking, float income, int status,
	int totalServices) : driverId(driverID), Person(fName, lName, day, month, year, cnic), experience(experience),
	driverLicence(drivingLicense), driverOverallRanking(driverOverallRanking), totalIncome(income),
	driverStatus(status), totalCompletedServices(totalServices)
{
	vehicle.setVehicleID(vehicleID);
}
//setter
void Driver::setDriverID(int ID)
{
	this->driverId = ID;
}
void Driver::setExperience(float experience)
{
	this->experience = experience;
}
void Driver::setDriverLicence(string license)
{
	this->driverLicence = license;
}
void Driver::setVehicle()
{
	int intInput = 0;
	//Registering Vehicle for Driver
	if (getDriverLicense() == "LTV")
	{
		vehicle.setVehicleLicenseType("LTV");

		cout << "1" << ". Bike" << endl;				//Route: Intracity  rideOrDeliery: Both
		cout << "2" << ". Scooter" << endl;				//Route: Intracity  rideOrDeliery: Both
		cout << "3" << ". Car" << endl;					//Route: Both		rideOrDeliery: Both
		cout << "4" << ". Rickshaw" << endl;			//Route: Intracity  rideOrDeliery: Both
		cout << "5" << ". Shahzor" << endl;				//Route: Both		rideOrDeliery: Delivery
		cout << "6" << ". Mazda - Titan" << endl;		//Route: Both		rideOrDeliery: Delivery
		cout << "Register a : ";
		cin >> intInput;
		while (intInput < 1 || intInput > 6)
		{
			cin.clear();
			cin.ignore();
			cout << "Error, Enter again : ";
			cin >> intInput;
		}
		switch (intInput)
		{
		case 1:
			vehicle.setVehicleType("Bike");
			vehicle.setRideOrDelivery(BothTransportation);
			vehicle.setRoute(Intracity);
			vehicle.setNoOfSeats(2);
			break;
		case 2:
			vehicle.setVehicleType("Scooter");
			vehicle.setRideOrDelivery(BothTransportation);
			vehicle.setRoute(Intracity);
			vehicle.setNoOfSeats(2);
			break;
		case 3:
			vehicle.setVehicleType("Car");
			vehicle.setRideOrDelivery(BothTransportation);
			vehicle.setRoute(BothRoute);
			vehicle.setNoOfSeats(4);
			break;
		case 4:
			vehicle.setVehicleType("Rickshaw");
			vehicle.setRideOrDelivery(BothTransportation);
			vehicle.setRoute(Intracity);
			vehicle.setNoOfSeats(4);
			break;
		case 5:
			vehicle.setVehicleType("Shahzor");
			vehicle.setRideOrDelivery(delivery);
			vehicle.setRoute(BothRoute);
			vehicle.setNoOfSeats(2);
			break;
		case 6:
			vehicle.setVehicleType("Mazda - Titan");
			vehicle.setRideOrDelivery(delivery);
			vehicle.setRoute(BothRoute);
			vehicle.setNoOfSeats(3);
			break;
		}
	}
	else if (getDriverLicense() == "HTV")
	{
		vehicle.setVehicleLicenseType("HTV");

		cout << "1" << ". Van" << endl;					//Route: Intercity  rideOrDeliery: Ride
		cout << "2" << ". Bus" << endl;					//Route: Intercity  rideOrDeliery: Ride
		cout << "3" << ". APV" << endl;					//Route: Intercity  rideOrDeliery: Ride
		cout << "4" << ". Campervans" << endl;			//Route: Intercity  rideOrDeliery: Ride
		cout << "5" << ". Caravan" << endl;				//Route: Intercity  rideOrDeliery: Ride
		cout << "6" << ". Truck" << endl;				//Route: Both		rideOrDeliery: Delivery
		cout << "7" << ". Car - Transporter" << endl;	//Route: Intercity  rideOrDeliery: Delivery
		cout << "8" << ". Tanker - Truck" << endl;		//Route: Intracity  rideOrDeliery: Delivery
		cout << "Register a : ";
		cin >> intInput;
		while (intInput < 1 || intInput > 8)
		{
			cin.clear();
			cin.ignore();
			cout << "Error, Enter again : ";
			cin >> intInput;
		}
		switch (intInput)
		{
		case 1:
			vehicle.setVehicleType("Van");
			vehicle.setRideOrDelivery(ride);
			vehicle.setRoute(Intercity);
			vehicle.setNoOfSeats(15);
			break;
		case 2:
			vehicle.setVehicleType("Bus");
			vehicle.setRideOrDelivery(ride);
			vehicle.setRoute(Intercity);
			vehicle.setNoOfSeats(50);
			break;
		case 3:
			vehicle.setVehicleType("APV");
			vehicle.setRideOrDelivery(ride);
			vehicle.setRoute(Intercity);
			vehicle.setNoOfSeats(8);
			break;
		case 4:
			vehicle.setVehicleType("Campervans");
			vehicle.setRideOrDelivery(ride);
			vehicle.setRoute(Intercity);
			vehicle.setNoOfSeats(4);
			break;
		case 5:
			vehicle.setVehicleType("Caravan");
			vehicle.setRideOrDelivery(ride);
			vehicle.setRoute(Intercity);
			vehicle.setNoOfSeats(4);
			break;
		case 6:
			vehicle.setVehicleType("Truck");
			vehicle.setRideOrDelivery(delivery);
			vehicle.setRoute(BothRoute);
			vehicle.setNoOfSeats(2);
			break;
		case 7:
			vehicle.setVehicleType("Car - Transporter");
			vehicle.setRideOrDelivery(delivery);
			vehicle.setRoute(Intercity);
			vehicle.setNoOfSeats(2);
			break;
		case 8:
			vehicle.setVehicleType("Tanker - Truck");
			vehicle.setRideOrDelivery(delivery);
			vehicle.setRoute(Intracity);
			vehicle.setNoOfSeats(2);
			break;
		}
	}
	else
	{
		vehicle.setVehicleLicenseType("BOTH");

		cout << "1" << ".  Bike" << endl;				//Route: Intracity  rideOrDeliery: Both
		cout << "2" << ".  Scooter" << endl;			//Route: Intracity  rideOrDeliery: Both
		cout << "3" << ".  Car" << endl;				//Route: Both		rideOrDeliery: Both
		cout << "4" << ".  Rickshaw" << endl;			//Route: Intracity  rideOrDeliery: Both
		cout << "5" << ".  Shahzor" << endl;			//Route: Both		rideOrDeliery: Delivery
		cout << "6" << ".  Mazda - Titan" << endl;		//Route: Both		rideOrDeliery: Delivery
		cout << "7" << ".  Van" << endl;				//Route: Intercity  rideOrDeliery: Ride
		cout << "8" << ".  Bus" << endl;				//Route: Intercity  rideOrDeliery: Ride
		cout << "9" << ".  APV" << endl;				//Route: Intercity  rideOrDeliery: Ride
		cout << "10" << ". Campervans" << endl;			//Route: Intercity  rideOrDeliery: Ride
		cout << "11" << ". Caravan" << endl;			//Route: Intercity  rideOrDeliery: Ride
		cout << "12" << ". Truck" << endl;				//Route: Both		rideOrDeliery: Delivery
		cout << "13" << ". Car - Transporter" << endl;	//Route: Intercity  rideOrDeliery: Delivery
		cout << "14" << ". Tanker - Truck" << endl;		//Route: Intracity  rideOrDeliery: Delivery
		cout << "Register a : ";
		cin >> intInput;
		while (intInput < 1 || intInput > 14)
		{
			cin.clear();
			cin.ignore();
			cout << "Error, Enter again : ";
			cin >> intInput;
		}
		switch (intInput)
		{
		case 1:
			vehicle.setVehicleType("Bike");
			vehicle.setRideOrDelivery(BothTransportation);
			vehicle.setRoute(Intracity);
			vehicle.setNoOfSeats(2);
			break;
		case 2:
			vehicle.setVehicleType("Scooter");
			vehicle.setRideOrDelivery(BothTransportation);
			vehicle.setRoute(Intracity);
			vehicle.setNoOfSeats(2);
			break;
		case 3:
			vehicle.setVehicleType("Car");
			vehicle.setRideOrDelivery(BothTransportation);
			vehicle.setRoute(BothRoute);
			vehicle.setNoOfSeats(4);
			break;
		case 4:
			vehicle.setVehicleType("Rickshaw");
			vehicle.setRideOrDelivery(BothTransportation);
			vehicle.setRoute(Intracity);
			vehicle.setNoOfSeats(4);
			break;
		case 5:
			vehicle.setVehicleType("Shahzor");
			vehicle.setRideOrDelivery(delivery);
			vehicle.setRoute(BothRoute);
			vehicle.setNoOfSeats(2);
			break;
		case 6:
			vehicle.setVehicleType("Mazda - Titan");
			vehicle.setRideOrDelivery(delivery);
			vehicle.setRoute(BothRoute);
			vehicle.setNoOfSeats(3);
			break;
		case 7:
			vehicle.setVehicleType("Van");
			vehicle.setRideOrDelivery(ride);
			vehicle.setRoute(Intercity);
			vehicle.setNoOfSeats(15);
			break;
		case 8:
			vehicle.setVehicleType("Bus");
			vehicle.setRideOrDelivery(ride);
			vehicle.setRoute(Intercity);
			vehicle.setNoOfSeats(50);
			break;
		case 9:
			vehicle.setVehicleType("APV");
			vehicle.setRideOrDelivery(ride);
			vehicle.setRoute(Intercity);
			vehicle.setNoOfSeats(8);
			break;
		case 10:
			vehicle.setVehicleType("Campervans");
			vehicle.setRideOrDelivery(ride);
			vehicle.setRoute(Intercity);
			vehicle.setNoOfSeats(4);
			break;
		case 11:
			vehicle.setVehicleType("Caravan");
			vehicle.setRideOrDelivery(ride);
			vehicle.setRoute(Intercity);
			vehicle.setNoOfSeats(4);
			break;
		case 12:
			vehicle.setVehicleType("Truck");
			vehicle.setRideOrDelivery(delivery);
			vehicle.setRoute(BothRoute);
			vehicle.setNoOfSeats(2);
			break;
		case 13:
			vehicle.setVehicleType("Car - Transporter");
			vehicle.setRideOrDelivery(delivery);
			vehicle.setRoute(Intercity);
			vehicle.setNoOfSeats(2);
			break;
		case 14:
			vehicle.setVehicleType("Tanker - Truck");
			vehicle.setRideOrDelivery(delivery);
			vehicle.setRoute(Intracity);
			vehicle.setNoOfSeats(2);
			break;
		}
	}

	//Vehicle Model
	string model;
	bool tryAgain = true;
	cout << "Enter Vehicle Model : ";
	while (tryAgain)
	{
		try
		{
			cin >> model;

			if (!checkCharacters(model))
				throw string("Model should contain only letters ");

			tryAgain = false;

		}
		catch (string error)
		{
			cout << error;
		}
	}
	vehicle.setVehicleModel(model);
	
	//Registration Number
	cout << "Eneter 4 digit Vehicle Registration Number : ";
	while (intInput < 999 || intInput > 9999)
	{
		try
		{
			cin >> intInput;
			if (intInput < 999 || intInput > 9999)
				throw string("Enter a 4 digit Reg.No : ");
			if (!cin)
				throw string("Enter Only Integer : ");
		}
		catch (string error)
		{
			cin.clear();
			cin.ignore();
			cout << error;
		}

	}
	vehicle.setRegNo(intInput);

	Date date;
	cout << "Enter Manufacturing Date of Vehicle : ";
	cin >> date;
	vehicle.setManufacturingDate(date);

	float floatInput;
	cout << "Enter Average Milage per km : ";
	cin >> floatInput;
	while (floatInput < 1)
	{
		try
		{
			cin >> floatInput;
			if (floatInput >= 30)
				throw string("Wrong Mileage must be less than 30 ");
			if (!cin)
				throw string("Enter Only Integer : ");
		}
		catch (string error)
		{
			cin.clear();
			cin.ignore();
			cout << error;
		}

	}
	int temp = -1, seats;
	bool again = true;

	if (vehicle.getVehicleType() == "Car" || vehicle.getVehicleType() == "Van" || vehicle.getVehicleType() == "Rickshaw"
		|| vehicle.getVehicleType() == "Bus" || vehicle.getVehicleType() == "APV")
	{
		cout << "Default seats set for your Vehicle : " << vehicle.getNoOfSeats();
		cout << "\nDo you want to add more? Yes(1) No (0) : ";
		while (again)
		{
			try
			{
				cin >> temp;
				if (temp != 0 && temp != 1)
					throw 0;
				if (!cin)
					throw ("Enter Only Integers");

				again = false;
			}
			catch (int)
			{
				cout << "Select 0 or 1: ";
			}
			catch (string error)
			{	
				cin.clear();
				cin.ignore();
				cout << error;
			}
		}
		
		//edit seats;
		again = true;
		if (temp == 1)
		{
			cout << "\nEnter Updated Seats : ";
			while (again)
			{
				try
				{
					cin >> seats;

					if ((vehicle.getVehicleType() == "Car" && (temp > 8 || temp < 2)))
						throw string(" seats 2-8");
					if (((vehicle.getVehicleType() == "Van" || vehicle.getVehicleType() == "APV") && (temp < 8 || temp > 15)))
						throw string(" seats 8-15");
					if ((vehicle.getVehicleType() == "Bus") && (temp > 60 || temp < 50))
						throw string(" seats 50-60");
					if ((vehicle.getVehicleType() == "Rickshaw") && (temp > 6 || temp < 4))
						throw string(" seats ");
					if (!cin)
						throw string("Enter integer only");

					again = false; //used to stop the loop when the correct seats are entered
					vehicle.setNoOfSeats(seats);
				}
				catch (string error)
				{
					cin.clear();
					cin.ignore();
					cout << error;
				}
			}
		}
	}

	vehicle.setAvgMileage(floatInput);
	//sets overall ranking to 0 when the vehicle is registered
	vehicle.setOverallRanking(0.0f);
	//new vehicle status is free
	vehicle.setVehicleStatus(false);		//false == free, true == booked

}
void Driver::setVehicle(Vehicle v)
{
	this->vehicle = v;
}
void Driver::setOverallRanking(float ovrraallRanking)
{
	this->driverOverallRanking = ovrraallRanking;
}
void Driver::setTotalIncome(float income)
{
	this->totalIncome += income;
}
void Driver::setDriverStatus(int status)		// 1 for free, 2 if booked
{
	
	this->driverStatus = status;
}
void Driver::setTotalServices(int add)
{
	this->totalCompletedServices += add;
}
//getter
int Driver::getDriverID() const
{
	return driverId;
}
float Driver::getExperience() const
{
	return experience;
}
string Driver::getDriverLicense() const
{
	return driverLicence;
}
Vehicle Driver::getVehicle()
{
	return vehicle;
}
float Driver::getOverallRanking() const
{
	return driverOverallRanking;
}
float Driver::getTotalIncome() const
{
	return totalIncome;
}
int Driver::getDriverStatus() const
{
	return driverStatus;
}
int Driver::getTotalServices() const
{
	return totalCompletedServices;
}
//other methods

void Driver::AddNewDriver()
{
	string strInput = "";

	cin >> personName;	//inputs person name
	cin >> DOB;
	setAge(DOB);			//inputs Date of Birth
	if (age < 18)
	{
		cout << "You need atleast to be 18, You can't register as a Driver";
		
		return;
	}
	setCNIC();

	cout << "Enter Experience : ";
	try
	{
		cin >> experience;
		if (experience > age)
			throw string("Experience should be less than age ");
		if (!cin)
			throw string("Enter Only float : ");
	}
	catch (string error)
	{
		cin.clear();
		cin.ignore();
		cout << error;
	}

	int intInput = 1;
	cout << "\n1. LTV (Small Vehicles)\n2. HTV (Large Vehicle)\n3. Both\nSelect Your License Type : ";
	cin >> intInput;
	while (intInput < 1 || intInput > 3)
	{
		try
		{
			cin >> intInput;
			if (intInput < 1 || intInput > 3)
				throw string("Select from 1-3 : ");
			if (!cin)
				throw string("Enter Only Integer : ");
		}
		catch (string error)
		{
			cin.clear();
			cin.ignore();
			cout << error;
		}

	}

	if (intInput == 1)
		setDriverLicence("LTV");
	else if (intInput == 2)
		setDriverLicence("HTV");
	else
		setDriverLicence("Both");

	//Adding Vehicle for Driver
	setVehicle();
	//driver set to free by default
	setDriverStatus(1);
	//sets to 0 for new driver;
	setOverallRanking(0);
	setTotalIncome(0);
	setTotalServices(0);

	//setting a Vehicle for driver
	
	int save;
	cout << "Do you want to save data? No(0) Yes(1) ";
	cin >> save;
	while (save != 1 && save != 0)
	{
		cin.clear();
		cin.ignore();
		cout << "Enter 1 or 0 : ";
		cin >> save;
	}
	if (save == 1) 
	{
		//generating Vehicle ID and Driver ID
		vehicle.setVehicleID(generate4digitID());
		setDriverID(generate4digitID());
		vehicle.setOwnerDriverID(driverId);
		writeDriverInFile();
	}

	//writing Driver ID in file LOGIN DETAILS every time a new customer is registered
	fstream writeInFile;
	writeInFile.open("LOGIN DETAILS.txt", ios::app);
	if (writeInFile.is_open())
	{
		writeInFile << getDriverID() << endl;
	}
	else
		cout << "All Unique File IDs File can't be opened for wrting Sign In";
	writeInFile.close();
}
void Driver::writeDriverInFile()
{
	ofstream writeInFile;	//used to write in file

	writeInFile.open("Drivers.txt", ios::app);
	if (writeInFile.is_open())
	{
		writeInFile << left << setw(6) << getDriverID() << setw(6) << vehicle.getVehicleID() << "  " << getName()
			<< "  " << getDOB() << " " << setw(4) << getAge() << setw(18) << getCNIC() << setw(3) << getExperience() << "\t" << setw(6)
			<< getDriverLicense() << setw(5) << getOverallRanking() << setw(6) << getTotalIncome() << setw(2) << getDriverStatus() 
			<< setw(4) << getTotalServices() << endl;
	}
	else
		cout << "Drivers File can't be opened for Writing";
	writeInFile.close();

	vehicle.writeVehicleInFile();	
}
void Driver::getDriverFromFile(int loginDriverId)
{
	fstream readingDriver;
	readingDriver.open("Drivers.txt");

	if (readingDriver.is_open())
	{

		int driverID, driverVehicleID, age, driverStatus, totalServices, year, day, month;
		float driverOverallRanking, income, experience;
		string fName, lName, cnic, license, dash;

		while (readingDriver >> driverID >> driverVehicleID >> fName >> lName >> day >> month 
			>> year >> age >> cnic >> experience >> license >> driverOverallRanking >> income >> driverStatus >> totalServices)
		{
			//if driver Id from file matches to the ID of driver who has logged in than it copies data
			if (driverID == loginDriverId)
			{
				this->personName = Name(fName, lName);
				this->DOB = Date(day, month, year);
				setAge(Date(day, month, year));
				this->CNIC = cnic;
				this->experience = experience;
				this->driverId = driverID;
				this->vehicle.setVehicleID(driverVehicleID);
				this->driverLicence = license;
				this->driverOverallRanking = driverOverallRanking;
				this->totalIncome = income;
				this->driverStatus = driverStatus;
				this->totalCompletedServices = totalServices;

				//if the Driver is found for the loop breaks
				readingDriver.close();
			}
		}
	}
	else
		cout << "Drivers File can't be opened for copying Data from File";
	readingDriver.close();
}
void Driver::removePreviousVehicleOfDriver()
{
	int vehicleToDeleteLineNo = 0;

	string temp;
	int fileVehicleID;

	ifstream ReadFromFile;
	ReadFromFile.open("Vehicle.txt");
	if (ReadFromFile.is_open())
	{
		while (ReadFromFile >> temp >> fileVehicleID >> temp >> temp >> temp >> temp >> temp
			>> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp)
		{
			//counting on which line the vehicle is that is to be deleted
			++vehicleToDeleteLineNo;
			if (this->vehicle.getVehicleID() == fileVehicleID)
			{
				//if the vehicle is found that is to be deleted than close the file now we have the line number to delete
				ReadFromFile.close();
				break;
			}
		}
	}
	else
		cout << "Vehicle File can't be opened for Deleting";
	ReadFromFile.close();

	string file = "Vehicle.txt";
	//removing previous vehicle by removing the line
	deleteFromFile(file, vehicleToDeleteLineNo);
	
}
void Driver::deleteDriverfromFile()
{
	int driverToDeleteLineNo = 0;

	fstream readingDriver;
	readingDriver.open("Drivers.txt");

	if (readingDriver.is_open())
	{
		int driverID, driverVehicleID, age, driverStatus, totalServices, year, day, month;
		float driverOverallRanking, income, experience;
		string fName, lName, cnic, license, dash;

		while (readingDriver >> driverID >> driverVehicleID >> fName >> lName >> day >> month
			>> year >> age >> cnic >> experience >> license >> driverOverallRanking >> income >> driverStatus >> totalServices)
		{
			//counting on which line the driver is that is to be deleted
			++driverToDeleteLineNo;
			//if driver Id from file matches to the ID of driver who has logged in than it copies data
			if (this->driverId == driverID)
			{
				//if the driver is found that is to be deleted than close the file now we have the line number to delete
				readingDriver.close();
			}
		}
	}
	else
		cout << "Drivers File can't be opened for Deleting";
	readingDriver.close();

	string file = "Drivers.txt";
	//removing previous driver by removing the line
	deleteFromFile(file, driverToDeleteLineNo);
	
}
//operator overload
ostream& operator << (ostream& out, Driver& d)
{
	out << "Name : " << d.getName().getFirstName() << " " << d.getName().getLastName() << endl;
	out << "DOB : " << d.getDOB().getDay() << "-" << d.DOB.getMonth() << "-" << d.DOB.getYear() << endl;
	out << "Age : " << d.getAge() << endl;
	out << "CNIC : " << d.getCNIC() << endl;
	out << "Driver ID : " << d.getDriverID() << endl;
	out << "Vehicle ID : " << d.vehicle.getVehicleID() << endl;
	out << "Experience : " << d.getExperience() << endl;
	out << "Driver License : " << d.getDriverLicense() << endl;
	out << "Overall Ranking : " << d.getOverallRanking() << endl;
	out << "Total Income : " << d.getTotalIncome() << endl;
	out << "Total Services : " << d.getTotalServices() << endl;
	out << "Driver Status : "; (d.getDriverStatus() == 1) ? cout << "Free" : cout << "Booked" << endl;
	out << "\n\n-----------------------------------------------\n\n";

	return out;
}

Driver::~Driver() {}

void Driver::addVehicle()
{
	cout << "\nAdd Details of New Vehicle";
	Sleep(50);
	system("pause");
	system("cls");
	setVehicle();
	//generating Vehicle ID
	vehicle.setVehicleID(generate4digitID());
	//replacing old with new so that it updates the Vehicle Id in the Driver's File
	deleteDriverfromFile();
	writeDriverInFile();
}

//-----------------------------------Vehicle class definition-------------------------------------

Vehicle::Vehicle() : vehicleID(0), ownerDriverId(0), vehicleModel(""), vehicleType(""), registrationNo(0),
vehicleLicenseType(""), manufacturingDate(0), avgMileage(0), numOfSeats(0), vehicleStatus(false), 
rideOrDelivery(CategoryNull), route(RouteNull), overallRanking(0.0f), totalCompletedServices(0) {}

Vehicle::Vehicle(int vehicleID, int OwnerDriverId, string VehicleType, string vehicleModel, int regNo, string vehicleLicenseType,
	Date manufacturingDate, float avgMileage, int numOfSeats, bool status,
	TransportionCategory rideOrDelivery, Route route, int totalServices)
	: vehicleID(vehicleID), ownerDriverId(OwnerDriverId), vehicleModel(vehicleModel), vehicleType(VehicleType), registrationNo(regNo),
	vehicleLicenseType(vehicleLicenseType), manufacturingDate(manufacturingDate),
	avgMileage(avgMileage), numOfSeats(numOfSeats), vehicleStatus(status), rideOrDelivery(rideOrDelivery),
	route(route), totalCompletedServices(totalServices)
{
	overallRanking = 0;
}
//setter
void Vehicle::setVehicleID(int ID)
{
	this->vehicleID = ID;
}
void Vehicle::setOwnerDriverID(int ID)
{
	this->ownerDriverId = ID;
}
void Vehicle::setVehicleModel(string model)
{
	this->vehicleModel = model;
}
void Vehicle::setVehicleType(string type)
{
	this->vehicleType = type;
}
void Vehicle::setRegNo(int regNo)
{
	this->registrationNo = regNo;
}
void Vehicle::setVehicleLicenseType(string licenseType)
{
	this->vehicleLicenseType = licenseType;
}
void Vehicle::setManufacturingDate(Date date)
{
	this->manufacturingDate = date;
}
void Vehicle::setAvgMileage(float milage)
{
	this->avgMileage = milage;
}
void Vehicle::setNoOfSeats(int seatsNo)
{
	this->numOfSeats = seatsNo;
}
void Vehicle::setVehicleStatus(bool status)
{
	this->vehicleStatus = status;
}
void Vehicle::setRideOrDelivery(TransportionCategory rideOrDelivery)
{
	this->rideOrDelivery = rideOrDelivery;
}
void Vehicle::setRoute(Route route)
{
	this->route = route;
}
void Vehicle::setOverallRanking(float ranking)
{
	this->overallRanking = ranking;
}
//getter
int Vehicle::getVehicleID()
{
	return vehicleID;
}
int Vehicle::getOwnerDriverID()
{
	return ownerDriverId;
}
string Vehicle::getVehicleModel()
{
	return vehicleModel;
}
string Vehicle::getVehicleType()
{
	return vehicleType;
}
int Vehicle::getRegNo()
{
	return registrationNo;
}
string Vehicle::getVehicleLicenseType()
{
	return vehicleLicenseType;
}
Date Vehicle::getManufacturingDate()
{
	return manufacturingDate;
}
void Vehicle::setTotalVehicleServices(int add)
{
	this->totalCompletedServices += add;
}
float Vehicle::getAvgMileage()
{
	return avgMileage;
}
int Vehicle::getNoOfSeats()
{
	return numOfSeats;
}
bool Vehicle::getVehicleStatus()
{
	return vehicleStatus;
}
TransportionCategory Vehicle::getRideOrDelivery()
{
	return rideOrDelivery;
}
Route Vehicle::getRoute()
{
	return route;
}
float Vehicle::getOverallRanking()
{
	return overallRanking;
}
void Vehicle::writeVehicleInFile()
{
	ofstream writeInFile;	//used to write in file

	writeInFile.open("Vehicle.txt", ios::app);
	if (writeInFile.is_open())
	{
		
		writeInFile << left << setw(6) << getOwnerDriverID() << setw(6) << getVehicleID() << setw(12) << getVehicleModel() << setw(17) 
			<< getVehicleType() << setw(6) << getRegNo() << setw(5) << getVehicleLicenseType() << " " << getManufacturingDate()
			<< setw(4) << getAvgMileage() << setw(4) << getNoOfSeats() << setw(3) << getVehicleStatus() << setw(3) 
			<< setw(3) << getRideOrDelivery() << setw(3) << getRoute() << setw(5) << getOverallRanking() << setw(5)
			<< getTotalVehicleServices() << endl;
	}
	else
		cout << "Drivers File can't be opened for Writing";
	writeInFile.close();

}

Vehicle Vehicle::getVehicleFromFile(int driverId)
{
	int fileVehicleID, fileRegNo, fileNumOfSeats, fileVehicleStatus, fileRideOrDelivery, fileRoute, fileOwnerDriverId, fileDay,fileMonth,fileYear, fileTotalVehicleServices;
	float fileAvgMilage, fileOverallRanking;
	string fileVehicleModel, fileVehicleType, fileVehicleLicenseType;

	fstream ReadVehicle;
	ReadVehicle.open("Vehicle.txt");
	if (ReadVehicle.is_open())
	{
		while (ReadVehicle >> fileOwnerDriverId >> fileVehicleID >> fileVehicleModel >> fileVehicleType >> fileRegNo 
			>> fileVehicleLicenseType >> fileDay >> fileMonth >> fileYear >> fileAvgMilage >> fileNumOfSeats 
			>> fileVehicleStatus >> fileRideOrDelivery >> fileRoute >> fileOverallRanking >> fileTotalVehicleServices)
		{
			if (driverId == fileOwnerDriverId)
			{
				this->vehicleID = fileVehicleID;
				this->ownerDriverId = fileOwnerDriverId;
				this->vehicleModel = fileVehicleModel;
				this->vehicleType = fileVehicleType;
				this->registrationNo = fileRegNo;
				this->vehicleLicenseType = fileVehicleLicenseType;
				this->manufacturingDate = Date(fileDay, fileMonth, fileYear);
				this->avgMileage = fileAvgMilage;
				this->numOfSeats = fileNumOfSeats;
				this->vehicleStatus = fileVehicleStatus;
				
				if (fileRideOrDelivery == 0)
					this->rideOrDelivery = ride;
				else if (fileRideOrDelivery == 1)
					this->rideOrDelivery = delivery;
				else if (fileRideOrDelivery == 2)
					this->rideOrDelivery = BothTransportation;
				
				if (fileRoute == 0)
					this->route = Intracity;
				else if (fileRoute == 1)
					this->route = Intercity;
				else if (fileRoute == 2)
					this->route = BothRoute;

				this->overallRanking = fileOverallRanking;
				this->totalCompletedServices = fileTotalVehicleServices;
				ReadVehicle.close();
			}
		}
	}
	else
		cout << "Vehicle File can't be opened for Total Matches";
	ReadVehicle.close();

	return *this;
}

ostream& operator << (ostream& out, const Vehicle& v)
{
	out << "\nDriver ID: " << v.ownerDriverId;
	out << "\nVehicle ID: " << v.vehicleID;
	out << "\nVehicle Model: " << v.vehicleModel;
	out << "\nVehicle Type: " << v.vehicleType;
	out << "\nRegistration Number: " << v.registrationNo;
	out << "\nVehicle License Type: " << v.vehicleLicenseType;
	out << "\nManufacturing Date: " << v.manufacturingDate;
	out << "\nAverage Mileage: " << v.avgMileage;
	out << "\nNumber of Seats: " << v.numOfSeats;
	out << "\nVehicle Status: " << (v.vehicleStatus == 1 ? "Booked" : "Free"); 
	out << "\nRide or Delivery: ";
	if (v.rideOrDelivery == ride)
		out << "Ride";
	else if (v.rideOrDelivery == delivery)
		out << "Delivery";
	else
		out << "Both";
	
	out << "\nRoute: ";
	if (v.rideOrDelivery == Intercity)
		out << "Intercity";
	else if (v.rideOrDelivery == Intracity) 
		out << "Intracity";
	else 
		out << "Both";

	out << "\nOverall Ranking: " << v.overallRanking;
	out << "\nTotal Completed Service: " << v.totalCompletedServices;
	out << endl;
	out << "\n\n-----------------------------------------------\n\n";
	return out;
}

Vehicle::~Vehicle() {}
int Vehicle::getTotalVehicleServices() const
{
	return totalCompletedServices;
}
//-----------------------------------Service class definition-------------------------------------

Service::Service() : route(RouteNull), source(""),
destination(""), distance(0), serviceStatus(1), fuelrate(0), customerID(0),
driverID(0), vehicleID(0), fare(0), vehicleRanking(0), driverRanking(0) {}
Service::Service(Date bookingDate, Time bookingTime, Route route,
	string source, string destination, float distance, int status,
	float fuelrate, int customerID, int driverID, int vehicleID, int fare,
	float vehicleRanking, float driverRanking)
	: bookingDate(bookingDate), bookingTime(bookingTime),
	route(route), source(source), destination(destination),
	distance(distance), serviceStatus(status), fuelrate(fuelrate),
	customerID(customerID), driverID(driverID), vehicleID(vehicleID),
	fare(fare), vehicleRanking(vehicleRanking), driverRanking(driverRanking) {}
//setter
void Service::setBookingDate(Date bookingDate)
{
	this->bookingDate = bookingDate;
}
void Service::setBookingTime(Time bookingTime)
{
	this->bookingTime = bookingTime;
}
void Service::setRoute(Route route)
{
	this->route = route;
}
void Service::setSource(string source)
{
	this->source = source;
}
void Service::setDestination(string destination)
{
	this->destination = destination;
}
void Service::setDistance(float distance)
{
	this->distance = distance;
}
void Service::setServiceStatus(int status)
{
	this->serviceStatus = status;
}
void Service::setFuelRate(float fuelrate)
{
	this->fuelrate = fuelrate;
}
void Service::setCustomerID(int customerID)
{
	this->customerID = customerID;
}
void Service::setDriverID(int driverID)
{
	this->driverID = driverID;
}
void Service::setVehicleID(int ID)
{
	vehicleID = ID;
}
void Service::setFare(int fare)
{
	this->fare = fare;
}
void Service::setVehicleRanking(float vehicleRanking)
{
	this->vehicleRanking = vehicleRanking;
}
void Service::setDriverRanking(float driverRanking)
{
	this->driverRanking = driverRanking;
}
//getter
Date Service::getBookingDate() const
{
	return bookingDate;
}
Time Service::getBookingTime() const
{
	return bookingTime;
}
Route Service::getRoute() const
{
	return route;
}
string Service::getSource() const
{
	return source;
}
std::string Service::getDestination() const
{
	return destination;
}
float Service::getDistance() const
{
	return distance;
}
int Service::getServiceStatus() const
{
	return serviceStatus;
}
float Service::getFuelRate() const
{
	return fuelrate;
}
int Service::getCustomerID() const
{
	return customerID;
}
int Service::getDriverID() const
{
	return driverID;
}
int Service::getVehicleID() const
{
	return vehicleID;
}
int Service::getFare() const
{
	return fare;
}
float Service::getVehicleRanking() const
{
	return vehicleRanking;
}
float Service::getDriverRanking() const
{
	return driverRanking;
}

void Service::writeServiceInFile()
{
	ofstream writeInFile;	//used to write in file

	writeInFile.open("Service.txt", ios::app);
	if (writeInFile.is_open())
	{
		/*writeInFile << left << setw(6) << getCustomerID() << setw(6) << getDriverID() << setw(6) << getVehicleID() << " " 
			<< getBookingDate() << "   " << setw(11) << getBookingTime() << setw(3) << getRoute() << setw(10) << getSource() << " " << setw(10)
			<< getDestination() << " " << setw(9) << getDistance() << setw(3) << getServiceStatus() << setw(5) << getFuelRate()
			<< setw(6) << getFare() << setw(5) << getDriverRanking() << setw(5) << getVehicleRanking();*/
		
		writeInFile << left << setw(6) << customerID << setw(6) << driverID << setw(6) << vehicleID << " "
			<< bookingDate << "   " << setw(11) << bookingTime << setw(3) << route << setw(10) << source << " " << setw(10)
			<< destination << " " << setw(9) << distance << setw(3) << serviceStatus << setw(5) << fuelrate
				<< setw(6) << fare << setw(5) << driverRanking << setw(5) << vehicleRanking;
	}
	else
		cout << "Service File can't be opened for Writing";
	writeInFile.close();
}

//-----------------------------------Ride class definition-------------------------------------

Ride::Ride() : noOfPassengers(0), wantAc("") {}
Ride::Ride(Date bookingDate, Time bookingTime, Route route,
     string source, string destination, float distance, int status,
     float fuelrate, int customerID, int driverID, int vehicleID,
     int fare, float vehicleRanking, float driverRanking,
     int noOfPassengers, string wantAc)
    : Service(bookingDate, bookingTime, route, source, destination, distance,
              status, fuelrate, customerID, driverID, vehicleID, fare,
              vehicleRanking, driverRanking),
      noOfPassengers(noOfPassengers), wantAc(wantAc) {}
void Ride::setNoOfPassenger(int noOfPassenger)
{
	this->noOfPassengers = noOfPassenger;
}
void Ride::setWantAc(string ac)
{
	wantAc = ac;
}
//getter
int Ride::getNoOfPassenger() const
{
	return noOfPassengers;
}
string Ride::getWantAc() const
{
	return wantAc;
}
//pure virtual
void Ride::setRideTypeDetails(float num, string Ac)
{
	this->noOfPassengers = num;
	this->wantAc = Ac;
}
void Ride::getRideTypeDetails(float& num, string& Ac) const
{
	num = getNoOfPassenger();
	Ac = getWantAc();
	
}

float Ride::CalculateFare(float mileage, float vehicelOverallRanking, float driverOverallRanking)
{
	float fare;
	fare = (getDistance() / mileage) * getFuelRate();
	
	if (vehicelOverallRanking * driverOverallRanking > 20)
		fare += ((vehicelOverallRanking * driverOverallRanking) * 12);
	else if (vehicelOverallRanking * driverOverallRanking > 15)
		fare += ((vehicelOverallRanking * driverOverallRanking) * 10);
	else if (vehicelOverallRanking * driverOverallRanking > 10)
		fare += ((vehicelOverallRanking * driverOverallRanking) * 7);
	else 
		fare += ((vehicelOverallRanking * driverOverallRanking) * 4);

	if (wantAc == "YES")
		fare += 100;

	return fare;
}

void Ride::writeServiceInFile()
{
	ofstream writeInFile;	//used to write in file
	
	Service::writeServiceInFile();

	writeInFile.open("Service.txt", ios::app);
	if (writeInFile.is_open())
	{
		writeInFile << left << setw(11) << "Ride" << setw(6) << getNoOfPassenger() << setw(10) << getWantAc() << endl;
	}
	else
		cout << "Service File can't be opened for Writing for Ride";
	writeInFile.close();

}

Ride::~Ride() {}

//-----------------------------------Delivery class definition-------------------------------------

Delivery::Delivery() : goodsWeight(0), goodsType("") {};
Delivery::Delivery(Date bookingDate, Time bookingTime, Route route,
	string source, string destination, float distance, int status,
	float fuelrate, int customerID, int driverID, int vehicleID,
	int fare, float vehicleRanking, float driverRanking,
	float weight, string type)
: Service(bookingDate, bookingTime, route,
		source, destination, distance, status, fuelrate, customerID,
		driverID, vehicleID, fare, vehicleRanking, driverRanking),
	goodsWeight(weight), goodsType(type) {}
//setter
void Delivery::setWeight(float weight) 
{
	this->goodsWeight = weight;
}
void Delivery::setGoodType(string type) 
{
	this->goodsType = type;
}
//getter
float Delivery::getWeight() const 
{
	return this->goodsWeight;
}
string Delivery::getGoodType() const 
{
	return goodsType;
}
//pure Virtual
void Delivery::setRideTypeDetails(float weight, string type)
{
	this->goodsWeight = weight;
	this->goodsType = type;
}
void Delivery::getRideTypeDetails(float& weight, string& type) const 
{
	weight = getWeight();
	type = getGoodType();
}

float Delivery::CalculateFare(float mileage, float vehicelOverallRanking, float driverOverallRanking)
{
	float fare;
	fare = (getDistance() / mileage) * getFuelRate();

	if (vehicelOverallRanking * driverOverallRanking > 20)
		fare += ((vehicelOverallRanking * driverOverallRanking) * 12);
	else if (vehicelOverallRanking * driverOverallRanking > 15)
		fare += ((vehicelOverallRanking * driverOverallRanking) * 10);
	else if (vehicelOverallRanking * driverOverallRanking > 10)
		fare += ((vehicelOverallRanking * driverOverallRanking) * 7);
	else
		fare += ((vehicelOverallRanking * driverOverallRanking) * 4);


	if (goodsWeight >= 500)
		fare += 1300;
	else if (goodsWeight >= 400)
		fare += 1100;
	else if (goodsWeight >= 300)
		fare += 800;
	else if (goodsWeight >= 200)
		fare += 500;
	else if (goodsWeight >= 100)
		fare += 200;
	else if (goodsWeight >= 50)
		fare += 100;
	else if (goodsWeight >= 10)
		fare += 30;
	if (goodsWeight >= 5)
		fare += 15;

	return fare;
}

Delivery::~Delivery() {}

void Delivery::writeServiceInFile()
{
	ofstream writeInFile;	//used to write in file

	Service::writeServiceInFile();

	writeInFile.open("Service.txt", ios::app);
	if (writeInFile.is_open())
	{
		writeInFile << left << setw(11) << "Delivery" << setw(6) << getWeight() << setw(10) << getGoodType() << endl;
	}
	else
		cout << "Service File can't be opened for Writing for Delivery";
	writeInFile.close();
}

//-----------------------------------TMS class definition--------------------------------------

TMS::TMS() : driver(), customer(), loginAs(loggedOut) {}
TMS::TMS(User loginAs) : driver(), customer(), loginAs(loginAs) {}
User TMS::Sign_IN(int RequestFromAdmin = 0)
{
	//request from Admin means if TMS class admin adds new Customer or Driver
	//RequestFromAdmin != 0 means that New Driver/Customer is being added by ADMIN

	ifstream readFromFile;	//used to get data from file 
	ofstream writeInfile;	//used to write in file

	bool stopReading = false;
	User loginAs = loggedOut;
	int input, pin, fID;
	int newAccount = 0;
	int  fPin, fLogin;		//f = file
	string fileUserName, userName;

	if (RequestFromAdmin == 0)
	{
		cout << "1. Admin\n";
		cout << "2. Customer\n";
		cout << "3. Driver\n";
		cout << "4. Exit\n";
		cout << "login as: \n";
		cin >> input;
		while (input > 4 || input < 1)
		{
			cin.clear();
			cin.ignore();
			cout << "Select from 1-4 : ";
			cin >> input;
		}
	}
	else
	{
		input = RequestFromAdmin;
	}

	if (input == 1)
		loginAs = asAdmin;
	else if (input == 2)
		loginAs = asCustomer;
	else if (input == 3)
		loginAs = asDriver;
	if (input == 4)
		return EXIT;
	
	//This portion runs when new account is made by User, it will not run when Admin creates account for Customer or Driver
	if (RequestFromAdmin == 0)
	{
		do
		{
			bool again = true;

			readFromFile.open("LOGIN DETAILS.txt", ios::in);
			if (readFromFile.is_open())
			{
				cout << "Enter userName : ";
				while (again)
				{
					try
					{
						cin >> userName;
						if (userName.length() > 10 || userName.length() < 5)
							throw string("Wrong Username, Enter Again : ");

						again = false;
					}
					catch (string error)
					{	
						cin.clear();
						cin.ignore();
						cout << error;
					}
				}
				//reading from file 
				while (readFromFile >> fileUserName >> fPin >> fLogin >> fID && !stopReading)
				{
					if (userName == fileUserName && loginAs == fLogin)
					{
						again = true;	//bool set to true again to try catch for PIN

						cout << "Enter 4 digit pin : ";
						while (again)
						{
							try
							{
								cin >> pin;
								if (pin != fPin)
									throw string("Wrong PIN, Try Again : ");
								else if (pin == fPin)
								{
									cout << "Successfully Logged in";
									stopReading = true;		//if login than stop reading from file
									again = false;
								}
								else if (!cin)
									throw string("Enter only Integer : ");

								again = false;
							}
							catch (string error)
							{
								cin.clear();
								cin.ignore();
								cout << error;
							}
						}
					}
				}
			}
			else
				cout << "LOGIN DETAILS File can't be opened for reading Sign In";
			readFromFile.close();
		} while (stopReading == false && loginAs == asAdmin); //this loop will run if username is not found if LOGIN was for ADMIN



		//it will run when username is not found and create new account but new account of admin can't be created
		if (stopReading == false && loginAs != asAdmin)
		{
			cout << "Create a new account against this Phone No? No(0) Yes(1) : ";
			cin >> newAccount;
			if (newAccount == 1)
			{
				cout << "Set 4 Digit PIN : ";
				cin >> pin;
				while (pin < 1000 || pin > 9999)
				{
					cin.clear();
					cin.ignore();
					cout << "Enter 4 digits : ";
					cin >> pin;
				}
				writeInfile.open("LOGIN DETAILS.txt", ios::app);
				if (writeInfile.is_open())
				{
					writeInfile << userName << "\t" << pin << "\t" << loginAs << "\t";
				}
				else
					cout << "All Unique File IDs File can't be opened for wrting Sign In";
				writeInfile.close();
			}
			else
			{
				return loggedOut;
			}
		}
		//if an old user logged in than get his data from file
		if (newAccount == 0 && loginAs != asAdmin)
		{
			readFromFile.open("LOGIN DETAILS.txt", ios::app);
			if (readFromFile.is_open())
			{
				while (readFromFile >> fileUserName >> fPin >> fLogin >> fID)
				{
					if (userName == fileUserName && pin == fPin && loginAs == fLogin)
					{
						if (loginAs == asCustomer)
							customer.getCustomerFromFile(fID);
						else if (loginAs == asDriver)
						{
							driver.getDriverFromFile(fID);
							driver.setVehicle(driver.getVehicle().getVehicleFromFile(fID));
						}
					}
				}
			}
			else
				cout << "All Unique File IDs File can't be opened for reading Old user Sign IN";
			readFromFile.close();
		}
	}
	//This portion runs when Admin creates new account for Customer or Driver
	else if (RequestFromAdmin == 2 || RequestFromAdmin == 3)
	{
		bool again = true;

		readFromFile.open("LOGIN DETAILS.txt", ios::in);
		if (readFromFile.is_open())
		{
			cout << "Enter userName : ";
			while (again)
			{
				try
				{
					cin >> userName;
					if (userName.length() > 10 || userName.length() < 5)
						throw string("Wrong Username, Enter Again : ");

					//reading from file 
					while (readFromFile >> fileUserName >> fPin >> fLogin >> fID)
					{
						if (userName == fileUserName && loginAs == fLogin)
						{
							/*if same username is found in file than it moves the cursor to the start of file
							and throw exception to take input again and check again */
							readFromFile.clear();
							readFromFile.seekg(0, ios::beg);
							throw string("UserName already taken, Try Again :");
						}
					}
					readFromFile.close();
					again = false;
				}
				catch (string error)
				{
					cin.clear();
					cin.ignore();
					cout << error;
				}
			}
		}
		else
			cout << "LOGIN DETAILS file can't be Opened for New Account Reuqest by Admin";
		
		cout << "Set 4 Digit Pin : ";
		cin >> pin;
		while (pin < 1000 || pin > 9999)
		{
			cin.clear();
			cin.ignore();
			cout << "Enter 4 digits : ";
			cin >> pin;
		}
		writeInfile.open("LOGIN DETAILS.txt", ios::app);
		if (writeInfile.is_open())
		{
			writeInfile << userName << "\t" << pin << "\t" << loginAs << "\t";
		}
		else
			cout << "All Unique File IDs File can't be opened for wrting Sign In";
		writeInfile.close();
	}
	return loginAs;
}
void TMS::LOGGED_IN(User loginAs)
{
	int option; //holds menu option

	if (loginAs == asDriver)
	{
		//it means that the driver has already not been registered
		if (driver.getDriverID() == 0)
			driver.AddNewDriver();
		else
		{
			system("cls");
			cout << "\n1. View Personal Details";		//done
			cout << "\n2. View Vehicle";				//done
			cout << "\n3. Add/Remove Vehicle";			//done
			cout << "\n4. View Service Request";		//done
			cout << "\n5. View Service History";		//done
			cout << "\n6. Delete Account (Driver) ";	//done
			cout << "\n7. Log out\nSelect : ";			//done
			cin >> option;
			while (option > 7 || option < 1)
			{
				cin.ignore();
				cin.clear();
				cout << "Enter between 1 - 7 : ";
				cin >> option;
			}
			switch (option)
			{
			case 1:
				//View Personal Details
				
				cout << driver << endl;
				system("pause");
				LOGGED_IN(asDriver);
				break;
			case 2:
				//View Vehicle
				
				cout << driver.getVehicle();
				system("pause");
				LOGGED_IN(asDriver);
				break;
			case 3:
				//Add/Remove Vehicle
			{
				system("cls");
				int temp = 0;
				bool tryAgain = true;
				cout << "To add a new Vehicle, Old Vehicle will be deleted";
				cout << "\nDelete? No(0) Yes(1) : ";
				while (tryAgain)
				{
					try
					{
						cin >> temp;

						if (temp != 1 && temp != 0 || !cin)
							throw string("Select 1 or 2 : ");

						tryAgain = false;
					}
					catch (string error)
					{
						cin.clear();
						cin.ignore();
						cout << error;
					}
				}
				if (temp == 1)
				{
					int fileVehicleStatus, fileVehicleID;
					string temp;
					bool vehicleIsFree = false, vehicleFound = false;
					fstream ReadVehicle;

					//checking if the Vehicle is free or Not, becuase you can't delete a Vehicle while it's not free
					ReadVehicle.open("Vehicle.txt");
					if (ReadVehicle.is_open())
					{
						while (ReadVehicle >> temp >> fileVehicleID >> temp >> temp >> temp >> temp
							>> temp >> temp >> temp >> temp >> temp >> fileVehicleStatus >> temp >> temp >> temp >> temp)
						{
							if (driver.getVehicle().getVehicleID() == fileVehicleID)
							{
								vehicleFound = true; //vehicel is Found now will check if the vehicle is free or not
								if (fileVehicleStatus == 0)
								{
									vehicleIsFree = true;
									ReadVehicle.close();
								}	
							}
							else
								vehicleFound = false; //if there is no vehicle available of the driver
						}
					}
					else
						cout << "Vehicle File can't be opened for Deleting";
					ReadVehicle.close();

					//if Vehicle is free it will remove old vehicle and ask to add a new vehicle
					//if vehicle is found only than it will delete else it will just add New Vehicle
					if (vehicleIsFree == true)
					{
						driver.removePreviousVehicleOfDriver();
						cout << "DATA DELETED";
						driver.addVehicle();
					}
					//if the vehicle is not found it will ask for input of the vehicle
					if (vehicleFound == false)
					{
						cout << "\nNo Previous Vehicle Found";
						driver.addVehicle();
					}
				
					//setting/updating the vehicle in Driver again
					driver.setVehicle(driver.getVehicle().getVehicleFromFile(driver.getDriverID()));
					system("pause");
					LOGGED_IN(asDriver);
				}
			}
				system("pause");
				break;
			case 4:
				//View Service Request
				
				viewServiceRequest();
				system("pause");
				break;
			case 5:
				//View Service History
				
				printServiceHistory(driver.getDriverID());
				system("pause");
				break;
			case 6:
				//Delete Account (Driver)
				
				removeDriver(driver.getDriverID());
				system("pause");
				Sign_IN();
				break;
			case 7:
				//LogOut
				system("cls");
				system("pause");
				Sign_IN();
				break;
			}
		}
	}
	else if (loginAs == asCustomer)
	{
		//0 means that the customer has already not been registered
		if (customer.getCustomerID() == 0)
			customer.addNewCustomer();
		else
		{
			system("cls");
			cout << "\n1. View Personal Details";		//done
			cout << "\n2. Service Request";
			cout << "\n3. View Service History";		//done
			cout << "\n4. Delete Account (Customer)";	//done
			cout << "\n5. Log out\nSelect : ";			//done
			cin >> option;
			while (option > 5 || option < 1)
			{
				cin.ignore();
				cin.clear();
				cout << "Enter between 1 - 7 : ";
				cin >> option;
			}
			switch (option)
			{
			case 1:
				//View Personal Details
				cout << customer << endl;
				system("pause");
				LOGGED_IN(asCustomer);
				break;
			case 2:
				//Service Request
				BookAService();
				system("pause");
				break;
			case 3:
				//View Service History
				printServiceHistory(customer.getCustomerID());
				system("pause");
				break;
			case 4:
				//Delete Account (Customer)
				removeCustomer(customer.getCustomerID());
				system("pause");
				Sign_IN();
				break;
			case 5:
				//LogOut
				system("cls");
				Sign_IN();
				break;

			}
		}	
	}
	else if (loginAs == asAdmin)
	{
		system("cls");
		cout << "\n1. Add New Customer";		//done
		cout << "\n2. Delete Customer Account";	//done
		cout << "\n3. Add New Driver";			//done
		cout << "\n4. Delete Driver Account";	//done
		cout << "\n5. Print one Customer";		//done
		cout << "\n6. Print one Driver";		//done
		cout << "\n7. Print one Vehicle";		//done
		cout << "\n8. Print All Customers";		//done
		cout << "\n9. Print All Drivers";		//done
		cout << "\n10. Print All Vehicles";		//done
		cout << "\n11. Print Service History of Specific Customer";		//done
		cout << "\n12. Print Service History of Specific Driver";		//done
		cout << "\n13. Print Service History of Specific Vehicle";		//done
		cout << "\n14. Print Drivers above 4.5 Ranking";				//done
		cout << "\n15. Print License Details of Drivers";				//done
		cout << "\n16. Print Drivers with Income";						//done
		cout << "\n17. Print Pending Services on Specific Date";
		cout << "\n18. Print All Pending Services";			//done
		cout << "\n19. Print All Cancelled Services";		//done
		cout << "\n20. Log out\nSelect: ";					//done
		cin >> option;
		while (option > 20 || option < 1)
		{
			cin.ignore();
			cin.clear();
			cout << "Enter between 1 - 20 : ";
			cin >> option;
		}
		switch (option)
		{
		case 1:
			//Add New Customer
			addNewCustomer();
			system("pause");
			break;
		case 2:
			//Delete Customer Account
		{
			int id = 0;
			bool customerFoundAndDeleted = false;
			cout << "Enter 4 digit ID to remove Customer or 1 to Go Back : ";
			while (customerFoundAndDeleted == false && id != 1)
			{
				try
				{
					cin >> id;
					customerFoundAndDeleted = removeCustomer(id);
					if (customerFoundAndDeleted == false)
						throw string("Enter again : ");
					else if (id < 1000 || id > 9999 || !cin)
						throw string("Enter 4 digit ID : ");
				}
				catch (string error)
				{
					cout << error << " or press 1 to go back : ";
				}
			}
		}
		break;
		case 3:
			//Add New Driver
			addNewDriver();
			system("pause");
			break;
		case 4:
			//Delete Driver Account
		{
			int id = 0;
			bool driverFoundAndDeleted = false;
			cout << "Enter 4 digit ID to remove Driver or 1 to Go Back : ";
			while (driverFoundAndDeleted == false && id != 1)
			{
				try
				{
					cin >> id;
					driverFoundAndDeleted = removeDriver(id);
					if (driverFoundAndDeleted == false)
						throw string("Enter again : ");
					else if (id < 1000 || id > 9999 || !cin)
						throw string("Enter 4 digit ID : ");
				}
				catch (string error)
				{
					cin.clear();
					cin.ignore();
					cout << error << " or press 1 to go back : ";
				}
			}
		}
			system("pause");
		break;
		case 5:
			//Print Specific Customer
		{
			int id = 0;
			bool again = true;
			cout << "Enter Customer ID or 1 to Return : ";
			while (again)
			{
				try
				{
					cin >> id;
					if (id == 1)
						again = false;
					else if (isValidID(id, asCustomer) == false || !cin)
						throw string("Enter Again : ");

					again = false;
				}
				catch (string error)
				{
					cin.clear();
					cin.ignore();
					cout << error << " or 1 to Return : ";
				}
			}
			//if user has not choosed to return and has entered an ID
			if (id != 1)
				printCustomers(id);
		}
			system("pause");
		break;
		case 6:
			//Print Specific Driver
		{
			int id = 0;
			bool again = true;
			cout << "Enter Driver ID or 1 to Return : ";
			while (again)
			{
				try
				{
					cin >> id;
					if (id == 1)
						again = false;
					else if (isValidID(id, asDriver) == false || !cin)
						throw string("Enter Again : ");

					again = false;
				}
				catch (string error)
				{
					cin.clear();
					cin.ignore();
					cout << error << " or 1 to Return : ";
				}
			}
			//if user has not choosed to return and has entered an ID
			if (id != 1)
				printDrivers(id);
		}
		system("pause");
		break;
		case 7:
			//Print Specific Vehicle
		{
			int id = 0;
			bool again = true;
			string temp;
			int fileVehicleID;
			cout << "Enter Vehicle ID or 1 to Return : ";
			while (again)
			{
				try
				{
					cin >> id;
					if (id == 1) //loop will end if user chooses to return
						again = false;
					else if (!cin)
						throw string("Enter 4 Digit ID,");
					//if id is not 4 digit
					else if (id > 9999 || id < 1000)
						throw string("Enter 4 Digit ID,");

					//open the Vehicle file to see if the entered ID is of Vehicle or not
					fstream readVehicle;
					readVehicle.open("Vehicle.txt");
					if (readVehicle.is_open())
					{
						while (readVehicle >> temp >> fileVehicleID >> temp >> temp >> temp >> temp >> temp
							>> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp)
						{
							//if a valid Id is found the loop ends
							if (fileVehicleID == id)
							{
								again = false;
								readVehicle.close();
							}
						}
					}
					readVehicle.close();

					if (again == true)
						throw string("Customer ID not found, Enter Again ");
				}
				catch (string error)
				{
					cin.clear();
					cin.ignore();
					cout << error << " or 1 to Return : ";
				}
			}
			//if user has not choosed to return and has entered an ID
			if (id != 1)
				printVehicles(id);
		}
		system("pause");
		break;
		case 8:
			//Print all Customers
			printCustomers();
			system("pause");
			break;
		case 9:
			//Print all Drivers
			printDrivers();
			system("pause");
			break;
		case 10:
			//Print all Vehicles
			printVehicles();
			system("pause");
			break;
		case 11:
			//Service history of Specific Customer
		{
			int id = 0;
			bool again = true;
			cout << "Enter Customer ID or 1 to Return : ";
			while (again)
			{
				try
				{
					cin >> id;
					if (id == 1)
						again = false;
					else if (isValidID(id, asCustomer) == false || !cin)
						throw string("Enter Again, ");

					again = false;
				}
				catch (string error)
				{
					cin.clear();
					cin.ignore();
					cout << error << " or 1 to Return : ";
				}
			}
			//if user has not choosed to return and has entered an ID
			if (id != 1)
				printServiceHistory(id);
		}
		system("pause");
		break;
		case 12:
			//Service history of Specific Driver
		{
			int id = 0;
			bool again = true;
			cout << "Enter Driver ID or 1 to Return : ";
			while (again)
			{
				try
				{
					cin >> id;
					if (id == 1)
						again = false;
					else if (isValidID(id, asDriver) == false || !cin)
						throw string("Enter Again, ");

					again = false;
				}
				catch (string error)
				{
					cin.clear();
					cin.ignore();
					cout << error << " or 1 to Return : ";
				}
			}
			//if user has not choosed to return and has entered an ID
			if (id != 1)
				printServiceHistory(id);
		}
		system("pause");
		break;
		case 13:
			//Service history of Specific Vehicle
		{
			int id = 0;
			bool again = true;
			string temp;
			int fileVehicleID;
			cout << "Enter Vehicle ID or 1 to Return : ";
			while (again)
			{
				try
				{
					cin >> id;
					if (id == 1) //loop will end if user chooses to return
						again = false;
					else if (!cin)
						throw string("Enter 4 Digit ID,");
					//if id is not 4 digit
					else if (id > 9999 || id < 1000)
						throw string("Enter 4 Digit ID,");

					//open the Vehicle file to see if the entered ID is of Vehicle or not
					fstream readVehicle;
					readVehicle.open("Vehicle.txt");
					if (readVehicle.is_open())
					{
						while (readVehicle >> temp >> fileVehicleID >> temp >> temp >> temp >> temp >> temp
							>> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp)
						{
							//if a valid Id is found the loop ends
							if (fileVehicleID == id)
							{
								again = false;
								readVehicle.close();
							}
						}
					}
					readVehicle.close();

					if (again == true)
						throw string("Customer ID not found, Enter Again ");
				}
				catch (string error)
				{
					cin.clear();
					cin.ignore();
					cout << error << " or 1 to Return : ";
				}
			}
			//if user has not choosed to return and has entered an ID
			if (id != 1)
				printServiceHistory(id);
		}
		system("pause");
		break;
		case 14:
			//Print Driver above 4.5 Ranking
			printHighRankDriver();
			system("pause");
			break;
		case 15:
			//Print License Details of all Drivers
			printLicensesDetails();
			system("pause");
			break;
		case 16:
			//Print Driver with Income
			printIncome();
			system("pause");
			break;
		case 17:
			//Print Pending Services on Specific Date
		{
			int date = 0 ;
			cin >> date;
			printAllPendingServices(date);
		}
			break;
		case 18:
			//Print All Pending Services
			printAllPendingServices();
			system("pause");
			break;
		case 19:
			//Print All Cancelled Services
			printAllCancelledServices();
			system("pause");
			break;
		case 20:
			//Log Out
			Sign_IN();
			break;
		}
	}
}

void TMS::BookAService()
{
	int match = 0;
	fstream getServiceFromFile;
	string bookingTime, source, destination, RideOrDelivery;
	float distance, fuelrate, vehicleRanking, driverRanking;
	int	customerID, driverID, fileVehicleID, fare;
	int day, month, year;
	int serviceStatus;	//1 for Completed, 2 if Pending and 3 if Cancelled, 4 not approved
	int route;			//0 for Intracity, 1 for Intercity 
	float noOfPassengersOrGoodsWeight; //holds NumOfPassengers if it was Ride else holds Goods Weight if it was Delivery
	string wantAcOrGoodsType;		 //holds WantAc (YES/NO) if it was Ride else holds Goods Type if it was Delivery
	bool OldServiceCompleted = true;
	int lineNumberOfPendingService = 0;
	
	getServiceFromFile.open("Service.txt");
	if (getServiceFromFile.is_open())
	{
		while (getServiceFromFile >> customerID >> driverID >> fileVehicleID >> day >> month >> year >> bookingTime
			>> route >> source >> destination >> distance >> serviceStatus >> fuelrate >> fare >> driverRanking
			>> vehicleRanking >> RideOrDelivery >> noOfPassengersOrGoodsWeight >> wantAcOrGoodsType)
		{
			//if there will be a pending service than this will be useful as we will get the line no of the service when the loop break, we will have the line no
			++lineNumberOfPendingService;
			//if customer is already in a Pending Service he will be shown 
			if (customerID == customer.getCustomerID() && serviceStatus == 2)
			{
				OldServiceCompleted = false;
				break;
			}
			//checking if the service has been made completed by driver becuase than customer has to give ranking and give fare
			if (customerID == customer.getCustomerID() && serviceStatus == 1 && vehicleRanking == 0 && driverRanking == 0)
			{
				OldServiceCompleted = false;
				break;
			}
			//if service needs approval from driver
			if (customerID == customer.getCustomerID() && serviceStatus == 4)
			{
				OldServiceCompleted = false;
				break;
			}
		}
	}
	else
		cout << "Service File can't be opened for counting service that are pending driver approval";
	getServiceFromFile.close();

	//if there is no Pending Service
	if (OldServiceCompleted == true)
	{
		if (serviceStatus == 3 && customerID == customer.getCustomerID())
		{
			cout << "\nThe Service has been Cancelled:\n";
			cout << "\nCustomer ID : " << customerID;
			cout << "\nSource : " << source;
			cout << "\nDestination : " << destination;
			cout << "\nRoute : "; route == 0 ? cout << "Intracity" : cout << "Intercity";
			cout << "\nRide or Delivery : " << RideOrDelivery;
			cout << "\nFare : " << fare;
			cout << "\n---------------------------------------\n";
			cout << "Request a new Service\n";
			system("pause");
		}

		int choice, location;
		string source = "", destination = "";
		float distance = 0;
		TransportionCategory rideOrDelivery = CategoryNull; //Enum
		Route route = RouteNull;	//Enum
		bool tryAgain = true;

		cout << "Book:\n1. Ride\n2.Delivery\nEnter : ";
		while (tryAgain)
		{
			try
			{
				cin >> choice;

				if (choice != 1 && choice != 2 || !cin)
					throw string("Select only 1 or 2: ");

				tryAgain = false;
			}
			catch (string error)
			{
				cin.clear();
				cin.ignore();
				cout << error;
			}
		}
		choice == 1 ? rideOrDelivery = ride : rideOrDelivery = delivery;


		tryAgain = true;
		cout << "Select:\n1. Intracity\n2. Intercity\nEnter : ";
		while (tryAgain)
		{
			try
			{
				cin >> choice;

				if (choice != 1 && choice != 2 || !cin)
					throw string("Select only 1 or 2: ");

				tryAgain = false;
			}
			catch (string error)
			{
				cin.clear();
				cin.ignore();
				cout << error;
			}
		}
		choice == 1 ? route = Intracity : route = Intercity;

		tryAgain = true;
		if (route == Intercity)
		{
			cout << "1. FSD\n2. LHR\n3. ISB\nSelect your Location : ";
			while (tryAgain)
			{
				try
				{
					cin >> location;

					if ((location != 1 && location != 2 && location != 3) || !cin)
						throw string("Select only 1 or 2 or 3: ");

					tryAgain = false;
				}
				catch (string error)
				{
					cin.clear();
					cin.ignore();
					cout << error;
				}
			}

			customer.selectIntercityOptions(location, source, destination, distance);
		}
		else if (route == Intracity)
		{
			customer.selectIntracityOptions(source, destination, distance);
		}

		int passenger = 0;
		string type;
		float weight;
		string wantAC;

		Service* servicePtr = nullptr;
		Ride rideObj;
		Delivery deliveryObj;

		if (rideOrDelivery == ride)
		{
			int temp;

			cout << "Enter no of Passengers : ";
			cin >> passenger;
			while (passenger < 0 || passenger > 60)
			{
				cin.clear();
				cin.ignore();
				cout << "Enter again : ";
				cin >> passenger;
			}
			cout << "Do you want AC? NO (0) YES (1) : ";
			cin >> temp;
			while (temp < 0 || temp > 1)
			{
				cin.clear();
				cin.ignore();
				cout << "Enter again : ";
				cin >> temp;
			}
			temp == 1 ? wantAC = "YES" : wantAC = "NO";

			rideObj.setNoOfPassenger(passenger);
			rideObj.setWantAc(wantAC);
			servicePtr = &rideObj;
		}
		else if (rideOrDelivery == delivery)
		{
			int temp;
			cout << "1. Courier\n2. Freight\n3. Oil\nSelect Delivery Type : ";
			cin >> temp;
			while (temp > 3 || temp < 1)
			{
				cin.clear();
				cin.ignore();
				cout << "Invalid Input, Enter again: ";
				cin >> temp;
			}
			if (temp == 1)
				type = "Courier";
			else if (temp == 2)
				type = "Freight";
			else
				type = "Oil";

			cout << "Enter Good Weight: ";
			cin >> weight;
			while (weight <= 0)
			{
				cin.clear();
				cin.ignore();
				cout << "Enter correct weight again : ";
				cin >> weight;
			}
			deliveryObj.setGoodType(type);
			deliveryObj.setWeight(weight);
			servicePtr = &deliveryObj;

		}

		Time currentTime;
		Date currentDate(currentTime.getCurrentDay(), currentTime.getCurrentMonth(), currentTime.getCurrentYear());

		servicePtr->setBookingDate(currentDate);
		servicePtr->setBookingTime(currentTime);
		servicePtr->setSource(source);
		servicePtr->setDestination(destination);
		servicePtr->setDistance(distance);
		servicePtr->setRoute(route);
		servicePtr->setServiceStatus(4); //1 for Completed, 2 if Pending and 3 if Cancelled, 4 Pendind Aproval from Driver

		//finding totalMatches of Vehicles according to customer's Requirement
		int totalMatch = 0;
		int fileVehicleID, fileRegNo, fileOwnerDriverId, fileNumOfSeats, fileVehicleStatus, fileRideOrDelivery, fileRoute, fileTotalVehicleServices, fileDay, fileMonth, fileYear;
		float fileAvgMilage, fileVehicleOverallRanking;
		string fileVehicleModel, fileVehicleType, fileVehicleLicenseType, fileDate;

		ifstream ReadFromFile;
		ReadFromFile.open("Vehicle.txt");
		//finding the toal matched vehicle from file
		if (ReadFromFile.is_open())
		{

			while (ReadFromFile >> fileOwnerDriverId >> fileVehicleID >> fileVehicleModel >> fileVehicleType >> fileRegNo
				>> fileVehicleLicenseType >> fileDay >> fileMonth >> fileYear >> fileAvgMilage >> fileNumOfSeats
				>> fileVehicleStatus >> fileRideOrDelivery >> fileRoute >> fileVehicleOverallRanking >> fileTotalVehicleServices)
			{
				/*
				vehicleStatus should be free (0)
				either fileRoute equals to Both(2) or the route given by user
				either fileRideOrDelivery of Vehicle equals to Both(2) or the option (0) or (1) given by user
				num of seats of vehicle should be atleast equal to num of Passenger asked.
				driver's seats is subtracted from total seats
				*/
				if (fileVehicleStatus == 0 && (route == fileRoute || fileRoute == 2)
					&& (rideOrDelivery == fileRideOrDelivery || fileRideOrDelivery == 2) && (fileNumOfSeats - 1) >= passenger)
				{

					if (rideOrDelivery == delivery)
					{
						//showing vehicle by maximum weight it can delivery //if weigth is <=10 than these vehicle will be selected
						if (type == "Courier" && weight <= 10)
						{
							if (fileVehicleType == "Bike" || fileVehicleType == "Scooter" || fileVehicleType == "Rickshaw" || fileVehicleType == "Car")
								totalMatch++;
						}
						//if (10 < weigth <= 20) than these vehicle will be selected
						else if (type == "Courier" && weight > 10 && weight <= 20)
						{
							if (fileVehicleType == "Rickshaw" || fileVehicleType == "Car")
								totalMatch++;
						}
						//if weigth is > 20 than these vehicle will be selected
						else if (type == "Courier" && weight > 20)
						{
							if (fileVehicleType == "Shahzor" || fileVehicleType == "Mazda - Titan" || fileVehicleType == "Truck");
							totalMatch++;
						}

						//if Frieght is selected than these vehicle will be selected
						else if (type == "Freight")
						{
							if (fileVehicleType == "Shahzor" || fileVehicleType == "Mazda - Titan" || fileVehicleType == "Truck");
							totalMatch++;
						}

						//if Oil is selected than only Tanker Truck will be selected
						else if (type == "Oil")
							if (fileVehicleType == "Tanker - Truck")
								totalMatch++;
					}
					else if (rideOrDelivery == ride)
					{
						if (wantAC == "YES" && (fileVehicleType == "Car" || fileVehicleType == "Bus" || fileVehicleType == "APV"
							|| fileVehicleType == "Campervans" || fileVehicleType == "Caravan"))
							totalMatch++;
						else
							totalMatch++;
					}
				}
			}
		}
		else
			cout << "Vehicle File can't be opened for Total Matches";
		ReadFromFile.close();

		//to hold all the rankings of vehicle that should be printed 
		float* allOverallRanking = new float[totalMatch];
		//to hold the Vehicle IDs of vehicle that have been printed/show to user so that it don't print again
		int* allPrintedVehicleID = new int[totalMatch];

		//initilizes with zero
		for (int i = 0; i < totalMatch; i++)
			allPrintedVehicleID[i] = 0;

		//taking Overall Ranking of all Vehicles that are to be printed from File
		ReadFromFile.open("Vehicle.txt");
		if (ReadFromFile.is_open())
		{
			int i = 0;

			while (ReadFromFile >> fileOwnerDriverId >> fileVehicleID >> fileVehicleModel >> fileVehicleType >> fileRegNo
				>> fileVehicleLicenseType >> fileDay >> fileMonth >> fileYear >> fileAvgMilage >> fileNumOfSeats
				>> fileVehicleStatus >> fileRideOrDelivery >> fileRoute >> fileVehicleOverallRanking >> fileTotalVehicleServices)
			{
				if (fileVehicleStatus == 0 && (route == fileRoute || fileRoute == 2)
					&& (rideOrDelivery == fileRideOrDelivery || fileRideOrDelivery == 2) && (fileNumOfSeats - 1) >= passenger)
				{
					if (rideOrDelivery == delivery)
					{
						//showing vehicle by maximum weight it can delivery
						//if weigth is <=10 than these vehicle will be selected
						if (type == "Courier" && weight <= 10)
						{
							if (fileVehicleType == "Bike" || fileVehicleType == "Scooter" || fileVehicleType == "Rickshaw" || fileVehicleType == "Car")
							{
								allOverallRanking[i] = fileVehicleOverallRanking;
								i++;
							}
						}
						//if (10 < weigth <= 20) than these vehicle will be selected
						else if (type == "Courier" && weight > 10 && weight <= 20)
						{
							if (fileVehicleType == "Rickshaw" || fileVehicleType == "Car")
							{
								allOverallRanking[i] = fileVehicleOverallRanking;
								i++;
							}
						}
						//if weigth is > 20 than these vehicle will be selected
						else if (type == "Courier" && weight > 20)
						{
							if (fileVehicleType == "Shahzor" || fileVehicleType == "Mazda - Titan" || fileVehicleType == "Truck");
							{
								allOverallRanking[i] = fileVehicleOverallRanking;
								i++;
							}
						}

						//if Frieght is selected than these vehicle will be selected
						else if (type == "Freight")
						{
							if (fileVehicleType == "Shahzor" || fileVehicleType == "Mazda - Titan" || fileVehicleType == "Truck");
							{
								allOverallRanking[i] = fileVehicleOverallRanking;
								i++;
							}
						}

						//if Oil is selected than only Tanker Truck will be selected
						else if (type == "Oil")
							if (fileVehicleType == "Tanker - Truck")
							{
								allOverallRanking[i] = fileVehicleOverallRanking;
								i++;
							}
					}
					else if (rideOrDelivery == ride)
					{
						if (wantAC == "YES" && (fileVehicleType == "Car" || fileVehicleType == "Bus" || fileVehicleType == "APV"
							|| fileVehicleType == "Campervans" || fileVehicleType == "Caravan"))
						{
							allOverallRanking[i] = fileVehicleOverallRanking;
							i++;
						}
						else
							allOverallRanking[i] = fileVehicleOverallRanking;
							i++;
					}
				}
			}
		}
		else
			cout << "Vehicle File can't be opened for Copying Overall Ranking";
		ReadFromFile.close();

		//sorting Ranking from highest to lowest
		sortRankingInDescending(allOverallRanking, totalMatch);

		int index = 0;
		bool alreadyPrinted = false;
		ReadFromFile.open("Vehicle.txt");
		//printing matched vehicles
		if (ReadFromFile.is_open())
		{
			//runs until all the matched vehicles are printed
			for (int i = 0; i < totalMatch; i++)
			{
				//reads data from file
				while (ReadFromFile >> fileOwnerDriverId >> fileVehicleID >> fileVehicleModel >> fileVehicleType >> fileRegNo
					>> fileVehicleLicenseType >> fileDay >> fileMonth >> fileYear >> fileAvgMilage >> fileNumOfSeats
					>> fileVehicleStatus >> fileRideOrDelivery >> fileRoute >> fileVehicleOverallRanking >> fileTotalVehicleServices)
				{
					if (fileVehicleStatus == 0 && (route == fileRoute || fileRoute == 2)
						&& (rideOrDelivery == fileRideOrDelivery || fileRideOrDelivery == 2) && (fileNumOfSeats - 1) >= passenger)
					{
						//gets overall ranking from file and matches from the array of to print in decensing order
						if (allOverallRanking[i] == fileVehicleOverallRanking)
						{
							//sees if the vehicle is to be printed or not
							for (int a = 0; a < totalMatch; a++)
							{
								//compares fileVehicleID with the Vehicle IDs of all printed vehicle, if it is found than the flag is 
								//made true and it don't print that vehicle
								if (fileVehicleID == allPrintedVehicleID[a])
								{
									alreadyPrinted = true;
								}
							}

							fstream readingDriver;

							int driverStatus, totalServices, driverID, driverVehicleID, age, day, month, year;
							float income, experience, driverOverallRanking;
							string fName, lName, cnic, license;
							bool driverFound = false;

							readingDriver.open("Drivers.txt");
							if (readingDriver.is_open())
							{
								while (readingDriver >> driverID >> driverVehicleID >> fName >> lName >> day >> month >> year >> age >> cnic >>
									experience >> license >> driverOverallRanking >> income >> driverStatus >> totalServices)
								{
									//if vehicle Id from Driver file == Vehicle Id from Vehicle File
									if (driverVehicleID == fileVehicleID)
									{
										//if the Driver is found for the vehicle the loop breaks
										readingDriver.close();
									}
								}
							}
							else
								cout << "Drivers File can't be opened for showing Vehicle";
							readingDriver.close();

							servicePtr->setCustomerID(customer.getCustomerID());
							servicePtr->setFuelRate(200);
							servicePtr->setFare(servicePtr->CalculateFare(fileAvgMilage, fileVehicleOverallRanking, driverOverallRanking));

							//prints the vehicle
							if (alreadyPrinted == false)
							{
								cout << "\n------------------------------------------";
								cout << "\nID : " << fileVehicleID;
								cout << "\nModel : " << fileVehicleModel;
								cout << "\nType : " << fileVehicleType;
								cout << "\nVehicle Ranking : " << fileVehicleOverallRanking << "(" << fileTotalVehicleServices << ")";
								cout << "\nDriver Ranking : " << driverOverallRanking << "(" << totalServices << ")";
								cout << "\nFare : " << servicePtr->getFare();
								cout << "\nStatus : ";
								if (driverStatus == 1)// 1 for free, 2 if booked
									cout << "Free";

								cout << "\n------------------------------------------\n";

								allPrintedVehicleID[index++] = fileVehicleID;
							}
							//sets the flag to false to print check and print next vehicle
							alreadyPrinted = false;
						}
					}
				}
				//set the file to read from start
				ReadFromFile.clear();
				ReadFromFile.seekg(0, ios::beg);
			}
			if (totalMatch == 0)
				cout << "No Vehicle currently available";
		}
		else
			cout << "Vehicle File can't be opened for Printing Vehicles";
		ReadFromFile.close();

		if (totalMatch != 0)
		{
			int selectedID;
			bool found = false;

			//selecting Vehicle to book
			cout << "\nSelect Vehicle ID to book :";
			while (found == false)
			{
				try
				{
					cin >> selectedID;
					if (selectedID > 9999 || selectedID < 1000)
						throw string("Enter 4 digits ");
					if (!cin)
						throw string("Enter Integer ");

					for (int i = 0; i < totalMatch, found != true; i++)
					{
						if (selectedID != allPrintedVehicleID[i])
							found = false;
						else
							found = true;
					}

					if (found == false)
						throw string("Enter from above ID ");
				}
				catch (string error)
				{
					cin.clear();
					cin.ignore();
					cout << error;
				}
			}

			int driverID, driverVehicleID;
			float driverOverallRanking;
			string temp;
			fstream readingDriver;
			readingDriver.open("Drivers.txt");
			if (readingDriver.is_open())
			{
				while (readingDriver >> driverID >> driverVehicleID >> temp >> temp >> temp >> temp >> temp >> temp >> temp >>
					temp >> temp >> driverOverallRanking >> temp >> temp >> temp)
				{
					//if vehicle Id from Driver file == Vehicle Id selected by customer
					if (driverVehicleID == selectedID)
					{
						//if the Driver is found for the vehicle the loop breaks
						readingDriver.close();
					}
				}
			}
			else
				cout << "Drivers File can't be opened for showing Vehicle";
			readingDriver.close();

			//setting the vehicleID, driverID, and Fare of service of the selected Vehicle to write in File
			servicePtr->setDriverID(driverID);
			servicePtr->setVehicleID(driverVehicleID);
			driver.getDriverFromFile(driverID);
			driver.setVehicle(driver.getVehicle().getVehicleFromFile(driverID));

			//setting fare of service towrite in file
			servicePtr->setFare(servicePtr->CalculateFare(driver.getVehicle().getAvgMileage(), driver.getVehicle().getOverallRanking(), driverOverallRanking));

			//driver ranking and vehicle ranking is set to 0 for the service because the service is still not completed it is just booked
			servicePtr->setDriverRanking(0);
			servicePtr->setVehicleRanking(0);

			servicePtr->writeServiceInFile();

			cout << "Service Request has been sent to Driver";

		}
	}
	else if (OldServiceCompleted == false)
	{
		//checking if the service has been made completed by driver becuase than customer has to give ranking and give fare
		if (serviceStatus == 1)
		{
			//==========================================================================================================================================

			//Opens the Service to Updte the Service Status in File
			int lineNoService = 0;
			Service* servicePtr = nullptr;
			Ride rideObj;
			Delivery deliveryObj;

			//getting the service data by line number of pending Service
			getServiceFromFile.open("Service.txt");
			if (getServiceFromFile.is_open())
			{
				getServiceFromFile >> customerID >> driverID >> fileVehicleID >> day >> month >> year >> bookingTime
					>> route >> source >> destination >> distance >> serviceStatus >> fuelrate >> fare >> driverRanking
					>> vehicleRanking >> RideOrDelivery >> noOfPassengersOrGoodsWeight >> wantAcOrGoodsType;

				while (!getServiceFromFile.eof())
				{
					//counting the 
					lineNoService++;

					//if the line number of pending service if found than that service data will be taken from file
					if (lineNoService == lineNumberOfPendingService)
					{
						//geeting the data of the Service Request that was put on by Customer and accepted by driver
						if (RideOrDelivery == "Ride")
						{
							Time bTime = bookingTime;
							Route way;
							//0 for Intracity, 1 for Intercity 
							route == 0 ? way = Intracity : way = Intercity;
							rideObj = Ride(Date(day, month, year), bTime, way, source, destination, distance, serviceStatus, fuelrate, customerID,
								driverID, fileVehicleID, fare, vehicleRanking, driverRanking, noOfPassengersOrGoodsWeight, wantAcOrGoodsType);
							servicePtr = &rideObj;
						}
						else
						{
							Time bTime = bookingTime;
							Route way;
							//0 for Intracity, 1 for Intercity 
							route == 0 ? way = Intracity : way = Intercity;
							deliveryObj = Delivery(Date(day, month, year), bTime, way, source, destination, distance, serviceStatus, fuelrate, customerID,
								driverID, fileVehicleID, fare, vehicleRanking, driverRanking, noOfPassengersOrGoodsWeight, wantAcOrGoodsType);
							servicePtr = &deliveryObj;
						}
						getServiceFromFile.close();
					}

					getServiceFromFile >> customerID >> driverID >> fileVehicleID >> day >> month >> year >> bookingTime
						>> route >> source >> destination >> distance >> serviceStatus >> fuelrate >> fare >> driverRanking
						>> vehicleRanking >> RideOrDelivery >> noOfPassengersOrGoodsWeight >> wantAcOrGoodsType;
				}
			}
			else
				cout << "Service File can't be opened for Getting Data of Service of Pending Services of Driver";
			getServiceFromFile.close();

			//==========================================================================================================================================

			float userRankDriver, userRankVehicle;
			bool again = true;

			cout << "You Service was Completed";
			cout << "\nCustomer ID : " << customerID;
			cout << "\nSource : " << source;
			cout << "\nDestination : " << destination;
			cout << "\nRoute : "; route == 0 ? cout << "Intracity" : cout << "Intercity";
			cout << "\nRide or Delivery : " << RideOrDelivery;
			cout << "\nFare : " << fare;
			cout << "\n---------------------------------------\n";

			//taking input for driver ranking for the Service
			while (again)
			{
				try
				{
					cout << "Give Driver Ranking out 0-5 : ";
					cin >> userRankDriver;

					if (cin.fail())
						throw string("Enter Float number");
					if (userRankDriver < 0 || userRankDriver > 5)
						throw string("Enter 0-5 number");

					again = false;

				}
				catch (string error)
				{
					cin.clear();
					cin.ignore();
					system("cls");
					cout << "You Service was Completed";
					cout << "\nCustomer ID : " << customerID;
					cout << "\nSource : " << source;
					cout << "\nDestination : " << destination;
					cout << "\nRoute : "; route == 0 ? cout << "Intracity" : cout << "Intercity";
					cout << "\nRide or Delivery : " << RideOrDelivery;
					cout << "\nFare : " << fare;
					cout << "\n---------------------------------------\n";
					cout << error << " again : ";
				}
			}

			//taking input for Vehicle ranking for the Service
			again = true;
			while (again)
			{
				try
				{
					cout << "Give Vehicle Ranking out 0-5 : ";
					cin >> userRankVehicle;

					if (cin.fail())
						throw string("Enter Float number");
					if (userRankVehicle < 0 || userRankVehicle > 5)
						throw string("Enter 0-5 number");

					again = false;

				}
				catch (string error)
				{
					cin.clear();
					cin.ignore();
					system("cls");
					cout << "You Service was Completed";
					cout << "\nCustomer ID : " << customerID;
					cout << "\nSource : " << source;
					cout << "\nDestination : " << destination;
					cout << "\nRoute : "; route == 0 ? cout << "Intracity" : cout << "Intercity";
					cout << "\nRide or Delivery : " << RideOrDelivery;
					cout << "\nFare : " << fare;
					cout << "\n---------------------------------------\n";
					cout << error << " again : ";
				}
			}

			//taking fare from customer
			float amount, tempAmount;
			again = true;
			while (again)
			{
				try
				{

					cout << "\nYou need to Pay : " << fare << "\nEnter the amount : ";
					cin >> amount;

					if (amount < 0)
						throw string("Enter correct amount");
					if (cin.fail())
						throw string("Enter correct amount");

					again = false;
				}
				catch (string error)
				{
					cin.clear();
					cin.ignore();
					cout << error << " again : ";
				}
			}

			again = true;
			//if user enters a valid amount but it is less than the cost of the drink than this loop asks for the reaming amount 
			while (amount < fare)
			{
				tempAmount = amount;
				cout << "\nYou have still got " << fare - amount << " remaining amount to pay, Enter : ";
				while (again)
				{
					try
					{
						cin >> amount;

						if (amount < 0)
							throw string("Enter correct amount");
						if (cin.fail())
							throw string("Enter correct amount");

						again = false;
					}
					catch (string error)
					{
						cin.clear();
						cin.ignore();
						cout << error << " again : ";
					}
				}
				amount = amount + tempAmount;
			}

			//calculating amount to be returned
			cout << "\nAmount Returned is : " << amount - fare << endl;

			//setting ranking in service
			servicePtr->setVehicleRanking(userRankVehicle);
			servicePtr->setDriverRanking(userRankDriver);

			//==========================================================================================================================================

			//Updating Customer
			fstream readingCustomer;
			readingCustomer.open("Customer.txt");
			int lineNoCustomer = 0;
			if (readingCustomer.is_open())
			{
				int fileCustomerID, day, month, year, age, totalBooking;
				string fileFName, fileLName, fileCNIC;

				while (readingCustomer >> fileCustomerID >> fileFName >> fileLName >> day >> month >> year >> age >> fileCNIC >> totalBooking)
				{
					++lineNoCustomer;
					if (fileCustomerID == servicePtr->getCustomerID())
					{
						readingCustomer.close();
					}
				}
			}
			else
				cout << "Customer File can't be opened for Reading Customer Line in Book Ride";
			readingCustomer.close();

			//==========================================================================================================================================

			//opens the Drivers file to change driver status in file
			int driverID2, driverVehicleID;
			float driverOverallRanking;
			string temp1, temp2, temp3, temp4, temp5, temp6, temp7,
				temp8, temp9, temp10, temp11, temp12, temp;

			fstream readingDriver;
			int lineNoDriver = 0; //resets to zero
			readingDriver.open("Drivers.txt");
			if (readingDriver.is_open())
			{
				while (readingDriver >> driverID2 >> driverVehicleID >> temp1 >> temp2 >> temp3 >> temp4 >> temp5 >> temp6 >> temp7 >>
					temp8 >> temp9 >> driverOverallRanking >> temp10 >> temp11 >> temp12)
				{
					lineNoDriver++;
					//finding the driver line number of the Pending Service
					if (driverID2 == servicePtr->getDriverID())
					{
						//if the Driver Line NO is found than break the loop
						readingDriver.close();
					}
				}
			}
			else
				cout << "Drivers File can't be opened for Finding Line No for editing Driver Status in Pending Service";
			readingDriver.close();

			//==============================================================================================================================================

			//open the Vehicle file to change Vehicle Status in File
			fstream readVehicle;
			int VehicleID2;
			int lineNoVehicle = 0; //resets to zero
			readVehicle.open("Vehicle.txt");
			if (readVehicle.is_open())
			{
				while (readVehicle >> temp >> VehicleID2 >> temp >> temp >> temp >> temp >> temp
					>> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp)
				{
					lineNoVehicle++;
					//finding the vehicle line number of the Pending Service
					if (VehicleID2 == servicePtr->getVehicleID())
					{
						//if the Vehocle Line NO is found than break the loop
						readVehicle.close();
					}
				}
			}
			else
				cout << "Vehicle File can't be opened for Finding Line No for editing Vehicle Status in Pending Service";
			readVehicle.close();

			//==============================================================================================================================================

				//deleting customer from file and updating it 
			deleteFromFile("Customer.txt", lineNoCustomer);

			//adds one to total customer booking
			customer.setTotalBookings(1);

			//setting Driver Ranking
			driver.getDriverFromFile(servicePtr->getDriverID());
			driver.setOverallRanking(servicePtr->getDriverRanking());

			//setting vehicle Ranking and assigning the updated vehicle to driver
			Vehicle v = driver.getVehicle().getVehicleFromFile(servicePtr->getDriverID());
			v.setOverallRanking(userRankVehicle);
			cout << v.getOverallRanking();
			driver.setVehicle(v);
			//not updating totalVehicle Service and totalDriverService because the Service is completed by Vehicle

			deleteFromFile("Drivers.txt", lineNoDriver);
			deleteFromFile("Vehicle.txt", lineNoVehicle);
			deleteFromFile("Service.txt", lineNoService);

			//writing updated in file
			servicePtr->writeServiceInFile();
			customer.writeCustomerInFile();
			driver.writeDriverInFile();

		}
		//if service is Pending and so Customer can cancel it
		else if (serviceStatus == 2)
		{
			string option;
			cout << "\nThe Service is Pending:\n";
			cout << "\nCustomer ID : " << customerID;
			cout << "\nSource : " << source;
			cout << "\nDestination : " << destination;
			cout << "\nRoute : "; route == 0 ? cout << "Intracity" : cout << "Intercity";
			cout << "\nRide or Delivery : " << RideOrDelivery;
			cout << "\nFare : " << fare;
			cout << "\n---------------------------------------\n";
			cout << "Press 1 to Cancel it or 0 to go back : ";
			cin >> option;
			while (option != "1" && option != "0")
			{
				cin.clear();
				cin.ignore();
				cout << "Press 1 or 0 only :";
				cin >> option;
			}
				//==============================================================================================================================================

			if (option == "1")
			{//Opens the Service to Updte the Service Status in File
				int lineNoService = 0;
				Service* servicePtr2 = nullptr;
				Ride rideObj;
				Delivery deliveryObj;

				//getting the service data by line number of pending Service
				getServiceFromFile.open("Service.txt");
				if (getServiceFromFile.is_open())
				{
					getServiceFromFile >> customerID >> driverID >> fileVehicleID >> day >> month >> year >> bookingTime
						>> route >> source >> destination >> distance >> serviceStatus >> fuelrate >> fare >> driverRanking
						>> vehicleRanking >> RideOrDelivery >> noOfPassengersOrGoodsWeight >> wantAcOrGoodsType;

					while (!getServiceFromFile.eof())
					{
						//counting the 
						lineNoService++;

						//if the line number of pending service if found than that service data will be taken from file
						if (lineNoService == lineNumberOfPendingService)
						{
							//geeting the data of the Service Request that was put on by Customer and accepted by driver
							if (RideOrDelivery == "Ride")
							{
								Time bTime = bookingTime;
								Route way;
								//0 for Intracity, 1 for Intercity 
								route == 0 ? way = Intracity : way = Intercity;
								rideObj = Ride(Date(day, month, year), bTime, way, source, destination, distance, serviceStatus, fuelrate, customerID,
									driverID, fileVehicleID, fare, vehicleRanking, driverRanking, noOfPassengersOrGoodsWeight, wantAcOrGoodsType);
								servicePtr2 = &rideObj;
							}
							else
							{
								Time bTime = bookingTime;
								Route way;
								//0 for Intracity, 1 for Intercity 
								route == 0 ? way = Intracity : way = Intercity;
								deliveryObj = Delivery(Date(day, month, year), bTime, way, source, destination, distance, serviceStatus, fuelrate, customerID,
									driverID, fileVehicleID, fare, vehicleRanking, driverRanking, noOfPassengersOrGoodsWeight, wantAcOrGoodsType);
								servicePtr2 = &deliveryObj;
							}
							getServiceFromFile.close();
						}

						getServiceFromFile >> customerID >> driverID >> fileVehicleID >> day >> month >> year >> bookingTime
							>> route >> source >> destination >> distance >> serviceStatus >> fuelrate >> fare >> driverRanking
							>> vehicleRanking >> RideOrDelivery >> noOfPassengersOrGoodsWeight >> wantAcOrGoodsType;
					}
				}
				else
					cout << "Service File can't be opened for Getting Data of Service of Pending Services of Driver";
				getServiceFromFile.close();

				//==============================================================================================================================================

				//opens the Drivers file to change driver status in file
				int driverID2, driverVehicleID;
				float driverOverallRanking;
				string temp1, temp2, temp3, temp4, temp5, temp6, temp7,
					temp8, temp9, temp10, temp11, temp12, temp;

				fstream readingDriver;
				int lineNoDriver = 0; //resets to zero
				readingDriver.open("Drivers.txt");
				if (readingDriver.is_open())
				{
					while (readingDriver >> driverID2 >> driverVehicleID >> temp1 >> temp2 >> temp3 >> temp4 >> temp5 >> temp6 >> temp7 >>
						temp8 >> temp9 >> driverOverallRanking >> temp10 >> temp11 >> temp12)
					{
						lineNoDriver++;
						//finding the driver line number of the Pending Service
						if (driverID2 == servicePtr2->getDriverID())
						{
							//if the Driver Line NO is found than break the loop
							readingDriver.close();
						}
					}
				}
				else
					cout << "Drivers File can't be opened for Finding Line No for editing Driver Status in Pending Service";
				readingDriver.close();

				//==============================================================================================================================================
				//open the Vehicle file to change Vehicle Status in File
				fstream readVehicle;
				int VehicleID2;
				int lineNoVehicle = 0; //resets to zero
				readVehicle.open("Vehicle.txt");
				if (readVehicle.is_open())
				{
					while (readVehicle >> temp >> VehicleID2 >> temp >> temp >> temp >> temp >> temp
						>> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp)
					{
						lineNoVehicle++;
						//finding the vehicle line number of the Pending Service
						if (VehicleID2 == servicePtr2->getVehicleID())
						{
							//if the Vehocle Line NO is found than break the loop
							readVehicle.close();
						}
					}
				}
				else
					cout << "Vehicle File can't be opened for Finding Line No for editing Vehicle Status in Pending Service";
				readVehicle.close();

				//==============================================================================================================================================

				//deleting the Serivce from file
				deleteFromFile("Service.txt", lineNoService);
				//deleting the Driver from file
				deleteFromFile("Drivers.txt", lineNoDriver);
				//deleting the Vehicle from file
				deleteFromFile("Vehicle.txt", lineNoVehicle);
				//setting Driver Status to Free after the Service has been Cancelled
				driver.setDriverStatus(1);
				//setting Vehicle Status to Free after the Service has been Cancelled
				Vehicle v = driver.getVehicle();
				v.setVehicleStatus(false);
				driver.setVehicle(v);
				//changing Service Status from PENDING CANCELLED; 
				//if Service is Cancelled the Customer is charged 5% and Fare is added to Driver's Income 

				//===========================================================================================================================
				//taking fare from customer
				//5% charges Fine to customer
				float FareAmount = (servicePtr2->getFare() * 5.0f) / 100.0f;
				float amount, tempAmount;
				bool again = true;
				while (again)
				{
					try
					{

						cout << "\nYou need to Pay : " << fare << "\nEnter the amount : ";
						cin >> amount;

						if (amount < 0)
							throw string("Enter correct amount");
						if (cin.fail())
							throw string("Enter correct amount");

						again = false;
					}
					catch (string error)
					{
						cin.clear();
						cin.ignore();
						cout << error << " again : ";
					}
				}

				again = true;
				//if user enters a valid amount but it is less than the cost of the drink than this loop asks for the reaming amount 
				while (amount < FareAmount)
				{
					tempAmount = amount;
					cout << "\nYou have still got " << FareAmount - amount << " remaining amount to pay, Enter : ";
					while (again)
					{
						try
						{
							cin >> amount;

							if (amount < 0)
								throw string("Enter correct amount");
							if (cin.fail())
								throw string("Enter correct amount");

							again = false;
						}
						catch (string error)
						{
							cin.clear();
							cin.ignore();
							cout << error << " again : ";
						}
					}
					amount = amount + tempAmount;
				}

				//calculating amount to be returned
				cout << "\nAmount Returned is : " << amount - FareAmount << endl;

				//===========================================================================================================================
				servicePtr2->setServiceStatus(3);
				driver.setTotalIncome(FareAmount);
				//add 0 to total Services Completed of Driver, Vehicle and Customer
				driver.setTotalServices(0);
				//writing Updated Service in File
				servicePtr2->writeServiceInFile();
				v.setTotalVehicleServices(1);
				driver.setVehicle(v);
				//writing Driver and Vehicle with updated status and Salary in file (WriteVehicleInFile() is called inside WriteDriverInFile())
				driver.writeDriverInFile();

				//==============================================================================================================================================

			}
			else if (option == "0")
			{
				return;
			}
		}
		//if service need to be approved by ride
		else if (serviceStatus == 4)
		{
			int temp;
			cout << "\nThe Service is Pending Driver's Approval :\n";
			cout << "\nCustomer ID : " << customerID;
			cout << "\nSource : " << source;
			cout << "\nDestination : " << destination;
			cout << "\nRoute : "; route == 0 ? cout << "Intracity" : cout << "Intercity";
			cout << "\nRide or Delivery : " << RideOrDelivery;
			cout << "\nFare : " << fare;
			cout << "\n---------------------------------------\n";
			cout << "Press 1 to go back or 2 to cancel";
			cin >> temp;
			while (temp < 1 || temp >2)
			{
				cin.clear();
				cin.ignore();
				cout << "Enter again : ";
				cin >> temp;
			}
			if (temp == 1)
			{
				
			}
			//cancel
			else if (temp == 2)
			{
				//Opens the Service to Updte the Service Status in File
				int lineNoService = 0;
				Service* servicePtr = nullptr;
				Ride rideObj;
				Delivery deliveryObj;

				//getting the service data by line number of pending Service
				getServiceFromFile.open("Service.txt");
				if (getServiceFromFile.is_open())
				{
					getServiceFromFile >> customerID >> driverID >> fileVehicleID >> day >> month >> year >> bookingTime
						>> route >> source >> destination >> distance >> serviceStatus >> fuelrate >> fare >> driverRanking
						>> vehicleRanking >> RideOrDelivery >> noOfPassengersOrGoodsWeight >> wantAcOrGoodsType;

					while (!getServiceFromFile.eof())
					{
						//counting the 
						lineNoService++;

						//if the line number of pending service if found than that service data will be taken from file
						if (lineNoService == lineNumberOfPendingService)
						{
							//geeting the data of the Service Request that was put on by Customer and accepted by driver
							if (RideOrDelivery == "Ride")
							{
								Time bTime = bookingTime;
								Route way;
								//0 for Intracity, 1 for Intercity 
								route == 0 ? way = Intracity : way = Intercity;
								rideObj = Ride(Date(day, month, year), bTime, way, source, destination, distance, serviceStatus, fuelrate, customerID,
									driverID, fileVehicleID, fare, vehicleRanking, driverRanking, noOfPassengersOrGoodsWeight, wantAcOrGoodsType);
								servicePtr = &rideObj;
							}
							else
							{
								Time bTime = bookingTime;
								Route way;
								//0 for Intracity, 1 for Intercity 
								route == 0 ? way = Intracity : way = Intercity;
								deliveryObj = Delivery(Date(day, month, year), bTime, way, source, destination, distance, serviceStatus, fuelrate, customerID,
									driverID, fileVehicleID, fare, vehicleRanking, driverRanking, noOfPassengersOrGoodsWeight, wantAcOrGoodsType);
								servicePtr = &deliveryObj;
							}
							getServiceFromFile.close();
						}

						getServiceFromFile >> customerID >> driverID >> fileVehicleID >> day >> month >> year >> bookingTime
							>> route >> source >> destination >> distance >> serviceStatus >> fuelrate >> fare >> driverRanking
							>> vehicleRanking >> RideOrDelivery >> noOfPassengersOrGoodsWeight >> wantAcOrGoodsType;
					}
				}
				else
					cout << "Service File can't be opened for Getting Data of Service of Pending Services of Driver";
				getServiceFromFile.close();

				deleteFromFile("Service.txt", lineNoService);
				servicePtr->setServiceStatus(3);
				servicePtr->writeServiceInFile();

			}
		}
		

	}
}

void TMS::viewServiceRequest()
{

	int match = 0;
	fstream getServiceFromFile;
	string bookingTime, source, destination, RideOrDelivery;
	float distance, fuelrate, vehicleRanking, driverRanking;
	int	customerID, driverID, fileVehicleID, fare;
	int day, month, year;
	int serviceStatus;	//1 for Completed, 2 if Pending and 3 if Cancelled, 4 not approved
	int route;			//0 for Intracity, 1 for Intercity 
	float noOfPassengersOrGoodsWeight; //holds NumOfPassengers if it was Ride else holds Goods Weight if it was Delivery
	string wantAcOrGoodsType;		 //holds WantAc (YES/NO) if it was Ride else holds Goods Type if it was Delivery
	bool OldServiceCompleted = true;
	int lineNumberOfPendingService = 0;
	//counting service that are pending driver approval
	getServiceFromFile.open("Service.txt");
	if (getServiceFromFile.is_open())
	{
		while (getServiceFromFile >> customerID >> driverID >> fileVehicleID >> day >> month >> year >> bookingTime
			>> route >> source >> destination >> distance >> serviceStatus >> fuelrate >> fare >> driverRanking
			>> vehicleRanking >> RideOrDelivery >> noOfPassengersOrGoodsWeight >> wantAcOrGoodsType)
		{
			//finding services request to driver if no Service is pending
			if (driverID == driver.getDriverID() && serviceStatus == 4)
			{
				OldServiceCompleted = true;
				match++;
			}
			//if there will be a pending service than this will be useful as we will get the line no of the service when the loop break, we will have the line no
			++lineNumberOfPendingService;
			//if driver is already in a Pending Service he will be shown that 
			if (driverID == driver.getDriverID() && serviceStatus == 2)
			{
				OldServiceCompleted = false;
				break;
			}
		}

	}
	else
		cout << "Service File can't be opened for counting service that are pending driver approval";
	getServiceFromFile.close();

	//if there is No Pending Service and a service needs approval from driver
	if (OldServiceCompleted == true)
	{
		//if there is no Request available
		if (match > 0)
		{
			//This hold the customerID, DriverID, VehicleID and RideOrDelivery of Service at (0-4 index) that are pending approval from Driver
			/*	[i][0] = customerID;
				[i][1] = driverID;
				[i][2] = fileVehicleID;
				[i][3] = 1; //1 for ride 2 for delivery
			*/
			int** pendingServicesID = new int* [match];
			for (int i = 0; i < match; i++)
			{
				pendingServicesID[i] = new int[4];
			}

			//getting IDs and storing them in array
			int i = 0, j = 0;
			getServiceFromFile.open("Service.txt");
			if (getServiceFromFile.is_open())
			{
				while (getServiceFromFile >> customerID >> driverID >> fileVehicleID >> day >> month >> year >> bookingTime
					>> route >> source >> destination >> distance >> serviceStatus >> fuelrate >> fare >> driverRanking
					>> vehicleRanking >> RideOrDelivery >> noOfPassengersOrGoodsWeight >> wantAcOrGoodsType)
				{
					if (driverID == driver.getDriverID() && serviceStatus == 4 && RideOrDelivery == "Ride")
					{
						pendingServicesID[i][0] = customerID;
						pendingServicesID[i][1] = driverID;
						pendingServicesID[i][2] = fileVehicleID;
						pendingServicesID[i][3] = 1; //1 for ride 2 for delivery
						i++;
					}
					else if (driverID == driver.getDriverID() && serviceStatus == 4 && RideOrDelivery == "Delivery")
					{
						pendingServicesID[i][0] = customerID;
						pendingServicesID[i][1] = driverID;
						pendingServicesID[i][2] = fileVehicleID;
						pendingServicesID[i][3] = 2; //1 for ride 2 for delivery
						i++;
					}
				}
			}
			else
				cout << "Service File can't be opened for storing ID in array";
			getServiceFromFile.close();

			//showing request to driver 
			getServiceFromFile.open("Service.txt");
			if (getServiceFromFile.is_open())
			{
				while (getServiceFromFile >> customerID >> driverID >> fileVehicleID >> day >> month >> year >> bookingTime
					>> route >> source >> destination >> distance >> serviceStatus >> fuelrate >> fare >> driverRanking
					>> vehicleRanking >> RideOrDelivery >> noOfPassengersOrGoodsWeight >> wantAcOrGoodsType)
				{
					if (driverID == driver.getDriverID() && serviceStatus == 4)
					{
						cout << "\nCustomer ID : " << customerID;
						cout << "\nSource : " << source;
						cout << "\nDestination : " << destination;
						cout << "\nRoute : "; route == 0 ? cout << "Intracity" : cout << "Intercity";
						cout << "\nRide or Delivery : " << RideOrDelivery;
						cout << "\nFare : " << fare;
						cout << "\n---------------------------------------\n";
					}
				}
			}
			else
				cout << "Service File can't be opened for Showing Request to Driver";
			getServiceFromFile.close();

			//asking driver to approve a request
			int selectedID;
			bool found = false;
			int k = 0;
			cout << "Enter Customer ID to Accept Request or 1 to go back, 2 to delete request: ";
			while (found == false)
			{
				try
				{
					cin >> selectedID;
					if (selectedID > 9999 || selectedID < 1000 && selectedID != 1)
						throw string("Enter 4 digits");
					if (!cin)
						throw string("Enter Integer");

					//when the pendingService that is accepted by driver will be found loop will be broken so we will have the
					//index (k) of Service that is approved by Driver
					for (k = 0; k < match; k++)
					{
						if (selectedID != pendingServicesID[k][0])
							found = false;
						else
						{
							found = true;
							break;
						}
					}

					if (selectedID == 1)
						return; // break from case

					if (found == false)
						throw string("Enter from above ID");
				}
				catch (string error)
				{
					cin.clear();
					cin.ignore();
					cout << error;
				}
			}
			//==============================================================================================================================================

			//Opens the Service to Update the Service Status in File
			int lineNoService = 0;
			Service* servicePtr = nullptr;
			Ride rideObj;
			Delivery deliveryObj;
			//editing the STATUSES of service, vehicle, driver in file if driver has entered the customer ID to choose the request correctly;
			if (selectedID != 1)
			{
				getServiceFromFile.open("Service.txt");
				if (getServiceFromFile.is_open())
				{
					getServiceFromFile >> customerID >> driverID >> fileVehicleID >> day >> month >> year >> bookingTime
						>> route >> source >> destination >> distance >> serviceStatus >> fuelrate >> fare >> driverRanking
						>> vehicleRanking >> RideOrDelivery >> noOfPassengersOrGoodsWeight >> wantAcOrGoodsType;
					while (!getServiceFromFile.eof())
					{
						//counting th eline no of the Service Request that was put on by Customer and accepted by driver, so that we can delete it
						lineNoService++;
						//if the all IDs (Vehicle, Customer, Driver) are matches the service, to check that correct service is choosen, and if the RideOrDelivery matches so
						//that if can be confirmed that this is the exact service that was set by customer 
						if (customerID == pendingServicesID[k][0] && driverID == pendingServicesID[k][1] && fileVehicleID == pendingServicesID[k][2] &&
							((RideOrDelivery == "Ride" && pendingServicesID[k][3] == 1) || (RideOrDelivery == "Delivery" && pendingServicesID[k][3] == 2)) && serviceStatus == 4)
						{
							//geeting the data of the Service Request that was put on by Customer and accepted by driver
							if (RideOrDelivery == "Ride")
							{
								Time bTime = bookingTime;
								Route way;
								//0 for Intracity, 1 for Intercity 
								route == 0 ? way = Intracity : way = Intercity;
								rideObj = Ride(Date(day, month, year), bTime, way, source, destination, distance, serviceStatus, fuelrate, customerID,
									driverID, fileVehicleID, fare, vehicleRanking, driverRanking, noOfPassengersOrGoodsWeight, wantAcOrGoodsType);
								servicePtr = &rideObj;
							}
							else
							{
								Time bTime = bookingTime;
								Route way;
								//0 for Intracity, 1 for Intercity 
								route == 0 ? way = Intracity : way = Intercity;
								deliveryObj = Delivery(Date(day, month, year), bTime, way, source, destination, distance, serviceStatus, fuelrate, customerID,
									driverID, fileVehicleID, fare, vehicleRanking, driverRanking, noOfPassengersOrGoodsWeight, wantAcOrGoodsType);
								servicePtr = &deliveryObj;
							}
							getServiceFromFile.close();
						}
						getServiceFromFile >> customerID >> driverID >> fileVehicleID >> day >> month >> year >> bookingTime
							>> route >> source >> destination >> distance >> serviceStatus >> fuelrate >> fare >> driverRanking
							>> vehicleRanking >> RideOrDelivery >> noOfPassengersOrGoodsWeight >> wantAcOrGoodsType;
					}
				}
				else
					cout << "Service File can't be opened for Finding Line No for editing Service approved by Driver";
				getServiceFromFile.close();

				//deleting the Serivce from file
				deleteFromFile("Service.txt", lineNoService);

				//changing Service Status from PENDING APPROVAL BY DRIVER to PENDING  and writing in File 
				servicePtr->setServiceStatus(2);
				servicePtr->writeServiceInFile();

				//==============================================================================================================================================

				//opens the Drivers file to change driver status in file
				int driverID2, driverVehicleID;
				float driverOverallRanking;
				string temp;

				fstream readingDriver;
				int lineNoDriver = 0; //resets to zero
				readingDriver.open("Drivers.txt");
				if (readingDriver.is_open())
				{
					while (readingDriver >> driverID2 >> driverVehicleID >> temp >> temp >> temp >> temp >> temp >> temp >> temp >>
						temp >> temp >> driverOverallRanking >> temp >> temp >> temp)
					{
						lineNoDriver++;
						//pendingServicesID[k][1] stores the driver ID of the Driver who accepted the Service
						if (driverID2 == pendingServicesID[k][1])
						{
							//if the Driver Line NO is found that has accepted the Service, than break the loop
							readingDriver.close();
						}
					}
				}
				else
					cout << "Drivers File can't be opened for Finding Line No for editing Driver Status";
				readingDriver.close();

				//==============================================================================================================================================

					//open the Vehicle file to change Vehicle Status in File
				fstream readVehicle;
				int VehicleID2;
				int lineNoVehicle = 0; //resets to zero
				readVehicle.open("Vehicle.txt");
				if (readVehicle.is_open())
				{
					while (readVehicle >> temp >> VehicleID2 >> temp >> temp >> temp >> temp >> temp
						>> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp)
					{
						lineNoVehicle++;
						//pendingServicesID[k][2] stores the Vehicle ID of the Driver who accepted the Service 
						if (VehicleID2 == pendingServicesID[k][2])
						{
							//if the Vehocle Line NO is found that has accepted the Service, than break the loop
							readVehicle.close();
						}
					}
				}
				else
					cout << "Vehicle File can't be opened for Finding Line No for editing Vehicle Status of Driver who approved Service";
				readVehicle.close();

				//==============================================================================================================================================
					//deleting the Driver from file
				deleteFromFile("Drivers.txt", lineNoDriver);
				//deleting the Vehicle from file
				deleteFromFile("Vehicle.txt", lineNoVehicle);
				//setting Driver Status to Booked
				driver.setDriverStatus(2);
				//setting Vehicle Status to Booked
				Vehicle v = driver.getVehicle();
				v.setVehicleStatus(true);
				driver.setVehicle(v);
				//writing Driver and Vehicle with updated status in file (WriteVehicleInFile() is called inside WriteDriverInFile())
				driver.writeDriverInFile();

				//==============================================================================================================================================
				system("pause");
			}
			//if the request has been deleted by Driver
			else if (selectedID == 2)
			{
				getServiceFromFile.open("Service.txt");
				if (getServiceFromFile.is_open())
				{
					getServiceFromFile >> customerID >> driverID >> fileVehicleID >> day >> month >> year >> bookingTime
						>> route >> source >> destination >> distance >> serviceStatus >> fuelrate >> fare >> driverRanking
						>> vehicleRanking >> RideOrDelivery >> noOfPassengersOrGoodsWeight >> wantAcOrGoodsType;
					while (!getServiceFromFile.eof())
					{
						//counting th eline no of the Service Request that was put on by Customer and accepted by driver, so that we can delete it
						lineNoService++;
						//if the all IDs (Vehicle, Customer, Driver) are matches the service, to check that correct service is choosen, and if the RideOrDelivery matches so
						//that if can be confirmed that this is the exact service that was set by customer 
						if (customerID == pendingServicesID[k][0] && driverID == pendingServicesID[k][1] && fileVehicleID == pendingServicesID[k][2] &&
							((RideOrDelivery == "Ride" && pendingServicesID[k][3] == 1) || (RideOrDelivery == "Delivery" && pendingServicesID[k][3] == 2)) && serviceStatus == 4)
						{
							//geeting the data of the Service Request that was put on by Customer and accepted by driver
							if (RideOrDelivery == "Ride")
							{
								Time bTime = bookingTime;
								Route way;
								//0 for Intracity, 1 for Intercity 
								route == 0 ? way = Intracity : way = Intercity;
								rideObj = Ride(Date(day, month, year), bTime, way, source, destination, distance, serviceStatus, fuelrate, customerID,
									driverID, fileVehicleID, fare, vehicleRanking, driverRanking, noOfPassengersOrGoodsWeight, wantAcOrGoodsType);
								servicePtr = &rideObj;
							}
							else
							{
								Time bTime = bookingTime;
								Route way;
								//0 for Intracity, 1 for Intercity 
								route == 0 ? way = Intracity : way = Intercity;
								deliveryObj = Delivery(Date(day, month, year), bTime, way, source, destination, distance, serviceStatus, fuelrate, customerID,
									driverID, fileVehicleID, fare, vehicleRanking, driverRanking, noOfPassengersOrGoodsWeight, wantAcOrGoodsType);
								servicePtr = &deliveryObj;
							}
							getServiceFromFile.close();
						}
						getServiceFromFile >> customerID >> driverID >> fileVehicleID >> day >> month >> year >> bookingTime
							>> route >> source >> destination >> distance >> serviceStatus >> fuelrate >> fare >> driverRanking
							>> vehicleRanking >> RideOrDelivery >> noOfPassengersOrGoodsWeight >> wantAcOrGoodsType;
					}
				}
				else
					cout << "Service File can't be opened for Finding Line No for editing Service approved by Driver";
				getServiceFromFile.close();

				//deleting the Serivce from file
				deleteFromFile("Service.txt", lineNoService);

				//changing Service Status from PENDING APPROVAL BY DRIVER to CANCELLED and writing in File 
				servicePtr->setServiceStatus(3);
				servicePtr->writeServiceInFile();
			}

			for (int i = 0; i < match; i++)
			{
				delete[] pendingServicesID[i];
			}
			delete[] pendingServicesID;
		}
		else if (match == 0)
			cout << "No Request Available";

	}
	//if there is Pending Service
	else if (OldServiceCompleted == false)
	{
		int option;
		cout << "\nThe Service is Pending:\n";
		cout << "\nCustomer ID : " << customerID;
		cout << "\nSource : " << source;
		cout << "\nDestination : " << destination;
		cout << "\nRoute : "; route == 0 ? cout << "Intracity" : cout << "Intercity";
		cout << "\nRide or Delivery : " << RideOrDelivery;
		cout << "\nFare : " << fare;
		cout << "\n---------------------------------------\n";
		cout << "Press 1 to Complete it or 2 to cancel it";
		cin >> option;
		while (option > 2 || option < 1)
		{
			cin.clear();
			cin.ignore();
			cout << "Press 1 or 2 only :";
			cin >> option;
		}
		//==============================================================================================================================================

		//Opens the Service to Updte the Service Status in File
		int lineNoService = 0;
		Service* servicePtr = nullptr;
		Ride rideObj;
		Delivery deliveryObj;

		//getting the service data by line number of pending Service
		getServiceFromFile.open("Service.txt");
		if (getServiceFromFile.is_open())
		{
			getServiceFromFile >> customerID >> driverID >> fileVehicleID >> day >> month >> year >> bookingTime
				>> route >> source >> destination >> distance >> serviceStatus >> fuelrate >> fare >> driverRanking
				>> vehicleRanking >> RideOrDelivery >> noOfPassengersOrGoodsWeight >> wantAcOrGoodsType;

			while (!getServiceFromFile.eof())
			{
				//counting the 
				lineNoService++;

				//if the line number of pending service if found than that service data will be taken from file
				if (lineNoService == lineNumberOfPendingService)
				{
					//geeting the data of the Service Request that was put on by Customer and accepted by driver
					if (RideOrDelivery == "Ride")
					{
						Time bTime = bookingTime;
						Route way;
						//0 for Intracity, 1 for Intercity 
						route == 0 ? way = Intracity : way = Intercity;
						rideObj = Ride(Date(day, month, year), bTime, way, source, destination, distance, serviceStatus, fuelrate, customerID,
							driverID, fileVehicleID, fare, vehicleRanking, driverRanking, noOfPassengersOrGoodsWeight, wantAcOrGoodsType);
						servicePtr = &rideObj;
					}
					else
					{
						Time bTime = bookingTime;
						Route way;
						//0 for Intracity, 1 for Intercity 
						route == 0 ? way = Intracity : way = Intercity;
						deliveryObj = Delivery(Date(day, month, year), bTime, way, source, destination, distance, serviceStatus, fuelrate, customerID,
							driverID, fileVehicleID, fare, vehicleRanking, driverRanking, noOfPassengersOrGoodsWeight, wantAcOrGoodsType);
						servicePtr = &deliveryObj;
					}
					getServiceFromFile.close();
				}

				getServiceFromFile >> customerID >> driverID >> fileVehicleID >> day >> month >> year >> bookingTime
					>> route >> source >> destination >> distance >> serviceStatus >> fuelrate >> fare >> driverRanking
					>> vehicleRanking >> RideOrDelivery >> noOfPassengersOrGoodsWeight >> wantAcOrGoodsType;
			}
		}
		else
			cout << "Service File can't be opened for Getting Data of Service of Pending Services of Driver";
		getServiceFromFile.close();

		//==============================================================================================================================================
		
		//opens the Drivers file to change driver status in file
		int driverID2, driverVehicleID;
		float driverOverallRanking;
		string temp1, temp2, temp3, temp4, temp5, temp6, temp7,
			temp8, temp9, temp10, temp11, temp12,temp;

		fstream readingDriver;
		int lineNoDriver = 0; //resets to zero
		readingDriver.open("Drivers.txt");
		if (readingDriver.is_open())
		{
			while (readingDriver >> driverID2 >> driverVehicleID >> temp1 >> temp2 >> temp3 >> temp4 >> temp5 >> temp6 >> temp7 >>
				temp8 >> temp9 >> driverOverallRanking >> temp10 >> temp11 >> temp12)
			{
				lineNoDriver++;
				//finding the driver line number of the Pending Service
				if (driverID2 == servicePtr->getDriverID())
				{
					//if the Driver Line NO is found than break the loop
					readingDriver.close();
				}
			}
		}
		else
			cout << "Drivers File can't be opened for Finding Line No for editing Driver Status in Pending Service";
		readingDriver.close();

		//==============================================================================================================================================
		//open the Vehicle file to change Vehicle Status in File
		fstream readVehicle;
		int VehicleID2;
		int lineNoVehicle = 0; //resets to zero
		readVehicle.open("Vehicle.txt");
		if (readVehicle.is_open())
		{
			while (readVehicle >> temp >> VehicleID2 >> temp >> temp >> temp >> temp >> temp
				>> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp)
			{
				lineNoVehicle++;
				//finding the vehicle line number of the Pending Service
				if (VehicleID2 == servicePtr->getVehicleID())
				{
					//if the Vehocle Line NO is found than break the loop
					readVehicle.close();
				}
			}
		}
		else
			cout << "Vehicle File can't be opened for Finding Line No for editing Vehicle Status in Pending Service";
		readVehicle.close();

		//==============================================================================================================================================

		//deleting the Serivce from file
		deleteFromFile("Service.txt", lineNoService);
		//deleting the Driver from file
		deleteFromFile("Drivers.txt", lineNoDriver);
		//deleting the Vehicle from file
		deleteFromFile("Vehicle.txt", lineNoVehicle);
		//setting Driver Status to Free after the Service has been Completed or Cancelled
		driver.setDriverStatus(1);
		//setting Vehicle Status to Free after the Service has been Completed or Cancelled
		Vehicle v = driver.getVehicle();
		v.setVehicleStatus(false);
		driver.setVehicle(v);
		//changing Service Status from PENDING to COMPLETED or CANCELLED; 
		//if Service is Completed the Fare is added to Driver's Income 
		if (option == 1)
		{
			servicePtr->setServiceStatus(1);
			driver.setTotalIncome(servicePtr->getFare());
			//add 1 to total Services Completed of Driver, Vehicle and Customer
			driver.setTotalServices(1);
		}
		//if Service is Cancelled 5% of Fare is deducted from Driver's Income 
		else if (option == 2)
		{
			servicePtr->setServiceStatus(3);
			cout << "Service Cancelled\n5% of Fare " << servicePtr->getFare() << " deducted : " << -1 * ((servicePtr->getFare() * 5.0f) / 100.0f);
			driver.setTotalIncome(-(servicePtr->getFare() * 5.0f) / 100.0f);
			//totalbooking add krni ha 
		}


		//writing Updated Service in File
		servicePtr->writeServiceInFile();
		v.setTotalVehicleServices(1);
		driver.setVehicle(v);
		//writing Driver and Vehicle with updated status and Salary in file (WriteVehicleInFile() is called inside WriteDriverInFile())
		driver.writeDriverInFile();

		//==============================================================================================================================================
	}
}

void TMS::addNewCustomer() 
{
	//create a SIGN IN for customer
	Sign_IN(2);
	//adding a new customer
	customer.addNewCustomer();
	
	if (customer.getAge() < 18)
		Sign_IN();

}
bool TMS::removeCustomer(int customerToRemoveId)
{
	int deleteLine = 0;
	fstream readingLOGIN;
	readingLOGIN.open("LOGIN DETAILS.txt");
	bool customerFound = false;

	//LOGIN Details
	if (readingLOGIN.is_open())
	{
		int fileDriverID, login;
		string temp;

		while (readingLOGIN >> temp >> temp >> login >> fileDriverID)
		{
			//counting on which line the Login Details are that are to be deleted
			++deleteLine;
			if (customerToRemoveId == fileDriverID && login == asCustomer)
			{
				customerFound = true;
				//if the details are found that are to be deleted than close the file now we have the line number to delete
				readingLOGIN.close();
			}
		}
	}
	else
		cout << "LOGIN DETAILS File can't be opened for Deleting Customer";
	readingLOGIN.close();

	if (customerFound == true)
	{
		fstream readingService;
		int fileCustomerID;
		int fileServiceStatus;  //1 for Completed, 2 if Pending and 3 if Cancelled
		string temp;

		readingService.open("Service.txt");
		if (readingService.is_open())
		{
			while (readingService >> fileCustomerID >> temp >> temp >> temp >> temp >> temp >> temp
				>> temp >> temp >> temp >> temp >> fileServiceStatus >> temp >> temp >> temp
				>> temp >> temp >> temp >> temp)
			{
				/*if customer Id from file matches to the ID of customer who has to be removed than it checks if the customer 
				is free or not, customer can de deleted only if he is free,*/
				if (customerToRemoveId == fileCustomerID)
				{
					//Customer will not be free when fileServiceStatus == 2, it means that the Service is Pending
					if (fileServiceStatus == 2)
					{
						cout << "Customer is not free so can't be removed ";
						readingService.close();
						return false;
					}
				}
			}
		}
		else
			cout << "Customer File can't be opened for Deleting";
		readingService.close();

		string file = "LOGIN DETAILS.txt";
		//removing LOGIN DETAILS by removing the line
		deleteFromFile(file, deleteLine);
		
		//getting customer from File that is to be removed 
		customer.getCustomerFromFile(customerToRemoveId);
		//removing that customer
		customer.deleteCustomerFromFile();
		cout << "\nAccount Deleted\n";
		//returning true if the data is deleted
		return customerFound;
	}
	else //if Customer id is not found in file it will return from here 
	{
		cout << "Customer Id not found : ";
		return customerFound;
	}

}
void TMS::addNewDriver() 
{
	//create a SIGN IN for driver
	Sign_IN(3);
	//adding a new driver
	driver.AddNewDriver();

	if (driver.getAge() < 18)
		Sign_IN();
}
bool TMS::removeDriver(int driverToRemoveId) 
{
	int deleteLine = 0;
	fstream readingLOGIN;
	readingLOGIN.open("LOGIN DETAILS.txt");
	bool driverFound = false;

	//LOGIN Details
	if (readingLOGIN.is_open())
	{
		int fileDriverID;
		int login;
		string temp;

		while (readingLOGIN >> temp >> temp >> login >> fileDriverID)
		{
			//counting on which line the Login Details are that are to be deleted
			++deleteLine;
			if (driverToRemoveId == fileDriverID && login == asDriver)
			{
				driverFound = true;
				//if the details are found that are to be deleted than close the file now we have the line number to delete
				readingLOGIN.close();
			}
		}
	}
	else
		cout << "LOGIN DETAILS File can't be opened for Deleting Driver";
	readingLOGIN.close();

	if (driverFound == true)
	{		
		//checking If the driver is free than it will be deleted only
		fstream readingDriver;
		int driverVehicleID, driverStatus, driverID;
		string temp;

		readingDriver.open("Drivers.txt");
		if (readingDriver.is_open())
		{
			while (readingDriver >> driverID >> driverVehicleID >> temp >> temp >> temp >> temp
				>> temp >> temp >> temp >> temp >> temp >> temp >> temp >> driverStatus >> temp)
			{
				//if driver Id from file matches to the ID of driver who has to be removed than it checks if the driver is free or not
				if (driverToRemoveId == driverID)
				{
					if (driverStatus != 1)
					{
						cout << "Driver is not free so can't be removed ";
						readingDriver.close();
						return false;
					}
				}
			}
		}
		else
			cout << "Drivers File can't be opened for Deleting Driver";
		readingDriver.close();

		string file = "LOGIN DETAILS.txt";
		//removing LOGIN DETAILS by removing the line
		deleteFromFile(file, deleteLine);

		/*if driver is free than it will remove driver's vehicle and driver from file, it will call the function from the Driver obj in 
		TMS class for the driver and vehicle that is to be removed, so for that we will have to get the Driver Data and Vehicle data from file to delete*/
		driver.getDriverFromFile(driverToRemoveId);
		driver.setVehicle(driver.getVehicle().getVehicleFromFile(driverToRemoveId));
		//removing vehicle and driver
		driver.removePreviousVehicleOfDriver();
		driver.deleteDriverfromFile();
		cout << "\nAccount Deleted\n";
		//returning true if the data is deleted
		return driverFound;
	}
	else //if driver id is not found in file it will return from here 
	{	
		cout << "Driver Id not found : ";
		return driverFound;
	}
}
//Prints single driver if DriverID is passes else it will print all Drivers
void TMS::printDrivers(int DriverID) 
{
	fstream readingDriver;
	readingDriver.open("Drivers.txt");

	if (readingDriver.is_open())
	{
		int driverID, driverVehicleID, age, driverStatus, totalServices, year, day, month;
		float driverOverallRanking, income, experience;
		string fName, lName, cnic, license;

		while (readingDriver >> driverID >> driverVehicleID >> fName >> lName >> day >> month
			>> year >> age >> cnic >> experience >> license >> driverOverallRanking >> income >> driverStatus >> totalServices)
		{
			//if no ID is passed than it will print all driver
			if (DriverID == 0)
			{
				driver = Driver(driverID, driverVehicleID, fName, lName, day, month, year, cnic,
					experience, license, driverOverallRanking, income, driverStatus, totalServices);
				cout << driver;
			}
			//if driverID is passed than it matches and prints the corresponding driver and return
			else if (DriverID == driverID)
			{
				driver = Driver(driverID, driverVehicleID, fName, lName, day, month, year, cnic,
					experience, license, driverOverallRanking, income, driverStatus, totalServices);
				cout << driver;
				readingDriver.close();
				return;
			}
		}
	}
	else
		cout << "Drivers File can't be opened for Printing Drivers";
	readingDriver.close();
}
//Prints single Customer if CustomerID is passes else it will print all Customers
void TMS::printCustomers(int CustomerID) 
{
	fstream readingCustomer;
	readingCustomer.open("Customer.txt");

	if (readingCustomer.is_open())
	{
		int fileCustomerID, day, month, year, age, totalBooking;
		string fileFName, fileLName, fileCNIC;

		while (readingCustomer >> fileCustomerID >> fileFName >> fileLName >> day >> month >> year >> age >> fileCNIC >> totalBooking)
		{
			//if no ID is passed than it will print all customers
			if (CustomerID == 0)
			{
				customer = Customer(fileFName, fileLName, Date(day, month, year), fileCNIC, fileCustomerID, totalBooking);
				cout << customer;
			}
			//if CustomerID is passed than it matches and prints the corresponding Customer and return
			else if (CustomerID == fileCustomerID)
			{
				customer = Customer(fileFName, fileLName, Date(day, month, year), fileCNIC, fileCustomerID, totalBooking);
				cout << customer;
				readingCustomer.close();
				return;
			}
		}
	}
	else
		cout << "Customer File can't be opened for Printing Customer";
	readingCustomer.close();
}
//Prints single Vehicle if VehicleID is passes else it will print all Vehilcles
void TMS::printVehicles(int VehicleID)
{
	fstream readVehicle;
	readVehicle.open("Vehicle.txt");
	if (readVehicle.is_open())
	{
		int fileOwnerDriverId, fileVehicleID, fileRegNo, fileNumOfSeats, fileVehicleStatus, fileRideOrDelivery, fileRoute, fileTotalVehicleServices, day, month, year;
		float fileAvgMileage, fileVehicleOverallRanking;
		string fileVehicleModel, fileVehicleType, fileVehicleLicenseType;
		TransportionCategory category = CategoryNull;
		Route route = RouteNull;

		while (readVehicle >> fileOwnerDriverId >> fileVehicleID >> fileVehicleModel >> fileVehicleType >> fileRegNo >> fileVehicleLicenseType >> day >> month >> year
			>> fileAvgMileage >> fileNumOfSeats >> fileVehicleStatus >> fileRideOrDelivery >> fileRoute >> fileVehicleOverallRanking >> fileTotalVehicleServices)
		{
			//if no ID is passed than it will print all customers
			if (VehicleID == 0)
			{
				if (fileRideOrDelivery == 0)
					category = ride;
				else if (fileRideOrDelivery == 1)
					category = delivery;
				else if (fileRideOrDelivery == 2)
					category = BothTransportation;

				if (fileRoute == 0)
					route = Intracity;
				else if (fileRoute == 1)
					route = Intercity;
				else if (fileRoute == 2)
					route = BothRoute;

				Vehicle vehicle(fileVehicleID, fileOwnerDriverId, fileVehicleType, fileVehicleModel, fileRegNo, fileVehicleLicenseType, Date(day, month, year), fileAvgMileage,
					fileNumOfSeats, fileVehicleStatus, category, route, fileTotalVehicleServices);
				cout << vehicle;
			}
			//if VehicleID is passed than it matches and prints the corresponding Vehicle and return
			else if (VehicleID == fileVehicleID)
			{
				if (fileRideOrDelivery == 0)
					category = ride;
				else if (fileRideOrDelivery == 1)
					category = delivery;
				else if (fileRideOrDelivery == 2)
					category = BothTransportation;

				if (fileRoute == 0)
					route = Intracity;
				else if (fileRoute == 1)
					route = Intercity;
				else if (fileRoute == 2)
					route = BothRoute;

				Vehicle vehicle(fileVehicleID, fileOwnerDriverId, fileVehicleType, fileVehicleModel, fileRegNo, fileVehicleLicenseType, Date(day, month, year), fileAvgMileage,
					fileNumOfSeats, fileVehicleStatus, category, route, fileTotalVehicleServices);
				cout << vehicle;
				readVehicle.close();
				return;
			}
		}
	}
	else
		cout << "Vehicle File can't be opened for Printing Vehicle";
	readVehicle.close();
}
//Prints Service Histroy of a particular Vehicle ID, Driver ID or Customer ID
void TMS::printServiceHistory(int printAgainstID) 
{
	ifstream getServiceFromFile;

	string bookingTime, source, destination, RideOrDelivery;
	float distance, fuelrate, vehicleRanking, driverRanking;
	int	customerID, driverID, fileVehicleID, fare;
	int day, month, year;
	int serviceStatus;	//1 for Completed, 2 if Pending, 3 if Cancelled, 4 Pending Approval from Driver
	int route;			//0 for Intracity, 1 for Intercity 
	float noOfPassengersOrGoodsWeight; //holds NumOfPassengers if it was Ride else holds Goods Weight if it was Delivery
	string wantAcOrGoodsType;		 //holds WantAc (YES/NO) if it was Ride else holds Goods Type if it was Delivery
	bool printed = false;

	getServiceFromFile.open("Service.txt");
	if (getServiceFromFile.is_open())
	{
		while (getServiceFromFile >> customerID >> driverID >> fileVehicleID >> day >> month >> year >> bookingTime
			>> route >> source >> destination >> distance >> serviceStatus >> fuelrate >> fare >> driverRanking
			>> vehicleRanking >> RideOrDelivery >> noOfPassengersOrGoodsWeight >> wantAcOrGoodsType)
		{
				/*this IF match jo bhi ID pass ki gai ho ager wo customer sy match wo tu ussy print kr dy ager driver y tu
				ussy aur ager vehicle id pass ho gi tu vehicle id wali consdition sy true mil jai ga to print ho jai gi, tu 
				ek he function main sub kaaam ho jai ga, bus jahan function call ho wahan condition ho k jis hissab sy print krna 
				ha wohi ID  parameter main pass ho rhi ha, in teeno main sy koi ek he condition ek time sahi honi ha, kiyon k 
				ID unique hain tu match nhi kr skti*/

			if (printAgainstID == fileVehicleID || printAgainstID == driverID || printAgainstID == customerID)
			{
				cout << "\n-----------------------------------------------\n";
				cout << "\nCustomer ID : " << customerID;
				cout << "\nDriver ID : " << driverID;
				cout << "\nVehicle ID : " << fileVehicleID;
				cout << "\nBooking Date : " << day << "-" << month << "-" << year;
				cout << "\nBooking Time : " << bookingTime;
				cout << "\nRoute : "; route == Intracity ? cout << "Intracity" : cout << "Intercity";
				cout << "\nSource : " << source;
				cout << "\nDestination : " << destination;
				cout << "\nDistance : " << distance;
				//1 for Completed, 2 if Pending, 3 if Cancelled, 4 Pending Approval from Driver
				cout << "\nService Status : ";
				if (serviceStatus == 1)
					cout << "Completed";
				else if (serviceStatus == 2)
					cout << "Pending";
				else if (serviceStatus == 3)
					cout << "Cancelled";
				else if (serviceStatus == 4)
					cout << "Pending Driver Approval";
				cout << "\nFuel Rate : " << fuelrate;
				cout << "\nFare : " << fare;
				cout << "\nDriver Ranking : " << driverRanking;
				cout << "\nVehicle Ranking : " << vehicleRanking;

				if (RideOrDelivery == "Ride")
				{
					cout << "\nNo of Passengers : " << noOfPassengersOrGoodsWeight;
					cout << "\nWanted Ac : " << wantAcOrGoodsType;
					cout << "\n-----------------------------------------------\n";
				}
				else if (RideOrDelivery == "Delivery")
				{
					cout << "\nGood Weight : " << noOfPassengersOrGoodsWeight;
					cout << "\nGood Type : " << wantAcOrGoodsType;
					cout << "\n-----------------------------------------------\n";
				}

				printed = true;
			}
		}
	}
	else
		cout << "Service File can't be opened for printing Service History";
	getServiceFromFile.close();

	if (printed == false)
		cout << "No Service History Exist againt ID " << printAgainstID;
}
//Prints drivers who have ranking above or equal to 4.5
void TMS::printHighRankDriver() 
{
	fstream readDriver;
	
	readDriver.open("Drivers.txt");
	if (readDriver.is_open())
	{
		int driverID, driverVehicleID, age, driverStatus, totalServices, year, day, month;
		float driverOverallRanking, income, experience;
		string fName, lName, cnic, license;
		int totalDriversAbove4_5 = 0;
		int ranking4_5 = 0; //total Rankings above or equal to 4.5
	
	
		while (readDriver >> driverID >> driverVehicleID >> fName >> lName >> day >> month
			>> year >> age >> cnic >> experience >> license >> driverOverallRanking >> income >> driverStatus >> totalServices)
		{
			
			//reading total drivers who have ranking above or equal to 4.5
			if (driverOverallRanking >= 4.5)
			{
				++ranking4_5;
				++totalDriversAbove4_5;
			}
		}
		
		//Total Drivers inFile
		Driver* driver = new Driver[totalDriversAbove4_5];
		//Stores all rankings above 4.5 it can have duplicate values
		float* allRankingAbove4_5 = new float[totalDriversAbove4_5];
		//Array to store unique Rankings, it will not have same ranking twice
		float* filteredRankingAbove4_5 = new float[totalDriversAbove4_5];
		
		//initilizez every index with 0
		for (int i = 0; i < totalDriversAbove4_5; ++i)
		{
			allRankingAbove4_5[i] = 0.0;
			filteredRankingAbove4_5[i] = 0.0;
		}

		//setting cursor in file to start
		readDriver.clear();
		readDriver.seekg(0, ios::beg);
		
		//reading data again
		while (readDriver >> driverID >> driverVehicleID >> fName >> lName >> day >> month
			>> year >> age >> cnic >> experience >> license >> driverOverallRanking >> income >> driverStatus >> totalServices)
		
		{
			if (driverOverallRanking >= 4.5)
			{
				//initilizing driver array with all drivers in with ranking equal to or above 4.5
				for (int i = 0; i < totalDriversAbove4_5; i++)
				{
					driver[0] = Driver(driverID, driverVehicleID, fName, lName, day, month, year, cnic,
						experience, license, driverOverallRanking, income, driverStatus, totalServices);

					//storing ranking of all driver
					allRankingAbove4_5[i] = driverOverallRanking;
				}
			}
		}
		readDriver.close();
		
		//storing allRankingAbove4_5 in filteredRankingAbove4_5 to remove any duplicate value
		int filteredSize = 0;
		for (int i = 0; i < 7; ++i)
		{
			bool isDuplicate = false;
			for (int j = 0; j < filteredSize; ++j)
			{
				/*takes single element of allRankingAbove4_5and matches it with every element of filteredRankingAbove4_5  to see if
				the value in allRankingAbove4_5 array is already present in filteredRankingAbove4_5, if yes than it moves to next index of allRankingAbove4_5*/
				if (filteredRankingAbove4_5[j] == allRankingAbove4_5[i])
				{
					isDuplicate = true;
					break;
				}
			}
			//if value is not duplicate than it is stored in fiteredRankingAbove4_5 than 
			if (!isDuplicate)
			{
				filteredRankingAbove4_5[filteredSize] = allRankingAbove4_5[i];
				++filteredSize;
			}
		}
		/*created a new array of fixed size, i will not store no duplicate and no index will be empty as in case of filteredRankingAbove4_5
		some index at last could be of no use after duplicate values have been removed*/
		float* filteredAndSortedRankingAbove4_5 = new float[filteredSize];

		//initilizez every index
		for (int i = 0; i < filteredSize; ++i)
		{
			filteredAndSortedRankingAbove4_5[i] = filteredRankingAbove4_5[i];
		}
		//sorting it in descending order
		sortRankingInDescending(filteredRankingAbove4_5, filteredSize);

		//this loop print driver ascending order if the ranking of driver matches the ranking in filteredAndSortedRankingAbove4_5 array
		for (int i = 0; i < filteredSize; i++)
		{
			for (int j = 0; j < totalDriversAbove4_5; j++)
			{
				if (driver[j].getOverallRanking() == filteredAndSortedRankingAbove4_5[i])
				{
					cout << driver[j];
				}
			}
		}
		
		/*delete[] driver;
		driver = NULL;
		delete[] allRankingAbove4_5;
		allRankingAbove4_5 = NULL;
		delete[] filteredRankingAbove4_5;
		filteredRankingAbove4_5 = NULL;
		delete[] filteredAndSortedRankingAbove4_5;
		filteredAndSortedRankingAbove4_5 = NULL;*/

	}
	else
		cout << "Drivers File can not be opened for counting Drivers";
	readDriver.close();

}				  
void TMS::printLicensesDetails() 
{
	fstream readingDriver;
	readingDriver.open("Drivers.txt");

	if (readingDriver.is_open())
	{
		int driverID, driverVehicleID, age, driverStatus, totalServices, year, day, month;
		float driverOverallRanking, income, experience;
		string fName, lName, cnic, license, dash;

		while (readingDriver >> driverID >> driverVehicleID >> fName >> lName >> day >> month
			>> year >> age >> cnic >> experience >> license >> driverOverallRanking >> income >> driverStatus >> totalServices)
		{
			cout << "Name : " << fName << " " << lName << endl;
			cout << "CNIC : " << cnic << endl;
			cout << "Driver ID : " << driverID << endl;
			cout << "Vehicle ID : " << driverVehicleID << endl;
			cout << "Has License of HTV/LTV: " << license << endl;
			cout << "\n\n-----------------------------------------------\n\n";
		}
	}
	else
		cout << "Drivers File can't be opened for Printing Income";
	readingDriver.close();
}
//Prints Income of All Drivers
void TMS::printIncome() 
{
	fstream readingDriver;
	readingDriver.open("Drivers.txt");

	if (readingDriver.is_open())
	{
		int driverID, driverVehicleID, age, driverStatus, totalServices, year, day, month;
		float driverOverallRanking, income, experience;
		string fName, lName, cnic, license, dash;

		while (readingDriver >> driverID >> driverVehicleID >> fName >> lName >> day >> month
			>> year >> age >> cnic >> experience >> license >> driverOverallRanking >> income >> driverStatus >> totalServices)
		{
			cout << "Name : " << fName << " " << lName << endl;
			cout << "CNIC : " << cnic << endl;
			cout << "Driver ID : " << driverID << endl;
			cout << "Overall Ranking : " << driverOverallRanking << endl;
			cout << "Total Income : " << income << endl;
			cout << "Total Completed Services : " << totalServices << endl;
			cout << "\n\n-----------------------------------------------\n\n";			
		}
	}
	else
		cout << "Drivers File can't be opened for Printing Income";
	readingDriver.close();
}

void TMS::setDriverRanking(float currentGivenRating) 
{
	//The formula used is:
	//driverOverallRanking = ((driverOverallRanking * totalCompletedServices) + currentGivenRating) / (totalCompletedServices + 1);
	driver.setOverallRanking((driver.getOverallRanking() * driver.getTotalServices()) + currentGivenRating / (driver.getTotalServices() + 1));
	//adds one to total Completed Services of Driver
	driver.setTotalServices(1);
}
void TMS::setVehicleRanking(float currentGivenRating)
{
	//The formula used is:
	//vehicleOverallRanking = ((vehicleOverallRanking * totalVehicleCompletedServices) + currentGivenRating) / (totalVehicleCompletedServices + 1);
	driver.getVehicle().setOverallRanking((driver.getVehicle().getOverallRanking() * driver.getVehicle().getTotalVehicleServices()) + currentGivenRating / (driver.getVehicle().getTotalVehicleServices() + 1));
	//adds one to total Completed Services of Vehicle
	driver.getVehicle().setTotalVehicleServices(1);
}
	
//Print details of all pending services on a particular date.
void TMS::printAllPendingServices(Date dateToPrintData)
{
	ifstream getServiceFromFile;

	string bookingTime, source, destination, RideOrDelivery;
	float distance, fuelrate, vehicleRanking, driverRanking;
	int	customerID, driverID, fileVehicleID, fare;
	int day, month, year;
	int serviceStatus;	//1 for Completed, 2 if Pending, 3 if Cancelled, 4 Pending Approval from Driver
	int route;			//0 for Intracity, 1 for Intercity 
	float noOfPassengersOrGoodsWeight; //holds NumOfPassengers if it was Ride else holds Goods Weight if it was Delivery
	string wantAcOrGoodsType;		 //holds WantAc (YES/NO) if it was Ride else holds Goods Type if it was Delivery

	getServiceFromFile.open("Service.txt");
	if (getServiceFromFile.is_open())
	{
		while (getServiceFromFile >> customerID >> driverID >> fileVehicleID >> day >> month >> year >> bookingTime
			>> route >> source >> destination >> distance >> serviceStatus >> fuelrate >> fare >> driverRanking
			>> vehicleRanking >> RideOrDelivery >> noOfPassengersOrGoodsWeight >> wantAcOrGoodsType)
		{
			if ((serviceStatus == 2 || serviceStatus == 2) && dateToPrintData == Date(day, month, year))
			{
				cout << "\n-----------------------------------------------\n";
				cout << "\nCustomer ID : " << customerID;
				cout << "\nDriver ID : " << driverID;
				cout << "\nVehicle ID : " << fileVehicleID;
				cout << "\nBooking Date : " << day << "-" << month << "-" << year;
				cout << "\nBooking Time : " << bookingTime;
				cout << "\nRoute : "; route == Intracity ? cout << "Intracity" : cout << "Intercity";
				cout << "\nSource : " << source;
				cout << "\nDestination : " << destination;
				cout << "\nDistance : " << distance;
				//1 for Completed, 2 if Pending and 3 if Cancelled
				cout << "\nService Status : ";
				if (serviceStatus == 1)
					cout << "Completed";
				else if (serviceStatus == 2)
					cout << "Pending";
				else if (serviceStatus == 3)
					cout << "Cancelled";
				else if (serviceStatus == 4)
					cout << "Pending Driver Approval";
				cout << "\nFuel Rate : " << fuelrate;
				cout << "\nFare : " << fare;
				cout << "\nDriver Ranking : " << driverRanking;
				cout << "\nVehicle Ranking : " << vehicleRanking;

				if (RideOrDelivery == "Ride")
				{
					cout << "\nNo of Passengers : " << noOfPassengersOrGoodsWeight;
					cout << "\nWanted Ac : " << wantAcOrGoodsType;
					cout << "\n-----------------------------------------------\n";
				}
				else if (RideOrDelivery == "Delivery")
				{
					cout << "\nGood Weight : " << noOfPassengersOrGoodsWeight;
					cout << "\nGood Type : " << wantAcOrGoodsType;
					cout << "\n-----------------------------------------------\n";
				}
			}
		}
	}
	else
		cout << "Service File can't be opened for printing Service History of Driver";
	getServiceFromFile.close();
}			
//Print details of all pending services
void TMS::printAllPendingServices()
{
	ifstream getServiceFromFile;

	string bookingTime, source, destination, RideOrDelivery;
	float distance, fuelrate, vehicleRanking, driverRanking;
	int	customerID, driverID, fileVehicleID, fare;
	int day, month, year;
	int serviceStatus;	//1 for Completed, 2 if Pending and 3 if Cancelled
	int route;			//0 for Intracity, 1 for Intercity 
	float noOfPassengersOrGoodsWeight; //holds NumOfPassengers if it was Ride else holds Goods Weight if it was Delivery
	string wantAcOrGoodsType;		 //holds WantAc (YES/NO) if it was Ride else holds Goods Type if it was Delivery

	getServiceFromFile.open("Service.txt");
	if (getServiceFromFile.is_open())
	{
		while (getServiceFromFile >> customerID >> driverID >> fileVehicleID >> day >> month >> year >> bookingTime
			>> route >> source >> destination >> distance >> serviceStatus >> fuelrate >> fare >> driverRanking
			>> vehicleRanking >> RideOrDelivery >> noOfPassengersOrGoodsWeight >> wantAcOrGoodsType)
		{
			//if Service Status == 2 means Service is pending
			if (serviceStatus == 2 || serviceStatus == 4)
			{
				cout << "\n-----------------------------------------------\n";
				cout << "\nCustomer ID : " << customerID;
				cout << "\nDriver ID : " << driverID;
				cout << "\nVehicle ID : " << fileVehicleID;
				cout << "\nBooking Date : " << day << "-" << month << "-" << year;
				cout << "\nBooking Time : " << bookingTime;
				cout << "\nRoute : "; route == Intracity ? cout << "Intracity" : cout << "Intercity";
				cout << "\nSource : " << source;
				cout << "\nDestination : " << destination;
				cout << "\nDistance : " << distance;
				//1 for Completed, 2 if Pending and 3 if Cancelled
				cout << "\nService Status : ";
				if (serviceStatus == 1)
					cout << "Completed";
				else if (serviceStatus == 2)
					cout << "Pending";
				else if (serviceStatus == 3)
					cout << "Cancelled";
				else if (serviceStatus == 4)
					cout << "Pending Driver Approval";
				cout << "\nFuel Rate : " << fuelrate;
				cout << "\nFare : " << fare;
				cout << "\nDriver Ranking : " << driverRanking;
				cout << "\nVehicle Ranking : " << vehicleRanking;

				if (RideOrDelivery == "Ride")
				{
					cout << "\nNo of Passengers : " << noOfPassengersOrGoodsWeight;
					cout << "\nWanted Ac : " << wantAcOrGoodsType;
					cout << "\n-----------------------------------------------\n";
				}
				else if (RideOrDelivery == "Delivery")
				{
					cout << "\nGood Weight : " << noOfPassengersOrGoodsWeight;
					cout << "\nGood Type : " << wantAcOrGoodsType;
					cout << "\n-----------------------------------------------\n";
				}
			}
		}
	}
	else
		cout << "Service File can't be opened for printing Service History of Driver";
	getServiceFromFile.close();
}			
//Print details of all cancelled services 
void TMS::printAllCancelledServices() 
{
	ifstream getServiceFromFile;

	string bookingTime, source, destination, RideOrDelivery;
	float distance, fuelrate, vehicleRanking, driverRanking;
	int	customerID, driverID, fileVehicleID, fare;
	int day, month, year;
	int serviceStatus;	//1 for Completed, 2 if Pending and 3 if Cancelled
	int route;			//0 for Intracity, 1 for Intercity 
	float noOfPassengersOrGoodsWeight; //holds NumOfPassengers if it was Ride else holds Goods Weight if it was Delivery
	string wantAcOrGoodsType;		 //holds WantAc (YES/NO) if it was Ride else holds Goods Type if it was Delivery

	getServiceFromFile.open("Service.txt");
	if (getServiceFromFile.is_open())
	{
		while (getServiceFromFile >> customerID >> driverID >> fileVehicleID >> day >> month >> year >> bookingTime
			>> route >> source >> destination >> distance >> serviceStatus >> fuelrate >> fare >> driverRanking
			>> vehicleRanking >> RideOrDelivery >> noOfPassengersOrGoodsWeight >> wantAcOrGoodsType)
		{
			//if Service Status == 3 means Service is Cancelled
			if (serviceStatus == 3)
			{
				cout << "\n-----------------------------------------------\n";
				cout << "\nCustomer ID : " << customerID;
				cout << "\nDriver ID : " << driverID;
				cout << "\nVehicle ID : " << fileVehicleID;
				cout << "\nBooking Date : " << day << "-" << month << "-" << year;
				cout << "\nBooking Time : " << bookingTime;
				cout << "\nRoute : "; route == Intracity ? cout << "Intracity" : cout << "Intercity";
				cout << "\nSource : " << source;
				cout << "\nDestination : " << destination;
				cout << "\nDistance : " << distance;
				//1 for Completed, 2 if Pending and 3 if Cancelled
				cout << "\nService Status : ";
				if (serviceStatus == 1)
					cout << "Completed";
				else if (serviceStatus == 2)
					cout << "Pending";
				else if (serviceStatus == 3)
					cout << "Cancelled";
				cout << "\nFuel Rate : " << fuelrate;
				cout << "\nFare : " << fare;
				cout << "\nDriver Ranking : " << driverRanking;
				cout << "\nVehicle Ranking : " << vehicleRanking;

				if (RideOrDelivery == "Ride")
				{
					cout << "\nNo of Passengers : " << noOfPassengersOrGoodsWeight;
					cout << "\nWanted Ac : " << wantAcOrGoodsType;
					cout << "\n-----------------------------------------------\n";
				}
				else if (RideOrDelivery == "Delivery")
				{
					cout << "\nGood Weight : " << noOfPassengersOrGoodsWeight;
					cout << "\nGood Type : " << wantAcOrGoodsType;
					cout << "\n-----------------------------------------------\n";
				}
			}
		}
	}
	else
		cout << "Service File can't be opened for printing Service History of Driver";
	getServiceFromFile.close();
}
