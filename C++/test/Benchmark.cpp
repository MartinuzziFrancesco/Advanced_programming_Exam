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

int N_max=50000; 

template<class T, typename V>
void take_time(T bst, ofstream& results_file, std::vector<V>& values){
  for(int i=0; i<N_max; i+=50){
    auto start_time = chrono::high_resolution_clock::now();
    
    for(int j=0; j<i; ++j){
      bst.find(values[j]);
    }
    auto end_time = chrono::high_resolution_clock::now();
    auto total_time=chrono::duration_cast<chrono::microseconds>(end_time-start_time).count();
    results_file<<i<<" "<< total_time <<" "<< total_time/double(i)<<" "<<log2(total_time/double(i))<<endl;
  }
};

void benchmark_bst_stdmap(){
  // define and open results file 
  ofstream results_file_bst;
  results_file_bst.open("benchmark_results/benchmark_bst.txt");
  ofstream results_file_stdmap;
  results_file_stdmap.open("benchmark_results/benchmark_stdmap.txt");
  ofstream results_file_bbst;
  results_file_bbst.open("benchmark_results/benchmark_bbst.txt");
  //type = int case

  //initialize bst and vector for the values
  BST<int, int> bst;
  std::vector<int> values(N_max);
    
  std::iota(std::begin(values), std::end(values), 1); //populate vector 
  std::random_shuffle(values.begin(), values.end()); //randomize vector
  //populate bst from vector
  for(const auto& k :values){      //iterate over container
    std::pair<int, int> data{k, k};
    bst.insert(data);
  }
  //take time and store it in file
  take_time(bst, results_file_bst, values);
  results_file_bst.close();
  //build the map from vector
  std::map<int,int> std_map{};
  for ( const auto& k : values ) {
    std_map.emplace(k,k); 
  }
  //take time and store it in file
  take_time(std_map, results_file_stdmap, values);
  results_file_stdmap.close();
  
  //balance tree
  bst.balance();
  //take time and store it in file
  take_time(bst, results_file_bbst, values);
  results_file_bbst.close();
};

int main(){
  //compare int BST and float BST
  benchmark_bst_stdmap();
  return 0;
};
