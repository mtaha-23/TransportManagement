//22F-3277 and 22F-8803
#include<iostream>
#include<fstream>
#include<string>
#include"interface.h"
using namespace std;
int main()
{
	TMS indriver;
	User loginAs = loggedOut;

	while (loginAs == loggedOut)
	{
		loginAs = indriver.Sign_IN(0);
	}
	while (loginAs != EXIT)
	{
		indriver.LOGGED_IN(loginAs);
	}

	cout << "\nThanks for Using Our Cab Service";
	return 0;
}