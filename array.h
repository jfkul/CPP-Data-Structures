//
// Created by jk on 4/22/26.
//

#ifndef DATA_STRUCTURES_ARRAY_H
#define DATA_STRUCTURES_ARRAY_H

#include <memory>
#include <initializer_list>
#include <cstddef>

template <typename T>
class Array
{
private:
    T* m_array {};
    size_t m_size {};
public:
    Array(std::initializer_list<T> list)
        : m_array { new T[list.size()] }
    , m_size { list.size() }
    {
        size_t i = 0;
        for (const T& value : list)
        {
            m_array[i++] = value;
        }
    }
    ~Array()
    {
        delete[] m_array;
    }

    Array(const Array& arr)
        : m_array { new T[arr.m_size] }
    , m_size { arr.m_size }
    {
        for (size_t i = 0; i < arr.m_size; ++i)
        {
            m_array[i] = arr.m_array[i];
        }
    }

    Array(Array&& arr)
        : m_array { arr.m_array }
    , m_size { arr.m_size }
    {
        arr.m_size = 0;
        arr.m_array = nullptr;
    }

    Array& operator=(const Array& arr)
    {
        if (&arr == this)
            return *this;

        delete[] m_array;

        m_size = arr.m_size;

        if (arr.m_array)
        {
            m_array = new T[arr.m_size];

            for (size_t i = 0; i < arr.m_size; ++i)
            {
                m_array[i] = arr.m_array[i];
            }
        }
        else
        {
            m_array = nullptr;
        }

        return *this;
    }

    Array& operator=(Array&& arr) noexcept
    {
        if (&arr == this)
            return *this;

        delete[] m_array;

        m_size = arr.m_size;
        m_array = arr.m_array;

        arr.m_size = 0;
        arr.m_array = nullptr;

        return *this;
    }

    T& operator[](size_t index)
    {
        return m_array[index];
    }

    const T& operator[](size_t index) const
    {
        return m_array[index];
    }

    size_t size() const { return m_size; }
};

#endif //DATA_STRUCTURES_ARRAY_H
