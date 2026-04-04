# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [1.0.0] - 2026-04-04

### Added

- Initial stable release of the `faker` C++ library with business, computer, datetime, location, number, payment, person, product, and string modules.
- Bilingual and localized fake data support for English, Simplified Chinese, Traditional Chinese, and Japanese.
- Example project, API guides, Doxygen configuration, cross-platform CI workflows, code coverage, and comprehensive unit tests.

### Changed

- Reworked the CMake build, install, packaging, and shared-library export flow for broader platform support.
- Improved documentation structure and API navigation for both English and Chinese guides.

### Fixed

- Fixed UTF-8 text truncation that could break downstream database imports.
- Fixed mismatched bilingual placeholders and MSVC/shared-library integration issues.
