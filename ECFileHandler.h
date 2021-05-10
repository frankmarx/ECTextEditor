#ifndef ECFILEHANDLER_H
#define ECFILEHANDLER_H

#include "ECTextDocument.h"
// File Handler
class ECFileHandler
{
public:
    ECFileHandler(std::string fileName, ECTextDocumentCtrl& ctrlIn);
    void UpdateFile();
    std::string GetName();
private:
    std::string _fileName;
    ECTextDocumentCtrl& _ctrl;
};

#endif