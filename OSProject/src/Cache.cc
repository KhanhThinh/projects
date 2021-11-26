#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "ui.cc"
using namespace std;

string const Cache::Path = "cache-fs";
string const Cache::Signature = "Cache-Final";

class Cache
{
private:
    static string const Path;
    static string const Signature;
    vector<string> VolumePathList;

    bool exist()
    {
        fstream f(this->Path, ios_base::in);
        if (f.is_open())
        {
            f.close();
            return true;
        }
        return false;
    }
    void init()
    {
        fstream f(this->Path, ios_base::out);
        if (f.is_open())
        {
            f.clear();
            f << this->Signature << "\n";
            f.close();
        }
    }
    void read()
    {
        fstream f(this->Path, ios_base::in);
        if (f.is_open())
        {
            f.clear();
            string s;
            getline(f, s, '\n');
            if (s != this->Signature)
            {
                throw "Signature error";
            }
            while (getline(f, s, '\n'))
            {
                this->VolumePathList.push_back(s);
            }
            f.close();
        }
    }

public:
    Cache()
    {
        if (this->exist())
        {
            this->read();
        }
        else
        {
            this->init();
        }
    }
    ~Cache(){};
    bool isEmpty() const
    {
        return this->VolumePathList.size() == 0;
    }
    void add(string const &volumeFilePath)
    {
        for (string str : this->VolumePathList)
        {
            if (str == volumeFilePath)
                return;
        }

        this->VolumePathList.push_back(volumeFilePath);
        fstream file(this->Path, ios_base::app);
        if (file.is_open())
        {
            file.clear();
            file << volumeFilePath << "\n";
            file.close();
        }
        else
        {
            throw "File name error";
        }
    }
    void update()
    {
        for (size_t i = 0; i < this->VolumePathList.size();)
        {
            fstream f(this->VolumePathList[i], ios_base::in);
            if (f.is_open())
            {
                f.close();
                return;
            }

            else
            {
                auto temp = this->VolumePathList[i];
                this->VolumePathList[i] = this->VolumePathList.back();
                this->VolumePathList.back() = temp;

                this->VolumePathList.pop_back();
            }
        }

        fstream file(this->Path, ios_base::out);
        if (file.is_open())
        {
            file.clear();
            file << this->Signature << "\n";
            for (string volumeFilePath : this->VolumePathList)
            {
                file << volumeFilePath << "\n";
            }
            file.close();
        }
    }
    void clear()
    {
        this->VolumePathList.clear();
        this->init();
    }
    void showListOfRecentlyOpenedVol() const
    {
        if (!this->isEmpty())
        {
            cout << "Recent volumes" << endl;
            for (size_t i = 0; i < this->VolumePathList.size(); ++i)
            {
                cout << "     <" << i + 1 << " > ";
                gotoXY(10, whereY());
                cout << this->VolumePathList[i] << endl;
            }
        }
    }
    bool hasVol(string &s) const
    {
        if (s.length() != 0 && s.front() == '<' && s.back() == '>')
        {
            size_t indexVol = 0;
            for (size_t i = 1; i < s.length() - 1; ++i)
            {
                if (s[i] >= '0' && s[i] <= '9')
                {
                    indexVol *= 10;
                    indexVol += s[i] - '0';
                }
                else
                {
                    indexVol = 0;
                    break;
                }
            }
            if (indexVol >= 1 && indexVol <= this->VolumePathList.size())
            {
                s = this->VolumePathList[indexVol - 1];
                return true;
            }
        }
        return false;
    }
};