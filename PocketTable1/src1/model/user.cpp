#include "user.h"

User::User(string _login, string _password, Role _role) //авторизация
  : login(_login), password(_password), role(_role) {
}

string User::role_to_string(Role role) {
  if (role == ProductManager) {
    return "Product";
  }
  return "Company";
}

User::Role User::string_to_role(string str) {
  if (str == "Product")
    return Role::ProductManager;
  if (str == "Company")
    return Role::CompanyManager;
  throw string("wrong role");
}
