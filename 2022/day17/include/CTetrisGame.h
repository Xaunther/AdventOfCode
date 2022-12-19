#pragma once

#include "CHorizontalPiece.h"
#include "CTruenoPiece.h"
#include "CCornerPiece.h"
#include "CKiszanerPiece.h"
#include "CSquarePiece.h"

#include "CWinds.h"

#include <array>
#include <map>

class CTetrisGame
{
public:
	using piece_sequence = std::array<std::reference_wrapper<ATetrisPiece>, 5>;
	using rocks_row = std::array<bool, 7>;
	using rocks = std::map<std::size_t, rocks_row, std::greater<std::size_t>>;

	explicit CTetrisGame( const CWinds& aWinds, const std::size_t& aNumGames );

	void Play( const std::size_t& aNumGames );

	const CWinds::winds& GetWinds() const;
	std::size_t GetHeight() const;

private:
	CHorizontalPiece mHorizontalPiece;
	CTruenoPiece mTruenoPiece;
	CCornerPiece mCornerPiece;
	CKiszanerPiece mKiszanerPiece;
	CSquarePiece mSquarePiece;
	piece_sequence mPieceSequence;

	const CWinds::winds mWinds;
	const std::size_t mRightBorder = 8;
	rocks mRocks;
};