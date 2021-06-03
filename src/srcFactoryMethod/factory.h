#include "header.h"

enum eCars{
  PICKUP_TRUCK = 1,
  SPORTS = 2,
  CONVERTIBLE = 3
};

class CarsFactory{
public:
  static Cars* produceCars(eCars _carsID){
    Cars* newCar = NULL;
    switch (_carsID)
    {
      case PICKUP_TRUCK:
        newCar = new PickUpTruck;
        break;
      case SPORTS:
        newCar = new SportsCar;
        break;
      case CONVERTIBLE:
        newCar = new ConvertibleCar;
        break; 
      default:
        cout << "Invalid car!!!" << endl;
        return NULL;
    }
    newCar->output();
  }
};