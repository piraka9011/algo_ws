/**
	EECE2560: Proj2a
	LinkedList.cpp
	Purpose: This file contains the implementation of a linked list. All
    features of a linked list will be added here as need for Proj 2.
	@author: Anas Abou Allaban & Turki Alrifaie
	@version: 1.0 2/11/17
*/

#include "LinkedList.h"

/**
    LinkedList class constructor. Sets the head of the linked list to NULL
 */
LinkedList::LinkedList()
{
    headNode = NULL;
}

/**
    Boolean function to check if the list is empty by checking if the headnode
    is a null ptr.
 */
bool LinkedList::isEmpty()
{
    return headNode == NULL;
}

/**
    Inserts a card at the head of the linked list, where the node is in front
    of the head.
    @param: Card c: a card object that is used to create a Card node and put it
            in the list
 */
void LinkedList::insertHead(Card c)
{
    // Create new node
    node<Card>* n = new node<Card>;
    // Set value as card
    n->nodeValue = c;
    // Set next node to head
    n->next = headNode;
    // Put head back in head position
    headNode = n;
}

/**
    Inserts a card at the tail/end of linked list, where the new node's next
    ptr is NULL
    @param: Card c: a card object that is used to create a Card node and put it
            in the list
 */
void LinkedList::replace(Card c)
{
    if(isEmpty())
    {
        insertHead(c);
        return;
    }
    node<Card>* n = new node<Card>;
    node<Card>* curr = headNode;
    // Iterate through list until the end/NULL
    while(curr->next)
    {
        curr = curr->next;
    }
    // Set the value of the node;
    n->nodeValue = c;
    // Set the node at the element after the last
    curr->next = n;
    // Set the next element as null (Node is at end of list)
    n->next = NULL;
}

/**
    This function deletes the card at the head and sets the node after the head
    as the new head node
 */

void LinkedList::removeHead()
{
    // Create a temp node to store location of the head
    node<Card>* temp = headNode;
    // Set the head node as the next element
    headNode = headNode->next;
    // Delete old head
    delete temp;
}

/**
    Returns a node<Card>* object that can be used to access the card data
    and the next element.
    @param: int i: index used in the for loop to look for a card in the list
 */
node<Card>* LinkedList::getCard(int i)
{
    node<Card>* curr = headNode;
    for (int j = 0; j < i; j++)
    {
        curr = curr->next;
    }
    return curr;
}

/**
    This overloaded operator prints out the entire linked list from top to bottom
    @param: std::ostream& os: Output stream object used as the LHS of the
            operator's std::cout
            LinkedList& d: A LinkedList object used to get the head of the list and then
            have an iterator iterate through the list.
    @return: std::ostream& os: An output stream object to print to the console
 */
std::ostream& operator << (std::ostream &os, LinkedList &l)
{
    // Iterator
    node<Card>* curr = l.getHeadNode();
    // Loop until we have reached the end of the list (null/false)
    while(curr)
    {
        os << curr->nodeValue;
        curr = curr->next;
    }
    return os;
}

LinkedList::~LinkedList() {}