#include "../include/BTree.h"
#include <memory>
#include <algorithm>
#include <string>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <map>
#include <unordered_map>
#include <chrono>
#include <fstream>
#include <iostream>
#include <numeric>

using namespace std;

int N_max = 12000000;
int n_find = 100;
int n_try = 20;
string PATH_NAME = "benchmark_results/Benchmark_On_Size_";

template <class T, typename V>
void take_time(T bst, ofstream &results_file, std::vector<V> &values){
  double median=0;
  for (int i = 1; i <= n_try; i++){  
    auto start_time = chrono::high_resolution_clock::now();
    for (int j = 1; j <= n_find; j++)
    {
      bst.find(rand()%values.size()+1);
    }
    auto end_time = chrono::high_resolution_clock::now();
    auto total_time = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
    median+=total_time;  
  }
  median/=n_try;
  results_file << values.size() << ",\t\t" << median << ",\t\t" << median / double(n_find) << ",\t\t" << log2(median / double(n_find)) << endl;
};

int main()
{
  ofstream results_file_bst;
  results_file_bst.open(PATH_NAME + "bst.txt");
  ofstream results_file_stdmap;
  results_file_stdmap.open(PATH_NAME + "stdmap.txt");
  ofstream results_file_bbst;
  results_file_bbst.open(PATH_NAME + "bbst.txt");
  ofstream results_file_bstl;
  results_file_bstl.open(PATH_NAME + "bstl.txt");
  ofstream results_file_stdumap;
  results_file_stdumap.open(PATH_NAME + "stdumap.txt");

  for (uint i = 100; i < N_max; i *= 1.2)
  {
    BST<int, int> bst;
    //BST<int, int> bst_linear;
    std::vector<int> values(i);
    

    std::iota(std::begin(values), std::end(values), 1); //populate vector
    /**for (const auto &k : values)
    { //iterate over container
      std::pair<int, int> data{k, k};
      bst_linear.insert(data);
    }
    take_time(bst_linear, results_file_bstl, values);
    */
    std::random_shuffle(values.begin(), values.end());  //randomize vector
                                                        //populate bst from vector
    for (const auto &k : values)
    { //iterate over container
      std::pair<int, int> data{k, k};
      bst.insert(data);
    }

    take_time(bst, results_file_bst, values);

    //build the map from vector
    std::map<int, int> std_map{};
    std::unordered_map<int, int> std_umap{};
    for (const auto &k : values){
      std_map.emplace(k, k);
      std_umap.emplace(k, k);
    }
    //take time and store it in file
    take_time(std_map, results_file_stdmap, values);
    take_time(std_umap, results_file_stdumap, values);
    
    

    //balance tree
    bst.balance();
    //take time and store it in file
    take_time(bst, results_file_bbst, values);
  }

  results_file_bst.close();
  results_file_stdmap.close();
  results_file_bbst.close();

  return 0;
}
