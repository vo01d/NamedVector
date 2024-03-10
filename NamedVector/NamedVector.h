#ifndef _NAMEDVECTOR_H_
#define _NAMEDVECTOR_H_

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

template <typename _Ty>
class NamedVector {
public:
    using value_type = _Ty;
    using value_type_reference = value_type&;
    using value_type_const_reference = const value_type&;

    using name_type = std::string;
    using name_type_reference = name_type&;
    using name_type_const_reference = const name_type&;

    using data_type = std::pair<value_type, name_type>;
private:
    using data = std::vector<data_type>;
    using data_ptr = std::shared_ptr<data>;
public:
    using size_type = data::size_type;
    using difference_type = data::difference_type;

    using reference = data_type&;
    using const_reference = const data_type&;

    using pointer = data_type*;
    using const_pointer = const data_type*;

    using iterator = data::iterator;
    using const_iterator = data::const_iterator;
    using reverse_iterator = data::reverse_iterator;
    using const_reverse_iterator = data::const_reverse_iterator;

    NamedVector() : m_data(std::make_shared<data>()) {
    }

    NamedVector(const NamedVector& other) : m_data(other.m_data) {
    }

    ~NamedVector() noexcept {
    }

    reference operator[](int index) {
        if (index >= size()) {
            throw std::out_of_range("Index is out of range");
        }

        return (*m_data)[index];
    }

    const_reference operator[](int index) const {
        if (index >= size()) {
            throw std::out_of_range("Index is out of range");
        }

        return (*m_data)[index];
    }

    value_type_reference operator[](name_type_const_reference name) {
        const auto iter = std::find_if(begin(), end(),
            [&name](const_reference pair) {
                return name == pair.second;
            });
        if (iter == end()) {
            throw std::invalid_argument(name + " is not found in the NamedVector");
        }

        return iter->first;
    }

    value_type_const_reference operator[](name_type_const_reference name) const {
        const auto iter = std::find_if(begin(), end(),
            [&name](const_reference pair) {
                return name == pair.second;
            });
        if (iter == end()) {
            throw std::invalid_argument(name + " is not found in the NamedVector");
        }

        return iter->first;
    }

    void push_back(value_type_const_reference obj, name_type_const_reference name) {
        copyIfNotUnique();

        m_data->emplace_back(obj, name);
    }

    void reserve(size_type newCapacity) {
        m_data->reserve(newCapacity);
    }

    void clear() {
        m_data->clear();
    }

    bool empty() const {
        return m_data->empty();
    }

    size_type size() const {
        return m_data->size();
    }

    size_type capacity() const {
        return m_data->capacity();
    }

    iterator begin() {
        return m_data->begin();
    }

    const_iterator begin() const {
        return m_data->begin();
    }

    iterator end() {
        return m_data->end();
    }

    const_iterator end() const {
        return m_data->end();
    }

    reverse_iterator rbegin() {
        return m_data->rbegin();
    }

    const_reverse_iterator rbegin() const {
        return m_data->rbegin();
    }

    reverse_iterator rend() {
        return m_data->rend();
    }

    const_reverse_iterator rend() const {
        return m_data->rend();
    }

    const_iterator cbegin() const {
        return begin();
    }

    const_iterator cend() const {
        return end();
    }

    const_reverse_iterator crbegin() const {
        return rbegin();
    }

    const_reverse_iterator crend() const {
        return rend();
    }
private:
    void copyIfNotUnique() {
        if (m_data.use_count() > 1) {
            m_data = std::make_shared<data>(*m_data);
        }
    }

    data_ptr m_data;
};

#endif 