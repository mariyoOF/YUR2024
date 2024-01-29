#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <vector>
using namespace std;

class Order { //класс для работы с заказом
public:
  string date;
  vector<int> product_ids;
};

#endif // ORDER_H
