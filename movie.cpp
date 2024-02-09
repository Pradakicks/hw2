#include <sstream>
#include <iomanip>
#include "product.h"
#include "movie.h"
#include "util.h"

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating) 
: Product(category, name, price, qty),  genre_(genre), rating_(rating) {
}

Movie::~Movie(){}

std::set<std::string> Movie::keywords() const {
    std::set<std::string> name = parseStringToWords(name_);
    std::set<std::string> category = parseStringToWords(category_);
    std::set<std::string> genre = parseStringToWords(genre_);
    std::set<std::string> rating = parseStringToWords(rating_);
    std::set<std::string> keywords = setUnion(name, category);
    keywords = setUnion(keywords, genre);
    keywords = setUnion(keywords, rating);
    return keywords;
}


std::string Movie::displayString() const {
    std::stringstream buffer;
    buffer << name_ << std::endl;
    buffer << "genre: " << genre_ << " rating: " << rating_ << std::endl;
    buffer << price_ << " " << qty_ << " left.";
    return buffer.str();
}

void Movie::dump(std::ostream& os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_  << "\n" << rating_  << endl;
}