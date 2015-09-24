/*
The MIT License (MIT)

Copyright (c) 2015 John Bryan

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef NODE_H_
#define NODE_HPP_

#include <memory>
#include <iostream>
#include <algorithm>


template <typename K, typename V>
class Node
{
protected:
  const K key;
  const V value;  
  
public:
  Node(K key, V value) : key(key),
			 value(value),
			 left(nullptr),
			 right(nullptr) {}
  
  Node(std::shared_ptr<Node<K, V> > &node) : key(0), value(0) {}
  
  std::weak_ptr< Node<K, V> > parent;
  std::shared_ptr< Node<K, V> > left;
  std::shared_ptr< Node<K, V> > right;
  
  K getKey() {return key;};
  
  V getValue() {return value;};

  bool isLeaf() { if(!left && !right) return true; else return false;};

  int height();
  
  int _height(std::shared_ptr< Node<K, V> > node);

  static void rotateLeft(std::shared_ptr< Node<K, V> > &node);

  static void rotateRight(std::shared_ptr< Node<K, V> > &node);

  friend std::ostream& operator<< (std::ostream& out,
					   const Node<K, V>& n)
  {
    out << "{key: " << n.key << " value: " << n.value << "}";
    return out;
  }
};

template <typename K, typename V>
int Node<K,V>::height()
{
  if(this->isLeaf()) return 1;

  int leftHeight = _height(this->left);
  int rightHeight = _height(this->right);

  int height = std::max(leftHeight, rightHeight);
  return height + 1;
}

template <typename K, typename V>
int Node<K,V>::_height(std::shared_ptr <Node<K, V> > node)
{
  if(node->isLeaf()) return 1;
  
  int leftHeight = 1;
  int rightHeight = 1;

  if(node->left) leftHeight = _height(node->left);
  if(node->right) rightHeight = _height(node->right);
  
  int height = std::max(leftHeight, rightHeight);
  return height + 1;
}

template <typename K, typename V>
void Node<K,V>::rotateLeft(std::shared_ptr< Node<K, V> > &node)
{
  K tempKey = node->getKey();
  auto temp = node->parent.lock();
  auto pivot = node->right;

  node->right = pivot->left;
  pivot->left = node;
  node = pivot;

  //fix parent pointers
  node->left->parent = node;
  node->left->right->parent = node->left;
  node->parent = temp;

  //fix child pointers of node parent
  if(temp->right->getKey() == tempKey) temp->right = node;
  else  temp->left = node;
}
template <typename K, typename V>
void Node<K,V>::rotateRight(std::shared_ptr< Node<K, V> > &node)
{
  K tempKey = node->getKey();
  auto temp = node->parent.lock();
  auto pivot = node->left;
  
  node->left = pivot->right;
  pivot->right = node;
  node = pivot;
  
  //fix parent pointers
  node->right->parent = node;
  node->right->left->parent = node->right;
  node->parent = temp;

  //fix child pointers of node parent
  //if else statement determines which child needs to be fixed  
  if(temp->right->getKey() == tempKey) temp->right = node;
  else  temp->left = node;
  
}

template <typename K, typename V>
class RBNode : public Node<K, V>
{
public: 
  typedef enum{red, black} color;

  //constructor
  RBNode(K key, V value) : Node<K, V>(key, value) {}
  
  RBNode::color getColor() { return nodeColor;}
  
private:
  RBNode::color nodeColor;
  

};


#endif
