// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file computer.cpp

#include "faker/computer.h"

#include <algorithm>
#include <format>
#include <optional>
#include <random>
#include <source_location>
#include <span>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "computer_data.h"
#include "faker/types/enums.h"
#include "permutation_generator.h"
#include "person_data.h"
#include "random_engine.h"
#include "random_helper.h"
#include "string_helper.h"
#include "validation.h"

namespace faker::computer {

namespace {

PermutationGenerator ipv4_pg(20000000ULL, 4000000000ULL - 1);
PermutationGenerator ipv6_low_pg(20000000000000000ULL, 200000000000000000ULL - 1);
PermutationGenerator mac_pg(100000000ULL, 100000000000ULL - 1);

PermutationGenerator url_pg(0, 2176782336 - 1, PermutationGenerator::BaseN::Base36);       //  36^6 - 1
PermutationGenerator hostname_pg(0, 2176782336 - 1, PermutationGenerator::BaseN::Base36);  //  36^6 - 1

constexpr std::size_t kUniqueSuffixWidth = 6;
constexpr std::string_view kBase36Chars  = "0123456789abcdefghijklmnopqrstuvwxyz";

std::string get_username();

void validate_non_empty_items(
    const std::span<const std::string_view> values,
    const std::string_view                  name,
    const std::source_location&             location = std::source_location::current()
) {
    if (std::ranges::any_of(values, [](const std::string_view value) { return value.empty(); })) {
        throw_exception<std::invalid_argument>(
            "Invalid string: '" + std::string(name) + "' must not contain empty items.",
            location
        );
    }
}

std::string to_base36_fixed_width(uint64_t value, const std::size_t width) {
    std::string out(width, '0');
    for (std::size_t i = 0; i < width; ++i) {
        out[width - 1 - i] = kBase36Chars[value % 36];
        value /= 36;
    }
    return out;
}

std::string generate_host_value(
    const std::span<const std::string_view>          subdomains,
    std::optional<std::span<const std::string_view>> tlds,
    const bool                                       unique,
    PermutationGenerator&                            generator,
    const bool                                       include_protocol
) {
    if (!subdomains.empty()) { validate_non_empty_items(subdomains, "subdomains"); }

    std::string subdomain;
    std::string tld;

    if (!subdomains.empty()) { subdomain = std::string(pick_one(subdomains)); }

    if (tlds.has_value()) {
        check_empty<std::invalid_argument>(tlds.value(), "tlds");
        validate_non_empty_items(tlds.value(), "tlds");
        tld = std::string(pick_one(tlds.value()));
    } else {
        tld = std::string(pick_one(kTldsDefault));
    }

    std::string username = get_username();
    if (unique) {
        username += to_base36_fixed_width(generator.next_uint64(), kUniqueSuffixWidth);
    }

    std::string host;
    if (subdomain.empty()) {
        host = username + "." + tld;
    } else {
        host = subdomain + "." + username + "." + tld;
    }

    if (!include_protocol) { return host; }
    return "https://" + host;
}

FileTypes pick_file_type() {
    constexpr std::array file_types = {
        FileTypes::Application,
        FileTypes::Archive,
        FileTypes::Audio,
        FileTypes::Configuration,
        FileTypes::Development,
        FileTypes::Document,
        FileTypes::Font,
        FileTypes::Image,
        FileTypes::Installer,
        FileTypes::Library,
        FileTypes::Log,
        FileTypes::Temporary,
        FileTypes::Video,
    };
    std::mt19937_64&              random_engine = get_random_engine();
    std::uniform_int_distribution distribution(0, static_cast<int>(file_types.size()) - 1);
    const FileTypes               random_file_type = file_types[distribution(random_engine)];
    return random_file_type;
}

std::string get_username() {
    auto const selected_name_language = pick_language(
        Languages::English | Languages::SimplifiedChinese | Languages::TraditionalChinese | Languages::Japanese
    );

    std::string_view username;
    switch (selected_name_language) {
    case Languages::English: username = pick_one(person::kEnglishSocialNetworkId).translation; break;
    case Languages::SimplifiedChinese:
        username = pick_one(person::kSimplifiedChineseSocialNetworkId).translation;
        break;
    case Languages::TraditionalChinese:
        username = pick_one(person::kTraditionalChineseSocialNetworkId).translation;
        break;
    case Languages::Japanese: username = pick_one(person::kJapaneseSocialNetworkId).translation; break;
    }
    return std::string(username);
}

}  // namespace

std::string ip_address(const IpAddressType ip_address_type, const bool unique) {
    std::mt19937_64& random_engine = get_random_engine();

    if (ip_address_type == IpAddressType::IPv4) {
        if (unique) {
            const uint32_t value = static_cast<uint32_t>(ipv4_pg.next_uint64());
            return std::format("{}.{}.{}.{}", value >> 24 & 0xFF, value >> 16 & 0xFF, value >> 8 & 0xFF, value & 0xFF);
        }
        std::uniform_int_distribution distribution(0, 255);
        return std::to_string(distribution(random_engine)) +
               "." +
               std::to_string(distribution(random_engine)) +
               "." +
               std::to_string(distribution(random_engine)) +
               "." +
               std::to_string(distribution(random_engine));
    }

    std::uniform_int_distribution distribution(0, 0xFFFF);

    const auto ip0 = static_cast<uint16_t>(distribution(random_engine));
    const auto ip1 = static_cast<uint16_t>(distribution(random_engine));
    const auto ip2 = static_cast<uint16_t>(distribution(random_engine));
    const auto ip3 = static_cast<uint16_t>(distribution(random_engine));

    if (unique) {
        const uint64_t low_value = ipv6_low_pg.next_uint64();

        const auto ip4 = static_cast<uint16_t>(low_value >> 48 & 0xFFFF);
        const auto ip5 = static_cast<uint16_t>(low_value >> 32 & 0xFFFF);
        const auto ip6 = static_cast<uint16_t>(low_value >> 16 & 0xFFFF);
        const auto ip7 = static_cast<uint16_t>(low_value & 0xFFFF);

        return std::format(
            "{:04x}:{:04x}:{:04x}:{:04x}:{:04x}:{:04x}:{:04x}:{:04x}",
            ip0,
            ip1,
            ip2,
            ip3,
            ip4,
            ip5,
            ip6,
            ip7
        );
    }

    const auto ip4 = static_cast<uint16_t>(distribution(random_engine));
    const auto ip5 = static_cast<uint16_t>(distribution(random_engine));
    const auto ip6 = static_cast<uint16_t>(distribution(random_engine));
    const auto ip7 = static_cast<uint16_t>(distribution(random_engine));

    return std::format(
        "{:04x}:{:04x}:{:04x}:{:04x}:{:04x}:{:04x}:{:04x}:{:04x}",
        ip0,
        ip1,
        ip2,
        ip3,
        ip4,
        ip5,
        ip6,
        ip7
    );
}

std::string mac_address(const bool unique) {
    std::mt19937_64&              random_engine = get_random_engine();
    std::uniform_int_distribution distribution(0, 255);

    const unsigned int rand_byte = distribution(random_engine);

    auto mac0 = static_cast<uint8_t>(rand_byte & 0xFE | 0x02);

    if (unique) {
        const uint64_t value = mac_pg.next_uint64();

        const auto mac1 = static_cast<uint8_t>(value >> 32 & 0xFF);
        const auto mac2 = static_cast<uint8_t>(value >> 24 & 0xFF);
        const auto mac3 = static_cast<uint8_t>(value >> 16 & 0xFF);
        const auto mac4 = static_cast<uint8_t>(value >> 8 & 0xFF);
        const auto mac5 = static_cast<uint8_t>(value & 0xFF);

        return std::format("{:02x}:{:02x}:{:02x}:{:02x}:{:02x}:{:02x}", mac0, mac1, mac2, mac3, mac4, mac5);
    }

    const auto mac1 = distribution(random_engine);
    const auto mac2 = distribution(random_engine);
    const auto mac3 = distribution(random_engine);
    const auto mac4 = distribution(random_engine);
    const auto mac5 = distribution(random_engine);

    return std::format("{:02x}:{:02x}:{:02x}:{:02x}:{:02x}:{:02x}", mac0, mac1, mac2, mac3, mac4, mac5);
}

std::string file_path(const OperatingSystems operating_systems, const std::span<const std::string_view> extensions) {
    auto const selected_operating_system = pick_operating_system(operating_systems);

    char separator = '/';

    std::string_view path_format;
    switch (selected_operating_system) {
    case OperatingSystems::Windows:
        path_format = pick_one(kWindowsPathFormats);
        separator   = '\\';
        break;
    case OperatingSystems::macOS: path_format = pick_one(kMacOSPathFormats); break;
    case OperatingSystems::Linux: path_format = pick_one(kLinuxPathFormats); break;
    }

    const auto username = get_username();

    const std::string base_path   = replace_placeholder(path_format, username);
    std::string       folder_path = base_path;
    std::string       extension;
    if (extensions.empty()) {
        const auto selected_file_type = pick_file_type();
        folder_path                   = base_path + separator + std::string(kFoldersMap.at(selected_file_type));
    } else {
        // Get extension
        extension               = std::string(pick_one(extensions));
        const auto extension_it = kExtensionsMap.find(extension);
        const auto file_type    = extension_it == kExtensionsMap.end() ? FileTypes::Other : extension_it->second;
        const auto folder_it    = kFoldersMap.find(file_type);
        const auto folder       = folder_it == kFoldersMap.end() ? "" : folder_it->second;
        if (folder.empty()) {
            folder_path = base_path + separator + extension;
        } else {
            folder_path = base_path + separator + std::string(folder);
        }
    }

    const auto file_name_format    = pick_one(kFileNameFormats);
    const auto file_name_main_part = pick_one(kFileNameMainParts);
    const auto file_name           = replace_wildcard_with_letter(
        replace_wildcard_with_digit(replace_placeholder(file_name_format, file_name_main_part))
    );

    if (extensions.empty()) { return folder_path + separator + file_name; }

    return folder_path + separator + file_name + "." + extension;
}

std::string file_directory(const OperatingSystems operating_systems) {
    auto const selected_operating_system = pick_operating_system(operating_systems);

    char separator = '/';

    std::string_view path_format;
    switch (selected_operating_system) {
    case OperatingSystems::Windows:
        path_format = pick_one(kWindowsPathFormats);
        separator   = '\\';
        break;
    case OperatingSystems::macOS: path_format = pick_one(kMacOSPathFormats); break;
    case OperatingSystems::Linux: path_format = pick_one(kLinuxPathFormats); break;
    }

    const auto        username  = get_username();
    const std::string base_path = replace_placeholder(path_format, username);
    std::string       folder_path;
    const auto        file_type = pick_file_type();
    const auto        folder_it = kFoldersMap.find(file_type);
    const auto        folder    = folder_it == kFoldersMap.end() ? "" : folder_it->second;
    if (folder.empty()) {
        folder_path = base_path;
    } else {
        folder_path = base_path + separator + std::string(folder);
    }

    return folder_path;
}

std::string file_name(const std::span<const std::string_view> extensions) {
    std::string extension;
    if (!extensions.empty()) {
        // Get extension
        extension = std::string(pick_one(extensions));
    }
    const auto file_name_format    = pick_one(kFileNameFormats);
    const auto file_name_main_part = pick_one(kFileNameMainParts);
    auto       file_name           = replace_wildcard_with_letter(
        replace_wildcard_with_digit(replace_placeholder(file_name_format, file_name_main_part))
    );
    if (extensions.empty()) { return file_name; }
    return file_name + "." + extension;
}

std::string file_extension(const std::span<const std::string_view> extensions) {
    if (extensions.empty()) { return ""; }
    return std::string(pick_one(extensions));
}

std::string url(
    const std::span<const std::string_view>          subdomains,
    std::optional<std::span<const std::string_view>> tlds,
    const bool                                       unique
) {
    return generate_host_value(subdomains, tlds, unique, url_pg, true);
}

std::string hostname(
    const std::span<const std::string_view>          subdomains,
    std::optional<std::span<const std::string_view>> tlds,
    const bool                                       unique
) {
    return generate_host_value(subdomains, tlds, unique, hostname_pg, false);
}

File::File(const OperatingSystems operating_systems, const std::span<const std::string_view> extensions) :
    operating_systems_(operating_systems), extensions_(extensions.begin(), extensions.end()) {
    roll();
}

File::~File() = default;

void File::reroll() {
    roll();
}

std::string File::path() const {
    return path_;
}

std::string File::directory() const {
    return directory_;
}

std::string File::name() const {
    return name_;
}

std::string File::extension() const {
    return extension_;
}

void File::roll() {
    selected_operating_system_ = pick_operating_system(operating_systems_);

    char separator = '/';

    std::string_view path_format;
    switch (selected_operating_system_) {
    case OperatingSystems::Windows:
        path_format = pick_one(kWindowsPathFormats);
        separator   = '\\';
        break;
    case OperatingSystems::macOS: path_format = pick_one(kMacOSPathFormats); break;
    case OperatingSystems::Linux: path_format = pick_one(kLinuxPathFormats); break;
    }

    const auto username = get_username();

    const std::string base_path   = replace_placeholder(path_format, username);
    std::string       folder_path = base_path;
    std::string       extension;
    if (extensions_.empty()) {
        const auto selected_file_type = pick_file_type();
        folder_path                   = base_path + separator + std::string(kFoldersMap.at(selected_file_type));
        extension                     = "";
    } else {
        // Get extension
        extension               = pick_one<std::string>(extensions_);
        const auto extension_it = kExtensionsMap.find(extension);
        const auto file_type    = extension_it == kExtensionsMap.end() ? FileTypes::Other : extension_it->second;
        const auto folder_it    = kFoldersMap.find(file_type);
        const auto folder       = folder_it == kFoldersMap.end() ? "" : folder_it->second;
        if (folder.empty()) {
            folder_path = base_path + separator + extension;
        } else {
            folder_path = base_path + separator + std::string(folder);
        }
    }

    const auto file_name_format    = pick_one(kFileNameFormats);
    const auto file_name_main_part = pick_one(kFileNameMainParts);
    const auto file_name           = replace_wildcard_with_letter(
        replace_wildcard_with_digit(replace_placeholder(file_name_format, file_name_main_part))
    );

    if (extensions_.empty()) {
        path_ = folder_path + separator + file_name;
        name_ = file_name;
    } else {
        path_ = folder_path + separator + file_name + "." + extension;
        name_ = file_name + "." + extension;
    }
    directory_ = folder_path;
    extension_ = extension;
}

}  // namespace faker::computer
