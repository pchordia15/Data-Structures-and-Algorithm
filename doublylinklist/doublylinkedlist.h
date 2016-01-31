//
//  @file   doublylinkedlist.h Declaration of Doubly Link List
//                           for playlist application.
//
//  @brief  Implementation of Doubly Linked List for developing
//          a playlist application for music.
//
//  @author Priyanka Chordia
//  @date   1/28/15.
//

#ifndef CSCI_311_DOUBLYLINKEDLIST__H
#define CSCI_311_DOUBLYLINKEDLIST__H

#include <stdio.h>
#include <string>
#include <iostream>

using std::string;
using std::cout;

class DoublyLinkedList
{
   public:
      DoublyLinkedList();
      ~DoublyLinkedList();

      bool empty();
      void append(string &s);
      void insertBefore(string &s);
      void insertAfter(string &s);
      void remove(string &s);
      void begin();
      void end();
      bool next();
      bool prev();
      bool find(string &s);
      const string& getData();

   private:
      class Node
      {
         public:
            Node();
            Node(string &s);
            ~Node();

            Node *next;
            Node *prev;
            string *data;
      };

      Node *head, *tail, *current;
      int count;
};

#endif /* defined(CSCI_311_DOUBLYLINKEDLIST__H) */
