#include <libcsc/smallvector/SmallVector.hpp>

#include <gtest/gtest.h>



TEST(smallvector, IsEmpty) {
    libcsc::SmallVector<int, 5> v;
    EXPECT_EQ(v.is_empty(), true);
    EXPECT_EQ(v.size(), 0);
    EXPECT_EQ(v.capacity(), 5);
    EXPECT_EQ(v.static_capacity(), 5);
}

TEST(stablevector, PushBack) {
    libcsc::SmallVector<int, 5> v;
    EXPECT_EQ(v.size(), 0);
    EXPECT_EQ(v.capacity(), 5);
    v.push_back(5);
    EXPECT_EQ(v.size(), 1);
    EXPECT_EQ(v[0], 5);
    EXPECT_EQ(v.capacity(), 5);
}


TEST(stablevector, Remove) {
    libcsc::SmallVector<int, 5> v;
    v.push_back(5);
    EXPECT_EQ(v[0], 5);
    v.push_back(6);
    EXPECT_EQ(v[1], 6);
    v.remove(0);
    EXPECT_EQ(v[0], 6);
}

TEST(stablevector, UpCapacity) {
    libcsc::SmallVector<int, 1> v;
    v.push_back(5);
    EXPECT_EQ(v.capacity(), 1);
    v.push_back(5);
    EXPECT_EQ(v.capacity(), 2);
}

TEST(stablevector, Clear) {
    libcsc::SmallVector<int, 1> v;
    v.push_back(5);
    EXPECT_EQ(v.size(), 1);
    EXPECT_EQ(v[0], 5);
    v.clear();
    EXPECT_EQ(v.size(), 0);
    EXPECT_EQ(v.is_empty(), true);
}

TEST(stablevector, Iterator) {
    libcsc::SmallVector<int, 5> v;
    v.push_back(5);
    EXPECT_EQ(*(v.begin()), 5);
    v.push_back(4);
    EXPECT_EQ(*(v.begin() + 1), 4);
    EXPECT_EQ(*(v.end() - 1), 4);


    int s = 0;
    for (auto it : v) {
        s += it;
    }
    EXPECT_EQ(s, 9);
}

