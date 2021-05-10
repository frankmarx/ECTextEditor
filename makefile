ECEditor: ECEditorTest.o ECCommand.o ECEditorView.o ECObserver.o ECTextDocument.o ECTextViewImp.o ECKeyHandler.o ECFileHandler.o
	g++ ECEditorTest.o ECCommand.o ECEditorView.o ECObserver.o ECTextDocument.o ECTextViewImp.o ECKeyHandler.o ECFileHandler.o -o editor

ECEditorTest.o: ECEditorTest.cpp
	g++ -c ECEditorTest.cpp

ECCommand.o: ECCommand.cpp ECCommand.h
	g++ -c ECCommand.cpp

ECEditorView.o: ECEditorView.cpp ECEditorView.h
	g++ -c ECEditorView.cpp

ECObserver.o: ECObserver.cpp ECObserver.h
	g++ -c ECObserver.cpp

ECTextDocument.o: ECTextDocument.cpp ECTextDocument.h
	g++ -c ECTextDocument.cpp

ECTextViewImp.o: ECTextViewImp.cpp ECTextViewImp.h
	g++ -c ECTextViewImp.cpp

ECKeyHandler.o: ECKeyHandler.cpp ECKeyHandler.h
	g++ -c ECKeyHandler.cpp

ECFileHandler.o: ECFileHandler.cpp ECFileHandler.h
	g++ -c ECFileHandler.cpp

clean:
	rm *.o editor