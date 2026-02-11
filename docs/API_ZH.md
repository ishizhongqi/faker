# faker API 快速使用文档（中文）

本文档按模块列出公开 API，用“1 行说明 + 参数要点 + 简短示例”的方式说明使用方法。

## 1. 基础引入

```cpp
#include <faker/faker.h>
```

枚举位标志可用位或 `|` 组合，例如：`Languages::English | Languages::Japanese`。

## 2. 核心类型

### 2.1 `faker::Bilingual`

用于保存“原文 + 翻译”两个字符串。

- 构造：`Bilingual(std::string_view original, std::string_view translation)`
- 构造：`explicit Bilingual(const BilingualView&)`
- 方法：`original()`、`translation()`、`original_view()`、`translation_view()`、`set_original()`、`set_translation()`、`swap()`、`empty()`

```cpp
faker::Bilingual name("张伟", "Zhang Wei");
std::string a = name.original();            // 拷贝
std::string_view b = name.original_view();  // 视图（不拷贝）
```

## 3. `faker::business`

### `company_name(languages)`
生成本地化公司名。

- `languages`：语言位标志，默认 `Languages::English`

```cpp
auto c = faker::business::company_name(faker::Languages::Japanese);
```

### `department(languages)`
生成本地化部门名。

```cpp
auto d = faker::business::department();
```

### `industry(languages)`
生成本地化行业名。

```cpp
auto i = faker::business::industry(faker::Languages::SimplifiedChinese);
```

### `class Company`
强关联实体：`name + industry`。

- 构造：`Company(Languages languages = Languages::English)`
- 方法：`reroll()`、`name()`、`industry()`

```cpp
faker::business::Company company;
company.reroll();
auto name = company.name();
```

## 4. `faker::computer`

### `ip_address(type, unique)`
生成 IPv4/IPv6 地址。

- `type`：`IpAddressType::IPv4` 或 `IpAddressType::IPv6`
- `unique`：运行期唯一序列

```cpp
auto ip = faker::computer::ip_address(faker::IpAddressType::IPv6, true);
```

### `mac_address(unique)`
生成 MAC 地址。

```cpp
auto mac = faker::computer::mac_address();
```

### `file_path(operating_systems, extensions)`
按系统风格生成文件路径。

- `operating_systems`：`OperatingSystems` 位标志
- `extensions`：可选扩展名列表

```cpp
auto p = faker::computer::file_path(
    faker::OperatingSystems::Linux,
    std::to_array<std::string_view>({"txt", "log"})
);
```

### `file_directory(operating_systems)`
生成目录路径。

```cpp
auto dir = faker::computer::file_directory(faker::OperatingSystems::Windows);
```

### `file_name(extensions)`
生成文件名（可带扩展名）。

```cpp
auto n = faker::computer::file_name(std::to_array<std::string_view>({"jpg", "png"}));
```

### `file_extension(extensions)`
从输入扩展名中随机选一个（输入空则返回空）。

```cpp
auto ext = faker::computer::file_extension(std::to_array<std::string_view>({"cpp", "h"}));
```

### `url(subdomains, tlds, unique)`
生成 URL。

- `subdomains`：可选子域名列表（空=不带子域名）
- `tlds`：可选顶级域名列表（`nullopt` 用默认）

```cpp
auto u = faker::computer::url(
    std::to_array<std::string_view>({"api"}),
    std::to_array<std::string_view>({"com"}),
    false
);
```

### `hostname(subdomains, tlds, unique)`
生成主机名（不带协议）。

```cpp
auto h = faker::computer::hostname();
```

### `class File`
强关联实体：`path/directory/name/extension`。

- 构造：`File(OperatingSystems os = OperatingSystems::Windows, span<...> extensions = {})`
- 方法：`reroll()`、`path()`、`directory()`、`name()`、`extension()`

```cpp
faker::computer::File f(
    faker::OperatingSystems::macOS,
    std::to_array<std::string_view>({"cpp"})
);
auto path = f.path();
```

## 5. `faker::datetime`

### `date(start_date, end_date, days_of_week)`
生成 `YYYY-MM-DD` 日期字符串。

```cpp
auto d = faker::datetime::date("2025-01-01", "2025-12-31", faker::DaysOfWeek::Monday);
```

### `time(start_time, end_time)`
生成 `HH:MM:SS` 时间字符串。

```cpp
auto t = faker::datetime::time("09:00:00", "18:00:00");
```

### `datetime(start_date, end_date, start_time, end_time, days_of_week)`
生成 `YYYY-MM-DD HH:MM:SS` 日期时间字符串。

```cpp
auto dt = faker::datetime::datetime();
```

## 6. `faker::location`

### `address_line1(regions)` / `address_line2(regions)`
生成本地化地址行。

```cpp
auto l1 = faker::location::address_line1(faker::Regions::Japan);
auto l2 = faker::location::address_line2(faker::Regions::Japan);
```

### `postcode(regions)`
生成邮编。

```cpp
auto code = faker::location::postcode();
```

### `full_address(regions)`
生成完整地址。

```cpp
auto addr = faker::location::full_address(faker::Regions::China);
```

### `city(regions)`
生成城市名。

```cpp
auto city = faker::location::city();
```

### `region(country_codes_standard, languages)`
生成地区名称或 ISO 代码。

```cpp
auto r1 = faker::location::region(faker::CountryCodesStandard::None, faker::Languages::English);
auto r2 = faker::location::region(faker::CountryCodesStandard::ISO_3166_1_alpha_2);
```

### `class Location`
强关联实体地址对象。

- 构造：`Location(Regions regions = Regions::UnitedStates)`
- 方法：`reroll()`、`address_line1()`、`address_line2()`、`postcode()`、`full_address()`、`city()`、`region()`

```cpp
faker::location::Location loc(faker::Regions::UnitedKingdom);
auto full = loc.full_address();
```

## 7. `faker::number`

### `integer<T>(start, end)`
生成有符号整数。

```cpp
auto v = faker::number::integer<int>(-100, 100);
```

### `unsigned_integer<T>(start, end)`
生成无符号整数。

```cpp
auto u = faker::number::unsigned_integer<uint64_t>(1, 1000000);
```

### `decimal<T>(start, end, decimal_places)`
生成浮点小数。

```cpp
auto x = faker::number::decimal<double>(-1.0, 1.0, 4);
```

### `decimal_string<T>(start, end, decimal_places)`
生成固定小数位字符串。

```cpp
auto s = faker::number::decimal_string<double>(0.0, 100.0, 6);
```

## 8. `faker::payment`

### `payment_method(payment_methods)`
生成支付方式。

```cpp
auto m = faker::payment::payment_method(std::to_array<std::string_view>({"Credit Card", "PayPal"}));
```

### `card_type(languages, card_types)`
生成本地化卡类型。

```cpp
auto t = faker::payment::card_type(faker::Languages::English, faker::CardTypes::Visa);
```

### `card_number(card_types, unique)`
生成卡号。

```cpp
auto n = faker::payment::card_number(faker::CardTypes::MasterCard, true);
```

### `card_date(start_month, end_month)`
生成 `MM/YY` 卡日期。

```cpp
auto d = faker::payment::card_date("01/24", "12/30");
```

### `class Card`
强关联实体：卡类型、卡号、日期。

- 构造：`Card(languages, card_types, start_month, end_month, unique)`
- 方法：`reroll()`、`type()`、`number()`、`date()`、`payment_method()`

```cpp
faker::payment::Card card(faker::Languages::English, faker::CardTypes::Visa, "01/25", "12/30", true);
auto num = card.number();
```

## 9. `faker::person`

### `first_name(languages, genders)` / `last_name(languages)` / `full_name(languages, genders)`
生成本地化姓名字段。

```cpp
auto fn = faker::person::first_name();
auto ln = faker::person::last_name();
auto full = faker::person::full_name();
```

### `gender(languages)` / `title(languages, genders)` / `marital_status(languages)`
生成个人属性字段。

```cpp
auto g = faker::person::gender();
auto ti = faker::person::title();
auto ms = faker::person::marital_status();
```

### `phone_number(is_international, include_delimiters, regions, unique)`
生成电话号码。

```cpp
auto p = faker::person::phone_number(true, true, faker::Regions::UnitedStates, true);
```

### `email(languages, domains, unique)`
生成邮箱。

```cpp
auto e = faker::person::email(faker::Languages::English, std::to_array<std::string_view>({"example.com"}), true);
```

### `job_title(languages)`
生成职位。

```cpp
auto j = faker::person::job_title();
```

### `social_network_id(languages, unique)`
生成社交 ID（`Bilingual`）。

```cpp
auto sid = faker::person::social_network_id(faker::Languages::Japanese, false);
```

### `class Person`
强关联实体人物对象。

- 构造：`Person(genders, languages, regions, email_domains, unique)`
- 方法：`reroll()`、`full_name()`、`first_name()`、`last_name()`、`gender()`、`title()`、`marital_status()`、`phone_number()`、`email()`、`job_title()`、`social_network_id()`

```cpp
faker::person::Person person(faker::Genders::F, faker::Languages::English, faker::Regions::UnitedStates);
auto email = person.email();
```

## 10. `faker::product`

### `product_name(languages, keywords)`
生成商品名。

```cpp
auto n = faker::product::product_name(faker::Languages::English, std::to_array<std::string_view>({"Phone", "Watch"}));
```

### `product_category(languages)` / `color(languages)` / `size()`
生成商品分类、颜色、尺码。

```cpp
auto c = faker::product::product_category();
auto color = faker::product::color();
auto size = faker::product::size();
```

### `barcode(barcode_types, unique)`
生成条码字符串。

```cpp
auto b = faker::product::barcode(faker::BarcodeTypes::EAN13, true);
```

## 11. `faker::string`

### `enum_item(enums)`
从输入列表随机选一个字符串。

```cpp
auto item = faker::string::enum_item(std::to_array<std::string_view>({"A", "B", "C"}));
```

### `text(number_of_chars_start, number_of_chars_end)`
按长度范围生成随机文本。

```cpp
auto txt = faker::string::text(120, 240);
```

### `uuid(include_hyphens)`
生成 UUID v4 字符串。

```cpp
auto u1 = faker::string::uuid();
auto u2 = faker::string::uuid(false);
```

## 12. 枚举类型（速查）

常用枚举：
- `DaysOfWeek`
- `Languages`
- `Regions`
- `CountryCodesStandard`
- `Genders`
- `CardTypes`
- `BarcodeTypes`
- `IpAddressType`
- `OperatingSystems`

其中大多数支持按位或 `|` 组合。
