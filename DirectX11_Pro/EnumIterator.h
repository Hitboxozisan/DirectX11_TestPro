#pragma once

#include <type_traits>

template<typename T, T beginType, T endType>
class EnumIterator
{
public:
	EnumIterator() : currentVal(static_cast<unType>(beginType)) {};
	EnumIterator(const T& end) : currentVal(static_cast<unType>(end)) {};

	EnumIterator begin() const { return *this; }
	EnumIterator end()
	{
		static const EnumIterator itr = ++EnumIterator(endType);
		return itr;
	}

	T operator*() const { return static_cast<T>(currentVal); }

	EnumIterator operator++()
	{
		currentVal++;
		return *this;
	}

	bool operator!=(const EnumIterator& end) const { return currentVal != end.currentVal; }
private:
	// Šî–{int‚¾‚ª”O‚Ì‚½‚ß‰½‚É‚Å‚à‘Î‰ž‚Å‚«‚é‚æ‚¤‚ÉŠî’êŒ^‚ðŽæ“¾
	typedef typename std::underlying_type<T>::type unType;

	int currentVal;
};
