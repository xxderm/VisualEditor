#pragma once
#include <cstdint>
#include <memory>

namespace VisualEditor {

    template<class T>
    class Storage final {
    public:
        Storage() {
            mData = new T[1];
            mCapacity = 1;
        }
        Storage(Storage& other) {
            if (this != &other) {
                delete mData;
                mData = new T[other.mCapacity];
                for (uint32_t i = 0; i < other.Size(); ++i)
                    mData[i] = other.mData[i];
                mCurrent = other.mCurrent;
                mCapacity = other.mCapacity;
            }
        }
        Storage(Storage&& other) {
            if (this != &other) {
                delete[] mData;
                mData = other.mData;
                mCurrent = other.mCurrent;
                mCapacity = other.mCapacity;
                other.mData = nullptr;
                other.mCurrent = other.mCapacity = 0;
            }
        }
        ~Storage() { delete[] mData; }
        Storage& operator=(Storage& other) {
            if (this != &other) {
                delete[] mData;
                mData = new T[other.mCapacity];
                for (uint32_t i = 0; i < other.Size(); ++i)
                    mData[i] = other.mData[i];
                mCurrent = other.mCurrent;
                mCapacity = other.mCapacity;
            }
            return *this;
        }
        Storage& operator=(Storage&& other) noexcept {
            if (this != &other) {
                delete[] mData;
                mData = other.mData;
                mCurrent = other.mCurrent;
                mCapacity = other.mCapacity;
                other.mData = nullptr;
                other.mCurrent = other.mCapacity = 0;
            }
            return *this;
        }
        void Replace(uint32_t index, const T& value) {
            // TODO: Удалить объект и заменить
            mData[index] = value;
        }
        void Push(const T& value) {
            if (mCurrent >= mCapacity) Expand();
            mData[mCurrent++] = value;
        }
        void Remove(uint32_t index) {
            for (uint32_t i = index + 1; i < mCurrent; ++i)
                mData[i - 1] = mData[i];
            --mCurrent;
        }
        T& Back() const { return mData[mCurrent - 1]; }
        T& operator[](uint32_t index) { return mData[index]; }
        T& At(uint32_t index) { return mData[index]; }
        const T& operator[](uint32_t index) const { return mData[index]; }
        bool Empty() const { return mCurrent == 0; }
        uint32_t Size() const noexcept { return mCurrent; }
        uint32_t Capacity() const noexcept { return mCapacity; }
    private:
        void Expand() {
            mCapacity *= 2;
            T* tmp = mData;
            mData = new T[mCapacity];
            for (uint32_t i = 0; i < mCurrent; ++i)
                mData[i] = tmp[i];
            delete[] tmp;
        }
    private:
        T* mData = nullptr;
        uint32_t mCapacity{};
        uint32_t mCurrent{};
    };

}