#ifndef USER_H
#define USER_H

#include <string>

using namespace std; //упрощение работы с кодом, с помощью единого прописания пространства имен

class User { //класс для работы с пользователями
public:
  enum Role {
    ProductManager, CompanyManager //Конструктор Менеджера-Товаров и Менеджер-Магазина
  };

  User(string _login, string _password, Role _role); //прописываем параметры для объекта "Пользователь"

  static string role_to_string(Role role);
  static Role string_to_role(string);

  string login, password;
  Role role;
};

#define CURRENT_USER Singleton<string>::instance()
#endif // USER_H
