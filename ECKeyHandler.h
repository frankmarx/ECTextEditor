#ifndef ECKEYHANDLER_H
#define ECKEYHANDLER_H

#include "ECEditorView.h"
#include "ECTextDocument.h"
#include "ECObserver.h"
#include "ECFileHandler.h"

class ECEditorView;

class ECKeyHandler
{
public:
    ECKeyHandler();
    virtual bool CanHandle(int key) = 0;
    virtual void Handle(int key) = 0;
};

class ECAlphaNumericHandler : public ECKeyHandler
{
public:
    ECAlphaNumericHandler(ECTextDocumentCtrl& ctrlIn, ECEditorView * viewIn, ECKeyHandler * nextHandler);
    virtual bool CanHandle(int key);
    virtual void Handle(int key);
private:
    ECKeyHandler * _nextHandler;
    ECTextDocumentCtrl& _ctrl;
    ECEditorView * _view;
};

class ECArrowHandler : public ECKeyHandler
{
public:
    ECArrowHandler(ECTextDocumentCtrl& ctrlIn, ECEditorView * viewIn, ECKeyHandler * nextHandler);
    virtual bool CanHandle(int key);
    virtual void Handle(int key);
private:
    ECKeyHandler * _nextHandler;
    ECTextDocumentCtrl& _ctrl;
    ECEditorView * _view;
};


class ECEnterHandler : public ECKeyHandler
{
public:
    ECEnterHandler(ECTextDocumentCtrl& ctrlIn, ECEditorView * viewIn, ECKeyHandler * nextHandler = NULL);
    virtual bool CanHandle(int key);
    virtual void Handle(int key);
private:
    ECKeyHandler * _nextHandler;
    ECTextDocumentCtrl& _ctrl;
    ECEditorView * _view;
};

class ECBackSpaceHandler : public ECKeyHandler
{
public:
    ECBackSpaceHandler(ECTextDocumentCtrl& ctrlIn, ECEditorView * viewIn, ECKeyHandler * nextHandler = NULL);
    virtual bool CanHandle(int key);
    virtual void Handle(int key);
private:
    ECKeyHandler * _nextHandler;
    ECTextDocumentCtrl& _ctrl;
    ECEditorView * _view;
};

class ECUndoRedoHandler : public ECKeyHandler
{
public:
    ECUndoRedoHandler(ECTextDocumentCtrl& ctrlIn, ECEditorView * viewIn, ECKeyHandler * nextHandler = NULL);
    virtual bool CanHandle(int key);
    virtual void Handle(int key);
private:
    ECKeyHandler * _nextHandler;
    ECTextDocumentCtrl& _ctrl;
    ECEditorView * _view;
};

class ECctrlFHandler : public ECKeyHandler
{
public:
    ECctrlFHandler(ECTextDocumentCtrl& ctrlIn, ECEditorView * viewIn, ECKeyHandler * nextHandler = NULL);
    virtual bool CanHandle(int key);
    virtual void Handle(int key);
private:
    ECKeyHandler * _nextHandler;
    ECTextDocumentCtrl& _ctrl;
    ECEditorView * _view;
};

class ECFindAlphaNumericHandler : public ECKeyHandler
{
public:
    ECFindAlphaNumericHandler(ECTextDocumentCtrl& ctrlIn, ECEditorView * viewIn, ECKeyHandler * nextHandler = NULL);
    virtual bool CanHandle(int key);
    virtual void Handle(int key);
private:
    ECKeyHandler * _nextHandler;
    ECTextDocumentCtrl& _ctrl;
    ECEditorView * _view;
};
class ECFindEnterHandler : public ECKeyHandler
{
public:
    ECFindEnterHandler(ECTextDocumentCtrl& ctrlIn, ECEditorView * viewIn, ECKeyHandler * nextHandler = NULL);
    virtual bool CanHandle(int key);
    virtual void Handle(int key);
private:
    ECKeyHandler * _nextHandler;
    ECTextDocumentCtrl& _ctrl;
    ECEditorView * _view;
};
class ECFindBackSlashHandler : public ECKeyHandler
{
public:
    ECFindBackSlashHandler(ECTextDocumentCtrl& ctrlIn, ECEditorView * viewIn, ECKeyHandler * nextHandler = NULL);
    virtual bool CanHandle(int key);
    virtual void Handle(int key);
private:
    ECKeyHandler * _nextHandler;
    ECTextDocumentCtrl& _ctrl;
    ECEditorView * _view;
};

class ECFindBackspaceHandler : public ECKeyHandler
{
public:
    ECFindBackspaceHandler(ECTextDocumentCtrl& ctrlIn, ECEditorView * viewIn, ECKeyHandler * nextHandler = NULL);
    virtual bool CanHandle(int key);
    virtual void Handle(int key);
private:
    ECKeyHandler * _nextHandler;
    ECTextDocumentCtrl& _ctrl;
    ECEditorView * _view;
};

class ECEscHandler : public ECKeyHandler
{
public:
    ECEscHandler(ECTextDocumentCtrl& ctrlIn, ECEditorView * viewIn, ECKeyHandler * nextHandler = NULL);
    virtual bool CanHandle(int key);
    virtual void Handle(int key);
private:
    ECKeyHandler * _nextHandler;
    ECTextDocumentCtrl& _ctrl;
    ECEditorView * _view;
};

class ECReplaceEnterHandler : public ECKeyHandler
{
public:
    ECReplaceEnterHandler(ECTextDocumentCtrl& ctrlIn, ECEditorView * viewIn, ECKeyHandler * nextHandler = NULL);
    virtual bool CanHandle(int key);
    virtual void Handle(int key);
private:
    ECKeyHandler * _nextHandler;
    ECTextDocumentCtrl& _ctrl;
    ECEditorView * _view;
};

class ECReplaceBackspaceHandler : public ECKeyHandler
{
public:
    ECReplaceBackspaceHandler(ECTextDocumentCtrl& ctrlIn, ECEditorView * viewIn, ECKeyHandler * nextHandler = NULL);
    virtual bool CanHandle(int key);
    virtual void Handle(int key);
private:
    ECKeyHandler * _nextHandler;
    ECTextDocumentCtrl& _ctrl;
    ECEditorView * _view;
};

class ECReplaceAlphaNumericHandler : public ECKeyHandler
{
public:
    ECReplaceAlphaNumericHandler(ECTextDocumentCtrl& ctrlIn, ECEditorView * viewIn, ECKeyHandler * nextHandler = NULL);
    virtual bool CanHandle(int key);
    virtual void Handle(int key);
private:
    ECKeyHandler * _nextHandler;
    ECTextDocumentCtrl& _ctrl;
    ECEditorView * _view;
};

class ECExitHandler : public ECKeyHandler
{
public:
    ECExitHandler(ECTextDocumentCtrl& ctrlIn, ECEditorView * viewIn, ECFileHandler * fileHandIn, ECKeyHandler * nextHandler = NULL);
    virtual bool CanHandle(int key);
    virtual void Handle(int key);
private:
    ECKeyHandler * _nextHandler;
    ECTextDocumentCtrl& _ctrl;
    ECEditorView * _view;
    ECFileHandler * _fileHand;

};
#endif