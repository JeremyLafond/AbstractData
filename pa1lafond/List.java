/*
Jeremy Lafond
jalafond
pa1
*/

public class List
{
	// constructor
   private class Node
   {
      	// Fields
      	int data;
      	Node next;
      	Node prev;
      
      	// Constructor for node
       	Node(int data) 
      	{	 
      		this.data = data;
      		prev = null;
      		next = null;
      	}
      	//some getters and setters I started with for testing purposes	
		public Node getBack() 
		{
			return prev;
		}
		public void setBack(Node back)
		{
			this.prev = back;
		}
		public Node getFront() 
		{
			return next;
		}
		public void setFront(Node front) 
		{
			this.next = front;
		}
		public int getD() 
      	{
			return data;
		}
		public void setD(int data) 
		{
			this.data = data;
		}
   }

   // Fields
    Node front; //sentinel
    Node back; //sentinel
    Node cursor;
    int length;
    int index; //index for array

   // Constructor
   public List()
   { 
   		clear();
   }


   // Access Functions --------------------------------------------------------

   // length()
   // Returns number of elements in list
   int length() 
   { 
      return length; 
   }
	// Returns back element. Pre: length()>0
   int back()
   {
   		if(length > 0)
		{
			return back.data;
		}
		else
		{
			throw new RuntimeException("List error: back() called on an empty list");
		}
	
   }
   // returns front element. Pre: length()>0
   int front()
   {
   		if(length > 0)
		{
			return front.data;
		}
		else
		{
			throw new RuntimeException("List error: front() called on an empty list");
		}
   }

   //if cursor is defined, returns the index of the cursor element,
   //otherwise returns -1
   int index()
   {
   		if (cursor != null)
   		{
   			return index;
   		}
   		return -1;
   }

   //returns cursor element so long as length() > 0 and index() > 0
   int get()
   {
   		if(length() > 0 && index() >= 0)
   		{
   			return cursor.data;
   		}
   		return -1;
   }

   //returns true iff this list and L are the same integer sequence
   boolean equals(List L)
   {
   		if(L.length() == 0 && length() == 0)
   		{
   			return true;
   		}
  		if(L.length() == length())
  			{
  				Node temp = front;
  				Node list = L.front;
  				for (int j = 0; j < L.length; j++)
  				{
  					if(temp.data == list.data) //iter thru indexes
  					{
  						temp = temp.next;
  						list = list.next;
  						return true;
  					}
  				}
  				return false;
  			}
  			return false;
   }
// Manipulation procedures -----------------------------------------------------


// Resets this List to its original empty state.
void clear()
{
	back = front = null;
	cursor = null;
	length = 0;
	index = -1;
}

// If List is non-empty, places the cursor under the front element,
// otherwise does nothing.
void moveFront()
{
	if(length() != 0)
	{
		cursor = front;
		index = 0;
	}
}

// If List is non-empty, places the cursor under the back element,
 // otherwise does nothing.
void moveBack() 
{
	if(length() != 0)
	{
		cursor = back;
		index = length - 1;
	}
}

// If cursor is defined and not at front, moves cursor one step toward
 // front of this List, if cursor is defined and at front, cursor becomes
// undefined, if cursor is undefined does nothing.
void movePrev()
{
	if (index() <= length() -1 && index() >= 0)
	{
		cursor = cursor.prev;
		index--;
	}
	else
	{
		index= -1;
	}
}

// If cursor is defined and not at back, moves cursor one step toward
// back of this List, if cursor is defined and at back, cursor becomes
// undefined, if cursor is undefined does nothing.
void moveNext()
{
	if(index < length-1 && index >= 0)
	{
		cursor = cursor.next;
		index++;
	}
	else
	{
		index= -1;
	}
}

// Insert new element into this List. If List is non-empty,
// insertion takes place before front element.
void prepend(int data)
{
	Node newFront = new Node(data);	// holds our new data in a connectable node
	if(length() > 0)
	{
		front.prev = newFront;
		newFront.next = front;
		front = newFront;
		length++;
	}
	if(length() <= 0)
	{
		back = front = newFront;
		length++;
	}
	index++;
}

// Insert new element into this List. If List is non-empty,
// insertion takes place after back element.
void append(int data)
{
	Node newBack = new Node(data);	// holds our new data
	if(length() > 0)
	{
		back.next = newBack;
		newBack.prev = back;
		back = newBack;
		length++;
	}
	if(length() <= 0)
	{
		back = front = newBack;
		length++;
		index++;
	}
}

// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(int data)
{
	if(length <= 0)
	{
		throw new RuntimeException("List error: insertBefore() was called on an empty list.");
	}
	if(index < 0 || index > length - 1)
	{
		throw new RuntimeException("List error: insertBefore() was called with index undefined");
	}
	if(length > 0 && index >= 0)
	{
		Node tempCursor = cursor; //cursor holder
		Node newStuff = new Node(data); //holds our new data in node

		if(cursor.prev == null)
		{
			cursor.prev = newStuff; //links cursor next to new data
			newStuff.next = cursor; //links prev of new data with cursor
			front = newStuff; //moves back to new data node
			length++;
			index++;
		}
		else
		{
			tempCursor = tempCursor.prev;
			newStuff.next = cursor;
			newStuff.prev = tempCursor;
			tempCursor.next = newStuff;
			cursor.prev = newStuff;
			length++;
			index++;
		}
	}
}

// Inserts new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(int data)
{
	if(length <= 0)
	{
		throw new RuntimeException("List error: insertAfter() was called on an empty list.");
	}
	if(index < 0 || index > length - 1)
	{
		throw new RuntimeException("List error: insertAfter() was called with index undefined");
	}
	if(length > 0 && index >= 0)
	{
		Node tempCursor = cursor; //cursor holder
		Node newStuff = new Node(data); //holds our new data in node

		if(cursor.next == null)
		{
			cursor.next = newStuff; //links cursor next to new data
			newStuff.prev = cursor; //links prev of new data with cursor
			back = newStuff; //moves back to new data node
			length++;
			//index++;
		}
		else
		{
			tempCursor = tempCursor.next;
			newStuff.prev = cursor;
			newStuff.next = tempCursor;
			tempCursor.prev = newStuff;
			cursor.next = newStuff;
			length++;
			//index++;
		}
	}
}

// Deletes the front element. Pre: length()>0
void deleteFront() 
{
	if(length <= 0)
	{
		throw new RuntimeException("List error: deleteFront() was called on an empty list");
	}
	if(front == null)
	{
		return;
	}
	if(length == 1)
	{
		this.clear();
	}
	if(cursor == front)
	{
		cursor = null;
		front.next.prev = null;
		front = front.next;
		length--;
		index--;
	}
	else
	{
		front = front.next;
		front.prev.next = null;
		front.prev = null;
		length--;
		index--;
	}
}

// Deletes the back element. Pre: length()>0
void deleteBack() 
{
	Node tempBack = back;
	if(length <= 0)
	{
		throw new RuntimeException("List error: deleteBack() was called on an empty list");
	}
	if(length == 1)
	{
		this.clear();
	}
	if(cursor == back)
	{
		cursor = null;
		index = -1;
		back = back.prev;
		back.next = null;
		length--;
	}
	else
	{
		back = back.prev;
		back.next = null;
		length--;
	}

}
//additional method for moving through array to index
void move(int m)
{
	//make sure m is valid index
		if(m >= length || m <0)
		{
			//if not valid resets cursor 
			cursor = null;
			index = -1;
		}
		else
		{
			cursor = front; //start at front
			index = 0;
			for(int i = 0; i < m; i++)
			{
				moveNext();//utilizes moveNext to iterate through each node
			}
		}
}

// Deletes cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
// Other methods
void delete()
{
	if(index < 0 || cursor == null)
	{
		throw new RuntimeException("Error: delete() was called on a list with an undefined cursor");
	}
	if(length() > 0 && index() >= 0)
	{
		Node tempCursor = cursor;
		if(cursor == back)
		{
			deleteBack();
		}
		else if(cursor == front)
		{
			deleteFront();
		}
		else
		{
		tempCursor.next = cursor.next;
		tempCursor.prev = cursor.prev;
		tempCursor.prev.next = cursor.next;// sets the next link for the node before cursor past cursor
		tempCursor.next.prev = cursor.prev;// sets the prev link for the node after cursor past cursor
		cursor = null;
		tempCursor = null;
		index = -1;
		length--;
		}
	}
	else
	{
		throw new RuntimeException("List error: delete() was called on an empty List");
	}
} 

//OTHER--------------------------------------------------------------------
// Returns a new List representing the same integer sequence as this
// List. The cursor in the new list is undefined, regardless of the
// state of the cursor in this List. This List is unchanged.
List copy()
{
	List copy = new List();
	Node tempFront = this.front;
	if(this.length <= 0)
	{
		return copy;
	}
	while(tempFront != null)
	{	
		copy.append(tempFront.data);
		tempFront = tempFront.next;
	}
	return copy;
} 

// Overrides Object's toString method. Returns a String
// representation of this List consisting of a space
// separated sequence of integers, with front on left.
public String toString()
{
	String str = new String("");
	if(length() > 0)
	{
		Node t = front;
		while(t.next != null)
		{
			{
				str += t.data + " ";
				t = t.next;
			}
		}
		if(t.next == null) //delete whitespace on trailing end of last element
			{
				str += t.data;
			}
	}
	return str;
}

}