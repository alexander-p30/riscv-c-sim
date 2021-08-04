#ifndef TEST_H
#define TEST_H

void testSuccess(int *totalTests, int *failedTests);

void testFail();

void testSw(uint32_t address, int32_t kte, int32_t dado, int *totalTests, int *failedTests);

void testSb(uint32_t address, int32_t kte, int8_t dado, int32_t expectedValue, int *totalTests, int *failedTests);

void testLw(uint32_t address, int32_t kte, int32_t expectedValue, int *totalTests, int *failedTests);

void testLb(uint32_t address, int32_t kte, int32_t expectedValue, int *totalTests, int *failedTests);

void testLbu(uint32_t address, int32_t kte, int32_t expectedValue, int *totalTests, int *failedTests);

int main();

#endif
