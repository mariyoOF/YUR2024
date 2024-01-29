#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
using namespace std;

class Product { //класс для работы с данным товара
public:
  int id; //ключ-номер типа
  string name; //название
  string article; // артикл
  int cost; //цена
  int kind; //сорт(тип продукта)
  string expiry_date; //годен до
  string receipt_date; //дата завоза
};
#endif // PRODUCT_H
