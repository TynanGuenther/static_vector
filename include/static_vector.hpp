#pragma once
#include <cstddef>
#include <memory>
#include <new>
#include <type_traits>
#include <utility>

template<typename T, std::size_t Capacity>
class StaticVector {
    public:
	StaticVector() noexcept : size_(0) {}

	~StaticVector() {
	    clear();
	}

	StaticVector(const StaticVector& other) {
	    copy_from(other);
	}

	StaticVector& operator=(const StaticVector& other) {
	    if(this != &other) {
		clear();
		copy_from(other);
	    }
	    return *this;
	}

	StaticVector(StaticVector&& other) noexcept {
	    move_from(std::move(other));
	}

	StaticVector& operator=(StaticVector&& other) noexcept {
	    if (this != &other) {
		clear();
		copy_from(std::move(other));
	    }
	    return *this;
	}

	template<typename... Args>
	    bool emplace_back(Args&&... args) {
		if (size_ >= Capacity)
		    return false;

		new (data_ptr(size_)) T(std::forward<Args>(args)...);
		++size_;
		return true;
	}

	bool pop_back() {
	    if (size_ == 0) {
		return false;
	    }

	    --size_;
	    data_ptr(size_)->~T();
	    return true;
	}

	T& operator[](std::size_t index) {
	    return *data_ptr(index);
	}

	const T& operator[](std::size_t index) const {
	    return *data_ptr(index);
	}

	std::size_t size() const noexcept {
	    return size_;
	}

	constexpr std::size_t capacity() const noexcept {
	    return Capacity;
	}

	void clear() noexcept {
	    while (size_ > 0) {
		pop_back();
	    }
	}
    private:
	alignas(T) unsigned char storage_[sizeof(T) * Capacity];
	std::size_t size_;

	T* data_ptr(std::size_t index) {
	    return std::launder(reinterpret_cast<T*>(&storage_[index * sizeof(T)]));
	}

	const T* data_ptr(std::size_t index) const {
	    return std::launder(reinterpret_cast<const T*>(&storage_[index * sizeof(T)]));
	}

	void copy_from(const StaticVector& other) {
	    for (std::size_t i = 0; i < other.size_; ++i) {
		emplace_back(other[i]);
	    }
	}

	void move_from(StaticVector&& other) {
	    for (std::size_t i = 0; i < other.size_; ++i) {
		emplace_back(std::move(other[i]));
	    }
	    other.clear();
	}
};
