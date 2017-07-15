#include "Editor.h"
#include <string>
#include <stack>
#include "Line.h"
#include "Action.h"
#include "LinkedNode.h"
#include "LinkedList.h"



void Editor::insertLine()
{
	Line eline;
	LinkedNode<Line> *cnode = lines.getNodeAt(cursor);

	lines.insertNode(cnode, eline);
	cursor=cursor+1;
	
	Action insertL(INSERT_LINE, cursor);
	history.push(insertL);
			
	
}	
	


	/* Inserts characater _c_ to the line that the cursor is at by calling
	 * corresponding function from Line class. Then, INSERT_CHAR action is added
	 * ti action history.
	 */
void Editor::insertChar(char c)
{

	Line *iline;
	LinkedNode<Line> *cnode = lines.getNodeAt(cursor);
	iline=cnode->getData();

	Action insertC(INSERT_CHAR, cursor, iline->getCursorPosition(), c);
	history.push(insertC);
												
	
	(cnode->getData())->insert(c); 
	
}
	
	/* Calls corresponding function from Line class if there is a chacarter
		at the cursor position and saves the action to the history.
	 * if there is no character at the cursor position, function does nothing
	 */
void Editor::del()
{
	Line *dline;
	LinkedNode<Line> *cnode = lines.getNodeAt(cursor);
	
	dline=cnode->getData();
	
	
	int localC=dline->getCursorPosition();
	if(localC != dline->getLength())
	{
		Action ddel(DEL, cursor, localC, dline->getCharAt(localC));
		history.push(ddel);
	}												
	
	(cnode->getData())->del();
	
}
	

/* Calls corresponding function from Line class if there is a chacarter
on the left of cursor position and saves the action to the history.
* if the cursor is at the beginning of the line, function does nothing. 
*/
void Editor::backspace()
{
	Line *bline;
	LinkedNode<Line> *cnode = lines.getNodeAt(cursor);
	
	bline=cnode->getData();

	int localC=bline->getCursorPosition();

	if(localC != 0)
	{	
		Action back(BACKSPACE, cursor, localC-1, bline->getCharAt(localC-1));
		history.push(back);
	}
	(cnode->getData())->backspace(); 

}
	
	/* Reverts the last action If there is an action in the history stack.
	 * Revertable actions are:
	 	- backspacing a character
	 	- deleting a character
	 	- inserting a character
	 	- inserting a line
	 */
void Editor::undo()
{

if(history.size()>0)	
{
	Action un=history.top();
		
	
	
	if(un.getType() == 0)//INSERT_CHAR
	{
		//char ch=un.getParam();
		int row=un.getRow();
		int col=un.getCol();
		
		Line *u1;
		LinkedNode<Line> *cnode = lines.getNodeAt(row);
		u1=cnode->getData();
		

		cursor=row;		
		u1->moveCursorTo(col);

		u1->del();


		history.pop();
	}
	else if(un.getType() == 1)//DEL
	{
		char ch=un.getParam();
		int row=un.getRow();
		int col=un.getCol();
		
		Line *u1;
		LinkedNode<Line> *cnode = lines.getNodeAt(row);
		u1=cnode->getData();

		cursor=row;
		u1->moveCursorTo(col);	
		u1->insert(ch);
		u1->moveCursorTo(col);
		history.pop();
	}
	
	else if(un.getType() == 2)//BACKSPACE
	{
		char ch=un.getParam();
		int row=un.getRow();
		int col=un.getCol();

		Line *u1;
		LinkedNode<Line> *cnode = lines.getNodeAt(row);
		u1=cnode->getData();
				
		cursor=row;				
		u1->moveCursorTo(col);
		u1->insert( ch);
		history.pop();
		

	}
	
	else if(un.getType() == 3)//INSERT_LINE
	{
		int row=un.getRow();
		
		LinkedNode<Line> *cnode = lines.getNodeAt(row);
	
		cursor=row;		
		
		moveCursorUp();
		lines.deleteNode(cnode);
		
			
		history.pop();
	}	
}
	
	
}
	


/* Moves the cursor up by 1 if the cursor is not at the first line.
 */
void Editor::moveCursorUp()
{
	if(cursor > 0)
		cursor=cursor-1;
}

	
/* Moves the cursor down by 1 if the cursor is not at the last line.
 */
void Editor::moveCursorDown()
{
	LinkedNode<Line> *cnode = lines.getNodeAt(cursor);
												//if(cnode->next != NULL
	if(cnode->getNext() != NULL)
		cursor=cursor+1;
}
	


/* Calls corresponding function from Line class
*/	
void Editor::moveCursorLeft()
{
	Line *mline;
	LinkedNode<Line> *cnode = lines.getNodeAt(cursor);
	
//	mline=cnode->data;
	mline=cnode->getData();
	mline->moveCursorLeft();

}



/* Calls corresponding function from Line class
*/	
void Editor::moveCursorRight()
{
	Line *mline;
	LinkedNode<Line> *cnode = lines.getNodeAt(cursor);
	
//	mline=cnode->data;
	mline=cnode->getData();	
	mline->moveCursorRight();

}	




	
/* Returns cursor row(global cursor) under 0-based numbering.
*/
int Editor::getCursorRow() const
{
	return cursor;
} 



/* Returns cursor column(cursor of the line that global cursor is at) 
 * under 0-based numbering.
 */
int Editor::getCursorCol() const
{
	Line *gline;
	LinkedNode<Line> *cnode = lines.getNodeAt(cursor);
	
	//gline=cnode->data;
	gline=cnode->getData();
	return gline->getCursorPosition();
}




	
/* Returns line count of the editor
*/
int Editor::getLength() const
{
	LinkedNode<Line> *count=lines.getHead();
	int counter=1;
	
	while(count != lines.getTail())
	{
		counter++;
		count=count->getNext();
	}
	
	return counter;

}
	


/* Returns the content of the idx-th line under 0-based numbering.
*/
std::string Editor::getLine(int idx) const
{
	Line *lline;
	LinkedNode<Line> *cnode = lines.getNodeAt(idx);
	lline=cnode->getData();
	
	/* int getLength() const; Returns the length of the line. */
	int length=lline->getLength();
 
	/* char getCharAt(int idx) const - Returns the character at the `idx`-th position. 
	 * - `idx` should be given under 0-based numbering.
	 */
	char* out = new char[length + 1];
	int i=0;
	for(i=0; i<length; i++)
	{
		out[i]=lline->getCharAt(i);								
	}
	out[i] = 0;
	return out;
}



