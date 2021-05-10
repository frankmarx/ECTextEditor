#ifndef ECEDITOR_VIEW_H
#define ECEDITOR_VIEW_H

#include "ECTextViewImp.h"
#include "ECObserver.h"

class ECObserver;
class ECTextViewImp;

class ECEditorView 
{
public:
    ECEditorView(ECTextViewImp * impIn, ECTextDocumentCtrl& ctrlIn, std::string fileName);
    void Attach(ECObserver * obs);
    void Notify();
    void Show();
    void AddRow(std::string rowIn);
    void InitRows();
    void UpdateStatusRow(std::string left, std::string right);
    int GetKeyPressed();
    int GetCursorX();
    int GetCursorY();
    void SetCursorX(int xVal);
    void SetCursorY(int yVal);
    int GetDocPosY();
    bool GetSearchMode();
    void SetSearchMode(bool mode);
    bool GetReplaceMode();
    void SetReplaceMode(bool mode);
    int GetCurrPage();
    void SetCurrPage(int pageNum);
    int GetNumRowInView();
    int GetNumPages();
    std::string GetCurrSearch();
    void SetCurrSearch(std::string search);
    std::string GetCurrReplace();
    void SetCurrReplace(std::string replace);
    void AddCursHist(std::tuple<int, int> cursIn);
    std::tuple<int, int> GetCursor(int index);
    int GetCursIndex();
    void SetCursIndex(int index);
    std::tuple<std::string, std::string> GetStatusRow();
    void Highlight(int row, int colBegin, int colEnd, int clr);
    void UnHighlight(int row, int colBegin, int colEnd, int clr);
    void AllWhite();
    void FindAndHighlight(std::string search);
    void FindAndUnHighlight(std::string search);
private:
    ECTextViewImp * _imp;
    ECTextDocumentCtrl& _ctrl;
    int _currPage;
    int _cursIndex;
    bool _searchMode;
    bool _replaceMode;
    std::string _fileName;
    std::string _currSearch;
    std::string _currReplace;
    std::vector<std::tuple<int, int>> _cursorHist;
};

#endif