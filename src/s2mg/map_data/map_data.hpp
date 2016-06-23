#pragma once

#include "map_dimensions.hpp"
#include "handles.hpp"
#include "n_handles.hpp"

#include <vector>

namespace s2mg {

template<typename HandleType, typename T>
class map_data
{
public:
    using this_type = map_data<HandleType, T>;
    using container_type = std::vector<T>;

    // Container typedefs
    using value_type             = typename container_type::value_type;
    using allocator_type         = typename container_type::allocator_type;
    using size_type              = typename container_type::size_type;
    using difference_type        = typename container_type::difference_type;
    using reference              = typename container_type::reference;
    using const_reference        = typename container_type::const_reference;
    using pointer                = typename container_type::pointer;
    using const_pointer          = typename container_type::const_pointer;
    using iterator               = typename container_type::iterator;
    using const_iterator         = typename container_type::const_iterator;
    using reverse_iterator       = typename container_type::reverse_iterator;
    using const_reverse_iterator = typename container_type::const_reverse_iterator;

public:
    explicit map_data(const map_dimensions& _dimensions) :
        data_(n_handles<HandleType>(_dimensions))
    {
    }

    map_data() = delete;
    map_data(const this_type&) = default;
    map_data(this_type&&) = default;
    map_data& operator=(const this_type&) = default;
    map_data& operator=(this_type&&) = default;

    void assign(const value_type& _value)
    {
        return data_.assign(data_.size(), _value);
    }

    template<typename InputIt>
    void assign(InputIt _first, InputIt _last)
    {
        // assert(std::distance(_fist, _last) == data_.size());
        data_.assign(_first, _last);
    }

    void assign(std::initializer_list<value_type> _ilist)
    {
        assert(_ilist.size() == data_.size());
        data_.assign(_ilist);
    }

    reference at(const HandleType& _handle)
    {
        return data_.at(_handle.index());
    }

    const_reference at(const HandleType& _handle) const
    {
        return data_.at(_handle.index());
    }

    reference operator[](const HandleType& _handle)
    {
        return data_[_handle.index()];
    }

    const_reference operator[](const HandleType& _handle) const
    {
        return data_[_handle.index()];
    }

    reference front()
    {
        return data_.front();
    }

    const_reference front() const
    {
        return data_.front();
    }

    reference back()
    {
        return data_.back();
    }

    const_reference back() const
    {
        return data_.back();
    }

    pointer data()
    {
        return data_.data();
    }

    const_pointer data() const
    {
        return data_.data();
    }

    iterator        begin()       { return data_.begin();  }
    const_iterator  begin() const { return data_.begin();  }
    const_iterator cbegin() const { return data_.cbegin(); }

    reverse_iterator        rbegin()       { return data_.rbegin();  }
    const_reverse_iterator  rbegin() const { return data_.rbegin();  }
    const_reverse_iterator crbegin() const { return data_.crbegin(); }

    iterator        end()       { return data_.end();  }
    const_iterator  end() const { return data_.end();  }
    const_iterator cend() const { return data_.cend(); }

    reverse_iterator        rend()       { return data_.rend();  }
    const_reverse_iterator  rend() const { return data_.rend();  }
    const_reverse_iterator crend() const { return data_.crend(); }

    bool empty() const
    {
        return data_.empty();
    }

    size_type size() const
    {
        return data_.size();
    }

    size_type max_size() const
    {
        return data_.size();
    }

    size_type capacity() const
    {
        return data_.size();
    }

    void swap(this_type& _rhs)
    {
        data_.swap(_rhs.data_);
    }

    bool operator==(const this_type& _rhs) const { return data_ == _rhs.data_; }
    bool operator!=(const this_type& _rhs) const { return data_ != _rhs.data_; }
    bool operator< (const this_type& _rhs) const { return data_ <  _rhs.data_; }
    bool operator<=(const this_type& _rhs) const { return data_ <= _rhs.data_; }
    bool operator> (const this_type& _rhs) const { return data_ >  _rhs.data_; }
    bool operator>=(const this_type& _rhs) const { return data_ >= _rhs.data_; }

private:
    container_type data_;
};

template<typename T> using vertex_data   = map_data<vertex_handle,   T>;
template<typename T> using face_data     = map_data<face_handle,     T>;
template<typename T> using halfedge_data = map_data<halfedge_handle, T>;
template<typename T> using edge_data     = map_data<edge_handle,     T>;

}
