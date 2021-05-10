#ifndef ECTextDocument_h
#define ECTextDocument_h

#include "ECCommand.h"
#include <vector>
#include <string>

class ECTextDocument;
class ECCommandHistory;


// **********************************************************
// Controller for text document

class ECTextDocumentCtrl
{
public:
    ECTextDocumentCtrl(ECTextDocument  &docIn);          // conroller constructor takes the document as input
    virtual ~ECTextDocumentCtrl();
    void InsertTextAt(int posRow, int posCol, const std::vector<char> &listCharsToIns);    // insert a list of characters starting at position
    void RemoveTextAt(int posRow, int posCol, int lenToRemove);                            // remove a segment of characters  of lenToRemove starting from pos
    void CapTextAt(int posRow, int posCol, int lenToCap);                                  // Capitalize the text of lenToCap long starting from pos
    void LowerTextAt(int posRow, int posCol, int lenToLower);                              // Lowercase the text of lenToLoer starting from pos
    void InsertRowAt(int posRow, std::vector<char> rowToIns);
    void InsertBlankRowAt(int posRow);
    void RemoveRowAt(int posRow);
    char GetChar(int posRow, int posCol);
    int GetNumRows();
    int GetNumColsInRow(int posRow);
    std::string RowToStr(int posRow);
    void Undo();                                                            // undo any change you did to the text
    void Redo();                                                            // redo the change to the text

private:
    ECTextDocument & _doc;
    ECCommandHistory * _histCmds;
};

// **********************************************************
// Document for text document

class ECTextDocument
{
public:
    ECTextDocument();
    virtual ~ECTextDocument();
    ECTextDocumentCtrl &GetCtrl();          // return document controller
    int GetNumRows() const 
    { 
        return _gridChars.size(); 
    }
    int GetNumColsInRow(int posRow)
    {
        return _gridChars[posRow].size();
    }
    char GetCharAt(int posRow, int posCol) const;          // get char at current position
    std::vector<char> GetRowAt(int posRow);
    void InsertCharAt(int posRow, int posCol, char ch);    // insert a single char at position
    void RemoveCharAt(int posRow, int posCol);             // erase a single char at position
    void CapCharAt(int posRow, int posCol);                // capitalize the char at position
    void LowerCharAt(int posRow, int posCol);              // lowercase the char at position
    void InsertRow(int posRow, std::vector<char> rowToIns);
    void InsertBlankRow(int posRow);
    void RemoveRow(int rowPos);
    void Display() const;
private:
    ECTextDocumentCtrl _docCtrl;
    std::vector<std::vector<char>> _gridChars;
};

#endif /* ECTextDocument_h */
