#include "header.h"

int main(void){
  vector<Cars*> arrCars;
  int type; int i = 0;
  cout << "1 - Pickup Truck, 2 - Sports Cars, 3 - Convertible Cars, 0 - Exit" << endl;
  while (true)
  {
    cout << "Your type of car " << i + 1 << ": "; 
    cin >> type;
    if (type == 0 || type > 3) break;
    arrCars.push_back(CarsFactory::produceCars(static_cast<eCars>(type)));
    i++;
  }
  output(arrCars);
  return 0;
}
