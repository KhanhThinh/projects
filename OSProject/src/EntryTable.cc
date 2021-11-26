#include "Entry.cc"
#include "fileFolder.cc"
#include "ui.cc"
#include "VolumeInfo.cc"

class EntryTable
{
    friend class Volume;

private:
    Entry *root;
    vector<Entry *> list;

public:
    EntryTable()
    {
        this->root = new Folder();
    }

    ~EntryTable()
    {
        if (this->root != nullptr)
        {
            delete this->root;
            this->root = nullptr;
        }
    }
    void read(fstream &f, VolumeInfo const &info)
    {
        while (!info.isEnd(f))
        {
            Entry e;
            e.read(f);
            this->add(e);
        }
    }
    void write(fstream &f) const
    {
        for (Entry *e : this->list)
        {
            e->write(f);
        }
    }

    void add(Entry const &entry)
    {
        bool found = false;
        for (size_t i = 0; i < this->list.size(); ++i)
        {
            if (entry.hasParent(this->list[i]))
            {
                this->list.push_back(this->list[i]->add(entry));
                found = true;
                return;
            }
        }
        if (!found)
            this->list.push_back(this->root->add(entry));
    }
    void updateWhenDelete(Entry const *entry)
    {
        auto del = this->list.begin();
        auto iter = this->list.begin();

        for (; iter != this->list.end(); ++iter)
        {
            if (*iter == entry)
            {
                del = iter;
                break;
            }
        }
        if (iter == this->list.end())
        {
            throw "LogicError";
        }

        for (++iter; iter != this->list.end(); ++iter)
        {
            (*iter)->OffsetData -= (*del)->SizeData;
        }

        this->list.erase(del);
        this->list.shrink_to_fit();
    }
};
