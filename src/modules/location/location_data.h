// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file location_data.h

#ifndef FAKER_LOCATION_DATA_H
#define FAKER_LOCATION_DATA_H

#include <array>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "faker/types/bilingual.h"
#include "faker/types/enums.h"

namespace faker::location {

struct AddressComponents {
    // US: ZIP code/ZIP+4 code, UK: postcode(upper case), CN: postcode, JP:postal code
    std::string_view           postcode;
    // admin_level1:  US: state abbreviation, UK: post town(upper case), CN: province, JP: prefecture-level division
    // admin_level2:  US: city, UK: locality(only if required), CN: prefecture city, JP: municipal-level subdivision
    // admin_level3:  CN: county/area/district
    // admin_level4:  CN: town/street
    std::vector<BilingualView> admin_levels;
    // US: street name and house number, UK: street name and street number, CN: road, JP: land-lot
    BilingualView              street;
    // US: apartment/suite/room number (if any), CN: building and room number, JP: secondary unit
    BilingualView              building;
};

const std::unordered_map<CountryCodesStandard, std::unordered_map<Regions, std::string_view>>
    kRegionsByCountryCodesStandards = {
        {CountryCodesStandard::None,
         {
             {Regions::UnitedStates, "United States"},
             {Regions::UnitedKingdom, "United Kingdom"},
             {Regions::China, "China"},
             {Regions::Japan, "Japan"},
         }},
        {CountryCodesStandard::ISO_3166_1_alpha_2,
         {
             {Regions::UnitedStates, "US"},
             {Regions::UnitedKingdom, "GB"},
             {Regions::China, "CN"},
             {Regions::Japan, "JP"},
         }},
        {CountryCodesStandard::ISO_3166_1_alpha_3,
         {
             {Regions::UnitedStates, "USA"},
             {Regions::UnitedKingdom, "GBR"},
             {Regions::China, "CHN"},
             {Regions::Japan, "JPN"},
         }},
};

const std::unordered_map<Languages, std::unordered_map<Regions, std::string_view>> kRegions = {
    {Languages::English,
     {
         {Regions::UnitedStates, "United States"},
         {Regions::UnitedKingdom, "United Kingdom"},
         {Regions::China, "China"},
         {Regions::Japan, "Japan"},
     }},
    {Languages::SimplifiedChinese,
     {
         {Regions::UnitedStates, "美国"},
         {Regions::UnitedKingdom, "英国"},
         {Regions::China, "中国"},
         {Regions::Japan, "日本"},
     }},
    {Languages::TraditionalChinese,
     {
         {Regions::UnitedStates, "美國"},
         {Regions::UnitedKingdom, "英國"},
         {Regions::China, "中國"},
         {Regions::Japan, "日本"},
     }},
    {
        Languages::Japanese,
        {
            {Regions::UnitedStates, "米国"},
            {Regions::UnitedKingdom, "英国"},
            {Regions::China, "中国"},
            {Regions::Japan, "日本"},
        },
    }
};

constexpr int KUnitedStatesCityLevel  = 1;
constexpr int KUnitedKingdomCityLevel = 0;
constexpr int KChinaCityLevel         = 1;
constexpr int KJapanCityLevel         = 0;

// Note on placeholders:
// #: Represents a digit
// @: Represents an uppercase letter
// clang-format off
const auto kUnitedStatesAddressComponents = std::to_array<AddressComponents>({
    // State: California
    {"90210-####", {{"CA", "CA"}, {"Beverly Hills", "Beverly Hills"}}, {"#### Santa Monica Blvd", "#### Santa Monica Blvd"}, {}},
    {"90012-####", {{"CA", "CA"}, {"Los Angeles", "Los Angeles"}}, {"### N Spring St", "### N Spring St"}, {"Apt ###", "Apt ###"}},
    {"90028-####", {{"CA", "CA"}, {"Hollywood", "Hollywood"}}, {"#### Hollywood Blvd", "#### Hollywood Blvd"}, {"Suite ###", "Suite ###"}},
    {"94102-####", {{"CA", "CA"}, {"San Francisco", "San Francisco"}}, {"#### Larkin St", "#### Larkin St"}, {}},
    {"94103-####", {{"CA", "CA"}, {"San Francisco", "San Francisco"}}, {"### Howard St", "### Howard St"}, {"Ste ###", "Ste ###"}},
    {"94111-####", {{"CA", "CA"}, {"San Francisco", "San Francisco"}}, {"### Market St", "### Market St"}, {}},
    {"92101-####", {{"CA", "CA"}, {"San Diego", "San Diego"}}, {"#### Broadway", "#### Broadway"}, {"Unit @##", "Unit @##"}},
    {"92109-####", {{"CA", "CA"}, {"San Diego", "San Diego"}}, {"#### Mission Blvd", "#### Mission Blvd"}, {}},
    {"95814-####", {{"CA", "CA"}, {"Sacramento", "Sacramento"}}, {"#### Capitol Mall", "#### Capitol Mall"}, {"Fl ##", "Fl ##"}},
    {"95113-####", {{"CA", "CA"}, {"San Jose", "San Jose"}}, {"### S Market St", "### S Market St"}, {}},
    {"94043-####", {{"CA", "CA"}, {"Mountain View", "Mountain View"}}, {"#### Amphitheatre Pkwy", "#### Amphitheatre Pkwy"}, {}},

    // State: New York
    {"10001-####", {{"NY", "NY"}, {"New York", "New York"}}, {"### W 33rd St", "### W 33rd St"}, {"Apt ##@", "Apt ##@"}},
    {"10007-####", {{"NY", "NY"}, {"New York", "New York"}}, {"### Broadway", "### Broadway"}, {}},
    {"10036-####", {{"NY", "NY"}, {"New York", "New York"}}, {"#### Times Square", "#### Times Square"}, {"Suite ####", "Suite ####"}},
    {"11201-####", {{"NY", "NY"}, {"Brooklyn", "Brooklyn"}}, {"### Montague St", "### Montague St"}, {}},
    {"11211-####", {{"NY", "NY"}, {"Brooklyn", "Brooklyn"}}, {"#### Bedford Ave", "#### Bedford Ave"}, {"Apt ##", "Apt ##"}},
    {"14202-####", {{"NY", "NY"}, {"Buffalo", "Buffalo"}}, {"### Main St", "### Main St"}, {}},
    {"14203-####", {{"NY", "NY"}, {"Buffalo", "Buffalo"}}, {"### Pearl St", "### Pearl St"}, {"Unit ###", "Unit ###"}},
    {"12207-####", {{"NY", "NY"}, {"Albany", "Albany"}}, {"### State St", "### State St"}, {}},
    {"13202-####", {{"NY", "NY"}, {"Syracuse", "Syracuse"}}, {"### S Warren St", "### S Warren St"}, {}},
    {"14614-####", {{"NY", "NY"}, {"Rochester", "Rochester"}}, {"### E Main St", "### E Main St"}, {"Suite ##", "Suite ##"}},

    // State: Texas
    {"77002-####", {{"TX", "TX"}, {"Houston", "Houston"}}, {"### Main St", "### Main St"}, {"Floor ##", "Floor ##"}},
    {"77006-####", {{"TX", "TX"}, {"Houston", "Houston"}}, {"#### Westheimer Rd", "#### Westheimer Rd"}, {"Apt ####", "Apt ####"}},
    {"78701-####", {{"TX", "TX"}, {"Austin", "Austin"}}, {"### Congress Ave", "### Congress Ave"}, {}},
    {"78704-####", {{"TX", "TX"}, {"Austin", "Austin"}}, {"#### S Lamar Blvd", "#### S Lamar Blvd"}, {"Unit @", "Unit @"}},
    {"75201-####", {{"TX", "TX"}, {"Dallas", "Dallas"}}, {"#### Elm St", "#### Elm St"}, {}},
    {"75202-####", {{"TX", "TX"}, {"Dallas", "Dallas"}}, {"### N Akard St", "### N Akard St"}, {"Suite ####", "Suite ####"}},
    {"78205-####", {{"TX", "TX"}, {"San Antonio", "San Antonio"}}, {"### E Commerce St", "### E Commerce St"}, {}},
    {"76102-####", {{"TX", "TX"}, {"Fort Worth", "Fort Worth"}}, {"### Main St", "### Main St"}, {"Apt ###", "Apt ###"}},
    {"79901-####", {{"TX", "TX"}, {"El Paso", "El Paso"}}, {"### E San Antonio Ave", "### E San Antonio Ave"}, {}},

    // State: Florida
    {"33131-####", {{"FL", "FL"}, {"Miami", "Miami"}}, {"### Brickell Ave", "### Brickell Ave"}, {"Unit ####", "Unit ####"}},
    {"33139-####", {{"FL", "FL"}, {"Miami Beach", "Miami Beach"}}, {"### Ocean Dr", "### Ocean Dr"}, {}},
    {"32801-####", {{"FL", "FL"}, {"Orlando", "Orlando"}}, {"### S Orange Ave", "### S Orange Ave"}, {"Suite ###", "Suite ###"}},
    {"32819-####", {{"FL", "FL"}, {"Orlando", "Orlando"}}, {"#### Universal Blvd", "#### Universal Blvd"}, {}},
    {"33602-####", {{"FL", "FL"}, {"Tampa", "Tampa"}}, {"### N Franklin St", "### N Franklin St"}, {"Apt ###", "Apt ###"}},
    {"33606-####", {{"FL", "FL"}, {"Tampa", "Tampa"}}, {"### S Plant Ave", "### S Plant Ave"}, {}},
    {"32202-####", {{"FL", "FL"}, {"Jacksonville", "Jacksonville"}}, {"### N Laura St", "### N Laura St"}, {}},
    {"33301-####", {{"FL", "FL"}, {"Fort Lauderdale", "Fort Lauderdale"}}, {"### E Las Olas Blvd", "### E Las Olas Blvd"}, {"Ste ##", "Ste ##"}},
    {"34236-####", {{"FL", "FL"}, {"Sarasota", "Sarasota"}}, {"### John N Ringling Blvd", "### John N Ringling Blvd"}, {}},

    // State: Illinois
    {"60601-####", {{"IL", "IL"}, {"Chicago", "Chicago"}}, {"### N Michigan Ave", "### N Michigan Ave"}, {}},
    {"60606-####", {{"IL", "IL"}, {"Chicago", "Chicago"}}, {"### W Wacker Dr", "### W Wacker Dr"}, {"Suite ####", "Suite ####"}},
    {"60611-####", {{"IL", "IL"}, {"Chicago", "Chicago"}}, {"### E Chestnut St", "### E Chestnut St"}, {"Apt ##@", "Apt ##@"}},
    {"60614-####", {{"IL", "IL"}, {"Chicago", "Chicago"}}, {"#### N Clark St", "#### N Clark St"}, {}},
    {"62701-####", {{"IL", "IL"}, {"Springfield", "Springfield"}}, {"### E Adams St", "### E Adams St"}, {}},
    {"61602-####", {{"IL", "IL"}, {"Peoria", "Peoria"}}, {"### Main St", "### Main St"}, {"Unit ###", "Unit ###"}},
    {"61101-####", {{"IL", "IL"}, {"Rockford", "Rockford"}}, {"### S Main St", "### S Main St"}, {}},

    // State: Pennsylvania
    {"19102-####", {{"PA", "PA"}, {"Philadelphia", "Philadelphia"}}, {"#### Walnut St", "#### Walnut St"}, {"Apt ##@", "Apt ##@"}},
    {"19103-####", {{"PA", "PA"}, {"Philadelphia", "Philadelphia"}}, {"#### John F Kennedy Blvd", "#### John F Kennedy Blvd"}, {}},
    {"19106-####", {{"PA", "PA"}, {"Philadelphia", "Philadelphia"}}, {"### Chestnut St", "### Chestnut St"}, {"Floor #", "Floor #"}},
    {"15219-####", {{"PA", "PA"}, {"Pittsburgh", "Pittsburgh"}}, {"### Grant St", "### Grant St"}, {}},
    {"15222-####", {{"PA", "PA"}, {"Pittsburgh", "Pittsburgh"}}, {"### Liberty Ave", "### Liberty Ave"}, {"Ste ####", "Ste ####"}},
    {"17101-####", {{"PA", "PA"}, {"Harrisburg", "Harrisburg"}}, {"### N 2nd St", "### N 2nd St"}, {}},
    {"18101-####", {{"PA", "PA"}, {"Allentown", "Allentown"}}, {"### Hamilton St", "### Hamilton St"}, {}},
    {"16501-####", {{"PA", "PA"}, {"Erie", "Erie"}}, {"### State St", "### State St"}, {"Apt #", "Apt #"}},

    // State: Arizona
    {"85003-####", {{"AZ", "AZ"}, {"Phoenix", "Phoenix"}}, {"### N Central Ave", "### N Central Ave"}, {"Suite ###", "Suite ###"}},
    {"85004-####", {{"AZ", "AZ"}, {"Phoenix", "Phoenix"}}, {"### E Washington St", "### E Washington St"}, {}},
    {"85016-####", {{"AZ", "AZ"}, {"Phoenix", "Phoenix"}}, {"#### E Camelback Rd", "#### E Camelback Rd"}, {"Apt ###", "Apt ###"}},
    {"85701-####", {{"AZ", "AZ"}, {"Tucson", "Tucson"}}, {"### N Stone Ave", "### N Stone Ave"}, {}},
    {"85251-####", {{"AZ", "AZ"}, {"Scottsdale", "Scottsdale"}}, {"#### N Scottsdale Rd", "#### N Scottsdale Rd"}, {}},
    {"85281-####", {{"AZ", "AZ"}, {"Tempe", "Tempe"}}, {"### S Mill Ave", "### S Mill Ave"}, {"Unit @", "Unit @"}},
    {"86001-####", {{"AZ", "AZ"}, {"Flagstaff", "Flagstaff"}}, {"### W Route 66", "### W Route 66"}, {}},

    // State: Washington
    {"98101-####", {{"WA", "WA"}, {"Seattle", "Seattle"}}, {"#### Pike St", "#### Pike St"}, {"Apt ###", "Apt ###"}},
    {"98104-####", {{"WA", "WA"}, {"Seattle", "Seattle"}}, {"### 4th Ave", "### 4th Ave"}, {}},
    {"98121-####", {{"WA", "WA"}, {"Seattle", "Seattle"}}, {"#### Virginia St", "#### Virginia St"}, {"Unit ####", "Unit ####"}},
    {"98004-####", {{"WA", "WA"}, {"Bellevue", "Bellevue"}}, {"#### Bellevue Way NE", "#### Bellevue Way NE"}, {}},
    {"98402-####", {{"WA", "WA"}, {"Tacoma", "Tacoma"}}, {"#### Pacific Ave", "#### Pacific Ave"}, {"Suite ##", "Suite ##"}},
    {"99201-####", {{"WA", "WA"}, {"Spokane", "Spokane"}}, {"### W Main Ave", "### W Main Ave"}, {}},
    {"98501-####", {{"WA", "WA"}, {"Olympia", "Olympia"}}, {"#### Capitol Way S", "#### Capitol Way S"}, {}},

    // State: Massachusetts
    {"02108-####", {{"MA", "MA"}, {"Boston", "Boston"}}, {"### Beacon St", "### Beacon St"}, {}},
    {"02109-####", {{"MA", "MA"}, {"Boston", "Boston"}}, {"### State St", "### State St"}, {"Fl #", "Fl #"}},
    {"02110-####", {{"MA", "MA"}, {"Boston", "Boston"}}, {"### Franklin St", "### Franklin St"}, {"Suite ###", "Suite ###"}},
    {"02138-####", {{"MA", "MA"}, {"Cambridge", "Cambridge"}}, {"### Massachusetts Ave", "### Massachusetts Ave"}, {}},
    {"02139-####", {{"MA", "MA"}, {"Cambridge", "Cambridge"}}, {"### Main St", "### Main St"}, {"Apt ##", "Apt ##"}},
    {"01608-####", {{"MA", "MA"}, {"Worcester", "Worcester"}}, {"### Main St", "### Main St"}, {}},
    {"01103-####", {{"MA", "MA"}, {"Springfield", "Springfield"}}, {"#### Main St", "#### Main St"}, {}},
    {"01970-####", {{"MA", "MA"}, {"Salem", "Salem"}}, {"### Essex St", "### Essex St"}, {"Unit #@", "Unit #@"}},

    // State: Colorado
    {"80202-####", {{"CO", "CO"}, {"Denver", "Denver"}}, {"#### 17th St", "#### 17th St"}, {"Suite ####", "Suite ####"}},
    {"80203-####", {{"CO", "CO"}, {"Denver", "Denver"}}, {"### N Broadway", "### N Broadway"}, {}},
    {"80302-####", {{"CO", "CO"}, {"Boulder", "Boulder"}}, {"#### Pearl St", "#### Pearl St"}, {"Unit ###", "Unit ###"}},
    {"80903-####", {{"CO", "CO"}, {"Colorado Springs", "Colorado Springs"}}, {"### S Tejon St", "### S Tejon St"}, {}},
    {"81611-####", {{"CO", "CO"}, {"Aspen", "Aspen"}}, {"### E Main St", "### E Main St"}, {"Apt #", "Apt #"}},
    {"81003-####", {{"CO", "CO"}, {"Pueblo", "Pueblo"}}, {"### N Grand Ave", "### N Grand Ave"}, {}},

    // State: Georgia
    {"30303-####", {{"GA", "GA"}, {"Atlanta", "Atlanta"}}, {"### Marietta St NW", "### Marietta St NW"}, {}},
    {"30309-####", {{"GA", "GA"}, {"Atlanta", "Atlanta"}}, {"#### Peachtree St NE", "#### Peachtree St NE"}, {"Apt ####", "Apt ####"}},
    {"30361-####", {{"GA", "GA"}, {"Atlanta", "Atlanta"}}, {"### Perimeter Center E", "### Perimeter Center E"}, {"Suite ###", "Suite ###"}},
    {"31401-####", {{"GA", "GA"}, {"Savannah", "Savannah"}}, {"### E Bay St", "### E Bay St"}, {}},
    {"30901-####", {{"GA", "GA"}, {"Augusta", "Augusta"}}, {"### Broad St", "### Broad St"}, {"Unit ##", "Unit ##"}},
    {"31201-####", {{"GA", "GA"}, {"Macon", "Macon"}}, {"### Mulberry St", "### Mulberry St"}, {}},

    // State: Ohio
    {"43215-####", {{"OH", "OH"}, {"Columbus", "Columbus"}}, {"### N High St", "### N High St"}, {}},
    {"43210-####", {{"OH", "OH"}, {"Columbus", "Columbus"}}, {"#### Neil Ave", "#### Neil Ave"}, {"Rm ###", "Rm ###"}},
    {"44113-####", {{"OH", "OH"}, {"Cleveland", "Cleveland"}}, {"#### Professor Ave", "#### Professor Ave"}, {}},
    {"44114-####", {{"OH", "OH"}, {"Cleveland", "Cleveland"}}, {"### E 9th St", "### E 9th St"}, {"Suite ##", "Suite ##"}},
    {"45202-####", {{"OH", "OH"}, {"Cincinnati", "Cincinnati"}}, {"### E 4th St", "### E 4th St"}, {"Apt ###", "Apt ###"}},
    {"45402-####", {{"OH", "OH"}, {"Dayton", "Dayton"}}, {"### S Main St", "### S Main St"}, {}},
    {"44308-####", {{"OH", "OH"}, {"Akron", "Akron"}}, {"### S Main St", "### S Main St"}, {}},

    // State: North Carolina
    {"28202-####", {{"NC", "NC"}, {"Charlotte", "Charlotte"}}, {"### S Tryon St", "### S Tryon St"}, {"Suite ###", "Suite ###"}},
    {"28203-####", {{"NC", "NC"}, {"Charlotte", "Charlotte"}}, {"#### South Blvd", "#### South Blvd"}, {}},
    {"27601-####", {{"NC", "NC"}, {"Raleigh", "Raleigh"}}, {"### Fayetteville St", "### Fayetteville St"}, {"Apt ###", "Apt ###"}},
    {"27701-####", {{"NC", "NC"}, {"Durham", "Durham"}}, {"### W Main St", "### W Main St"}, {}},
    {"28801-####", {{"NC", "NC"}, {"Asheville", "Asheville"}}, {"### Patton Ave", "### Patton Ave"}, {"Unit @", "Unit @"}},
    {"27401-####", {{"NC", "NC"}, {"Greensboro", "Greensboro"}}, {"### N Elm St", "### N Elm St"}, {}},
    {"28401-####", {{"NC", "NC"}, {"Wilmington", "Wilmington"}}, {"### N Water St", "### N Water St"}, {}},

    // State: Michigan
    {"48226-####", {{"MI", "MI"}, {"Detroit", "Detroit"}}, {"### Woodward Ave", "### Woodward Ave"}, {"Apt ####", "Apt ####"}},
    {"48201-####", {{"MI", "MI"}, {"Detroit", "Detroit"}}, {"#### Cass Ave", "#### Cass Ave"}, {}},
    {"49503-####", {{"MI", "MI"}, {"Grand Rapids", "Grand Rapids"}}, {"### Pearl St NW", "### Pearl St NW"}, {"Suite ###", "Suite ###"}},
    {"48104-####", {{"MI", "MI"}, {"Ann Arbor", "Ann Arbor"}}, {"### S State St", "### S State St"}, {}},
    {"48933-####", {{"MI", "MI"}, {"Lansing", "Lansing"}}, {"### S Washington Sq", "### S Washington Sq"}, {}},
    {"49007-####", {{"MI", "MI"}, {"Kalamazoo", "Kalamazoo"}}, {"#### W Michigan Ave", "#### W Michigan Ave"}, {"Apt ###", "Apt ###"}},

    // State: Virginia
    {"23219-####", {{"VA", "VA"}, {"Richmond", "Richmond"}}, {"### E Main St", "### E Main St"}, {}},
    {"23451-####", {{"VA", "VA"}, {"Virginia Beach", "Virginia Beach"}}, {"#### Atlantic Ave", "#### Atlantic Ave"}, {"Suite ###", "Suite ###"}},
    {"22201-####", {{"VA", "VA"}, {"Arlington", "Arlington"}}, {"#### Wilson Blvd", "#### Wilson Blvd"}, {}},
    {"22314-####", {{"VA", "VA"}, {"Alexandria", "Alexandria"}}, {"### King St", "### King St"}, {"Apt ##", "Apt ##"}},
    {"22903-####", {{"VA", "VA"}, {"Charlottesville", "Charlottesville"}}, {"### W Main St", "### W Main St"}, {}},
    {"24011-####", {{"VA", "VA"}, {"Roanoke", "Roanoke"}}, {"### Market St SE", "### Market St SE"}, {}},

    // State: Oregon
    {"97201-####", {{"OR", "OR"}, {"Portland", "Portland"}}, {"#### SW Naito Pkwy", "#### SW Naito Pkwy"}, {"Suite ##", "Suite ##"}},
    {"97204-####", {{"OR", "OR"}, {"Portland", "Portland"}}, {"### SW 5th Ave", "### SW 5th Ave"}, {}},
    {"97209-####", {{"OR", "OR"}, {"Portland", "Portland"}}, {"#### NW 23rd Ave", "#### NW 23rd Ave"}, {"Apt #", "Apt #"}},
    {"97301-####", {{"OR", "OR"}, {"Salem", "Salem"}}, {"### State St", "### State St"}, {}},
    {"97401-####", {{"OR", "OR"}, {"Eugene", "Eugene"}}, {"### Willamette St", "### Willamette St"}, {}},

    // State: Utah
    {"84101-####", {{"UT", "UT"}, {"Salt Lake City", "Salt Lake City"}}, {"### S Main St", "### S Main St"}, {"Suite ###", "Suite ###"}},
    {"84111-####", {{"UT", "UT"}, {"Salt Lake City", "Salt Lake City"}}, {"### E 200 S", "### E 200 S"}, {}},
    {"84601-####", {{"UT", "UT"}, {"Provo", "Provo"}}, {"### W Center St", "### W Center St"}, {"Unit @", "Unit @"}},
    {"84060-####", {{"UT", "UT"}, {"Park City", "Park City"}}, {"### Main St", "### Main St"}, {}},
    {"84401-####", {{"UT", "UT"}, {"Ogden", "Ogden"}}, {"#### Washington Blvd", "#### Washington Blvd"}, {}},

    // State: Tennessee
    {"37201-####", {{"TN", "TN"}, {"Nashville", "Nashville"}}, {"### Broadway", "### Broadway"}, {"Apt ###", "Apt ###"}},
    {"37203-####", {{"TN", "TN"}, {"Nashville", "Nashville"}}, {"#### Demonbreun St", "#### Demonbreun St"}, {}},
    {"38103-####", {{"TN", "TN"}, {"Memphis", "Memphis"}}, {"### Union Ave", "### Union Ave"}, {"Suite ##", "Suite ##"}},
    {"37902-####", {{"TN", "TN"}, {"Knoxville", "Knoxville"}}, {"### S Gay St", "### S Gay St"}, {}},
    {"37402-####", {{"TN", "TN"}, {"Chattanooga", "Chattanooga"}}, {"### Broad St", "### Broad St"}, {}},

    // State: Nevada
    {"89101-####", {{"NV", "NV"}, {"Las Vegas", "Las Vegas"}}, {"### Fremont St", "### Fremont St"}, {}},
    {"89109-####", {{"NV", "NV"}, {"Las Vegas", "Las Vegas"}}, {"#### Las Vegas Blvd S", "#### Las Vegas Blvd S"}, {"Suite ####", "Suite ####"}},
    {"89501-####", {{"NV", "NV"}, {"Reno", "Reno"}}, {"### N Virginia St", "### N Virginia St"}, {}},
    {"89451-####", {{"NV", "NV"}, {"Incline Village", "Incline Village"}}, {"### Lakeshore Blvd", "### Lakeshore Blvd"}, {"Unit ###", "Unit ###"}},

    // State: Louisiana
    {"70112-####", {{"LA", "LA"}, {"New Orleans", "New Orleans"}}, {"### Canal St", "### Canal St"}, {}},
    {"70130-####", {{"LA", "LA"}, {"New Orleans", "New Orleans"}}, {"### St Charles Ave", "### St Charles Ave"}, {"Apt #", "Apt #"}},
    {"70116-####", {{"LA", "LA"}, {"New Orleans", "New Orleans"}}, {"### Bourbon St", "### Bourbon St"}, {}},
    {"70802-####", {{"LA", "LA"}, {"Baton Rouge", "Baton Rouge"}}, {"### 3rd St", "### 3rd St"}, {"Suite ##", "Suite ##"}},

    // State: Maryland
    {"21201-####", {{"MD", "MD"}, {"Baltimore", "Baltimore"}}, {"### N Charles St", "### N Charles St"}, {}},
    {"21202-####", {{"MD", "MD"}, {"Baltimore", "Baltimore"}}, {"### E Pratt St", "### E Pratt St"}, {"Suite ####", "Suite ####"}},
    {"21401-####", {{"MD", "MD"}, {"Annapolis", "Annapolis"}}, {"### Main St", "### Main St"}, {}},
    {"20850-####", {{"MD", "MD"}, {"Rockville", "Rockville"}}, {"### Rockville Pike", "### Rockville Pike"}, {"Apt ###", "Apt ###"}},

    // State: Missouri
    {"63101-####", {{"MO", "MO"}, {"St. Louis", "St. Louis"}}, {"### N Broadway", "### N Broadway"}, {}},
    {"63103-####", {{"MO", "MO"}, {"St. Louis", "St. Louis"}}, {"#### Olive St", "#### Olive St"}, {"Suite ###", "Suite ###"}},
    {"64105-####", {{"MO", "MO"}, {"Kansas City", "Kansas City"}}, {"#### Main St", "#### Main St"}, {}},
    {"65806-####", {{"MO", "MO"}, {"Springfield", "Springfield"}}, {"### S Campbell Ave", "### S Campbell Ave"}, {}},
    {"65203-####", {{"MO", "MO"}, {"Columbia", "Columbia"}}, {"### S 9th St", "### S 9th St"}, {"Unit @#", "Unit @#"}},

    // State: Kentucky
    {"40202-####", {{"KY", "KY"}, {"Louisville", "Louisville"}}, {"### W Main St", "### W Main St"}, {}},
    {"40507-####", {{"KY", "KY"}, {"Lexington", "Lexington"}}, {"#### Main St", "#### Main St"}, {"Suite ###", "Suite ###"}},
    {"42101-####", {{"KY", "KY"}, {"Bowling Green", "Bowling Green"}}, {"### State St", "### State St"}, {}},

});

const auto kUnitedKingdomAddressComponents = std::to_array<AddressComponents>({
    // Location: London (England)
    {"SW1A 0AA", {{"LONDON", "LONDON"}}, {"10 Downing Street", "10 Downing Street"}, {}},
    {"SW1A #@@", {{"LONDON", "LONDON"}}, {"## Parliament Street", "## Parliament Street"}, {}},
    {"W1U #@@", {{"LONDON", "LONDON"}}, {"### Baker Street", "### Baker Street"}, {"Flat @", "Flat @"}},
    {"EC1A #@@", {{"LONDON", "LONDON"}}, {"### St. John Street", "### St. John Street"}, {"Floor #", "Floor #"}},
    {"SE1 #@@", {{"LONDON", "LONDON"}}, {"### Tooley Street", "### Tooley Street"}, {}},
    {"SE1 #@@", {{"LONDON", "LONDON"}, {"South Bank", "South Bank"}}, {"## Belvedere Road", "## Belvedere Road"}, {"Apartment ###", "Apartment ###"}},
    {"N1 #@@", {{"LONDON", "LONDON"}, {"Islington", "Islington"}}, {"### Upper Street", "### Upper Street"}, {}},
    {"E1 #@@", {{"LONDON", "LONDON"}, {"Whitechapel", "Whitechapel"}}, {"### Whitechapel High St", "### Whitechapel High St"}, {"Flat ##", "Flat ##"}},
    {"NW1 #@@", {{"LONDON", "LONDON"}, {"Regent's Park", "Regent's Park"}}, {"### Outer Circle", "### Outer Circle"}, {}},
    {"WC2H #@@", {{"LONDON", "LONDON"}}, {"## Charing Cross Road", "## Charing Cross Road"}, {}},
    {"SW3 #@@", {{"LONDON", "LONDON"}, {"Chelsea", "Chelsea"}}, {"### King's Road", "### King's Road"}, {"Maisonette #", "Maisonette #"}},
    {"W2 #@@", {{"LONDON", "LONDON"}, {"Paddington", "Paddington"}}, {"### Praed Street", "### Praed Street"}, {}},

    // Location: Manchester (England)
    {"M1 #@@", {{"MANCHESTER", "MANCHESTER"}}, {"### Piccadilly", "### Piccadilly"}, {"Suite #", "Suite #"}},
    {"M2 #@@", {{"MANCHESTER", "MANCHESTER"}}, {"### Deansgate", "### Deansgate"}, {}},
    {"M3 #@@", {{"MANCHESTER", "MANCHESTER"}, {"Spinningfields", "Spinningfields"}}, {"# Hardman Square", "# Hardman Square"}, {"Floor #", "Floor #"}},
    {"M4 #@@", {{"MANCHESTER", "MANCHESTER"}, {"Ancoats", "Ancoats"}}, {"### Blossom Street", "### Blossom Street"}, {"Apt ###", "Apt ###"}},
    {"M15 #@@", {{"MANCHESTER", "MANCHESTER"}, {"Hulme", "Hulme"}}, {"### Stretford Road", "### Stretford Road"}, {}},
    {"M50 #@@", {{"SALFORD", "SALFORD"}, {"Salford Quays", "Salford Quays"}}, {"### The Quays", "### The Quays"}, {"The Lowry", "The Lowry"}},

    // Location: Liverpool (England)
    {"L1 #@@", {{"LIVERPOOL", "LIVERPOOL"}}, {"### Bold Street", "### Bold Street"}, {"Flat #@", "Flat #@"}},
    {"L2 #@@", {{"LIVERPOOL", "LIVERPOOL"}}, {"### Castle Street", "### Castle Street"}, {}},
    {"L3 #@@", {{"LIVERPOOL", "LIVERPOOL"}}, {"## Mann Island", "## Mann Island"}, {"Unit ###", "Unit ###"}},
    {"L4 #@@", {{"LIVERPOOL", "LIVERPOOL"}, {"Anfield", "Anfield"}}, {"## Anfield Road", "## Anfield Road"}, {}},
    {"L8 #@@", {{"LIVERPOOL", "LIVERPOOL"}, {"Toxteth", "Toxteth"}}, {"### Princes Avenue", "### Princes Avenue"}, {"Flat #", "Flat #"}},

    // Location: Birmingham (England)
    {"B1 #@@", {{"BIRMINGHAM", "BIRMINGHAM"}}, {"# Centenary Square", "# Centenary Square"}, {}},
    {"B2 #@@", {{"BIRMINGHAM", "BIRMINGHAM"}}, {"### New Street", "### New Street"}, {}},
    {"B3 #@@", {{"BIRMINGHAM", "BIRMINGHAM"}}, {"### Colmore Row", "### Colmore Row"}, {"Office ###", "Office ###"}},
    {"B4 #@@", {{"BIRMINGHAM", "BIRMINGHAM"}}, {"# Corporation Street", "# Corporation Street"}, {}},
    {"B5 #@@", {{"BIRMINGHAM", "BIRMINGHAM"}, {"Digbeth", "Digbeth"}}, {"### High Street Deritend", "### High Street Deritend"}, {"Studio #", "Studio #"}},

    // Location: Bristol (England)
    {"BS1 #@@", {{"BRISTOL", "BRISTOL"}}, {"### Baldwin Street", "### Baldwin Street"}, {}},
    {"BS1 #@@", {{"BRISTOL", "BRISTOL"}, {"Harbourside", "Harbourside"}}, {"## Anchor Road", "## Anchor Road"}, {"Apt ##", "Apt ##"}},
    {"BS8 #@@", {{"BRISTOL", "BRISTOL"}, {"Clifton", "Clifton"}}, {"### Whiteladies Road", "### Whiteladies Road"}, {}},
    {"BS6 #@@", {{"BRISTOL", "BRISTOL"}, {"Redland", "Redland"}}, {"### Redland Grove", "### Redland Grove"}, {"Flat @", "Flat @"}},

    // Location: Leeds (England)
    {"LS1 #@@", {{"LEEDS", "LEEDS"}}, {"### The Headrow", "### The Headrow"}, {}},
    {"LS2 #@@", {{"LEEDS", "LEEDS"}}, {"### Briggate", "### Briggate"}, {"Suite #", "Suite #"}},
    {"LS11 #@@", {{"LEEDS", "LEEDS"}, {"Holbeck", "Holbeck"}}, {"### Water Lane", "### Water Lane"}, {}},

    // Location: Newcastle upon Tyne (England)
    {"NE1 #@@", {{"NEWCASTLE UPON TYNE", "NEWCASTLE UPON TYNE"}}, {"### Grainger Street", "### Grainger Street"}, {}},
    {"NE1 #@@", {{"NEWCASTLE UPON TYNE", "NEWCASTLE UPON TYNE"}}, {"### Grey Street", "### Grey Street"}, {"Apartment ###", "Apartment ###"}},
    {"NE2 #@@", {{"NEWCASTLE UPON TYNE", "NEWCASTLE UPON TYNE"}, {"Jesmond", "Jesmond"}}, {"### Osborne Road", "### Osborne Road"}, {}},

    // Location: York (England)
    {"YO1 #@@", {{"YORK", "YORK"}}, {"### Stonegate", "### Stonegate"}, {}},
    {"YO1 #@@", {{"YORK", "YORK"}}, {"## High Petergate", "## High Petergate"}, {"The Shambles", "The Shambles"}},
    {"YO10 #@@", {{"YORK", "YORK"}}, {"### Heslington Road", "### Heslington Road"}, {"Flat ##", "Flat ##"}},

    // Location: Cambridge & Oxford (England)
    {"CB2 #@@", {{"CAMBRIDGE", "CAMBRIDGE"}}, {"### King's Parade", "### King's Parade"}, {}},
    {"CB5 #@@", {{"CAMBRIDGE", "CAMBRIDGE"}}, {"### Newmarket Road", "### Newmarket Road"}, {"Room #", "Room #"}},
    {"OX1 #@@", {{"OXFORD", "OXFORD"}}, {"### High Street", "### High Street"}, {}},
    {"OX2 #@@", {{"OXFORD", "OXFORD"}, {"Summertown", "Summertown"}}, {"### Banbury Road", "### Banbury Road"}, {"Flat #", "Flat #"}},

    // Location: Brighton (England)
    {"BN1 #@@", {{"BRIGHTON", "BRIGHTON"}}, {"### North Laine", "### North Laine"}, {}},
    {"BN2 #@@", {{"BRIGHTON", "BRIGHTON"}, {"Kemptown", "Kemptown"}}, {"### St George's Road", "### St George's Road"}, {"Apartment #", "Apartment #"}},

    // Location: Bath (England)
    {"BA1 #@@", {{"BATH", "BATH"}}, {"# The Circus", "# The Circus"}, {}},
    {"BA2 #@@", {{"BATH", "BATH"}}, {"### Southgate Street", "### Southgate Street"}, {"Flat #", "Flat #"}},

    // === Scotland ===
    // Location: Edinburgh
    {"EH1 #@@", {{"EDINBURGH", "EDINBURGH"}}, {"### High Street", "### High Street"}, {"Royal Mile", "Royal Mile"}},
    {"EH1 #@@", {{"EDINBURGH", "EDINBURGH"}}, {"### Princes Street", "### Princes Street"}, {}},
    {"EH2 #@@", {{"EDINBURGH", "EDINBURGH"}}, {"### George Street", "### George Street"}, {"Floor #", "Floor #"}},
    {"EH3 #@@", {{"EDINBURGH", "EDINBURGH"}, {"New Town", "New Town"}}, {"### Queen Street", "### Queen Street"}, {"Basement Flat", "Basement Flat"}},
    {"EH8 #@@", {{"EDINBURGH", "EDINBURGH"}, {"Old Town", "Old Town"}}, {"### Canongate", "### Canongate"}, {}},
    {"EH12 #@@", {{"EDINBURGH", "EDINBURGH"}}, {"### Haymarket Terrace", "### Haymarket Terrace"}, {"Flat #/#", "Flat #/#"}},

    // Location: Glasgow
    {"G1 #@@", {{"GLASGOW", "GLASGOW"}}, {"### Buchanan Street", "### Buchanan Street"}, {}},
    {"G2 #@@", {{"GLASGOW", "GLASGOW"}}, {"### Sauchiehall Street", "### Sauchiehall Street"}, {"Suite ##", "Suite ##"}},
    {"G3 #@@", {{"GLASGOW", "GLASGOW"}, {"Finnieston", "Finnieston"}}, {"### Argyle Street", "### Argyle Street"}, {}},
    {"G4 #@@", {{"GLASGOW", "GLASGOW"}}, {"### Cathedral Street", "### Cathedral Street"}, {"Room ##", "Room ##"}},
    {"G11 #@@", {{"GLASGOW", "GLASGOW"}, {"Partick", "Partick"}}, {"### Dumbarton Road", "### Dumbarton Road"}, {"Flat @/#", "Flat @/#"}},
    {"G12 #@@", {{"GLASGOW", "GLASGOW"}, {"Hillhead", "Hillhead"}}, {"### Byres Road", "### Byres Road"}, {}},

    // Location: Aberdeen & Dundee
    {"AB10 #@@", {{"ABERDEEN", "ABERDEEN"}}, {"### Union Street", "### Union Street"}, {}},
    {"AB24 #@@", {{"ABERDEEN", "ABERDEEN"}, {"Old Aberdeen", "Old Aberdeen"}}, {"### High Street", "### High Street"}, {"Apartment #", "Apartment #"}},
    {"DD1 #@@", {{"DUNDEE", "DUNDEE"}}, {"### Nethergate", "### Nethergate"}, {}},
    {"DD4 #@@", {{"DUNDEE", "DUNDEE"}}, {"### Albert Street", "### Albert Street"}, {"Flat ##", "Flat ##"}},

    // === Wales ===
    // Location: Cardiff
    {"CF10 #@@", {{"CARDIFF", "CARDIFF"}}, {"### St Mary Street", "### St Mary Street"}, {}},
    {"CF10 #@@", {{"CARDIFF", "CARDIFF"}, {"Cathays Park", "Cathays Park"}}, {"# King Edward VII Avenue", "# King Edward VII Avenue"}, {}},
    {"CF11 #@@", {{"CARDIFF", "CARDIFF"}, {"Canton", "Canton"}}, {"### Leckwith Road", "### Leckwith Road"}, {"Flat #", "Flat #"}},
    {"CF24 #@@", {{"CARDIFF", "CARDIFF"}, {"Roath", "Roath"}}, {"### City Road", "### City Road"}, {}},

    // Location: Swansea
    {"SA1 #@@", {{"SWANSEA", "SWANSEA"}}, {"### The Kingsway", "### The Kingsway"}, {}},
    {"SA1 #@@", {{"SWANSEA", "SWANSEA"}, {"Maritime Quarter", "Maritime Quarter"}}, {"### Trawler Road", "### Trawler Road"}, {"Apt ##", "Apt ##"}},

    // Location: Newport
    {"NP20 #@@", {{"NEWPORT", "NEWPORT"}}, {"### Commercial Street", "### Commercial Street"}, {}},

    // === Northern Ireland ===
    // Location: Belfast
    {"BT1 #@@", {{"BELFAST", "BELFAST"}}, {"### Donegall Square N", "### Donegall Square N"}, {}},
    {"BT1 #@@", {{"BELFAST", "BELFAST"}, {"Cathedral Quarter", "Cathedral Quarter"}}, {"### Donegall Street", "### Donegall Street"}, {"Office #", "Office #"}},
    {"BT2 #@@", {{"BELFAST", "BELFAST"}}, {"### Great Victoria Street", "### Great Victoria Street"}, {}},
    {"BT7 #@@", {{"BELFAST", "BELFAST"}}, {"### Ormeau Road", "### Ormeau Road"}, {"Flat @", "Flat @"}},
    {"BT9 #@@", {{"BELFAST", "BELFAST"}}, {"### Lisburn Road", "### Lisburn Road"}, {}},

    // Add more variety across different towns to reach ~200
    // England
    {"S1 #@@", {{"SHEFFIELD", "SHEFFIELD"}}, {"### Pinstone Street", "### Pinstone Street"}, {}},
    {"S10 #@@", {{"SHEFFIELD", "SHEFFIELD"}, {"Broomhill", "Broomhill"}}, {"### Whitham Road", "### Whitham Road"}, {"Flat ##", "Flat ##"}},
    {"LE1 #@@", {{"LEICESTER", "LEICESTER"}}, {"### Granby Street", "### Granby Street"}, {}},
    {"DE1 #@@", {{"DERBY", "DERBY"}}, {"### Iron Gate", "### Iron Gate"}, {"Apartment #", "Apartment #"}},
    {"NG1 #@@", {{"NOTTINGHAM", "NOTTINGHAM"}}, {"### Old Market Square", "### Old Market Square"}, {}},
    {"CV1 #@@", {{"COVENTRY", "COVENTRY"}}, {"### Corporation Street", "### Corporation Street"}, {"Floor #", "Floor #"}},
    {"PL1 #@@", {{"PLYMOUTH", "PLYMOUTH"}}, {"### Armada Way", "### Armada Way"}, {}},
    {"SO14 #@@", {{"SOUTHAMPTON", "SOUTHAMPTON"}}, {"### High Street", "### High Street"}, {"Flat #", "Flat #"}},
    {"PO1 #@@", {{"PORTSMOUTH", "PORTSMOUTH"}, {"Old Portsmouth", "Old Portsmouth"}}, {"### High Street", "### High Street"}, {}},
    {"EX4 #@@", {{"EXETER", "EXETER"}}, {"### Fore Street", "### Fore Street"}, {"Unit #", "Unit #"}},
    {"TR1 #@@", {{"TRURO", "TRURO"}}, {"### Boscawen Street", "### Boscawen Street"}, {}},
    {"CT1 #@@", {{"CANTERBURY", "CANTERBURY"}}, {"### The Parade", "### The Parade"}, {"Flat #", "Flat #"}},
    {"ME1 #@@", {{"ROCHESTER", "ROCHESTER"}}, {"### High Street", "### High Street"}, {}},
    {"HU1 #@@", {{"HULL", "HULL"}}, {"### Queen Victoria Square", "### Queen Victoria Square"}, {}},
    {"SR1 #@@", {{"SUNDERLAND", "SUNDERLAND"}}, {"### High Street West", "### High Street West"}, {"Suite #", "Suite #"}},
    {"WF1 #@@", {{"WAKEFIELD", "WAKEFIELD"}}, {"### Westgate", "### Westgate"}, {}},
    {"HD1 #@@", {{"HUDDERSFIELD", "HUDDERSFIELD"}}, {"### New Street", "### New Street"}, {}},
    {"BB1 #@@", {{"BLACKBURN", "BLACKBURN"}}, {"### King William Street", "### King William Street"}, {"Apartment ##", "Apartment ##"}},
    {"FY1 #@@", {{"BLACKPOOL", "BLACKPOOL"}}, {"### Promenade", "### Promenade"}, {}},
    {"PR1 #@@", {{"PRESTON", "PRESTON"}}, {"### Fishergate", "### Fishergate"}, {}},
    {"WN1 #@@", {{"WIGAN", "WIGAN"}}, {"### Standishgate", "### Standishgate"}, {"Flat #", "Flat #"}},
    {"OL1 #@@", {{"OLDHAM", "OLDHAM"}}, {"### High Street", "### High Street"}, {}},
    {"SK1 #@@", {{"STOCKPORT", "STOCKPORT"}}, {"### Merseyway", "### Merseyway"}, {}},
    {"CW1 #@@", {{"CREWE", "CREWE"}}, {"### Earle Street", "### Earle Street"}, {}},
    {"ST1 #@@", {{"STOKE-ON-TRENT", "STOKE-ON-TRENT"}, {"Hanley", "Hanley"}}, {"### Parliament Row", "### Parliament Row"}, {"Flat #", "Flat #"}},
    {"WS1 #@@", {{"WALSALL", "WALSALL"}}, {"### Park Street", "### Park Street"}, {}},
    {"WV1 #@@", {{"WOLVERHAMPTON", "WOLVERHAMPTON"}}, {"### Dudley Street", "### Dudley Street"}, {}},
    {"GL1 #@@", {{"GLOUCESTER", "GLOUCESTER"}}, {"### Southgate Street", "### Southgate Street"}, {"Apartment #@", "Apartment #@"}},
    {"WR1 #@@", {{"WORCESTER", "WORCESTER"}}, {"### High Street", "### High Street"}, {}},
    {"CH1 #@@", {{"CHESTER", "CHESTER"}}, {"### Eastgate Street", "### Eastgate Street"}, {}},
    {"SHREWSBURY", {{"SY1 #@@", "SY1 #@@"}}, {"### Pride Hill", "### Pride Hill"}, {}},
    {"HR1 #@@", {{"HEREFORD", "HEREFORD"}}, {"### High Town", "### High Town"}, {}},
    {"NR2 #@@", {{"NORWICH", "NORWICH"}}, {"### St Giles Street", "### St Giles Street"}, {"Flat #", "Flat #"}},

    // Scotland
    {"PA1 #@@", {{"PAISLEY", "PAISLEY"}}, {"### High Street", "### High Street"}, {}},
    {"FK8 #@@", {{"STIRLING", "STIRLING"}}, {"### Port Street", "### Port Street"}, {"Flat #", "Flat #"}},
    {"IV2 #@@", {{"INVERNESS", "INVERNESS"}}, {"### Bridge Street", "### Bridge Street"}, {}},
    {"KA7 #@@", {{"AYR", "AYR"}}, {"### High Street", "### High Street"}, {}},
    {"PH2 #@@", {{"PERTH", "PERTH"}}, {"### South Street", "### South Street"}, {"Apt #", "Apt #"}},

    // Wales
    {"LL57 #@@", {{"BANGOR", "BANGOR"}}, {"### High Street", "### High Street"}, {}},
    {"LL30 #@@", {{"LLANDUDNO", "LLANDUDNO"}}, {"### Mostyn Street", "### Mostyn Street"}, {}},

    // Northern Ireland
    {"BT48 #@@", {{"LONDONDERRY", "LONDONDERRY"}}, {"### Shipquay Street", "### Shipquay Street"}, {}},

    // London Suburbs for more variety
    {"CR0 #@@", {{"CROYDON", "CROYDON"}}, {"### High Street", "### High Street"}, {"Flat ###", "Flat ###"}},
    {"BR1 #@@", {{"BROMLEY", "BROMLEY"}}, {"### High Street", "### High Street"}, {}},
    {"KT1 #@@", {{"KINGSTON UPON THAMES", "KINGSTON UPON THAMES"}}, {"### Clarence Street", "### Clarence Street"}, {}},
    {"RM1 #@@", {{"ROMFORD", "ROMFORD"}}, {"### South Street", "### South Street"}, {}},
    {"IG1 #@@", {{"ILFORD", "ILFORD"}}, {"### High Road", "### High Road"}, {"Flat ##", "Flat ##"}},
    {"HA1 #@@", {{"HARROW", "HARROW"}}, {"### Station Road", "### Station Road"}, {}},
    {"EN1 #@@", {{"ENFIELD", "ENFIELD"}}, {"### Church Street", "### Church Street"}, {}},
    {"TW9 #@@", {{"RICHMOND", "RICHMOND"}}, {"### The Green", "### The Green"}, {"Apartment #", "Apartment #"}},
    {"SM1 #@@", {{"SUTTON", "SUTTON"}}, {"### High Street", "### High Street"}, {}},
    {"UB8 #@@", {{"UXBRIDGE", "UXBRIDGE"}}, {"### High Street", "### High Street"}, {}},
    {"DA6 #@@", {{"BEXLEYHEATH", "BEXLEYHEATH"}}, {"### The Broadway", "### The Broadway"}, {}},

    // More random towns
    {"RG1 #@@", {{"READING", "READING"}}, {"### Broad Street", "### Broad Street"}, {}},
    {"SL1 #@@", {{"SLOUGH", "SLOUGH"}}, {"### High Street", "### High Street"}, {"Apt #", "Apt #"}},
    {"LU1 #@@", {{"LUTON", "LUTON"}}, {"### George Street", "### George Street"}, {}},
    {"HP20 #@@", {{"AYLESBURY", "AYLESBURY"}}, {"### Market Square", "### Market Square"}, {}},
    {"SG1 #@@", {{"STEVENAGE", "STEVENAGE"}}, {"### Queensway", "### Queensway"}, {}},
    {"MK9 #@@", {{"MILTON KEYNES", "MILTON KEYNES"}}, {"### Silbury Boulevard", "### Silbury Boulevard"}, {"Suite #", "Suite #"}},
    {"GU1 #@@", {{"GUILDFORD", "GUILDFORD"}}, {"### High Street", "### High Street"}, {}},
    {"IP4 #@@", {{"IPSWICH", "IPSWICH"}}, {"### St Helens Street", "### St Helens Street"}, {}},
    {"NN1 #@@", {{"NORTHAMPTON", "NORTHAMPTON"}}, {"### Abington Street", "### Abington Street"}, {}},
    {"PE1 #@@", {{"PETERBOROUGH", "PETERBOROUGH"}}, {"### Cathedral Square", "### Cathedral Square"}, {}},
    {"TN1 #@@", {{"TUNBRIDGE WELLS", "TUNBRIDGE WELLS"}}, {"### Mount Pleasant Road", "### Mount Pleasant Road"}, {"Flat #", "Flat #"}},
    {"SS1 #@@", {{"SOUTHEND-ON-SEA", "SOUTHEND-ON-SEA"}}, {"### High Street", "### High Street"}, {}},
    {"CM2 #@@", {{"CHELMSFORD", "CHELMSFORD"}}, {"### High Street", "### High Street"}, {}},
    {"BD1 #@@", {{"BRADFORD", "BRADFORD"}}, {"### Broadway", "### Broadway"}, {}},
    {"BA1 #@@", {{"BATH", "BATH"}}, {"### Milsom Street", "### Milsom Street"}, {"Floor #", "Floor #"}},
    {"BS23 #@@", {{"WESTON-SUPER-MARE", "WESTON-SUPER-MARE"}}, {"### High Street", "### High Street"}, {}},
    {"SN1 #@@", {{"SWINDON", "SWINDON"}}, {"### Regent Street", "### Regent Street"}, {}},
    {"TQ2 #@@", {{"TORQUAY", "TORQUAY"}}, {"### Union Street", "### Union Street"}, {"Apartment #", "Apartment #"}},
    {"DN1 #@@", {{"DONCASTER", "DONCASTER"}}, {"### St Sepulchre Gate", "### St Sepulchre Gate"}, {}},
    {"LA1 #@@", {{"LANCASTER", "LANCASTER"}}, {"### Penny Street", "### Penny Street"}, {}},
    {"CA3 #@@", {{"CARLISLE", "CARLISLE"}}, {"### English Street", "### English Street"}, {}},
    {"DH1 #@@", {{"DURHAM", "DURHAM"}}, {"### Silver Street", "### Silver Street"}, {}},
    {"DL1 #@@", {{"DARLINGTON", "DARLINGTON"}}, {"### High Row", "### High Row"}, {}},
    {"HG1 #@@", {{"HARROGATE", "HARROGATE"}}, {"### Cambridge Street", "### Cambridge Street"}, {}},
    {"LN2 #@@", {{"LINCOLN", "LINCOLN"}}, {"### High Street", "### High Street"}, {"Apt #", "Apt #"}},
    {"WA1 #@@", {{"WARRINGTON", "WARRINGTON"}}, {"### Bridge Street", "### Bridge Street"}, {}},
    {"DY1 #@@", {{"DUDLEY", "DUDLEY"}}, {"### High Street", "### High Street"}, {}},
    {"WD17 #@@", {{"WATFORD", "WATFORD"}}, {"### High Street", "### High Street"}, {}},

});

const auto kChinaAddressComponents = std::to_array<AddressComponents>({
    // City: Beijing (北京市) - Municipality (Corrected by you)
    {"100006", {{}, {"北京市", "Beijing"}, {"东城区", "Dongcheng District"}, {"东华门街道", "Donghuamen Subdistrict"}}, {"东安门大街##号", "No. ## Dong'anmen Street"}, {"#号院#楼###室", "Courtyard #, Bldg #, Rm ###"}},
    {"100005", {{}, {"北京市", "Beijing"}, {"东城区", "Dongcheng District"}, {"建国门街道", "Jianguomen Subdistrict"}}, {"赵堂子胡同##号", "No. ## Zhaotangzi Hutong"}, {}},
    {"100032", {{}, {"北京市", "Beijing"}, {"西城区", "Xicheng District"}, {"金融街街道", "Jinnrongjie Subdistrict"}}, {"金融大街##号", "No. ## Jinnrong Avenue"}, {"##层", "Fl ##"}},
    {"100011", {{}, {"北京市", "Beijing"}, {"西城区", "Xicheng District"}, {"德胜街道", "Desheng Subdistrict"}}, {"德胜门外大街##号", "No. ## Deshengmenwai Street"}, {}},
    {"100020", {{}, {"北京市", "Beijing"}, {"朝阳区", "Chaoyang District"}, {"朝外街道", "Chaowai Subdistrict"}}, {"朝阳门外大街##号", "No. ## Chaoyangmenwai Street"}, {"##室", "Rm ##"}},
    {"100027", {{}, {"北京市", "Beijing"}, {"朝阳区", "Chaoyang District"}, {"三里屯街道", "Sanlitun Subdistrict"}}, {"工体北路##号", "No. ## Gongti North Road"}, {}},
    {"100102", {{}, {"北京市", "Beijing"}, {"朝阳区", "Chaoyang District"}, {"望京街道", "Wangjing Subdistrict"}}, {"望京西路##号", "No. ## West Wangjing Road"}, {"#栋###室", "Bldg #, Rm ###"}},
    {"100080", {{}, {"北京市", "Beijing"}, {"海淀区", "Haidian District"}, {"中关村街道", "Zhongguancun Subdistrict"}}, {"中关村大街##号", "No. ## Zhongguancun Street"}, {"#号楼", "Bldg #"}},
    {"100083", {{}, {"北京市", "Beijing"}, {"海淀区", "Haidian District"}, {"学院路街道", "Xueyuanlu Subdistrict"}}, {"学院路##号", "No. ## Xueyuan Road"}, {"#号院#单元##层", "Courtyard #, Unit #, Fl ##"}},
    {"100039", {{}, {"北京市", "Beijing"}, {"海淀区", "Haidian District"}, {"万寿路街道", "Wanshoulu Subdistrict"}}, {"复兴路##号", "No. ## Fuxing Road"}, {}},
    {"100085", {{}, {"北京市", "Beijing"}, {"昌平区", "Changping District"}, {"回龙观街道", "Huilongguan Subdistrict"}}, {"育知东路##号", "No. ## Yuzhi East Road"}, {"#区#号楼", "Area #, Bldg #"}},

    // City: Shanghai (上海市) - Municipality
    {"200002", {{}, {"上海市", "Shanghai"}, {"黄浦区", "Huangpu District"}, {"外滩街道", "The Bund Subdistrict"}}, {"中山东一路##号", "No. ## Zhongshan East-1 Road"}, {}},
    {"200001", {{}, {"上海市", "Shanghai"}, {"黄浦区", "Huangpu District"}, {"南京东路街道", "Nanjing East Road Subdistrict"}}, {"南京东路##号", "No. ## Nanjing East Road"}, {"#楼", "Fl #"}},
    {"200010", {{}, {"上海市", "Shanghai"}, {"黄浦区", "Huangpu District"}, {"豫园街道", "Yuyuan Subdistrict"}}, {"福佑路##号", "No. ## Fuyou Road"}, {}},
    {"200031", {{}, {"上海市", "Shanghai"}, {"徐汇区", "Xuhui District"}, {"湖南路街道", "Hunan Road Subdistrict"}}, {"淮海中路##号", "No. ## Huaihai Middle Road"}, {"##室", "Rm ##"}},
    {"200031", {{}, {"上海市", "Shanghai"}, {"徐汇区", "Xuhui District"}, {"天平路街道", "Tianping Road Subdistrict"}}, {"衡山路##号", "No. ## Hengshan Road"}, {"#号楼#单元#层", "Bldg #, Unit #, Fl #"}},
    {"200040", {{}, {"上海市", "Shanghai"}, {"静安区", "Jing'an District"}, {"静安寺街道", "Jing'an Temple Subdistrict"}}, {"南京西路##号", "No. ## Nanjing West Road"}, {"##座##室", "Tower ##, Rm ##"}},
    {"200042", {{}, {"上海市", "Shanghai"}, {"静安区", "Jing'an District"}, {"曹家渡街道", "Caojiadu Subdistrict"}}, {"万航渡路##号", "No. ## Wanhangdu Road"}, {}},
    {"200120", {{}, {"上海市", "Shanghai"}, {"浦东新区", "Pudong New Area"}, {"陆家嘴街道", "Lujiazui Subdistrict"}}, {"世纪大道##号", "No. ## Century Avenue"}, {"##层", "Fl ##"}},
    {"201210", {{}, {"上海市", "Shanghai"}, {"浦东新区", "Pudong New Area"}, {"张江镇", "Zhangjiang Town"}}, {"祖冲之路##号", "No. ## Zuchongzhi Road"}, {"#号楼#层", "Bldg #, Fl #"}},
    {"200052", {{}, {"上海市", "Shanghai"}, {"长宁区", "Changning District"}, {"新华路街道", "Xinhua Road Subdistrict"}}, {"延安西路##号", "No. ## Yan'an West Road"}, {}},
    {"200062", {{}, {"上海市", "Shanghai"}, {"普陀区", "Putuo District"}, {"长风新村街道", "Changfeng Xincun Subdistrict"}}, {"大渡河路##号", "No. ## Daduhe Road"}, {"#号楼", "Bldg #"}},
    {"200085", {{}, {"上海市", "Shanghai"}, {"虹口区", "Hongkou District"}, {"四川北路街道", "Sichuan North Road Subdistrict"}}, {"四川北路##号", "No. ## Sichuan North Road"}, {}},
    {"200433", {{}, {"上海市", "Shanghai"}, {"杨浦区", "Yangpu District"}, {"五角场街道", "Wujiaochang Subdistrict"}}, {"黄兴路##号", "No. ## Huangxing Road"}, {"#座##室", "Tower #, Rm ##"}},

    // Province: Guangdong (广东省)
    // City: Guangzhou (广州市)
    {"510030", {{"广东省", "Guangdong Province"}, {"广州市", "Guangzhou City"}, {"越秀区", "Yuexiu District"}, {"北京街道", "Beijing Subdistrict"}}, {"中山五路##号", "No. ## Zhongshan 5th Road"}, {}},
    {"510620", {{"广东省", "Guangdong Province"}, {"广州市", "Guangzhou City"}, {"天河区", "Tianhe District"}, {"天河南街道", "Tianhenan Subdistrict"}}, {"体育西路##号", "No. ## Tiyu West Road"}, {"#座##层", "## Tower, Fl ##"}},
    {"510627", {{"广东省", "Guangdong Province"}, {"广州市", "Guangzhou City"}, {"天河区", "Tianhe District"}, {"冼村街道", "Xiancun Subdistrict"}}, {"黄埔大道西##号", "No. ## Huangpu Avenue West"}, {"##室", "Rm ##"}},
    {"510240", {{"广东省", "Guangdong Province"}, {"广州市", "Guangzhou City"}, {"海珠区", "Haizhu District"}, {"江南中街道", "Jiangnanzhong Subdistrict"}}, {"江南大道中##号", "No. ## Jiangnan Avenue Middle"}, {}},
    {"510130", {{"广东省", "Guangdong Province"}, {"广州市", "Guangzhou City"}, {"荔湾区", "Liwan District"}, {"沙面街道", "Shamian Subdistrict"}}, {"沙面北街##号", "No. ## Shamian North Street"}, {}},
    {"510405", {{"广东省", "Guangdong Province"}, {"广州市", "Guangzhou City"}, {"白云区", "Baiyun District"}, {"三元里街道", "Sanyuanli Subdistrict"}}, {"广园中路##号", "No. ## Guangyuan Middle Road"}, {}},
    {"510700", {{"广东省", "Guangdong Province"}, {"广州市", "Guangzhou City"}, {"黄埔区", "Huangpu District"}, {"黄埔街道", "Huangpu Subdistrict"}}, {"港湾路##号", "No. ## Gangwan Road"}, {"#栋#单元", "Bldg #, Unit #"}},
    // City: Shenzhen (深圳市)
    {"518033", {{"广东省", "Guangdong Province"}, {"深圳市", "Shenzhen City"}, {"福田区", "Futian District"}, {"福田街道", "Futian Subdistrict"}}, {"深南大道##号", "No. ## Shennan Boulevard"}, {"#座##室", "Block #, Rm ##"}},
    {"518031", {{"广东省", "Guangdong Province"}, {"深圳市", "Shenzhen City"}, {"福田区", "Futian District"}, {"华强北街道", "Huaqiangbei Subdistrict"}}, {"华强北路##号", "No. ## Huaqiang North Road"}, {"#层", "Fl #"}},
    {"518001", {{"广东省", "Guangdong Province"}, {"深圳市", "Shenzhen City"}, {"罗湖区", "Luohu District"}, {"桂园街道", "Guiyuan Subdistrict"}}, {"解放路##号", "No. ## Jiefang Road"}, {}},
    {"518019", {{"广东省", "Guangdong Province"}, {"深圳市", "Shenzhen City"}, {"罗湖区", "Luohu District"}, {"东门街道", "Dongmen Subdistrict"}}, {"东门中路##号", "No. ## Dongmen Middle Road"}, {}},
    {"518057", {{"广东省", "Guangdong Province"}, {"深圳市", "Shenzhen City"}, {"南山区", "Nanshan District"}, {"粤海街道", "Yuehai Subdistrict"}}, {"科技南路##号", "No. ## Keji South Road"}, {"#栋#楼", "Bldg #, Fl #"}},
    {"518052", {{"广东省", "Guangdong Province"}, {"深圳市", "Shenzhen City"}, {"南山区", "Nanshan District"}, {"南头街道", "Nantou Subdistrict"}}, {"桃园路##号", "No. ## Taoyuan Road"}, {}},
    {"518101", {{"广东省", "Guangdong Province"}, {"深圳市", "Shenzhen City"}, {"宝安区", "Bao'an District"}, {"新安街道", "Xin'an Subdistrict"}}, {"创业一路##号", "No. ## Chuangye 1st Road"}, {"#期#栋", "Phase #, Bldg #"}},
    {"518116", {{"广东省", "Guangdong Province"}, {"深圳市", "Shenzhen City"}, {"龙岗区", "Longgang District"}, {"龙城街道", "Longcheng Subdistrict"}}, {"龙翔大道##号", "No. ## Longxiang Avenue"}, {}},

    // Province: Zhejiang (浙江省)
    // City: Hangzhou (杭州市)
    {"310006", {{"浙江省", "Zhejiang Province"}, {"杭州市", "Hangzhou City"}, {"上城区", "Shangcheng District"}, {"湖滨街道", "Hubin Subdistrict"}}, {"延安路##号", "No. ## Yan'an Road"}, {}},
    {"310002", {{"浙江省", "Zhejiang Province"}, {"杭州市", "Hangzhou City"}, {"上城区", "Shangcheng District"}, {"清波街道", "Qingbo Subdistrict"}}, {"河坊街##号", "No. ## Hefang Street"}, {}},
    {"310013", {{"浙江省", "Zhejiang Province"}, {"杭州市", "Hangzhou City"}, {"西湖区", "Xihu District"}, {"西湖街道", "Xihu Subdistrict"}}, {"龙井路##号", "No. ## Longjing Road"}, {}},
    {"310012", {{"浙江省", "Zhejiang Province"}, {"杭州市", "Hangzhou City"}, {"西湖区", "Xihu District"}, {"古荡街道", "Gudang Subdistrict"}}, {"文二西路##号", "No. ## Wen'er West Road"}, {"#幢#单元", "Bldg #, Unit #"}},
    {"310005", {{"浙江省", "Zhejiang Province"}, {"杭州市", "Hangzhou City"}, {"拱墅区", "Gongshu District"}, {"米市巷街道", "Mishixiang Subdistrict"}}, {"湖墅南路##号", "No. ## Hushu South Road"}, {}},
    {"311201", {{"浙江省", "Zhejiang Province"}, {"杭州市", "Hangzhou City"}, {"萧山区", "Xiaoshan District"}, {"城厢街道", "Chengxiang Subdistrict"}}, {"市心中路##号", "No. ## Shixin Middle Road"}, {}},
    {"310051", {{"浙江省", "Zhejiang Province"}, {"杭州市", "Hangzhou City"}, {"滨江区", "Binjiang District"}, {"西兴街道", "Xixing Subdistrict"}}, {"江南大道##号", "No. ## Jiangnan Avenue"}, {"##室", "Rm ##"}},

    // Province: Sichuan (四川省)
    // City: Chengdu (成都市)
    {"610016", {{"四川省", "Sichuan Province"}, {"成都市", "Chengdu City"}, {"锦江区", "Jinjiang District"}, {"春熙路街道", "Chunxi Road Subdistrict"}}, {"总府路##号", "No. ## Zongfu Road"}, {"#层", "Fl #"}},
    {"610016", {{"四川省", "Sichuan Province"}, {"成都市", "Chengdu City"}, {"锦江区", "Jinjiang District"}, {"盐市口街道", "Yanshikou Subdistrict"}}, {"人民南路二段##号", "No. ## Renmin South Road, Sec. 2"}, {}},
    {"610017", {{"四川省", "Sichuan Province"}, {"成都市", "Chengdu City"}, {"青羊区", "Qingyang District"}, {"草市街街道", "Caoshijie Subdistrict"}}, {"西玉龙街##号", "No. ## West Yulong Street"}, {}},
    {"610015", {{"四川省", "Sichuan Province"}, {"成都市", "Chengdu City"}, {"青羊区", "Qingyang District"}, {"宽窄巷子街道", "Kuanzhaixiangzi Subdistrict"}}, {"长顺上街##号", "No. ## Changshun Upper Street"}, {"#号院", "Courtyard #"}},
    {"610041", {{"四川省", "Sichuan Province"}, {"成都市", "Chengdu City"}, {"武侯区", "Wuhou District"}, {"玉林街道", "Yulin Subdistrict"}}, {"玉林南路##号", "No. ## Yulin South Road"}, {}},
    {"610041", {{"四川省", "Sichuan Province"}, {"成都市", "Chengdu City"}, {"武侯区", "Wuhou District"}, {"浆洗街街道", "Jiangxijie Subdistrict"}}, {"武侯祠大街##号", "No. ## Wuhouci Street"}, {}},
    {"610051", {{"四川省", "Sichuan Province"}, {"成都市", "Chengdu City"}, {"成华区", "Chenghua District"}, {"猛追湾街道", "Mengzhuiwan Subdistrict"}}, {"建设路##号", "No. ## Jianshe Road"}, {"#栋#单元", "Bldg #, Unit #"}},
    {"610041", {{"四川省", "Sichuan Province"}, {"成都市", "Chengdu City"}, {"高新技术产业开发区", "High-tech Zone"}, {"芳草街街道", "Fangcaojie Subdistrict"}}, {"神仙树南路##号", "No. ## Shenxianshu South Road"}, {}},
    {"610041", {{"四川省", "Sichuan Province"}, {"成都市", "Chengdu City"}, {"高新技术产业开发区", "High-tech Zone"}, {"桂溪街道", "Guixi Subdistrict"}}, {"天府大道北段##号", "No. ## Tianfu Avenue North Section"}, {"#区#栋", "Area #, Bldg #"}},

    // Province: Jiangsu (江苏省)
    // City: Nanjing (南京市)
    {"210018", {{"江苏省", "Jiangsu Province"}, {"南京市", "Nanjing City"}, {"玄武区", "Xuanwu District"}, {"新街口街道", "Xinjiekou Subdistrict"}}, {"中山路##号", "No. ## Zhongshan Road"}, {"##楼", "Fl ##"}},
    {"210001", {{"江苏省", "Jiangsu Province"}, {"南京市", "Nanjing City"}, {"秦淮区", "Qinhuai District"}, {"夫子庙街道", "Fuzimiao Subdistrict"}}, {"贡院西街##号", "No. ## Gongyuan West Street"}, {}},
    {"210019", {{"江苏省", "Jiangsu Province"}, {"南京市", "Nanjing City"}, {"建邺区", "Jianye District"}, {"奥体中心街道", "Olympic Center Subdistrict"}}, {"江东中路##号", "No. ## Jiangdong Middle Road"}, {}},
    {"210009", {{"江苏省", "Jiangsu Province"}, {"南京市", "Nanjing City"}, {"鼓楼区", "Gulou District"}, {"湖南路街道", "Hunan Road Subdistrict"}}, {"中央路##号", "No. ## Zhongyang Road"}, {}},
    {"211100", {{"江苏省", "Jiangsu Province"}, {"南京市", "Nanjing City"}, {"江宁区", "Jiangning District"}, {"东山街道", "Dongshan Subdistrict"}}, {"竹山路##号", "No. ## Zhushan Road"}, {"#栋###室", "Bldg #, Rm ###"}},
    // City: Suzhou (苏州市)
    {"215005", {{"江苏省", "Jiangsu Province"}, {"苏州市", "Suzhou City"}, {"姑苏区", "Gusu District"}, {"平江街道", "Pingjiang Subdistrict"}}, {"观前街##号", "No. ## Guanqian Street"}, {}},
    {"215028", {{"江苏省", "Jiangsu Province"}, {"苏州市", "Suzhou City"}, {"工业园区", "Industrial Park"}, {"娄葑街道", "Loufeng Subdistrict"}}, {"现代大道##号", "No. ## Xiandai Avenue"}, {"##楼", "Fl ##"}},
    {"215011", {{"江苏省", "Jiangsu Province"}, {"苏州市", "Suzhou City"}, {"虎丘区", "Huqiu District"}, {"狮山街道", "Shishan Subdistrict"}}, {"长江路##号", "No. ## Changjiang Road"}, {}},
    {"215300", {{"江苏省", "Jiangsu Province"}, {"苏州市", "Suzhou City"}, {"昆山市", "Kunshan City"}, {"玉山镇", "Yushan Town"}}, {"前进西路##号", "No. ## Qianjin West Road"}, {}},

    // Province: Shaanxi (陕西省)
    // City: Xi'an (西安市)
    {"710002", {{"陕西省", "Shaanxi Province"}, {"西安市", "Xi'an City"}, {"碑林区", "Beilin District"}, {"南院门街道", "Nanyuanmen Subdistrict"}}, {"南大街##号", "No. ## South Avenue"}, {}},
    {"710001", {{"陕西省", "Shaanxi Province"}, {"西安市", "Xi'an City"}, {"碑林区", "Beilin District"}, {"钟楼街道", "Zhonglou Subdistrict"}}, {"东大街##号", "No. ## East Avenue"}, {}},
    {"710061", {{"陕西省", "Shaanxi Province"}, {"西安市", "Xi'an City"}, {"雁塔区", "Yanta District"}, {"小寨路街道", "Xiaozhai Road Subdistrict"}}, {"小寨东路##号", "No. ## Xiaozhai East Road"}, {"#座##室", "Tower #, Rm ##"}},
    {"710061", {{"陕西省", "Shaanxi Province"}, {"西安市", "Xi'an City"}, {"雁塔区", "Yanta District"}, {"大雁塔街道", "Dayanta Subdistrict"}}, {"雁塔南路##号", "No. ## Yanta South Road"}, {}},
    {"710001", {{"陕西省", "Shaanxi Province"}, {"西安市", "Xi'an City"}, {"莲湖区", "Lianhu District"}, {"北院门街道", "Beiyuanmen Subdistrict"}}, {"西大街##号", "No. ## West Avenue"}, {}},

    // City: Chongqing (重庆市) - Municipality
    {"400011", {{}, {"重庆市", "Chongqing"}, {"渝中区", "Yuzhong District"}, {"解放碑街道", "Jiefangbei Subdistrict"}}, {"民族路##号", "No. ## Minzu Road"}, {}},
    {"400011", {{}, {"重庆市", "Chongqing"}, {"渝中区", "Yuzhong District"}, {"朝天门街道", "Chaotianmen Subdistrict"}}, {"长滨路##号", "No. ## Changbin Road"}, {}},
    {"400020", {{}, {"重庆市", "Chongqing"}, {"江北区", "Jiangbei District"}, {"观音桥街道", "Guanyinqiao Subdistrict"}}, {"建新北路##号", "No. ## Jianxin North Road"}, {"#号", "No #"}},
    {"400060", {{}, {"重庆市", "Chongqing"}, {"南岸区", "Nan'an District"}, {"南坪街道", "Nanping Subdistrict"}}, {"江南大道##号", "No. ## Jiangnan Avenue"}, {}},
    {"401147", {{}, {"重庆市", "Chongqing"}, {"渝北区", "Yubei District"}, {"龙塔街道", "Longta Subdistrict"}}, {"红锦大道##号", "No. ## Hongjin Avenue"}, {}},
    {"400030", {{}, {"重庆市", "Chongqing"}, {"沙坪坝区", "Shapingba District"}, {"三峡广场街道", "Sanxia Square Subdistrict"}}, {"小龙坎正街##号", "No. ## Xiaolongkan Main Street"}, {}},

    // Province: Hubei (湖北省)
    // City: Wuhan (武汉市)
    {"430014", {{"湖北省", "Hubei Province"}, {"武汉市", "Wuhan City"}, {"江岸区", "Jiang'an District"}, {"大智街道", "Dazhi Subdistrict"}}, {"中山大道##号", "No. ## Zhongshan Avenue"}, {}},
    {"430022", {{"湖北省", "Hubei Province"}, {"武汉市", "Wuhan City"}, {"江汉区", "Jianghan District"}, {"民族街道", "Minzu Subdistrict"}}, {"民生路##号", "No. ## Minsheng Road"}, {}},
    {"430071", {{"湖北省", "Hubei Province"}, {"武汉市", "Wuhan City"}, {"武昌区", "Wuchang District"}, {"中南路街道", "Zhongnan Road Subdistrict"}}, {"中南路##号", "No. ## Zhongnan Road"}, {}},
    {"430070", {{"湖北省", "Hubei Province"}, {"武汉市", "Wuhan City"}, {"洪山区", "Hongshan District"}, {"珞南街道", "Luonan Subdistrict"}}, {"珞喻路##号", "No. ## Luoyu Road"}, {}},
    {"430074", {{"湖北省", "Hubei Province"}, {"武汉市", "Wuhan City"}, {"东湖新技术开发区", "East Lake High-tech Zone"}, {"关东街道", "Guandong Subdistrict"}}, {"关山大道##号", "No. ## Guanshan Avenue"}, {"#期#栋", "Phase #, Bldg #"}},

    // City: Tianjin (天津市) - Municipality
    {"300051", {{}, {"天津市", "Tianjin"}, {"和平区", "Heping District"}, {"劝业场街道", "Quanyechang Subdistrict"}}, {"滨江道##号", "No. ## Binjiang Avenue"}, {}},
    {"300042", {{}, {"天津市", "Tianjin"}, {"和平区", "Heping District"}, {"小白楼街道", "Xiaobailou Subdistrict"}}, {"南京路##号", "No. ## Nanjing Road"}, {}},
    {"300200", {{}, {"天津市", "Tianjin"}, {"河西区", "Hexi District"}, {"大营门街道", "Dayingmen Subdistrict"}}, {"解放南路##号", "No. ## Jiefang South Road"}, {}},
    {"300100", {{}, {"天津市", "Tianjin"}, {"南开区", "Nankai District"}, {"鼓楼街道", "Gulou Subdistrict"}}, {"东马路##号", "No. ## Dongmalu"}, {}},
    {"300450", {{}, {"天津市", "Tianjin"}, {"滨海新区", "Binhai New Area"}, {"塘沽街道", "Tanggu Subdistrict"}}, {"解放路##号", "No. ## Jiefang Road"}, {}},

    // Province: Shandong (山东省)
    // City: Qingdao (青岛市)
    {"266071", {{"山东省", "Shandong Province"}, {"青岛市", "Qingdao City"}, {"市南区", "Shinan District"}, {"香港中路街道", "Hongkong Middle Road Subdistrict"}}, {"香港中路##号", "No. ## Hongkong Middle Road"}, {"##层", "Fl ##"}},
    {"266071", {{"山东省", "Shandong Province"}, {"青岛市", "Qingdao City"}, {"市南区", "Shinan District"}, {"八大关街道", "Badaguan Subdistrict"}}, {"汇泉路##号", "No. ## Huiquan Road"}, {}},
    {"266023", {{"山东省", "Shandong Province"}, {"青岛市", "Qingdao City"}, {"市北区", "Shibei District"}, {"台东街道", "Taidong Subdistrict"}}, {"台东三路##号", "No. ## Taidong 3rd Road"}, {"#号楼", "Bldg #"}},
    {"266101", {{"山东省", "Shandong Province"}, {"青岛市", "Qingdao City"}, {"崂山区", "Laoshan District"}, {"中韩街道", "Zhonghan Subdistrict"}}, {"海尔路##号", "No. ## Haier Road"}, {"#座##室", "Block #, Rm ##"}},
    {"266500", {{"山东省", "Shandong Province"}, {"青岛市", "Qingdao City"}, {"黄岛区", "Huangdao District"}, {"长江路街道", "Changjiang Road Subdistrict"}}, {"长江中路##号", "No. ## Changjiang Middle Road"}, {}},
    // City: Jinan (济南市)
    {"250011", {{"山东省", "Shandong Province"}, {"济南市", "Jinan City"}, {"历下区", "Lixia District"}, {"泉城路街道", "Quancheng Road Subdistrict"}}, {"泉城路##号", "No. ## Quancheng Road"}, {"#层", "Fl #"}},
    {"250013", {{"山东省", "Shandong Province"}, {"济南市", "Jinan City"}, {"历下区", "Lixia District"}, {"解放路街道", "Jiefang Road Subdistrict"}}, {"解放路##号", "No. ## Jiefang Road"}, {}},
    {"250001", {{"山东省", "Shandong Province"}, {"济南市", "Jinan City"}, {"市中区", "Shizhong District"}, {"大观园街道", "Daguan-yuan Subdistrict"}}, {"经四路##号", "No. ## Jingsi Road"}, {}},
    {"250022", {{"山东省", "Shandong Province"}, {"济南市", "Jinan City"}, {"槐荫区", "Huaiyin District"}, {"中大槐树街道", "Zhongdahuaishu Subdistrict"}}, {"经七路##号", "No. ## Jingqi Road"}, {"#栋#单元", "Bldg #, Unit #"}},
    {"250101", {{"山东省", "Shandong Province"}, {"济南市", "Jinan City"}, {"高新区", "High-tech Zone"}, {"舜华路街道", "Shunhua Road Subdistrict"}}, {"舜华路##号", "No. ## Shunhua Road"}, {"#区#楼", "Area #, Bldg #"}},

    // Province: Liaoning (辽宁省)
    // City: Shenyang (沈阳市)
    {"110001", {{"辽宁省", "Liaoning Province"}, {"沈阳市", "Shenyang City"}, {"和平区", "Heping District"}, {"太原街街道", "Taiyuanjie Subdistrict"}}, {"中华路##号", "No. ## Zhonghua Road"}, {"##室", "Rm ##"}},
    {"110002", {{"辽宁省", "Liaoning Province"}, {"沈阳市", "Shenyang City"}, {"和平区", "Heping District"}, {"南市场街道", "Nanshichang Subdistrict"}}, {"十一纬路##号", "No. ## Shiyiwei Road"}, {}},
    {"110011", {{"辽宁省", "Liaoning Province"}, {"沈阳市", "Shenyang City"}, {"沈河区", "Shenhe District"}, {"中街街道", "Zhongjie Subdistrict"}}, {"中街路##号", "No. ## Zhongjie Road"}, {}},
    {"110015", {{"辽宁省", "Liaoning Province"}, {"沈阳市", "Shenyang City"}, {"沈河区", "Shenhe District"}, {"五里河街道", "Wulihe Subdistrict"}}, {"青年大街##号", "No. ## Qingnian Street"}, {"#座#层", "Block #, Fl #"}},
    {"110032", {{"辽宁省", "Liaoning Province"}, {"沈阳市", "Shenyang City"}, {"皇姑区", "Huanggu District"}, {"三台子街道", "Santaizi Subdistrict"}}, {"长江街##号", "No. ## Changjiang Street"}, {}},
    {"110167", {{"辽宁省", "Liaoning Province"}, {"沈阳市", "Shenyang City"}, {"浑南区", "Hunnan District"}, {"奥体中心街道", "Olympic Center Subdistrict"}}, {"浑南四路##号", "No. ## Hunnan 4th Road"}, {}},
    // City: Dalian (大连市)
    {"116001", {{"辽宁省", "Liaoning Province"}, {"大连市", "Dalian City"}, {"中山区", "Zhongshan District"}, {"人民路街道", "Renmin Road Subdistrict"}}, {"中山路##号", "No. ## Zhongshan Road"}, {"#号楼", "Bldg #"}},
    {"116001", {{"辽宁省", "Liaoning Province"}, {"大连市", "Dalian City"}, {"中山区", "Zhongshan District"}, {"青泥洼桥街道", "Qingniwaqiao Subdistrict"}}, {"友好路##号", "No. ## Youhao Road"}, {}},
    {"116011", {{"辽宁省", "Liaoning Province"}, {"大连市", "Dalian City"}, {"西岗区", "Xigang District"}, {"北京街道", "Beijing Subdistrict"}}, {"黄河路##号", "No. ## Huanghe Road"}, {"#栋###室", "Bldg #, Rm ###"}},
    {"116023", {{"辽宁省", "Liaoning Province"}, {"大连市", "Dalian City"}, {"沙河口区", "Shahekou District"}, {"黑石礁街道", "Heishijiao Subdistrict"}}, {"中山路##号", "No. ## Zhongshan Road"}, {}},
    {"116600", {{"辽宁省", "Liaoning Province"}, {"大连市", "Dalian City"}, {"金州区", "Jinzhou District"}, {"拥政街道", "Yongzheng Subdistrict"}}, {"斯大林路##号", "No. ## Stalin Road"}, {}},

    // Province: Fujian (福建省)
    // City: Xiamen (厦门市)
    {"361001", {{"福建省", "Fujian Province"}, {"厦门市", "Xiamen City"}, {"思明区", "Siming District"}, {"鹭江街道", "Lujiang Subdistrict"}}, {"鹭江道##号", "No. ## Lujiang Road"}, {"##层", "Fl ##"}},
    {"361001", {{"福建省", "Fujian Province"}, {"厦门市", "Xiamen City"}, {"思明区", "Siming District"}, {"中华街道", "Zhonghua Subdistrict"}}, {"中山路##号", "No. ## Zhongshan Road"}, {}},
    {"361012", {{"福建省", "Fujian Province"}, {"厦门市", "Xiamen City"}, {"思明区", "Siming District"}, {"筼筜街道", "Yundang Subdistrict"}}, {"湖滨北路##号", "No. ## Hubin North Road"}, {}},
    {"361009", {{"福建省", "Fujian Province"}, {"厦门市", "Xiamen City"}, {"湖里区", "Huli District"}, {"江头街道", "Jiangtou Subdistrict"}}, {"台湾街##号", "No. ## Taiwan Street"}, {"#期#栋", "Phase #, Bldg #"}},
    {"361009", {{"福建省", "Fujian Province"}, {"厦门市", "Xiamen City"}, {"湖里区", "Huli District"}, {"金山街道", "Jinshan Subdistrict"}}, {"金尚路##号", "No. ## Jinshang Road"}, {}},
    {"361021", {{"福建省", "Fujian Province"}, {"厦门市", "Xiamen City"}, {"集美区", "Jimei District"}, {"集美街道", "Jimei Subdistrict"}}, {"银江路##号", "No. ## Yinjiang Road"}, {}},
    // City: Fuzhou (福州市)
    {"350001", {{"福建省", "Fujian Province"}, {"福州市", "Fuzhou City"}, {"鼓楼区", "Gulou District"}, {"东街街道", "Dongjie Subdistrict"}}, {"八一七北路##号", "No. ## Bayiqi North Road"}, {}},
    {"350001", {{"福建省", "Fujian Province"}, {"福州市", "Fuzhou City"}, {"鼓楼区", "Gulou District"}, {"五凤街道", "Wufeng Subdistrict"}}, {"五四路##号", "No. ## Wusi Road"}, {"#座##室", "Block #, Rm ##"}},
    {"350009", {{"福建省", "Fujian Province"}, {"福州市", "Fuzhou City"}, {"台江区", "Taijiang District"}, {"瀛洲街道", "Yingzhou Subdistrict"}}, {"台江路##号", "No. ## Taijiang Road"}, {}},
    {"350007", {{"福建省", "Fujian Province"}, {"福州市", "Fuzhou City"}, {"仓山区", "Cangshan District"}, {"仓前街道", "Cangqian Subdistrict"}}, {"麦园路##号", "No. ## Maiyuan Road"}, {"#号楼", "Bldg #"}},
    {"350011", {{"福建省", "Fujian Province"}, {"福州市", "Fuzhou City"}, {"晋安区", "Jin'an District"}, {"王庄街道", "Wangzhuang Subdistrict"}}, {"长乐中路##号", "No. ## Changle Middle Road"}, {}},

    // Province: Hunan (湖南省)
    // City: Changsha (长沙市)
    {"410001", {{"湖南省", "Hunan Province"}, {"长沙市", "Changsha City"}, {"芙蓉区", "Furong District"}, {"五里牌街道", "Wulipai Subdistrict"}}, {"五一大道##号", "No. ## Wuyi Avenue"}, {"#楼", "Fl #"}},
    {"410005", {{"湖南省", "Hunan Province"}, {"长沙市", "Changsha City"}, {"芙蓉区", "Furong District"}, {"文艺路街道", "Wenyi Road Subdistrict"}}, {"解放中路##号", "No. ## Jiefang Middle Road"}, {}},
    {"410002", {{"湖南省", "Hunan Province"}, {"长沙市", "Changsha City"}, {"天心区", "Tianxin District"}, {"坡子街街道", "Pozi Street Subdistrict"}}, {"湘江中路##号", "No. ## Xiangjiang Middle Road"}, {}},
    {"410006", {{"湖南省", "Hunan Province"}, {"长沙市", "Changsha City"}, {"岳麓区", "Yuelu District"}, {"桔子洲街道", "Juzizhou Subdistrict"}}, {"潇湘中路##号", "No. ## Xiaoxiang Middle Road"}, {}},
    {"410008", {{"湖南省", "Hunan Province"}, {"长沙市", "Changsha City"}, {"开福区", "Kaifu District"}, {"清水塘街道", "Qingshuitang Subdistrict"}}, {"营盘路##号", "No. ## Yingpan Road"}, {}},
    {"410007", {{"湖南省", "Hunan Province"}, {"长沙市", "Changsha City"}, {"雨花区", "Yuhua District"}, {"侯家塘街道", "Houjiatang Subdistrict"}}, {"劳动西路##号", "No. ## Laodong West Road"}, {"#栋#室", "Bldg #, Rm #"}},

    // Province: Henan (河南省)
    // City: Zhengzhou (郑州市)
    {"450003", {{"河南省", "Henan Province"}, {"郑州市", "Zhengzhou City"}, {"金水区", "Jinshui District"}, {"经八路街道", "Jingba Road Subdistrict"}}, {"花园路##号", "No. ## Huayuan Road"}, {"#号院#楼", "Courtyard #, Bldg #"}},
    {"450008", {{"河南省", "Henan Province"}, {"郑州市", "Zhengzhou City"}, {"金水区", "Jinshui District"}, {"未来路街道", "Weilai Road Subdistrict"}}, {"金水东路##号", "No. ## Jinshui East Road"}, {}},
    {"450000", {{"河南省", "Henan Province"}, {"郑州市", "Zhengzhou City"}, {"二七区", "Erqi District"}, {"解放路街道", "Jiefang Road Subdistrict"}}, {"二七路##号", "No. ## Erqi Road"}, {"##室", "Rm ##"}},
    {"450004", {{"河南省", "Henan Province"}, {"郑州市", "Zhengzhou City"}, {"管城回族区", "Guancheng Hui Autonomous District"}, {"西大街街道", "West Street Subdistrict"}}, {"西大街##号", "No. ## West Street"}, {}},
    {"450046", {{"河南省", "Henan Province"}, {"郑州市", "Zhengzhou City"}, {"郑东新区", "Zhengdong New Area"}, {"如意湖街道", "Ruyihu Subdistrict"}}, {"商务内环路##号", "No. ## Shangwu Inner Ring Road"}, {"##层", "Fl #"}},

    // Province: Hebei (河北省)
    // City: Shijiazhuang (石家庄市)
    {"050011", {{"河北省", "Hebei Province"}, {"石家庄市", "Shijiazhuang City"}, {"长安区", "Chang'an District"}, {"广安街道", "Guang'an Subdistrict"}}, {"中山东路##号", "No. ## Zhongshan East Road"}, {}},
    {"050011", {{"河北省", "Hebei Province"}, {"石家庄市", "Shijiazhuang City"}, {"长安区", "Chang'an District"}, {"建北街道", "Jianbei Subdistrict"}}, {"建设北大街##号", "No. ## Jianshe North Street"}, {}},
    {"050051", {{"河北省", "Hebei Province"}, {"石家庄市", "Shijiazhuang City"}, {"桥西区", "Qiaoxi District"}, {"中山路街道", "Zhongshan Road Subdistrict"}}, {"中华大街##号", "No. ## Zhonghua Street"}, {"#座##", "Block #"}},
    {"050051", {{"河北省", "Hebei Province"}, {"石家庄市", "Shijiazhuang City"}, {"新华区", "Xinhua District"}, {"合作路街道", "Hezuo Road Subdistrict"}}, {"合作路##号", "No. ## Hezuo Road"}, {}},
    {"050031", {{"河北省", "Hebei Province"}, {"石家庄市", "Shijiazhuang City"}, {"裕华区", "Yuhua District"}, {"裕兴街道", "Yuxing Subdistrict"}}, {"槐安东路##号", "No. ## Huai'an East Road"}, {"#期#栋", "Phase #, Bldg #"}},

    // Province: Heilongjiang (黑龙江省)
    // City: Harbin (哈尔滨市)
    {"150010", {{"黑龙江省", "Heilongjiang Province"}, {"哈尔滨市", "Harbin City"}, {"道里区", "Daoli District"}, {"中央大街街道", "Central Street Subdistrict"}}, {"中央大街##号", "No. ## Central Street"}, {}},
    {"150010", {{"黑龙江省", "Heilongjiang Province"}, {"哈尔滨市", "Harbin City"}, {"道里区", "Daoli District"}, {"斯大林街道", "Stalin Subdistrict"}}, {"友谊路##号", "No. ## Youyi Road"}, {}},
    {"150001", {{"黑龙江省", "Heilongjiang Province"}, {"哈尔滨市", "Harbin City"}, {"南岗区", "Nangang District"}, {"花园街道", "Huayuan Subdistrict"}}, {"红军街##号", "No. ## Hongjun Street"}, {"##室", "Rm ##"}},
    {"150080", {{"黑龙江省", "Heilongjiang Province"}, {"哈尔滨市", "Harbin City"}, {"南岗区", "Nangang District"}, {"燎原街道", "Liaoyuan Subdistrict"}}, {"学府路##号", "No. ## Xuefu Road"}, {}},
    {"150020", {{"黑龙江省", "Heilongjiang Province"}, {"哈尔滨市", "Harbin City"}, {"道外区", "Daowai District"}, {"靖宇街道", "Jingyu Subdistrict"}}, {"南二道街##号", "No. ## South 2nd Street"}, {}},
});

const auto kJapanAddressComponents = std::to_array<AddressComponents>({
    // Prefecture: Tōkyō-to (東京都)
    // City: Chiyoda-ku (千代田区)
    {"100-0005", {{"東京都", "Tōkyō-to"}, {"千代田区", "Chiyoda-ku"}}, {"丸の内#-##-##", "#-##-##, Marunouchi"}, {"丸の内ビルディング##階", "Marunouchi Building, Fl. ##"}},
    {"100-0004", {{"東京都", "Tōkyō-to"}, {"千代田区", "Chiyoda-ku"}}, {"大手町#-##-##", "#-##-##, Ōtemachi"}, {"大手町フィナンシャルシティ##F", "Ōtemachi Financial City, Fl. ##"}},
    {"101-0021", {{"東京都", "Tōkyō-to"}, {"千代田区", "Chiyoda-ku"}}, {"外神田#-##-##", "#-##-##, Sotokanda"}, {"秋葉原##ビル#階", "Akihabara ## Bldg., Fl. #"}},
    {"102-0083", {{"東京都", "Tōkyō-to"}, {"千代田区", "Chiyoda-ku"}}, {"麹町#-##-##", "#-##-##, Kōjimachi"}, {}},
    {"102-0074", {{"東京都", "Tōkyō-to"}, {"千代田区", "Chiyoda-ku"}}, {"九段南#-##-##", "#-##-##, Kudanminami"}, {}},

    // City: Chūō-ku (中央区)
    {"104-0061", {{"東京都", "Tōkyō-to"}, {"中央区", "Chūō-ku"}}, {"銀座#-##-##", "#-##-##, Ginza"}, {"銀座##ビル", "Ginza ## Bldg."}},
    {"103-0027", {{"東京都", "Tōkyō-to"}, {"中央区", "Chūō-ku"}}, {"日本橋#-##-##", "#-##-##, Nihonbashi"}, {}},
    {"104-0051", {{"東京都", "Tōkyō-to"}, {"中央区", "Chūō-ku"}}, {"佃#-##-##", "#-##-##, Tsukuda"}, {"大川端リバーシティ##号棟##室", "Okawabata River City, Bldg. ##, Rm. ##"}},
    {"104-0053", {{"東京都", "Tōkyō-to"}, {"中央区", "Chūō-ku"}}, {"晴海#-##-##", "#-##-##, Harumi"}, {"晴海アイランド##番館##号室", "Harumi Island ##, Rm. ##"}},

    // City: Minato-ku (港区)
    {"106-0032", {{"東京都", "Tōkyō-to"}, {"港区", "Minato-ku"}}, {"六本木#-##-##", "#-##-##, Roppongi"}, {"六本木ヒルズ森タワー##階", "Roppongi Hills Mori Tower, Fl. ##"}},
    {"107-0052", {{"東京都", "Tōkyō-to"}, {"港区", "Minato-ku"}}, {"赤坂#-##-##", "#-##-##, Akasaka"}, {"赤坂サカス##", "Akasaka Sacas ##"}},
    {"105-0011", {{"東京都", "Tōkyō-to"}, {"港区", "Minato-ku"}}, {"芝公園#-##-##", "#-##-##, Shibakōen"}, {}},
    {"108-0075", {{"東京都", "Tōkyō-to"}, {"港区", "Minato-ku"}}, {"港南#-##-##", "#-##-##, Kōnan"}, {"品川インターシティ##号館", "Shinagawa Intercity, Bldg. ##"}},
    {"107-0061", {{"東京都", "Tōkyō-to"}, {"港区", "Minato-ku"}}, {"北青山#-##-##", "#-##-##, Kita-Aoyama"}, {}},
    {"108-0071", {{"東京都", "Tōkyō-to"}, {"港区", "Minato-ku"}}, {"白金台#-##-##", "#-##-##, Shirokanedai"}, {"白金台##マンション", "Shirokanedai ## Mansion"}},

    // City: Shinjuku-ku (新宿区)
    {"160-0023", {{"東京都", "Tōkyō-to"}, {"新宿区", "Shinjuku-ku"}}, {"西新宿#-##-##", "#-##-##, Nishi-Shinjuku"}, {"東京都庁第一本庁舎##階", "Tokyo Metropolitan Government Bldg. No. 1, Fl. ##"}},
    {"160-0022", {{"東京都", "Tōkyō-to"}, {"新宿区", "Shinjuku-ku"}}, {"新宿#-##-##", "#-##-##, Shinjuku"}, {"新宿##ビル", "Shinjuku ## Bldg."}},
    {"162-0825", {{"東京都", "Tōkyō-to"}, {"新宿区", "Shinjuku-ku"}}, {"神楽坂#-##-##", "#-##-##, Kagurazaka"}, {}},
    {"169-0075", {{"東京都", "Tōkyō-to"}, {"新宿区", "Shinjuku-ku"}}, {"高田馬場#-##-##", "#-##-##, Takadanobaba"}, {}},

    // City: Shibuya-ku (渋谷区)
    {"150-0002", {{"東京都", "Tōkyō-to"}, {"渋谷区", "Shibuya-ku"}}, {"渋谷#-##-##", "#-##-##, Shibuya"}, {"渋谷ヒカリエ##階", "Shibuya Hikarie, Fl. ##"}},
    {"150-0043", {{"東京都", "Tōkyō-to"}, {"渋谷区", "Shibuya-ku"}}, {"道玄坂#-##-##", "#-##-##, Dōgenzaka"}, {"渋谷##ビル", "Shibuya ## Bldg."}},
    {"150-0001", {{"東京都", "Tōkyō-to"}, {"渋谷区", "Shibuya-ku"}}, {"神宮前#-##-##", "#-##-##, Jingūmae"}, {}},
    {"150-0013", {{"東京都", "Tōkyō-to"}, {"渋谷区", "Shibuya-ku"}}, {"恵比寿#-##-##", "#-##-##, Ebisu"}, {"恵比寿ガーデンプレイス##", "Yebisu Garden Place ##"}},
    {"150-0034", {{"東京都", "Tōkyō-to"}, {"渋谷区", "Shibuya-ku"}}, {"代官山町##-##", "##-##, Daikanyamachō"}, {}},

    // City: Taitō-ku (台東区)
    {"110-0007", {{"東京都", "Tōkyō-to"}, {"台東区", "Taitō-ku"}}, {"上野公園##-##", "##-##, Uenokōen"}, {}},
    {"111-0032", {{"東京都", "Tōkyō-to"}, {"台東区", "Taitō-ku"}}, {"浅草#-##-##", "#-##-##, Asakusa"}, {}},

    // City: Sumida-ku (墨田区)
    {"131-0045", {{"東京都", "Tōkyō-to"}, {"墨田区", "Sumida-ku"}}, {"押上#-##-##", "#-##-##, Oshiage"}, {}},

    // City: Musashino-shi (武蔵野市)
    {"180-0004", {{"東京都", "Tōkyō-to"}, {"武蔵野市", "Musashino-shi"}}, {"吉祥寺本町#-##-##", "#-##-##, Kichijōji Honchō"}, {}},

    // Prefecture: Kanagawa-ken (神奈川県)
    // City: Yokohama-shi (横浜市)
    {"220-0012", {{"神奈川県", "Kanagawa-ken"}, {"横浜市西区", "Yokohama-shi, Nishi-ku"}}, {"みなとみらい#-##-##", "#-##-##, Minatomirai"}, {"ランドマークタワー##階", "Landmark Tower, Fl. ##"}},
    {"231-0023", {{"神奈川県", "Kanagawa-ken"}, {"横浜市中区", "Yokohama-shi, Naka-ku"}}, {"山下町##-##", "##-##, Yamashitachō"}, {}},
    {"222-0033", {{"神奈川県", "Kanagawa-ken"}, {"横浜市港北区", "Yokohama-shi, Kōhoku-ku"}}, {"新横浜#-##-##", "#-##-##, Shin-Yokohama"}, {}},
    {"220-0005", {{"神奈川県", "Kanagawa-ken"}, {"横浜市西区", "Yokohama-shi, Nishi-ku"}}, {"南幸#-##-##", "#-##-##, Nansaiwai"}, {"横浜##ビル", "Yokohama ## Bldg."}},
    // City: Kawasaki-shi (川崎市)
    {"212-0014", {{"神奈川県", "Kanagawa-ken"}, {"川崎市幸区", "Kawasaki-shi, Saiwai-ku"}}, {"大宮町##-##", "##-##, Ōmiyachō"}, {}},
    // City: Kamakura-shi (鎌倉市)
    {"248-0006", {{"神奈川県", "Kanagawa-ken"}, {"鎌倉市", "Kamakura-shi"}}, {"小町#-##-##", "#-##-##, Komachi"}, {}},

    // Prefecture: Ōsaka-fu (大阪府)
    // City: Ōsaka-shi (大阪市)
    {"530-0001", {{"大阪府", "Ōsaka-fu"}, {"大阪市北区", "Ōsaka-shi, Kita-ku"}}, {"梅田#-##-##", "#-##-##, Umeda"}, {"梅田スカイビル##階", "Umeda Sky Bldg., Fl. ##"}},
    {"542-0076", {{"大阪府", "Ōsaka-fu"}, {"大阪市中央区", "Ōsaka-shi, Chūō-ku"}}, {"難波#-##-##", "#-##-##, Namba"}, {"なんばパークス##階", "Namba Parks, Fl. ##"}},
    {"542-0085", {{"大阪府", "Ōsaka-fu"}, {"大阪市中央区", "Ōsaka-shi, Chūō-ku"}}, {"心斎橋筋#-##-##", "#-##-##, Shinsaibashisuji"}, {}},
    {"542-0071", {{"大阪府", "Ōsaka-fu"}, {"大阪市中央区", "Ōsaka-shi, Chūō-ku"}}, {"道頓堀#-##-##", "#-##-##, Dōtonbori"}, {}},
    {"554-0031", {{"大阪府", "Ōsaka-fu"}, {"大阪市此花区", "Ōsaka-shi, Konohana-ku"}}, {"桜島#-##-##", "#-##-##, Sakurajima"}, {}},
    {"545-0052", {{"大阪府", "Ōsaka-fu"}, {"大阪市阿倍野区", "Ōsaka-shi, Abeno-ku"}}, {"阿倍野筋#-##-##", "#-##-##, Abenosuji"}, {"あべのハルカス##階", "Abeno Harukas, Fl. ##"}},
    {"556-0002", {{"大阪府", "Ōsaka-fu"}, {"大阪市浪速区", "Ōsaka-shi, Naniwa-ku"}}, {"恵美須東#-##-##", "#-##-##, Ebisuhigashi"}, {}},
    {"533-0033", {{"大阪府", "Ōsaka-fu"}, {"大阪市東淀川区", "Ōsaka-shi, Higashiyodogawa-ku"}}, {"東中島#-##-##", "#-##-##, Higashinakajima"}, {}},

    // City: Sakai-shi (堺市)
    {"590-0078", {{"大阪府", "Ōsaka-fu"}, {"堺市堺区", "Sakai-shi, Sakai-ku"}}, {"南瓦町#-##", "#-##, Minamikawaramachi"}, {}},

    // City: Suita-shi (吹田市)
    {"565-0826", {{"大阪府", "Ōsaka-fu"}, {"吹田市", "Suita-shi"}}, {"千里万博公園##-##", "##-##, Senribanpakukōen"}, {}},

    // Prefecture: Kyōto-fu (京都府)
    // City: Kyōto-shi (京都市)
    {"600-8001", {{"京都府", "Kyōto-fu"}, {"京都市下京区", "Kyōto-shi, Shimogyō-ku"}}, {"四条通##", "##, Shijō-dōri"}, {}},
    {"604-8001", {{"京都府", "Kyōto-fu"}, {"京都市中京区", "Kyōto-shi, Nakagyō-ku"}}, {"木屋町通##", "##, Kiyamachi-dōri"}, {}},
    {"605-0074", {{"京都府", "Kyōto-fu"}, {"京都市東山区", "Kyōto-shi, Higashiyama-ku"}}, {"祇園町南側##", "##, Gionmachi Minamigawa"}, {}},
    {"600-8216", {{"京都府", "Kyōto-fu"}, {"京都市下京区", "Kyōto-shi, Shimogyō-ku"}}, {"東塩小路町##", "##, Higashishiokōjichō"}, {}},
    {"602-0872", {{"京都府", "Kyōto-fu"}, {"京都市上京区", "Kyōto-shi, Kamigyō-ku"}}, {"河原町通##", "##, Kawaramachi-dōri"}, {}},
    {"616-8385", {{"京都府", "Kyōto-fu"}, {"京都市右京区", "Kyōto-shi, Ukyō-ku"}}, {"嵯峨天龍寺芒ノ馬場町##", "##, Sagatenryūji Susukinobabachō"}, {}},
    {"612-8001", {{"京都府", "Kyōto-fu"}, {"京都市伏見区", "Kyōto-shi, Fushimi-ku"}}, {"桃山町##", "##, Momoyamachō"}, {}},

    // Prefecture: Aichi-ken (愛知県)
    // City: Nagoya-shi (名古屋市)
    {"450-0002", {{"愛知県", "Aichi-ken"}, {"名古屋市中村区", "Nagoya-shi, Nakamura-ku"}}, {"名駅#-##-##", "#-##-##, Meieki"}, {"JRセントラルタワーズ##階", "JR Central Towers, Fl. ##"}},
    {"460-0008", {{"愛知県", "Aichi-ken"}, {"名古屋市中区", "Nagoya-shi, Naka-ku"}}, {"栄#-##-##", "#-##-##, Sakae"}, {"##ビル", "## Bldg."}},
    {"460-0011", {{"愛知県", "Aichi-ken"}, {"名古屋市中区", "Nagoya-shi, Naka-ku"}}, {"大須#-##-##", "#-##-##, Ōsu"}, {}},
    {"455-0033", {{"愛知県", "Aichi-ken"}, {"名古屋市港区", "Nagoya-shi, Minato-ku"}}, {"港町#-##", "#-##, Minatomachi"}, {}},
    {"456-0843", {{"愛知県", "Aichi-ken"}, {"名古屋市熱田区", "Nagoya-shi, Atsuta-ku"}}, {"神宮#-##-##", "#-##-##, Jingū"}, {}},

    // Prefecture: Hokkaidō (北海道)
    // City: Sapporo-shi (札幌市)
    {"060-0004", {{"北海道", "Hokkaidō"}, {"札幌市中央区", "Sapporo-shi, Chūō-ku"}}, {"北四条西#-##", "#-##, Kita-4-jō-Nishi"}, {}},
    {"064-0941", {{"北海道", "Hokkaidō"}, {"札幌市中央区", "Sapporo-shi, Chūō-ku"}}, {"旭ケ丘#-##-##", "#-##-##, Asahigaoka"}, {}},
    {"060-0042", {{"北海道", "Hokkaidō"}, {"札幌市中央区", "Sapporo-shi, Chūō-ku"}}, {"大通西#-##", "#-##, Ōdōri-Nishi"}, {}},
    {"064-0805", {{"北海道", "Hokkaidō"}, {"札幌市中央区", "Sapporo-shi, Chūō-ku"}}, {"南五条西#-##", "#-##, Minami-5-jō-Nishi"}, {}},
    {"062-0045", {{"北海道", "Hokkaidō"}, {"札幌市豊平区", "Sapporo-shi, Toyohira-ku"}}, {"羊ケ丘#番地", "Banchi #, Hitsujigaoka"}, {}},
    {"001-0010", {{"北海道", "Hokkaidō"}, {"札幌市北区", "Sapporo-shi, Kita-ku"}}, {"北十条西#-##", "#-##, Kita-10-jō-Nishi"}, {"##マンション##号", "## Mansion, Rm. ##"}},

    // City: Hakodate-shi (函館市)
    {"040-0053", {{"北海道", "Hokkaidō"}, {"函館市", "Hakodate-shi"}}, {"末広町##-##", "#-##, Suehirochō"}, {}},

    // City: Otaru-shi (小樽市)
    {"047-0027", {{"北海道", "Hokkaidō"}, {"小樽市", "Otaru-shi"}}, {"堺町#-##", "#-##, Sakaimachi"}, {}},

    // Prefecture: Fukuoka-ken (福岡県)
    // City: Fukuoka-shi (福岡市)
    {"810-0001", {{"福岡県", "Fukuoka-ken"}, {"福岡市中央区", "Fukuoka-shi, Chūō-ku"}}, {"天神#-##-##", "#-##-##, Tenjin"}, {"天神##ビル", "Tenjin ## Bldg."}},
    {"812-0011", {{"福岡県", "Fukuoka-ken"}, {"福岡市博多区", "Fukuoka-shi, Hakata-ku"}}, {"博多駅前#-##-##", "#-##-##, Hakataekimae"}, {"##ビル##階", "## Bldg., Fl. ##"}},
    {"812-0029", {{"福岡県", "Fukuoka-ken"}, {"福岡市博多区", "Fukuoka-shi, Hakata-ku"}}, {"古門戸町##-##", "##-##, Komondomachi"}, {}},
    {"814-0001", {{"福岡県", "Fukuoka-ken"}, {"福岡市早良区", "Fukuoka-shi, Sawara-ku"}}, {"百道浜#-##-##", "#-##-##, Momochihama"}, {}},
    {"819-0001", {{"福岡県", "Fukuoka-ken"}, {"福岡市西区", "Fukuoka-shi, Nishi-ku"}}, {"小戸#-##-##", "#-##-##, Odo"}, {}},

    // City: Kitakyūshū-shi (北九州市)
    {"802-0006", {{"福岡県", "Fukuoka-ken"}, {"北九州市小倉北区", "Kitakyūshū-shi, Kokurakita-ku"}}, {"魚町#-##-##", "#-##-##, Uomachi"}, {}},
    {"803-0814", {{"福岡県", "Fukuoka-ken"}, {"北九州市小倉北区", "Kitakyūshū-shi, Kokurakita-ku"}}, {"大手町##-##", "##-##, Ōtemachi"}, {}},

    // Prefecture: Hyōgo-ken (兵庫県)
    // City: Kōbe-shi (神戸市)
    {"650-0001", {{"兵庫県", "Hyōgo-ken"}, {"神戸市中央区", "Kōbe-shi, Chūō-ku"}}, {"加納町#-##-##", "#-##-##, Kanōchō"}, {}},
    {"650-0022", {{"兵庫県", "Hyōgo-ken"}, {"神戸市中央区", "Kōbe-shi, Chūō-ku"}}, {"元町通#-##-##", "#-##-##, Motomachidōri"}, {}},
    {"650-0044", {{"兵庫県", "Hyōgo-ken"}, {"神戸市中央区", "Kōbe-shi, Chūō-ku"}}, {"東川崎町#-##-##", "#-##-##, Higashikawasakichō"}, {}},
    {"657-0013", {{"兵庫県", "Hyōgo-ken"}, {"神戸市灘区", "Kōbe-shi, Nada-ku"}}, {"六甲台町#-##", "#-##, Rokkōdaichō"}, {}},

    // City: Himeji-shi (姫路市)
    {"670-0012", {{"兵庫県", "Hyōgo-ken"}, {"姫路市", "Himeji-shi"}}, {"本町##番地", "Banchi ##, Honmachi"}, {}},

    // Prefecture: Hiroshima-ken (広島県)
    // City: Hiroshima-shi (広島市)
    {"730-0035", {{"広島県", "Hiroshima-ken"}, {"広島市中区", "Hiroshima-shi, Naka-ku"}}, {"本通#-##", "#-##, Hondōri"}, {}},
    {"730-0011", {{"広島県", "Hiroshima-ken"}, {"広島市中区", "Hiroshima-shi, Naka-ku"}}, {"基町##-##", "##-##, Motomachi"}, {}},
    {"732-0052", {{"広島県", "Hiroshima-ken"}, {"広島市東区", "Hiroshima-shi, Higashi-ku"}}, {"光町#-##-##", "#-##-##, Hikari-machi"}, {}},

    // Prefecture: Saitama-ken (埼玉県)
    // City: Saitama-shi (さいたま市)
    {"330-0063", {{"埼玉県", "Saitama-ken"}, {"さいたま市浦和区", "Saitama-shi, Urawa-ku"}}, {"高砂#-##-##", "#-##-##, Takasago"}, {}},
    {"330-0854", {{"埼玉県", "Saitama-ken"}, {"さいたま市大宮区", "Saitama-shi, Ōmiya-ku"}}, {"桜木町#-##-##", "#-##-##, Sakuragichō"}, {}},

    // Prefecture: Chiba-ken (千葉県)
    // City: Chiba-shi (千葉市)
    {"260-0028", {{"千葉県", "Chiba-ken"}, {"千葉市中央区", "Chiba-shi, Chūō-ku"}}, {"新町##-##", "##-##, Shimmachi"}, {}},
    {"261-0023", {{"千葉県", "Chiba-ken"}, {"千葉市美浜区", "Chiba-shi, Mihama-ku"}}, {"中瀬#-##", "#-##, Nakase"}, {}},
    // City: Urayasu-shi (浦安市)
    {"279-0031", {{"千葉県", "Chiba-ken"}, {"浦安市", "Urayasu-shi"}}, {"舞浜#-##", "#-##, Maihama"}, {}},

    // Prefecture: Okinawa-ken (沖縄県)
    // City: Naha-shi (那覇市)
    {"900-0015", {{"沖縄県", "Okinawa-ken"}, {"那覇市", "Naha-shi"}}, {"久茂地#-##-##", "#-##-##, Kumoji"}, {}},
    {"900-0013", {{"沖縄県", "Okinawa-ken"}, {"那覇市", "Naha-shi"}}, {"牧志#-##-##", "#-##-##, Makishi"}, {}},
    {"903-0815", {{"沖縄県", "Okinawa-ken"}, {"那覇市", "Naha-shi"}}, {"首里金城町#-##", "#-##, Shurikinjocho"}, {}},

    // Prefecture: Miyagi-ken (宮城県)
    // City: Sendai-shi (仙台市)
    {"980-0811", {{"宮城県", "Miyagi-ken"}, {"仙台市青葉区", "Sendai-shi, Aoba-ku"}}, {"一番町#-##-##", "#-##-##, Ichibanchō"}, {"仙台##ビルヂング", "Sendai ## Building"}},
    {"980-0803", {{"宮城県", "Miyagi-ken"}, {"仙台市青葉区", "Sendai-shi, Aoba-ku"}}, {"国分町#-##-##", "#-##-##, Kokubunchō"}, {}},
    {"980-0021", {{"宮城県", "Miyagi-ken"}, {"仙台市青葉区", "Sendai-shi, Aoba-ku"}}, {"中央#-##-##", "#-##-##, Chūō"}, {"##ビル#階", "## Bldg., Fl. #"}},
    {"983-0852", {{"宮城県", "Miyagi-ken"}, {"仙台市宮城野区", "Sendai-shi, Miyagino-ku"}}, {"榴岡#-##-##", "#-##-##, Tsutsujigaoka"}, {}},
    {"982-0831", {{"宮城県", "Miyagi-ken"}, {"仙台市太白区", "Sendai-shi, Taihaku-ku"}}, {"長町#-##-##", "#-##-##, Nagamachi"}, {}},
    {"981-3133", {{"宮城県", "Miyagi-ken"}, {"仙台市泉区", "Sendai-shi, Izumi-ku"}}, {"泉中央#-##-##", "#-##-##, Izumi-Chūō"}, {}},

    // Prefecture: Ishikawa-ken (石川県)
    // City: Kanazawa-shi (金沢市)
    {"920-0852", {{"石川県", "Ishikawa-ken"}, {"金沢市", "Kanazawa-shi"}}, {"此花町##-##", "##-##, Konohanamachi"}, {}},
    {"920-0961", {{"石川県", "Ishikawa-ken"}, {"金沢市", "Kanazawa-shi"}}, {"香林坊#-##-##", "#-##-##, Kōrinbō"}, {"##ビル", "## Bldg."}},
    {"920-0981", {{"石川県", "Ishikawa-ken"}, {"金沢市", "Kanazawa-shi"}}, {"片町#-##-##", "#-##-##, Katamachi"}, {}},
    {"920-0931", {{"石川県", "Ishikawa-ken"}, {"金沢市", "Kanazawa-shi"}}, {"兼六町#-##", "#-##, Kenrokumachi"}, {}},
    {"920-0831", {{"石川県", "Ishikawa-ken"}, {"金沢市", "Kanazawa-shi"}}, {"東山#-##-##", "#-##-##, Higashiyama"}, {}},

    // Prefecture: Shizuoka-ken (静岡県)
    // City: Shizuoka-shi (静岡市)
    {"420-0857", {{"静岡県", "Shizuoka-ken"}, {"静岡市葵区", "Shizuoka-shi, Aoi-ku"}}, {"御幸町##-##", "##-##, Miyukichō"}, {}},
    {"420-0858", {{"静岡県", "Shizuoka-ken"}, {"静岡市葵区", "Shizuoka-shi, Aoi-ku"}}, {"伝馬町#-##-##", "#-##-##, Temmachō"}, {}},
    {"422-8067", {{"静岡県", "Shizuoka-ken"}, {"静岡市駿河区", "Shizuoka-shi, Suruga-ku"}}, {"南町##-##", "##-##, Minamichō"}, {"##ビル#階", "## Bldg., Fl. #"}},
    {"424-0816", {{"静岡県", "Shizuoka-ken"}, {"静岡市清水区", "Shizuoka-shi, Shimizu-ku"}}, {"真砂町#-##-##", "#-##-##, Masagochō"}, {}},
    // City: Hamamatsu-shi (浜松市)
    {"430-0933", {{"静岡県", "Shizuoka-ken"}, {"浜松市中央区", "Hamamatsu-shi, Chūō-ku"}}, {"鍛冶町##-##", "##-##, Kajimachi"}, {}},
    {"430-0926", {{"静岡県", "Shizuoka-ken"}, {"浜松市中央区", "Hamamatsu-shi, Chūō-ku"}}, {"砂山町##-##", "##-##, Sunayamachō"}, {}},

    // Prefecture: Okayama-ken (岡山県)
    // City: Okayama-shi (岡山市)
    {"700-0024", {{"岡山県", "Okayama-ken"}, {"岡山市北区", "Okayama-shi, Kita-ku"}}, {"駅元町##-##", "##-##, Ekimotomachi"}, {"##ビル", "## Bldg."}},
    {"700-0822", {{"岡山県", "Okayama-ken"}, {"岡山市北区", "Okayama-shi, Kita-ku"}}, {"表町#-##-##", "#-##-##, Omotechō"}, {}},
    {"700-0821", {{"岡山県", "Okayama-ken"}, {"岡山市北区", "Okayama-shi, Kita-ku"}}, {"中山下#-##-##", "#-##-##, Nakasange"}, {}},
    {"703-8256", {{"岡山県", "Okayama-ken"}, {"岡山市中区", "Okayama-shi, Naka-ku"}}, {"浜#-##-##", "#-##-##, Hama"}, {}},
    // City: Kurashiki-shi (倉敷市)
    {"710-0055", {{"岡山県", "Okayama-ken"}, {"倉敷市", "Kurashiki-shi"}}, {"阿知#-##-##", "#-##-##, Achi"}, {"##マンション", "## Mansion"}},
    {"710-0824", {{"岡山県", "Okayama-ken"}, {"倉敷市", "Kurashiki-shi"}}, {"白楽町##", "##, Shirokumachi"}, {}},

    // Prefecture: Niigata-ken (新潟県)
    // City: Niigata-shi (新潟市)
    {"950-0901", {{"新潟県", "Niigata-ken"}, {"新潟市中央区", "Niigata-shi, Chūō-ku"}}, {"弁天#-##-##", "#-##-##, Benten"}, {}},
    {"951-8063", {{"新潟県", "Niigata-ken"}, {"新潟市中央区", "Niigata-shi, Chūō-ku"}}, {"古町通#番町##", "#-banchō, ##, Furumachi-dōri"}, {"##ビル", "## Bldg."}},
    {"950-0086", {{"新潟県", "Niigata-ken"}, {"新潟市中央区", "Niigata-shi, Chūō-ku"}}, {"花園#-##-##", "#-##-##, Hanazono"}, {}},

    // Prefecture: Nagano-ken (長野県)
    // City: Nagano-shi (長野市)
    {"380-0823", {{"長野県", "Nagano-ken"}, {"長野市", "Nagano-shi"}}, {"南千歳#-##-##", "#-##-##, Minami-chitose"}, {}},
    {"380-0834", {{"長野県", "Nagano-ken"}, {"長野市", "Nagano-shi"}}, {"大字鶴賀問御所町##", "##, Ōaza-Tsuruga-Tongozechō"}, {}},
    // City: Matsumoto-shi (松本市)
    {"390-0811", {{"長野県", "Nagano-ken"}, {"松本市", "Matsumoto-shi"}}, {"中央#-##-##", "#-##-##, Chūō"}, {}},
    {"390-0874", {{"長野県", "Nagano-ken"}, {"松本市", "Matsumoto-shi"}}, {"大手#-##-##", "#-##-##, Ōte"}, {"##ビル", "## Bldg."}},
    // City: Karuizawa-machi (軽井沢町)
    {"389-0102", {{"長野県", "Nagano-ken"}, {"北佐久郡軽井沢町", "Kitasaku-gun, Karuizawa-machi"}}, {"軽井沢##", "##, Karuizawa"}, {}},

    // Prefecture: Gumma-ken (群馬県)
    // City: Takasaki-shi (高崎市)
    {"370-0849", {{"群馬県", "Gumma-ken"}, {"高崎市", "Takasaki-shi"}}, {"八島町##-##", "##-##, Yashimachō"}, {}},
    // City: Maebashi-shi (前橋市)
    {"371-0023", {{"群馬県", "Gumma-ken"}, {"前橋市", "Maebashi-shi"}}, {"本町#-##-##", "#-##-##, Honchō"}, {}},

    // Prefecture: Tochigi-ken (栃木県)
    // City: Utsunomiya-shi (宇都宮市)
    {"321-0964", {{"栃木県", "Tochigi-ken"}, {"宇都宮市", "Utsunomiya-shi"}}, {"駅前通り#-##-##", "#-##-##, Ekimae-dōri"}, {}},
    // City: Nikkō-shi (日光市)
    {"321-1431", {{"栃木県", "Tochigi-ken"}, {"日光市", "Nikkō-shi"}}, {"山内##", "##, Sannai"}, {}},

    // Prefecture: Ibaraki-ken (茨城県)
    // City: Mito-shi (水戸市)
    {"310-0015", {{"茨城県", "Ibaraki-ken"}, {"水戸市", "Mito-shi"}}, {"宮町#-##-##", "#-##-##, Miyamachi"}, {}},
    // City: Tsukuba-shi (つくば市)
    {"305-0032", {{"茨城県", "Ibaraki-ken"}, {"つくば市", "Tsukuba-shi"}}, {"竹園#-##-##", "#-##-##, Takezono"}, {}},

    // More Satellite Cities
    // Saitama-ken
    {"350-1122", {{"埼玉県", "Saitama-ken"}, {"川越市", "Kawagoe-shi"}}, {"脇田町##-##", "##-##, Wakitachō"}, {}},
    // Chiba-ken
    {"277-0842", {{"千葉県", "Chiba-ken"}, {"柏市", "Kashiwa-shi"}}, {"末広町#-##-##", "#-##-##, Suehirochō"}, {}},
    {"273-0005", {{"千葉県", "Chiba-ken"}, {"船橋市", "Funabashi-shi"}}, {"本町#-##-##", "#-##-##, Honchō"}, {}},
    // Tōkyō-to (Western Suburbs)
    {"190-0012", {{"東京都", "Tōkyō-to"}, {"立川市", "Tachikawa-shi"}}, {"曙町#-##-##", "#-##-##, Akebonochō"}, {}},
    {"192-0831", {{"東京都", "Tōkyō-to"}, {"八王子市", "Hachiōji-shi"}}, {"子安町#-##-##", "#-##-##, Koyasumachi"}, {}},
    {"201-0004", {{"東京都", "Tōkyō-to"}, {"狛江市", "Komae-shi"}}, {"岩戸北#-##-##", "#-##-##, Iwadokita"}, {}},

    // More Kansai Cities
    // Nara-ken
    {"630-8216", {{"奈良県", "Nara-ken"}, {"奈良市", "Nara-shi"}}, {"東向中町##", "##, Higashimuki Nakamachi"}, {}},
    // Wakayama-ken
    {"640-8331", {{"和歌山県", "Wakayama-ken"}, {"和歌山市", "Wakayama-shi"}}, {"美園町#-##-##", "#-##-##, Misonochō"}, {}},

    // More Chūgoku Region
    // Tottori-ken
    {"680-0835", {{"鳥取県", "Tottori-ken"}, {"鳥取市", "Tottori-shi"}}, {"東品治町##", "##, Higashi-Honjichō"}, {}},
    // Shimane-ken
    {"690-0003", {{"島根県", "Shimane-ken"}, {"松江市", "Matsue-shi"}}, {"朝日町##-##", "##-##, Asahimachi"}, {}},
    // Yamaguchi-ken
    {"750-0025", {{"山口県", "Yamaguchi-ken"}, {"下関市", "Shimonoseki-shi"}}, {"竹崎町#-##-##", "#-##-##, Takezakichō"}, {}},

    // Shikoku Island
    // Kagawa-ken
    {"760-0028", {{"香川県", "Kagawa-ken"}, {"高松市", "Takamatsu-shi"}}, {"鍛冶屋町#-##", "#-##, Kajiyamachi"}, {}},
    // Ehime-ken
    {"790-0004", {{"愛媛県", "Ehime-ken"}, {"松山市", "Matsuyama-shi"}}, {"大街道#-##-##", "#-##-##, Ōkaidō"}, {}},
    // Kōchi-ken
    {"780-0834", {{"高知県", "Kōchi-ken"}, {"高知市", "Kōchi-shi"}}, {"堺町#-##", "#-##, Sakaimachi"}, {}},
    // Tokushima-ken
    {"770-0831", {{"徳島県", "Tokushima-ken"}, {"徳島市", "Tokushima-shi"}}, {"寺島本町西#-##-##", "#-##-##, Terashimahonchōnishi"}, {}},

    // Kyushu Island - more cities
    // Kumamoto-ken
    {"860-0807", {{"熊本県", "Kumamoto-ken"}, {"熊本市中央区", "Kumamoto-shi, Chūō-ku"}}, {"下通#-##-##", "#-##-##, Shimotōri"}, {}},
    // Kagoshima-ken
    {"890-0053", {{"鹿児島県", "Kagoshima-ken"}, {"鹿児島市", "Kagoshima-shi"}}, {"中央町#-##", "#-##, Chūōchō"}, {}},
    // Nagasaki-ken
    {"850-0841", {{"長崎県", "Nagasaki-ken"}, {"長崎市", "Nagasaki-shi"}}, {"銅座町##-##", "##-##, Dōzamachi"}, {}},
    // Ōita-ken
    {"870-0921", {{"大分県", "Ōita-ken"}, {"大分市", "Ōita-shi"}}, {"萩原#-##-##", "#-##-##, Hagiwara"}, {}},

});
// clang-format on

}  // namespace faker::location

#endif  // FAKER_LOCATION_DATA_H
