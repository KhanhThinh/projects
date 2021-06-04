#include <iostream>
#include <vector>
using namespace std;

class Cars{
public:
  virtual void output() = 0;
  virtual void moveToStore() = 0;
};

class PickUpTruck: public Cars{ //Xe bán tải
public:
  void output(){
    cout << "A pickup truck is in production" << endl;
  }
  void moveToStore(){
    cout << "A pickup truck has been moved to store" << endl;
  }
};

class SportsCar: public Cars{ //Xe thể thao
public:
  void output(){
    cout << "A sports car is in production" << endl;
  }
  void moveToStore(){
    cout << "A sports car has been moved to store" << endl;
  }
};

class ConvertibleCar: public Cars{ //Xe mui trần
  void output(){
    cout << "A convertible car is in production" << endl;
  }
  void moveToStore(){
    cout << "A convertible car has been moved to store" << endl;
  }
};

enum eCars{
  PICKUP_TRUCK = 1,
  SPORTS = 2,
  CONVERTIBLE = 3
};

class CarsFactory{
public:
  static Cars* produceCars(eCars _carsID){
    switch (_carsID)
    {
      case 1: return new PickUpTruck();
      case 2: return new SportsCar();
      case 3: return new ConvertibleCar();
      default: return NULL;
    }
  }
};

void output(vector<Cars*>arrCars){
  for (unsigned int i = 0; i < arrCars.size();i++){
    arrCars.at(i)->output();
    arrCars.at(i)->moveToStore();
  }
}