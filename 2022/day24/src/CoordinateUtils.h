#pragma once

#include <utility>

template <typename T> std::pair<T, T> operator+( const std::pair<T, T>& aLHS, const std::pair<T, T>& aRHS )
{
	return { aLHS.first + aRHS.first, aLHS.second + aRHS.second };
}

template <typename T> std::pair<T, T> operator%( const std::pair<T, T>& aLHS, const std::pair<T, T>& aRHS )
{
	return { aLHS.first % aRHS.first, aLHS.second % aRHS.second };
}