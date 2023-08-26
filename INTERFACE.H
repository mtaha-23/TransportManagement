//22F-3277 and 22F-8803
#include<iostream>
#include<string>
#include<cstdlib>
#include<ctime>
#include<regex>
#include<fstream>
#include<cstdlib>
#include<Windows.h>
#include<iomanip>
using namespace std;
//class declarations
class Customer;
class Vehicle;
class Driver;
class Service;
class Ride;
class Delivery;

//enum
enum TransportionCategory { CategoryNull = -1, ride, delivery, BothTransportation };
enum Route { RouteNull = -1, Intracity, Intercity, BothRoute };
enum  User { EXIT = -1 , loggedOut, asAdmin, asCustomer, asDriver };

//functions
bool checkNumbersInCNIC(string);
bool checkCharacters(string);
bool checkNumber(string);
void sortRankingInDescending(float rankings[], int size);
int generate4digitID();	//used for generating 4 digit unique ID for customer, driver, and vehicle
void deleteFromFile(const string& filePath, int deleteLineNo);
bool isValidID(int ID, User loginAs);

//---------------------------------------------------------------------------------------

class Time
{
private:
	time_t currentTime;
	struct tm timeInfo;

public:
	Time();
	Time(const string&);
	//getter
	int getCurrentYear();
	int getCurrentMonth();
	int getCurrentDay();
	time_t getCurrentTime() const;
	string getCurrentTimeString() const;
	friend ostream& operator << (ostream&, const Time&);
	~Time();
};

//---------------------------------------------------------------------------------------

class Date
{
private:
	int day;
	int month;
	int year;

public:
	//default and overloaded constructor
	Date(int day, int month, int year);
	Date(string);
	void setDay(int);
	void setMonth(int);
	void setYear(int);
	int getDay();
	int getMonth();
	int getYear();
	//operator overload
	friend ostream& operator << (ostream&, const Date&);
	friend istream& operator >> (istream&, Date&);
	bool operator== (const Date&) const;
	~Date();
};

//---------------------------------------------------------------------------------------

class Name
{
private:
	string fName;
	string lName;

public:
	//default and overloaded constructor
	Name(string = "", string = "");
	//setter and getter
	void setFirstName(string);
	void setLastName(string);
	string getFirstName();
	string getLastName();
	//operator overload
	friend istream& operator >> (istream& in, Name& n);
	friend ostream& operator << (ostream& out, const Name& n);
	~Name();
};

//---------------------------------------------------------------------------------------

class Person
{
protected:
	Name personName;
	Date DOB;
	int age;
	string CNIC;
public:
	//default constructor
	Person();
	//Overloaded Constructor
	Person(string fName, string lName, int day, int month, int year, string cnic);
	Person(string fName, string lName, Date date, string cnic);
	//Copy Constructor
	Person(const Person& other);
	void setName();
	//setter
	void setName(string, string);
	void setDOB();
	void setDOB(int, int, int);
	void setAge(Date);
	void setCNIC();
	void setCNIC(string);
	//getter
	Name getName() const;
	Date getDOB() const;
	int getAge() const;
	string getCNIC() const;
	//Output operator
	friend ostream& operator << (ostream& out, const Person& p);
	friend istream& operator >> (istream& out, Person& p);
	//Destructor
	~Person();

};

//---------------------------------------------------------------------------------------

class Customer : public Person
{
private:
	int customerID;
	int totalBookings;

public:
	Customer();
	Customer(string fName, string lName, Date dob, string cnic, int CustomerID, int totalBooking);
	Customer(const Customer& c);
	//setter
	void setCustomerID(int);
	void setTotalBookings(int);
	//getter
	int getCustomerID() const;
	int getTotalBookings() const;
	//other methods
	void addNewCustomer();
	void selectIntercityOptions(int choice, string& source, string& destination, float& distance);	//out of city
	void selectIntracityOptions(string& source, string& destination, float& distance);	//with in same  city
	//to write customer in File
	void getCustomerFromFile(int);
	void writeCustomerInFile();
	void deleteCustomerFromFile();
	
	friend ostream& operator << (ostream& os, Customer&);
	~Customer();
};

//---------------------------------------------------------------------------------------

class Vehicle
{
private:
	int vehicleID;
	int ownerDriverId;			//driver Id of driver who owns the vehicle
	string vehicleType;			//Bus,van,car input
	string vehicleModel;		//Corolla, City, Civic etc
	int registrationNo;
	string vehicleLicenseType;  //License required for driving the vehicle
	Date manufacturingDate;
	float avgMileage;
	int numOfSeats;				//including driver seat
	bool vehicleStatus;			//false(0) for free, (1)true if booked in a service already
	TransportionCategory rideOrDelivery;
	Route route;
	float overallRanking;
	int totalCompletedServices;
public:
	Vehicle();
	Vehicle(int vehicleID, int OwnerDriverId, string VehicleType, string vehicleModel, int regNo, string vehicleLicenseType,
		Date manufacturingDate, float avgMileage, int numOfSeats, bool status, TransportionCategory rideOrDelivery,
		Route route, int totalCompletedServices);
	void setVehicleID(int);
	void setOwnerDriverID(int);
	void setVehicleModel(string);
	void setVehicleType(string);
	void setRegNo(int);
	void setVehicleLicenseType(string);
	void setManufacturingDate(Date);
	void setAvgMileage(float);
	void setNoOfSeats(int);
	void setVehicleStatus(bool);
	void setRideOrDelivery(TransportionCategory);
	void setRoute(Route);	//sets Intracity, InterCity
	void setOverallRanking(float);
	void setTotalVehicleServices(int);


	int getVehicleID();
	int getOwnerDriverID();
	string getVehicleModel();
	string getVehicleType();
	int getRegNo();
	string getVehicleLicenseType();
	Date getManufacturingDate();
	float getAvgMileage();
	int getNoOfSeats();
	bool getVehicleStatus();
	TransportionCategory getRideOrDelivery();
	Route getRoute();
	float getOverallRanking();
	int getTotalVehicleServices() const;

	void writeVehicleInFile();
	Vehicle getVehicleFromFile(int);
	friend ostream& operator << (ostream& os, const Vehicle&);

	~Vehicle();
};

//---------------------------------------------------------------------------------------

class Driver : public Person
{
protected:
	int driverId;
	float experience;				//in years
	string driverLicence;			//for Small Vehicle, Large Vehicle, Both Vehicles
	Vehicle vehicle;				//Vehicle the Driver Owns	
	float driverOverallRanking;
	float totalIncome;
	int driverStatus;				// 1 for free, 2 if booked
	int totalCompletedServices;

public:
	Driver();
	Driver(string fName, string lName, Date dob,
		string cnic, float experience, string drivingLicense,
		Vehicle vehicle, float driverOverallRanking, int status);
	Driver(int driverID, int vehicleID, string fName, string lName, int day, int month, int year,
		string cnic, float experience, string drivingLicense,
		float driverOverallRanking, float income, int status,
		int totalServices);
	void setDriverID(int);	//sets unique driver ID
	void setExperience(float);
	void setDriverLicence(string);
	void setVehicle();	
	void setVehicle(Vehicle);
	void setOverallRanking(float);
	void setTotalIncome(float);
	void setDriverStatus(int);
	void setDriverService(Delivery);
	void setDriverService(Ride);
	void setTotalServices(int);
	
	int getDriverID() const;
	float getExperience() const;
	string getDriverLicense() const;
	Vehicle getVehicle();
	float getOverallRanking() const;
	float getTotalIncome() const;
	int getDriverStatus() const;
	int getTotalServices() const;

	void AddNewDriver();
	void writeDriverInFile();
	void getDriverFromFile(int);
	void removePreviousVehicleOfDriver();
	void deleteDriverfromFile();
	void addVehicle();
	friend ostream& operator << (ostream& os, Driver&);

	~Driver();

};

//---------------------------------------------------------------------------------------

class Service
{
private:
	Date bookingDate;
	Time bookingTime;
	Route route; // intercity, intracity
	string source;		//starting location
	string destination;
	float distance; //in km
	int serviceStatus; //1 for Completed, 2 if Pending, 3 if Cancelled and 4 Pending Aproval from Driver === PENDING means ride is accepted by driver but not Completed
	float fuelrate;
	int	customerID; //Customer Id who booked the ride
	int driverID; //Driver Id
	int vehicleID; //vehicle Id
	int fare;
	float vehicleRanking; //0 to 5 scale (worst to best)
	float driverRanking; //0 to 5 scale (worst to best)

public:
	Service();
	Service(Date bookingDate, Time bookingTime, Route route,
		string source, string destination, float distance,
		int status, float fuelrate, int customerID, int driverID,
		int vehicleID, int fare, float vehicleRanking, float driverRanking);

	void setBookingDate(Date);
	void setBookingTime(Time);
	void setRoute(Route);
	void setSource(string);
	void setDestination(string);
	void setDistance(float);
	void setServiceStatus(int);
	void setFuelRate(float);
	void setCustomerID(int);
	void setDriverID(int);
	void setVehicleID(int);
	void setFare(int);
	void setVehicleRanking(float);
	void setDriverRanking(float);

	Date getBookingDate() const;
	Time getBookingTime() const;
	Route getRoute() const;
	string getSource() const;
	string getDestination() const;
	float getDistance() const;
	int getServiceStatus() const;
	float getFuelRate() const;
	int getCustomerID() const;
	int getDriverID() const;
	int getVehicleID() const;
	int getFare() const;
	float getVehicleRanking() const;
	float getDriverRanking() const;
	//pure virtual
	virtual void setRideTypeDetails(float, string) = 0;
	virtual void getRideTypeDetails(float&, string&) const = 0;
	virtual float CalculateFare(float mileage, float vehicelOverallRanking, float driverOverallRanking) = 0;
	virtual void writeServiceInFile();

};

//---------------------------------------------------------------------------------------

class Ride : public Service
{
	int noOfPassengers;
	string wantAc;  //Yes or No will be stored

public:
	Ride();
	Ride(Date bookingDate, Time bookingTime, Route route,
		string source, string destination, float distance,
		int status, float fuelrate, int customerID, int driverID,
		int vehicleID, int fare, float vehicleRanking,
		float driverRanking, int noOfPassengers, string wantAc);
	//setter 
	void setNoOfPassenger(int);
	void setWantAc(string);
	//getter 
	int getNoOfPassenger() const;
	string getWantAc() const;
	//pure virtual
	void setRideTypeDetails(float, string) override;
	void getRideTypeDetails(float& num, string& Ac) const override;
	
	float CalculateFare(float mileage, float vehicelOverallRanking, float driverOverallRanking);
	void writeServiceInFile();
	
	~Ride();
};

//---------------------------------------------------------------------------------------

class Delivery : public Service
{
	float goodsWeight;	//Weight of goods in Kg
	string goodsType;	//Courier or Frieght

public:
	Delivery();
	Delivery(Date bookingDate, Time bookingTime, Route route, 
		string source, string destination, float distance, int status,
		float fuelrate, int customerID, int driverID, int vehicleID, 
		int fare, float vehicleRanking, float driverRanking, 
		float weight, string type);
	//setter
	void setWeight(float);
	void setGoodType(string);
	//getter
	float getWeight() const;
	string getGoodType() const;
	//pure virtual 
	void setRideTypeDetails(float, string) override;
	void getRideTypeDetails(float& weight, string& type) const override;

	float CalculateFare(float mileage, float vehicelOverallRanking, float driverOverallRanking);
	void writeServiceInFile();

	~Delivery();
};

//---------------------------------------------------------------------------------------

class TMS 
{ 
	User loginAs;
	Customer customer;
	Driver driver;
	//Vehicle vehicle; //getter setter and constructor initalizing remaining
	
public:
	TMS();
	TMS(User loginAs);
	User Sign_IN(int);
	void LOGGED_IN(User loginAs);
	void addNewCustomer();	
	bool removeCustomer(int);
	void addNewDriver();
	bool removeDriver(int);
	void printDrivers(int = 0);					//Prints single driver ID if DriverID is passes else it will print all Drivers
	void printCustomers(int = 0);				//Prints single Customer ID if CustomerID is passes else it will print all Customers
	void printVehicles(int = 0);				//Prints single Vehicle ID if VehicleID is passes else it will print all Vehilcles
	void printServiceHistory(int);				//Prints Service Histroy of a particular Vehicle ID, Driver ID or Customer ID
	void printHighRankDriver();				    //Prints drivers who have ranking above 4.5.
	void printLicensesDetails();
	void printIncome();
	void BookAService();
	void viewServiceRequest();
	void setDriverRanking(float);
	void setVehicleRanking(float);
	void printAllPendingServices(Date);			//Print details of all pending services on a particular date
	void printAllPendingServices();				//Print details of all pending services 
	void printAllCancelledServices();			//Print details of all canceled services by a customer.
};