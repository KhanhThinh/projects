#include "Cache.cc"
#include "Volume.cc"

class Program
{
private:
    void open();
    void create();

    void init(string const &path)
    {
        this->vol = new Volume(path);
    }

    void close()
    {
        delete this->vol;
        this->vol = nullptr;
    }

    void homeScreen();
    void homeNav();
    Volume *vol;
    Cache buffer;

public:
    Program()
    {
        fixConsole();
        fixSize(123, 200);
        this->vol = nullptr;
    }

    ~Program()
    {
        if (this->vol != nullptr)
        {
            delete this->vol;
            this->vol = nullptr;
        }
    }

    void run()
    {
        this->homeNav();
    }
};