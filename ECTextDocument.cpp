#include "ECTextDocument.h"
#include <iostream>
#include <cctype>
#include <fstream>

using namespace std;

class ECCommandHistory;
class ECCommand;
// **********************************************************
// Controller for text document

ECTextDocumentCtrl :: ECTextDocumentCtrl(ECTextDocument &docIn) : _doc(docIn)
{
    _histCmds = new ECCommandHistory;
}

ECTextDocumentCtrl :: ~ECTextDocumentCtrl()
{
}

void ECTextDocumentCtrl :: InsertTextAt(int posRow, int posCol, const std::vector<char> &listCharsToIns)
{
    InsertTextAtCmd * ins = new InsertTextAtCmd(_doc, posRow, posCol, listCharsToIns);
    _histCmds->ExecuteCmd(ins);
    ins->Execute();
}

void ECTextDocumentCtrl :: RemoveTextAt(int posRow, int posCol, int lenToRemove)
{
    RemoveTextAtCmd* del = new RemoveTextAtCmd(_doc, posRow, posCol, lenToRemove);
    _histCmds->ExecuteCmd(del);
    del->Execute();
}
void ECTextDocumentCtrl :: CapTextAt(int posRow, int posCol, int lenToCap)
{
    CapTextAtCmd* cap = new CapTextAtCmd(_doc, posRow, posCol, lenToCap);
    _histCmds->ExecuteCmd(cap);
    cap->Execute();
}

void ECTextDocumentCtrl :: LowerTextAt(int posRow, int posCol, int lenToLower)
{
    LowerTextAtCmd* low = new LowerTextAtCmd(_doc, posRow, posCol, lenToLower);
    _histCmds->ExecuteCmd(low);
    low->Execute();
}

void ECTextDocumentCtrl :: RemoveRowAt(int posRow)
{
    RemoveRowCmd * rem = new RemoveRowCmd(_doc, posRow);
    _histCmds->ExecuteCmd(rem);
    rem->Execute();
}

void ECTextDocumentCtrl :: InsertBlankRowAt(int posRow)
{
    InsertBlankRowCmd * ins = new InsertBlankRowCmd(_doc, posRow);
    _histCmds->ExecuteCmd(ins);
    ins->Execute();
}

void ECTextDocumentCtrl :: InsertRowAt(int posRow, std::vector<char> rowToAdd)
{
    InsertRowCmd * ins = new InsertRowCmd(_doc, posRow, rowToAdd);
    _histCmds->ExecuteCmd(ins);
    ins->Execute();
}

void ECTextDocumentCtrl :: Undo()
{
    _histCmds->Undo();
}

void ECTextDocumentCtrl :: Redo()
{
    _histCmds->Redo();
}

char ECTextDocumentCtrl :: GetChar(int posRow, int posCol)
{
    return _doc.GetCharAt(posRow, posCol);
}

int ECTextDocumentCtrl :: GetNumRows()
{
    return _doc.GetNumRows();
}

int ECTextDocumentCtrl :: GetNumColsInRow(int posRow)
{
    return _doc.GetNumColsInRow(posRow);
}

std::string ECTextDocumentCtrl :: RowToStr(int posRow)
{
    std::string retStr;
    for (int i = 0; i < GetNumColsInRow(posRow); i++)
    {
        retStr.push_back(GetChar(posRow, i));
    }
    return retStr;
}

// **********************************************************
// Document for text document


ECTextDocumentCtrl & ECTextDocument :: GetCtrl()
{
    return _docCtrl;
}

ECTextDocument :: ECTextDocument() : _docCtrl(*this)
{
    // Start with one blank row
    std::vector<char> arr;
    _gridChars.push_back(arr);
}

ECTextDocument :: ~ECTextDocument()
{
}

char ECTextDocument :: GetCharAt(int posRow, int posCol) const
{
    return _gridChars[posRow][posCol];
}

std::vector<char> ECTextDocument :: GetRowAt(int posRow)
{
    return _gridChars[posRow];
}

void ECTextDocument :: InsertCharAt(int posRow, int posCol, char ch)
{
    // Trying to insert further than end of row, or before beginning of row
    if (posCol > _gridChars[posRow].size() || posCol < 0)
    {
        return;
    }
    // Trying to insert into row that doesn't exist
    if (posRow >= _gridChars.size() || posRow < 0)
    {
        return;
    }
    // Insertion at the end of row, can just pushback
    else if (posCol == _gridChars[posRow].size())
    {
        _gridChars[posRow].push_back(ch);
    }
    // Insertion anywhere else
    else
    {
        // Create temp array for characters after pos
        vector<char> temp;
        for (int i = posCol; i < _gridChars[posRow].size(); i++)
        {
            temp.push_back(_gridChars[posRow][i]);
        }
        // Insert ch at pos
        _gridChars[posRow][posCol] = ch;
        // Add temp to end
        int tempIndex = 0;
        for (int i = posCol + 1; i < _gridChars[posRow].size(); i++)
        {
            _gridChars[posRow][i] = temp[tempIndex];
            tempIndex += 1;
        }
        _gridChars[posRow].push_back(temp[tempIndex]);
    }

}
void ECTextDocument :: RemoveCharAt(int posRow, int posCol)
{
    // Trying to remove char that doesnt exist in row
    if (posCol >= _gridChars[posRow].size() || posCol < 0)
    {
        return;
    }
    // Trying to remove char in row that doesnt exist
    if (posRow > _gridChars.size())
    {
        return;
    }
    // Remove Last element in row
    else if (posCol == _gridChars[posRow].size() - 1)
    {
        _gridChars[posRow].pop_back();
    }
    // Remove anywhere else
    else
    {
        // Create temp array for characters after pos
        vector<char> temp;
        for (int i = posCol + 1; i < _gridChars[posRow].size(); i++)
        {
            temp.push_back(_gridChars[posRow][i]);
        }
        // Remove last element from list
        _gridChars[posRow].pop_back();
        // Add temp to end
        int tempIndex = 0;
        for (int i = posCol; i < _gridChars[posRow].size(); i++)
        {
            _gridChars[posRow][i] = temp[tempIndex];
            tempIndex += 1;
        }
    }
}

void ECTextDocument :: CapCharAt(int posRow, int posCol)
{
    // Trying to capitalize character out of bounds
    if (posCol > _gridChars[posRow].size() - 1 || posCol < 0)
    {
        return;
    }
    // Capitalize anywhere else
    else
    {
        if (islower(_gridChars[posRow][posCol]))
        {
            _gridChars[posRow][posCol] = toupper(_gridChars[posRow][posCol]);
        }
        else
        {
            return;
        }
    }
}

void ECTextDocument :: LowerCharAt(int posRow, int posCol)
{
    // Trying to lowercase character out of bounds
    if (posCol > _gridChars[posRow].size() - 1 || posCol < 0)
    {
        return;
    }
    // Lowercase anywhere else
    else
    {
        if (isupper(_gridChars[posRow][posCol]))
        {
            _gridChars[posRow][posCol] = tolower(_gridChars[posRow][posCol]);
        }
        else
        {
            return;
        }
    }
}

void ECTextDocument :: InsertRow(int posRow, std::vector<char> rowToIns)
{
    // Inserting row at inaccessable location
    if (posRow > _gridChars.size() || posRow < 0)
    {
        return;
    }
    // Inserting at end of Doc.  Can just pushback
    else if (_gridChars.size() == posRow)
    {
        _gridChars.push_back(rowToIns);
    }
    // Inserting anywhere else
    else
    {
        // Create temp array for vectors after posRow
        vector<vector<char>> temp;
        for (int i = posRow; i < _gridChars.size(); i++)
        {
            temp.push_back(_gridChars[i]);
        }
        // Insert blank row at posRow
        _gridChars[posRow] = rowToIns;
        // Add temp to end
        int tempIndex = 0;
        for (int i = posRow + 1; i < _gridChars.size(); i++)
        {
            _gridChars[i] = temp[tempIndex];
            tempIndex += 1;
        }
        _gridChars.push_back(temp[tempIndex]);
    }
}

void ECTextDocument :: InsertBlankRow(int posRow)
{
    std::vector<char> blankRow;
    // Inserting row at inaccessable location
    if (posRow > _gridChars.size() || posRow < 0)
    {
        return;
    }
    // Inserting at end of Doc.  Can just pushback
    else if (_gridChars.size() == posRow)
    {
        _gridChars.push_back(blankRow);
    }
    // Inserting anywhere else
    else
    {
        // Create temp array for vectors after posRow
        vector<vector<char>> temp;
        for (int i = posRow; i < _gridChars.size(); i++)
        {
            temp.push_back(_gridChars[i]);
        }
        // Insert blank row at posRow
        _gridChars[posRow] = blankRow;
        // Add temp to end
        int tempIndex = 0;
        for (int i = posRow + 1; i < _gridChars.size(); i++)
        {
            _gridChars[i] = temp[tempIndex];
            tempIndex += 1;
        }
        _gridChars.push_back(temp[tempIndex]);
    }
}

void ECTextDocument :: RemoveRow(int posRow)
{
    // Trying to remove row that doesnt exist
    if (posRow >= _gridChars.size() || posRow < 0)
    {
        return;
    }
    // Remove Last row
    else if (posRow == _gridChars.size() - 1)
    {
        _gridChars.pop_back();
    }
    // Remove anywhere else
    else
    {
        // Create temp array for vectors after pos
        vector<vector<char>> temp;
        for (int i = posRow + 1; i < _gridChars.size(); i++)
        {
            temp.push_back(_gridChars[i]);
        }
        // Remove last row from list
        _gridChars.pop_back();
        // Add temp to end
        int tempIndex = 0;
        for (int i = posRow; i < _gridChars.size(); i++)
        {
            _gridChars[i] = temp[tempIndex];
            tempIndex += 1;
        }
    }
}

void ECTextDocument :: Display() const
{
    for (std::vector<char> v : _gridChars)
    {
        for (char c : v)
        {
            cout << c;
        }
        cout << endl;
    }
}
