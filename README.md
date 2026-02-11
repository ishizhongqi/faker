# faker

[![Clang](https://github.com/ishizhongqi/faker/actions/workflows/build-clang.yml/badge.svg?branch=develop)](https://github.com/ishizhongqi/faker/actions/workflows/build-clang.yml?query=branch%3Adevelop)
[![GCC](https://github.com/ishizhongqi/faker/actions/workflows/build-gcc.yml/badge.svg?branch=develop)](https://github.com/ishizhongqi/faker/actions/workflows/build-gcc.yml?query=branch%3Adevelop)
[![AppleClang](https://github.com/ishizhongqi/faker/actions/workflows/build-apple-clang.yml/badge.svg?branch=develop)](https://github.com/ishizhongqi/faker/actions/workflows/build-apple-clang.yml?query=branch%3Adevelop)
[![MSVC](https://github.com/ishizhongqi/faker/actions/workflows/build-msvc.yml/badge.svg?branch=develop)](https://github.com/ishizhongqi/faker/actions/workflows/build-msvc.yml?query=branch%3Adevelop)
[![codecov](https://codecov.io/gh/ishizhongqi/faker/branch/develop/graph/badge.svg?token=7HM692QH9A)](https://codecov.io/gh/ishizhongqi/faker)

## Introduction

**faker** is a C++ library for generating realistic fake data.

The project originates from a practical need in database development and testing: producing large amounts of high-quality sample data quickly. While tools such as **_Navicat’s Data Generation_** provide similar capabilities, they are paid products.

This project aims to provide a lightweight and free alternative for common fake-data workflows. The `faker` library is the core component, and its modules are organized around familiar data-generation categories.

The design is also inspired by established open-source projects, including [joke2k/faker](https://github.com/joke2k/faker) and [cieslarmichal/faker-cxx](https://github.com/cieslarmichal/faker-cxx).

## Usage

### Compiler support

| Compiler                                                          | Minimum Version | Notes                                |
|-------------------------------------------------------------------|-----------------|--------------------------------------|
| [GCC](https://gcc.gnu.org/)                                       | 13              | Tested on Ubuntu (aarch64 / x86_64) |
| [Clang](https://clang.llvm.org/)                                  | 16              | LLVM Clang                           |
| [Apple Clang](https://clang.llvm.org/)                            | Xcode 15+       | macOS                                |
| [MSVC](https://visualstudio.microsoft.com/vs/features/cplusplus/) | 19.34           | Visual Studio 2022 (v143)            |

### Add library

#### Option 1: Git Submodule

```shell
mkdir third_party
cd third_party
git submodule add https://github.com/ishizhongqi/faker.git
git submodule update --init --recursive
```

Then, in your `CMakeLists.txt`:

```cmake
add_subdirectory(third_party/faker)

add_executable(your_target main.cpp)
target_link_libraries(your_target PRIVATE faker)
```

#### Option 2: FetchContent

```cmake
include(FetchContent)

FetchContent_Declare(
        faker
        GIT_REPOSITORY https://github.com/ishizhongqi/faker.git
        GIT_TAG main
)

FetchContent_MakeAvailable(faker)

add_executable(your_target main.cpp)
target_link_libraries(your_target PRIVATE faker)
```

### Start your project

[Source code](./example/main.cpp):

```c++
// Include the umbrella header <faker/faker.h>, or include individual module headers such as <faker/number.h>.
#include <faker/faker.h>

#include <iostream>
#include <string>

int main() {
    // Use a Bilingual object to store results from APIs that return bilingual output.
    const faker::Bilingual first_name_bilingual   = faker::person::first_name(faker::Languages::SimplifiedChinese);
    const std::string      first_name_original    = first_name_bilingual.original();
    const std::string      first_name_translation = first_name_bilingual.translation();
    std::cout << "First name: " << first_name_original << " (" << first_name_translation << ")" << std::endl;

    // Most function parameters have default values, so you can call these APIs without passing arguments.
    const std::string industry = faker::business::industry();
    std::cout << "Industry: " << industry << std::endl;

    // Some functions accept bitwise OR (|) for enum flags, allowing multiple selections in one call.
    const std::string date =
        faker::datetime::date("2023-01-01", "2023-12-31", faker::DaysOfWeek::Monday | faker::DaysOfWeek::Thursday);
    std::cout << "Date: " << date << std::endl;

    // Entity classes generate field values with stronger internal consistency.
    // You can construct them with or without arguments.
    const faker::person::Person person;
    // The fake data is ready after construction; call getters to access each field.
    std::cout << "Person::First name : " << person.first_name().original() << std::endl;
    std::cout << "Person::Full name  : " << person.full_name().original() << std::endl;
    std::cout << "Person::Gender     : " << person.gender() << std::endl;
    std::cout << "Person::Email      : " << person.email() << std::endl;

    // For additional APIs, see the source comments and documentation.
    return 0;
}
```

Output example:

```text
First name: 凯 (Kai)
Industry: Engineering industry
Date: 2023-12-07
Person::First name : Kimberly
Person::Full name  : Kimberly Mullen
Person::Gender     : Female
Person::Email      : KimberlyMullen.live@hotmail.com
```

## Modules

| Module   | Functions                                                                                                                            |
|:---------|:-------------------------------------------------------------------------------------------------------------------------------------|
| business | company_name, department, industry, **Company**                                                                                      |
| computer | ip_address*, mac_address*, file_path, file_directory, file_name, file_extension, url*, hostname*, **File***                        |
| datetime | date, time, datetime                                                                                                                 |
| location | address_line1, address_line2, postcode, full_address, city, region, **Location**                                                    |
| number   | integer, unsigned_integer, decimal, decimal_string                                                                                   |
| payment  | payment_method, card_type, card_number*, card_date, **Card***                                                                        |
| person   | first_name, last_name, full_name, gender, title, marital_status, phone_number*, email*, job_title, social_network_id*, **Person*** |
| product  | product_name, product_category, color, size, barcode*                                                                                |
| string   | enum_item, text, uuid                                                                                                                |

`function*`: Indicates that the function provides a `unique` parameter. When set to `true`, it generates unique random values during runtime.  
`**Bold**`: Indicates an entity class whose fields have stronger interdependencies.

Some data supports localization. Currently supported languages:

- English
- Simplified Chinese
- Traditional Chinese
- Japanese

## API Docs

- English: [docs/API_EN.md](./docs/API_EN.md)
- 中文: [docs/API_ZH.md](./docs/API_ZH.md)

## License

Licensed under the [MIT License](./LICENSE).
