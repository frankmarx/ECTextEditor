#include "ECCommand.h"
#include <iostream>
#include <algorithm>


// ******************************************************
// Insert Text Command
InsertTextAtCmd::InsertTextAtCmd(ECTextDocument& docIn, int posRow, int posCol, const std::vector<char>& listChars) :
    _doc(docIn), _posCol(posCol), _posRow(posRow), _chartoadd(listChars)
{}

void InsertTextAtCmd::Execute()
{
    for (int i = 0; i < _chartoadd.size(); i++)
    {
        _doc.InsertCharAt(_posRow, _posCol + i, _chartoadd[i]);
    }
}

void InsertTextAtCmd::UnExecute()
{
    for (int i = 0; i < _chartoadd.size(); i++)
    {
        _doc.RemoveCharAt(_posRow, _posCol);
    }
}


// Remove Text Command

RemoveTextAtCmd::RemoveTextAtCmd(ECTextDocument& docIn, int posRow, int posCol, int len) :
    _doc(docIn), _posCol(posCol), _posRow(posRow), _lentext(len)
{}

void RemoveTextAtCmd::Execute()
{
    for (int i = 0; i < _lentext; i++)
    {
        _charsRemoved.push_back(_doc.GetCharAt(_posRow, _posCol));
        _doc.RemoveCharAt(_posRow, _posCol);
    }
}

void RemoveTextAtCmd::UnExecute()
{
    for (int i = 0; i < _lentext; i++)
    {
        _doc.InsertCharAt(_posRow, _posCol + i, _charsRemoved[i]);
    }
}


// Capitalize Text Command

CapTextAtCmd::CapTextAtCmd(ECTextDocument& docIn, int posRow, int posCol, int len) :
    _doc(docIn), _posCol(posCol), _posRow(posRow), _lentext(len)
{}

void CapTextAtCmd::Execute()
{
    for (int i = 0; i < _lentext; i++)
    {
        // If lowercase make upper
        if (islower(_doc.GetCharAt(_posRow, _posCol + i)))
        {
			_doc.CapCharAt(_posRow, _posCol + i);
        }
        // Else, uneffected, keep track
        else
        {
            _notChanged.push_back(_posCol + i);
        }
    }
}

void CapTextAtCmd::UnExecute()
{
    for (int i = 0; i < _lentext; i++)
    {
        // If index was changed, change back
        if (!(std::find(_notChanged.begin(), _notChanged.end(), _posCol + 1) != _notChanged.end()))
        {
			_doc.LowerCharAt(_posRow, _posCol + i);
        }
        else
        {
            remove(_notChanged.begin(), _notChanged.end(), _posCol + 1);
        }

    }
}


// Lower Text Command

LowerTextAtCmd::LowerTextAtCmd(ECTextDocument& docIn, int posRow, int posCol, int len) :
    _doc(docIn), _posCol(posCol), _posRow(posRow), _lentext(len)
{}

void LowerTextAtCmd::Execute()
{
    for (int i = 0; i < _lentext; i++)
    {
        // If uppercase make lower
        if (isupper(_doc.GetCharAt(_posRow, _posCol + i)))
        {
			_doc.LowerCharAt(_posRow, _posCol + i);
        }
        // Else, uneffected, keep track
        else
        {
            _notChanged.push_back(_posCol + i);
        }
    }
}

void LowerTextAtCmd::UnExecute()
{
    for (int i = 0; i < _lentext; i++)
    {
        // If index was changed, change back
        if (!(std::find(_notChanged.begin(), _notChanged.end(), _posCol + 1) != _notChanged.end()))
        {
			_doc.CapCharAt(_posRow, _posCol + i);
        }
        else
        {
            remove(_notChanged.begin(), _notChanged.end(), _posCol + 1);
        }
    }
}

// Insert Blank Row Command

InsertBlankRowCmd::InsertBlankRowCmd(ECTextDocument& docIn, int posRow) : 
    _doc(docIn), _posRow(posRow)
{}

void InsertBlankRowCmd::Execute()
{
    _doc.InsertBlankRow(_posRow);
}

void InsertBlankRowCmd::UnExecute()
{
    _doc.RemoveRow(_posRow);
}

// Insert Row Command
InsertRowCmd::InsertRowCmd(ECTextDocument& docIn, int posRow, std::vector<char> rowToIns) : 
    _doc(docIn), _posRow(posRow), _rowToAdd(rowToIns)
{}

void InsertRowCmd::Execute()
{
    _doc.InsertRow(_posRow, _rowToAdd);
}

void InsertRowCmd::UnExecute()
{
    _doc.RemoveRow(_posRow);
}

// Remove Row Command
RemoveRowCmd::RemoveRowCmd(ECTextDocument& docIn, int posRow) : 
    _doc(docIn), _posRow(posRow)
{}

void RemoveRowCmd::Execute()
{
    _rowRemoved = _doc.GetRowAt(_posRow);
    _doc.RemoveRow(_posRow);
}

void RemoveRowCmd::UnExecute()
{
    _doc.InsertRow(_posRow, _rowRemoved);
}

// Implement command history
ECCommandHistory :: ECCommandHistory() : _index(-1), _histsize(0)
{
}

ECCommandHistory :: ~ECCommandHistory()
{
}

int ECCommandHistory :: GetHistorySize()
{
    return _cmdVector.size();
}

bool ECCommandHistory :: Undo()
{
    if (_index >= 0)
    {
		_cmdVector[_index]->UnExecute();
        _index -= 1;
        return true;
    }
    else
    {
        return false;
    }
}
bool ECCommandHistory :: Redo()
{
    if (_index + 1 < _histsize)
    {
        _cmdVector[_index + 1]->Execute();
        _index += 1;
        return true;
    }
    else
    {
        return false;
    }

}
void ECCommandHistory :: ExecuteCmd(ECCommand * pCmd)
{
    _cmdVector.push_back(pCmd);
    _index++;
    _histsize++; 
}

