 
#define MAP_HPP_
#include <memory>
#include <iostream>

template <typename K, typename V>
class Node
{
private:
  K key;
  V value;  
  
public:
  Node(K key, V value) : key(key),
			 value(value),
			 left(nullptr),
			 right(nullptr)  {}
   
  std::shared_ptr< Node<K, V> > left;
  std::shared_ptr< Node<K, V> > right;
  
  K getKey() {return key;};
  
  V getValue() {return value;};

  void setValue(const V& val) {value = val;};

  void setKey(const K& k) {key = k;};

  bool isLeaf() { if(!left && !right) return true; else return false;};

  friend std::ostream& operator<< (std::ostream& out, const Node<K, V>& n)
  {
    out << "{k: " << n.key << " v: " << n.value << "}";
    return out;
  }
};


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

  std::weak_ptr< Node<K,V> > search(const K &key);
  //coment
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
    std::cout << *root << " " << root->isLeaf() << std::endl;
  }

template <typename K, typename V>
bool Map<K, V>::_insert(std::shared_ptr< Node<K,V> > &node,
			std::shared_ptr< Node<K,V> > &parent)
{
  std::cout << "here " << *node << " " << *parent << std::endl;
  K currentKey = node->getKey();
  K parentKey = parent->getKey();
  using namespace std;
  
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
      std::cout << "key already exists" << std::endl;
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
std::weak_ptr< Node<K,V> > search(const K &key)
{
  std::weak_ptr< Node<K,V> >  p(new Node<K,V>());
  return p;
}
