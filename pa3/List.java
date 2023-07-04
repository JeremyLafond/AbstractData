/*
Jeremy Lafond
jalafond
pa3
modified List.java from pa1
*/
public class List
{
	// constructor
	private class Node
	{
		// Fields
		Object data;
		Node next;
		Node prev;
		// Constructor for node
		Node(Object inData) 
		{ 
			data = inData;
			prev = null;
			next = null;
		}
		public String toString()
		{
			return String.valueOf(data);
		}
	}
	// Fields
	Node front;
    Node back;
    Node cursor;
    int length;
    int index;
	// Constructor
	public List()
	{ 
		clear();
	}
	// Access Functions
	// length()
	// Returns number of elements in list
	public int length() 
	{ 
		return length; 
	}
	// index()
	// If cursor is defined, returns the index of the cursor element,
	// otherwise returns -1
	public int index()
	{
		if (cursor != null)
		{
			return index;
		}
		return -1;
	}
	// Returns back element. Pre: length()>0
	public Object back()
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
	// Returns front element. Pre: length()>0
	public Object front()
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
	// Returns cursor element so long as length() > 0 and index() > 0
	public Object get()
	{
		if(length > 0 && index >= 0)
		{
			return cursor.data;
		}
		else
		{
			throw new RuntimeException("List error: length is less than 0/index is less than 0.");
		}
	}
	// Returns true iff this list and L are the same integer sequence
	public boolean equals(Object obj)
	{
		if(obj instanceof List)
		{
			List other = (List) obj;
			Node thisFront = this.front;
			Node otherFront = other.front;
			if(this.length == 0 && length == 0)
			{
				return true;
			}
			if(this.length == other.length)
			{
				for(int j = 0; j <= this.length - 1; j++)
				{
					if(!(thisFront.data.equals(otherFront.data)))
						{
							return false;
						}
						else
						{
							thisFront = thisFront.next;
							otherFront = otherFront.next;
						}
				}
				return true;
			}
			return false;
		}
		return false;
	}
	// Manipulation procedures
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
			return;
		}
		return;
	}
	// If List is non-empty, places the cursor under the back element,
	// otherwise does nothing.
	void moveBack() 
	{
		if(length() != 0)
		{
			cursor = back;
			index = length - 1;
			return;
		}
		return;
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
			index = -1;
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
			index = -1;
		}
	}
	// Insert new element into this List. If List is non-empty,
	// insertion takes place before front element.
	void prepend(Object data)
	{
		Node newFront = new Node(data);
		if(length() > 0)
		{
			newFront.next = front;
			front.prev = newFront;
			front = newFront;
		}
		if(length() == 0)
		{
			back = front = newFront;
		}
		index++;
		length++;
	}
	// Insert new element into this List. If List is non-empty,
	// insertion takes place after back element.
	void append(Object data)
	{
		Node newBack = new Node(data);
		if(length() > 0)
		{
			back.next = newBack;
			newBack.prev = back;
			back = newBack;
			length++;
			return;
		}
		if(length() <= 0)
		{
			back = front = newBack;
			length++;
			return;
		}
	}
	// Insert new element before cursor.
	// Pre: length()>0, index()>=0
	void insertBefore(Object data)
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
			Node newStuff = new Node(data);
			if(cursor.prev == null)
			{
				cursor.prev = newStuff;
				front = newStuff;
				newStuff.next = cursor;
				length++;
				index++;
			}
			else
			{
				newStuff.prev = cursor.prev;
				cursor.prev.next = newStuff;
				cursor.prev = newStuff;
				newStuff.next = cursor;
				length++;
				index++;
			}
		}
	}
	// Inserts new element after cursor.
	// Pre: length()>0, index()>=0
	void insertAfter(Object data)
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
			Node newStuff = new Node(data);
			if(cursor.next == null)
			{
				back = newStuff;
				cursor.next = newStuff;
				newStuff.prev = cursor;
				length++;
			}
			else
			{
				newStuff.next = cursor.next;
				cursor.next.prev = newStuff;
				cursor.next = newStuff;
				newStuff.prev = cursor;
				length++;
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
			return;
		}
		if(cursor == front)
		{
			cursor = null;
			index = -1;
		}
		front = front.next;
		front.prev.next = null;
		front.prev = null;
		length--;
		if(index != -1)
		{
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
			return;
		}
		if(cursor == back)
		{
			cursor = null;
			index = -1;
		}
		back = back.prev;
		back.next.prev = null;
		back.next = null;
		length--;
	}
	// Deletes the element under the cursor Pre: index() >= 0
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
				tempCursor.prev.next = cursor.next;
				tempCursor.next.prev = cursor.prev;
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
				str += t.data + " ";
				t = t.next;
			}
			if(t.next == null)
			{
				str += t.data;
			}
		}
		return str;
	}
}