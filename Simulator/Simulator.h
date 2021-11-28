#pragma once

#include <cstdint>
#include <stdexcept>
#include <array>
#include <memory>

namespace M68K {
	typedef uint8_t Byte;
	typedef uint16_t Word;
	typedef uint32_t LongWord;
	typedef int8_t SByte;
	typedef int16_t SWord;
	typedef int32_t SLongWord;

	typedef union Data{
		Byte byte[4];
		Word word[2];
		LongWord longWord;

		SByte sByte[4];
		SWord sWord[2];
		SLongWord sLongWord;

		Data(Byte b){
			byte[0] = b;
		}

		Data(Word w){
			word[0] = w;
		}

		Data(LongWord l){
			longWord = l;
		}

		Data(SByte b){
			byte[0] = b;
		}

		Data(SWord w){
			word[0] = w;
		}

		Data(SLongWord l){
			longWord = l;
		}

		Data(){
			longWord = 0;
		}
	} data;

	constexpr int range(LongWord start, LongWord end) {
		int ret = (int) (end - start);
		if (ret < 0) throw std::runtime_error{"start address must be less than end address"};
		return ret;
	}

	struct SegmentedMemory {
		Byte rom                            [range(0x000000, 0x400000)]{};       // Cartridge ROM/RAM
		Byte SCDReserved                    [range(0x400000, 0x800000)]{};       // Reserved (used by the Mega-CD and 32X)
		Byte S32XReserved                   [range(0x800000, 0x840000)]{};       // Reserved (used by the 32X)
		Byte S32XFramebuffer                [range(0x840000, 0x860000)]{};       // 32X frame buffer
		Byte S32XFramebufferOverwriteMode   [range(0x860000, 0x880000)]{};       // 32X frame buffer overwrite mode
		Byte S32XCartridgeRom               [range(0x880000, 0x900000)]{};       // 32X cartridge ROM (first 512kB bank only)
		Byte S32XCartridgeBankSwitchedRom   [range(0x900000, 0xA00000)]{};       // 32X cartridge bankswitched ROM (any 512kB bank, controlled by 32X registers)
		Byte Z80Ram                         [range(0xA00000, 0xA10000)]{};       // Z80 memory space
		Byte versionRegister                [range(0xA10000, 0xA10002)]{};       // Version register
		Byte controller1Data                [range(0xA10002, 0xA10004)]{};       // Controller 1 data
		Byte controller2Data                [range(0xA10004, 0xA10006)]{};       // Controller 2 data
		Byte expansionPortData              [range(0xA10006, 0xA10008)]{};       // Expansion port data
		Byte controller1Control             [range(0xA10008, 0xA1000A)]{};       // Controller 1 control
		Byte controller2Control             [range(0xA1000A, 0xA1000C)]{};       // Controller 2 control
		Byte expansionPortControl           [range(0xA1000C, 0xA1000E)]{};       // Expansion port control
		Byte controller1SerialTransmit      [range(0xA1000E, 0xA10010)]{};       // Controller 1 serial transmit
		Byte controller1SerialReceive       [range(0xA10010, 0xA10012)]{};       // Controller 1 serial receive
		Byte controller1SerialControl       [range(0xA10012, 0xA10014)]{};       // Controller 1 serial control
		Byte controller2SerialTransmit      [range(0xA10014, 0xA10016)]{};       // Controller 2 serial transmit
		Byte controller2SerialReceive       [range(0xA10016, 0xA10018)]{};       // Controller 2 serial receive
		Byte controller2SerialControl       [range(0xA10018, 0xA1001A)]{};       // Controller 2 serial control
		Byte expansionPortSerialTransmit    [range(0xA1001A, 0xA1001C)]{};       // Expansion port serial transmit
		Byte expansionPortSerialReceive     [range(0xA1001C, 0xA1001E)]{};       // Expansion port serial receive
		Byte expansionPortSerialControl     [range(0xA1001E, 0xA10020)]{};       // Expansion port serial control
		Byte reserved1                      [range(0xA10020, 0xA11000)]{};       // Reserved
		Byte memoryModeRegister             [range(0xA11000, 0xA11002)]{};       // Memory mode register
		Byte reserved2                      [range(0xA11002, 0xA11100)]{};       // Reserved
		Byte Z80BusRequest                  [range(0xA11100, 0xA11102)]{};       // Z80 bus request
		Byte reserved3                      [range(0xA11102, 0xA11200)]{};       // Reserved
		Byte Z80Reset                       [range(0xA11200, 0xA11202)]{};       // Z80 reset
		Byte reserved4                      [range(0xA11202, 0xA13000)]{};       // Reserved
		Byte TIMERegisters                  [range(0xA13000, 0xA14000)]{};       // TIME registers; used to send signals to the cartridge
		Byte TMSSVerification               [range(0xA14000, 0xA14004)]={'S', 'E', 'G', 'A'};// TMSS "SEGA"
		Byte unused                         [range(0xA14004, 0xA14101)]{};
		Byte TMSSCartridgeRegister          [range(0xA14101, 0xA14102)]{};       // TMSS/cartridge register
		Byte reserved5                      [range(0xA14102, 0xC00000)]{};       // Reserved
		Byte VDPData                        [range(0xC00000, 0xC00011)]{};       // VDP data port/control port/H/V counter
		Byte PSGData                        [range(0xC00011, 0xC0001C)]{};       // PSG output
		Byte DebugRegister                  [range(0xC0001C, 0xC00020)]{};       // Debug register
		Byte reserved6                      [range(0xC00020, 0xFF0000)]{};       // Reserved
		Byte ram                            [range(0xFF0000, 0xFFFFFF) + 1]{};   // 68000 RAM

		template<typename T>
		void getValue(LongWord index, T &out);

		template<typename T>
		void setValue(LongWord index, T val);

		SegmentedMemory(SegmentedMemory&&) = default;
		SegmentedMemory() = default;

	private:
		template<typename T>
		void getValue(const Byte *data, LongWord index, size_t maxSize, T &out);

		template<typename T>
		void setValue(Byte *data, LongWord index, size_t maxSize, T val);
	};

	struct ConditionCodeRegister {
		Byte Carry: 1;
		Byte oVerflow: 1;
		Byte Zero: 1;
		Byte Negative: 1;
		Byte eXtended: 1;
	};
	struct SystemStatusRegister {
		Byte interruptPriorityMask: 3;
		Byte                       : 1;
		Byte masterInterruptState: 1;
		Byte supervisorUserState: 1;
		Byte traceEnable: 2;
	};

	struct StatusRegister {
		ConditionCodeRegister CCR;
		SystemStatusRegister SSR;
	};

	union AddressSpace {
		SegmentedMemory segMem;
		std::array<Byte , sizeof(SegmentedMemory)> rawMem{};

		AddressSpace(AddressSpace const&) {}
		AddressSpace() {} // NOLINT(modernize-use-equals-default)
	};

	struct CPU {
		data programCounter{};
		std::unique_ptr<AddressSpace> mem;
		data dataRegisters[8]{};
		data AddrRegisters[7]{};
		data userStackPointer{};
		data systemStackPointer{};
		StatusRegister statusRegister{};

		CPU();

		//~CPU() noexcept;

	};
}

template<typename T>
void M68K::SegmentedMemory::getValue(const Byte *data, LongWord index, size_t maxSize, T &out) {}

template<>
void M68K::SegmentedMemory::getValue(const Byte *data, LongWord index, size_t maxSize, Byte &out);

template<>
void M68K::SegmentedMemory::getValue(const Byte *data, LongWord index, size_t maxSize, Word &out);

template<>
void M68K::SegmentedMemory::getValue(const Byte *data, LongWord index, size_t maxSize, LongWord &out);

template<typename T>
void M68K::SegmentedMemory::getValue(LongWord index, T &out) {
	index = index & 0x00FFFFFF; // Highest byte is ignored
	switch (index) {
		case 0x000000 ... 0x400000 - 1: {
			getValue<T>(rom, index, sizeof(rom), out);
			return;
		}
		case 0x400000 ... 0x800000 - 1: {
			getValue<T>(SCDReserved, index - 0x400000, sizeof(SCDReserved), out);
			return;
		}
		case 0x800000 ... 0x840000 - 1: {
			getValue<T>(S32XReserved, index - 0x800000, sizeof(S32XReserved), out);
			return;
		}
		case 0x840000 ... 0x860000 - 1: {
			getValue<T>(S32XFramebuffer, index - 0x840000, sizeof(S32XFramebuffer), out);
			return;
		}
		case 0x860000 ... 0x880000 - 1: {
			getValue<T>(S32XFramebufferOverwriteMode, index - 0x860000, sizeof(S32XFramebufferOverwriteMode), out);
			return;
		}
		case 0x880000 ... 0x900000 - 1: {
			getValue<T>(S32XCartridgeRom, index - 0x880000, sizeof(S32XCartridgeRom), out);
			return;
		}
		case 0x900000 ... 0xA00000 - 1: {
			getValue<T>(S32XCartridgeBankSwitchedRom, index - 0x900000, sizeof(S32XCartridgeBankSwitchedRom), out);
			return;
		}
		case 0xA00000 ... 0xA10000 - 1: {
			getValue<T>(Z80Ram, index - 0xA00000, sizeof(Z80Ram), out);
			return;
		}
		case 0xA10000 ... 0xA10002 - 1: {
			getValue<T>(versionRegister, index - 0xA10000, sizeof(versionRegister), out);
			return;
		}
		case 0xA10002 ... 0xA10004 - 1: {
			getValue<T>(controller1Data, index - 0xA10002, sizeof(controller1Data), out);
			return;
		}
		case 0xA10004 ... 0xA10006 - 1: {
			getValue<T>(controller2Data, index - 0xA10004, sizeof(controller2Data), out);
			return;
		}
		case 0xA10006 ... 0xA10008 - 1: {
			getValue<T>(expansionPortData, index - 0xA10006, sizeof(expansionPortData), out);
			return;
		}
		case 0xA10008 ... 0xA1000A - 1: {
			getValue<T>(controller1Control, index - 0xA10008, sizeof(controller1Control), out);
			return;
		}
		case 0xA1000A ... 0xA1000C - 1: {
			getValue<T>(controller2Control, index - 0xA1000A, sizeof(controller2Control), out);
			return;
		}
		case 0xA1000C ... 0xA1000E - 1: {
			getValue<T>(expansionPortControl, index - 0xA1000C, sizeof(expansionPortControl), out);
			return;
		}
		case 0xA1000E ... 0xA10010 - 1: {
			getValue<T>(controller1SerialTransmit, index - 0xA1000E, sizeof(controller1SerialTransmit), out);
			return;
		}
		case 0xA10010 ... 0xA10012 - 1: {
			getValue<T>(controller1SerialReceive, index - 0xA10010, sizeof(controller1SerialReceive), out);
			return;
		}
		case 0xA10012 ... 0xA10014 - 1: {
			getValue<T>(controller1SerialControl, index - 0xA10012, sizeof(controller1SerialControl), out);
			return;
		}
		case 0xA10014 ... 0xA10016 - 1: {
			getValue<T>(controller2SerialTransmit, index - 0xA10014, sizeof(controller2SerialTransmit), out);
			return;
		}
		case 0xA10016 ... 0xA10018 - 1: {
			getValue<T>(controller2SerialReceive, index - 0xA10016, sizeof(controller2SerialReceive), out);
			return;
		}
		case 0xA10018 ... 0xA1001A - 1: {
			getValue<T>(controller2SerialControl, index - 0xA10018, sizeof(controller2SerialControl), out);
			return;
		}
		case 0xA1001A ... 0xA1001C - 1: {
			getValue<T>(expansionPortSerialTransmit, index - 0xA1001A, sizeof(expansionPortSerialTransmit), out);
			return;
		}
		case 0xA1001C ... 0xA1001E - 1: {
			getValue<T>(expansionPortSerialReceive, index - 0xA1001C, sizeof(expansionPortSerialReceive), out);
			return;
		}
		case 0xA1001E ... 0xA10020 - 1: {
			getValue<T>(expansionPortSerialControl, index - 0xA1001E, sizeof(expansionPortSerialControl), out);
			return;
		}
		case 0xA10020 ... 0xA11000 - 1: {
			getValue<T>(reserved1, index - 0xA10020, sizeof(reserved1), out);
			return;
		}
		case 0xA11000 ... 0xA11002 - 1: {
			getValue<T>(memoryModeRegister, index - 0xA11000, sizeof(memoryModeRegister), out);
			return;
		}
		case 0xA11002 ... 0xA11100 - 1: {
			getValue<T>(reserved2, index - 0xA11002, sizeof(reserved2), out);
			return;
		}
		case 0xA11100 ... 0xA11102 - 1: {
			getValue<T>(Z80BusRequest, index - 0xA11100, sizeof(Z80BusRequest), out);
			return;
		}
		case 0xA11102 ... 0xA11200 - 1: {
			getValue<T>(reserved3, index - 0xA11102, sizeof(reserved3), out);
			return;
		}
		case 0xA11200 ... 0xA11202 - 1: {
			getValue<T>(Z80Reset, index - 0xA11200, sizeof(Z80Reset), out);
			return;
		}
		case 0xA11202 ... 0xA13000 - 1: {
			getValue<T>(reserved4, index - 0xA11202, sizeof(reserved4), out);
			return;
		}
		case 0xA13000 ... 0xA14000 - 1: {
			getValue<T>(TIMERegisters, index - 0xA13000, sizeof(TIMERegisters), out);
			return;
		}
		case 0xA14000 ... 0xA14004 - 1: {
			getValue<T>(TMSSVerification, index - 0xA14000, sizeof(TMSSVerification), out);
			return;
		}
		case 0xA14004 ... 0xA14101 - 1: {
			getValue<T>(unused, index - 0xA14004, sizeof(unused), out);
			return;
		}
		case 0xA14101 ... 0xA14102 - 1: {
			getValue<T>(TMSSCartridgeRegister, index - 0xA14101, sizeof(TMSSCartridgeRegister), out);
			return;
		}
		case 0xA14102 ... 0xC00000 - 1: {
			getValue<T>(reserved5, index - 0xA14102, sizeof(reserved5), out);
			return;
		}
		case 0xC00000 ... 0xC00011 - 1: {
			getValue<T>(VDPData, index - 0xC00000, sizeof(VDPData), out);
			return;
		}
		case 0xC00011 ... 0xC0001C - 1: {
			getValue<T>(PSGData, index - 0xC00011, sizeof(PSGData), out);
			return;
		}
		case 0xC0001C ... 0xC00020 - 1: {
			getValue<T>(DebugRegister, index - 0xC0001C, sizeof(DebugRegister), out);
			return;
		}
		case 0xC00020 ... 0xFF0000 - 1: {
			getValue<T>(reserved6, index - 0xC00020, sizeof(reserved6), out);
			return;
		}
		case 0xFF0000 ... 0xFFFFFF: {
			getValue<T>(ram, index - 0xFF0000, sizeof(ram), out);
			return;
		}
		default:
			throw std::invalid_argument("Invalid index");
	}
}

template<typename T>
void M68K::SegmentedMemory::setValue(Byte *data, LongWord index, size_t maxSize, T val) {}

template<>
void M68K::SegmentedMemory::setValue(Byte *data, LongWord index, size_t maxSize, Byte val);

template<>
void M68K::SegmentedMemory::setValue(Byte *data, LongWord index, size_t maxSize, Word val);

template<>
void M68K::SegmentedMemory::setValue(Byte *data, LongWord index, size_t maxSize, LongWord val);

template<typename T>
void M68K::SegmentedMemory::setValue(LongWord index, T val) {
	index = index & 0x00FFFFFF; // Highest byte is ignored
	switch (index) {
		case 0x000000 ... 0x400000 - 1: {
			setValue<T>(rom, index, sizeof(rom), val);
			return;
		}
		case 0x400000 ... 0x800000 - 1: {
			setValue<T>(SCDReserved, index - 0x400000, sizeof(SCDReserved), val);
			return;
		}
		case 0x800000 ... 0x840000 - 1: {
			setValue<T>(S32XReserved, index - 0x800000, sizeof(S32XReserved), val);
			return;
		}
		case 0x840000 ... 0x860000 - 1: {
			setValue<T>(S32XFramebuffer, index - 0x840000, sizeof(S32XFramebuffer), val);
			return;
		}
		case 0x860000 ... 0x880000 - 1: {
			setValue<T>(S32XFramebufferOverwriteMode, index - 0x860000, sizeof(S32XFramebufferOverwriteMode), val);
			return;
		}
		case 0x880000 ... 0x900000 - 1: {
			setValue<T>(S32XCartridgeRom, index - 0x880000, sizeof(S32XCartridgeRom), val);
			return;
		}
		case 0x900000 ... 0xA00000 - 1: {
			setValue<T>(S32XCartridgeBankSwitchedRom, index - 0x900000, sizeof(S32XCartridgeBankSwitchedRom), val);
			return;
		}
		case 0xA00000 ... 0xA10000 - 1: {
			setValue<T>(Z80Ram, index - 0xA00000, sizeof(Z80Ram), val);
			return;
		}
		case 0xA10000 ... 0xA10002 - 1: {
			setValue<T>(versionRegister, index - 0xA10000, sizeof(versionRegister), val);
			return;
		}
		case 0xA10002 ... 0xA10004 - 1: {
			setValue<T>(controller1Data, index - 0xA10002, sizeof(controller1Data), val);
			return;
		}
		case 0xA10004 ... 0xA10006 - 1: {
			setValue<T>(controller2Data, index - 0xA10004, sizeof(controller2Data), val);
			return;
		}
		case 0xA10006 ... 0xA10008 - 1: {
			setValue<T>(expansionPortData, index - 0xA10006, sizeof(expansionPortData), val);
			return;
		}
		case 0xA10008 ... 0xA1000A - 1: {
			setValue<T>(controller1Control, index - 0xA10008, sizeof(controller1Control), val);
			return;
		}
		case 0xA1000A ... 0xA1000C - 1: {
			setValue<T>(controller2Control, index - 0xA1000A, sizeof(controller2Control), val);
			return;
		}
		case 0xA1000C ... 0xA1000E - 1: {
			setValue<T>(expansionPortControl, index - 0xA1000C, sizeof(expansionPortControl), val);
			return;
		}
		case 0xA1000E ... 0xA10010 - 1: {
			setValue<T>(controller1SerialTransmit, index - 0xA1000E, sizeof(controller1SerialTransmit), val);
			return;
		}
		case 0xA10010 ... 0xA10012 - 1: {
			setValue<T>(controller1SerialReceive, index - 0xA10010, sizeof(controller1SerialReceive), val);
			return;
		}
		case 0xA10012 ... 0xA10014 - 1: {
			setValue<T>(controller1SerialControl, index - 0xA10012, sizeof(controller1SerialControl), val);
			return;
		}
		case 0xA10014 ... 0xA10016 - 1: {
			setValue<T>(controller2SerialTransmit, index - 0xA10014, sizeof(controller2SerialTransmit), val);
			return;
		}
		case 0xA10016 ... 0xA10018 - 1: {
			setValue<T>(controller2SerialReceive, index - 0xA10016, sizeof(controller2SerialReceive), val);
			return;
		}
		case 0xA10018 ... 0xA1001A - 1: {
			setValue<T>(controller2SerialControl, index - 0xA10018, sizeof(controller2SerialControl), val);
			return;
		}
		case 0xA1001A ... 0xA1001C - 1: {
			setValue<T>(expansionPortSerialTransmit, index - 0xA1001A, sizeof(expansionPortSerialTransmit), val);
			return;
		}
		case 0xA1001C ... 0xA1001E - 1: {
			setValue<T>(expansionPortSerialReceive, index - 0xA1001C, sizeof(expansionPortSerialReceive), val);
			return;
		}
		case 0xA1001E ... 0xA10020 - 1: {
			setValue<T>(expansionPortSerialControl, index - 0xA1001E, sizeof(expansionPortSerialControl), val);
			return;
		}
		case 0xA10020 ... 0xA11000 - 1: {
			setValue<T>(reserved1, index - 0xA10020, sizeof(reserved1), val);
			return;
		}
		case 0xA11000 ... 0xA11002 - 1: {
			setValue<T>(memoryModeRegister, index - 0xA11000, sizeof(memoryModeRegister), val);
			return;
		}
		case 0xA11002 ... 0xA11100 - 1: {
			setValue<T>(reserved2, index - 0xA11002, sizeof(reserved2), val);
			return;
		}
		case 0xA11100 ... 0xA11102 - 1: {
			setValue<T>(Z80BusRequest, index - 0xA11100, sizeof(Z80BusRequest), val);
			return;
		}
		case 0xA11102 ... 0xA11200 - 1: {
			setValue<T>(reserved3, index - 0xA11102, sizeof(reserved3), val);
			return;
		}
		case 0xA11200 ... 0xA11202 - 1: {
			setValue<T>(Z80Reset, index - 0xA11200, sizeof(Z80Reset), val);
			return;
		}
		case 0xA11202 ... 0xA13000 - 1: {
			setValue<T>(reserved4, index - 0xA11202, sizeof(reserved4), val);
			return;
		}
		case 0xA13000 ... 0xA14000 - 1: {
			setValue<T>(TIMERegisters, index - 0xA13000, sizeof(TIMERegisters), val);
			return;
		}
		case 0xA14000 ... 0xA14004 - 1: {
			setValue<T>(TMSSVerification, index - 0xA14000, sizeof(TMSSVerification), val);
			return;
		}
		case 0xA14004 ... 0xA14101 - 1: {
			setValue<T>(unused, index - 0xA14004, sizeof(unused), val);
			return;
		}
		case 0xA14101 ... 0xA14102 - 1: {
			setValue<T>(TMSSCartridgeRegister, index - 0xA14101, sizeof(TMSSCartridgeRegister), val);
			return;
		}
		case 0xA14102 ... 0xC00000 - 1: {
			setValue<T>(reserved5, index - 0xA14102, sizeof(reserved5), val);
			return;
		}
		case 0xC00000 ... 0xC00011 - 1: {
			setValue<T>(VDPData, index - 0xC00000, sizeof(VDPData), val);
			return;
		}
		case 0xC00011 ... 0xC0001C - 1: {
			setValue<T>(PSGData, index - 0xC00011, sizeof(PSGData), val);
			return;
		}
		case 0xC0001C ... 0xC00020 - 1: {
			setValue<T>(DebugRegister, index - 0xC0001C, sizeof(DebugRegister), val);
			return;
		}
		case 0xC00020 ... 0xFF0000 - 1: {
			setValue<T>(reserved6, index - 0xC00020, sizeof(reserved6), val);
			return;
		}
		case 0xFF0000 ... 0xFFFFFF: {
			setValue<T>(ram, index - 0xFF0000, sizeof(ram), val);
			return;
		}
		default:
			throw std::invalid_argument("Invalid index");
	}
}
