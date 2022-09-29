#pragma once
#include <iostream>
using namespace std;

template<typename T>
class Array {
	T* arr;
	int size;
	int bound;
	int grow;

public:
	Array();
	Array(int size);
	Array(const Array& obj);
	~Array();

	void Add(T item);
	void FreeExtra();
	void RemoveAll();
	bool IsEmpty();

	void SetSize(int size, int grow);
	int GetSize();

	void InsertAt(int index, int kol, T x);
	void RemoveAt(int index, int kol);

	int GetBound();
	int GetUpperBound(int x);

	void Append(Array<T>& obj);

	void SetAt(int index, T item);
	T GetAt(int index);

	T& GetData();

	Array& operator=(const Array& obj);
	T& operator[](int index);

	void Random();
	void Print();
};

template<typename T>
Array<T>::Array() {
	grow = 1;
	size = 0;
	bound = 0;
	arr = nullptr;
}

template<typename T>
Array<T>::Array(int size) {
	this->size = size;
	grow = 1;
	bound = 0;
	arr = new T[size];
}

template<typename T>
Array<T>::Array(const Array& obj) {
	grow = obj.grow;
	size = obj.size;
	bound = obj.bound;
	this->~Array();
	arr = new T[size + 1];
	for (int i = 0; i < size; i++) {
		arr[i] = obj.arr[i];
	}
}

template<typename T>
Array<T>::~Array() {
	delete[] arr;
}

template <typename T>
void Array<T>::Random() {
	srand(time(0));
	for (int i = 0; i < size; i++) {
		arr[i] = rand() % 100;
	}
}

template<typename T>
void Array<T>::Add(T item) {
	if (bound == 0) {
		T* array = new T[size];
		for (int i = 0; i < size; i++) {
			array[i] = arr[i];
		}
		if (arr != nullptr) {
			this->~Array();
		}
		arr = new T[size + grow];
		bound = (grow - 1);
		for (int i = 0; i < size; i++) {
			arr[i] = array[i];
		}
		delete[] array;
		arr[size] = item;
		size++;
	}
	else {
		arr[size] = item;
		size++;
		bound--;
	}
}

template<typename T>
void Array<T>::FreeExtra() {
	T* array = new T[size];
	for (int i = 0; i < size; i++) {
		array[i] = arr[i];
	}
	if (arr != nullptr) {
		this->~Array();
	}
	arr = new T[size];
	for (int i = 0; i < size; i++) {
		arr[i] = array[i];
	}
	delete[] array;
}

template<typename T>
void Array<T>::RemoveAll() {
	for (int i = 0; i < size; i++) {
		arr[i] = 0;
	}
	size = 0;
}

template<typename T>
bool Array<T>::IsEmpty() {
	if (size == 0) {
		return true;
	}
	else {
		return false;
	}
}

template <typename T>
void Array<T>::Print() {
	for (int i = 0; i < this->size; ++i) {
		cout << "{" << i << "} = " << arr[i] << endl;
	}
}

template<typename T>
void Array<T>::SetSize(int size, int grow) {
	T* array = new T[size];
	for (int i = 0; i < size; i++) {
		array[i] = arr[i];
	}
	if (arr != nullptr) {
		this->~Array();
	}
	arr = new T[size];
	for (int i = 0; i < size; i++) {
		arr[i] = array[i];
	}
	delete[] array;
	bound = size - this->size;
	if (bound < 0) {
		bound = 0;
	}
	this->size = size - bound;
	this->grow = grow;
}

template<typename T>
int Array<T>::GetSize() {
	return size;
}

template<typename T>
void Array<T>::SetAt(int index, T item) {
	if (index < size) {
		arr[index] = item;
	}
	else {
		cout << "Wrong";
	}
}

template<typename T>
T Array<T>::GetAt(int index) {
	return arr[index];
}

template<typename T>
void Array<T>::InsertAt(int index, int kol, T x) {
	int new_size = size + kol;
	T* ptr = &x;
	T* array = new T[size];
	for (int i = 0; i < size; i++) {
		array[i] = arr[i];
	}

	if (bound >= kol) {
		for (int i = index; i < index + kol; i++) {
			arr[i] = *ptr++;
		}
		for (int i = index + kol, j = index; i < new_size; i++, j++) {
			arr[i] = array[j];
		}
		bound -= kol;
	}

	else {
		while ((new_size) < bound) {
			new_size += (size + grow);
		}
		if (arr != nullptr) {
			this->~Array();
		}
		arr = new T[new_size];
		for (int i = 0; i < index; i++) {
			arr[i] = array[i];
		}
		for (int i = index; i < index + kol; i++) {
			arr[i] = *ptr++;
		}
		for (int i = index + kol, k = index; i < new_size; i++, k++) {
			arr[i] = array[k];
		}
		bound = grow - 1;
	}
	size = new_size;
}

template<class T>
void Array<T>::RemoveAt(int index, int kol) {
	T* array = new T[size - kol];
	for (int i = 0; i < size - kol; i++) {
		if (i >= index) {
			array[i] = arr[i + kol];
		}
		else {
			array[i] = arr[i];
		}
	}
	if (arr != nullptr) {
		this->~Array();
	}
	arr = new T[size - kol];
	size -= kol;
	for (int i = 0; i < size; i++) {
		arr[i] = array[i];
	}
	delete[] array;
	bound = 0;
}

template<typename T>
int Array<T>::GetBound() {
	return bound;
}

template<typename T>
T& Array<T>::GetData() {
	return arr;
}

template<typename T>
int Array<T>::GetUpperBound(int x) {
	int index = bound;
	return index;
}

template<typename T>
void Array<T>::Append(Array<T>& obj) {
	T* array = new T[size + 1];
	for (int i = 0; i < size; i++) {
		array[i] = arr[i];
	}
	if (arr != nullptr) {
		this->~Array();
	}

	arr = new T[size + obj.size + 1 + bound];
	for (int i = 0, j = 0, k = 0; i < size + obj.size; i++) {
		if (i < size) {
			arr[i] = array[j];
			j++;
		}
		else {
			arr[i] = obj.arr[k];
			k++;
		}
	}
	size += obj.size;
	delete[] array;
}

template<typename T>
Array<T>& Array<T>::operator=(const Array& obj) {
	size = obj.size;
	bound = obj.bound;
	if (arr != nullptr) {
		this->~Array();
	}
	arr = new T[size + 1];
	for (int i = 0; i < size; i++) {
		arr[i] = obj.arr[i];
	}
	return *this;
}

template<typename T>
T& Array<T>::operator[](int index) {
	return arr[index];
}
