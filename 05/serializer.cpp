#include "serializer.h"

Serializer::Serializer(std::ostream& out): out_(out) {

}

template <class... ArgsT>
Error Serializer::process(ArgsT... args) {
    for (int i=0; )
}


template <class T>
Error Serializer::save(T& object) {
    return NoError;
}

template <class... ArgsT>
Error Serializer::operator()(ArgsT... args) {
    return process(args...);
}