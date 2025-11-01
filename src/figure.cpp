#include "../include/figure.h"
#include <string_view>
#include <iostream>

std::ostream& operator<<(std::ostream& os, const Figure& figure) {
    os << figure.description << ":\n";
    figure.print(os);
    return os;
}

std::istream& operator>>(std::istream& is, Figure& figure) {
  figure.read(is);
  return is;
}

Figure::Figure(std::string_view desc) : description(desc) {}