#include "BitSize.h"

#include <algorithm>
#include <limits>
#include <sstream>
#include <iomanip>
#include <cassert>

#define BITS_IN_BYTE 8.
#define BYTES_IN_KIBIBIT 128.
#define BYTES_IN_MEBIBIT 131072.
#define BYTES_IN_GIBIBIT 134217728.
#define BYTES_IN_TEBIBIT 137438953472.
#define BYTES_IN_PEBIBIT 140737488355328.5
#define BYTES_IN_KILOBIT 125.
#define BYTES_IN_MEGABIT 125000.
#define BYTES_IN_GIGABIT 125000000.
#define BYTES_IN_TERABIT 125000000000.
#define BYTES_IN_PETABIT 125000000000000.

namespace hvn3 {

	BitSize::BitSize(double bytes, BytePrefix prefix) :
			BitSize(bytes, prefix, prefix == BytePrefix::Binary ? ByteUnit::IEC : ByteUnit::Metric) {
	}
	BitSize::BitSize(double bytes, BytePrefix prefix, ByteUnit unit) {

		assert(unit != ByteUnit::IEC || prefix == BytePrefix::Binary);

		_bytes = RoundBytesToNearestBit(bytes);
		_unit = unit;
		_prefix = prefix;

	}

	double BitSize::Bits() const {

		return _bytes * BITS_IN_BYTE;

	}
	double BitSize::Bytes() const {

		return _bytes;

	}
	double BitSize::Kilobits() const {

		return Bytes() / BytesInKilobit(_prefix);

	}
	double BitSize::Megabits() const {

		return Bytes() / BytesInMegabit(_prefix);

	}
	double BitSize::Gigabits() const {

		return Bytes() / BytesInGigabit(_prefix);

	}
	double BitSize::Terabits() const {

		return Bytes() / BytesInTerabit(_prefix);

	}
	double BitSize::Petabits() const {

		return Bytes() / BytesInPetabit(_prefix);

	}

	std::string BitSize::LargestUnitSymbol() const {

		if ((std::abs)(Petabits()) >= 1.0)
			return PetabitSymbol(_unit);
		if ((std::abs)(Terabits()) >= 1.0)
			return TerabitSymbol(_unit);
		if ((std::abs)(Gigabits()) >= 1.0)
			return GigabitSymbol(_unit);
		if ((std::abs)(Megabits()) >= 1.0)
			return MegabitSymbol(_unit);
		if ((std::abs)(Kilobits()) >= 1.0)
			return KilobitSymbol(_unit);
		if ((std::abs)(Bytes()) >= 1.0)
			return ByteSymbol(_unit);

		return BitSymbol(_unit);

	}
	double BitSize::LargestUnitValue() const {

		if ((std::abs)(Petabits()) >= 1.0)
			return Petabits();
		if ((std::abs)(Terabits()) >= 1.0)
			return Terabits();
		if ((std::abs)(Gigabits()) >= 1.0)
			return Gigabits();
		if ((std::abs)(Megabits()) >= 1.0)
			return Megabits();
		if ((std::abs)(Kilobits()) >= 1.0)
			return Kilobits();
		if ((std::abs)(Bytes()) >= 1.0)
			return Bytes();

		return Bits();

	}

	void BitSize::AddBits(double size) {

		*this = BitSize(Bytes() + BitsInByte(_prefix) / size, _prefix, _unit);

	}
	void BitSize::AddBytes(double size) {

		*this = BitSize(Bytes() + size, _prefix, _unit);

	}
	void BitSize::AddKilobits(double size) {

		*this = BitSize(Bytes() + size * BytesInKilobit(_prefix), _prefix, _unit);

	}
	void BitSize::AddMegabits(double size) {

		*this = BitSize(Bytes() + size * BytesInMegabit(_prefix), _prefix, _unit);

	}
	void BitSize::AddGigabits(double size) {

		*this = BitSize(Bytes() + size * BytesInGigabit(_prefix), _prefix, _unit);

	}
	void BitSize::AddTerabits(double size) {

		*this = BitSize(Bytes() + size * BytesInTerabit(_prefix), _prefix, _unit);

	}
	void BitSize::AddPetabits(double size) {

		*this = BitSize(Bytes() + size * BytesInPetabit(_prefix), _prefix, _unit);

	}

	std::string BitSize::ToString(unsigned int precision) const {

		std::stringstream stream;

		stream << std::fixed << std::setprecision(precision) << LargestUnitValue() << ' ' << LargestUnitSymbol();

		return stream.str();

	}

	BitSize BitSize::MinValue() {

		return BitSize(0);

	}
	BitSize BitSize::MaxValue() {

		return BitSize(DBL_MAX);

	}

	BitSize BitSize::Parse(const std::string& string) {

		return Parse(string.c_str());

	}
	BitSize BitSize::Parse(const char* string) {

		BitSize object(0);

		if (!TryParse(string, object))
			throw std::invalid_argument("The input string was not in the correct format.");

		return object;

	}
	bool BitSize::TryParse(const std::string& string, BitSize& object) {

		return TryParse(string.c_str(), object);

	}
	bool BitSize::TryParse(const char* string, BitSize& object) {

		std::stringstream stream(string);
		double size = 0.0;
		std::string suffix;

		// Read the size and suffix.
		stream >> size >> suffix;

		// If this fails, return false.
		if (stream.fail())
			return false;

		// Compare the string to known suffixes.
		if (suffix == BitSymbol())
			object = BitSize::FromBits(size);
		else if (suffix == ByteSymbol())
			object = BitSize::FromBytes(size);

		else if (suffix == KilobitSymbol(ByteUnit::IEC))
			object = BitSize::FromKilobits(size, BytePrefix::Binary);
		else if (suffix == KilobitSymbol(ByteUnit::JEDEC))
			object = BitSize(size * BytesInKilobit(BytePrefix::Binary), BytePrefix::Binary, ByteUnit::JEDEC);
		else if (suffix == KilobitSymbol(ByteUnit::Metric))
			object = BitSize::FromKilobits(size, BytePrefix::Decimal);

		else if (suffix == MegabitSymbol(ByteUnit::IEC))
			object = BitSize::FromMegabits(size, BytePrefix::Binary);
		else if (suffix == MegabitSymbol(ByteUnit::Metric))
			object = BitSize::FromMegabits(size, BytePrefix::Decimal);

		else if (suffix == GigabitSymbol(ByteUnit::IEC))
			object = BitSize::FromGigabits(size, BytePrefix::Binary);
		else if (suffix == GigabitSymbol(ByteUnit::Metric))
			object = BitSize::FromGigabits(size, BytePrefix::Decimal);

		else if (suffix == TerabitSymbol(ByteUnit::IEC))
			object = BitSize::FromTerabits(size, BytePrefix::Binary);
		else if (suffix == TerabitSymbol(ByteUnit::Metric))
			object = BitSize::FromTerabits(size, BytePrefix::Decimal);

		else if (suffix == PetabitSymbol(ByteUnit::IEC))
			object = BitSize::FromPetabits(size, BytePrefix::Binary);
		else if (suffix == PetabitSymbol(ByteUnit::Metric))
			object = BitSize::FromPetabits(size, BytePrefix::Decimal);
		else
			object = BitSize::FromBits(size);

		return true;

	}

	BitSize BitSize::FromBits(double size, BytePrefix prefix) {

		return BitSize(size / BitsInByte(prefix), prefix);

	}
	BitSize BitSize::FromBytes(double size, BytePrefix prefix) {

		return BitSize(size, prefix);

	}
	BitSize BitSize::FromKilobits(double size, BytePrefix prefix) {

		return BitSize(size * BytesInKilobit(prefix), prefix);

	}
	BitSize BitSize::FromMegabits(double size, BytePrefix prefix) {

		return BitSize(size * BytesInMegabit(prefix), prefix);

	}
	BitSize BitSize::FromGigabits(double size, BytePrefix prefix) {

		return BitSize(size * BytesInGigabit(prefix), prefix);

	}
	BitSize BitSize::FromTerabits(double size, BytePrefix prefix) {

		return BitSize(size * BytesInTerabit(prefix), prefix);

	}
	BitSize BitSize::FromPetabits(double size, BytePrefix prefix) {

		return BitSize(size * BytesInPetabit(prefix), prefix);

	}

	double BitSize::BitsInByte(BytePrefix prefix) {

		return BITS_IN_BYTE;

	}
	double BitSize::BytesInKilobit(BytePrefix prefix) {

		switch (prefix) {
			case BytePrefix::Binary:
				return BYTES_IN_KIBIBIT;
			case BytePrefix::Decimal:
				return BYTES_IN_KILOBIT;
		}
		return BYTES_IN_KIBIBIT;
	}
	double BitSize::BytesInMegabit(BytePrefix prefix) {

		switch (prefix) {
			case BytePrefix::Binary:
				return BYTES_IN_MEBIBIT;
			case BytePrefix::Decimal:
				return BYTES_IN_MEGABIT;
		}
		return BYTES_IN_MEBIBIT;
	}
	double BitSize::BytesInGigabit(BytePrefix prefix) {

		switch (prefix) {
			case BytePrefix::Binary:
				return BYTES_IN_GIBIBIT;
			case BytePrefix::Decimal:
				return BYTES_IN_GIGABIT;
		}
		return BYTES_IN_GIBIBIT;
	}
	double BitSize::BytesInTerabit(BytePrefix prefix) {

		switch (prefix) {
			case BytePrefix::Binary:
				return BYTES_IN_TEBIBIT;
			case BytePrefix::Decimal:
				return BYTES_IN_TERABIT;
		}
		return BYTES_IN_TEBIBIT;
	}
	double BitSize::BytesInPetabit(BytePrefix prefix) {

		switch (prefix) {
			case BytePrefix::Binary:
				return BYTES_IN_PEBIBIT;
			case BytePrefix::Decimal:
				return BYTES_IN_PETABIT;
		}
		return BYTES_IN_PEBIBIT;
	}

	std::string BitSize::BitSymbol(ByteUnit unit) {

		return "b";

	}
	std::string BitSize::ByteSymbol(ByteUnit unit) {

		return "B";

	}
	std::string BitSize::KilobitSymbol(ByteUnit unit) {

		switch (unit) {
			case ByteUnit::IEC:
				return "Kibit";
			case ByteUnit::JEDEC:
				return "Kbit";
			case ByteUnit::Metric:
				return "kbit";
		}
		return "Kbit";

	}
	std::string BitSize::MegabitSymbol(ByteUnit unit) {

		switch (unit) {
			case ByteUnit::IEC:
				return "Mibit";
			case ByteUnit::JEDEC:
			case ByteUnit::Metric:
			default:
				return "Mbit";
		}


	}
	std::string BitSize::GigabitSymbol(ByteUnit unit) {

		switch (unit) {
			case ByteUnit::IEC:
				return "Gibit";
			case ByteUnit::JEDEC:
			case ByteUnit::Metric:
				return "Gbit";
		}

	}
	std::string BitSize::TerabitSymbol(ByteUnit unit) {

		switch (unit) {
			case ByteUnit::IEC:
				return "Tibit";
			case ByteUnit::JEDEC:
			case ByteUnit::Metric:
			default:
				return "Tbit";
		}

	}
	std::string BitSize::PetabitSymbol(ByteUnit unit) {

		switch (unit) {
			case ByteUnit::IEC:
				return "Pibit";
			case ByteUnit::JEDEC:
			case ByteUnit::Metric:
			default:
				return "Pbit";
		}

	}

	BitSize& BitSize::operator+=(const BitSize& rhs) {

		_bytes += rhs._bytes;

		return *this;

	}
	BitSize& BitSize::operator-=(const BitSize& rhs) {

		_bytes -= rhs._bytes;

		return *this;

	}

	bool operator==(const BitSize& lhs, const BitSize& rhs) {

		return (std::abs)(lhs.Bytes() - rhs.Bytes()) < 0.125; // difference of less than 1 bit

	}
	bool operator!=(const BitSize& lhs, const BitSize& rhs) {

		return !(lhs == rhs);

	}
	bool operator<(const BitSize& lhs, const BitSize& rhs) {

		return lhs.Bytes() < rhs.Bytes();

	}
	bool operator<=(const BitSize& lhs, const BitSize& rhs) {

		return (lhs.Bytes() < rhs.Bytes()) || (lhs == rhs);

	}
	bool operator>(const BitSize& lhs, const BitSize& rhs) {

		return lhs.Bytes() > rhs.Bytes();

	}
	bool operator>=(const BitSize& lhs, const BitSize& rhs) {

		return (lhs.Bytes() > rhs.Bytes()) || (lhs == rhs);

	}
	BitSize operator+(const BitSize& lhs, const BitSize& rhs) {

		return(BitSize(lhs.Bytes() + rhs.Bytes(), lhs._prefix, lhs._unit));

	}
	BitSize operator-(const BitSize& lhs, const BitSize& rhs) {

		return(BitSize(lhs.Bytes() - rhs.Bytes(), lhs._prefix, lhs._unit));

	}
	std::ostream& operator<<(std::ostream& lhs, const BitSize& rhs) {

		return lhs << rhs.ToString();

	}

}
