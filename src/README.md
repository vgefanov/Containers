# Текущие задачи

## Other

1. полное покрытие unit-тестами методов контейнерных классов c помощью библиотеки GTest
2. если будет время, привести все в соответствие с Google Style гайдом
3. логика работы стандартной библиотеки шаблонов (STL) (в части проверок, работы с памятью и поведения в нештатных ситуациях)

## List

* переделать итератор
    * стандартный итератор через ссылку
    * operator* Нет проверки, если ptr == nullptr
    * ++/-- нормальная работа
    * переход итератора через начало и конец
* константный итератор должен быть как отдельный класс реализован
* утечки в конструкторе переноса
* проверить покрытие
* В void list<T>::merge(list& other) не рассмотрен вариант, если list& other пустой, а так же не предусмотрены варианты когда первый и второй список не отсортированы. К примеру список1: 1 3 5 и список2: 2 4 6, тогда результат будет 1 2 3 4 5 6, это при варианте когда оба списка отсортированы. А в данном методе просто значения помещаются в конец списка
* можно было просто вызвать std::swap(pos1.ptr_->data_, pos2.ptr_->data_), а создали новый метод swap_elements(pos1, pos2);, в котором данная строка и реализована.
* В методах - Нет проверки пустой список или нет. Если он пустой, тогда не надо ничего делать. Из реализации, я понимаю, что будут удалены все элементы из списка перед данной нодой, которые равны значению в данной ноде. В оригинале удаляется предыдущая нода, если она совпадает с текущей. К примеру было: 2 3 2 2 3 4 2, будет 2 3 2 3 4 2

## Set

* константный итератор должен быть как отдельный класс реализован
* Проверка RBT https://www.cs.usfca.edu/~galles/visualization/RedBlack.html
* проверить покрытие
* в дереве set присутствует баласт в виде переменно типа int для value, лучше bool

## Multiset

* константный итератор должен быть как отдельный класс реализован
* проверить покрытие
* vector заменить на свой

## Map

* константный итератор должен быть как отдельный класс реализован
* в map имя метода end() совпадает с именем переменной в конструкторе итератора

## Array

* разнести по разным файлам
* константный итератор должен быть как отдельный класс реализован
* в array в операторе переноса не учитывается размер переносимого массива, что может привести к выходу за пределы выделенной памяти

# Vector

* разнести по разным файлам
* константный итератор должен быть как отдельный класс реализован

# Stack/Queue

# Основные стандартные контейнерные классы языка С++:

- ~~последовательные - для нахождения элемента необходимо последовательно просмотреть весь контейнер~~
    - ~~`list` (список)~~ **Рома**
    - ~~`queue` (очередь)~~ **Слава**
    - ~~`stack` (стек)~~ **Слава**
    - ~~`vector` (вектор)~~ **Слава**
    - ~~`array`~~ **Ира**

- ~~ассоциативные - для нахождения элемента достаточно обратиться по ассоциированному с значением ключу~~
    - ~~`map`~~ (словарь) **Ира**
    - ~~`set` (множество)~~ **Рома**
    - ~~`multiset`~~ **Рома**