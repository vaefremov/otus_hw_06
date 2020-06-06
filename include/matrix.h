#pragma once
#include <map>
#include <array>

namespace OTUS
{

template<typename T, T DEF, size_t N_DIM = 2>
class Matrix
{
    public:

    template<size_t DIM>
    struct helper_index
    {
        helper_index(Matrix& m, std::array<size_t, N_DIM>& ind): m_m{m}, m_ind(ind) {}
        helper_index<DIM+1> operator[](size_t j)
        {
            m_ind[DIM] = j;
            return helper_index<DIM+1>(m_m, m_ind);
        }
        Matrix& m_m;
        std::array<size_t, N_DIM>& m_ind;
    };

    template<>
    struct helper_index<N_DIM>
    {
        helper_index(Matrix& m, std::array<size_t, N_DIM>& ind): m_m{m}, m_ind{ind} {}
        helper_index<N_DIM>& operator= (T val) 
        {
            m_m.put(val, m_ind);
            return *this;
        }
        operator T()
        {
            return m_m.get(m_ind);
        }
        Matrix& m_m;
        std::array<size_t, N_DIM>& m_ind;
    };

    class m_iterator
    {
        public:
            using map_iterator_t = typename std::map<std::array<size_t, N_DIM>, T>::iterator;

            m_iterator(map_iterator_t it): m_mit(it) {}
            
            auto& operator++()
            {
                m_mit++;
                return *this;
            }
            
            auto operator*()
            {
                return *m_mit;
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

    T const& get(std::array<size_t, N_DIM> const& ind) const
    {
        auto it = m_map.find(ind);
        if(it == m_map.end())
        {
            return m_default;
        }
        return it->second;
    }
    
    void put(T val, std::array<size_t, N_DIM> const& ind)
    {
        if(val == m_default)
        {
            m_map.erase(ind);
            return;
        }
        m_map[ind] = val;
    }

    helper_index<1> operator[](size_t i)
    {   
        m_cur_index[0] = i;
        return helper_index<1>(*this, m_cur_index);
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

    std::map<std::array<size_t, N_DIM>, T> m_map;
    
    T m_default = DEF;
    std::array<size_t, N_DIM> m_cur_index;
};

}
