//
// Created by ggonz on 2/4/2021.
//

#include "gtest/gtest.h"
#include "Simulator.h"

class SimulatorTest : public testing::Test{
protected:
    M68K::CPU cpu;

    void SetUp() override{

    }

    void TearDown() override{

    }

};
#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

TEST_F(SimulatorTest, M68KCheckCorrectSize) {
	EXPECT_EQ(sizeof(M68K::Data), sizeof(M68K::LongWord));
	EXPECT_EQ(sizeof(M68K::ConditionCodeRegister), sizeof(M68K::Byte));
	EXPECT_EQ(sizeof(M68K::SystemStatusRegister), sizeof(M68K::Byte));
	EXPECT_EQ(sizeof(M68K::StatusRegister), sizeof(M68K::Word));
    EXPECT_EQ(sizeof(M68K::AddressSpace), 0x1000000);
}

TEST_F(SimulatorTest, M68KSegmentedMemory) {
    M68K::Byte b = 5;
    cpu.mem->segMem.setValue<M68K::Byte>(0x400000, b);
    cpu.mem->segMem.getValue<M68K::Byte>(0x400000, b);
    EXPECT_EQ(b, 5);
}

TEST_F(SimulatorTest, M68KRawMemory) {
    M68K::Byte b = 5;
    cpu.mem->rawMem[0x400000] = b;
    cpu.mem->segMem.getValue<M68K::Byte>(0x400000, b);
    EXPECT_EQ(b, 5);
}

TEST_F(SimulatorTest, M68KMemoryBoundryTest) {
    M68K::LongWord lw;

    EXPECT_THROW(cpu.mem->segMem.getValue<M68K::LongWord>(0x400000 - 2, lw), std::invalid_argument);
}
#pragma clang diagnostic pop