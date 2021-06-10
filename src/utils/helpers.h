#ifndef HELPERS_H
#define HELPERS_H

template<typename Base, typename T>
inline bool instanceof(const T* ptr) {
    return dynamic_cast<const Base*>(ptr) != nullptr;
}


#endif // HELPERS_H
