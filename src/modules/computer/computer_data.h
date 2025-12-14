// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file computer_data.h

#ifndef FAKER_COMPUTER_DATA_H
#define FAKER_COMPUTER_DATA_H

#include <array>
#include <string_view>
#include <unordered_map>

namespace faker::computer {

enum class FileTypes {
    Application,
    Archive,
    Audio,
    Configuration,
    Development,
    Document,
    Font,
    Image,
    Installer,
    Library,
    Log,
    Temporary,
    Video,
    Other
};

const std::unordered_map<FileTypes, std::string_view> kFoldersMap = {
    {FileTypes::Application, "apps"},
    {FileTypes::Archive, "archives"},
    {FileTypes::Audio, "audio"},
    {FileTypes::Configuration, "conf"},
    {FileTypes::Document, "docs"},
    {FileTypes::Font, "fonts"},
    {FileTypes::Image, "images"},
    {FileTypes::Installer, "install"},
    {FileTypes::Library, "lib"},
    {FileTypes::Log, "logs"},
    {FileTypes::Development, "src"},
    {FileTypes::Temporary, "tmp"},
    {FileTypes::Video, "video"},
    {FileTypes::Other, ""}
};

constexpr auto kWindowsPathFormats = std::to_array<std::string_view>({
    R"(C:\{})",
    R"(C:\Users\{})",
    R"(C:\Users\Administrator)",
    R"(C:\Users\Public)",
    R"(D:\{})",
});

constexpr auto kMacOSPathFormats = std::to_array<std::string_view>({
    "/Users/{}",
    "/Users/Administrator",
});

constexpr auto kLinuxPathFormats = std::to_array<std::string_view>({
    "/home/{}",
    "/home/Administrator",
});

constexpr auto kFileNameMainParts = std::to_array<std::string_view>({
    "alex",     "bob",     "charlie",       "david",     "emma",     "fiona",   "george",   "helen",       "ian",
    "julia",    "kevin",   "lily",          "mike",      "nancy",    "oscar",   "patty",    "quin",        "rose",
    "sam",      "tom",     "uma",           "vicky",     "will",     "xander",  "yara",     "zoe",         "adam",
    "beth",     "carl",    "diana",         "eric",      "faith",    "greg",    "holly",    "ivan",        "jane",
    "kate",     "leo",     "molly",         "nathan",    "olivia",   "paul",    "queen",    "ryan",        "sara",
    "ted",      "una",     "vince",         "wendy",     "xavier",   "amber",   "brooke",   "clark",       "dylan",
    "ellie",    "felix",   "gwen",          "hugo",      "isla",     "jace",    "kyle",     "luna",        "myles",
    "nora",     "owen",    "piper",         "quinn",     "rory",     "sienna",  "toby",     "ursula",      "vanessa",
    "wade",     "xena",    "yves",          "zane",      "ant",      "bat",     "cat",      "dog",         "eagle",
    "fox",      "goat",    "horse",         "ibis",      "jay",      "koala",   "lion",     "mouse",       "newt",
    "owl",      "pig",     "quail",         "rabbit",    "snake",    "tiger",   "viper",    "wolf",        "yak",
    "zebra",    "acacia",  "bamboo",        "cedar",     "daisy",    "elm",     "fern",     "grape",       "holly",
    "iris",     "juniper", "kelp",          "maple",     "nettle",   "oak",     "pine",     "quinoa",      "sunflower",
    "tulip",    "violet",  "willow",        "yam",       "zinnia",   "algae",   "aurora",   "breeze",      "cloud",
    "dawn",     "eclipse", "fog",           "gust",      "hail",     "ice",     "jungle",   "lightning",   "mist",
    "night",    "ocean",   "precipitation", "quake",     "rainbow",  "storm",   "tsunami",  "volcano",     "wind",
    "zephyr",   "dew",     "frost",         "humidity",  "airplane", "book",    "car",      "desk",        "envelope",
    "fork",     "guitar",  "hammer",        "ink",       "journal",  "kettle",  "lamp",     "mirror",      "notebook",
    "oven",     "pencil",  "quilt",         "radio",     "shovel",   "table",   "umbrella", "violin",      "watch",
    "yarn",     "phone",   "adventure",     "beauty",    "courage",  "dream",   "emotion",  "faith",       "glory",
    "honor",    "idea",    "joy",           "knowledge", "liberty",  "memory",  "nature",   "opportunity", "peace",
    "quality",  "reason",  "spirit",        "truth",     "unity",    "victory", "wisdom",   "youth",       "ambition",
    "belief",   "charm",   "destiny",       "elegance",  "freedom",  "grace",   "hope",     "inspiration", "justice",
    "kindness", "love",    "mystery",       "passion",   "quest",    "romance", "silence",  "thought",     "vision",
    "wonder",   "change",  "growth",        "harmony",   "infinity", "luck",    "patience",
});

constexpr auto kFileNameFormats = std::to_array<std::string_view>({
    "{}",
    "{}##",
    "{}####",
    "{}_##",
    "{}_####",
    "{}_@@##",
    "{}_@@####",
});

const std::unordered_map<std::string_view, FileTypes> kExtensionsMap = {
    // Application
    {"app", FileTypes::Application},
    {"lnk", FileTypes::Application},
    {"desktop", FileTypes::Application},
    {"exe", FileTypes::Application},

    // Archive
    {"zip", FileTypes::Archive},
    {"rar", FileTypes::Archive},
    {"7z", FileTypes::Archive},
    {"tar", FileTypes::Archive},
    {"iso", FileTypes::Archive},
    {"gz", FileTypes::Archive},
    {"bz2", FileTypes::Archive},
    {"xz", FileTypes::Archive},
    {"tgz", FileTypes::Archive},
    {"tbz2", FileTypes::Archive},
    {"txz", FileTypes::Archive},

    // Audio
    {"mp3", FileTypes::Audio},
    {"wav", FileTypes::Audio},
    {"flac", FileTypes::Audio},
    {"aac", FileTypes::Audio},
    {"ogg", FileTypes::Audio},
    {"m4a", FileTypes::Audio},
    {"wma", FileTypes::Audio},
    {"aiff", FileTypes::Audio},

    // Configuration
    {"ini", FileTypes::Configuration},
    {"conf", FileTypes::Configuration},
    {"config", FileTypes::Configuration},
    {"plist", FileTypes::Configuration},
    {"bak", FileTypes::Configuration},
    {"reg", FileTypes::Configuration},
    {"service", FileTypes::Configuration},

    // Development
    {"html", FileTypes::Development},
    {"htm", FileTypes::Development},
    {"css", FileTypes::Development},
    {"js", FileTypes::Development},
    {"py", FileTypes::Development},
    {"java", FileTypes::Development},
    {"class", FileTypes::Development},
    {"c", FileTypes::Development},
    {"cpp", FileTypes::Development},
    {"cc", FileTypes::Development},
    {"cxx", FileTypes::Development},
    {"hxx", FileTypes::Development},
    {"h", FileTypes::Development},
    {"hpp", FileTypes::Development},
    {"cs", FileTypes::Development},
    {"vb", FileTypes::Development},
    {"go", FileTypes::Development},
    {"rb", FileTypes::Development},
    {"lua", FileTypes::Development},
    {"sql", FileTypes::Development},
    {"sh", FileTypes::Development},
    {"bat", FileTypes::Development},
    {"cmd", FileTypes::Development},
    {"php", FileTypes::Development},
    {"json", FileTypes::Development},
    {"xml", FileTypes::Development},
    {"yml", FileTypes::Development},
    {"yaml", FileTypes::Development},

    // Document
    {"txt", FileTypes::Document},
    {"pdf", FileTypes::Document},
    {"doc", FileTypes::Document},
    {"docx", FileTypes::Document},
    {"xls", FileTypes::Document},
    {"xlsx", FileTypes::Document},
    {"ppt", FileTypes::Document},
    {"pptx", FileTypes::Document},
    {"rtf", FileTypes::Document},
    {"odt", FileTypes::Document},
    {"ods", FileTypes::Document},
    {"odp", FileTypes::Document},
    {"epub", FileTypes::Document},
    {"md", FileTypes::Document},
    {"tex", FileTypes::Document},
    {"csv", FileTypes::Document},
    {"pages", FileTypes::Document},
    {"numbers", FileTypes::Document},
    {"key", FileTypes::Document},

    // Executable
    {"dll", FileTypes::Library},
    {"so", FileTypes::Library},
    {"a", FileTypes::Library},

    // Font
    {"ttf", FileTypes::Font},
    {"otf", FileTypes::Font},
    {"fon", FileTypes::Font},
    {"ttc", FileTypes::Font},

    // Image
    {"jpg", FileTypes::Image},
    {"jpeg", FileTypes::Image},
    {"png", FileTypes::Image},
    {"gif", FileTypes::Image},
    {"bmp", FileTypes::Image},
    {"tiff", FileTypes::Image},
    {"tif", FileTypes::Image},
    {"webp", FileTypes::Image},
    {"svg", FileTypes::Image},
    {"ai", FileTypes::Image},
    {"eps", FileTypes::Image},
    {"psd", FileTypes::Image},
    {"raw", FileTypes::Image},
    {"cr2", FileTypes::Image},
    {"nef", FileTypes::Image},
    {"arw", FileTypes::Image},

    // Installer
    {"msi", FileTypes::Installer},
    {"dmg", FileTypes::Installer},
    {"pkg", FileTypes::Installer},
    {"deb", FileTypes::Installer},
    {"rpm", FileTypes::Installer},
    {"appimage", FileTypes::Installer},
    {"flatpak", FileTypes::Installer},
    {"snap", FileTypes::Installer},

    // Log
    {"log", FileTypes::Log},

    // Temporary
    {"tmp", FileTypes::Temporary},
    {"temp", FileTypes::Temporary},
    {"cache", FileTypes::Temporary},
    {"swp", FileTypes::Temporary},
    {"sock", FileTypes::Temporary},
    {"lock", FileTypes::Temporary},
    {"pid", FileTypes::Temporary},
    {"sav", FileTypes::Temporary},
    {"bak", FileTypes::Temporary},

    // Video
    {"mp4", FileTypes::Video},
    {"mkv", FileTypes::Video},
    {"avi", FileTypes::Video},
    {"mov", FileTypes::Video},
    {"webm", FileTypes::Video},
    {"flv", FileTypes::Video},
    {"m4v", FileTypes::Video},
    {"ts", FileTypes::Video},

};

}  // namespace faker::computer

#endif  // FAKER_COMPUTER_DATA_H
