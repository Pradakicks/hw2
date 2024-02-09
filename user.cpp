#include "user.h"
#include "product.h"
#include <iomanip>
using namespace std;

User::User() : name_("unknown"), balance_(0.0), type_(1)
{

}
User::User(std::string name, double balance, int type) :
    name_(name), balance_(balance), type_(type)
{

}

User::~User()
{

}


std::string User::getName() const
{
    return name_;
}

double User::getBalance() const
{
    return balance_;
}

void User::deductAmount(double amt)
{
    balance_ -= amt;
}

void User::purchaseItem(){
    std::vector<Product*>::iterator itr;
    for(itr = cart.begin(); itr != cart.end(); itr++){
        if((*itr)->getPrice() < getBalance() & (*itr)->getQty() > 0){
            (*itr)->subtractQty(1);
            deductAmount((*itr)->getPrice());
            cart.erase(itr);
            // return; // break;
        }
    }
}

void User::addToCart(Product* p){
    cart.push_back(p);
    return;
}

void User::viewCart(){
    std::cout << getName() << "'s cart:" << std::endl;
    size_t i = 1;
    std::vector<Product*>::iterator itr;
    for(itr = cart.begin(); itr != cart.end(); itr++){
        std::cout << "Item #: " << i << "\n " << (*itr)->displayString() << std::endl;
        i++;
    }
}


void User::dump(std::ostream& os)
{
    os << name_ << " "  << balance_ << " " << type_ << endl;
}
