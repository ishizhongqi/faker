# faker

## 简介

**faker** 是一个用于生成高质量虚拟数据的 C++ 库。

这个项目来自数据库开发与测试中的一个高频需求：快速构造大量可用的样本数据。虽然 **_Navicat 的 Data Generation_** 等工具已经提供了类似能力，但它们属于付费功能。

本项目的目标是提供一个轻量、免费、易集成的替代方案。`faker` 库是整个项目的核心组件，模块划分也围绕常见的数据生成场景展开。

项目实现还参考了多个成熟开源项目，包括 [joke2k/faker](https://github.com/joke2k/faker) 和 [cieslarmichal/faker-cxx](https://github.com/cieslarmichal/faker-cxx)。

## 使用方法

### 编译器支持

| Compiler                                                          | Minimum Version | Notes                                |
|-------------------------------------------------------------------|-----------------|--------------------------------------|
| [GCC](https://gcc.gnu.org/)                                       | 13              | Tested on Ubuntu (aarch64 / x86_64) |
| [Clang](https://clang.llvm.org/)                                  | 16              | LLVM Clang                           |
| [Apple Clang](https://clang.llvm.org/)                            | Xcode 15+       | macOS                                |
| [MSVC](https://visualstudio.microsoft.com/vs/features/cplusplus/) | 19.34           | Visual Studio 2022 (v143)            |

### 引入库

#### 方式一：Git Submodule

```shell
mkdir third_party
cd third_party
git submodule add https://github.com/ishizhongqi/faker.git
git submodule update --init --recursive
```

然后在你的 `CMakeLists.txt` 中加入：

```cmake
add_subdirectory(third_party/faker)

add_executable(your_target main.cpp)
target_link_libraries(your_target PRIVATE faker)
```

#### 方式二：FetchContent

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

### 快速开始

[示例代码](./example/main.cpp)：

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

| 模块      | 接口                                                                                                                                 |
|:----------|:-------------------------------------------------------------------------------------------------------------------------------------|
| business  | company_name, department, industry, **Company**                                                                                      |
| computer  | ip_address*, mac_address*, file_path, file_directory, file_name, file_extension, url*, hostname*, **File***                        |
| datetime  | date, time, datetime                                                                                                                 |
| location  | address_line1, address_line2, postcode, full_address, city, region, **Location**                                                    |
| number    | integer, unsigned_integer, decimal, decimal_string                                                                                   |
| payment   | payment_method, card_type, card_number*, card_date, **Card***                                                                        |
| person    | first_name, last_name, full_name, gender, title, marital_status, phone_number*, email*, job_title, social_network_id*, **Person*** |
| product   | product_name, product_category, color, size, barcode*                                                                                |
| string    | enum_item, text, uuid                                                                                                                |

`function*`：表示该函数支持 `unique` 参数。设为 `true` 时，运行期会生成唯一随机值。  
`**粗体**`：表示实体类，其字段之间具有更强的关联性。

部分数据支持本地化。目前支持以下语言：

- 英语
- 简体中文
- 繁体中文
- 日语

## API 文档

- English: [docs/API_GUIDE.md](./docs/API_GUIDE.md)
- 中文: [docs/API_GUIDE_CN.md](./docs/API_GUIDE_CN.md)

## 许可证

本项目基于 [MIT License](./LICENSE)。
