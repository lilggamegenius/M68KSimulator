#include "Simulator.h"

#include <memory>
#include "Exceptions.hpp"

M68K::CPU::CPU() {
	mem = std::make_unique<M68K::AddressSpace>();
}

template<>
void M68K::SegmentedMemory::getValue(const Byte *data, LongWord index, size_t, Byte &out) {
    out = data[index];
}

template<>
void M68K::SegmentedMemory::getValue(const Byte *data, LongWord index, size_t maxSize, Word &out) {
    if (index % 2 == 1) throw std::invalid_argument("Attempting to read word on odd address");
    if (index + 2 >= maxSize) throw std::invalid_argument("Attempting to read past address space boundry");
    M68K::data dat;
    dat.byte[0] = data[index + 1];
    dat.byte[1] = data[index];
    out = dat.word[0];
}

template<>
void M68K::SegmentedMemory::getValue(const Byte *data, LongWord index, size_t maxSize, LongWord &out) {
    if (index % 2 == 1) throw M68K::Exception<M68K::Vectors::AddressError>("Attempting to read word on odd address");
    if (index + 4 >= maxSize) throw std::invalid_argument("Attempting to read past address space boundry");
    M68K::data dat;
    dat.byte[0] = data[index + 3];
    dat.byte[1] = data[index + 2];
    dat.byte[2] = data[index + 1];
    dat.byte[3] = data[index];
    out = dat.longWord;
}


template<>
void M68K::SegmentedMemory::setValue(Byte *data, LongWord index, size_t, Byte val) {
    data[index] = val;
}

template<>
void M68K::SegmentedMemory::setValue(Byte *data, LongWord index, size_t maxSize, Word val) {
    if (index % 2 == 1) throw std::invalid_argument("Attempting to write word on odd address");
    if (index + 2 >= maxSize) throw std::invalid_argument("Attempting to write past address space boundry");
    M68K::data dat(val);
    data[index + 1] = dat.byte[0];
    data[index] = dat.byte[1];
}

template<>
void M68K::SegmentedMemory::setValue(Byte *data, LongWord index, size_t maxSize, LongWord val) {
    if (index % 2 == 1) throw M68K::Exception<M68K::Vectors::AddressError>("Attempting to write word on odd address");
    if (index + 4 >= maxSize) throw std::invalid_argument("Attempting to write past address space boundry");
    M68K::data dat(val);
    data[index + 3] = dat.byte[0];
    data[index + 2] = dat.byte[1];
    data[index + 1] = dat.byte[2];
    data[index] = dat.byte[3];
}