// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file computer.h

#ifndef FAKER_COMPUTER_H
#define FAKER_COMPUTER_H

#include <string>

#include "faker/internal/macros.h"
#include "faker/types/enums.h"

namespace faker::computer {

/// @brief Generates a random ip address.
/// @param ip_address_type Ip address type. Defaults to IpAddressType::IPv4.
/// @return An ip address.
/// @code
/// faker::computer::ip_address();  // "43.186.254.66"
/// faker::computer::ip_address(faker::IpAddressType::IPv6);  // "b7f5:713b:60bc:5df7:20cb:51a7:29e9:13e3"
/// @endcode
FAKER_EXPORT std::string ip_address(IpAddressType ip_address_type = IpAddressType::IPv4);

/// @brief Generates a random mac address.
/// @return A mac address.
/// @code
/// faker::computer::mac_address();  // "8e:6b:22:1a:7c:25"
/// @endcode
FAKER_EXPORT std::string mac_address();

/// @brief Generates a random file path.
/// @param operating_systems Operating systems. Defaults to OperatingSystem::Windows.
///                          If multiple operating systems are specified, bitwise(bitwise_or |) operator can be used.
/// @param extensions The list of file extensions. Defaults to "jpg,png,txt,rtf,pdf,docx,xlsx,csv,html,zip".
///                   If empty, the generated file path will not include extension.
/// @param delimiter Delimiter of extensions. Defaults to ','.
/// @return A file path.
/// @code
/// faker::computer::file_path(); // "C:\Users\Administrator\docs\car_20.txt"
/// faker::computer::file_path(OperatingSystems::macOS, "");  // "/Users/Administrator/video/beauty_Kc6387"
/// faker::computer::file_path(OperatingSystems::macOS | OperatingSystems::Linux, "jpg,png", ',');
/// // "/Users/VincentLau/images/airplane_fJ1471.jpg" or "/home/Administrator/images/gust8462.png"
/// @endcode
FAKER_EXPORT std::string file_path(
    OperatingSystems operating_systems = OperatingSystems::Windows,
    std::string_view extensions        = "jpg,png,txt,rtf,pdf,docx,xlsx,csv,html,zip",
    char delimiter                     = ','
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
/// @param extensions The list of file extensions. Defaults to "jpg,png,txt,rtf,pdf,docx,xlsx,csv,html,zip".
///                   If empty, the generated file name will not include extension.
/// @param delimiter Delimiter of extensions. Defaults to ','.
/// @return A file name.
/// @code
/// faker::computer::file_name();  // "jane89.html"
/// faker::computer::file_name("jpg, png", ',');  // "ocean_AJ22.png"
/// faker::computer::file_name("");  // "adam"
/// @endcode
FAKER_EXPORT std::string
          file_name(std::string_view extensions = "jpg,png,txt,rtf,pdf,docx,xlsx,csv,html,zip", char delimiter = ',');

/// @brief Generates a random file extension.
/// @param extensions The list of file extensions. Defaults to "jpg,png,txt,rtf,pdf,docx,xlsx,csv,html,zip".
///                   If empty, throw empty.
/// @param delimiter Delimiter of extensions. Defaults to ','.
/// @return A file extension.
/// @code
/// faker::computer::file_extension();  // "html"
/// faker::computer::file_extension("jpg, png", ',');  // "jpg"
/// faker::computer::file_extension("");  // ""
/// @endcode
FAKER_EXPORT std::string
    file_extension(std::string_view extensions = "jpg,png,txt,rtf,pdf,docx,xlsx,csv,html,zip", char delimiter = ',');

/// @brief Generates a random url.
/// @param subdomains The list of subdomains. Defaults to "auth,drive,image,video,www".
///                   If empty, the generated url will not include subdomain.
/// @param tlds The list of tlds(top-level-domains). Defaults to "biz,com,cn,info,jp,net,org,us,xyz".
///             If empty, throw error.
/// @param delimiter Delimiter of subdomains and tlds.
/// @return A url.
/// @code
/// faker::computer::url();  // "https://image.koizumi.org"
/// faker::computer::url("note", "com");  // "https://note.hotaru.com"
/// @endcode
FAKER_EXPORT std::string url(
    std::string_view subdomains = "auth,drive,image,video,www",
    std::string_view tlds       = "biz,com,cn,info,jp,net,org,us,xyz",
    char delimiter              = ','
);

/// @brief Generates a random hostname.
/// @param subdomains The list of subdomains. Defaults to "auth,drive,image,video,www".
///                   If empty, the generated hostname will not include subdomain.
/// @param tlds The list of tlds(top-level-domains). Defaults to "biz,com,cn,info,jp,net,org,us,xyz".
///             If empty, throw error.
/// @param delimiter Delimiter of subdomains and tlds.
/// @return A hostname.
/// @code
/// faker::computer::hostname();  // "image.koizumi.org"
/// faker::computer::hostname("note", "com");  // "note.hotaru.com"
/// @endcode
FAKER_EXPORT std::string hostname(
    std::string_view subdomains = "auth,drive,image,video,www",
    std::string_view tlds       = "biz,com,cn,info,jp,net,org,us,xyz",
    char delimiter              = ','
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
    /// @param extensions The list of file extensions. Defaults to "jpg,png,txt,rtf,pdf,docx,xlsx,csv,html,zip".
    ///                   If empty, the generated file path will not include extension.
    /// @param delimiter Delimiter of extensions. Defaults to ','.
    explicit File(
        OperatingSystems operating_systems = OperatingSystems::Windows,
        std::string_view extensions        = "jpg,png,txt,rtf,pdf,docx,xlsx,csv,html,zip",
        char delimiter                     = ','
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
    OperatingSystems operating_systems_;
    std::string      extensions_;
    char             delimiter_;

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
