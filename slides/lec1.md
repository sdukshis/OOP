## Стандарты языка C++

* C++98
* C++03
* C++11
* C++14 <-- Наш выбор!
* C++17


## Компиляторы

* [GCC](https://gcc.gnu.org/)
    * 5.4 и выше
* [Clang](http://clang.llvm.org/)
    * 3.8 и выше
* [Visual Studio](https://www.visualstudio.com/)
    * 2015 Update 2 и выше
* [Intel C++ compiler](https://software.intel.com/en-us/c-compilers)


## Среды разработки

* IDE
    * Visual Studio
    * CLion
    * QtCreator
    * ваш любимый текстовый редактор


## Hello, world

```cpp
#include <iostream>

int main() {
    cout << "Hello, world!\n";
}
```


## Типы данных

* логические
    * **bool**
* символьные
    * **char**
    * wchar_t
    * char16_t (C++11)
    * char32_t (C++11)
* целочисленные
    * short
    * **int**
    * long
    * long long (C++11)
* с плавающей точкой
    * float
    * **double**
    * long double



## Библиотека ввода/вывода
Заголовочный файл
```cpp
#include <iostream>
```
```cpp
std::cout << "Hello, " << "world!" << "\n"
std::cout << 4 << " times " << 5 << " will be " << 4*5;
```
```
int age;
std::cout << "Enter your age: ";
std::cin >> age;
```


## Управляющие конструкции

```cpp
if (x < 0) {
    x = -x;
}

if (x > 0) {
    sign = 1;
} else if (x < 0) {
    sign = -1;
} else {
    sign = 0;
}
```


## Управляющие конструкции

```cpp

switch(x) {
    case 0: //...
    case 1: //...
    ...
    default://...
}
```


## Управляющие конструкции

```cpp

for (int i = 0; i < n; ++i) {
    //...
}
```

Range-based for loop (C++11)
```cpp
for (int i in {1, 2, 3, 4, 5}) {
    //...
}
```


## Управляющие конструкции

```cpp

while (x > 0) {
    //...
    continue;
}
```
```cpp
do {
    if (error) {
        break;
    }
} while (x > 0);
```


## Функции

```cpp
int abs(int x) {
    return x >= 0 ? x : -x;
}
```
Перегрузка функций
```cpp
double abs(double x) {
    return x >= 0 ? x : -x;
}
```
Значения параметров по умолчанию
```cpp
bool is_equal(double lhs, double rhs, double eps = 1e-15) {
    return abs(lhs - rhs) <= eps;
}

is_equal(1.0, 1.00000001);
is_eqial(1.0, 1.00000001, 1e-7);
```
