#ifndef C_CAVERNS_H
#define C_CAVERNS_H

#include <istream>
#include <map>
#include <set>
#include <string>

class CCaverns
{
public:
	using cavern = std::string;
	using caverns = std::set<cavern>;
	using cavern_map = std::map<cavern, caverns>;

	friend std::istream& operator>>( std::istream& aInput, CCaverns& aCaverns );

	const cavern_map& GetCavernMap() const;

private:
	cavern_map mCavernMap;
};

#endif // C_CAVERNS_H