#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <vector>

using namespace std;
class Order
{
public:
  string date;
  string email;
  vector<int> product_ids;
};

#endif // ORDER_H
