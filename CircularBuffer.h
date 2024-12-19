#include <stdint.h>  // For fixed-width integer types like uint32_t

template <typename T, unsigned int Size>
class CircularBuffer {
private:
    T buffer[Size];
    unsigned int head = 0;
    unsigned int tail = 0;
    unsigned int count = 0;

public:
    void push(T item) {
        if (count < Size) {
            buffer[head] = item;
            head = (head + 1) % Size;
            ++count;
        }
    }

    T pop() {
        if (count > 0) {
            T item = buffer[tail];
            tail = (tail + 1) % Size;
            --count;
            return item;
        }
        return T();
    }

    bool isEmpty() const {
        return count == 0;
    }

    bool isFull() const {
        return count == Size;
    }

    unsigned int size() const {
        return count;
    }

    void clear() {
        head = 0;
        tail = 0;
        count = 0;
    }
};
