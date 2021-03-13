#include "pch.h"
#include "Soundex.h"

using namespace testing;
using namespace TDD;

class SoundexEncoding : public Test {
public:
	Soundex soundex;
};

TEST_F(SoundexEncoding, RetainSoleLetterOfOneLetterWord) {
	ASSERT_EQ(soundex.encode("Ab"), "A100");
	ASSERT_EQ(soundex.encode("Ac"), "A200");
	ASSERT_EQ(soundex.encode("Ad"), "A300");
}
TEST_F(SoundexEncoding, PadsWithZerosToEnsureThreeDigits)
{
	ASSERT_EQ(soundex.encode("I"), "I000");
}

TEST_F(SoundexEncoding, ReplaceConstantsWithAppropriateDigits) {
	ASSERT_EQ(soundex.encode("Ax"), "A200");
}

TEST_F(SoundexEncoding, IgonoreNonAlphabetics) {
	ASSERT_EQ(soundex.encode("A#"), "A000");
}

TEST_F(SoundexEncoding, ReplaceMultipleConsonatsWithDigits) {
	ASSERT_EQ(soundex.encode("Acdl"), "A234");
}

TEST_F(SoundexEncoding, LimitsLengthToFourCharacters) {
	ASSERT_EQ(soundex.encode("Dcdlb").length(), 4u);
}

TEST_F(SoundexEncoding, IgnoresVowelLikeLetters) {
	ASSERT_EQ(soundex.encode("BaAeEiIoOuUhHyYcdl"), "B234");
}

TEST_F(SoundexEncoding, CombineDuplicateEncodings) {
	//Let encodedDigit to public member...
	ASSERT_EQ(soundex.encodedDigit('b'), soundex.encodedDigit('f'));
	ASSERT_EQ(soundex.encodedDigit('c'), soundex.encodedDigit('g'));
	ASSERT_EQ(soundex.encodedDigit('d'), soundex.encodedDigit('t'));

	ASSERT_EQ(soundex.encode("Abfcgdt"), "A123");
}

TEST_F(SoundexEncoding, UppecasesFirstLetter) {
	//ASSERT_EQ(soundex.encode("abcd"), StartsWith("A"));
	ASSERT_EQ(soundex.encode("abcd"), "A123");  //It's like IgnoresVowelLikeLetters
}

TEST_F(SoundexEncoding, IgnoresCaseWhenEncodingConsonants) {
	ASSERT_EQ(soundex.encode("BCDL"), soundex.encode("Bcdl"));
}

TEST_F(SoundexEncoding, CombineDuplicateCodesWhen2ndLetterDuplicates1st) {
	ASSERT_EQ(soundex.encode("Bbcd"), "B230");
}

TEST_F(SoundexEncoding, DoesNotCombineDuplcateEncodingsSeparateByVowels) {
	ASSERT_EQ(soundex.encode("Jbob"), "J110");
}
