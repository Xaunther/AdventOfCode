#ifndef C_PAPER_H
#define C_PAPER_H

#include <deque>
#include <istream>
#include <ostream>
#include <set>

class CPaper
{
public:
	enum E_FOLD_TYPE
	{
		X,
		Y
	};

	using coordinates = std::pair<size_t, size_t>;
	using dots = std::set<coordinates>;
	using fold = std::pair<E_FOLD_TYPE, size_t>;
	using folds = std::deque<fold>;

	friend std::istream& operator>>( std::istream& aInput, CPaper& aPaper );
	friend std::ostream& operator<<( std::ostream& aOutput, const CPaper& aPaper );

	const dots& GetDots() const;
	const folds& GetFolds() const;

	void Fold();
	void FoldAll();

	coordinates CalculateSize() const;

private:
	dots mDots;
	folds mFolds;
};

#endif // C_PAPER_H