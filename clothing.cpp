#include <sstream>
#include <iomanip>
#include "product.h"
#include "clothing.h"
#include "util.h"

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand) 
: Product(category, name, price, qty),  size_(size), brand_(brand) {
}

Clothing::~Clothing(){}

std::set<std::string> Clothing::keywords() const {
    std::set<std::string> name = parseStringToWords(name_);
    std::set<std::string> category = parseStringToWords(category_);
    std::set<std::string> size = parseStringToWords(size_);
    std::set<std::string> brand = parseStringToWords(brand_);
    std::set<std::string> keywords = setUnion(name, category);
    keywords = setUnion(keywords, size);
    keywords = setUnion(keywords, brand);
    return keywords;
}


std::string Clothing::displayString() const {
    std::stringstream buffer;
    buffer << name_ << std::endl;
    buffer << "Size: " << size_ << " Brand: " << brand_ << std::endl;
    buffer << price_ << " " << qty_ << " left.";
    return buffer.str();
}

void Clothing::dump(std::ostream& os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_  << "\n" << brand_  << endl;
}