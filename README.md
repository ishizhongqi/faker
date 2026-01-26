# faker

[![Clang](https://github.com/ishizhongqi/faker/actions/workflows/build-clang.yml/badge.svg?branch=develop)](https://github.com/ishizhongqi/faker/actions/workflows/build-clang.yml?query=branch%3Adevelop)
[![GCC](https://github.com/ishizhongqi/faker/actions/workflows/build-gcc.yml/badge.svg?branch=develop)](https://github.com/ishizhongqi/faker/actions/workflows/build-gcc.yml?query=branch%3Adevelop)
[![AppleClang](https://github.com/ishizhongqi/faker/actions/workflows/build-apple-clang.yml/badge.svg?branch=develop)](https://github.com/ishizhongqi/faker/actions/workflows/build-apple-clang.yml?query=branch%3Adevelop)
[![MSVC](https://github.com/ishizhongqi/faker/actions/workflows/build-msvc.yml/badge.svg?branch=develop)](https://github.com/ishizhongqi/faker/actions/workflows/build-msvc.yml?query=branch%3Adevelop)
[![codecov](https://codecov.io/gh/ishizhongqi/faker/branch/develop/graph/badge.svg?token=7HM692QH9A)](https://codecov.io/gh/ishizhongqi/faker)

## Introduction

**faker** is a C++ library that generates fake data for you.

In database testing, it’s common to run into situations where you need to generate test data that’s where this idea came
from. I noticed that **_Navicat’s Data Generation_** already provides this functionality, but it’s a paid feature.

My plan is to develop a simple and free application like **_Navicat’s Data Generation_**
(of course, it won’t be as feature-rich as Navicat’s professional tool).
The **faker** library is part of this project, So the faker's modules are quite similar to **_Navicat’s Data Generation_
**.

This project also references some other popular open-source projects, such as
[joke2k/faker](https://github.com/joke2k/faker)  and
[cieslarmichal/faker-cxx](https://github.com/cieslarmichal/faker-cxx) .

## Usage

### Compiler support

| Compiler                                                          | Minimum Version | Notes                               |
|-------------------------------------------------------------------|-----------------|-------------------------------------|
| [GCC](https://gcc.gnu.org/)                                       | 13              | Tested on Ubuntu (aarch64 / x86_64) |
| [Clang](https://clang.llvm.org/)                                  | 16              | LLVM Clang                          |
| [Apple Clang](https://clang.llvm.org/)                            | Xcode 15+       | macOS                               |
| [MSVC](https://visualstudio.microsoft.com/vs/features/cplusplus/) | 19.34           | Visual Studio 2022 (v143)           |

### Add library

#### Option 1 : Git Submodule

```shell
mkdir third_party
cd third_party
git submodule add https://github.com/ishizhongqi/faker.git
git submodule update --init --recursive
```

Then in your `CMakeLists.txt`：

```cmake
add_subdirectory(third_party/faker)

add_executable(your_target main.cpp)
target_link_libraries(your_target PRIVATE faker)
```

#### Option 2 : FetchContent

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

[Source code](./example/main.cpp) :

```c++
// You can include the full header <faker/faker.h>, or include individual module headers like <faker/number.h>.
#include <faker/faker.h>

#include <iostream>
#include <string>

int main() {
    // You need to use a Bilingual object to store the return values from functions that provide bilingual output.
    const faker::Bilingual first_name_bilingual   = faker::person::first_name(faker::Languages::SimplifiedChinese);
    const std::string      first_name_original    = first_name_bilingual.original();
    const std::string      first_name_translation = first_name_bilingual.translation();
    std::cout << "First name: " << first_name_original << " (" << first_name_translation << ")" << std::endl;

    // Most function parameters have default values, so you can just call the functions without providing any arguments.
    const std::string industry = faker::business::industry();
    std::cout << "Industry: " << industry << std::endl;

    // Some functions allow bitwise OR (|) in their parameters,
    // which you can use when you want to generate multiple enum members at once.
    const std::string date =
        faker::datetime::date("2023-01-01", "2023-12-31", faker::DaysOfWeek::Monday | faker::DaysOfWeek::Thursday);
    std::cout << "Date: " << date << std::endl;

    // You can use a class to create an entity
    // where the generated data has stronger correlations between its fields.
    // Of course, you can choose to call it with or without parameters.
    const faker::person::Person person;
    // At this point, the fake data has been fully generated, and you just need to call the getters to get data.
    std::cout << "Person::First name : " << person.first_name().original() << std::endl;
    std::cout << "Person::Full name  : " << person.full_name().original() << std::endl;
    std::cout << "Person::Gender     : " << person.gender() << std::endl;
    std::cout << "Person::Email      : " << person.email() << std::endl;

    // For the other functions and classes, see the source code comments or the documentation.
    
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

| Module   | Functions                                                                                                                          |
|:---------|:-----------------------------------------------------------------------------------------------------------------------------------|
| business | company_name, department, industry, **Company**                                                                                    |
| computer | ip_address*, mac_address*, file_path, file_directory, file_name, file_extension, url*, hostname*, **File***                        |
| datetime | date, time, datetime                                                                                                               |
| location | address_line1, address_line2, postcode, full_address, city, region, **Location**                                                   |
| number   | integer, unsigned_integer, decimal, decimal_string                                                                                 |
| payment  | payment_method, card_type, card_number*, card_date, **Card***                                                                      |
| person   | first_name, last_name, full_name, gender, title, marital_status, phone_number*, email*, job_title, social_network_id*, **Person*** |
| product  | product_name, product_category, color, size, barcode*                                                                              |
| string   | enum_item, text, uuid                                                                                                              |

function* : Indicates that this function includes a unique parameter. When set to true, it enables the generation of
unique random values during program runtime.  
**Bold** : Indicates that this is an entity class, whose fields exhibit stronger interdependencies correlations.

Some data supports localization, currently supported languages are:

- English
- Simplified Chinese
- Traditional Chinese
- Japanese

## License

Licensed under the [MIT License](./LICENSE).
