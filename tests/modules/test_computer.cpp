// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file test_computer.cpp

#include <gtest/gtest.h>

#include <regex>

#include "computer_data.h"
#include "faker/computer.h"
#include "tests_helper.h"

using namespace ::testing;
using namespace ::faker;
using namespace faker::computer;

// class ComputerTest : public Test {};

TEST(ComputerTest, IpAddressWithSpecificType) {
    const auto ipv4 = ip_address(faker::IpAddressType::IPv4);
    ASSERT_FALSE(ipv4.empty());
    ASSERT_TRUE(std::regex_match(ipv4, std::regex(R"(^(\d{1,3}\.){3}\d{1,3}$)")));

    const auto ipv6 = ip_address(faker::IpAddressType::IPv6);
    ASSERT_FALSE(ipv6.empty());
    ASSERT_TRUE(std::regex_match(ipv6, std::regex(R"(^([0-9a-fA-F]{1,4}:){7}[0-9a-fA-F]{1,4}$)")));
}

TEST(ComputerTest, MacAddressValidFormat) {
    const auto mac = mac_address();
    ASSERT_FALSE(mac.empty());
    ASSERT_TRUE(std::regex_match(mac, std::regex(R"(^([0-9a-fA-F]{2}:){5}[0-9a-fA-F]{2}$)")));
}
