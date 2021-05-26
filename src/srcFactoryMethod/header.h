#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Cars{
protected:
  int type;
public:
  Cars(){
    type = 0;
  }
  virtual void output() = 0;
};

class PickUpTruck: public Cars{ //Xe bán tải
private:

public:
  PickUpTruck(){
    type = 1;
  }
  ~PickUpTruck(){

  }
  void output(){
    cout << "A pickup truck is in production" << endl;
  }
};

class SportsCar: public Cars{ //Xe thể thao
private:

public:
  SportsCar(){
    type = 2;
  }
  ~SportsCar(){

  }
  void output(){
    cout << "A sports car is in production" << endl;
  }
};

class ConvertibleCar: public Cars{ //Xe mui trần
private:

public:
  ConvertibleCar(){
    type = 3;
  }
  ~ConvertibleCar(){

  }
  void output(){
    cout << "A convertible car is in production" << endl;
  }
};

