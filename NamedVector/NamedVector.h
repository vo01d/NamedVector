#ifndef _NAMEDVECTOR_H_
#define _NAMEDVECTOR_H_

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

template <typename _Ty, class _Alloc = std::allocator<std::pair<_Ty, std::string>>>
class NamedVector {
public:
    using data_type = _Ty;
    using data_reference = data_type&;
    using data_const_reference = const data_type&;

    using name_type = std::string;
    using name_type_reference = name_type&;
    using name_type_const_reference = const name_type&;
private:
    using named_vector = std::vector<std::pair<data_type, name_type>, _Alloc>;
    using named_vector_shared_ptr = std::shared_ptr<named_vector>;
public:
    using value_type = named_vector::value_type;

    using allocator_type = named_vector::allocator_type;

    using size_type = named_vector::size_type;
    using difference_type = named_vector::difference_type;

    using reference = named_vector::reference;
    using const_reference = named_vector::const_reference;
    using pointer = named_vector::pointer;
    using const_pointer = named_vector::const_pointer;

    using iterator = named_vector::iterator;
    using const_iterator = named_vector::const_iterator;
    using reverse_iterator = named_vector::reverse_iterator;
    using const_reverse_iterator = named_vector::const_reverse_iterator;

    NamedVector() : m_namedVector(std::make_shared<named_vector>()) {
    }

    NamedVector(const NamedVector& other) : m_namedVector(other.m_namedVector) {
    }

    ~NamedVector() noexcept {
    }

    reference operator[](const int index) {
        if (index >= size()) {
            throw std::out_of_range("Index is out of range");
        }

        return (*m_namedVector)[index];
    }

    const_reference operator[](const int index) const {
        if (index >= size()) {
            throw std::out_of_range("Index is out of range");
        }

        return (*m_namedVector)[index];
    }

    data_reference operator[](name_type_const_reference name) {
        const auto iter = std::find_if(begin(), end(),
            [&name](const_reference pair) {
                return name == pair.second;
            });
        if (iter == end()) {
            throw std::invalid_argument(name + " is not found in the NamedVector");
        }

        return iter->first;
    }

    data_const_reference operator[](name_type_const_reference name) const {
        const auto iter = std::find_if(begin(), end(),
            [&name](const_reference pair) {
                return name == pair.second;
            });
        if (iter == end()) {
            throw std::invalid_argument(name + " is not found in the NamedVector");
        }

        return iter->first;
    }

    void push_back(data_const_reference obj, name_type_const_reference name) {
        copyIfNotUnique();

        m_namedVector->emplace_back(obj, name);
    }

    void reserve(size_type newCapacity) {
        m_namedVector->reserve(newCapacity);
    }

    void clear() {
        m_namedVector->clear();
    }

    bool empty() const {
        return m_namedVector->empty();
    }

    size_type size() const {
        return m_namedVector->size();
    }

    size_type capacity() const {
        return m_namedVector->capacity();
    }

    iterator begin() {
        return m_namedVector->begin();
    }

    const_iterator begin() const {
        return m_namedVector->begin();
    }

    iterator end() {
        return m_namedVector->end();
    }

    const_iterator end() const {
        return m_namedVector->end();
    }

    reverse_iterator rbegin() {
        return m_namedVector->rbegin();
    }

    const_reverse_iterator rbegin() const {
        return m_namedVector->rbegin();
    }

    reverse_iterator rend() {
        return m_namedVector->rend();
    }

    const_reverse_iterator rend() const {
        return m_namedVector->rend();
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
        if (m_namedVector.use_count() > 1) {
            m_namedVector = std::make_shared<named_vector>(*m_namedVector);
        }
    }

    named_vector_shared_ptr m_namedVector;
};

#endif 