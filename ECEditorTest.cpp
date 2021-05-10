// Test code for editor
#include "ECEditorView.h"
#include "ECFileHandler.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace  std;

int myCounter = 0;
ECKeyHandler * InitHandlers(ECTextDocumentCtrl& ctrl, ECEditorView * viewPtr, ECFileHandler * fileHand);

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        cout << "Error.  Usage: ./editor \"filename\"" << endl;
        return 1;
    }
    std::string fileName = argv[1];
    ECTextDocument doc;
    ECTextDocumentCtrl& ctrl = doc.GetCtrl();
    ECFileHandler * fileHand = new ECFileHandler(fileName, ctrl);
    ECTextViewImp imp;
    ECTextViewImp * impPtr = &imp;
    ECEditorView view(impPtr, ctrl, fileName);
    ECEditorView * viewPtr = &view;
    ECKeyHandler * first = InitHandlers(ctrl, viewPtr, fileHand);
    ECObserver * obs = new ECEditorObserver(viewPtr, ctrl, fileHand, first);
    view.Attach(obs);
    view.UpdateStatusRow(fileName, "Page 1");
    // Add what is in ctrl to view
    view.Notify();
    view.Show();
}

// Returns pointer to the first Handler in the Chain
ECKeyHandler * InitHandlers(ECTextDocumentCtrl& ctrl, ECEditorView * viewPtr, ECFileHandler * fileHand)
{
    ECKeyHandler * fifteenth = new ECExitHandler(ctrl, viewPtr, fileHand, NULL);
    ECKeyHandler * fourteenth = new ECReplaceEnterHandler(ctrl, viewPtr, fifteenth);
    ECKeyHandler * thirteenth = new ECReplaceBackspaceHandler(ctrl, viewPtr, fourteenth);
    ECKeyHandler * twelvth = new ECReplaceAlphaNumericHandler(ctrl, viewPtr, thirteenth);
    ECKeyHandler * eleventh = new ECFindBackSlashHandler(ctrl, viewPtr, twelvth);
    ECKeyHandler * tenth = new ECFindBackspaceHandler(ctrl, viewPtr, eleventh);
    ECKeyHandler * ninth = new ECFindEnterHandler(ctrl, viewPtr, tenth);
    ECKeyHandler * eigth = new ECEscHandler(ctrl, viewPtr, ninth);
    ECKeyHandler * seventh = new ECFindAlphaNumericHandler(ctrl, viewPtr, eigth);
    ECKeyHandler * sixth = new ECctrlFHandler(ctrl, viewPtr, seventh);
    ECKeyHandler * fifth = new ECUndoRedoHandler(ctrl, viewPtr, sixth);
    ECKeyHandler * fourth = new ECAlphaNumericHandler(ctrl, viewPtr, fifth);
    ECKeyHandler * third = new ECArrowHandler(ctrl, viewPtr, fourth);
    ECKeyHandler * second = new ECEnterHandler(ctrl, viewPtr, third);
    ECKeyHandler * first = new ECBackSpaceHandler(ctrl, viewPtr, second);
    return first;
}
