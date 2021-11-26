#include <Windows.h>
#include <queue>
using namespace std;

#include "VolumeInfo.cc"
#include "ui.cc"
#include "EntryTable.cc"

enum class ExportState
{
    SUCCESS = 0,
    NOT_FINISHED,
    SAME_NAME,
    BAD_PATH
};

class Volume
{
private:
    void init(string const &volumePath)
    {
        LPTSTR lptstrVFP = new TCHAR;
    }

    void seekToHead_g(fstream &f) const
    {
        f.seekg(0 - (int)sizeof(info), ios_base::end);
    }

    void seekToHead_p(fstream &f) const
    {
        f.seekp(0 - (int)sizeof(info), ios_base::end);
    }

    void seekToHeadEntry_g(fstream &f) const
    {
        this->info.seekToHead_g(f);
    }

    void seekToHeadEntry_p(fstream &f) const
    {
        this->info.seekToHead_p(f);
    }

    void perform()
    {
        this->navigate(this->table.root);
    }

    void navigate(Entry *entry);
    void update(Entry *entry);
    bool enterFolder(Entry *parent, bool &back);

    void setPass(Entry *f);
    void writeChange()
    {
        fstream f(this->Path, ios_base::in | ios_base::out | ios_base::binary);
        uint64_t newSize = 0;
        if (f.is_open())
        {
            this->seekToHeadEntry_p(f);
            this->table.write(f);
            this->info.write(f);

            newSize = f.tellp();
            f.close();

            this->resize(newSize);
        }
    }

    void delOnVol(Entry *f);
    bool del(Entry *entry, Entry *parent);

    void importGUI(Entry *parent);
    bool import(string const &newPath, Entry *parent);

    void exportGUI(Entry *f);
    ExportState exportFile(Entry *export_file, string const &desPath);

    void resize(uint64_t const &s);

    string Path;
    VolumeInfo info;
    EntryTable table;

public:
    Volume(string const &volumePath) : info(), table()
    {
        this->init(volumePath);
    }

    ~Volume() {}

    bool isVolumeFile()
    {
        bool isVolume = false;
        fstream f(this->Path, ios_base::in | ios_base::binary);
        if (f.is_open())
        {
            f.clear();
            this->seekToHead_g(f);
            this->info.read(f);
            isVolume = this->info.checkSign(f);
            f.close();
        }
        return isVolume;
    }

    bool create()
    {
        fstream temp(this->Path, ios_base::in | ios_base::binary);
        if (temp.is_open())
        {
            temp.close();
            return false;
        }

        fstream f(this->Path, ios_base::out | ios_base::binary);
        if (f.is_open())
        {
            f.clear();
            this->info.write(f);
            f.close();
            return true;
        }
        return false;
    }

    void open()
    {
        fstream f(this->Path, ios_base::in | ios_base::binary);
        if (f.is_open())
        {
            this->seekToHead_g(f);
            this->info.read(f);

            this->seekToHeadEntry_g(f);
            this->table.read(f, this->info);
            f.close();
        }
        this->perform();
    }

    bool isEmpty() const
    {
        return this->info.isEmpty();
    }

    string getPath() const
    {
        return this->Path;
    }
    static string const Extension;
};