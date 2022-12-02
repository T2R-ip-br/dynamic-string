// File: dynamic_string.h ( Заголовочный файл с определением класса dynamic_string )
// Version: 0.1
// Author: T2R-ip-br

#include <iostream>

class dynamic_string {

private:
    char * str;
    int size;

public:
    // Конструктор по умолчанию
    dynamic_string()
    {
        this->str = new char[1];
        this->size = 0;
    };

    // Конструктор принимающий символьную строку
    dynamic_string(const char * str)
    {
        this->size = strlen(str);
        this->str = new char[this->size + 1];
        for(int i = 0; i < this->size+1; i++) {
            this->str[i] = str[i];
        }
    }

    // Конструктор копирования
    dynamic_string(const dynamic_string & other)
    {
        this->size = other.size;
        this->str = new char[other.size];
        for(int i = 0; i < other.size+1; i++) {
            this->str[i] = other.str[i];
        }
    }

    // Перемещающий конструктор
    dynamic_string(dynamic_string && other)
    {
        this->str = other.str;
        this->size = other.size;
        other.str = nullptr;
        other.size = 0;
    }

    // Деструктор
    ~dynamic_string() {
        delete [] str;
    }

    // Функция определения длины строки
    static int strlen(const char * str)
    {
        int count = 0;
        int i = 0;
        while (str[i++] != '\0')
            count++;

        return count;
    }

    // Переопределение оператора <<
    friend std::ostream & operator << (std::ostream & os, const dynamic_string& str)
    {
        os << str.str;
        return os;
    }

    // Переопределение оператора >>
    friend std::istream & operator >> (std::istream & is, dynamic_string& str)
    {
        is >> str.str;
        str.size = strlen(str.str);
        return is;
    }

    // Переопределение оператора присваивания
    dynamic_string & operator = (const dynamic_string & other)
    {
        delete [] this->str;

        this->size = other.size;
        this->str = new char[size];
        for(int i = 0; i < this->size+1; i++) {
            this->str[i] = other.str[i];
        }

        return *this;
    }

    // Перемещающий оператор присваивания
    dynamic_string & operator = (dynamic_string && other)
    {
        delete [] this->str;

        this->str = other.str;
        this->size = other.size;
        other.str = nullptr;
        other.size = 0;

        return *this;
    }

    // Переопределение оператора сложения (внешняя функция)
    dynamic_string operator + (const dynamic_string & other);

    // Функция сравнения двух динамических строк
    int compareTo(const dynamic_string & other)
    {
        int length = (this->size < other.size) ? this->size : other.size;

        for (int i = 0; i < length+1; i++) {
            if (this->str[i] < other.str[i])
                return 1;
            else if (this->str[i] > other.str[i])
                return -1;
        }

        if (this->size < other.size)
            return 1;
        else if (this->size > other.size)
            return -1;
        else
            return 0;
    }

    // Возвращает длину строки
    int length() {
        return this->size;
    }
};

// Определение оператора сложения как внешния функция
dynamic_string dynamic_string::operator + (const dynamic_string & other)
{
    dynamic_string temp;
    temp.size = this->size + other.size;
    temp.str = new char[temp.size+1];

    int i = 0;
    for(i; i < this->size; i++) {
        temp.str[i] = this->str[i];
    }
    for(int t = 0; t < other.size+1; t++, i++) {
        temp.str[i] = other.str[t];
    }

    return temp;
}

