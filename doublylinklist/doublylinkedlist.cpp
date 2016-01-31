//
//  @file doublylinkedlist.cpp Implementation of Doubly link
//                             list for playlist application
//
//  @brief Implementation of a doubly Linked List for a
//         playlist application for music.
//
//  @author Priyanka Chordia
//  @date   1/28/15.
//

#include "doublylinkedlist.h"


/*
   DoublyLinkedList :: Node :: Node()

   Desc:  Default constructor of class Node initialised
          using initialization list which takes 3 
          arguments next, prev and data.
   Input:  N/A
   Output: N/A
 
 */

DoublyLinkedList :: Node :: Node() :
   next(NULL), prev(NULL) , data(new string())
{

}


/*
   DoublyLinkedList :: Node :: Node(string &song)
 
   Desc:  Parameterized constructor of class Node which
          assigns memory to data and has three arguments
          which are initialised using initialization list.
   Input:  N/A
   Output: N/A
 
 */

DoublyLinkedList :: Node :: Node(string &song) :
   next(NULL) , prev(NULL) , data(new string(song))
{

}


/*
   DoublyLinkedList :: Node :: ~Node()

   Desc:  Destructor of class Node to delete the
          reference of the memory allocated.
   Input:  N/A
   Output: N/A
 
 */

DoublyLinkedList :: Node :: ~Node()
{
   delete data;
}


/*
   DoublyLinkedList :: DoublyLinkedList()
 
   Desc:  Default constructor of class DoublyLinkedList
          initialised using an initialization list.
   Input:  N/A
   Output: N/A

 */

DoublyLinkedList :: DoublyLinkedList() :
   head(NULL) , tail(NULL) , current(NULL) , count(0)
{

}


/*
   DoublyLinkedList :: ~DoublyLinkedList()
 
   Desc: Default destructor of class DoublyLinkedList
         to delete the reference of the node.
   Input:  N/A
   Output: N/A

 */
DoublyLinkedList :: ~DoublyLinkedList()
{
   // Deletes the entire linked list.
   Node *temp = head;
   while(temp != NULL)
   {
      current = temp;
      temp = temp->next;
      delete current;
   }
}


/*
   bool DoublyLinkedList :: empty()
 
   Desc:  Checks if there is any node in the link list
          else returns false.
   Input:  N/A
   Output: isempty: return true if empty
                    else return false.
 
 */

bool DoublyLinkedList :: empty()
{
   if(count == 0)
      return true;
   else
      return false;
}

/*
   void DoublyLinkedList :: begin()
 
   Desc:  Sets the current to the first(head) node of the
          linked list.
   Input:  N/A
   Output: N/A

 */

void DoublyLinkedList :: begin()
{
   current = head;
}

/*
   void DoublyLinkedList :: end()
 
   Desc:  Sets the current to the end(tail) node of the
          linked list.
   Input:  N/A
   Output: N/A

 */

void DoublyLinkedList :: end()
{
   current = tail;
}

/*
   bool DoublyLinkedList :: next()
 
   Desc:  Sets the current to the next node of the
          current node in the linked list.
   Input:  N/A
   Output: returns true if next node is present.

 */

bool DoublyLinkedList :: next()
{
   if(current && current->next != NULL)
   {
      current = current->next;
      return true;
   }
   else
      return false;
}

/*
   bool DoublyLinkedList :: prev()
 
   Desc:  Sets the current to the prev node of the
          current node in the linked list.
   Input:  N/A
   Output: returns true if prev node is present.

 */

bool DoublyLinkedList :: prev()
{
   if(current->prev != NULL)
   {
      current = current->prev;
      return true;
   }
   else
      return false;
}

/*
   const string& DoublyLinkedList :: getData()
 
   Desc:  Returns the data of current node in the
          linked list.
   Input:  N/A
   Output: returns current node if list not empty

 */

const string& DoublyLinkedList :: getData()
{
   static const string str = "";
   if(!empty())
      return *(current->data);
   else
      return str;
}

/*
   void DoublyLinkedList :: append(string &song)
 
   Desc:  Appends a new node to the tail of the
          linked list and sets the new node to current.
   Input:  song: Song name which is to be appended.
   Output: N/A
 
 */

void DoublyLinkedList :: append(string &song)
{
   Node *input = new Node(song);
   if(empty())
   {
      head = tail = current = input;
   }
   else
   {
      tail->next = input;
      input->next = NULL;
      input->prev = tail;
      current = tail = input;
   }
   count++;
}

/*
   void DoublyLinkedList :: insertBefore(string &song)
 
   Desc:  Inserts a new node before the current node of the
          linked list.
   Input:  song: Song name which is to be inserted before
                the current node.
   Output: N/A
 
 */

void DoublyLinkedList :: insertBefore(string &song)
{
   Node *input = new Node(song);
   if(empty())
   {
      head = tail = current = input;
   }
   else
   {
      if(current == head)
      {
         head->prev = input;
         input->next = head;
         head = head->prev;
         head->prev = NULL;
         current = head;
      }
      else
      {
         if(current->prev)
         {
            Node *temp = current->prev;
            input->prev = temp;
            current->prev = input;
            input->next = current;
            temp->next = input;
            current = input;
         }
      }
   }
   count++;
}

/*
   void DoublyLinkedList :: insertAfter(string &song)
 
   Desc:  Inserts a new node after the current node of
          the linked list.
   Input: song: song name which is to be inserted after the
                current song.
   Output: N/A
 
 */

void DoublyLinkedList :: insertAfter(string &song)
{
   Node *input = new Node(song);
   if(empty())
   {
      head = tail = current = input;
   }
   else
   {
      if(current == tail)
      {
         tail->next = input;
         input->prev = tail;
         tail = tail->next;
         tail->next = NULL;
         current = tail;
      }
      else
      {
         if(current->next)
         {
            Node *temp = current->next;
            input->next = temp;
            input->prev = current;
            current->next = input;
            temp->prev = input;
            current = input;
         }
      }
   }
   count++;
}

/*
   bool DoublyLinkedList :: find(string &song)
 
   Desc:  searches for the node and returns true if
          the node is present in the linked list.
   Input: song: name of the song that is to be 
                searched.
   Output: return true if the song is present.

 */

bool DoublyLinkedList :: find(string &song)
{
   Node *temp = head;
   if(!empty())
   {
      while(temp != NULL)
      {
         if(song.compare(*(temp->data)) == 0)
         {
            current = temp;
            return true;
         }
         temp = temp->next;
      }
   }
   return false;
}

/*
   void DoublyLinkedList :: remove(string &song)
 
   Desc:  removes the node passed if present,
          from the linked list.
   Input: song: song name which is to be deleted
                from the linked list.
   Output:  N/A
 
 */

void DoublyLinkedList :: remove(string &song)
{
   Node *temp = head;
   if(!empty())
   {
      if(count == 1)
      {
         delete current;
         head->next = head->prev = NULL;
         head = tail = current = NULL;
         count--;
      }
      else
      {
         while(temp && song.compare(*(temp->data)) != 0)
         {
            temp = temp->next;
         }
         if(temp == NULL)
         {
            return;
         }
         if(temp == head)
         {
            head = head->next;
            current = head;
            head->prev = NULL;
            temp->prev = temp->next = NULL;
            delete temp;
         }
         else if(temp == tail)
         {
            tail = tail->prev;
            current = tail;
            tail->next = NULL;
            temp->prev = temp->next = NULL;
            delete temp;
         }
         else
         {
            Node *tempPrev = temp->prev;
            Node *tempNext = temp->next;
            tempPrev->next = tempNext;
            tempNext->prev = tempPrev;
            temp->prev = temp->next = NULL;
            current = tempNext;
            delete temp;
         }
         count--;
      }
   }
}
