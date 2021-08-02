#ifndef TEST_H
#define TEST_H

void testSuccess(int *totalTests, int *failedTests);

void testFail();

void testLw(uint32_t address, int32_t kte, int32_t expectedValue, int *totalTests, int *failedTests);

void testSw(uint32_t address, int32_t kte, int32_t dado, int *totalTests, int *failedTests);

int main();

#endif
