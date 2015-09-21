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
  Map<int, int> m = Map<int, int>();

  //insert arbitrary values into the map
  int j;
  j = 3;
  
  std::default_random_engine generator;
  std::uniform_int_distribution<int> distribution(0,10000-1);

  int key = 0;
  for(int k = 0; k <100; k++)
    {
      j = 15;
      key = distribution(generator);
      m.insert(key,j);
    }

  std::shared_ptr< Node<int,int> > p;
  p = std::move(m.search(key));
  if(p)
    {
      std::cout << "in main " << *p << std::endl;
    }
  return 0;
}
