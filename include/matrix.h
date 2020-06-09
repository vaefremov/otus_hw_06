#pragma once
#include <map>
#include <array>

namespace OTUS
{

template<typename T, T DEF, size_t N_DIM = 2>
class Matrix;


template<typename T, T DEF, size_t N_DIM, size_t DIM>
struct helper_index 
{
    helper_index(Matrix<T, DEF, N_DIM>* m, std::array<size_t, DIM>& ind): m_m{m}
    {
        std::copy(std::begin(ind), std::end(ind), std::begin(m_ind));
    }
    helper_index() = delete;
    helper_index(helper_index const&) = delete;
    helper_index(helper_index &&) = delete;
    helper_index& operator=(helper_index& other) = delete;
    helper_index<T, DEF, N_DIM, DIM+1> operator[](size_t j)
    {
        m_ind[DIM] = j;
        return helper_index<T, DEF, N_DIM, DIM+1>(m_m, m_ind);
    }
    Matrix<T, DEF, N_DIM>* m_m;
    /**
     * Partially-built set of indices.
     * 
     * Alternatively, we may keep the only copy of index set in the main object (i.e. Matrix)
     * and pass only the references to this global object. However, this design leads to strange
     * effects (see the matrix/indexes_interdependency test, this strange behaviour was mentionned
     * by Sergey Koltsov in his review).
     */
    std::array<size_t, DIM+1> m_ind;
};

template<typename T, T DEF, size_t N_DIM>
struct helper_index<T, DEF, N_DIM, N_DIM> 
{
    helper_index(Matrix<T, DEF, N_DIM>* m, std::array<size_t, N_DIM>& ind): m_m{m}, m_ind{ind} {}
    helper_index() = delete;
    helper_index(helper_index const&) = delete;
    helper_index(helper_index &&) = delete;
    helper_index& operator=(helper_index& other) = delete;
    helper_index<T, DEF, N_DIM, N_DIM>& operator= (T val) 
    {
        m_m->put(val, m_ind);
        return *this;
    }
    operator T()
    {
        return m_m->get(m_ind);
    }
    Matrix<T, DEF, N_DIM>* m_m;
    std::array<size_t, N_DIM> m_ind;
};


template<typename T, T DEF, size_t N_DIM >
class Matrix
{
    public:


    class m_iterator
    {
        public:
            using map_iterator_t = typename std::map<std::array<size_t, N_DIM>, T>::const_iterator;

            m_iterator(map_iterator_t it): m_mit{it} {}
            
            auto const& operator++()
            {
                m_mit++;
                return *this;
            }
            
            auto operator*() const
            {
                return *m_mit;
            }
            
            bool operator==(m_iterator const& other) const
            {
                return m_mit == other.m_mit;
            }
            
            bool operator!=(m_iterator const& other) const
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

    helper_index<T, DEF, N_DIM, 1> operator[](size_t i)
    {   
        std::array<size_t, 1> cur_index;
        cur_index[0] = i;
        return helper_index<T, DEF, N_DIM, 1>(this, cur_index);
    }
    size_t size() const
    {
        return m_map.size();
    }
    m_iterator begin() const
    {
        return m_iterator(m_map.cbegin());
    }
    m_iterator end() const
    {
        return m_iterator(m_map.cend());
    }
    private:

    std::map<std::array<size_t, N_DIM>, T> m_map;
    
    T m_default = DEF;
};

}
