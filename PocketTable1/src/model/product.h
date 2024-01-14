#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
using namespace std;

class Product {
public:
  int id;
  string name;
  string article;
  int cost;
  int kind;
  string expiry_date;
  string receipt_date;
};
#endif // PRODUCT_H
