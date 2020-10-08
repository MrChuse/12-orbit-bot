#include "gtest/gtest.h"
#include "main_func.h"

TEST(someTest, TestOnBuild){
    ASSERT_EQ(1, 1);
}

/*int main(int argc, char** argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}*/