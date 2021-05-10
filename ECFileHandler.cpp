#include "ECFileHandler.h"
#include <iostream>
#include <cctype>
#include <fstream>

using namespace std;

ECFileHandler :: ECFileHandler(std::string fileName, ECTextDocumentCtrl& ctrlIn) 
    : _fileName(fileName), _ctrl(ctrlIn) 
{
    // Load file
    ifstream fileIn;
    fileIn.open(_fileName, ios::in);
    if (fileIn)
    {
        int row = 0;
        std::string line;
        std::vector<std::vector<char>> docGrid;
        // Populate doc with file's contents
        while (std::getline(fileIn, line))
        {
            if (line == "")
            {
                std::vector<char> empty;
                docGrid.push_back(empty);
            }
            else
            {
                std::vector<char> lineVec(line.begin(), line.end());
                docGrid.push_back(lineVec);
            }
        }
        fileIn.close();
        for (std::vector<char> rowChar : docGrid)
        {
            if (rowChar.size() == 0)
            {
                _ctrl.InsertBlankRowAt(row);
            }
            else
            {
                _ctrl.InsertRowAt(row, rowChar);
            }
            row ++;
        }
        if (docGrid.size() == 0)
        {
            _ctrl.InsertBlankRowAt(row);
        }
        _ctrl.RemoveRowAt(_ctrl.GetNumRows() - 1);
    }
    else
    {
        ofstream newFile(_fileName);
        newFile.close();
    }
}

void ECFileHandler :: UpdateFile()
{
    // Load File
    ofstream fileIn;
    fileIn.open(_fileName, ios::out | ios::trunc);
    for (int i = 0; i < _ctrl.GetNumRows(); i++)
    {
        std::string line = "";
        for (int j = 0; j < _ctrl.GetNumColsInRow(i); j++)
        {
            line += _ctrl.GetChar(i, j);
        }
        fileIn << line << '\n';
    }
    fileIn.close();
}

string ECFileHandler :: GetName()
{
    return _fileName;
}