// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file product_data.h

#ifndef FAKER_PRODUCT_DATA_H
#define FAKER_PRODUCT_DATA_H

#include <array>
#include <string_view>

namespace faker::product {

constexpr auto kEnglishProductNamePrefixesAndSuffixes = std::to_array<std::string_view>({
    "{}",
    "{} Pro",
    "{} Plus",
    "{} Premium",
    "{} Enterprise",
    "{} Ultra",
    "{} Pro Max",
    "{} Max",
    "{} Air",
    "{} Mini",
    "{} Lite",
    "{} SE",
    "{} FE",
    "{} Core",
    "{} Limited Edition",
    "{} PI",
    "Omni {}",
    "Ambi {}",
});

constexpr auto kSimplifiedChineseProductNamePrefixesAndSuffixes = std::to_array<std::string_view>({
    "{}",
    "{} 青春版",
    "{} 尊享版",
    "{} 典藏版",
    "{} 旗舰版",
});

constexpr auto kTraditionalChineseProductNamePrefixesAndSuffixes = std::to_array<std::string_view>({
    "{}",
    "{} 青春版",
    "{} 尊享版",
    "{} 限定版",
    "{} 旗艦版",
});

constexpr auto kJapaneseProductNamePrefixesAndSuffixes = std::to_array<std::string_view>({
    "{}",
    "{} コレクション",
    "{} 限定",
});

constexpr auto kEnglishProductCategories = std::to_array<std::string_view>({
    "Appliances",
    "Apps & Games",
    "Arts, Handicrafts & Sewing",
    "Automotive Parts & Accessories",
    "Baby",
    "Baggage & Travel Equipment",
    "Beauty & Personal Care",
    "Books",
    "CDs & Vinyl",
    "Cell Phones & Accessories",
    "Collectibles & Fine Art",
    "Computers & Electronics",
    "Film Supplies",
    "Food",
    "Garden & Outdoor",
    "Health & Baby Care",
    "Household & Kitchen Appliances",
    "Industrial & Scientific Supplies",
    "Musical Instruments",
    "Others",
    "Pet Supplies",
    "Sports & Outdoor",
    "Tools & Home Decoration",
    "Toys & Games",
    "Video Games",
});

constexpr auto kSimplifiedChineseProductCategories = std::to_array<std::string_view>({
    "家电",
    "应用程式及游戏",
    "艺术，手工艺品及缝纫",
    "汽车零配件",
    "婴儿用品",
    "行李及旅行装备",
    "美容与个人护理",
    "书本",
    "CD及黑胶唱片",
    "手机及配件",
    "收藏品及美术用品",
    "电脑与电子用品",
    "影视用品",
    "食品",
    "花园与户外",
    "保健，家庭及婴儿护理",
    "家居及厨房用具",
    "工业及科学用品",
    "乐器用品",
    "其他",
    "宠物用品",
    "运动与户外用品",
    "工具与家居装饰",
    "玩具与游戏",
    "电子游戏",
});

constexpr auto kTraditionalChineseProductCategories = std::to_array<std::string_view>({
    "家電",
    "應用程式及遊戲",
    "藝術，手工藝品及縫紉",
    "汽車零配件",
    "嬰兒用品",
    "行李及旅行裝備",
    "美容與個人護理",
    "書本",
    "CD及黑膠唱片",
    "手機及配件",
    "收藏品及美術用品",
    "電腦與電子用品",
    "影視用品",
    "食品",
    "花園與戶外",
    "保健，家庭及嬰兒護理",
    "家居及廚房用具",
    "工業及科學用品",
    "樂器用品",
    "其他",
    "寵物用品",
    "運動與戶外用品",
    "工具與家居裝飾",
    "玩具與遊戲",
    "電子遊戲",
});

constexpr auto kJapaneseProductCategories = std::to_array<std::string_view>({
    "家電",
    "アプリとゲーム",
    "芸術、手工芸品、縫製",
    "自動車部品",
    "ベビー用品",
    "手荷物および旅行用品",
    "美容とパーソナルケア",
    "書籍",
    "CDとレコード",
    "携帯電話とアクセサリー",
    "収集品と画材",
    "コンピュータおよび電子機器",
    "映画およびテレビ用品",
    "食品",
    "庭とアウトドア",
    "健康、在宅、ベビーケア",
    "家庭用および台所用電化製品",
    "工業および科学用品",
    "楽器用品",
    "その他",
    "ペット用品",
    "スポーツとアウトドア用品",
    "ツールと家の装飾",
    "おもちゃとゲーム",
    "電子ゲーム",
});

constexpr auto kEnglishColors = std::to_array<std::string_view>({
    "Amber",      "Apricot",    "Beige",       "Black",         "Bronze",
    "Brown",      "Camel",      "Chocolate",   "Chrome Yellow", "Coffee",
    "Cream",      "Dark Gray",  "Dark Red",    "Dim Gray",      "Fire Brick",
    "Gainsboro",  "Gold",       "Gray",        "Honey Orange",  "Indian Red",
    "Iron",       "Jasmine",    "Khaki",       "Light Coral",   "Light Gray",
    "Lime",       "Maroon",     "Misty Rose",  "Mustard",       "Olive",
    "Orange",     "Orange Red", "Peach",       "Persimmon",     "Red",
    "Rosy Brown", "Salmon",     "Sand Beige",  "Scarlet",       "Sepia",
    "Silver",     "Snow",       "Strong Red",  "Tangerine",     "Tropical Orange",
    "Vermilion",  "White",      "White Smoke", "Yellow",
});

constexpr auto kSimplifiedChineseColors = std::to_array<std::string_view>({
    "琥珀色", "杏黄",   "米色",   "黑色",     "青铜色", "褐色",       "驼色", "巧克力色", "铬黄",   "咖啡色",
    "奶油色", "暗灰",   "暗红",   "昏灰",     "砖红色", "庚斯博罗灰", "金色", "灰色",     "蜜橙",   "印度红",
    "铁灰色", "茉莉黄", "卡其色", "亮珊瑚色", "亮灰色", "柠檬绿色",   "栗色", "雾玫瑰色", "芥末黄", "橄榄色",
    "橙色",   "橙红",   "桃色",   "柿子橙",   "红色",   "玫瑰褐",     "鲑红", "沙棕",     "猩红色", "乌贼墨色",
    "银色",   "雪色",   "鲜红",   "橘色",     "热带橙", "朱红色",     "白色", "白烟色",   "黄色",
});

constexpr auto kTraditionalChineseColors = std::to_array<std::string_view>({
    "琥珀色", "杏黃",   "米色",   "黑色",     "青銅色", "褐色",       "駝色", "巧克力色", "鉻黃",   "咖啡色",
    "奶油色", "暗灰",   "暗紅",   "昏灰",     "磚紅色", "庚斯博羅灰", "金色", "灰色",     "蜜橙",   "印度紅",
    "鐵灰色", "茉莉黃", "卡其色", "亮珊瑚色", "亮灰色", "檸檬绿色",   "栗色", "霧玫瑰色", "芥末黃", "橄欖色",
    "橙色",   "橙紅",   "桃色",   "柿子橙",   "紅色",   "玫瑰褐",     "鮭紅", "沙棕",     "猩紅色", "烏賊墨色",
    "銀色",   "雪色",   "鮮紅",   "橘色",     "熱帶橙", "朱紅色",     "白色", "白煙色",   "黃色",
});

constexpr auto kJapaneseColors = std::to_array<std::string_view>({
    "アンバー",
    "アプリコット",
    "ベージュ",
    "黒",
    "ブロンズ",
    "ブラウン",
    "キャメル",
    "チョコレート色",
    "黄鉛",
    "コーヒー色",
    "クリーム色",
    "ダークグレー",
    "ダークレッド",
    "薄暗い",
    "ブリックレッド",
    "ゲインズボローグレイ",
    "ゴールデン",
    "グレー",
    "ハニーオレンジ",
    "インディアンレッド",
    "鉄灰色",
    "ジャスミンイエロー",
    "カーキ",
    "明るい珊瑚",
    "明るい灰色",
    "レモングリーン",
    "マルーン",
    "ミスティローズ",
    "マスタードイエロー",
    "オリーブ",
    "オレンジ",
    "オレンジレッド",
    "ピーチ",
    "柿オレンジ",
    "レッド",
    "ローズブラウン",
    "サーモンレッド",
    "サンドブラウン",
    "スカーレット",
    "セピア",
    "シルバー",
    "雪の色",
    "真っ赤",
    "タンジェリン",
    "トロピカルオレンジ",
    "バーミリオン",
    "白い",
    "白い煙",
    "イエロー",
});

constexpr auto kProductSizes = std::to_array<std::string_view>({
    "XS",
    "S",
    "M",
    "L",
    "XL",
    "XXL",
});

constexpr auto kBarcodeEAN13Formats = std::to_array<std::string_view>({
    // US: 000-019, 030-039, 060-139
    "00###########",
    "01###########",
    "03###########",
    "06###########",
    "07###########",
    "08###########",
    "09###########",
    "10###########",
    "11###########",
    "12###########",
    "13###########",
    // UK: 500-509
    "50###########",
    // CN: 690-695
    "690##########",
    "691##########",
    "692##########",
    "693##########",
    "694##########",
    "695##########",
    // JP: 450-459, 490-499
    "45###########",
    "49###########",
});

constexpr auto kBarcodeEAN8Formats = std::to_array<std::string_view>({
    // US: 000-019, 030-039, 060-139
    "00######",
    "01######",
    "03######",
    "06######",
    "07######",
    "08######",
    "09######",
    "10######",
    "11######",
    "12######",
    "13######",
    // UK: 500-509
    "50######",
    // CN: 690-695
    "690#####",
    "691#####",
    "692#####",
    "693#####",
    "694#####",
    "695#####",
    // JP: 450-459, 490-499
    "45######",
    "49######",
});

constexpr auto kBarcodeUPCAFormats = std::to_array<std::string_view>({
    "0###########",
    "1###########",
    "6###########",
    "7###########",
    "3###########",
    "5###########",
});

constexpr auto kBarcodeUPCEFormats = std::to_array<std::string_view>({
    "0#####",
    "1#####",
    "6#####",
    "7#####",
    "3#####",
    "5#####",
});

constexpr auto kBarcodeISBNFormats = std::to_array<std::string_view>({
    "978##########",
    "979##########",
});

}  // namespace faker::product

#endif  // FAKER_PRODUCT_DATA_H
