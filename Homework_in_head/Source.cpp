#include <iostream>
#include <vector>

class A {
public:
	virtual ~A() {}	// добавляем виртуальный деструктор от утечки памяти (вроде так)
	virtual void foo(std::vector<int>& vec) = 0;
};

class B : public A {
public:
	void foo(std::vector<int>& vec) override {
		std::cout << "foo function" << std::endl;
		vec.erase(vec.begin());
	}
};

// Что можно сделать с объявлением foo, чтобы v имело другое количество элементов ?// Наверное в параметрах функции убрать амперсант, тогда вектор будет копироваться и удалять копию первого элемента

int main() {

	A* b = new B();
	std::vector<int> v = { 1,2,3 }; // остается два элемента 2 и 3, потому что в функции единичка удаляется методом erase (первый элемент - begin)
	b->foo(v);
	delete b;	// объект нужно удалить, потому как это указатель на класс А, чтобы не засорял память
}