#include <iostream>
#include <fstream>
#include "Entry.cc"

using namespace std;
class VolumeInfo
{
private:
    static uint32_t const defaultSign;
    uint32_t Signature;
    uint32_t SizeEntryTable;
    uint64_t OffsetEntryTable;

public:
    VolumeInfo()
    {
        this->Signature = defaultSign;
        this->SizeEntryTable = 0;
        this->OffsetEntryTable = 0;
    }

    ~VolumeInfo() {}

    bool isEmpty() const
    {
        return this->SizeEntryTable == 0;
    }

    uint64_t getEntryOffset() const
    {
        return this->OffsetEntryTable;
    }

    void write(fstream &f) const
    {
        f.write((char *)&this->Signature, sizeof(this->Signature));
        f.write((char *)&this->SizeEntryTable, sizeof(this->SizeEntryTable));
        f.write((char *)&this->OffsetEntryTable, sizeof(this->OffsetEntryTable));
    }

    void read(fstream &f) const
    {
        f.read((char *)&this->Signature, sizeof(this->Signature));
        f.read((char *)&this->SizeEntryTable, sizeof(this->SizeEntryTable));
        f.read((char *)&this->OffsetEntryTable, sizeof(this->OffsetEntryTable));
    }

    bool checkSign(fstream &f) const
    {
        return this->Signature == this->defaultSign;
    }

    void seekToHead_g(fstream &f) const
    {
        f.seekg(this->OffsetEntryTable);
    }

    void seekToHead_p(fstream &f) const
    {
        f.seekp(this->OffsetEntryTable);
    }

    bool isEnd(fstream &f) const
    {
        return f.tellg() == (this->OffsetEntryTable + this->SizeEntryTable);
    }

    void updateAfterDelete(Entry const *entry)
    {
        this->SizeEntryTable -= entry->getSize();
        this->OffsetEntryTable -= entry->getSizeData();
    }

    void updateAfterSetPassWord(size_t const &oldLen, size_t const &newLen)
    {
        this->SizeEntryTable += (newLen - oldLen);
    }

    void updateOffset(uint64_t const &newOffset)
    {
        this->OffsetEntryTable = newOffset;
    }

    void updateSize(uint64_t const &newTailPos)
    {
        this->SizeEntryTable = newTailPos - this->OffsetEntryTable;
    }
};