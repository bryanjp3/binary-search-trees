 
#include<iostream>
#include "Map.hpp"
#include <memory>
int main()
{
  Map<int, int> m = Map<int, int>();

  //insert arbitrary values into the map
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
