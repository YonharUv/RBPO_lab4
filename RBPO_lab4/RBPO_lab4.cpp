#include <iostream>
#include <initializer_list>
#include <iterator>

template <typename T>
class QueueBasedOnArray
{
public:
    using Iterator = T*;
    // Конструктор по умолчанию
    QueueBasedOnArray();

    // Явный конструктор преобразования
    explicit QueueBasedOnArray(unsigned size);

    // Конструктор копирования
    QueueBasedOnArray(const QueueBasedOnArray& other);

    // Конструктор перемещения
    QueueBasedOnArray(QueueBasedOnArray&& other);

    // Конструктор с использованием списка инициализации
    QueueBasedOnArray(std::initializer_list<int> list);

    // Деструктор
    ~QueueBasedOnArray();

    // Итераторы для работы с элементами очереди
    QueueBasedOnArray::Iterator begin();
    const QueueBasedOnArray::Iterator begin() const;
    QueueBasedOnArray::Iterator end();
    const QueueBasedOnArray::Iterator end() const;

    // Перегрузка оператора индексации для доступа к элементам очереди
    const int& operator[](int index) const;
    int& operator[](int index);

    // Перегрузка оператора присваивания для копирования очереди
    QueueBasedOnArray& operator=(const QueueBasedOnArray& other);

    // Перегрузка оператора присваивания для перемещения очереди
    QueueBasedOnArray& operator=(QueueBasedOnArray&& other);

    // Перегрузка оператора присваивания для списка инициализации
    QueueBasedOnArray& operator=(std::initializer_list<int> ilist);

    int GetSize();
    bool Push(const T& element);
    bool Pop(T& element);
    bool Peek(T& element);


private:
    T* arr; // Указатель на массив
    int count; // Текущее количество элементов в очереди
};

template <typename T>
QueueBasedOnArray<T>::QueueBasedOnArray() : arr(nullptr), count(0){}

template <typename T>
QueueBasedOnArray<T>::QueueBasedOnArray(unsigned size) : count(size)
{
    arr = new int[size];
}

template <typename T>
QueueBasedOnArray<T>::~QueueBasedOnArray()
{
    if (count > 0)
        delete[] arr;
}

template <typename T>
QueueBasedOnArray<T>::QueueBasedOnArray(const QueueBasedOnArray& other)
{
    arr = new int[other.count];
    count = other.count;
    for (int i = 0; i < count; ++i)
    {
        arr[i] = other.arr[i];
    }
}

template <typename T>
QueueBasedOnArray<T>::QueueBasedOnArray(QueueBasedOnArray&& other)
{
    arr = other.arr;
    count = other.count;
    other.arr = nullptr;
}

template <typename T>
QueueBasedOnArray<T>::QueueBasedOnArray(std::initializer_list<int> ilist)
    : arr(new int[ilist.size()]), count(ilist.size())
{
    int i = 0;
    for (const auto& element : ilist)
    {
        arr[i++] = element;
    }
}

template <typename T>
int QueueBasedOnArray<T>::GetSize()
{
    return count;
}

template <typename T>
typename QueueBasedOnArray<T>::Iterator QueueBasedOnArray<T>::begin()
{
    return Iterator(arr);
}
template <typename T>
const typename QueueBasedOnArray<T>::Iterator QueueBasedOnArray<T>::begin() const
{
    return Iterator(arr);
}

template <typename T>
typename QueueBasedOnArray<T>::Iterator QueueBasedOnArray<T>::end()
{
    return Iterator(arr + count);
}

template <typename T>
const typename QueueBasedOnArray<T>::Iterator QueueBasedOnArray<T>::end() const
{
    return Iterator(arr + count);
}

// Перегрузка оператора индексации для доступа к элементам очереди
const int& QueueBasedOnArray<int>::operator[](int index) const
{
    return arr[index];
}

int& QueueBasedOnArray<int>::operator[](int index)
{
    return arr[index];
}

// Перегрузка оператора присваивания для копирования очереди
template <typename T>
QueueBasedOnArray<T>& QueueBasedOnArray<T>::operator=(const QueueBasedOnArray& other)
{
    if (this != &other)
    {
        delete[] arr;
        arr = new int[other.count];
        count = other.count;
        for (int i = 0; i < count; ++i)
        {
            arr[i] = other.arr[i];
        }
    }
    return *this;
}

// Перегрузка оператора присваивания для перемещения очереди
template <typename T>
QueueBasedOnArray<T>& QueueBasedOnArray<T>::operator=(QueueBasedOnArray&& other)
{
    if (this != &other)
    {
        delete[] arr;
        arr = other.arr;
        count = other.count;
        other.arr = nullptr;
    }
    return *this;
}

// Перегрузка оператора присваивания для списка инициализации
template <typename T>
QueueBasedOnArray<T>& QueueBasedOnArray<T>::operator=(std::initializer_list<int> ilist)
{
    delete[] arr;
    arr = new int[ilist.size()];
    count = ilist.size();
    int i = 0;
    for (const auto& element : ilist)
    {
        arr[i++] = element;
    }
    return *this;
}

// Метод для добавления элемента в конец очереди
bool QueueBasedOnArray<int>::Push(const int& element)
{
    int* arr2 = arr;

    try {
        arr = new int[count + 1];

        for (int i = 0; i < count; i++)
            arr[i] = arr2[i];

        arr[count] = element;

        count++;

        if (count > 1)
            delete[] arr2;

        return true;
    }

    catch(...)
    {
        // Вернуть старый указатель на arr
        arr = arr2;

        return false;
    }
}

// Метод для удаления элемента из начала очереди
bool QueueBasedOnArray<int>::Pop(int& element)
{
    if (count == 0)
        return false;

    else {
        int* arr2;

        element = arr[0];

        arr2 = new int[count - 1];

        count--;

        for (int i = 0; i < count; i++)
            arr2[i] = arr[i + 1];

        if (count > 0)
            delete[] arr;

        arr = arr2;

        return true;
    }
}

// Метод для просмотра элемента в начале очереди, не удаляя его

bool QueueBasedOnArray<int>::Peek(int& element)
{
    if (count > 0)
    {
        element = arr[0];
        return true;
    }else
        return false;
}

int main()
{
    // Тестирование конструкторов
    QueueBasedOnArray<int> queue1;  // Конструктор по умолчанию
    QueueBasedOnArray<int> queue2(5);  // Явный конструктор преобразования
    QueueBasedOnArray<int> queue3 = { 1, 2, 3, 4, 5 };  // Конструктор с использованием списка инициализации

    // Тестирование оператора присваивания для списка инициализации
    queue1 = { 10, 20, 30 };

    // Тестирование методов Push, Pop, Peek
    queue1.Push(100);
    queue1.Push(200);
    queue1.Push(300);

    int poppedElement;
    if (queue1.Pop(poppedElement))
        std::cout << "Popped element: " << poppedElement << std::endl;
    else
        std::cout << "Queue is empty, cannot pop." << std::endl;

    int peekedElement;
    if (queue1.Peek(peekedElement))
        std::cout << "Peeked element: " << peekedElement << std::endl;
    else
        std::cout << "Queue is empty, cannot peek." << std::endl;

    // Вывод размеров очередей
    std::cout << "Size of queue1: " << queue1.GetSize() << std::endl;
    std::cout << "Size of queue2: " << queue2.GetSize() << std::endl;
    std::cout << "Size of queue3: " << queue3.GetSize() << std::endl;

    // Вывод элементов очереди с использованием итераторов
    std::cout << "Elements of queue1: ";
    for (int* i1 = queue1.begin(); i1 != queue1.end(); ++i1)
        std::cout << *i1 << " ";
    std::cout << std::endl;

    std::cout << "Elements of queue3: ";
    for (int* i3 = queue3.begin(); i3 != queue3.end(); ++i3)
        std::cout << *i3 << " ";
    std::cout << std::endl;

    return 0;
}