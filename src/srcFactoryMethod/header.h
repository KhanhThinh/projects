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
protected:
  int n;
public:
  static vector<Cars*> arrCars;
  void inputCars(){
    cout << "Input the number of cars imported to your store: ";
    cin >> n;
    arrCars.resize(n);
  }
  vector<Cars*> getArrCars(){
    return arrCars;
  }

  int getNumber(){
    return n;
  }

  static Cars* produceCars(eCars _carsID){
    Cars* newCar = NULL;
    switch (_carsID)
    {
      case PICKUP_TRUCK:
        newCar = new PickUpTruck();
        break;
      case SPORTS:
        newCar = new SportsCar();
        break;
      case CONVERTIBLE:
        newCar = new ConvertibleCar();
        break; 
      default:
        cout << "Invalid car!!!" << endl;
        return NULL;
    }
    arrCars.push_back(newCar);
  }
  void output(){
    for (int i = 0; i < arrCars.size(); i++){
      
    }
  }
};

class OriginalCarsFactory{
public:
  virtual Cars* produceCars(eCars _carsID) = 0;
};

class PickUpFactory: public OriginalCarsFactory{
public:
  Cars* produceCars(eCars _carsID){
    if (_carsID == 1) return new PickUpTruck;
    else return NULL;
  }
};

class SportsFactory: public OriginalCarsFactory{
public:
  Cars* produceCars(eCars _carsID){
    if (_carsID == 2) return new SportsCar;
    else return NULL;
  }
};

class ConvertibleFactory: public OriginalCarsFactory{
public:
  Cars* produceCars(eCars _carsID){
    if (_carsID == 3) return new ConvertibleCar;
    else return NULL;
  }
};
