//
// Created by Vova on 25.05.2020.
//

#include "ByteSize.h"

#include <algorithm>
#include <limits>
#include <sstream>
#include <iomanip>
#include <cassert>
#include <exception>

#define BITS_IN_BYTE 8.
#define BYTES_IN_KIBIBYTE 1024.
#define BYTES_IN_MEBIBYTE 1048576.
#define BYTES_IN_GIBIBYTE 1073741824.
#define BYTES_IN_TEBIBYTE 1099511627776.
#define BYTES_IN_PEBIBYTE 1125899906842624.
#define BYTES_IN_KILOBYTE 1000.
#define BYTES_IN_MEGABYTE 1000000.
#define BYTES_IN_GIGABYTE 1000000000.
#define BYTES_IN_TERABYTE 1000000000000.
#define BYTES_IN_PETABYTE 1000000000000000.

namespace hvn3 {

	ByteSize::ByteSize(double bytes, BytePrefix prefix) :
			ByteSize(bytes, prefix, prefix == BytePrefix::Binary ? ByteUnit::IEC : ByteUnit::Metric) {
	}
	ByteSize::ByteSize(double bytes, BytePrefix prefix, ByteUnit unit) {

		assert(unit != ByteUnit::IEC || prefix == BytePrefix::Binary);

		_bytes = RoundBytesToNearestBit(bytes);
		_unit = unit;
		_prefix = prefix;

	}

	double ByteSize::Bits() const {

		return _bytes * BITS_IN_BYTE;

	}
	double ByteSize::Bytes() const {

		return _bytes;

	}
	double ByteSize::Kilobytes() const {

		return Bytes() / BytesInKilobyte(_prefix);

	}
	double ByteSize::Megabytes() const {

		return Bytes() / BytesInMegabyte(_prefix);

	}
	double ByteSize::Gigabytes() const {

		return Bytes() / BytesInGigabyte(_prefix);

	}
	double ByteSize::Terabytes() const {

		return Bytes() / BytesInTerabyte(_prefix);

	}
	double ByteSize::Petabytes() const {

		return Bytes() / BytesInPetabyte(_prefix);

	}

	std::string ByteSize::LargestUnitSymbol() const {

		if ((std::abs)(Petabytes()) >= 1.0)
			return PetabyteSymbol(_unit);
		if ((std::abs)(Terabytes()) >= 1.0)
			return TerabyteSymbol(_unit);
		if ((std::abs)(Gigabytes()) >= 1.0)
			return GigabyteSymbol(_unit);
		if ((std::abs)(Megabytes()) >= 1.0)
			return MegabyteSymbol(_unit);
		if ((std::abs)(Kilobytes()) >= 1.0)
			return KilobyteSymbol(_unit);
		if ((std::abs)(Bytes()) >= 1.0)
			return ByteSymbol(_unit);

		return BitSymbol(_unit);

	}
	double ByteSize::LargestUnitValue() const {

		if ((std::abs)(Petabytes()) >= 1.0)
			return Petabytes();
		if ((std::abs)(Terabytes()) >= 1.0)
			return Terabytes();
		if ((std::abs)(Gigabytes()) >= 1.0)
			return Gigabytes();
		if ((std::abs)(Megabytes()) >= 1.0)
			return Megabytes();
		if ((std::abs)(Kilobytes()) >= 1.0)
			return Kilobytes();
		if ((std::abs)(Bytes()) >= 1.0)
			return Bytes();

		return Bits();

	}

	void ByteSize::AddBits(double size) {

		*this = ByteSize(Bytes() + BitsInByte(_prefix) / size, _prefix, _unit);

	}
	void ByteSize::AddBytes(double size) {

		*this = ByteSize(Bytes() + size, _prefix, _unit);

	}
	void ByteSize::AddKilobytes(double size) {

		*this = ByteSize(Bytes() + size * BytesInKilobyte(_prefix), _prefix, _unit);

	}
	void ByteSize::AddMegabytes(double size) {

		*this = ByteSize(Bytes() + size * BytesInMegabyte(_prefix), _prefix, _unit);

	}
	void ByteSize::AddGigabytes(double size) {

		*this = ByteSize(Bytes() + size * BytesInGigabyte(_prefix), _prefix, _unit);

	}
	void ByteSize::AddTerabytes(double size) {

		*this = ByteSize(Bytes() + size * BytesInTerabyte(_prefix), _prefix, _unit);

	}
	void ByteSize::AddPetabytes(double size) {

		*this = ByteSize(Bytes() + size * BytesInPetabyte(_prefix), _prefix, _unit);

	}

	std::string ByteSize::ToString(unsigned int precision) const {

		std::stringstream stream;

		stream << std::fixed << std::setprecision(precision) << LargestUnitValue() << ' ' << LargestUnitSymbol();

		return stream.str();

	}

	ByteSize ByteSize::MinValue() {

		return ByteSize(0);

	}
	ByteSize ByteSize::MaxValue() {

		return ByteSize(DBL_MAX);

	}

	ByteSize ByteSize::Parse(const std::string& string) {

		return Parse(string.c_str());

	}
	ByteSize ByteSize::Parse(const char* string) {

		ByteSize object(0);

		if (!TryParse(string, object))
			throw std::invalid_argument("The input string was not in the correct format.");

		return object;

	}
	bool ByteSize::TryParse(const std::string& string, ByteSize& object) {

		return TryParse(string.c_str(), object);

	}
	bool ByteSize::TryParse(const char* string, ByteSize& object) {

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
			object = ByteSize::FromBits(size);
		else if (suffix == ByteSymbol())
			object = ByteSize::FromBytes(size);

		else if (suffix == KilobyteSymbol(ByteUnit::IEC))
			object = ByteSize::FromKilobytes(size, BytePrefix::Binary);
		else if (suffix == KilobyteSymbol(ByteUnit::JEDEC))
			object = ByteSize(size * BytesInKilobyte(BytePrefix::Binary), BytePrefix::Binary, ByteUnit::JEDEC);
		else if (suffix == KilobyteSymbol(ByteUnit::Metric))
			object = ByteSize::FromKilobytes(size, BytePrefix::Decimal);

		else if (suffix == MegabyteSymbol(ByteUnit::IEC))
			object = ByteSize::FromMegabytes(size, BytePrefix::Binary);
		else if (suffix == MegabyteSymbol(ByteUnit::Metric))
			object = ByteSize::FromMegabytes(size, BytePrefix::Decimal);

		else if (suffix == GigabyteSymbol(ByteUnit::IEC))
			object = ByteSize::FromGigabytes(size, BytePrefix::Binary);
		else if (suffix == GigabyteSymbol(ByteUnit::Metric))
			object = ByteSize::FromGigabytes(size, BytePrefix::Decimal);

		else if (suffix == TerabyteSymbol(ByteUnit::IEC))
			object = ByteSize::FromTerabytes(size, BytePrefix::Binary);
		else if (suffix == TerabyteSymbol(ByteUnit::Metric))
			object = ByteSize::FromTerabytes(size, BytePrefix::Decimal);

		else if (suffix == PetabyteSymbol(ByteUnit::IEC))
			object = ByteSize::FromPetabytes(size, BytePrefix::Binary);
		else if (suffix == PetabyteSymbol(ByteUnit::Metric))
			object = ByteSize::FromPetabytes(size, BytePrefix::Decimal);
		else
			object = ByteSize::FromBits(size);

		return true;

	}

	ByteSize ByteSize::FromBits(double size, BytePrefix prefix) {

		return ByteSize(size / BitsInByte(prefix), prefix);

	}
	ByteSize ByteSize::FromBytes(double size, BytePrefix prefix) {

		return ByteSize(size, prefix);

	}
	ByteSize ByteSize::FromKilobytes(double size, BytePrefix prefix) {

		return ByteSize(size * BytesInKilobyte(prefix), prefix);

	}
	ByteSize ByteSize::FromMegabytes(double size, BytePrefix prefix) {

		return ByteSize(size * BytesInMegabyte(prefix), prefix);

	}
	ByteSize ByteSize::FromGigabytes(double size, BytePrefix prefix) {

		return ByteSize(size * BytesInGigabyte(prefix), prefix);

	}
	ByteSize ByteSize::FromTerabytes(double size, BytePrefix prefix) {

		return ByteSize(size * BytesInTerabyte(prefix), prefix);

	}
	ByteSize ByteSize::FromPetabytes(double size, BytePrefix prefix) {

		return ByteSize(size * BytesInPetabyte(prefix), prefix);

	}

	double ByteSize::BitsInByte(BytePrefix prefix) {

		return BITS_IN_BYTE;

	}
	double ByteSize::BytesInKilobyte(BytePrefix prefix) {

		switch (prefix) {
			case BytePrefix::Binary:
				return BYTES_IN_KIBIBYTE;
			case BytePrefix::Decimal:
				return BYTES_IN_KILOBYTE;
		}
		return BYTES_IN_KIBIBYTE;
	}
	double ByteSize::BytesInMegabyte(BytePrefix prefix) {

		switch (prefix) {
			case BytePrefix::Binary:
				return BYTES_IN_MEBIBYTE;
			case BytePrefix::Decimal:
				return BYTES_IN_MEGABYTE;
		}
		return BYTES_IN_MEBIBYTE;
	}
	double ByteSize::BytesInGigabyte(BytePrefix prefix) {

		switch (prefix) {
			case BytePrefix::Binary:
				return BYTES_IN_GIBIBYTE;
			case BytePrefix::Decimal:
				return BYTES_IN_GIGABYTE;
		}
		return BYTES_IN_GIBIBYTE;
	}
	double ByteSize::BytesInTerabyte(BytePrefix prefix) {

		switch (prefix) {
			case BytePrefix::Binary:
				return BYTES_IN_TEBIBYTE;
			case BytePrefix::Decimal:
				return BYTES_IN_TERABYTE;
		}
		return BYTES_IN_TEBIBYTE;
	}
	double ByteSize::BytesInPetabyte(BytePrefix prefix) {

		switch (prefix) {
			case BytePrefix::Binary:
				return BYTES_IN_PEBIBYTE;
			case BytePrefix::Decimal:
				return BYTES_IN_PETABYTE;
		}
		return BYTES_IN_PEBIBYTE;
	}

	std::string ByteSize::BitSymbol(ByteUnit unit) {

		return "b";

	}
	std::string ByteSize::ByteSymbol(ByteUnit unit) {

		return "B";

	}
	std::string ByteSize::KilobyteSymbol(ByteUnit unit) {

		switch (unit) {
			case ByteUnit::IEC:
				return "KiB";
			case ByteUnit::JEDEC:
				return "KB";
			case ByteUnit::Metric:
				return "kB";
		}

		return "kB";
	}
	std::string ByteSize::MegabyteSymbol(ByteUnit unit) {

		switch (unit) {
			case ByteUnit::IEC:
				return "MiB";
			case ByteUnit::JEDEC:
			case ByteUnit::Metric:
				return "MB";
		}
		return "MB";
	}
	std::string ByteSize::GigabyteSymbol(ByteUnit unit) {

		switch (unit) {
			case ByteUnit::IEC:
				return "GiB";
			case ByteUnit::JEDEC:
			case ByteUnit::Metric:
				return "GB";
		}
		return "GB";
	}
	std::string ByteSize::TerabyteSymbol(ByteUnit unit) {

		switch (unit) {
			case ByteUnit::IEC:
				return "TiB";
			case ByteUnit::JEDEC:
			case ByteUnit::Metric:
				return "TB";
		}
		return "TB";
	}
	std::string ByteSize::PetabyteSymbol(ByteUnit unit) {

		switch (unit) {
			case ByteUnit::IEC:
				return "PiB";
			case ByteUnit::JEDEC:
			case ByteUnit::Metric:
				return "PB";
		}
		return "PB";
	}

	ByteSize& ByteSize::operator+=(const ByteSize& rhs) {

		_bytes += rhs._bytes;

		return *this;

	}
	ByteSize& ByteSize::operator-=(const ByteSize& rhs) {

		_bytes -= rhs._bytes;

		return *this;

	}

	bool operator==(const ByteSize& lhs, const ByteSize& rhs) {

		return (std::abs)(lhs.Bytes() - rhs.Bytes()) < 0.125; // difference of less than 1 bit

	}
	bool operator!=(const ByteSize& lhs, const ByteSize& rhs) {

		return !(lhs == rhs);

	}
	bool operator<(const ByteSize& lhs, const ByteSize& rhs) {

		return lhs.Bytes() < rhs.Bytes();

	}
	bool operator<=(const ByteSize& lhs, const ByteSize& rhs) {

		return (lhs.Bytes() < rhs.Bytes()) || (lhs == rhs);

	}
	bool operator>(const ByteSize& lhs, const ByteSize& rhs) {

		return lhs.Bytes() > rhs.Bytes();

	}
	bool operator>=(const ByteSize& lhs, const ByteSize& rhs) {

		return (lhs.Bytes() > rhs.Bytes()) || (lhs == rhs);

	}
	ByteSize operator+(const ByteSize& lhs, const ByteSize& rhs) {

		return(ByteSize(lhs.Bytes() + rhs.Bytes(), lhs._prefix, lhs._unit));

	}
	ByteSize operator-(const ByteSize& lhs, const ByteSize& rhs) {

		return(ByteSize(lhs.Bytes() - rhs.Bytes(), lhs._prefix, lhs._unit));

	}
	std::ostream& operator<<(std::ostream& lhs, const ByteSize& rhs) {

		return lhs << rhs.ToString();

	}

}
