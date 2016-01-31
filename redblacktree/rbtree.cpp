//
//  @file rbtree.cpp Implementation of Red Black tree
//                    assignment.
//
//  @brief Implementation of a red black tree with its various
//           functionality.
//  @author Priyanka Chordia
//  @date   4/13/15.
//

#include <iostream>
#include <iomanip>
#include "rbtree.h"

using std::cout;
using std::setw;
using std::endl;

/*
 void RBTree::reverseInOrderPrint(Node *x, int depth)
 
 Desc:  Prints the nodes in the red black tree.
 Input:  N/A
 Output: N/A
 
 */

void RBTree::reverseInOrderPrint(Node *x, int depth) {
  if ( x != nil ) {
    reverseInOrderPrint(x->right, depth+1);
    cout << setw(depth*4+4) << x->color << " ";
    cout << *(x->key) << " " << *(x->value) << endl;
    reverseInOrderPrint(x->left, depth+1);
  }
}

/*
 RBTree::RBTree() : nil(new Node())
 
 Desc:  Default constructor of the class RBTree
 Input:  N/A
 Output: N/A
 
 */

RBTree::RBTree() : nil(new Node())
{
  root = nil;
}

/*
 RBTree::~RBTree()
 
 Desc:  Default destructor of the class RBTree
 Input:  N/A
 Output: N/A
 
 */

RBTree::~RBTree()
{
  traversePostOrderAndDelete(root);
  delete nil;
}

/*
 void RBTree :: traversePostOrderAndDelete(Node *node)
 
 Desc:  A function that traverses the tree in postorder
        and deletes the entire tree.
 Input:  node: initial node from where the postorder
                traversal works.
 Output: N/A
 
 */

void RBTree :: traversePostOrderAndDelete(Node *node)
{
  if(node != nil && node != NULL && 
     node->right != NULL && 
     node->left != NULL
    )
  {
    traversePostOrderAndDelete(node->right);
    traversePostOrderAndDelete(node->left);
    delete node;
  }
}

/*
 RBTree::Node::Node() : parent(NULL), left(NULL), right(NULL),
 color('B'), key(new string()), value(new string())
 
 Desc:  A default constructor of Node class.
 Input:  N/A
 Output: N/A
 
 */

RBTree::Node::Node() : parent(NULL), left(NULL), right(NULL),
  color('B'), key(new string()), value(new string())
{

}

/*
 RBTree::Node::Node(const string& k, const string& v, Node* n) :
 parent(n), left(n), right(n), color('B'), key(new string(k)),
 value(new string(v))
 
 Desc:  A parameterized constructor of Node class.
 Input:  N/A
 Output: N/A
 
 */

RBTree::Node::Node(const string& k, const string& v, Node* n) :
  parent(n), left(n), right(n), color('B'), key(new string(k)),
  value(new string(v))
{

}

/*
 RBTree::Node::~Node()
 
 Desc:  A destructor of Node class.
 Input:  N/A
 Output: N/A
 
 */

RBTree::Node::~Node()
{
  delete key;
  delete value;
}

/*
 void RBTree::rbInsert(const string &key, const string &value)
 
 Desc:  A function that calls the rbInsert function to insert
        a node in the tree.
 Input:  key: a key that is to be inserted.
         value: satellite data
 Output: N/A
 
 */

void RBTree::rbInsert(const string &key, const string &value)
{
  Node *node = new Node(key, value, nil);
  rbInsert(node);
}

/*
 void RBTree::rbInsert(Node *node)
 
 Desc:  A function that inserts a new node in the tree.
 Input:  node: the new node to be inserted.
 Output: N/A
 
 */

void RBTree::rbInsert(Node *node)
{
  Node *y = nil;
  Node *x = root;

  while(x!=nil)
  {
    y=x;
    if(*(node->key) < *(x->key))
    {
      x = x->left;
    }
    else
    {
      x = x->right;
    }
  }

  node->parent = y;
  if(y == nil)
  {
    root = node;
  }
  else if(*(node->key) < *(y->key))
  {
    y->left = node;
  }
  else
  {
    y->right = node;
  }

  node->left = nil;
  node->right = nil;
  node->color = 'R';
  rbInsertFixup(node);
}

/*
 void RBTree::rbInsertFixup(Node *node)
 
 Desc:  A function that fixes the new node inserted in the tree
        to comply with the rb tree properties.
 Input:  node: the new node that needs to be fixed.
 Output: N/A
 
 */

void RBTree::rbInsertFixup(Node *node)
{
  Node *y;
  while(node->parent->color == 'R')
  {
    if(node->parent == node->parent->parent->left)
    {
      y = node->parent->parent->right;

      if(y->color == 'R')
      {
        node->parent->color = 'B';
        y->color = 'B';
        node->parent->parent->color = 'R';
        node = node->parent->parent;
      }

      else
      {
        if(node == node->parent->right)
        {
          node = node->parent;
          leftRotate(node);
        }

        node->parent->color = 'B';
        node->parent->parent->color = 'R';
        rightRotate(node->parent->parent);
      }
    }
    else
    {
      y = node->parent->parent->left;

      if(y->color == 'R')
      {
        node->parent->color = 'B';
        y->color = 'B';
        node->parent->parent->color = 'R';
        node = node->parent->parent;
      }

      else
      {
        if(node == node->parent->left)
        {
          node = node->parent;
          rightRotate(node);
        }

        node->parent->color = 'B';
        node->parent->parent->color = 'R';
        leftRotate(node->parent->parent);
      }
    }
  }
  root->color = 'B';
}

/*
 void RBTree::leftRotate(Node *node)
 
 Desc:  A function that rotates the node to left to satisfy the rb
        tree properties.
 Input:  node: the new node that needs to be rotated.
 Output: N/A
 
 */

void RBTree::leftRotate(Node *node)
{
  Node *y;
  y = node->right;
  node->right = y->left;

  if(y->left != nil)
  {
    y->left->parent = node;
  }
  y->parent = node->parent;

  if(node->parent == nil)
  {
    root = y;
  }

  else
  {
    if(node == node->parent->left)
    {
      node->parent->left = y;
    }

    else{
      node->parent->right = y;
    }
  }

  y->left = node;
  node->parent = y;
}

/*
 void RBTree::rightRotate(Node *node)
 
 Desc:  A function that rotates the node to right to satisfy the rb 
        tree properties.
 Input:  node: the new node that needs to be rotated.
 Output: N/A
 
 */

void RBTree::rightRotate(Node *node)
{
  Node *y;
  y = node->left;
  node->left = y->right;

  if(y->right != nil)
  {
    y->right->parent = node;
  }
  y->parent = node->parent;

  if(node->parent == nil)
  {
    root = y;
  }

  else
  {
    if(node == node->parent->right)
    {
      node->parent->right = y;
    }

    else{
      node->parent->left = y;
    }
  }

  y->right = node;
  node->parent = y;
}

/*
 void RBTree::rbPrintTree()
 
 Desc:  A function that calls the reverseInorderPrint
        to print the nodes in the tree.
 Input:  N/A
 Output: N/A
 
 */

void RBTree::rbPrintTree()
{
  reverseInOrderPrint(root, 0);
}

/*
 RBTree::Node* RBTree::rbTreeSearch(Node *node, const string &key)
 
 Desc:  A function that searches for the node in the tree.
 Input:  node: the node that needs to be searched.
         key: the value of the node to be searched.
 Output: N/A
 
 */

RBTree::Node* RBTree::rbTreeSearch(Node *node, const string &key)
{
  if(node == nil)
  {
    return nil;
  }
  else if(*(node->key) == key)
  {
    return node;
  }
  else if(*(node->key) < key)
  {
    return rbTreeSearch(node->right, key);
  }
  else
  {
    return rbTreeSearch(node->left, key);
  }
}

/*
 vector<const string*> RBTree::rbFind(const string& key)
 
 Desc:  A function that searches for the node and its 
        multiple occurrences in the tree.
 Input: key: the value of the node to be searched.
 Output: N/A
 
 */

vector<const string*> RBTree::rbFind(const string& key)
{
  vector<const string*> vect;
  Node* node = root;
  if(root == nil)
  {
    return vect;
  }
  else
  {
    node = rbTreeSearch(root, key);
    if(node!=nil)
    {
      string find_str = *(node->key);
      find_str.append(" ");
      find_str.append(*(node)->value);
      vect.push_back(new string(find_str));

      find_str = "";
      Node* temp = node;
      while((node = rbTreePredecessor(node))!=nil)
      {
        if(*(node->key) == key)
        {
          find_str = *(node->key);
          find_str.append(" ");
          find_str.append(*(node)->value);
          vect.push_back(new string(find_str));

          find_str = "";
        }
      }

      node = temp;
      while((node = rbTreeSuccessor(node))!=nil)
      {
        if(*(node->key) == key)
        {
          find_str = *(node->key);
          find_str.append(" ");
          find_str.append(*(node)->value);
          vect.push_back(new string(find_str));

          find_str = "";
        }
      }
    }
    return vect;
  }
}

/*
 void RBTree::rbDelete(const string &key, const string &value)
 
 Desc:  A function that deletes the node from the tree.
 Input: key: the value of the node to be deleted.
        value: consist of satellite data.
 Output: N/A
 
 */

void RBTree::rbDelete(const string &key, const string &value)
{
  Node *node = rbTreeSearch(root,key);
  if(node == nil)
  {
    return;
  }
  if(*(node->key) == key && *(node->value) == value)
  {
    rbDelete(node);
    delete node;
    rbDelete(key,value);
  }
  else
  {
    Node *temp = node;
    while((node = rbTreePredecessor(node))!=nil)
    {
      if(*(node->key) == key && *(node->value) == value)
      {
        rbDelete(node);
        delete node;
        rbDelete(key,value);
        return;
      }
    }

    node = temp;
    while((node = rbTreeSuccessor(node))!=nil)
    {
      if(*(node->key) == key && *(node->value)==value)
      {
        rbDelete(node);
        delete node;
        rbDelete(key,value);
        return;
      }
    }
  }
}

/*
 void RBTree::rbDelete(Node *node)
 
 Desc:  A function that deletes the node from the tree.
 Input: node: the node that needs to be deleted.
 Output: N/A
 
 */

void RBTree::rbDelete(Node *node)
{
  Node *x, *y;
  y = node;
  char y_original_color = y->color;
  if(node->left == nil)
  {
    x = node->right;
    rbTransplant(node,x);
  }
  else if(node->right == nil)
  {
    x = node->left;
    rbTransplant(node,x);
  }
  else
  {
    y = rbTreeMaximum(node->left);
    y_original_color = y->color;
    x = y->left;
    if(y->parent == node)
    {
      x->parent = y;
    }
    else
    {
      rbTransplant(y,x);
      y->left = node->left;
      y->left->parent = y;
    }
    rbTransplant(node,y);
    y->right = node->right;
    y->right->parent = y;
    y->color = node->color;
  }
  if(y_original_color=='B')
    rbDeleteFixup(x);
}

/*
 void RBTree::rbDeleteFixup(Node *node)
 
 Desc:  A function that fixes the entire tree after a node
        is being deleted.
 Input: node: the node that needs to be fixed.
 Output: N/A
 
 */

void RBTree::rbDeleteFixup(Node *node)
{
  Node *w;
  while (node != root && node->color == 'B')
  {
    if(node == node->parent->left)
    {
      w = node->parent->right;
      if(w->color=='R')
      {
        w->color='B';
        node->parent->color = 'R';
        leftRotate(node->parent);
        w = node->parent->right;
      }
      if(w->left->color =='B' && w->right->color=='B')
      {
        w->color = 'R';
        node = node->parent;
      }
      else if(w->right->color == 'B')
      {
        w->left->color = 'B';
        w->color = 'R';
        rightRotate(w);
        w = node->parent->right;
      }
      else
      {
        w->color = node->parent->color;
        node->parent->color ='B';
        w->right->color ='B';
        leftRotate(node->parent);
        node = root;
      }
    }
    else
    {
      w = node->parent->left;
      if(w->color == 'R')
      {
        w->color = 'B';
        node->parent->color = 'R';
        rightRotate(node->parent);
        w = node->parent->left;
      }
      if(w->left->color =='B' && w->right->color == 'B')
      {
        w->color ='R';
        node = node->parent;
      }
      else if(w->left->color == 'B')
      {
        w->right->color ='B';
        w->color='R';
        leftRotate(w);
        w = node->parent->left;
      }
      else
      {
        w->color = node->parent->color;
        node->parent->color ='B';
        w->left->color ='B';
        rightRotate(node->parent);
        node = root;
      }
    }
  }
  node->color='B';
}

/*
 RBTree::Node* RBTree::rbTreeMaximum(Node *node)
 
 Desc:  A function that finds the maximum node in the tree.
 Input: N/A
 Output: N/A
 
 */

RBTree::Node* RBTree::rbTreeMaximum(Node *node)
{
  while(node->right != nil)
    node = node->right;
  return node;
}

/*
 RBTree::Node* RBTree::rbTreeMinimum(Node *node)
 
 Desc:  A function that finds the minimum node in the tree.
 Input: N/A
 Output: N/A
 
 */

RBTree::Node* RBTree::rbTreeMinimum(Node *node)
{
  while(node->left != nil)
    node = node->left;
  return node;
}

/*
 RBTree::Node* RBTree::rbTreeSuccessor(Node *node)
 
 Desc:  A function that finds the successor of the node in the tree.
 Input: N/A
 Output: N/A
 
 */

RBTree::Node* RBTree::rbTreeSuccessor(Node *node)
{
  Node *y;
  if(node->right != nil)
    return rbTreeMinimum(node->right);

  y = node->parent;
  while(y!=nil && node == y->right)
  {
    node = y;
    y = y->parent;
  }
  return y;
}

/*
 RBTree::Node* RBTree::rbTreePredecessor(Node *node)
 
 Desc:  A function that finds the predecessor of the node in the tree.
 Input: N/A
 Output: N/A
 
 */

RBTree::Node* RBTree::rbTreePredecessor(Node *node)
{
  Node *y;
  if(node->left != nil)
    return rbTreeMaximum(node->left);

  y = node->parent;
  while(y!=nil && node == y->left)
  {
    node = y;
    y = y->parent;
  }
  return y;
}

/*
 void RBTree :: rbTransplant(Node* u, Node* v)
 
 Desc:  A function to transplant inside the red black tree.
 Input: N/A
 Output: N/A
 
 */

void RBTree :: rbTransplant(Node* u, Node* v)
{
  if(u->parent == nil)
  {
    root = v;
  }
  else if(u == u->parent->left)
  {
    u->parent->left = v;
  }
  else
  {
    u->parent->right = v;
  }
  v->parent = u->parent;
}
