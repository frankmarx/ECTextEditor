#ifndef ECCommand_h
#define ECCommand_h

#include <vector>
#include "ECTextDocument.h"


// ******************************************************
// Implement command design pattern
class ECTextDocument;

class ECCommand
{
public:
    virtual ~ECCommand() {}
    virtual void Execute() = 0;
    virtual void UnExecute() = 0;
};

class InsertTextAtCmd : public ECCommand
{
public:
    InsertTextAtCmd(ECTextDocument& docIn, int posRow, int posCol, const std::vector<char>& listChars);
    virtual void Execute();
    virtual void UnExecute();
private:
    int _posCol;
    int _posRow;
    std::vector<char> _chartoadd;
    ECTextDocument& _doc;
};

class RemoveTextAtCmd : public ECCommand
{
public:
    RemoveTextAtCmd(ECTextDocument& docIn, int posRow, int posCol, int len);
    virtual void Execute();
    virtual void UnExecute();
private:
    int _posCol;
    int _posRow;
    int _lentext;
    std::vector<char> _charsRemoved;
    ECTextDocument& _doc;
};

class CapTextAtCmd : public ECCommand
{
public:
    CapTextAtCmd(ECTextDocument& docIn, int posRow, int posCol, int len);
    virtual void Execute();
    virtual void UnExecute();
private:
    int _posCol;
    int _posRow;
    int _lentext;
    ECTextDocument& _doc;
    std::vector<int> _notChanged;
};

class LowerTextAtCmd : public ECCommand
{
public:
    LowerTextAtCmd(ECTextDocument& docIn, int posRow, int posCol, int len);
    virtual void Execute();
    virtual void UnExecute();
private:
    int _posCol;
    int _posRow;
    int _lentext;
    ECTextDocument& _doc;
    std::vector<int> _notChanged;
};

class InsertBlankRowCmd : public ECCommand
{
public:
    InsertBlankRowCmd(ECTextDocument& docIn, int posRow);
    virtual void Execute();
    virtual void UnExecute();
private:
    int _posRow;
    ECTextDocument& _doc;
};

class InsertRowCmd : public ECCommand
{
public:
    InsertRowCmd(ECTextDocument& docIn, int posRow, std::vector<char> rowToIns);
    virtual void Execute();
    virtual void UnExecute();
private:
    int _posRow;
    std::vector<char> _rowToAdd;
    ECTextDocument& _doc;
};

class RemoveRowCmd : public ECCommand
{
public:
    RemoveRowCmd(ECTextDocument& docIn, int posRow);
    virtual void Execute();
    virtual void UnExecute();
private:
    int _posRow;
    std::vector<char> _rowRemoved;
    ECTextDocument& _doc;
};


// ******************************************************
// Implement command history

class ECCommandHistory
{
public:
    ECCommandHistory();
    virtual ~ECCommandHistory();
    bool Undo();
    bool Redo();
    void ExecuteCmd(ECCommand *pCmd);
    int GetHistorySize();
    
private:
    // your code goes here
    std::vector<ECCommand*> _cmdVector;
    int _index;
    int _histsize;
};


#endif /* ECCommand_h */
