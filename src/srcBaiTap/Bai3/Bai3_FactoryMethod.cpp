#include "Phone.h"
#include "StorePhone.h"

int main()
{
	PhoneArray *Arr = new PhoneArray();
	Arr->input();
	cout << "-------------------" << endl;
	Arr->output();
	_getch();
	Arr->Search();
	return 0;
}