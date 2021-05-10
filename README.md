# ECTextEditor
Vi-Style Text Editor for my C++ course

This editor implements Model-View-Controller, Chain of Responsibility, and the Observer design pattern.
ECTextViewImp is the subject and notifies ECObserver on a key press.
ECTextViewImp was provided by the instructor and takes care of properly displaying a window with text.
When ECObserver is notified, it handles the key pressed using Chain of Responsibility.
There are various Key Handlers who will edit the document model, then update the view using ECTextViewImp.
The grid is the model (ECTextDocument),  the controller (ECTextDocuemntCtrl) has access to and edits the model, and the view (ECEditorView) has access to the controller and ECTextViewImp.
The Model-View-Controller design allows me to have a grid of characters for the model, but only have to display what is needed for the view.
