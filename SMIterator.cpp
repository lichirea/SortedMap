#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>

using namespace std;
//worst,best,total: O(height); this is always the same no matter how it is called
SMIterator::SMIterator(const SortedMap& m) : map(m){
    Node* node = map.root;
    while(node != nullptr){
        s.push_back(node);
        node = node->left;
    }
    if(!s.empty()){
        currentNode = s.back();
    }
    else{
        currentNode = nullptr;
    }
}
//worst,best,total: O(height); this is always the same no matter how it is called
void SMIterator::first(){
    s.clear();
    Node* node = map.root;
    while(node != nullptr){
        s.push_back(node);
        node = node->left;
    }
    if(!s.empty()){
        currentNode = s.back();
    }
    else{
        currentNode = nullptr;
    }
}
//worst,best,total: O(height); this is always the same no matter how it is called
void SMIterator::next(){
    if(!valid()) throw std::exception();
    Node* node = s.back();
    s.pop_back();
    if(node->right != nullptr){
        node = node->right;
        while(node!= nullptr){
            s.push_back(node);
            node = node->left;
        }
    }
    if(!s.empty()){
        currentNode = s.back();
    }
    else{
        currentNode = nullptr;
    }
}
//worst,best,total: ϴ(1); this is always the same no matter how it is called
bool SMIterator::valid() const{
    if(currentNode == nullptr) return false;
    return true;
}
//worst,best,total: ϴ(1); this is always the same no matter how it is called
TElem SMIterator::getCurrent() const{
    if(!valid()) throw std::exception();
   return currentNode->info;
}



