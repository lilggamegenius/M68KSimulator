//
// Created by ggonz on 2/10/2021.
//
#pragma once

#include <stdexcept>
#include "Simulator.h"

namespace M68K {
    enum Vectors{
        ResetStackPointer,
        ResetProgramCounter,
        AccessFault,
        AddressError,
        IllegalInstruction,
        IntegerDividebyZero,
        CHKCHK2Instruction,
        FTRAPccTRAPccTRAPVInstructions,
        PrivilegeViolation,
        Trace,
        Line1010Emulator,
        Line1111Emulator,
        Reserved,
        CoprocessorProtocolViolation,
        FormatError,
        UninitializedInterrupt,
    };

    constexpr const char* strings[] = {
            "Reset Initial Interrupt Stack Pointer",
            "Reset Initial Program Counter",
            "Access Fault",
            "Address Error",
            "Illegal Instruction",
            "Integer Divide by Zero",
            "CHK, CHK2 Instruction",
            "FTRAPcc, TRAPcc, TRAPV Instructions",
            "Privilege Violation",
            "Trace",
            "Line 1010 Emulator (Unimplemented A- Line Opcode)",
            "Line 1111 Emulator (Unimplemented F-Line Opcode)",
            "(Unassigned, Reserved)",
            "Coprocessor Protocol Violation",
            "Format Error",
            "Uninitialized Interrupt"
    };

    constexpr const char* getVectorString(const Vectors vector){
        return strings[vector];
    }


    template<Vectors v> class Exception : public std::runtime_error {
    public:
        Byte offset = v * 4;
        std::string error = getVectorString(v);

        explicit Exception(const std::string &arg) : runtime_error(arg) {

        }

        explicit Exception(const char *string) : runtime_error(string) {

        }

        explicit Exception(runtime_error &&error) noexcept: runtime_error(error) {

        }

        explicit Exception(const runtime_error &error) noexcept: runtime_error(error) {

        }
    };
}