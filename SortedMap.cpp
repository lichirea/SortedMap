#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
using namespace std;




//worst,best,total: ϴ(1); this is always the same no matter how it is called
SortedMap::SortedMap(Relation r) {
	this->r = r;
	this->length = 0;
	this->root = nullptr;
	this->flag = nullptr;
}
//worst,best,total: O(height); this is always the same no matter how it is called
TValue SortedMap::add(TKey k, TValue v) {
	TValue oldv = NULL_TVALUE;
	TElem e{k,v};
	flag = nullptr;
	root = insert_rec(root, e);
	if(flag != nullptr){
	    oldv = flag->info.second;
	    flag->info.second = e.second;
	}
	flag = nullptr;
	return oldv;
}
//worst,best,total: O(height); this is always the same no matter how it is called
TValue SortedMap::search(TKey k) const {
    return search_rec(root, k);
}
//worst: O(height!)
// best: O(height)
// total: O(height!);
// actually i dont know how this will behave when it has to recursively remove elements with 2 children each, i guess
// it would become something like O(height!) at worst
TValue SortedMap::remove(TKey k) {
	TValue oldv = NULL_TVALUE;
	oldv = remove_rec(root, k);
    if(oldv != NULL_TVALUE) length--;
	return oldv;
}
//worst,best,total: ϴ(1); this is always the same no matter how it is called
int SortedMap::size() const {
	return this->length;
}
//worst,best,total: ϴ(1); this is always the same no matter how it is called
bool SortedMap::isEmpty() const {
	if(length == 0) return true;
	return false;
}

SMIterator SortedMap::iterator() const {
	return SMIterator(*this);
}
//worst,best,total: O(length); this is always the same no matter how it is called
SortedMap::~SortedMap() {
    delete_rec(root);
}

// PRIVATE
//worst,best,total: ϴ(1); this is always the same no matter how it is called
Node* SortedMap::initNode(TElem pair) {
    Node* x = new Node;
    x->info=pair;
    x->left = nullptr;
    x->right = nullptr;
    return x;
}

//worst,best,total: O(height); this is always the same no matter how it is called
Node* SortedMap::insert_rec(Node *node, TElem e) {
    if(node == nullptr){
        node = initNode(e);
        length++;
    }
    else if(node->info.first == e.first){
        flag = node;
        return node;
    }
    else if(!r(node->info.first, e.first)){
        node->left = insert_rec(node->left, e);
    }
    else{
        node->right = insert_rec(node->right, e);
    }
    return node;
}
//worst,best,total: O(height); this is always the same no matter how it is called
TValue SortedMap::search_rec(Node *node, TKey k) const{
    if(node == nullptr){
        return NULL_TVALUE;
    }
    else{
        if(node->info.first == k){
            return node->info.second;
        }
        else if(!r(node->info.first, k)){
            return search_rec(node->left, k);
        }
        else{
            return search_rec(node->right, k);
        }
    }
}
//worst: O(height!)
// best: O(height)
// total: O(height!);
// actually i dont know how this will behave when it has to recursively remove elements with 2 children each, i guess
// it would become something like O(height!) at worst
TValue SortedMap::remove_rec(Node *node, TKey k) {
    if(node == nullptr){
        return NULL_TVALUE;
    }
    else if(node->info.first == k) {
        Node* p = parent(node);
        if (node->left != nullptr && node->right != nullptr){
            Node* m = maximum(node->left);
            TValue oldv = node->info.second;
            TElem placeholder = m->info;
            remove(m->info.first);
            node->info = placeholder;
            return oldv;
        }
        else if(node->left != nullptr ){
            if(p != nullptr){
                if(p->left == node){
                    p->left = node->left;
                }
                if(p->right == node){
                    p->right = node->left;
                }
            }
            else{
                root = node->left;
            }
            TValue oldv = node->info.second;
            delete node;
            node = nullptr;
            return oldv;
        }
        else if(node->right != nullptr){
            if(p != nullptr){
                if(p->left == node){
                    p->left = node->right;
                }
                if(p->right == node){
                    p->right = node->right;
                }
            }
            else{
                root = node->right;
            }
            TValue oldv = node->info.second;
            delete node;
            node = nullptr;
            return oldv;
        }
        else { // it has no children
            if(p != nullptr){
                if(p->left == node){
                    p->left = nullptr;
                }
                if(p->right == node){
                    p->right = nullptr;
                }
            }
            else{
                root = nullptr;
            }
            TValue oldv = node->info.second;
            delete node;
            node = nullptr;
            return oldv;
        }

    }
    else if(!r(node->info.first, k)){
        return remove_rec(node->left, k);
    }
    else{
        return remove_rec(node->right, k);
    }
}
//worst,best,total: O(height); this is always the same no matter how it is called
Node *SortedMap::parent(Node *node) {
    Node* c = root;
    if(c == node){
        return nullptr;
    }
    else{
        while(c != nullptr && c->left != node && c->right != node){
            if(!r(c->info.first, node->info.first)){
                c = c->left;
            }
            else{
                c = c->right;
            }
        }
        return c;
    }
}
//worst,best,total: O(height); this is always the same no matter how it is called
Node *SortedMap::maximum(Node *node) const{
    Node* current = node;
    while(current->right != nullptr){
        current = current->right;
    }
    return current;
}
//worst,best,total: O(height); this is always the same no matter how it is called
Node *SortedMap::minimum(Node* node) const{
    Node* current = node;
    while(current->left != nullptr){
        current = current->left;
    }
    return current;
}
//worst,best,total: O(length); this is always the same no matter how it is called
void SortedMap::delete_rec(Node *node) {
    if(length > 1){
        if(node->right != nullptr)
            delete_rec(node->right);
        if(node->left != nullptr)
            delete_rec(node->left);
    }
    delete node;
}

//returns a vector with all the keys from the sortedmap
//worst,best,total: O(length); this is always the same no matter how it is called
std::vector<TKey> SortedMap::keySet() const {
    std::vector<TKey> v;
    SMIterator it = this->iterator();
    it.first();
    while(it.valid()){
        v.push_back(it.getCurrent().first);
        it.next();
    }
    return v;
}

