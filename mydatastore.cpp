#include <sstream>
#include <iomanip>
#include <string>
#include <set>
#include <map>
#include <vector>
#include "datastore.h"
#include "mydatastore.h"
#include "util.h"

MyDataStore::MyDataStore(){
    
}

MyDataStore::~MyDataStore()
{
  for (Product* p : store) {
        delete p;
    }

    for (User* u : users) {
        delete u;
    }

}

void MyDataStore::addProduct(Product *p)
{
    // std::cout << searchKeys.size() << std::endl;
    // std::cout << store.size() << std::endl;
    // std::cout << users.size() << std::endl;
    std::set<std::string> keywords = p->keywords();
    std::set<std::string>::iterator itr;
    for(std::string keyword: keywords){
        searchKeys[keyword].insert(p);
        keywordBank.insert(keyword);
    }
    store.insert(p);
    
}

void MyDataStore::addUser(User *u)
{
    users.insert(u);
}

std::vector<Product *> MyDataStore::search(std::vector<std::string> &terms, int type)
{
    std::vector<std::string>::iterator itr;
    std::vector<Product *> validProductsV;
    std::set<Product *> validProducts;

    if(type == 0){
        validProducts = store;
    }
    for (itr = terms.begin(); itr != terms.end(); itr++){
        std::set<std::string> t = parseStringToWords(convToLower(*itr));
        std::string currentTerm;
        if(t.begin() != t.end()){
            currentTerm =  *(t.begin());
        }

        if(searchKeys[currentTerm].size() >= 1){
            if(type == 0){
                validProducts = setIntersection(validProducts, searchKeys[currentTerm]);
            } else if(type == 1){
                validProducts = setUnion(validProducts, searchKeys[currentTerm]);
            }
        }

    }

    std::set<Product *>::iterator validItr;

    for (validItr = validProducts.begin(); validItr != validProducts.end(); validItr++){
        validProductsV.push_back(*validItr);
    }
    return validProductsV;
}

void MyDataStore::dump(std::ostream &ofile)
{
    ofile << "<products>\n" << std::fixed << std::setprecision(2);

    std::set<Product *>::iterator productItr;
    for(productItr = store.begin(); productItr != store.end(); productItr++){
        (*productItr)->dump(ofile);
    }
    
    ofile << "</products>\n<users>\n";

    std::set<User *>::iterator userItr;
    for(userItr = users.begin(); userItr != users.end(); userItr++){
        (*userItr)->dump(ofile);
    }

    ofile << "</users>" << std::endl;



}

std::set<User*>&  MyDataStore::getUsers(){
    return users;
}


void MyDataStore::purchaseItem(User* u){


    std::vector<Product*>::iterator itr;
    itr = carts[u].begin();
    while(itr != carts[u].end()){
        if((*itr)->getPrice() < u->getBalance() & (*itr)->getQty() > 0){
            std::vector<Product*>::iterator temp = itr;
            (*itr)->subtractQty(1);
            u->deductAmount((*itr)->getPrice());
            itr = carts[u].erase(temp);
        } else {
            itr++;
        }
    }
}

void MyDataStore::addToCart(User* u, Product* p){
    carts[u].push_back(p);
    return;
}

void MyDataStore::viewCart(User* u){
    // std::cout << getName() << "'s cart:" << std::endl;
    size_t i = 1;
    std::vector<Product*>::iterator itr;
    for(itr =  carts[u].begin(); itr !=  carts[u].end(); itr++){
        std::cout << "Item " << i << std::endl;
        std::cout << (*itr)->displayString() << std::endl;
        i++;
    }
}