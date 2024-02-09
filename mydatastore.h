#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <vector>
#include <map>
#include "product.h"
#include "user.h"
#include "datastore.h"




class MyDataStore : public DataStore {
public:
        
    MyDataStore();
    ~MyDataStore();

    void addProduct(Product* p);

    void addUser(User* u);

    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    std::set<User*> & getUsers();
    
    void dump(std::ostream& ofile);



private:
    std::set<Product*> store;
    std::set<User*> users;
    std::map<std::string, std::set<Product*>> searchKeys;
    std::set<std::string> keywordBank;
};

#endif