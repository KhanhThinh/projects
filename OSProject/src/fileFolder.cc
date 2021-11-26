#include "Entry.cc"

class File : public Entry
{
public:
    File() = default;
    File(Entry const &entry) : Entry(entry) {}
    ~File() {}

    void display() override
    {
        int y = whereY();
        gotoXY(73, y);
        cout << "File   ";
        gotoXY(0, y);
        Entry::display();
    }

    Entry *add(Entry const &entry) override
    {
        return nullptr;
    }
    void del(Entry *entry) override {}
    vector<Entry *> getSubEntryList() const override
    {
        return vector<Entry *>();
    }
    bool hasChildSameName(Entry const &entry) const override
    {
        return true;
    }
};

class Folder : public Entry
{
private:
    vector<Entry *> list;

public:
    Folder() = default;
    Folder(Entry const &entry) : Entry(entry) {}
    ~Folder()
    {
        for (size_t i = 0; i < this->list.size(); ++i)
        {
            if (this->list[i] != nullptr)
            {
                delete this->list[i];
                this->list[i] = nullptr;
            }
        }
        this->list.resize(0);
        this->list.shrink_to_fit();
    }

    Entry *add(Entry const &temp) override
    {
        Entry *e;
        if (temp.IsFolder())
        {
            e = new Folder(temp);
        }
        else
        {
            e = new File(temp);
        }
        this->list.push_back(e);
        return e;
    }

    void del(Entry *entry) override
    {
        for (auto iter = this->list.begin(); iter != this->list.end(); ++iter)
        {
            if (*iter == entry)
            {
                delete *iter;
                this->list.erase(iter);
                this->list.shrink_to_fit();
                return;
            }
        }
    }

    vector<Entry *> getSubEntryList() const override
    {
        return this->list;
    }

    bool hasChildSameName(Entry const &entry) const override
    {
        for (size_t i = 0; i < this->list.size(); ++i)
        {
            if (this->list[i]->getName() == entry.getName())
            {
                return true;
            }
        }
        return false;
    }

    void display()
    {

        int y = whereY();
        gotoXY(73, y);
        cout << "Folder     ";
        gotoXY(0, y);

        Entry::display();
    }
    void displayParent()
    {

        cout << "..";
        printSpace(120);
        int y = whereY();
        gotoXY(73, y);
        cout << "Folder     ";
        gotoXY(0, y + 1);
    }

    void show()
    {
        displayParent();
        for (int i = 0; i < list.size(); i++)
        {
            list[i]->display();
        }
    }

    int getSize()
    {
        return list.size();
    }

    Entry *getEntry(int i)
    {
        return list[i];
    }
};