// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file test_computer.cpp

#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <regex>

#include "computer_data.h"
#include "faker/computer.h"
#include "tests_helper.h"

using namespace ::testing;
using namespace ::faker;
using namespace faker::computer;

TEST(ComputerTest, ShouldGenerateIPv4Address) {
    const auto generated_ipv4 = ip_address(IpAddressType::IPv4);
    ASSERT_FALSE(generated_ipv4.empty());
    ASSERT_TRUE(std::regex_match(generated_ipv4, std::regex(R"(^(\d{1,3}\.){3}\d{1,3}$)")));
}

TEST(ComputerTest, ShouldGenerateUniqueIPv4Address) {
    const auto generated_ipv4 = ip_address(IpAddressType::IPv4, true);
    ASSERT_FALSE(generated_ipv4.empty());
    ASSERT_TRUE(std::regex_match(generated_ipv4, std::regex(R"(^(\d{1,3}\.){3}\d{1,3}$)")));
}

TEST(ComputerTest, ShouldGenerateIPv6Address) {
    const auto generated_ipv6 = ip_address(IpAddressType::IPv6);
    ASSERT_FALSE(generated_ipv6.empty());
    ASSERT_TRUE(std::regex_match(generated_ipv6, std::regex(R"(^([0-9a-fA-F]{1,4}:){7}[0-9a-fA-F]{1,4}$)")));
}

TEST(ComputerTest, ShouldGenerateUniqueIPv6Address) {
    const auto generated_ipv6 = ip_address(IpAddressType::IPv6, true);
    ASSERT_FALSE(generated_ipv6.empty());
    ASSERT_TRUE(std::regex_match(generated_ipv6, std::regex(R"(^([0-9a-fA-F]{1,4}:){7}[0-9a-fA-F]{1,4}$)")));
}

TEST(ComputerTest, ShouldGenerateMacAddress) {
    const auto generated_mac = mac_address();
    ASSERT_FALSE(generated_mac.empty());
    ASSERT_TRUE(std::regex_match(generated_mac, std::regex(R"(^([0-9a-fA-F]{2}:){5}[0-9a-fA-F]{2}$)")));
}

TEST(ComputerTest, ShouldGenerateUniqueMacAddress) {
    const auto generated_mac = mac_address(true);
    ASSERT_FALSE(generated_mac.empty());
    ASSERT_TRUE(std::regex_match(generated_mac, std::regex(R"(^([0-9a-fA-F]{2}:){5}[0-9a-fA-F]{2}$)")));
}

struct OperatingSystemsPattern {
    OperatingSystems operating_systems;
};

const std::unordered_map<OperatingSystems, std::string> path_patterns_with_extensions = {
    {OperatingSystems::Windows, R"(^[a-zA-Z]:\\(?:[^\s/:*?""<>|]+\\)*[^\s/:*?""<>|]+\.(?:[^\s/:*?""<>|]+|)$)"},
    {OperatingSystems::macOS, R"(^/(?:[^\s/:*?""<>|]+/)*[^\s/:*?""<>|]+\.(?:[^\s/:*?""<>|]+|)$)"},
    {OperatingSystems::Linux, R"(^/(?:[^\s/:*?""<>|]+/)*[^\s/:*?""<>|]+\.(?:[^\s/:*?""<>|]+|)$)"},
};

const std::unordered_map<OperatingSystems, std::string> path_patterns_without_extensions = {
    {OperatingSystems::Windows, R"(^[a-zA-Z]:\\(?:[^\s/:*?""<>|]+\\)*[^\s/:*?""<>|]+$)"},
    {OperatingSystems::macOS, R"(^/(?:[^\s/:*?""<>|]+/)*[^\s/:*?""<>|]+$)"},
    {OperatingSystems::Linux, R"(^/(?:[^\s/:*?""<>|]+/)*[^\s/:*?""<>|]+$)"},
};

const std::unordered_map<OperatingSystems, std::string> directory_patterns = {
    {OperatingSystems::Windows, R"(^[a-zA-Z]:\\(?:[^\s/:*?""<>|]+\\)*[^\s/:*?""<>|]+\\?$)"},
    {OperatingSystems::macOS, R"(^/(?:[^\s/:*?""<>|]+/)*[^\s/:*?""<>|]+/?$)"},
    {OperatingSystems::Linux, R"(^/(?:[^\s/:*?""<>|]+/)*[^\s/:*?""<>|]+/?$)"},
};

const std::string name_pattern_with_extensions = R"(^[^\s/:*?""<>|]+\.[^\s/:*?""<>|]+$)";

const std::string name_pattern_without_extensions = R"(^[^\s/:*?""<>|]+$)";

class FileSystemsTest : public TestWithParam<OperatingSystems> {};

TEST_P(FileSystemsTest, ShouldGenerateFilePathWithExtensions) {
    const auto& operating_systems = GetParam();
    const auto  generated_path = file_path(operating_systems, std::to_array<std::string_view>({"jpg", "png", "txt"}));
    ASSERT_FALSE(generated_path.empty());
    ASSERT_TRUE(std::regex_match(generated_path, std::regex(path_patterns_with_extensions.at(operating_systems))));
}

TEST_P(FileSystemsTest, ShouldGenerateFilePathWithUnknownExtensions) {
    const auto& operating_systems = GetParam();
    const auto  generated_path    = file_path(operating_systems, std::to_array<std::string_view>({"abc", "cbd"}));
    ASSERT_FALSE(generated_path.empty());
    ASSERT_TRUE(std::regex_match(generated_path, std::regex(path_patterns_with_extensions.at(operating_systems))));
}

TEST_P(FileSystemsTest, ShouldGenerateFilePathWithoutExtensions) {
    const auto& operating_systems = GetParam();
    const auto  generated_path    = file_path(operating_systems, {});
    ASSERT_FALSE(generated_path.empty());
    ASSERT_TRUE(std::regex_match(generated_path, std::regex(path_patterns_without_extensions.at(operating_systems))));
}

TEST_P(FileSystemsTest, ShouldGenerateFileDirectory) {
    const auto& operating_systems   = GetParam();
    const auto  generated_directory = file_directory(operating_systems);
    ASSERT_FALSE(generated_directory.empty());
    ASSERT_TRUE(std::regex_match(generated_directory, std::regex(directory_patterns.at(operating_systems))));
}

TEST_P(FileSystemsTest, ShouldGenerateFileNameWithExtensions) {
    const auto generated_name = file_name(std::to_array<std::string_view>({"jpg", "png", "txt"}));
    ASSERT_FALSE(generated_name.empty());
    ASSERT_TRUE(std::regex_match(generated_name, std::regex(name_pattern_with_extensions)));
}

TEST_P(FileSystemsTest, ShouldGenerateFileNameWithoutExtensions) {
    const auto generated_name = file_name({});
    ASSERT_FALSE(generated_name.empty());
    ASSERT_TRUE(std::regex_match(generated_name, std::regex(name_pattern_without_extensions)));
}

TEST_P(FileSystemsTest, ShouldGenerateFileExtensionWithExtensions) {
    const auto generated_extension = file_extension(std::to_array<std::string_view>({"jpg", "png", "txt"}));
    ASSERT_FALSE(generated_extension.empty());
}

TEST_P(FileSystemsTest, ShouldGenerateFileExtensionWithoutExtensions) {
    const auto generated_extension = file_extension({});
    ASSERT_TRUE(generated_extension.empty());
}

TEST_P(FileSystemsTest, ShouldGenerateFileWithExtensions) {
    const auto& operating_systems = GetParam();

    File file(operating_systems, std::to_array<std::string_view>({"jpg", "png", "txt"}));

    const auto generated_path      = file.path();
    const auto generated_directory = file.directory();
    const auto generated_name      = file.name();
    const auto generated_extension = file.extension();

    ASSERT_FALSE(generated_path.empty());
    ASSERT_TRUE(std::regex_match(generated_path, std::regex(path_patterns_with_extensions.at(operating_systems))));
    ASSERT_FALSE(generated_directory.empty());
    ASSERT_TRUE(std::regex_match(generated_directory, std::regex(directory_patterns.at(operating_systems))));
    ASSERT_FALSE(generated_name.empty());
    ASSERT_TRUE(std::regex_match(generated_name, std::regex(name_pattern_with_extensions)));
    ASSERT_FALSE(generated_extension.empty());

    file.reroll();

    const auto reroll_path      = file.path();
    const auto reroll_directory = file.directory();
    const auto reroll_name      = file.name();
    const auto reroll_extension = file.extension();

    ASSERT_FALSE(reroll_path.empty());
    ASSERT_TRUE(std::regex_match(reroll_path, std::regex(path_patterns_with_extensions.at(operating_systems))));
    ASSERT_FALSE(reroll_directory.empty());
    ASSERT_TRUE(std::regex_match(reroll_directory, std::regex(directory_patterns.at(operating_systems))));
    ASSERT_FALSE(reroll_name.empty());
    ASSERT_TRUE(std::regex_match(reroll_name, std::regex(name_pattern_with_extensions)));
    ASSERT_FALSE(reroll_extension.empty());
}

TEST_P(FileSystemsTest, ShouldGenerateFileWithUnknownExtensions) {
    const auto& operating_systems = GetParam();

    File file(operating_systems, std::to_array<std::string_view>({"abc", "cbd"}));

    const auto generated_path      = file.path();
    const auto generated_directory = file.directory();
    const auto generated_name      = file.name();
    const auto generated_extension = file.extension();

    ASSERT_FALSE(generated_path.empty());
    ASSERT_TRUE(std::regex_match(generated_path, std::regex(path_patterns_with_extensions.at(operating_systems))));
    ASSERT_FALSE(generated_directory.empty());
    ASSERT_TRUE(std::regex_match(generated_directory, std::regex(directory_patterns.at(operating_systems))));
    ASSERT_FALSE(generated_name.empty());
    ASSERT_TRUE(std::regex_match(generated_name, std::regex(name_pattern_with_extensions)));
    ASSERT_FALSE(generated_extension.empty());

    file.reroll();

    const auto reroll_path      = file.path();
    const auto reroll_directory = file.directory();
    const auto reroll_name      = file.name();
    const auto reroll_extension = file.extension();

    ASSERT_FALSE(reroll_path.empty());
    ASSERT_TRUE(std::regex_match(reroll_path, std::regex(path_patterns_with_extensions.at(operating_systems))));
    ASSERT_FALSE(reroll_directory.empty());
    ASSERT_TRUE(std::regex_match(reroll_directory, std::regex(directory_patterns.at(operating_systems))));
    ASSERT_FALSE(reroll_name.empty());
    ASSERT_TRUE(std::regex_match(reroll_name, std::regex(name_pattern_with_extensions)));
    ASSERT_FALSE(reroll_extension.empty());
}

TEST_P(FileSystemsTest, ShouldGenerateFileWithoutExtensions) {
    const auto operating_systems = GetParam();

    File file(operating_systems, {});

    const auto generated_path      = file.path();
    const auto generated_directory = file.directory();
    const auto generated_name      = file.name();
    const auto generated_extension = file.extension();

    ASSERT_FALSE(generated_path.empty());
    ASSERT_TRUE(std::regex_match(generated_path, std::regex(path_patterns_without_extensions.at(operating_systems))));
    ASSERT_FALSE(generated_directory.empty());
    ASSERT_TRUE(std::regex_match(generated_directory, std::regex(directory_patterns.at(operating_systems))));
    ASSERT_FALSE(generated_name.empty());
    ASSERT_TRUE(std::regex_match(generated_name, std::regex(name_pattern_without_extensions)));
    ASSERT_TRUE(generated_extension.empty());

    file.reroll();

    const auto reroll_path      = file.path();
    const auto reroll_directory = file.directory();
    const auto reroll_name      = file.name();
    const auto reroll_extension = file.extension();

    ASSERT_FALSE(reroll_path.empty());
    ASSERT_TRUE(std::regex_match(reroll_path, std::regex(path_patterns_without_extensions.at(operating_systems))));
    ASSERT_FALSE(reroll_directory.empty());
    ASSERT_TRUE(std::regex_match(reroll_directory, std::regex(directory_patterns.at(operating_systems))));
    ASSERT_FALSE(reroll_name.empty());
    ASSERT_TRUE(std::regex_match(reroll_name, std::regex(name_pattern_without_extensions)));
    ASSERT_TRUE(reroll_extension.empty());
}

INSTANTIATE_TEST_SUITE_P(
    FileSystemsTests,
    FileSystemsTest,
    ValuesIn(
        std::vector<OperatingSystems>({OperatingSystems::Windows, OperatingSystems::macOS, OperatingSystems::Linux})
    ),
    [](const TestParamInfo<OperatingSystems>& param_info) { return to_string(param_info.param); }
);

TEST(ComputerTest, ShouldGenerateUrlWithSubdomain) {
    const auto generated_url =
        url(std::to_array<std::string_view>({"auth", "drive", "image"}),
            std::to_array<std::string_view>({"com", "org", "net"}));
    ASSERT_FALSE(generated_url.empty());
    ASSERT_TRUE(
        std::regex_match(generated_url, std::regex(R"(^https://[^\s/:*?""<>|]+\.[^\s/:*?""<>|]+\.[^\s/:*?""<>|]+$)"))
    );
}

TEST(ComputerTest, ShouldGenerateUrlWithoutSubdomain) {
    const auto generated_url = url({}, std::to_array<std::string_view>({"com", "org", "net"}));
    ASSERT_FALSE(generated_url.empty());
    ASSERT_TRUE(std::regex_match(generated_url, std::regex(R"(^https://[^\s/:*?""<>|]+\.[^\s/:*?""<>|]+$)")));
}

TEST(ComputerTest, ShouldGenerateUrlWhenNullOptional) {
    const auto generated_url = url();
    ASSERT_FALSE(generated_url.empty());
    ASSERT_TRUE(std::regex_match(generated_url, std::regex(R"(^https://[^\s/:*?""<>|]+\.[^\s/:*?""<>|]+$)")));
}

TEST(ComputerTest, ShouldGenerateUniqueUrl) {
    const auto generated_url = url({}, std::to_array<std::string_view>({"com", "org", "net"}), true);
    ASSERT_FALSE(generated_url.empty());
    ASSERT_TRUE(std::regex_match(generated_url, std::regex(R"(^https://[^\s/:*?""<>|]+\.[^\s/:*?""<>|]+$)")));
}

TEST(ComputerTest, ShouldThrowExceptionWhenTldsOfUrlIsEmpty) {
    std::vector<std::string_view> empty_tlds = {};
    ASSERT_THROW(url(std::to_array<std::string_view>({"auth", "drive", "image"}), empty_tlds), std::invalid_argument);
}

TEST(ComputerTest, ShouldGenerateHostnameWithSubdomain) {
    const auto generated_hostname = hostname(
        std::to_array<std::string_view>({"auth", "drive", "image"}),
        std::to_array<std::string_view>({"com", "org", "net"})
    );
    ASSERT_FALSE(generated_hostname.empty());
    ASSERT_TRUE(
        std::regex_match(generated_hostname, std::regex(R"(^[^\s/:*?""<>|.]+?\.[^\s/:*?""<>|.]+?\.[^\s/:*?""<>|.]+$)"))
    );
}

TEST(ComputerTest, ShouldGenerateHostnameWhenNullOptional) {
    const auto generated_hostname = hostname(std::to_array<std::string_view>({"auth", "drive", "image"}));
    ASSERT_FALSE(generated_hostname.empty());
    ASSERT_TRUE(
        std::regex_match(generated_hostname, std::regex(R"(^[^\s/:*?""<>|.]+?\.[^\s/:*?""<>|.]+?\.[^\s/:*?""<>|.]+$)"))
    );
}

TEST(ComputerTest, ShouldGenerateHostnameWithoutSubdomain) {
    const auto generated_hostname = hostname({}, std::to_array<std::string_view>({"com", "org", "net"}));
    ASSERT_FALSE(generated_hostname.empty());
    ASSERT_TRUE(std::regex_match(generated_hostname, std::regex(R"(^[^\s/:*?""<>|.]+?\.[^\s/:*?""<>|.]+$)")));
}

TEST(ComputerTest, ShouldGenerateUniqueHostname) {
    const auto generated_hostname = hostname({}, std::to_array<std::string_view>({"com", "org", "net"}), true);
    ASSERT_FALSE(generated_hostname.empty());
    ASSERT_TRUE(std::regex_match(generated_hostname, std::regex(R"(^[^\s/:*?""<>|.]+?\.[^\s/:*?""<>|.]+$)")));
}

TEST(ComputerTest, ShouldThrowExceptionWhenTldsOfHostnameIsEmpty) {
    std::vector<std::string_view> empty_tlds = {};
    ASSERT_THROW(
        hostname(std::to_array<std::string_view>({"auth", "drive", "image"}), empty_tlds),
        std::invalid_argument
    );
}
