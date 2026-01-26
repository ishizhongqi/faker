# faker

## 简介

**faker** 是一个用于生成虚假数据的 C++ 库。

在数据库测试中，经常会遇到需要生成测试数据的情况，这正是这个想法的来源。我注意到
**_Navicat 的数据生成（Data Generation）_** 已经提供了类似的功能，但这是一个付费功能。

我的计划是开发一个类似 **_Navicat 的数据生成（Data Generation）_** 的简单应用
（当然，它不会像 Navicat 的专业工具那样功能丰富）。
**faker** 库是该项目的一部分，因此 faker 的各个模块在设计上与 **_Navicat 的数据生成（Data Generation）_** 相似。

本项目还参考了一些其他流行的开源项目，例如
[joke2k/faker](https://github.com/joke2k/faker) 以及
[cieslarmichal/faker-cxx](https://github.com/cieslarmichal/faker-cxx) 。

## 使用方法

### 编译器支持

| Compiler                                                          | Minimum Version | Notes                               |
|-------------------------------------------------------------------|-----------------|-------------------------------------|
| [GCC](https://gcc.gnu.org/)                                       | 13              | Tested on Ubuntu (aarch64 / x86_64) |
| [Clang](https://clang.llvm.org/)                                  | 16              | LLVM Clang                          |
| [Apple Clang](https://clang.llvm.org/)                            | Xcode 15+       | macOS                               |
| [MSVC](https://visualstudio.microsoft.com/vs/features/cplusplus/) | 19.34           | Visual Studio 2022 (v143)           |

### 添加库

#### 方法一： Git Submodule

```shell
mkdir third_party
cd third_party
git submodule add https://github.com/ishizhongqi/faker.git
git submodule update --init --recursive
```

然后在你的`CMakeLists.txt` 中加入以下内容:

```cmake
add_subdirectory(third_party/faker)

add_executable(your_target main.cpp)
target_link_libraries(your_target PRIVATE faker)
```

#### 方法二: FetchContent

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

### 开始你的项目

[源代码](example/main.cpp)：

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

输出示例：

```text
First name: 凯 (Kai)
Industry: Engineering industry
Date: 2023-12-07
Person::First name : Kimberly
Person::Full name  : Kimberly Mullen
Person::Gender     : Female
Person::Email      : KimberlyMullen.live@hotmail.com
```

## 模块

| 模块       | 接口                                                                                                                                |
|:---------|:----------------------------------------------------------------------------------------------------------------------------------|
| business | company_name, department, industry, **Company**                                                                                   |
| computer | ip_address*, mac_address*, file_path, file_directory, file_name, file_extension, url*, hostname*, **File***                       |
| datetime | date, time, datetime                                                                                                              |
| location | address_line1, address_line2, postcode, full_address, city, region, **Location**                                                  |
| number   | integer, unsigned_integer, decimal, decimal_string                                                                                |
| payment  | payment_method, card_type, card_number*, card_date, **Card***                                                                     |
| person   | first_name, last_name, full_name, gender, title, marital_status, phone_number*, email*, job_title, social_network_id, **Person*** |
| product  | product_name, product_category, color, size, barcode*                                                                             |
| string   | enum_item, text, uuid                                                                                                             |

function* : 表示该函数包含unique参数，当参数为true时，用于在程序运行时生成唯一的随机值。  
**粗体** : 表示这是实体类，他的字段之间有更强的相关性。

部分数据支持本地化，目前支持的语言包括：

- 英语
- 简体中文
- 繁体中文
- 日语

## 许可证

本项目基于 [MIT License](LICENSE) 。
