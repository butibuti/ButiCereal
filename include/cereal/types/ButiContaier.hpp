
#ifndef CEREAL_TYPES_BUTICONTAINER_HPP_
#define CEREAL_TYPES_BUTICONTAINER_HPP_

#include "ButiCereal/include/cereal/cereal.hpp"
#include "ButiMemorySystem/ButiMemorySystem/ButiList.h"

namespace cereal
{
template <class Archive, class T> inline
typename std::enable_if<traits::is_output_serializable<BinaryData<T>, Archive>::value
    && std::is_arithmetic<T>::value && !std::is_same<T, bool>::value, void>::type
    CEREAL_SAVE_FUNCTION_NAME(Archive& ar, ButiEngine::List<T> const& list)
{
    ar(make_size_tag(static_cast<size_type>(list.GetSize())));
    ar(binary_data(list.data(), list.GetSize() * sizeof(T)));
}

template <class Archive, class T> inline
typename std::enable_if<traits::is_input_serializable<BinaryData<T>, Archive>::value
    && std::is_arithmetic<T>::value && !std::is_same<T, bool>::value, void>::type
    CEREAL_LOAD_FUNCTION_NAME(Archive& ar, ButiEngine::List<T>& list)
{
    size_type listSize;
    ar(make_size_tag(listSize));

    list.Resize(static_cast<std::size_t>(listSize));
    ar(binary_data(list.data(), static_cast<std::size_t>(listSize) * sizeof(T)));
}

template <class Archive, class T> inline
typename std::enable_if<(!traits::is_output_serializable<BinaryData<T>, Archive>::value
    || !std::is_arithmetic<T>::value) && !std::is_same<T, bool>::value, void>::type
    CEREAL_SAVE_FUNCTION_NAME(Archive& ar, ButiEngine::List<T> const& list)
{
    ar(make_size_tag(static_cast<size_type>(list.GetSize()))); 
    for (auto&& v : list)
        ar(v);
}

template <class Archive, class T> inline
typename std::enable_if<(!traits::is_input_serializable<BinaryData<T>, Archive>::value
    || !std::is_arithmetic<T>::value) && !std::is_same<T, bool>::value, void>::type
    CEREAL_LOAD_FUNCTION_NAME(Archive& ar, ButiEngine::List<T>& list)
{
    size_type size;
    ar(make_size_tag(size));

    list.Resize(static_cast<std::size_t>(size));
    for (auto&& v : list)
        ar(v);
}

} // namespace cereal

#endif // CEREAL_TYPES_BUTICONTAINER_HPP_