#include "ECEditorView.h"

ECEditorView :: ECEditorView(ECTextViewImp * impIn, ECTextDocumentCtrl& ctrlIn, std::string fileNameIn) : 
_imp(impIn), _ctrl(ctrlIn), _currPage(1), _cursIndex(-1), _fileName(fileNameIn), _searchMode(false), _replaceMode(false)
{}

void ECEditorView :: Attach(ECObserver * obs)
{
    _imp->Attach(obs);
}

void ECEditorView :: Notify()
{
    _imp->Notify();
}

void ECEditorView :: Show()
{
    _imp->Show();
}

void ECEditorView :: UpdateStatusRow(std::string left, std::string right)
{
    _imp->ClearStatusRows();
    _imp->AddStatusRow(left, right, true);
}

void ECEditorView :: AddRow(std::string rowIn)
{
    _imp->AddRow(rowIn);
}

int ECEditorView :: GetKeyPressed()
{
    return _imp->GetPressedKey();
}

int ECEditorView :: GetCursorX()
{
    return _imp->GetCursorX();
}

int ECEditorView :: GetCursorY()
{
    return _imp->GetCursorY();
}

void ECEditorView :: SetCursorX(int xVal)
{
    _imp->SetCursorX(xVal);
}

void ECEditorView :: SetCursorY(int yVal)
{
    _imp->SetCursorY(yVal);
}

int ECEditorView :: GetDocPosY()
{
    int offset = (_currPage - 1) * _imp->GetRowNumInView();
    return _imp->GetCursorY() + offset;
}

bool ECEditorView :: GetSearchMode()
{
    return _searchMode;
}

void ECEditorView :: SetSearchMode(bool mode)
{
    _searchMode = mode;
}

bool ECEditorView :: GetReplaceMode()
{
    return _replaceMode;
}

void ECEditorView :: SetReplaceMode(bool mode)
{
    _replaceMode = mode;
}

int ECEditorView :: GetCurrPage()
{
    return _currPage;
}

void ECEditorView :: SetCurrPage(int pageNum)
{
    _currPage = pageNum;
}

int ECEditorView :: GetNumRowInView()
{
    return _imp->GetRowNumInView();
}

int ECEditorView :: GetNumPages()
{
    int retVal = (_ctrl.GetNumRows() + _imp->GetRowNumInView() - 1) / _imp->GetRowNumInView();
    if (retVal == 0)
    {
        retVal ++;
    }
    return retVal;
}

void ECEditorView :: InitRows()
{
    _imp->InitRows();
}

void ECEditorView :: SetCurrSearch(std::string search)
{
    _currSearch = search;
}

std::string ECEditorView :: GetCurrSearch()
{
    return _currSearch;
}

void ECEditorView :: SetCurrReplace(std::string replace)
{
    _currReplace = replace;
}

std::string ECEditorView :: GetCurrReplace()
{
    return _currReplace;
}

void ECEditorView :: AddCursHist(std::tuple<int, int> cursIn)
{
    _cursorHist.push_back(cursIn);
    _cursIndex ++;
}

std::tuple<int, int> ECEditorView :: GetCursor(int index)
{
    return _cursorHist[index];
}

int ECEditorView :: GetCursIndex()
{
    return _cursIndex;
}

void ECEditorView :: SetCursIndex(int index)
{
    _cursIndex = index;
}

std::tuple<std::string, std::string> ECEditorView :: GetStatusRow()
{
    std::string str1 = _fileName;
    std:: string str2 = "Page ";
    str2 += std::to_string(_currPage);
    std::tuple<std::string, std::string> retTup = {str1, str2};
    return retTup;
}

void ECEditorView :: UnHighlight(int row, int colBegin, int colEnd, int clr)
{
    _imp->SetColor(row, colBegin, colEnd, TEXT_COLOR_WHITE);
}

void ECEditorView :: Highlight(int row, int colBegin, int colEnd, int clr)
{
    _imp->SetColor(row, colBegin, colEnd, TEXT_COLOR_RED);
}

void ECEditorView :: AllWhite()
{
    for (int i = 0; i < _ctrl.GetNumRows(); i++)
    {
        _imp->SetColor(i, 0, _ctrl.GetNumColsInRow(i) - 1, TEXT_COLOR_GREEN);
        _imp->SetColor(i, 0, _ctrl.GetNumColsInRow(i) - 1, TEXT_COLOR_WHITE);
    }
}

void ECEditorView :: FindAndUnHighlight(std::string currSearch)
{
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
        for (size_t index : occ[i])
        {
            UnHighlight(i, index, index + currSearch.length() - 1, 31);
        }
    }
}

void ECEditorView :: FindAndHighlight(std::string currSearch)
{
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
        for (size_t index : occ[i])
        {
            Highlight(i, index, index + currSearch.length() - 1, 31);
        }
    }
}