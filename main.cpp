 
#include<iostream>
#include "Map.hpp"
#include <memory>
int main()
{
  Node<int, int>  n = Node<int, int>(5,5);
  Node<int, int>  n2 = Node<int, int>(4,8);

  //std::unique_ptr<Node<int, int> > p1(new Node<int, int>);


  Map<int, int> m = Map<int, int>();

  int i, j;
  i = 1;
  j = 3;
  m.insert(i,j);
  i++;
  m.insert(i, j);
  i++;
  m.insert(i,j);//i =3
  
  i = 7;
  m.insert(i,j);
  
  i = -5;
  m.insert(i,j);
  //std::cout << "hi " << n2.getValue() << std::endl;
  return 0;
}
