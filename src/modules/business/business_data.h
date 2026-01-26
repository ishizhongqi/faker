// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file business_data.h

#ifndef FAKER_BUSINESS_DATA_H
#define FAKER_BUSINESS_DATA_H

#include <array>
#include <span>
#include <string_view>
#include <unordered_map>

#include "faker/types/bilingual.h"
#include "faker/types/enums.h"

namespace faker::business {

enum class Industries {
    Catering,
    Consulting,
    Electronics,
    Engineering,
    FinancialServices,
    Industrial,
    InformationTechnology,
    LandedProperty,
    Logistic,
    Manufacturing,
    Pharmaceutical,
    Telecommunication,
    Trading,
};

constexpr auto kEnglishCompanySuffixes = std::to_array<BilingualView>({
    {"Company Limited", "Company Limited"},
    {"Limited", "Limited"},
    {"Corporation", "Corporation"},
    {"Inc.", "Inc."},
    {"LLC", "LLC"},
});

constexpr auto kSimplifiedChineseCompanySuffixes = std::to_array<BilingualView>({
    {"有限公司", "Company Limited"},
    {"股份有限公司", "Corporation"},
    {"有限责任公司", "LLC"},
});

constexpr auto kTraditionalChineseCompanySuffixes = std::to_array<BilingualView>({
    {"有限公司", "Company Limited"},
    {"股份有限公司", "Corporation"},
    {"有限责任公司", "LLC"},
});

constexpr auto kJapaneseCompanySuffixes = std::to_array<BilingualView>({
    {"株式会社", "Corporation"},
});

constexpr auto kEnglishLastNameSuffixes = std::to_array<BilingualView>({
    {"", ""},
    {" Brothers", " Brothers"},
});

constexpr auto kSimplifiedChineseLastNameSuffixes = std::to_array<BilingualView>({
    {"", ""},
    {"氏", " Shi"},
    {"氏兄弟", " Brothers"},
});

constexpr auto kTraditionalChineseLastNameSuffixes = std::to_array<BilingualView>({
    {"", ""},
    {"記", " Kee"},
    {"氏兄弟", " Brothers"},
});

constexpr auto kJapaneseLastNameSuffixes = std::to_array<BilingualView>({
    {"", ""},
    {"商会", " Shokai"},
    {"商店", " Shoten"},
});

const std::unordered_map<Languages, std::unordered_map<Industries, std::string_view>> kIndustries = {
    {Languages::English,
     {
         {Industries::Catering, "Catering industry"},
         {Industries::Consulting, "Consulting industry"},
         {Industries::Electronics, "Electronics industry"},
         {Industries::Engineering, "Engineering industry"},
         {Industries::FinancialServices, "Financial services industry"},
         {Industries::Industrial, "Industrial industry"},
         {Industries::InformationTechnology, "Information technology industry"},
         {Industries::LandedProperty, "Landed property industry"},
         {Industries::Logistic, "Logistic industry"},
         {Industries::Manufacturing, "Manufacturing industry"},
         {Industries::Pharmaceutical, "Pharmaceutical industry"},
         {Industries::Telecommunication, "Telecommunication industry"},
         {Industries::Trading, "Trading industry"},
     }},
    {Languages::SimplifiedChinese,
     {
         {Industries::Catering, "餐饮业"},
         {Industries::Consulting, "咨询业"},
         {Industries::Electronics, "电子行业"},
         {Industries::Engineering, "工程业"},
         {Industries::FinancialServices, "金融服务业"},
         {Industries::Industrial, "工业"},
         {Industries::InformationTechnology, "信息技术业"},
         {Industries::LandedProperty, "房地产业"},
         {Industries::Logistic, "物流业"},
         {Industries::Manufacturing, "制造业"},
         {Industries::Pharmaceutical, "制药业"},
         {Industries::Telecommunication, "电信业"},
         {Industries::Trading, "贸易行业"},
     }},
    {Languages::TraditionalChinese,
     {
         {Industries::Catering, "餐飲業"},
         {Industries::Consulting, "諮詢業"},
         {Industries::Electronics, "電子業"},
         {Industries::Engineering, "工程業"},
         {Industries::FinancialServices, "金融服務業"},
         {Industries::Industrial, "工業"},
         {Industries::InformationTechnology, "信息技術業"},
         {Industries::LandedProperty, "房地產業"},
         {Industries::Logistic, "物流業"},
         {Industries::Manufacturing, "製造業"},
         {Industries::Pharmaceutical, "製藥業"},
         {Industries::Telecommunication, "電訊業"},
         {Industries::Trading, "貿易行業"},
     }},
    {Languages::Japanese,
     {
         {Industries::Catering, "ケータリング業界"},
         {Industries::Consulting, "コンサルティング業界"},
         {Industries::Electronics, "エレクトロニクス産業"},
         {Industries::Engineering, "エンジニアリング業界"},
         {Industries::FinancialServices, "金融サービス業界"},
         {Industries::Industrial, "産業"},
         {Industries::InformationTechnology, "情報技術産業"},
         {Industries::LandedProperty, "不動産業界"},
         {Industries::Logistic, "物流業界"},
         {Industries::Manufacturing, "製造業界"},
         {Industries::Pharmaceutical, "製薬業界"},
         {Industries::Telecommunication, "電気通信産業"},
         {Industries::Trading, "貿易業界"},
     }},
};

constexpr auto kEnglishCateringBusinessWords = std::to_array<BilingualView>({
    {"Catering", "Catering"},
    {"Food Service", "Food Service"},
});

constexpr auto kSimplifiedChineseCateringBusinessWords = std::to_array<BilingualView>({
    {"餐饮", "Catering"},
    {"食品服务", "Food Service"},
});

constexpr auto kTraditionalChineseCateringBusinessWords = std::to_array<BilingualView>({
    {"餐飲", "Catering"},
    {"食品服務", "Food Service"},
});

constexpr auto kJapaneseCateringBusinessWords = std::to_array<BilingualView>({
    {"ケータリング", "Catering"},
    {"食品サービス", "Food Service"},
});

constexpr auto kEnglishConsultingBusinessWords = std::to_array<BilingualView>({
    {"Consulting", "Consulting"},
    {"Advisory", "Advisory"},
});

constexpr auto kSimplifiedChineseConsultingBusinessWords = std::to_array<BilingualView>({
    {"咨询", "Consulting"},
    {"顾问", "Advisory"},
});

constexpr auto kTraditionalChineseConsultingBusinessWords = std::to_array<BilingualView>({
    {"諮詢", "Consulting"},
    {"顧問", "Advisory"},
});

constexpr auto kJapaneseConsultingBusinessWords = std::to_array<BilingualView>({
    {"コンサルティング", "Consulting"},
    {"顧問", "Advisory"},
});

constexpr auto kEnglishElectronicsBusinessWords = std::to_array<BilingualView>({
    {"Electronics", "Electronics"},
    {"Semiconductor", "Semiconductor"},
    {"Appliance", "Appliance"},
});

constexpr auto kSimplifiedChineseElectronicsBusinessWords = std::to_array<BilingualView>({
    {"电子", "Electronics"},
    {"半导体", "Semiconductor"},
    {"家电", "Appliance"},
});

constexpr auto kTraditionalChineseElectronicsBusinessWords = std::to_array<BilingualView>({
    {"電子", "Electronics"},
    {"半導體", "Semiconductor"},
    {"家電", "Appliance"},
});

constexpr auto kJapaneseElectronicsBusinessWords = std::to_array<BilingualView>({
    {"エレクトロニクス", "Electronics"},
    {"半導体", "Semiconductor"},
    {"家電", "Appliance"},
});

constexpr auto kEnglishEngineeringBusinessWords = std::to_array<BilingualView>({
    {"Engineering", "Engineering"},
    {"Construction", "Construction"},
});

constexpr auto kSimplifiedChineseEngineeringBusinessWords = std::to_array<BilingualView>({
    {"工程", "Engineering"},
    {"建设", "Construction"},
});

constexpr auto kTraditionalChineseEngineeringBusinessWords = std::to_array<BilingualView>({
    {"工程", "Engineering"},
    {"建設", "Construction"},
});

constexpr auto kJapaneseEngineeringBusinessWords = std::to_array<BilingualView>({
    {"エンジニアリング", "Engineering"},
    {"建設", "Construction"},
});

constexpr auto kEnglishFinancialServicesBusinessWords = std::to_array<BilingualView>({
    {"Financial Services", "Financial Services"},
    {"Financial", "Financial"},
    {"Investment", "Investment"},
    {"Insurance", "Insurance"},
});

constexpr auto kSimplifiedChineseFinancialServicesBusinessWords = std::to_array<BilingualView>({
    {"金融服务", "Financial Services"},
    {"金融", "Financial"},
    {"投资", "Investment"},
    {"保险", "Insurance"},
});

constexpr auto kTraditionalChineseFinancialServicesBusinessWords = std::to_array<BilingualView>({
    {"金融服務", "Financial Services"},
    {"金融", "Financial"},
    {"投資", "Investment"},
    {"保險", "Insurance"},
});

constexpr auto kJapaneseFinancialServicesBusinessWords = std::to_array<BilingualView>({
    {"金融サービス", "Financial Services"},
    {"金融", "Financial"},
    {"投資", "Investment"},
    {"保險", "Insurance"},
});

constexpr auto kEnglishIndustrialBusinessWords = std::to_array<BilingualView>({
    {"Industrial", "Industrial"},
    {"Machinery", "Machinery"},
    {"Equipment", "Equipment"},
    {"Heavy Industry", "Heavy Industry"},
});

constexpr auto kSimplifiedChineseIndustrialBusinessWords = std::to_array<BilingualView>({
    {"工业", "Industrial"},
    {"机械", "Machinery"},
    {"設備", "Equipment"},
    {"重工", "Heavy Industry"},
});

constexpr auto kTraditionalChineseIndustrialBusinessWords = std::to_array<BilingualView>({
    {"工業", "Industrial"},
    {"機械", "Machinery"},
    {"設備", "Equipment"},
    {"重工", "Heavy Industry"},
});

constexpr auto kJapaneseIndustrialBusinessWords = std::to_array<BilingualView>({
    {"産業", "Industrial"},
    {"機械", "Machinery"},
    {"設備", "Equipment"},
    {"重工業", "Heavy Industry"},
});

constexpr auto kEnglishInformationTechnologyBusinessWords = std::to_array<BilingualView>({
    {"Information Technology", "Information Technology"},
    {"Software", "Software"},
    {"Internet", "Internet"},
    {"Computer System", "Computer System"},
});

constexpr auto kSimplifiedChineseInformationTechnologyBusinessWords = std::to_array<BilingualView>({
    {"信息技术", "Information Technology"},
    {"软件", "Software"},
    {"互联网", "Internet"},
    {"计算机系统", "Computer System"},
});

constexpr auto kTraditionalChineseInformationTechnologyBusinessWords = std::to_array<BilingualView>({
    {"信息技術", "Information Technology"},
    {"軟體", "Software"},
    {"互聯網", "Internet"},
    {"電腦系統", "Computer System"},
});

constexpr auto kJapaneseInformationTechnologyBusinessWords = std::to_array<BilingualView>({
    {"情報技術", "Information Technology"},
    {"ソフトウェア", "Software"},
    {"インターネット", "Internet"},
    {"コンピュータシステム", "Computer System"},
});

constexpr auto kEnglishLandedPropertyBusinessWords = std::to_array<BilingualView>({
    {"Property", "Property"},
    {"Real Estate", "Real Estate"},
});

constexpr auto kSimplifiedChineseLandedPropertyBusinessWords = std::to_array<BilingualView>({
    {"地产", "Property"},
    {"房地产", "Real Estate"},
});

constexpr auto kTraditionalChineseLandedPropertyBusinessWords = std::to_array<BilingualView>({
    {"地產", "Property"},
    {"房地產", "Real Estate"},
});

constexpr auto kJapaneseLandedPropertyBusinessWords = std::to_array<BilingualView>({
    {"プロパティ", "Property"},
    {"不動產", "Real Estate"},
});

constexpr auto kEnglishLogisticBusinessWords = std::to_array<BilingualView>({
    {"Logistic", "Logistic"},
    {"Transportation", "Transportation"},
    {"Warehousing", "Warehousing"},
});

constexpr auto kSimplifiedChineseLogisticBusinessWords = std::to_array<BilingualView>({
    {"物流", "Logistic"},
    {"运输", "Transportation"},
    {"仓储", "Warehousing"},
});

constexpr auto kTraditionalChineseLogisticBusinessWords = std::to_array<BilingualView>({
    {"物流", "Logistic"},
    {"運輸", "Transportation"},
    {"倉儲", "Warehousing"},
});

constexpr auto kJapaneseLogisticBusinessWords = std::to_array<BilingualView>({
    {"物流", "Logistic"},
    {"運輸", "Transportation"},
    {"倉庫", "Warehousing"},
});

constexpr auto kEnglishManufacturingBusinessWords = std::to_array<BilingualView>({
    {"Manufacturing", "Manufacturing"},
    {"Production", "Production"},
});

constexpr auto kSimplifiedChineseManufacturingBusinessWords = std::to_array<BilingualView>({
    {"制造", "Manufacturing"},
    {"生产", "Production"},
});

constexpr auto kTraditionalChineseManufacturingBusinessWords = std::to_array<BilingualView>({
    {"製造", "Manufacturing"},
    {"生產", "Production"},
});

constexpr auto kJapaneseManufacturingBusinessWords = std::to_array<BilingualView>({
    {"製造", "Manufacturing"},
    {"生產", "Production"},
});

constexpr auto kEnglishPharmaceuticalBusinessWords = std::to_array<BilingualView>({
    {"Pharma", "Pharma"},
    {"Pharmaceutical", "Pharmaceutical"},
    {"Drug", "Drug"},
    {"Biotechnology", "Biotechnology"},
});

constexpr auto kSimplifiedChinesePharmaceuticalBusinessWords = std::to_array<BilingualView>({
    {"制药", "Pharma"},
    {"医药", "Pharmaceutical"},
    {"药品", "Drug"},
    {"生物科技", "Biotechnology"},
});

constexpr auto kTraditionalChinesePharmaceuticalBusinessWords = std::to_array<BilingualView>({
    {"製藥", "Pharma"},
    {"醫藥", "Pharmaceutical"},
    {"藥品", "Drug"},
    {"生物科技", "Biotechnology"},
});

constexpr auto kJapanesePharmaceuticalBusinessWords = std::to_array<BilingualView>({
    {"製薬", "Pharma"},
    {"医薬", "Pharmaceutical"},
    {"薬品", "Drug"},
    {"バイオテクノロジー", "Biotechnology"},
});

constexpr auto kEnglishTelecommunicationBusinessWords = std::to_array<BilingualView>({
    {"Telecommunication", "Telecommunication"},
    {"Communication", "Communication"},
    {"Network", "Network"},
    {"Wireless", "Wireless"},
});

constexpr auto kSimplifiedChineseTelecommunicationBusinessWords = std::to_array<BilingualView>({
    {"电信", "Telecommunication"},
    {"通信", "Communication"},
    {"网络", "Network"},
    {"无线", "Wireless"},
});

constexpr auto kTraditionalChineseTelecommunicationBusinessWords = std::to_array<BilingualView>({
    {"電信", "Telecommunication"},
    {"通訊", "Communication"},
    {"網絡", "Network"},
    {"無線", "Wireless"},
});

constexpr auto kJapaneseTelecommunicationBusinessWords = std::to_array<BilingualView>({
    {"電気通信", "Telecommunication"},
    {"通信", "Communication"},
    {"ネットワーク", "Network"},
    {"無線", "Wireless"},
});

constexpr auto kEnglishTradingBusinessWords = std::to_array<BilingualView>({
    {"Trading", "Trading"},
    {"Foreign Trading", "Foreign Trading"},
    {"Commerce", "Commerce"},
});

constexpr auto kSimplifiedChineseTradingBusinessWords = std::to_array<BilingualView>({
    {"贸易", "Trading"},
    {"外贸", "Foreign Trading"},
    {"商业", "Commerce"},
});

constexpr auto kTraditionalChineseTradingBusinessWords = std::to_array<BilingualView>({
    {"貿易", "Trading"},
    {"外貿", "Foreign Trading"},
    {"商業", "Commerce"},
});

constexpr auto kJapaneseTradingBusinessWords = std::to_array<BilingualView>({
    {"貿易", "Trading"},
    {"外貿", "Foreign Trading"},
    {"商業", "Commerce"},
});

const std::unordered_map<Languages, std::unordered_map<Industries, std::span<const BilingualView>>> kBusinessWords = {
    {Languages::English,
     {
         {Industries::Catering, kEnglishCateringBusinessWords},
         {Industries::Consulting, kEnglishConsultingBusinessWords},
         {Industries::Electronics, kEnglishElectronicsBusinessWords},
         {Industries::Engineering, kEnglishEngineeringBusinessWords},
         {Industries::FinancialServices, kEnglishFinancialServicesBusinessWords},
         {Industries::Industrial, kEnglishIndustrialBusinessWords},
         {Industries::InformationTechnology, kEnglishInformationTechnologyBusinessWords},
         {Industries::LandedProperty, kEnglishLandedPropertyBusinessWords},
         {Industries::Logistic, kEnglishLogisticBusinessWords},
         {Industries::Manufacturing, kEnglishManufacturingBusinessWords},
         {Industries::Pharmaceutical, kEnglishPharmaceuticalBusinessWords},
         {Industries::Telecommunication, kEnglishTelecommunicationBusinessWords},
         {Industries::Trading, kEnglishTradingBusinessWords},
     }},
    {Languages::SimplifiedChinese,
     {
         {Industries::Catering, kSimplifiedChineseCateringBusinessWords},
         {Industries::Consulting, kSimplifiedChineseConsultingBusinessWords},
         {Industries::Electronics, kSimplifiedChineseElectronicsBusinessWords},
         {Industries::Engineering, kSimplifiedChineseEngineeringBusinessWords},
         {Industries::FinancialServices, kSimplifiedChineseFinancialServicesBusinessWords},
         {Industries::Industrial, kSimplifiedChineseIndustrialBusinessWords},
         {Industries::InformationTechnology, kSimplifiedChineseInformationTechnologyBusinessWords},
         {Industries::LandedProperty, kSimplifiedChineseLandedPropertyBusinessWords},
         {Industries::Logistic, kSimplifiedChineseLogisticBusinessWords},
         {Industries::Manufacturing, kSimplifiedChineseManufacturingBusinessWords},
         {Industries::Pharmaceutical, kSimplifiedChinesePharmaceuticalBusinessWords},
         {Industries::Telecommunication, kSimplifiedChineseTelecommunicationBusinessWords},
         {Industries::Trading, kSimplifiedChineseTradingBusinessWords},
     }},
    {Languages::TraditionalChinese,
     {
         {Industries::Catering, kTraditionalChineseCateringBusinessWords},
         {Industries::Consulting, kTraditionalChineseConsultingBusinessWords},
         {Industries::Electronics, kTraditionalChineseElectronicsBusinessWords},
         {Industries::Engineering, kTraditionalChineseEngineeringBusinessWords},
         {Industries::FinancialServices, kTraditionalChineseFinancialServicesBusinessWords},
         {Industries::Industrial, kTraditionalChineseIndustrialBusinessWords},
         {Industries::InformationTechnology, kTraditionalChineseInformationTechnologyBusinessWords},
         {Industries::LandedProperty, kTraditionalChineseLandedPropertyBusinessWords},
         {Industries::Logistic, kTraditionalChineseLogisticBusinessWords},
         {Industries::Manufacturing, kTraditionalChineseManufacturingBusinessWords},
         {Industries::Pharmaceutical, kTraditionalChinesePharmaceuticalBusinessWords},
         {Industries::Telecommunication, kTraditionalChineseTelecommunicationBusinessWords},
         {Industries::Trading, kTraditionalChineseTradingBusinessWords},
     }},
    {Languages::Japanese,
     {
         {Industries::Catering, kJapaneseCateringBusinessWords},
         {Industries::Consulting, kJapaneseConsultingBusinessWords},
         {Industries::Electronics, kJapaneseElectronicsBusinessWords},
         {Industries::Engineering, kJapaneseEngineeringBusinessWords},
         {Industries::FinancialServices, kJapaneseFinancialServicesBusinessWords},
         {Industries::Industrial, kJapaneseIndustrialBusinessWords},
         {Industries::InformationTechnology, kJapaneseInformationTechnologyBusinessWords},
         {Industries::LandedProperty, kJapaneseLandedPropertyBusinessWords},
         {Industries::Logistic, kJapaneseLogisticBusinessWords},
         {Industries::Manufacturing, kJapaneseManufacturingBusinessWords},
         {Industries::Pharmaceutical, kJapanesePharmaceuticalBusinessWords},
         {Industries::Telecommunication, kJapaneseTelecommunicationBusinessWords},
         {Industries::Trading, kJapaneseTradingBusinessWords},
     }},
};

constexpr auto kEnglishDepartments = std::to_array<std::string_view>({
    "Accounting & Finance",
    "Administrative & Management",
    "Customer Service Support",
    "Engineering",
    "Export",
    "Human resource",
    "Information Technology Support",
    "Legal Department",
    "Logistics",
    "Marketing",
    "Product Quality",
    "Production",
    "Public Relations",
    "Purchasing",
    "Research & Development",
    "Sales",
});

constexpr auto kSimplifiedChineseDepartments = std::to_array<std::string_view>({
    "会计及金融部",
    "行政管理部",
    "服务支持部",
    "工程部",
    "外销部",
    "人力资源部",
    "信息技术支持部",
    "法律部",
    "物流部",
    "市场部",
    "产品质量部",
    "生产部",
    "公关部",
    "采购部",
    "研究及开发部",
    "销售部",
});

constexpr auto kTraditionalChineseDepartments = std::to_array<std::string_view>({
    "會計及金融部",
    "行政管理部",
    "服務支援部",
    "工程部",
    "外銷部",
    "人力資源部",
    "信息技術支援部",
    "法律部",
    "物流部",
    "市場部",
    "產品質量部",
    "生產部",
    "公關部",
    "採購部",
    "研究及開發部",
    "銷售部",
});

constexpr auto kJapaneseDepartments = std::to_array<std::string_view>({
    "会計財務部",
    "管理部門",
    "サービスサポート部門",
    "エンジニアリング部門",
    "輸出部門",
    "人事部",
    "情報技術支援部",
    "法務部",
    "ロジスティクス部門",
    "マーケティング部",
    "製品品質部門",
    "生産部",
    "広報部",
    "購買部",
    "研究開発部",
    "営業部",
});

}  // namespace faker::business

#endif  // FAKER_BUSINESS_DATA_H
