/* 
 * Created by Matthias "Nelaty" Gensheimer on 28.02.21.
 * Copyright (c) 2021 Matthias Gensheimer. All rights reserved.
 */
#include "R3D/Utility/FixedSizeContainer.h"

#include "catch2/catch_all.hpp"

TEST_CASE("A zero size container can not hold elements")
{
    r3::FixedSizeContainer<int> container;
    CHECK(container.getSize() == 0);
    CHECK(container.getEntriesLeft() == 0);
    CHECK(container.getEntriesUsed() == 0);
    CHECK(container.getAvailableEntry() == nullptr);
}

TEST_CASE("Initialize the container and add elements")
{
    r3::FixedSizeContainer<int> container;
    SECTION("A zero size container can not hold elements")
    {
        container.init(0);
        CHECK(container.getSize() == 0);
        CHECK(container.getEntriesUsed() == 0);
        CHECK(container.getEntriesLeft() == 0);
        CHECK(container.isFull());
        CHECK_FALSE(container.isEmpty());
        CHECK(container.getAvailableEntry() == nullptr);
    }
    SECTION("A container with a size of one can hold one element")
    {
        container.init(1);
        CHECK(container.getSize() == 1);
        CHECK(container.getEntriesUsed() == 0);
        CHECK(container.getEntriesLeft() == 1);
        CHECK(container.isEmpty());
        CHECK_FALSE(container.isFull());

        int* entry = container.getAvailableEntry();
        *entry = 5;
        CHECK(container.getEntriesUsed() == 1);
        CHECK(container.getEntriesLeft() == 0);
        CHECK(container.isFull());
        CHECK_FALSE(container.isEmpty());
        CHECK(container.getAvailableEntry() == nullptr);
        CHECK(*entry == 5);
    }
    SECTION("A container with a size of two can hold two elements")
    {
        container.init(2);
        CHECK(container.getSize() == 2);
        CHECK(container.getEntriesUsed() == 0);
        CHECK(container.getEntriesLeft() == 2);
        CHECK(container.isEmpty());

        int* entry1 = container.getAvailableEntry();
        *entry1 = -24;
        CHECK(container.getEntriesLeft() == 1);
        CHECK(container.getEntriesUsed() == 1);
        CHECK_FALSE(container.isFull());
        CHECK_FALSE(container.isEmpty());

        int* entry2 = container.getAvailableEntry();
        *entry2 = 55;
        CHECK(container.getEntriesUsed() == 2);
        CHECK(container.getEntriesLeft() == 0);
        CHECK_FALSE(container.isEmpty());
        CHECK(container.isFull());
        CHECK(container.getAvailableEntry() == nullptr);

        CHECK(entry1 != entry2);
        CHECK(*entry1 == -24);
        CHECK(*entry2 == 55);
        CHECK(container.getSize() == 2);
    }
}

TEST_CASE("Access first and last elements of a container")
{
    r3::FixedSizeContainer<int> container(20);
    CHECK(container.front() == nullptr);
    CHECK(container.back() == nullptr);
    CHECK(container.getData().size() == 20);

    {
        int* entry = container.getAvailableEntry();
        REQUIRE(entry != nullptr);
        *entry = 1;
        CHECK(container.front() == container.back());
        CHECK(*container.front() == 1);
        const auto& allEntries = container.getData();
        CHECK(allEntries.size() == 20);
        CHECK(allEntries[0] == 1);
    }
    {
        int* entry = container.getAvailableEntry();
        REQUIRE(entry != nullptr);
        *entry = 2;
        CHECK(container.front() != container.back());
        CHECK(*container.front() == 1);
        CHECK(*container.back() == 2);
        const auto& allEntries = container.getData();
        CHECK(allEntries.size() == 20);
        CHECK(allEntries[0] == 1);
        CHECK(allEntries[1] == 2);
    }
    container.init(20);
    CHECK(container.getSize() == 20);
    CHECK(container.getData().size() == 20);
}

TEST_CASE("Reset a container")
{
    r3::FixedSizeContainer<int> container(5);
    for(int i = 0; i < 5; ++i)
    {
        *container.getAvailableEntry() = i;
        CHECK(*container.back() == i);
    }
    CHECK(container.getEntriesLeft() == 0);
    container.reset();
    CHECK(container.getEntriesLeft() == 5);
    CHECK(container.front() == nullptr);
    CHECK(container.back() == nullptr);
    for(int i = 0; i < 5; ++i)
    {
        CHECK(*container.getAvailableEntry() == i);
    }
}