#pragma once

#include "ByteSizeCommon.h"
#include <string>

namespace hvn3 {

	class ByteSize {

	public:
		explicit ByteSize(double bytes, BytePrefix prefix = BytePrefix::Binary);
		ByteSize(double bytes, BytePrefix prefix, ByteUnit unit);

		[[nodiscard]] double Bits() const;
		[[nodiscard]] double Bytes() const;

		[[nodiscard]] double Kilobytes() const;
		[[nodiscard]] double Megabytes() const;
		[[nodiscard]] double Gigabytes() const;
		[[nodiscard]] double Terabytes() const;
		[[nodiscard]] double Petabytes() const;

		[[nodiscard]] std::string LargestUnitSymbol() const;
		[[nodiscard]] double LargestUnitValue() const;

		void AddBits(double size);
		void AddBytes(double size);
		void AddKilobytes(double size);
		void AddMegabytes(double size);
		void AddGigabytes(double size);
		void AddTerabytes(double size);
		void AddPetabytes(double size);

		[[nodiscard]] std::string ToString(unsigned int precision = 2) const;

		static ByteSize MinValue();
		static ByteSize MaxValue();

		static ByteSize Parse(const std::string& string);
		static ByteSize Parse(const char* string);
		static bool TryParse(const std::string& string, ByteSize& object);
		static bool TryParse(const char* string, ByteSize& object);

		static ByteSize FromBits(double size, BytePrefix prefix = BytePrefix::Binary);
		static ByteSize FromBytes(double size, BytePrefix prefix = BytePrefix::Binary);
		static ByteSize FromKilobytes(double size, BytePrefix prefix = BytePrefix::Binary);
		static ByteSize FromMegabytes(double size, BytePrefix prefix = BytePrefix::Binary);
		static ByteSize FromGigabytes(double size, BytePrefix prefix = BytePrefix::Binary);
		static ByteSize FromTerabytes(double size, BytePrefix prefix = BytePrefix::Binary);
		static ByteSize FromPetabytes(double size, BytePrefix prefix = BytePrefix::Binary);

		static double BitsInByte(BytePrefix prefix = BytePrefix::Binary);
		static double BytesInKilobyte(BytePrefix prefix = BytePrefix::Binary);
		static double BytesInMegabyte(BytePrefix prefix = BytePrefix::Binary);
		static double BytesInGigabyte(BytePrefix prefix = BytePrefix::Binary);
		static double BytesInTerabyte(BytePrefix prefix = BytePrefix::Binary);
		static double BytesInPetabyte(BytePrefix prefix = BytePrefix::Binary);

		static std::string BitSymbol(ByteUnit unit = ByteUnit::IEC);
		static std::string ByteSymbol(ByteUnit unit = ByteUnit::IEC);
		static std::string KilobyteSymbol(ByteUnit unit = ByteUnit::IEC);
		static std::string MegabyteSymbol(ByteUnit unit = ByteUnit::IEC);
		static std::string GigabyteSymbol(ByteUnit unit = ByteUnit::IEC);
		static std::string TerabyteSymbol(ByteUnit unit = ByteUnit::IEC);
		static std::string PetabyteSymbol(ByteUnit unit = ByteUnit::IEC);

		ByteSize& operator+=(const ByteSize& rhs);
		ByteSize& operator-=(const ByteSize& rhs);

		friend ByteSize operator+(const ByteSize& lhs, const ByteSize& rhs);
		friend ByteSize operator-(const ByteSize& lhs, const ByteSize& rhs);

	private:
		BytePrefix _prefix;
		ByteUnit _unit;
		double _bytes;

	};

	bool operator==(const ByteSize& lhs, const ByteSize& rhs);
	bool operator!=(const ByteSize& lhs, const ByteSize& rhs);
	bool operator<(const ByteSize& lhs, const ByteSize& rhs);
	bool operator<=(const ByteSize& lhs, const ByteSize& rhs);
	bool operator>(const ByteSize& lhs, const ByteSize& rhs);
	bool operator>=(const ByteSize& lhs, const ByteSize& rhs);
	ByteSize operator+(const ByteSize& lhs, const ByteSize& rhs);
	ByteSize operator-(const ByteSize& lhs, const ByteSize& rhs);
	std::ostream& operator<<(std::ostream& lhs, const ByteSize& rhs);

}
