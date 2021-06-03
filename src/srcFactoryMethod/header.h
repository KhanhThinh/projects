#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Cars{
public:
  virtual void output() = 0;
};

class PickUpTruck: public Cars{ //Xe bán tải
public:
  void output(){
    cout << "A pickup truck is in production" << endl;
  }
};

class SportsCar: public Cars{ //Xe thể thao
public:
  void output(){
    cout << "A sports car is in production" << endl;
  }
};

class ConvertibleCar: public Cars{ //Xe mui trần
  void output(){
    cout << "A convertible car is in production" << endl;
  }
};

