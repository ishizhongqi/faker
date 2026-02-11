# faker API Quick Guide (English)

This document lists all public APIs with a one-line description, key parameters, and short examples.

## 1. Common Setup

```cpp
#include <faker/faker.h>
```

Use bitwise `|` for enum flags (e.g. `Languages::English | Languages::Japanese`).

## 2. Core Types

### 2.1 `faker::Bilingual`

One object that stores `original` text and `translation` text.

- Constructor: `Bilingual(std::string_view original, std::string_view translation)`
- Constructor: `explicit Bilingual(const BilingualView&)`
- Methods: `original()`, `translation()`, `original_view()`, `translation_view()`, `set_original()`, `set_translation()`, `swap()`, `empty()`

```cpp
faker::Bilingual name("张伟", "Zhang Wei");
std::string a = name.original();         // copy
std::string_view b = name.original_view(); // view (no copy)
```

## 3. `faker::business`

### `company_name(languages)`
Generate a localized company name.

- `languages`: `Languages` flags, default `Languages::English`

```cpp
auto c = faker::business::company_name(faker::Languages::Japanese);
```

### `department(languages)`
Generate a localized department string.

```cpp
auto d = faker::business::department();
```

### `industry(languages)`
Generate a localized industry string.

```cpp
auto i = faker::business::industry(faker::Languages::SimplifiedChinese);
```

### `class Company`
Correlated entity with company `name` and `industry`.

- Constructor: `Company(Languages languages = Languages::English)`
- Methods: `reroll()`, `name()`, `industry()`

```cpp
faker::business::Company company;
company.reroll();
auto name = company.name();
```

## 4. `faker::computer`

### `ip_address(type, unique)`
Generate IPv4/IPv6 address.

- `type`: `IpAddressType::IPv4` or `IpAddressType::IPv6`
- `unique`: unique-at-runtime sequence

```cpp
auto ip = faker::computer::ip_address(faker::IpAddressType::IPv6, true);
```

### `mac_address(unique)`
Generate MAC address.

```cpp
auto mac = faker::computer::mac_address();
```

### `file_path(operating_systems, extensions)`
Generate file path for OS style.

- `operating_systems`: `OperatingSystems` flags
- `extensions`: optional extension list

```cpp
auto p = faker::computer::file_path(
    faker::OperatingSystems::Linux,
    std::to_array<std::string_view>({"txt", "log"})
);
```

### `file_directory(operating_systems)`
Generate directory path.

```cpp
auto dir = faker::computer::file_directory(faker::OperatingSystems::Windows);
```

### `file_name(extensions)`
Generate file name (with extension if provided).

```cpp
auto n = faker::computer::file_name(std::to_array<std::string_view>({"jpg", "png"}));
```

### `file_extension(extensions)`
Pick one extension (or empty when input empty).

```cpp
auto ext = faker::computer::file_extension(std::to_array<std::string_view>({"cpp", "h"}));
```

### `url(subdomains, tlds, unique)`
Generate URL.

- `subdomains`: optional list (empty => no subdomain)
- `tlds`: optional list (nullopt => defaults)

```cpp
auto u = faker::computer::url(
    std::to_array<std::string_view>({"api"}),
    std::to_array<std::string_view>({"com"}),
    false
);
```

### `hostname(subdomains, tlds, unique)`
Generate hostname only (no scheme).

```cpp
auto h = faker::computer::hostname();
```

### `class File`
Correlated entity with `path/directory/name/extension`.

- Constructor: `File(OperatingSystems os = OperatingSystems::Windows, span<...> extensions = {})`
- Methods: `reroll()`, `path()`, `directory()`, `name()`, `extension()`

```cpp
faker::computer::File f(
    faker::OperatingSystems::macOS,
    std::to_array<std::string_view>({"cpp"})
);
auto path = f.path();
```

## 5. `faker::datetime`

### `date(start_date, end_date, days_of_week)`
Generate date string in `YYYY-MM-DD`.

```cpp
auto d = faker::datetime::date("2025-01-01", "2025-12-31", faker::DaysOfWeek::Monday);
```

### `time(start_time, end_time)`
Generate time string in `HH:MM:SS`.

```cpp
auto t = faker::datetime::time("09:00:00", "18:00:00");
```

### `datetime(start_date, end_date, start_time, end_time, days_of_week)`
Generate datetime string in `YYYY-MM-DD HH:MM:SS`.

```cpp
auto dt = faker::datetime::datetime();
```

## 6. `faker::location`

### `address_line1(regions)` / `address_line2(regions)`
Generate localized address lines.

```cpp
auto l1 = faker::location::address_line1(faker::Regions::Japan);
auto l2 = faker::location::address_line2(faker::Regions::Japan);
```

### `postcode(regions)`
Generate postcode/zip.

```cpp
auto code = faker::location::postcode();
```

### `full_address(regions)`
Generate full localized address.

```cpp
auto addr = faker::location::full_address(faker::Regions::China);
```

### `city(regions)`
Generate localized city.

```cpp
auto city = faker::location::city();
```

### `region(country_codes_standard, languages)`
Generate region name or ISO code.

```cpp
auto r1 = faker::location::region(faker::CountryCodesStandard::None, faker::Languages::English);
auto r2 = faker::location::region(faker::CountryCodesStandard::ISO_3166_1_alpha_2);
```

### `class Location`
Correlated location entity.

- Constructor: `Location(Regions regions = Regions::UnitedStates)`
- Methods: `reroll()`, `address_line1()`, `address_line2()`, `postcode()`, `full_address()`, `city()`, `region()`

```cpp
faker::location::Location loc(faker::Regions::UnitedKingdom);
auto full = loc.full_address();
```

## 7. `faker::number`

### `integer<T>(start, end)`
Generate signed integer.

```cpp
auto v = faker::number::integer<int>(-100, 100);
```

### `unsigned_integer<T>(start, end)`
Generate unsigned integer.

```cpp
auto u = faker::number::unsigned_integer<uint64_t>(1, 1000000);
```

### `decimal<T>(start, end, decimal_places)`
Generate floating-point decimal.

```cpp
auto x = faker::number::decimal<double>(-1.0, 1.0, 4);
```

### `decimal_string<T>(start, end, decimal_places)`
Generate decimal as string with fixed precision formatting.

```cpp
auto s = faker::number::decimal_string<double>(0.0, 100.0, 6);
```

## 8. `faker::payment`

### `payment_method(payment_methods)`
Generate payment method.

```cpp
auto m = faker::payment::payment_method(std::to_array<std::string_view>({"Credit Card", "PayPal"}));
```

### `card_type(languages, card_types)`
Generate localized card type.

```cpp
auto t = faker::payment::card_type(faker::Languages::English, faker::CardTypes::Visa);
```

### `card_number(card_types, unique)`
Generate card number.

```cpp
auto n = faker::payment::card_number(faker::CardTypes::MasterCard, true);
```

### `card_date(start_month, end_month)`
Generate card date in `MM/YY`.

```cpp
auto d = faker::payment::card_date("01/24", "12/30");
```

### `class Card`
Correlated card entity.

- Constructor: `Card(languages, card_types, start_month, end_month, unique)`
- Methods: `reroll()`, `type()`, `number()`, `date()`, `payment_method()`

```cpp
faker::payment::Card card(faker::Languages::English, faker::CardTypes::Visa, "01/25", "12/30", true);
auto num = card.number();
```

## 9. `faker::person`

### `first_name(languages, genders)` / `last_name(languages)` / `full_name(languages, genders)`
Generate localized name parts.

```cpp
auto fn = faker::person::first_name();
auto ln = faker::person::last_name();
auto full = faker::person::full_name();
```

### `gender(languages)` / `title(languages, genders)` / `marital_status(languages)`
Generate localized profile fields.

```cpp
auto g = faker::person::gender();
auto ti = faker::person::title();
auto ms = faker::person::marital_status();
```

### `phone_number(is_international, include_delimiters, regions, unique)`
Generate phone number.

```cpp
auto p = faker::person::phone_number(true, true, faker::Regions::UnitedStates, true);
```

### `email(languages, domains, unique)`
Generate email.

```cpp
auto e = faker::person::email(faker::Languages::English, std::to_array<std::string_view>({"example.com"}), true);
```

### `job_title(languages)`
Generate job title.

```cpp
auto j = faker::person::job_title();
```

### `social_network_id(languages, unique)`
Generate social ID (`Bilingual`).

```cpp
auto sid = faker::person::social_network_id(faker::Languages::Japanese, false);
```

### `class Person`
Correlated person entity.

- Constructor: `Person(genders, languages, regions, email_domains, unique)`
- Methods: `reroll()`, `full_name()`, `first_name()`, `last_name()`, `gender()`, `title()`, `marital_status()`, `phone_number()`, `email()`, `job_title()`, `social_network_id()`

```cpp
faker::person::Person person(faker::Genders::F, faker::Languages::English, faker::Regions::UnitedStates);
auto email = person.email();
```

## 10. `faker::product`

### `product_name(languages, keywords)`
Generate product name.

```cpp
auto n = faker::product::product_name(faker::Languages::English, std::to_array<std::string_view>({"Phone", "Watch"}));
```

### `product_category(languages)` / `color(languages)` / `size()`
Generate product category, color, and size.

```cpp
auto c = faker::product::product_category();
auto color = faker::product::color();
auto size = faker::product::size();
```

### `barcode(barcode_types, unique)`
Generate barcode string.

```cpp
auto b = faker::product::barcode(faker::BarcodeTypes::EAN13, true);
```

## 11. `faker::string`

### `enum_item(enums)`
Pick one item from input list.

```cpp
auto item = faker::string::enum_item(std::to_array<std::string_view>({"A", "B", "C"}));
```

### `text(number_of_chars_start, number_of_chars_end)`
Generate random text in a length range.

```cpp
auto txt = faker::string::text(120, 240);
```

### `uuid(include_hyphens)`
Generate UUID v4 string.

```cpp
auto u1 = faker::string::uuid();
auto u2 = faker::string::uuid(false);
```

## 12. Enum Types (Quick Reference)

Main enums used by APIs:
- `DaysOfWeek`
- `Languages`
- `Regions`
- `CountryCodesStandard`
- `Genders`
- `CardTypes`
- `BarcodeTypes`
- `IpAddressType`
- `OperatingSystems`

Most of them support bitwise `|` combinations.
