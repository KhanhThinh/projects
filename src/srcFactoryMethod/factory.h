#include "header.h"

enum eCars{
  PICKUP_TRUCK = 1,
  SPORTS = 2,
  CONVERTIBLE = 3
};

class CarsFactory{
public:
  CarsFactory(){}
  ~CarsFactory(){}
  static Cars* produceCars(eCars _carsID){
    switch (_carsID)
    {
      case PICKUP_TRUCK:
        return new PickUpTruck();
        break;
      case SPORTS:
        return new SportsCar();
        break;
      case CONVERTIBLE:
        return new ConvertibleCar();
        break; 
      default:
        return NULL;
        break;
    }
  }
};