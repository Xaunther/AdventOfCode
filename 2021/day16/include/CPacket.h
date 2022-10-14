#ifndef C_PACKET_H
#define C_PACKET_H

#include <deque>
#include <istream>
#include <optional>
#include <vector>

class CPacket
{
public:
	using binary_sequence = std::deque<bool>;

	class COperator
	{
	public:
		using length_type_id = bool;
		using packets = std::vector<CPacket>;

		COperator( binary_sequence& aBinarySequence );

		std::size_t SumVersions() const;
		const packets& GetPackets() const;

	private:
		length_type_id mLengthTypeID;
		packets mPackets;
	};

	using version = unsigned short;
	using type_id = unsigned short;
	using literal_value = std::optional<std::size_t>;
	using optional_operator = std::optional<COperator>;

	explicit CPacket() = default;
	explicit CPacket( binary_sequence& aBinarySequence );

	std::size_t SumVersions() const;
	std::size_t Operate() const;

	friend std::istream& operator>>( std::istream& aInput, CPacket& aPacket );

private:
	version mVersion;
	type_id mTypeID;
	literal_value mLiteralValue;
	optional_operator mOperator;
};

#endif // C_PACKET_H