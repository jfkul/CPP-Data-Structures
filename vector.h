//
// Created by jk on 4/22/26.
//

#ifndef DATA_STRUCTURES_VECTOR_H
#define DATA_STRUCTURES_VECTOR_H

#include <memory>
#include <initializer_list>
#include <cstddef>

constexpr size_t kResizeMultiplier { 2 };

// std::vector style type
template <typename T>
class Vector
{
private:
    T* m_data {};
    size_t m_size {};
    size_t m_capacity {};

public:
    Vector(std::initializer_list<T> list)
        : m_data { new T[list.size()] }
        , m_size { list.size() }
        , m_capacity { list.size() }
    {
        size_t i { 0 };
        for (auto it { list.begin() }; it != list.end(); ++it)
        {
            m_data[i++] = *it;
        }
    }

    ~Vector()
    {
        delete[] m_data;
    }

    Vector(const Vector& vec)
        : m_data { new T[vec.m_capacity] }
        , m_size { vec.m_size }
        , m_capacity { vec.m_capacity }
    {
        size_t i { 0 };
        for (auto it { vec.begin() }; it != vec.end(); ++it)
        {
            m_data[i++] = *it;
        }
    }

    Vector (Vector&& vec) noexcept
        : m_data { vec.m_data }
        , m_size { vec.m_size }
        , m_capacity { vec.m_capacity }
    {
        vec.m_data = nullptr;
        vec.m_size = 0;
        vec.m_capacity = 0;
    }

    Vector& operator=(const Vector& vec)
    {
        if (&vec == this)
            return *this;

        delete[] m_data;

        m_size = vec.m_size;
        m_capacity = vec.m_capacity;

        m_data = new T[vec.m_capacity];

        size_t i { 0 };
        for (auto it { vec.begin() }; it != vec.end(); ++it)
        {
            m_data[i++] = *it;
        }

        return *this;
    }

    Vector& operator=(Vector&& vec) noexcept
    {
        if (&vec == this)
            return *this;

        delete[] m_data;

        m_data = vec.m_data;
        m_size = vec.m_size;
        m_capacity = vec.m_capacity;

        vec.m_data = nullptr;
        vec.m_size = 0;
        vec.m_capacity = 0;

        return *this;
    }

    T& operator[](size_t index)
    {
        return m_data[index];
    }
    const T& operator[] (size_t index) const
    {
        return m_data[index];
    }

    void resize(size_t newSize)
    {
        if (newSize == m_size)
        {
            return;
        }
        else if (newSize < m_size)
        {
            m_size = newSize;
        }
        else
        {
            if (newSize <= m_capacity)
            {
                m_size = newSize;
            }
            else
            {
                reserve(newSize);
                m_size = newSize;
            }
        }
    }

    void reserve(size_t newCapacity)
    {
        if (newCapacity > m_capacity)
        {
            T* newData = new T[newCapacity];
            for (size_t i { 0 }; i < m_size; ++i)
            {
                newData[i] = m_data[i];
            }

            delete[] m_data;

            m_data = newData;
            m_capacity = newCapacity;
        }
    }
    void push_back(const T& element)
    {
        size_t lastSize = m_size;

        if (m_size + 1 > m_capacity)
        {
            if (m_capacity * kResizeMultiplier > 0)
            {
                reserve(m_capacity * kResizeMultiplier);
            }
            else
                reserve(1);
        }
        resize(m_size + 1);
        m_data[lastSize] = element;
    }

    T* begin() { return m_data; }
    T* end() { return m_data + m_size; }
    const T* begin() const { return m_data; }
    const T* end() const { return m_data + m_size; }

    size_t size() const { return m_size; }
    size_t capacity() const { return m_capacity; }
};

#endif //DATA_STRUCTURES_VECTOR_H
