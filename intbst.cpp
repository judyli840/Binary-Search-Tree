// intbst.cpp
// Implements class IntBST
// Judy Li, 02/16/19

#include "intbst.h"

#include <iostream>
using std::cout;

// constructor sets up empty tree
IntBST::IntBST() : root(0) { }

// destructor deletes all nodes
IntBST::~IntBST() {
    clear(root);
}

// recursive helper for destructor
void IntBST::clear(Node *n) {
    if (n) {
	clear(n->left);
	clear(n->right);
	delete n;
    }
}

// insert value in tree; return false if duplicate
bool IntBST::insert(int value) {
    // handle special case of empty tree first
    if (!root) {
	root = new Node(value);
	return true;
    }
    // otherwise use recursive helper
    return insert(value, root);
}

// recursive helper for insert (assumes n is never 0)
bool IntBST::insert(int value, Node *n) {
    if (value == n->info)
	return false;
    if (value < n->info) {
	if (n->left)
	    return insert(value, n->left);
	else {
	    n->left = new Node(value);
	    n->left->parent = n;
	    return true;
	}
    }
    else {
	if (n->right)
	    return insert(value, n->right);
	else {
	    n->right = new Node(value);
	    n->right->parent = n;
	    return true;
	}
    }
}

// print tree data pre-order
void IntBST::printPreOrder() const {
    printPreOrder(root);
}

// recursive helper for printPreOrder()
void IntBST::printPreOrder(Node *n) const {
    if (n) {
	cout << n->info << " ";
	printPreOrder(n->left);
	printPreOrder(n->right);
    }
}

// print tree data in-order, with helper
void IntBST::printInOrder() const {
    printInOrder(root);
}
void IntBST::printInOrder(Node *n) const {
    if (!n)
	    return;
    if (n !=0){
    printInOrder(n->left);
    cout << n->info << " ";
    printInOrder(n->right);
    }

}

// prints tree data post-order, with helper
void IntBST::printPostOrder() const {
    printPostOrder(root);
}

void IntBST::printPostOrder(Node *n) const {
    if(!n)
        return;

    printPostOrder(n->left);
    printPostOrder(n->right);
    cout << n->info << " ";
}

// return sum of values in tree
int IntBST::sum() const {
    return sum(root);
}

// recursive helper for sum
int IntBST::sum(Node *n) const {
    if(!n)
        return 0;
    
    return sum(n->left)+ sum(n->right) + n->info;
}

// return count of values
int IntBST::count() const {
    return count(root);
}

// recursive helper for count
int IntBST::count(Node *n) const {
    int c = 0;
    if (!n){
	return 0;
    }
    c = count(n->left)+count(n->right)+ 1;
    return c;
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
IntBST::Node* IntBST::getNodeFor(int value, Node* n) const{
    if(!n)
	return NULL;
    if(n !=0 && n->info == value)
        return n;
    if(value < n->info)
    	return getNodeFor(value, n->left);
    if(value > n->info)
    	return getNodeFor(value, n->right);
	
    return NULL;
}

// returns true if value is in the tree; false if not
bool IntBST::contains(int value) const {
    if(getNodeFor(value, root) != 0)
        return true;
    else
        return false;
}

// returns the Node containing the predecessor of the given value
IntBST::Node* IntBST::getPredecessorNode(int value) const{
    Node* n = getNodeFor(value,root);

    if (root->info >= value){
        if(n->right == NULL && n->left == NULL){
        if((n->parent->info > value) && (n->parent->parent->info > value))
            return 0;
        if(value > n->parent->info)
            return n->parent;
        n = n->parent;
        return n->parent;
        }

        if (n->left != NULL){
            n = n->left;
            while (n->right != NULL)
                n = n->right;
            return n;
        }
    }

    if (root->info < value){
        if(n->right == NULL && n->left == NULL){
            if (n->parent->info < value)
                return n->parent;
            n = n->parent;
            return n->parent;
        }
        if(n->left != NULL){
            n = n->left;
            while (n->right != NULL)
                n = n->right;
            return n;
        }
    }
    return 0;
    
}

// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const{
    if (getPredecessorNode(value)==0)
        return 0;
    int n = getPredecessorNode(value)->info;
    return n;
}

// returns the Node containing the successor of the given value
IntBST::Node* IntBST::getSuccessorNode(int value) const{
    Node *n = getNodeFor(value, root);

   if (root->info <= value){
        if((n->right == NULL) && (n->left == NULL)){
            while(value> n->parent->info)
                n=n->parent;
            return n->parent;
        }
        if(n->right != NULL){
            n = n->right;
            while(n->left != NULL)
                n=n->left;
            return n;
        }
    }

    if(root->info > value){
        if((n->right == NULL) && (n->left == NULL)){
            if(n->parent->info > n->info){
	    	return n->parent;
	    }
	    n = n->parent;
	    while(value > n->info)
		    n = n->parent;
	    return n;
	    
        }
        if(n->right != NULL){
            n = n->right;
            while (n->left != NULL)
                n = n->left;
            return n;
        }
    }
    n = n->parent;
    while(value > n->info)
	n = n->parent;
    return n;

  /*  if (root->info <= value){
        if((n->right == NULL) && (n->parent->info < n->info)){
		while(value > n->parent->info)
			n = n->parent;
		return n->parent;
	}
     
        if(n->right == NULL)
            return n->parent;
	else{
		n=n->right;
            while(n->left !=NULL)
                n=n->left;
            return n;
	}
    }

    if(root->info > value){
        if((n->right == NULL) && (value > n->parent->info)){
            while (value >= n->info)
                n=n->parent;
            return n;
        }
        if(n->right == NULL)
            return n->parent;
        else
        {
            n=n->right;
            while(n->left !=NULL)
                n=n->left;
            return n;
        }
    }

      return 0;*/
    
}

// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const{
    Node *n = getNodeFor(value, root);
    if((n->right == NULL) && (n->parent->info < n->info)  && root->info < value)
            return 0;
    return getSuccessorNode(value)->info;


}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool IntBST::remove(int value){
    Node *n = getNodeFor(value, root);
    if(n == NULL)
	    return false;
    if(n==root &&  n->left ==NULL && n->right == NULL){
	    delete n;
	    root =NULL;
	    return true;
    }

   if(n->left ==NULL && n->right == NULL){
        if(n->parent->info> n->info){
            n->parent->left = NULL;
        }
        if(n->parent->info< n->info){
            n->parent->right = NULL;
        }
        delete n;
	n = NULL;
        return true;
    }

  // while(n->left !=NULL || n->right != NULL){

	 /*  while(n->left !=NULL && n->right != NULL){
		   Node *s = getSuccessorNode(n->info);
		   n->info = s->info;
		   n = s;
	   }*/

/*	if (n->left == NULL && n->right == NULL){
		delete n;
		return true;
	}*/

    if(n->left !=NULL && n->right == NULL){
        if(n->parent->info < n->info){
            n->parent->right = n->left;
	    n->left->parent = n->parent;
        }
	if(n->parent->info > n->info){
            n->parent->left = n->left;
	    n->left->parent = n->parent;
	}
        
        delete n;
	n=NULL;
        return true;
    }


    if(n->left ==NULL && n->right != NULL){
        if(n->parent->info < n->info){
            n->parent->right = n->right;
	    n->right->parent = n->parent;
        }
	if(n->parent->info > n->info){
            n->parent->left = n->right;
	    n->right->parent = n->parent;
	}
        delete n;
	n = NULL;
        return true;
    }

    remove(getSuccessor(value));

  /*  while(n->left !=NULL && n->right != NULL){
            Node *s = getSuccessorNode(n->info);
            n->info = s->info;
            n = s;
   }*/

    
   
   
    
   /* if (n->info > n->parent->info)
	    n->parent->right = NULL;
    else
	    n->parent->left = NULL;

    delete n;
    return true;*/

    

        

  /*if(n->left !=NULL && n->right != NULL){
    while ( n->right != NULL){
        Node *s = n->right;
        int temp = n->info;
        n->info = s->info;
        s->info = temp;

        Node *ntemp = n;
        n = s;
        s = ntemp;
    }*/

    /* if (n->left !=NULL && n->right != NULL){
        int num = n->info;
        Node *s = getSuccessorNode(value);
        n->info = getSuccessor(value);
        s->info = num;
        if(s->right == NULL && s->left !=NULL){
            if(s->parent->info < s->info){
            s->parent->right = s->right;
            }
            if(s->parent->info > s->info){
            s->parent->left = s->right;
            }
        }
        
        if(s->right != NULL && s->left ==NULL){
            if(s->parent->info < s->info){
                s->parent->right = s->right;
            }
            if(s->parent->info > s->info){
                s->parent->left = s->right;
            }
        }*/
       
 
    
  return false;
        

}
