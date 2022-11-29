#pragma once
#include "pch.hpp"

namespace VisualEditor {
    template<class T>
    class Storage final {
    public:
        struct Iterator final {
            using IterCat = std::forward_iterator_tag;
            using DiffType = std::ptrdiff_t;
            using ValueType = T;
            using Ptr = T*;
            using Ref = T&;

            Iterator(Ptr other) : mPtr(other) {}

            Ref operator*() const { return *mPtr; }

            Ptr operator->() { return mPtr; }

            Iterator& operator++() {
                mPtr++;
                return *this;
            }

            Iterator operator++(int) {
                Iterator temp = *this;
                ++(*this);
                return temp;
            }

            friend bool operator==(const Iterator& lhs, const Iterator& rhs) {
                return lhs.mPtr == rhs.mPtr;
            }

            friend bool operator!=(const Iterator& lhs, const Iterator& rhs) {
                return lhs.mPtr != rhs.mPtr;
            }
        private:
            Ptr mPtr;
        };

        Iterator Begin() {
            return Iterator(&mValue[0]);
        }

        Iterator End() {
            return Iterator(&mValue[mSize]);
        }

        Storage<T>& operator=(const Storage<T>& other);

        T& operator[](const uint32_t index) { return mValue[index]; }

        T& At(const uint32_t index) { return mValue[index]; }

        Storage() = default;

        Storage(uint32_t capacity);

        Storage(const Storage<T>& other);

        void Clean();

        void Push(const T& value);

        void Pop(const uint32_t& index);

        void Pop(const uint32_t& begin, const uint32_t& end);

        uint32_t GetSize() const noexcept { return mSize; }

        uint32_t GetCapacity() const noexcept { return mCapacity; }

        ~Storage();
    private:
        void Realloc();
    private:
        T* mValue = nullptr;
        uint32_t mSize = 0;
        uint32_t mCapacity = 0;
    };

    template<class T>
    Storage<T>::Storage(uint32_t capacity) {
        mValue = new T[capacity];
        mCapacity = capacity;
    }

    template<class T>
    Storage<T>::Storage(const Storage<T> &other) {
        *this = other;
    }

    template<class T>
    void Storage<T>::Push(const T &value) {
        if (mSize >= mCapacity)
            Realloc();
        mValue[mSize] = value;
        ++mSize;
    }

    template<class T>
    void Storage<T>::Pop(const uint32_t &index) {
        if (mSize != 0) {
            Storage<T> temp(mSize - 1);
            for (uint32_t i = 0; i < mSize; ++i) {
                if (i == index) continue;
                temp.Push(mValue[i]);
            }
            *this = temp;
        }
    }

    template<class T>
    Storage<T>::~Storage() {
        this->Clean();
    }

    template<class T>
    void Storage<T>::Clean() {
        if (nullptr != mValue) {
            delete[] mValue;
            mValue = nullptr;
        }
        mSize = 0;
        mCapacity = 0;
    }

    template<class T>
    void Storage<T>::Realloc() {
        ++mCapacity;
        auto oldValues = new T[mCapacity];
        const auto oldSize = this->mSize;
        const auto byteSize = sizeof(T) * mSize;
        memcpy_s(oldValues, byteSize, mValue, byteSize);
        *this = Storage(mCapacity);
        mSize = oldSize;
        memcpy_s(mValue, byteSize, oldValues, byteSize);
        delete[] oldValues;
    }

    template<class T>
    Storage<T> &Storage<T>::operator=(const Storage<T> &other) {
        this->Clean();
        mSize = other.mSize;
        mCapacity = other.mCapacity;
        mValue = new T[mCapacity];
        const auto& byteSize = sizeof(T) * mSize;
        memcpy_s(mValue, byteSize, other.mValue, byteSize);
        return *this;
    }

    template<class T>
    void Storage<T>::Pop(const uint32_t &begin, const uint32_t &end) {
        for (uint32_t i = begin; i < end; ++i)
            this->Pop(i);
    }
}