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
#ifndef MAP_H_
#define MAP_HPP_
#include <memory>
#include <iostream>
#include <algorithm>

template <typename K, typename V>
class Node
{
private:
  const K key;
  const V value;  
  
public:
  Node(K key, V value) : key(key),
			 value(value),
			 left(nullptr),
			 right(nullptr)  {}
   
  std::shared_ptr< Node<K, V> > left;
  std::shared_ptr< Node<K, V> > right;
  
  K getKey() {return key;};
  
  V getValue() {return value;};

  bool isLeaf() { if(!left && !right) return true; else return false;};

  int height();
  
  int _height(std::shared_ptr< Node<K, V> > node);

  void rotateLeft();

  void rotateRight();

  friend std::ostream& operator<< (std::ostream& out, const Node<K, V>& n)
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
void Node<K,V>::rotateLeft()
{
  auto p = std::make_shared< Node<K,V> >(this->right);
  
  this->right.release();
  this->right = std::make_shared< Node<K,V> >(p->left);
  this->left = std::make_shared< Node<K,V> >(p);
}
/**************************************************************/
template <typename K, typename V>
class Map
{
  
private:  
  std::shared_ptr< Node<K,V> > root;

public:
  Map() : root(nullptr) {}

  void insert(const K &key_, const V &value_);
  
  bool _insert(std::shared_ptr< Node<K,V> > &node,
	       std::shared_ptr< Node<K,V> > &parent);

  bool deleteNode(const K &key);

  std::shared_ptr< Node<K,V> > search(const K &key);

  std::shared_ptr<Node<K,V> > _search(std::shared_ptr<Node<K,V> > node,
				      const K &key);
  
};

template <typename K, typename V>
void Map<K, V>::insert(const K &key_, const V &value_)
  {
    std::shared_ptr< Node<K,V> > p(new Node<K,V>(key_, value_));
      
    if(!root)  
    {
      std::cout << "no root" << std::endl;         
      root = std::move(p);
    }
    
    else _insert(p, root);
  }

template <typename K, typename V>
bool Map<K, V>::_insert(std::shared_ptr< Node<K,V> > &node,
			std::shared_ptr< Node<K,V> > &parent)
{  
  K currentKey = node->getKey();
  K parentKey = parent->getKey();
  
  if(currentKey > parentKey)
    {     
      if(!parent->right)
	{
	  parent->right = std::move(node);
	  return true;
	}
      else _insert(node, parent->right);
    }

  if(currentKey < parentKey)
    {      
      if(!parent->left)
	{	 
	  parent->left = std::move(node);
	  return true;
	}
      else _insert(node, parent->left);
     }

  if(currentKey == parent->getKey())
    {
      std::cout << "cannot insert. key already exists" << std::endl;
      return false;
    }

  else return false;
}

template <typename K, typename V>
bool deleteNode(const K &key)
{  
  return true;
}

template <typename K, typename V>
std::shared_ptr< Node<K,V> > Map<K,V>::search(const K &key)
{
  std::shared_ptr< Node<K,V> >  p;

  if(key == root->getKey()) p = root;
  
  else if(key > root->getKey()) p = _search(root->right, key);  
  else if(key < root->getKey()) p = _search(root->left, key);
  
  return p;
}

template <typename K, typename V>
std::shared_ptr< Node<K,V> > Map<K,V>::_search(std::shared_ptr<Node<K,V> > node,
					       const K &key)
{
  if(!node)
    {
      std::cout << "not in tree" << std::endl;
      return node;
    }
  
  std::cout << "searching " << *node  << std::endl;
  std::shared_ptr<Node<K,V> > p;
  
  if(key == node->getKey())
    {
      std::cout << "match: " << *node << std::endl;
      return node;
    }
  
  if(!node->isLeaf())
    {
      if(key > node->getKey()) p = _search(node->right, key);
      if(key < node->getKey()) p = _search(node->left, key);
    }
  
  if(node->isLeaf() && key != node->getKey()) std::cout << "not in map" << std::endl;
  return p;
}
#endif

