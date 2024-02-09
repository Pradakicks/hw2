#include <sstream>
#include <iomanip>
#include "product.h"
#include "book.h"
#include "util.h"

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, const std::string ISBN, const std::string author) 
: Product(category, name, price, qty),  ISBN_(ISBN), author_(author) {
}

Book::~Book(){}

std::set<std::string> Book::keywords() const {
    std::set<std::string> name = parseStringToWords(name_);
    std::set<std::string> category = parseStringToWords(category_);
    std::set<std::string> ISBN = parseStringToWords(ISBN_);
    std::set<std::string> author = parseStringToWords(author_);
    std::set<std::string> keywords = setUnion(name, category);
    keywords = setUnion(keywords, ISBN);
    keywords = setUnion(keywords, author);
    return keywords;
}


std::string Book::displayString() const {
    std::stringstream buffer;
    buffer << name_ << std::endl;
    buffer << "Author: " << author_ << " ISBN: " << ISBN_ << std::endl;
    buffer << price_ << " " << qty_ << " left.";
    return buffer.str();
}

void Book::dump(std::ostream& os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << ISBN_  << "\n" << author_  << endl;
}