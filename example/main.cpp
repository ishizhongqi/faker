// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file main.cpp

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
