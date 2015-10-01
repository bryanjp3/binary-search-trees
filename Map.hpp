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

#ifndef MAP_HPP_
#define MAP_HPP_

#include "Node.hpp"

template <typename K, typename V>
class Map;
template <typename K, typename V>
class RBMap;

template <typename K, typename V>
class Map
{
  
protected:  
  std::shared_ptr< Node<K,V> > root;
  
public:
  Map() : root(nullptr) {}

  void insert(const K &key_, const V &value_);
  
  bool _insert(std::shared_ptr< Node<K,V> > &node,
	       std::shared_ptr< Node<K,V> > &parent);

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
	  node->parent = parent;
	  parent->right = std::move(node);
	  return true;
	}
      else _insert(node, parent->right);
    }

  if(currentKey < parentKey)
    {      
      if(!parent->left)
	{
	  node->parent = parent;
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

/*****************************************************************************/

template <typename K, typename V>
class RBMap : public Map<K, V>
{
private:  

public:

  RBMap() : Map<K, V>() {}
  
  void insert(K _key, V _value);  
};

template <typename K, typename V>
void RBMap<K, V>::insert(K _key, V _value)
{
  std::shared_ptr< Node<K, V> > p(new Node<K, V>(_key, _value));
  
  if (!Map<K, V>::root)
    {
      std::cout << "creating root node" << std::endl;
      Map<K, V>::root = p;
      std::cout << *Map<K, V>::root << std::endl;
    }
    
  else
    {
      std::shared_ptr< Node<K, V> > x = Map<K, V>::root;
      std::shared_ptr< Node<K, V> > y;

      while(x)
	{
	  std::cout << *x << " " << *p << std::endl;
	  y = x;	  
	  if( _key < x->getKey()) x = x->left;
	  else x = x->right;
	}
      p->parent = y;

      if(p->getKey() < y->getKey()) y->left = p;
      else y->right = p;      
      }
}

#endif

