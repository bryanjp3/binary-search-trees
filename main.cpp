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
#include<iostream>
#include <memory>
#include <random>
#include "Map.hpp"

int main()
{
  RBMap<int, int> m = RBMap<int, int>();

  //insert arbitrary values into the map
  int j = 55;
  
  std::default_random_engine generator;
  std::uniform_int_distribution<int> distribution(0,10000-1);

  int key;
  /*
  for(int i = 0; i < 100; i++)
    {
      key = distribution(generator);
      m.insert(key,j);
    }
   */

  key = 0;
  m.insert(key, j);

  key = 5;
  m.insert(key, j);
  key = 7;
  m.insert(key, j);
  key = 3;
  m.insert(key, j);
  key = 4;
  m.insert(key, j);
  key = 2;
  m.insert(key, j);
  
  key = 5;
  //std::shared_ptr< Node<int,int> > p;
  //p = std::move(m.search(key));
  /*
  if(p)
    {
      std::cout << "the value for the key is " << *p << std::endl;
      std::cout << p->height() << " is the height" << std::endl;
      auto temp = p->parent.lock();
      std::cout << *temp << std::endl;

      std::cout << "\n with rotation \n";
      Node<int, int>::rotateRight(p);
      Node<int, int>::rotateLeft(p);
      key = 7;
      p = std::move(m.search(key));
      std::cout << "the value for the key is " << *p << std::endl;
      std::cout << p->height() << " is the height" << std::endl;
      auto temp2 = p->parent.lock();
      std::cout << " parent node: " << *temp2 << std::endl;
    }*/

  
  
  return 0;
}
