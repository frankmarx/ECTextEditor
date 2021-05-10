#include <vector>
#include <string>
#include <iostream>
#include "ECTextDocument.h"
#include "ECTextViewImp.h"
#include "ECObserver.h"
#include "ECKeyHandler.h"



ECEditorObserver :: ECEditorObserver(ECEditorView * viewIn, ECTextDocumentCtrl& ctrlIn, ECFileHandler * fileHandler, ECKeyHandler * firstHandler) 
    : _view(viewIn), _ctrl(ctrlIn), _fileHandler(fileHandler), _firstHandler(firstHandler) {}

void ECEditorObserver :: Update()
{
    // Handle key pressed
    int key = _view->GetKeyPressed();

    _firstHandler->Handle(key);

    _fileHandler->UpdateFile();
    
    // Update view
    int numRowsView = _view->GetNumRowInView();
    int docPosY = _view->GetDocPosY();
    int cursorY = _view->GetCursorY();

    std::tuple<int, int> cursor = {_view->GetCursorX(), cursorY};
    _view->AddCursHist(cursor);

    int page = _view->GetCurrPage();

    // If bigger than view, add page
    if (cursorY > numRowsView - 1)
    {
        _view->SetCurrPage(page + 1);
        _view->SetCursorY(0);
        page ++;
    }
    // Else if negative move to previous page
    else if (cursorY < 0)
    {
        _view->SetCurrPage(page - 1);
        _view->SetCursorY(numRowsView - 1);
        page --;
    }
    if (!_view->GetSearchMode() && !_view->GetReplaceMode())
    {
        _view->UpdateStatusRow(std::get<0>(_view->GetStatusRow()), std::get<1>(_view->GetStatusRow()));
    }
    int startDisplay = (page - 1) * numRowsView;
    int numPages = _view->GetNumPages();
    _view->InitRows();

    // If last page, add all the rows in _ctrl from startDistplay 
    if (page == numPages || numPages == 1)
    {
        for (int i = startDisplay; i < _ctrl.GetNumRows(); i++)
        {
            std::string sToAdd;
            for (int j = 0; j < _ctrl.GetNumColsInRow(i); j++)
            {
                sToAdd.push_back(_ctrl.GetChar(i, j));
            }
            _view->AddRow(sToAdd);
        }
    }
    // If another page add all that fits in window
    else if (page < numPages)
    {
        for (int i = startDisplay; i < numRowsView; i++)
        {
            std::string sToAdd;
            for (int j = 0; j < _ctrl.GetNumColsInRow(i); j++)
            {
                sToAdd.push_back(_ctrl.GetChar(i, j));
            }
            _view->AddRow(sToAdd);
        }
    }
}
