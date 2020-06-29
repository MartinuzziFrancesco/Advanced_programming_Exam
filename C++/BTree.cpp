#include "BTree.h"


int main()
{
  BST<int, int> test{};
  for(size_t i=0; i<10; ++i){
    const std::pair<int, int> p{rand()%32, rand()%32};
    test.insert(p);
  }

  return 0;
}
