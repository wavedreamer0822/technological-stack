#include "ExcuteSaveFile.h"
#include "VTUWriter.h"
namespace LxCFD
{
    void ExcuteSaveFile::Excute()
    {
        VTUWriter vtu;
        vtu.ExportScalars = ExportScalars;
        vtu.WriteFile(FilePath);
    }
}