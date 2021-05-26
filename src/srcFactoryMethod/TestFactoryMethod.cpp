#include "header.h"
#include "factory.h"

int main(void){
  //Giả sử bây giờ tôi muốn xử lý đơn nhập hàng của một cửa hàng
  //Bao gồm một số lượng xe bất kỳ, và ngẫu nhiên nhiều dòng xe khác nhau
  cout << "Nhap so luong xe can nhap ve cua hang: ";
  int n; cin >> n;

  //Tạo một vector để quản lý các dòng xe:
  vector<Cars*> arrCars;
  arrCars.resize(n);

  //Xu ly nhap dong xe
  cout << "1. Dong xe ban tai - 2. Dong xe the thao - 3. Dong xe mui tran" << endl;
  for (int i = 0; i < n; i++){
    cout << "Nhap dong xe thu " << i+1 << ": ";
    int type; cin >> type;
    if (type > 0 && type <= 3){
      arrCars.at(i) = CarsFactory::produceCars(static_cast<eCars>(type));
      arrCars.at(i)->output();
    } 
  }
  return 0;
}
