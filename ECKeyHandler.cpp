#include "ECKeyHandler.h"
#include "ECTextViewImp.h"
#include "ECTextDocument.h"
#include <fstream>
#include <iostream>


ECKeyHandler :: ECKeyHandler() {}

ECAlphaNumericHandler :: ECAlphaNumericHandler(ECTextDocumentCtrl& ctrlIn, ECEditorView * viewIn, ECKeyHandler * nextHandler)
    : _ctrl(ctrlIn), _view(viewIn), _nextHandler(nextHandler) {}

ECArrowHandler :: ECArrowHandler(ECTextDocumentCtrl& ctrlIn, ECEditorView * viewIn, ECKeyHandler * nextHandler)
    : _ctrl(ctrlIn), _view(viewIn), _nextHandler(nextHandler) {}

ECEnterHandler :: ECEnterHandler(ECTextDocumentCtrl& ctrlIn, ECEditorView * viewIn, ECKeyHandler * nextHandler)
    : _ctrl(ctrlIn), _view(viewIn), _nextHandler(nextHandler) {}

ECBackSpaceHandler :: ECBackSpaceHandler(ECTextDocumentCtrl& ctrlIn, ECEditorView * viewIn, ECKeyHandler * nextHandler)
    : _ctrl(ctrlIn), _view(viewIn), _nextHandler(nextHandler) {}

ECUndoRedoHandler :: ECUndoRedoHandler(ECTextDocumentCtrl& ctrlIn, ECEditorView * viewIn, ECKeyHandler * nextHandler)
    : _ctrl(ctrlIn), _view(viewIn), _nextHandler(nextHandler) {}

ECctrlFHandler :: ECctrlFHandler(ECTextDocumentCtrl& ctrlIn, ECEditorView * viewIn, ECKeyHandler * nextHandler)
    : _ctrl(ctrlIn), _view(viewIn), _nextHandler(nextHandler) {}

ECFindAlphaNumericHandler :: ECFindAlphaNumericHandler(ECTextDocumentCtrl& ctrlIn, ECEditorView * viewIn, ECKeyHandler * nextHandler)
    : _ctrl(ctrlIn), _view(viewIn), _nextHandler(nextHandler) {}

ECFindBackSlashHandler :: ECFindBackSlashHandler(ECTextDocumentCtrl& ctrlIn, ECEditorView * viewIn, ECKeyHandler * nextHandler)
    : _ctrl(ctrlIn), _view(viewIn), _nextHandler(nextHandler) {}

ECFindBackspaceHandler :: ECFindBackspaceHandler(ECTextDocumentCtrl& ctrlIn, ECEditorView * viewIn, ECKeyHandler * nextHandler)
    : _ctrl(ctrlIn), _view(viewIn), _nextHandler(nextHandler) {}

ECFindEnterHandler :: ECFindEnterHandler(ECTextDocumentCtrl& ctrlIn, ECEditorView * viewIn, ECKeyHandler * nextHandler)
    : _ctrl(ctrlIn), _view(viewIn), _nextHandler(nextHandler) {}

ECEscHandler :: ECEscHandler(ECTextDocumentCtrl& ctrlIn, ECEditorView * viewIn, ECKeyHandler * nextHandler)
    : _ctrl(ctrlIn), _view(viewIn), _nextHandler(nextHandler) {}

ECReplaceEnterHandler :: ECReplaceEnterHandler(ECTextDocumentCtrl& ctrlIn, ECEditorView * viewIn, ECKeyHandler * nextHandler)
    : _ctrl(ctrlIn), _view(viewIn), _nextHandler(nextHandler) {}

ECReplaceBackspaceHandler :: ECReplaceBackspaceHandler(ECTextDocumentCtrl& ctrlIn, ECEditorView * viewIn, ECKeyHandler * nextHandler)
    : _ctrl(ctrlIn), _view(viewIn), _nextHandler(nextHandler) {}

ECReplaceAlphaNumericHandler :: ECReplaceAlphaNumericHandler(ECTextDocumentCtrl& ctrlIn, ECEditorView * viewIn, ECKeyHandler * nextHandler)
    : _ctrl(ctrlIn), _view(viewIn), _nextHandler(nextHandler) {}

ECExitHandler :: ECExitHandler(ECTextDocumentCtrl& ctrlIn, ECEditorView * viewIn, ECFileHandler * fileHandIn, ECKeyHandler * nextHandler)
    : _ctrl(ctrlIn), _view(viewIn), _nextHandler(nextHandler), _fileHand(fileHandIn) {}


bool ECAlphaNumericHandler :: CanHandle(int key)
{
    return (32 <= key && key <= 126 && !_view->GetSearchMode() && !_view->GetReplaceMode());
}
void ECAlphaNumericHandler :: Handle(int key)
{
    int docPosY = _view->GetDocPosY();
    int cursorY = _view->GetCursorY();
    int cursorX = _view->GetCursorX();
    if (CanHandle(key))
    {
        char charToAdd = (char)key;
        std::vector<char> vecToAdd;
        vecToAdd.push_back(charToAdd);
        _ctrl.InsertTextAt(docPosY, cursorX, vecToAdd);
        _view->SetCursorX(cursorX + 1);
    }
    else if (_nextHandler != NULL)
    {
        _nextHandler->Handle(key);
    }
}

bool ECArrowHandler :: CanHandle(int key)
{
    return (1000 <= key && key <= 1003);
}
void ECArrowHandler :: Handle(int key)
{
    int docPosY = _view->GetDocPosY();
    int cursorY = _view->GetCursorY();
    int cursorX = _view->GetCursorX();
    if (CanHandle(key))
    {
        // Left Arrow Key
        if (key == 1000)
        {
            // Cursor at beginning of document, do nothing
            if (cursorX == 0 && docPosY == 0)
            {}
            // Cursor at beginning of any other row, move to end of previous row
            else if (cursorX == 0)
            {
                _view->SetCursorX(_ctrl.GetNumColsInRow(docPosY - 1));
                _view->SetCursorY(cursorY - 1);
            }
            // Otherwise, just move left
            else
            {
                _view->SetCursorX(cursorX - 1);
            }
        }
        // Right Arrow Key
        else if (key == 1001)
        {
            // Cursor at end of document, do nothing
            if (cursorX == _ctrl.GetNumColsInRow(docPosY) && docPosY == (_ctrl.GetNumRows() - 1))
            {}
            // Cursor at end of any other row, move to beginning of next row
            else if (cursorX == _ctrl.GetNumColsInRow(docPosY))
            {
                _view->SetCursorX(0);
                _view->SetCursorY(cursorY + 1);
            }
            else
            {
                _view->SetCursorX(cursorX + 1);
            }
        }
        // Up Arrow Key
        else if (key == 1002)
        {
            // Cursor at top row, do nothing
            if (docPosY == 0)
            {}
            // If row above is bigger or equal, just move up
            else if (cursorX <= _ctrl.GetNumColsInRow(docPosY - 1))
            {
                _view->SetCursorY(cursorY - 1);
            }
            // If row above is smaller, move cursor up and to the end of that row
            else if (cursorX > _ctrl.GetNumColsInRow(docPosY - 1))
            {
                _view->SetCursorX(_ctrl.GetNumColsInRow(docPosY - 1));
                _view->SetCursorY(cursorY - 1);
            }
        }
        // Down Arrow Key
        else if (key == 1003)
        {
            // Cursor at bottom row, do nothing
            if (docPosY == (_ctrl.GetNumRows() - 1))
            {}
            // If row below is bigger or equal, just move down
            else if (cursorX <= _ctrl.GetNumColsInRow(docPosY + 1))
            {
                _view->SetCursorY(cursorY + 1);
            }
            // If row below is smaller, move cursor down and to the end of that row 
            else if (cursorX > _ctrl.GetNumColsInRow(docPosY + 1))
            {
                _view->SetCursorX(_ctrl.GetNumColsInRow(docPosY + 1));
                _view->SetCursorY(cursorY + 1);
            }
        }
    }
    else if (_nextHandler != NULL)
    {
        _nextHandler->Handle(key);
    }
}

bool ECEnterHandler :: CanHandle(int key)
{
    return (key == 13 && !(_view->GetSearchMode()) && !(_view->GetReplaceMode()));
}
void ECEnterHandler :: Handle(int key)
{
    int docPosY = _view->GetDocPosY();
    int cursorY = _view->GetCursorY();
    int cursorX = _view->GetCursorX();
    if (CanHandle(key))
    {
        // Cursor at end of the row
        if (cursorX == _ctrl.GetNumColsInRow(docPosY))
        {
            _ctrl.InsertBlankRowAt(docPosY + 1);
        }
        // Cursor at beginning of row
        else if (cursorX == 0)
        {
            _ctrl.InsertBlankRowAt(cursorY);
        }
        // Cursor anywhere else
        else
        {
            // Save char at end of row
            std::vector<char> endOfRow;
            for (int i = cursorX; i < _ctrl.GetNumColsInRow(docPosY); i++)
            {
                endOfRow.push_back(_ctrl.GetChar(docPosY, i));
            }
            // Delete chars at end of row
            _ctrl.RemoveTextAt(docPosY, cursorX, endOfRow.size());
            // Add new row below current row with saved Chars
            _ctrl.InsertRowAt(docPosY + 1, endOfRow);
        }
        _view->SetCursorY(cursorY + 1);
        _view->SetCursorX(0);
    }
    else if (_nextHandler != NULL)
    {
        _nextHandler->Handle(key);
    }
}

bool ECBackSpaceHandler :: CanHandle(int key)
{
    return (key == 127 && !(_view->GetSearchMode()) && !(_view->GetReplaceMode()));
}
void ECBackSpaceHandler :: Handle(int key)
{
    int docPosY = _view->GetDocPosY();
    int cursorY = _view->GetCursorY();
    int cursorX = _view->GetCursorX();
    if (CanHandle(key))
    {
        // Cursor at begeinning of row
        if (cursorX == 0)
        {
            // Cursor at beginning of Document. Do nothing
            if (docPosY == 0)
            {
                return;
            }
            // If row is empty, we can simply delete the row and move cursor to the end of the previous row
            else if (_ctrl.GetNumColsInRow(docPosY) == 0)
            {
                _ctrl.RemoveRowAt(docPosY);
                _view->SetCursorY(cursorY - 1);
                _view->SetCursorX(_ctrl.GetNumColsInRow(docPosY - 1));
            }
            // Else, save the characters in the row into a vector to add to previous row
            else
            {
                std::vector<char> endOfRow;
                for (int i = 0; i < _ctrl.GetNumColsInRow(docPosY); i++)
                {
                    endOfRow.push_back(_ctrl.GetChar(docPosY, i));
                }
                _ctrl.RemoveRowAt(docPosY);
                _view->SetCursorX(_ctrl.GetNumColsInRow(docPosY - 1));
                _view->SetCursorY(cursorY - 1);
                // Here, make sure to not use cursorX, as it hasn't been updated
                _ctrl.InsertTextAt(docPosY - 1, _view->GetCursorX(), endOfRow);
            }
        }
        // Otherwise, just delete character at position
        else
        {
            _ctrl.RemoveTextAt(docPosY, cursorX - 1, 1);
            _view->SetCursorX(cursorX - 1);
        }
    }
    else if (_nextHandler != NULL)
    {
        _nextHandler->Handle(key);
    }
}


bool ECUndoRedoHandler :: CanHandle(int key)
{
    return ((key == 26 || key == 25) && !(_view->GetSearchMode()) && !(_view->GetReplaceMode()));
}

void ECUndoRedoHandler :: Handle(int key)
{
    if (CanHandle(key))
    {
        if (key == 26)
        {
            _ctrl.Undo();
            _view->SetCursorX(std::get<0>(_view->GetCursor(_view->GetCursIndex() - 1)));
            _view->SetCursorY(std::get<1>(_view->GetCursor(_view->GetCursIndex() - 1)));
            _view->SetCursIndex(_view->GetCursIndex() - 1);
        }
        if (key == 25)
        {
            _ctrl.Redo();
            _view->SetCursorX(std::get<0>(_view->GetCursor(_view->GetCursIndex() + 1)));
            _view->SetCursorY(std::get<1>(_view->GetCursor(_view->GetCursIndex() + 1)));
            _view->SetCursIndex(_view->GetCursIndex() + 1);
        }
    }
    else if (_nextHandler != NULL)
    {
        _nextHandler->Handle(key);
    }
}

bool ECctrlFHandler :: CanHandle(int key)
{
    return (key == 6 && !(_view->GetSearchMode()));
}

void ECctrlFHandler :: Handle(int key)
{
    if (CanHandle(key))
    {
        _view->SetSearchMode(true);
        _view->SetReplaceMode(false);
        _view->UpdateStatusRow(_view->GetCurrSearch(), "Find");
    }
    else if (_nextHandler != NULL)
    {
        _nextHandler->Handle(key);
    }
}

bool ECFindAlphaNumericHandler :: CanHandle(int key)
{
    return (32 <= key && key <= 126 && key != 47 && (_view->GetSearchMode()));
}
void ECFindAlphaNumericHandler :: Handle(int key)
{
    if (CanHandle(key))
    {
        char charToAdd = (char)key;
        std::string updated = _view->GetCurrSearch();
        updated.push_back(charToAdd);
        _view->SetCurrSearch(updated);
        _view->UpdateStatusRow(updated, "Search");
    }
    else if (_nextHandler != NULL)
    {
        _nextHandler->Handle(key);
    }
}

bool ECFindBackSlashHandler :: CanHandle(int key)
{
    return (key == 47 && _view->GetSearchMode());
}
void ECFindBackSlashHandler :: Handle(int key)
{
    if (CanHandle(key))
    {
        _view->SetReplaceMode(true);
        _view->SetSearchMode(false);
        _view->UpdateStatusRow(_view->GetCurrReplace(), "Replace");
    }
    else if (_nextHandler != NULL)
    {
        _nextHandler->Handle(key);
    }
}

bool ECFindBackspaceHandler :: CanHandle(int key)
{
    return (key == 127 && (_view->GetSearchMode()));
}
void ECFindBackspaceHandler :: Handle(int key)
{
    if (CanHandle(key))
    {
        if (_view->GetCurrSearch().length() > 0)
        {
            std::string search = _view->GetCurrSearch();
            search.pop_back();
            _view->SetCurrSearch(search);
            _view->UpdateStatusRow(search, "Search");
        }
    }
    else if (_nextHandler != NULL)
    {
        _nextHandler->Handle(key);
    }
}
bool ECFindEnterHandler :: CanHandle(int key)
{
    return (key == 13 && (_view->GetSearchMode()));
}
void ECFindEnterHandler :: Handle(int key)
{
    if (CanHandle(key))
    {
        std::string currSearch = _view->GetCurrSearch();
        _view->FindAndHighlight(currSearch);
    }
    else if (_nextHandler != NULL)
    {
        _nextHandler->Handle(key);
    }
}

bool ECEscHandler :: CanHandle(int key)
{
    return (key == 27);
}
void ECEscHandler :: Handle(int key)
{
    if (CanHandle(key))
    {
        if (_view->GetSearchMode())
        {
            _view->SetSearchMode(false);
            _view->FindAndUnHighlight(_view->GetCurrSearch());
            _view->SetCurrSearch("");
            _view->SetCurrReplace("");
        }
        else if (_view->GetReplaceMode())
        {
            _view->SetReplaceMode(false);
            _view->SetSearchMode(true);
            _view->UpdateStatusRow(_view->GetCurrSearch(), "Find");
        }
    }
    else if (_nextHandler != NULL)
    {
        _nextHandler->Handle(key);
    }
}

bool ECReplaceBackspaceHandler :: CanHandle(int key)
{
    return (key == 127 && (_view->GetReplaceMode()));
}
void ECReplaceBackspaceHandler :: Handle(int key)
{
    if (CanHandle(key))
    {
        if (_view->GetCurrReplace().length() > 0)
        {
            std::string replace = _view->GetCurrReplace();
            replace.pop_back();
            _view->SetCurrReplace(replace);
            _view->UpdateStatusRow(replace, "Replace");
        }
    }
    else if (_nextHandler != NULL)
    {
        _nextHandler->Handle(key);
    }
}

bool ECReplaceAlphaNumericHandler :: CanHandle(int key)
{
    return (32 <= key && key <= 126 && (_view->GetReplaceMode()));
}
void ECReplaceAlphaNumericHandler :: Handle(int key)
{
    if (CanHandle(key))
    {
        char charToAdd = (char)key;
        std::string updated = _view->GetCurrReplace();
        updated.push_back(charToAdd);
        _view->SetCurrReplace(updated);
        _view->UpdateStatusRow(updated, "Replace");
    }
    else if (_nextHandler != NULL)
    {
        _nextHandler->Handle(key);
    }
}

bool ECReplaceEnterHandler :: CanHandle(int key)
{
    return (key == 13 && _view->GetReplaceMode());
}

void ECReplaceEnterHandler :: Handle(int key)
{
    if (CanHandle(key))
    {
        // Get The current search, and current replace
        std::string currSearch = _view->GetCurrSearch();
        _view->FindAndUnHighlight(currSearch);
        std::string currReplace = _view->GetCurrReplace();
        std::vector<char> replace;
        for (char c : currReplace)
        {
            replace.push_back(c);
        }
        // Get difference in size
        int dif = currSearch.size() - replace.size();
        // Keep a vector of vector off occurances, every "row" in the vector 
        // contains the columns of the occurances of the first letter of the search
        std::vector<std::vector<size_t>> occ;
        for (int i = 0; i < _ctrl.GetNumRows(); i++)
        {
            std::vector<size_t> rowOcc;
            std::string currRow = _ctrl.RowToStr(i);
            size_t pos = currRow.find(currSearch, 0);
            while(pos != std::string::npos)
            {
                rowOcc.push_back(pos);
                pos = currRow.find(currSearch, pos+1);
            }
            occ.push_back(rowOcc);
        }
        
        for (int i = 0; i < occ.size(); i++)
        {
            for (int j = 0; j < occ[i].size(); j++)
            {
                _ctrl.RemoveTextAt(i, (occ[i][j] - (dif * j)), currSearch.length());
                _ctrl.InsertTextAt(i, (occ[i][j] - (dif * j)), replace);
            }
        }
        _view->FindAndHighlight(currReplace);
        _view->SetReplaceMode(false);
        _view->SetSearchMode(true);
        _view->SetCurrSearch(currReplace);
    }
    else if (_nextHandler != NULL)
    {
        _nextHandler->Handle(key);
    }
}

bool ECExitHandler :: CanHandle(int key)
{
    return (key == 17);
}

void ECExitHandler :: Handle(int key)
{
    if (CanHandle(key))
    {
        _fileHand->UpdateFile();
    }
    else if (_nextHandler != NULL)
    {
        _nextHandler->Handle(key);
    }
}