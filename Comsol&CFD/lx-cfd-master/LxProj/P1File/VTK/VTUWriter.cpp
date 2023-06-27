#include "VTUWriter.h"
#include <sstream>
#include <iostream>
#include "AppRes.h"
#include "EnumsToString.h"
#include "VtuCell.h"

namespace LxCFD
{
    bool VTUWriter::WriteFile(const std::string &filePath)
    {
        if (!StartWriter(filePath))
            return false;
        WriteVTUFile();
        LxConsole::Info("文件已保存至" + filePath);
        return true;
    }
    void VTUWriter::WriteVTUFile()
    {
        WriteXmlHead("<VTKFile type=\"UnstructuredGrid\" version=\"0.1\" byte_order=\"LittleEndian\">");
        {
            WriteXmlHead("<UnstructuredGrid>");
            for (auto &z : AppRes::FvMesh->Zones)
            {
                std::stringstream ss;
                ss << "<Piece NumberOfPoints=\"" << z->Nodes->size() << "\" NumberOfCells=\"" << z->Cells.size() << "\">";
                WriteXmlHead(ss.str());
                {
                    WritePoints(*z);
                    WriteCells(*z);
                    WriteCellData(*z);
                }
                WriteXmlEnd("</Piece>");
            }
            WriteXmlEnd("</UnstructuredGrid>");
        }
        WriteXmlEnd("</VTKFile>");
    }
    void VTUWriter::WritePoints(const FvZone &z)
    {
        WriteXmlHead("<Points>");
        {
            WriteXmlHead("<DataArray type=\"Float32\" NumberOfComponents=\"3\" format=\"ascii\">");
            auto &nodes = z.Nodes;
            for (int i1 = 0; i1 < (int)nodes->size(); ++i1)
            {
                WriteSpaceEnter(i1, 3);
                auto &node = nodes->at(i1);
                Writer << (float)node.X << " " << (float)node.Y << " " << (float)node.Z << " ";
            }
            Writer << std::endl;
            WriteXmlEnd("</DataArray>");
        }
        WriteXmlEnd("</Points>");
    }
    void VTUWriter::WriteCells(const FvZone &z)
    {
        WriteXmlHead("<Cells>");
        {
            std::vector<VtuCell> cells(z.Cells.size()); // = new VtuCell[z.Cells.Length];
            ShortArray::Deep store;
            store.Initialize(1,cells.size());
            {
                int offset = 0;
                int i1 = 0;
                for (; i1 <= z.InnerIndex.CellIDs.End; ++i1)
                {
                    if (!cells.at(i1).AddCellInf_inner(z.Cells.at(i1), z.Faces, store, offset))
                    {
                        LxConsole::Error("输出Cell时出错，无法识别的网格类型");
                    }
                }
                for (; i1 < (int)cells.size(); ++i1)
                {
                    if (!cells.at(i1).AddCellInf_bound(z.Cells.at(i1), z.Faces, store, offset))
                    {
                        LxConsole::Error("输出Cell时出错，无法识别的网格类型");
                    }
                }
            }
            WriteXmlHead("<DataArray type=\"Int32\" Name=\"connectivity\" format=\"ascii\">");
            {
                for (int i1 = 0; i1 < (int)cells.size(); ++i1)
                {
                    WriteSpaceEnter(i1, 3);
                    for (auto &ite : cells.at(i1).Connect)
                    {
                        Writer << ite << " ";
                    }
                }
                Writer << std::endl;
            }
            WriteXmlEnd("</DataArray>");
            WriteXmlHead("<DataArray type=\"Int32\" Name=\"offsets\" format=\"ascii\">");
            {
                for (int i1 = 0; i1 < (int)cells.size(); ++i1)
                {
                    WriteSpaceEnter(i1, 10);
                    Writer << cells.at(i1).OffSet << " ";
                }
                Writer << std::endl;
            }
            WriteXmlEnd("</DataArray>");
            WriteXmlHead("<DataArray type=\"UInt8\" Name=\"types\" format=\"ascii\">");
            {
                for (int i1 = 0; i1 < (int)cells.size(); ++i1)
                {
                    WriteSpaceEnter(i1, 15);
                    Writer << cells.at(i1).Type << " ";
                }
                Writer << std::endl;
            }
            WriteXmlEnd("</DataArray>");
        }
        WriteXmlEnd("</Cells>");
    }
    void VTUWriter::WriteCellData(const FvZone &z)
    {
        if (ExportScalars.size() == 0)
            return;
        WriteXmlHead("<CellData>");
        {
            for (auto &scalartype : ExportScalars)
            {
                if (scalartype == ScalarTypes::Velocity)
                {
                    auto *uarray = z.CFDFields.GetArray(ScalarTypes::Vel_U);
                    auto *varray = z.CFDFields.GetArray(ScalarTypes::Vel_V);
                    auto *warray = z.CFDFields.GetArray(ScalarTypes::Vel_W);
                    if (uarray == nullptr || varray == nullptr || warray == nullptr)
                        continue;
                    WriteXmlHead("<DataArray type=\"Float32\" Name=\"Velocity\" NumberOfComponents=\"3\" format=\"ascii\">");
                    {
                        for (std::size_t i1 = 0; i1 < z.Cells.size(); ++i1)
                        {
                            WriteSpaceEnter(i1, 3);
                            std::stringstream ss;
                            ss << (float)uarray->at(i1) << " " << (float)varray->at(i1) << " " << (float)warray->at(i1) << " ";
                            Writer << ss.str();
                        }
                        Writer << std::endl;
                    }
                    WriteXmlEnd("</DataArray>");
                }
                else
                {
                    auto *array = z.CFDFields.GetArray(scalartype);
                    if (array == nullptr)
                        continue;
                    EnumsToString enumtostring;
                    std::stringstream ss;
                    ss << "<DataArray type=\"Float32\" Name=\"" << enumtostring.ConvertToString(scalartype) << "\" format=\"ascii\">";
                    WriteXmlHead(ss.str());
                    {
                        for (std::size_t i1 = 0; i1 < z.Cells.size(); i1++)
                        {
                            WriteSpaceEnter(i1, 5);
                            Writer << (float)array->at(i1) << " ";
                        }
                        Writer << std::endl;
                    }
                    WriteXmlEnd("</DataArray>");
                }
            }
        }
        WriteXmlEnd("</CellData>");
    }

}