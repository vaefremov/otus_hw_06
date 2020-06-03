#pragma once
#include <map>
#include <tuple>

namespace OTUS
{

template<typename T, int DEF>
class Matrix
{
    public:

    struct helper_2nd_index
    {
        helper_2nd_index(Matrix& m, size_t i, size_t j): m_m(m), m_i(i), m_j(j) {}
        helper_2nd_index& operator= (T val) 
        {
            m_m.put(m_i, m_j, val);
            return *this;
        }
        operator T()
        {
            return m_m.get(m_i, m_j);
        }
        Matrix& m_m;
        size_t m_i;
        size_t m_j;
    };

    struct helper_1st_index
    {
        helper_1st_index(Matrix& m, size_t i): m_m(m), m_i(i) {}
        helper_2nd_index operator[](size_t j)
        {
            return helper_2nd_index(m_m, m_i, j);
        }
        Matrix& m_m;
        size_t m_i;
    };

    class m_iterator
    {
        public:
            using map_iterator_t = typename std::map<std::pair<size_t, size_t>, T>::iterator;
            m_iterator(map_iterator_t it): m_mit(it) {}
            m_iterator& operator++()
            {
                m_mit++;
                return *this;
            }
            std::tuple<size_t, size_t, T> operator*()
            {
                return std::make_tuple(m_mit->first.first, m_mit->first.second, m_mit->second);
            }
            bool operator==(m_iterator const& other)
            {
                return m_mit == other.m_mit;
            }
            bool operator!=(m_iterator const& other)
            {
                return m_mit != other.m_mit;
            }
        private:
            map_iterator_t m_mit;
    };

    Matrix() = default;
    ~Matrix() = default;
    T const& get(size_t i, size_t j) const
    {
        auto it = m_map.find(std::pair(i,j));
        if(it == m_map.end())
        {
            return m_default;
        }
        return it->second;
    }
    
    void put(size_t i, size_t j, T val)
    {
        if(val == m_default)
        {
            m_map.erase(std::pair(i,j));
            return;
        }
        m_map[std::pair(i,j)] = val;
    }

    helper_1st_index operator[](size_t i)
    {
        return helper_1st_index(*this, i);
    }
    size_t size()
    {
        return m_map.size();
    }
    m_iterator begin()
    {
        return m_iterator(m_map.begin());
    }
    m_iterator end()
    {
        return m_iterator(m_map.end());
    }
    private:

    std::map<std::pair<size_t, size_t>, T> m_map;
    T m_default = DEF;
};

}
