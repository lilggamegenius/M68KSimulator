//
// Created by ggonz on 11/15/2021.
//

#pragma once

#include "../Simulator.h"
#include "../includes/BitMaskEnums.hpp"

namespace M68K::Opcodes {
	enum class AddressingMode : Byte {
		DataRegister, AddressRegister, Address, AddressWithPostInc, AddressWithPreDec, AddressWithDisplace, AddressWithIndex,
		PCWithDisplace, PCWithIndex, AbsoluteShort, AbsoluteLong, Immediate
	};

	enum class OperationSize : Byte {
		None, Byte = bit(1), Word = bit(2), Long = bit(3)
	};
	ENABLE_BITMASK_OPERATORS(OperationSize)

	enum class Condition: Byte {
		True, False, Higher, LowerOrSame, CarryClear, CarrySet, NotEqual, Equal, OverflowClear, OverflowSet,
		Plus, Minus, GreaterOrEqual, LessThan, GreaterThan, LessOrEqual
	};

	class Opcode {
	public:
		OperationSize dataSize = OperationSize::None;
		virtual Word getBits() = 0;
		virtual Word getMask() = 0;
		virtual Word getArgMask() = 0;
	};
}

/*
 * All supported instructions for the M68000
 * ABCD             - Add Decimal with Extend
 * ADD              - Add
 * ADDA             - Address
 * ADDI             - Add Immediate
 * ADDQ             - Add Quick
 * ADDX             - Add with Extend
 * AND              - Logical AND
 * ANDI             - Logical AND Immediate
 * ANDI to CCR      - AND Immediate to Condition Code Register
 * ANDI to SR 1     - AND Immediate to Status Register
 * ASL, ASR         - Arithmetic Shift Left and Right
 * Bcc              - Branch Conditionally
 * BCHG             - Test Bit and Change
 * BCLR             - Test Bit and Clear
 * BRA              - Branch
 * BSET             - Test Bit and Set
 * BSR              - Branch to Subroutine
 * BTST             - Test Bit
 * CHK              - Check Register Against Bound
 * CLR              - Clear
 * CMP              - Compare
 * CMPA             - Compare Address
 * CMPI             - Compare Immediate
 * CMPM             - Compare Memory to Memory
 * DBcc             - Test Condition, Decrement and Branch
 * DIVS             - Signed Divide
 * DIVU             - Unsigned Divide
 * EOR              - Logical Exclusive-OR
 * EORI             - Logical Exclusive-OR Immediate
 * EORI to CCR      - Exclusive-OR Immediate to Condition Code Register
 * EORI to SR 1     - Exclusive-OR Immediate to Status Register
 * EXG              - Exchange Registers
 * EXT              - Sign Extend
 * ILLEGAL          - Take Illegal Instruction Trap
 * JMP              - Jump
 * JSR              - Jump to Subroutine
 * LEA              - Load Effective Address
 * LINK             - Link and Allocate
 * LSL,LSR          - Logical Shift Left and Right
 * MOVE             - Move
 * MOVEA            - Move Address
 * MOVE to CCR      - Move to Condition Code Register
 * MOVE from SR 1   - Move from Status Register
 * MOVE to SR 1     - Move to Status Register
 * MOVE USP 1       - Move User Stack Pointer
 * MOVEM            - Move Multiple Registers
 * MOVEP            - Move Peripheral
 * MOVEQ            - Move Quick
 * MULS             - Signed Multiply
 * MULU             - Unsigned Multiply
 * NBCD             - Negate Decimal with Extend
 * NEG              - Negate
 * NEGX             - Negate with Extend
 * NOP              - No Operation
 * NOT              - Logical Complement
 * OR               - Logical Inclusive-OR
 * ORI              - Logical Inclusive-OR Immediate
 * ORI to CCR       - Inclusive-OR Immediate to Condition Code Register
 * ORI to SR 1      - Inclusive-OR Immediate to Status Register
 * PEA              - Push Effective Address
 * RESET 1          - Reset External Devices
 * ROL,ROR          - Rotate Left and Right
 * ROXL, ROXR       - Rotate with Extend Left and Right
 * RTE 1            - Return from Exception
 * RTR              - Return and Restore
 * RTS              - Return from Subroutine
 * SBCD             - Subtract Decimal with Extend
 * Scc              - Set Conditionally
 * STOP 1           - Stop
 * SUB              - Subtract
 * SUBA             - Subtract Address
 * SUBI             - Subtract Immediate
 * SUBQ             - Subtract Quick
 * SUBX             - Subtract with Extend
 * SWAP             - Swap Register Words
 * TAS              - Test Operand and Set
 * TRAP             - Trap
 * TRAPV            - Trap on Overflow
 * TST              - Test Operand
 * UNLK             - Unlink
 */