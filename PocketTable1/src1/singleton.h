//применяется для организации глобальной точки доступа к БД и для запоминания текущего пользователя
#ifndef SINGLETON_H
#define SINGLETON_H

#include <QObject>

template <class T>
class Singleton {
public:
  static T& instance() {
    static T instance;
    return instance;
  }

private:
  Singleton();
  ~Singleton();
  Singleton(const Singleton &);
  Singleton& operator=(const Singleton &);
};

#endif
