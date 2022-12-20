#pragma once

#include "CHorizontalPiece.h"
#include "CTruenoPiece.h"
#include "CCornerPiece.h"
#include "CKiszanerPiece.h"
#include "CSquarePiece.h"

#include "CWinds.h"

#include <array>
#include <deque>

class CTetrisGame
{
public:
	static const std::size_t WIDTH = 7;

	using piece_sequence = std::array<std::reference_wrapper<ATetrisPiece>, 5>;
	using rocks_row = std::array<bool, WIDTH>;
	using rocks = std::deque<std::pair<std::size_t, rocks_row>>;

	explicit CTetrisGame( const CWinds& aWinds, const std::size_t& aNumGames );

	void Play( const std::size_t& aNumGames );

	const CWinds::winds& GetWinds() const;
	std::size_t GetHeight() const;

private:
	void AddPieceToRocks( const ATetrisPiece& aPiece );

	CHorizontalPiece mHorizontalPiece;
	CTruenoPiece mTruenoPiece;
	CCornerPiece mCornerPiece;
	CKiszanerPiece mKiszanerPiece;
	CSquarePiece mSquarePiece;
	piece_sequence mPieceSequence;

	const CWinds::winds mWinds;
	const std::size_t mRightBorder = WIDTH + 1;
	rocks mRocks;
};