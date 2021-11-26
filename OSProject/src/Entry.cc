#include "Console.cc"
#include "SHA256.h"
#include "ui.cc"
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class Entry
{
    friend class EntryTable;

private:
    void initName()
    {
        size_t startPos = 0;
        for (int i = this->PathLen - 1 - this->IsFolder(); i >= 0; --i)
        {
            if (this->path[i] == SLASH)
            {
                startPos = i + 1;
                break;
            }
        }
        this->name = this->path.substr(startPos, this->PathLen - startPos - this->IsFolder());
    }

    void standardPath()
    {
        string temp = "";
        for (size_t i = 0; i < this->PathLen; ++i)
        {
            if (this->path[i] == '\\')
            {
                temp += '/';
            }
            else
            {
                temp += this->path[i];
            }
        }

        this->path = temp;
        this->PathLen = temp.length();
    }

    void updatePath(Entry *parent)
    {
        this->path = parent->getPath() + this->path;
        this->PathLen = this->path.length();
    }

protected:
    uint16_t ModifiedTime;
    uint16_t ModifiedDate;
    uint32_t SizeData;
    uint16_t PathLen;
    uint16_t PassLen;
    uint64_t OffsetData;
    string path;
    string pass;
    string name;
    string fullPath;
    bool isFolder;

public:
    static const char SLASH = '/';
    Entry()
    {
        this->ModifiedTime = 0;
        this->ModifiedDate = 0;
        this->SizeData = 0;
        this->PathLen = 0;
        this->PassLen = 0;
        this->OffsetData = 0;
        this->path = "";
        this->pass = "";
        this->name = "";

        this->fullPath = "";
        this->isFolder = false;
    }

    Entry(Entry const &entry)
    {
        *this = entry;
    }

    virtual ~Entry() {}

    void read(fstream &f)
    {
        f.read((char *)&this->ModifiedTime, sizeof(this->ModifiedTime));
        f.read((char *)&this->ModifiedDate, sizeof(this->ModifiedDate));
        f.read((char *)&this->SizeData, sizeof(this->SizeData));
        f.read((char *)&this->PathLen, sizeof(this->PathLen));
        f.read((char *)&this->PassLen, sizeof(this->PassLen));
        f.read((char *)&this->OffsetData, sizeof(this->OffsetData));

        this->path.resize(this->PathLen);
        f.read((char *)this->path.c_str(), this->PathLen);

        this->pass.resize(this->PassLen);
        f.read((char *)this->pass.c_str(), this->PassLen);

        this->initName();
    }

    void write(fstream &f) const
    {
        f.write((char *)&this->ModifiedTime, sizeof(this->ModifiedTime));
        f.write((char *)&this->ModifiedDate, sizeof(this->ModifiedDate));
        f.write((char *)&this->SizeData, sizeof(this->SizeData));
        f.write((char *)&this->PathLen, sizeof(this->PathLen));
        f.write((char *)&this->PassLen, sizeof(this->PassLen));
        f.write((char *)&this->OffsetData, sizeof(this->OffsetData));
        f.write((char *)this->path.c_str(), this->PathLen);
        f.write((char *)this->pass.c_str(), this->PassLen);
    }

    bool IsFolder() const
    {
        if (this->path == "")
            throw "LogicError";
        return this->path.back() == SLASH;
    }

    bool isLocked() const
    {
        return this->PassLen != 0;
    }

    bool hasName(string const &n) const
    {
        return n == this->name;
    }

    bool hasParent(Entry const *parent) const
    {
        string parPath = parent->getPath();
        if (parPath.length() >= this->PathLen)
            return false;
        size_t i = 0;
        while (i < parPath.length())
        {
            if (parPath[i] != this->path[i])
                return false;
            ++i;
        }
        // TODO: Fix error
        while (i < (size_t)(this->PathLen - this->IsFolder()))
        {
            if (this->path[i] == SLASH)
            {
                return false;
            }
            ++i;
        }
        return true;
    }

    string getPath() const
    {
        return this->path;
    }
    uint32_t getSizeData() const
    {
        return this->SizeData;
    }
    uint32_t getSize() const
    {
        return sizeof(this->ModifiedTime) + sizeof(this->ModifiedDate) + sizeof(this->SizeData) + sizeof(this->PathLen) + sizeof(this->PassLen) + sizeof(this->OffsetData) + this->path.length() + this->pass.length();
    }
    uint16_t getPassLen() const
    {
        return this->PassLen;
    }
    string getFullPath() const
    {
        return this->fullPath;
    }
    bool getIsFolder() const
    {
        return this->isFolder;
    }

    virtual Entry *add(Entry const &entry)
    {
        return nullptr;
    }

    virtual void del(Entry *entry) {}

    virtual vector<Entry *> getSubEntryList() const
    {
        return vector<Entry *>();
    }

    virtual bool hasChildSameName(Entry const &entry) const
    {
        return true;
    }

    void write(ostream &f) const
    {
        f.write((char *)&this->ModifiedTime, sizeof(this->ModifiedTime));
        f.write((char *)&this->ModifiedDate, sizeof(this->ModifiedDate));
        f.write((char *)&this->SizeData, sizeof(this->SizeData));
        f.write((char *)&this->PathLen, sizeof(this->PathLen));
        f.write((char *)&this->PassLen, sizeof(this->PassLen));
        f.write((char *)&this->OffsetData, sizeof(this->OffsetData));
        f.write((char *)this->path.c_str(), this->PathLen);
        f.write((char *)this->pass.c_str(), this->PassLen);
    }

    virtual void display()
    {
        cout << " " << name;
        printSpace(49 - name.length());

        if (!IsFolder())
        {
            string s = numCommas(this->SizeData);
            printSpace(20 - s.length());
            cout << s << "  ";
        }
        else
        {
            printSpace(23);
        }

        gotoXY(whereX() + 10, whereY());

        cout << "  ";
        this->dispModDate();
        cout << "  ";
        this->dispModTime();
        printSpace(27 - 19);

        if (isLocked())
        {
            printSpace(10 - 3);
            cout << "YES";
        }

        else
        {
            printSpace(10 - 2);
            cout << "NO";
        }
        cout << endl;
    }
    virtual void show() {}
    virtual int getListSize()
    {
        return 0;
    }

    virtual Entry *getEntry(int i)
    {
        return nullptr;
    }

    void setPass(string pass)
    {
        SHA256 sha;
        this->pass = sha(addPepper(addSalt(pass)));
        this->PassLen = pass.length();
    }

    void resetPass()
    {
        this->pass = "";
        this->PassLen = 0;
    }
    bool checkPass(string pass)
    {
        SHA256 sha;
        uint8_t salt[3] = {0x4E, 0x48, 0x54};

        for (int i = 0; i < pass.length(); i++)
        {
            ui::checkPassword(i);

            string test = pass;
            test[i] ^= salt[0];

            for (int j = 0; j < pass.length(); j++)
            {
                string test1 = test;
                test1[j] ^= salt[1];

                for (int k = 0; k < pass.length(); k++)
                {
                    string test2 = test1;
                    test2[k] ^= salt[2];

                    uint8_t v = 0;
                    while (true)
                    {
                        string toSHA = test2 + (char)v;
                        toSHA = sha(toSHA);

                        if (this->pass.compare(toSHA) == 0)
                            return true;
                        if (v = 255)
                            break;
                        else
                            v++;
                    }
                }
            }
        }
        return false;
    }
    string getName() const
    {
        return this->name;
    }
    void dispModTime()
    {
        uint8_t hour, min, sec;

        hour = (this->ModifiedTime >> 11);
        if (hour < 10)
            cout << "0" << (int)hour << ":";
        else
            cout << (int)hour << ":";

        min = (this->ModifiedTime >> 5) & 63;
        if (min < 10)
            cout << "0" << (int)min << ":";
        else
            cout << (int)min << ":";

        sec = (this->ModifiedTime & 31) << 1;
        if (sec < 10)
            cout << "0" << (int)sec;
        else
            cout << (int)sec;
    }

    void dispModDate()
    {
        uint8_t date, month, year;
        date = month = year = 0;
        string dom;

        date = this->ModifiedDate & 31;
        if (date < 10)
            cout << "0" << (int)date << "/";
        else
            cout << (int)date << "/";

        month = (this->ModifiedDate >> 5) & 15;
        if (date < 10)
            cout << "0" << (int)month << "/";
        else
            cout << (int)month << "/";

        year = (this->ModifiedDate >> 9);
        cout << ((int)year + 1980);
    }

    void seekToHead_g(fstream &f) const
    {
        f.seekg((uint64_t)this->OffsetData);
    }

    void seekToHead_p(fstream &f) const
    {
        f.seekp((uint64_t)this->OffsetData);
    }

    void seekToEnd_g(fstream &f) const
    {
        f.seekg((uint64_t)this->OffsetData + (uint64_t)this->SizeData);
    }

    void seekToEnd_p(fstream &f) const
    {
        f.seekp((uint64_t)this->OffsetData + (uint64_t)this->SizeData);
    }

    void convert(_WIN32_FIND_DATAA ffd, string fpath, string fname, uint64_t &insert_pos)
    {
        FileTimeToDosDateTime(&ffd.ftLastWriteTime, &this->ModifiedDate, &this->ModifiedTime);

        this->SizeData = ffd.nFileSizeLow;
        this->PathLen = fname.length();
        this->PassLen = 0;
        this->OffsetData = insert_pos;
        insert_pos += this->SizeData;

        this->path = fname;
        this->fullPath = fpath;

        if (ffd.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
            this->isFolder = true;
        else
            this->isFolder = false;
    }

    void standardizeImport(Entry *parent)
    {
        this->standardPath();
        this->updatePath(parent);
        this->initName();
    }
};
