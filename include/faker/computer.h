// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file computer.h

#ifndef FAKER_COMPUTER_H
#define FAKER_COMPUTER_H

#include <optional>
#include <span>
#include <string>
#include <string_view>
#include <vector>

#include "faker/internal/export.h"
#include "faker/types/enums.h"

namespace faker::computer {

/// @brief Generates a random ip address.
/// @param ip_address_type Ip address type. Defaults to IpAddressType::IPv4.
/// @param unique Whether to generate a unique ip address. Defaults to false.
/// @return An ip address.
/// @code
/// faker::computer::ip_address();  // "43.186.254.66"
/// faker::computer::ip_address(faker::IpAddressType::IPv6);  // "b7f5:713b:60bc:5df7:20cb:51a7:29e9:13e3"
/// @endcode
/// @note The unique option has a runtime generation limit. Exceeding it may cause errors.
FAKER_EXPORT std::string ip_address(IpAddressType ip_address_type = IpAddressType::IPv4, bool unique = false);

/// @brief Generates a random mac address.
/// @param unique Whether to generate a unique mac address. Defaults to false.
/// @return A mac address.
/// @code
/// faker::computer::mac_address();  // "8e:6b:22:1a:7c:25"
/// @endcode
/// @note The unique option has a runtime generation limit. Exceeding it may cause errors.
FAKER_EXPORT std::string mac_address(bool unique = false);

/// @brief Generates a random file path.
/// @param operating_systems Operating systems. Defaults to OperatingSystem::Windows.
///                          If multiple operating systems are specified, bitwise(bitwise_or |) operator can be used.
/// @param extensions The list of file extensions.
///                   Defaults to {}.
///                   If empty, the generated file path will not include extension.
/// @return A file path.
/// @code
/// faker::computer::file_path(); // "C:\Users\Administrator\docs\car_20"
/// faker::computer::file_path(OperatingSystems::macOS, {});  // "/Users/Administrator/video/beauty_Kc6387"
/// faker::computer::file_path(OperatingSystems::macOS | OperatingSystems::Linux,
///                            std::to_array<std::string_view>({"jpg", "png"}));
/// // "/Users/VincentLau/images/airplane_fJ1471.jpg" or "/home/Administrator/images/gust8462.png"
/// @endcode
FAKER_EXPORT std::string file_path(
    OperatingSystems                  operating_systems = OperatingSystems::Windows,
    std::span<const std::string_view> extensions        = {}
);

/// @brief Generates a random file directory.
/// @param operating_systems Operating systems. Defaults to OperatingSystem::Windows.
///                          If multiple operating systems are specified, bitwise(bitwise_or |) operator can be used.
/// @return A file directory.
/// @code
/// faker::computer::file_directory();  // "C:\Users\Administrator\docs"
/// faker::computer::file_directory(OperatingSystems::macOS | OperatingSystems::Linux);
/// // "/Users/Administrator/audio" or "/home/Yore/lib"
/// @endcode
FAKER_EXPORT std::string file_directory(OperatingSystems operating_systems = OperatingSystems::Windows);

/// @brief Generates a random file name.
/// @param extensions The list of file extensions.
///                   Defaults to {}.
///                   If empty, the generated file name will not include extension.
/// @return A file name.
/// @code
/// faker::computer::file_name();  // "jane89"
/// faker::computer::file_name(std::to_array<std::string_view>({"jpg", "png"}));  // "ocean_AJ22.png"
/// faker::computer::file_name({});  // "adam"
/// @endcode
FAKER_EXPORT std::string file_name(std::span<const std::string_view> extensions = {});

/// @brief Generates a random file extension.
/// @param extensions The list of file extensions.
///                   Defaults to {}.
///                   If empty, return empty string.
/// @return A file extension.
/// @code
/// faker::computer::file_extension();  // ""
/// faker::computer::file_extension(std::to_array<std::string_view>({"jpg", "png"}));  // "jpg"
/// faker::computer::file_extension({});  // ""
/// @endcode
FAKER_EXPORT std::string file_extension(std::span<const std::string_view> extensions = {});

/// @brief Generates a random url.
/// @param subdomains The list of subdomains.
///                   Defaults to {}.
///                   If empty, the generated url will not include subdomain.
/// @param tlds The list of tlds(top-level-domains).
///             Defaults to std::nullopt, equivalent to {"com", "net", "org"}.
///             If empty, throw error.
/// @param unique Whether to generate a unique url. Defaults to false.
/// @return A url.
/// @code
/// faker::computer::url();  // "https://image.koizumi.com"
/// faker::computer::url(std::to_array<std::string_view>({"note"}), std::to_array<std::string_view>({"com"}));
/// // "https://note.hotaru.com"
/// @endcode
/// @note The unique option has a runtime generation limit. Exceeding it may cause errors.
FAKER_EXPORT std::string url(
    std::span<const std::string_view>                subdomains = {},
    std::optional<std::span<const std::string_view>> tlds       = std::nullopt,
    bool                                             unique     = false
);

/// @brief Generates a random hostname.
/// @param subdomains The list of subdomains.
///                   Defaults to {}.
///                   If empty, the generated hostname will not include subdomain.
/// @param tlds The list of tlds(top-level-domains).
///             Defaults to std::nullopt, equivalent to {"com", "net", "org"}.
///             If empty, throw error.
/// @param unique Whether to generate a unique hostname. Defaults to false.
/// @return A hostname.
/// @code
/// faker::computer::hostname();  // "image.koizumi.com"
/// faker::computer::hostname(std::to_array<std::string_view>({"note"}), std::to_array<std::string_view>({"com"}));
/// // "note.hotaru.com"
/// @endcode
/// @note The unique option has a runtime generation limit. Exceeding it may cause errors.
FAKER_EXPORT std::string hostname(
    std::span<const std::string_view>                subdomains = {},
    std::optional<std::span<const std::string_view>> tlds       = std::nullopt,
    bool                                             unique     = false
);

/// @brief Represents a file entity with a generated path, directory, name and extension
///        that are strongly correlated and contextually appropriate.
/// @code
/// faker::computer::File f1();
/// f1.path();  // "D:\PennyBay\src\unity_ek85.html"
/// f1.directory();  // "D:\PennyBay\src"
/// f1.name();  // "unity_ek85.html"
/// f1.extension();  // "html"
/// faker::computer::File f2(faker::OperatingSystems::macOS);
/// f2.path();  // "/Users/PaperShan/src/willow.cpp"
/// f2.directory();  // "/Users/PaperShan/src"
/// f2.name();  // "willow.cpp"
/// f2.extension();  // "cpp"
/// @endcode
class FAKER_EXPORT File {
public:
    /// @brief Constructs a file entity.
    /// @param operating_systems Operating system. Defaults to OperatingSystem::Windows.
    ///                          If multiple operating systems are specified, bitwise(bitwise_or |) operator can be
    ///                          used.
    /// @param extensions The list of file extensions.
    ///                   Defaults to {}.
    ///                   If empty, the generated file path will not include extension.
    explicit File(
        OperatingSystems                  operating_systems = OperatingSystems::Windows,
        std::span<const std::string_view> extensions        = {}
    );

    /// @brief Destroys the file entity.
    ~File();

    /// @brief Regenerates file data.
    void reroll();

    /// @brief Gets the file path.
    /// @return File path.
    [[nodiscard]] std::string path() const;

    /// @brief Gets the file directory.
    /// @return File directory.
    [[nodiscard]] std::string directory() const;

    /// @brief Gets the file name.
    /// @return File name.
    [[nodiscard]] std::string name() const;

    /// @brief Gets the file extension.
    /// @return File extension.
    [[nodiscard]] std::string extension() const;

private:
    // Constructor parameters.
    OperatingSystems         operating_systems_;
    std::vector<std::string> extensions_;

    // Selection.
    OperatingSystems selected_operating_system_ = OperatingSystems::Windows;

    // Generated data.
    std::string path_;
    std::string directory_;
    std::string name_;
    std::string extension_;

    // Generates file data.
    void roll();
};

}  // namespace faker::computer

#endif  // FAKER_COMPUTER_H
