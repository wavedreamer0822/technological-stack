#pragma once
#include "IWriteFile.h"
#include "XMLWriter.h"
#include "FvZone.h"
namespace LxCFD
{
    class VTUWriter : public XMLWriter, public IWriteFile
    {
    public:
        std::vector<ScalarTypes> ExportScalars;
        virtual bool WriteFile(const std::string &filePath) override;
        void WriteVTUFile();
        void WritePoints(const FvZone &z);
        void WriteCells(const FvZone &z);
        void WriteCellData(const FvZone &z);
    };
}