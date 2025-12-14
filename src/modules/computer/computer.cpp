// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file computer.cpp

#include "faker/computer.h"

#include <format>
#include <random>
#include <string>
#include <string_view>
#include <utility>

#include "business_data.h"
#include "computer_data.h"
#include "faker/types/enums.h"
#include "person_data.h"
#include "random_engine.h"
#include "random_helper.h"
#include "string_helper.h"
#include "validation.h"

namespace faker::computer {

static FileTypes pick_file_type() {
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

static std::string get_username() {
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

std::string ip_address(const IpAddressType ip_address_type) {
    std::mt19937_64& random_engine = get_random_engine();

    if (ip_address_type == IpAddressType::IPv4) {
        std::uniform_int_distribution distribution(0, 255);
        return std::to_string(distribution(random_engine)) +
               "." +
               std::to_string(distribution(random_engine)) +
               "." +
               std::to_string(distribution(random_engine)) +
               "." +
               std::to_string(distribution(random_engine));
    }

    std::uniform_int_distribution distribution(0, 0xffff);
    return std::format(
        "{:04x}:{:04x}:{:04x}:{:04x}:{:04x}:{:04x}:{:04x}:{:04x}",
        distribution(random_engine),
        distribution(random_engine),
        distribution(random_engine),
        distribution(random_engine),
        distribution(random_engine),
        distribution(random_engine),
        distribution(random_engine),
        distribution(random_engine)
    );
}

std::string mac_address() {
    std::mt19937_64&              random_engine = get_random_engine();
    std::uniform_int_distribution distribution(0, 255);

    const unsigned int rand_byte = distribution(random_engine);
    auto               mac0      = static_cast<unsigned char>(rand_byte & 0xFE | 0x02);
    return std::format(
        "{:02x}:{:02x}:{:02x}:{:02x}:{:02x}:{:02x}",
        mac0,
        distribution(random_engine),
        distribution(random_engine),
        distribution(random_engine),
        distribution(random_engine),
        distribution(random_engine)
    );
}

std::string
    file_path(const OperatingSystems operating_systems, const std::string_view extensions, const char delimiter) {
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
        auto extensions_vector  = split_and_trim(extensions, delimiter);
        extension               = pick_one<std::string>(extensions_vector);
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
    const auto file_name =
        replace_wildcard_to_letter(replace_wildcard_to_digit(replace_placeholder(file_name_format, file_name_main_part))
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

    const auto        username = get_username();
    std::string       extension;
    const std::string base_path   = replace_placeholder(path_format, username);
    std::string       folder_path = base_path;
    const auto        file_type   = pick_file_type();
    const auto        folder_it   = kFoldersMap.find(file_type);
    const auto        folder      = folder_it == kFoldersMap.end() ? "" : folder_it->second;
    folder_path                   = base_path + separator + std::string(folder);

    return folder_path;
}

std::string file_name(const std::string_view extensions, const char delimiter) {
    std::string extension;
    if (!extensions.empty()) {
        // Get extension
        auto extensions_vector = split_and_trim(extensions, delimiter);
        extension              = pick_one<std::string>(extensions_vector);
    }
    const auto file_name_format    = pick_one(kFileNameFormats);
    const auto file_name_main_part = pick_one(kFileNameMainParts);
    auto       file_name =
        replace_wildcard_to_letter(replace_wildcard_to_digit(replace_placeholder(file_name_format, file_name_main_part))
        );
    if (extensions.empty()) { return file_name; }
    return file_name + "." + extension;
}

std::string file_extension(const std::string_view extensions, const char delimiter) {
    if (extensions.empty()) { return ""; }
    return pick_one<std::string>(split_and_trim(extensions, delimiter));
}

std::string url(const std::string_view subdomains, const std::string_view tlds, const char delimiter) {
    CHECK_EMPTY(std::invalid_argument, tlds);

    std::string subdomain;

    if (subdomains.empty()) {
        subdomain = "";
    } else {
        subdomain = pick_one<std::string>(split_and_trim(subdomains, delimiter));
    }

    const auto tld = pick_one<std::string>(split_and_trim(tlds, delimiter));

    const auto username = get_username();

    if (subdomain.empty()) { return "https://" + username + "." + tld; }
    return "https://" + subdomain + "." + username + "." + tld;
}

std::string hostname(const std::string_view subdomains, const std::string_view tlds, const char delimiter) {
    CHECK_EMPTY(std::invalid_argument, tlds);

    std::string subdomain;

    if (subdomains.empty()) {
        subdomain = "";
    } else {
        subdomain = pick_one<std::string>(split_and_trim(subdomains, delimiter));
    }

    const auto tld = pick_one<std::string>(split_and_trim(tlds, delimiter));

    const auto username = get_username();

    if (subdomain.empty()) { return username + "." + tld; }
    return subdomain + "." + username + "." + tld;
}

File::File(const OperatingSystems operating_systems, const std::string_view extensions, const char delimiter) :
    operating_systems_(operating_systems), extensions_(extensions), delimiter_(delimiter) {
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
        auto extensions_vector  = split_and_trim(std::string(extensions_), delimiter_);
        extension               = pick_one<std::string>(extensions_vector);
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
    const auto file_name =
        replace_wildcard_to_letter(replace_wildcard_to_digit(replace_placeholder(file_name_format, file_name_main_part))
        );

    if (extensions_.empty()) {
        path_ = folder_path + separator + file_name;
    } else {
        path_ = folder_path + separator + file_name + "." + extension;
    }
    directory_ = folder_path;
    name_      = file_name + "." + extension;
    extension_ = extension;
}

}  // namespace faker::computer
