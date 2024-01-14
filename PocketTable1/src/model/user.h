#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

class User {
public:
  enum Role {
    ProductManager, CompanyManager
  };

  User(string _login, string _password, Role _role);

  static string role_to_string(Role role);
  static Role string_to_role(string);

  string login, password;
  Role role;
};

#define CURRENT_USER Singleton<string>::instance()

#endif // USER_H
