//19120163 - Bùi Lê Tuấn Anh

/* Yêu cầu đề bài:

    Một hiệu sách có kinh doanh sách thuộc ba thể loại: Truyện tranh, Sách văn học trong nước và sách văn học nước ngoài. 
Trong đó:
  - Các quyển sách được xuất bản bằng Tiếng Việt (ngôn ngữ gốc hoặc biên dịch), phục vụ độc giả trong nước.
  - Mỗi quyển sách có các thông tin: Tên, tác giả, năm xuất bản, số trang, thể loại. Truyện tranh có thể có nhiều phần. 
Sách văn học có thể có nhiều chương.
  - Cần nhập và lấy thông tin sách để phục vụ việc trao đổi và buôn bán, và việc lấy thông tin của 1 quyển thuộc thể loại này 
không gây ảnh hưởng đến thông tin của những quyển thuộc thể loại khác.

Viết chương trình quản lý hiệu sách này.
Lưu ý: Thực tế có thể có nhiều thông tin về thể loại, ngôn ngữ xuất bản và nhà xuất bản sách, không xem xét trong bài tập này.

*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Book{
protected:
  string bookName; string author; 
  int yearPublished;
  int numPages; int type;
public:
  Book(){
    type = 0;
    numPages = 0;
  }
  virtual void input() = 0;
  virtual void output() = 0;
};

class CartoonBooks: public Book{ //Truyện tranh hoạt hình
private:
  int numParts;
public:
  CartoonBooks(){
    type = 1;
  }
  void input(){
    cout << "Nhap cac thong tin cua truyen: " << endl;
    cout << "Ten truyen: "; cin >> bookName;
    cout << "Tac gia: "; cin >> author;
    cout << "Nam xuat ban: "; cin >> yearPublished;
    cout << "So trang: "; cin >> numPages;
    cout << "Nhap so phan: "; cin >> numParts;
  }
  void output(){
    cout << "Thong tin cua quyen " << bookName << " - " << author << endl;
    cout << "The loai: Truyen tranh hoat hinh" << endl;
    cout << "Nam xuat ban: " << yearPublished << endl;
    cout << "So trang: " <<  numPages << endl;
    cout << "So phan: " << numParts << endl;
  }  
};

class VietnameseBooks: public Book{ //Sách văn học trong nước

};

class ForeignLanguageBooks: public Book{ //Sách văn học nước ngoài

};

class BookStore{ //Lớp quản lý thông tin sách - Factory Method

};


int main(void){
  return 0;
}
