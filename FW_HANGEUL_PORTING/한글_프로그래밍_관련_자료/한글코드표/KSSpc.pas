{
	파일 : KSSpc.pas
	기능 : KS C 5601-1987 완성형 특수문자 1128자 코드표

	날짜 : 2002년 1월 2일 수요일


	
        $A1             하위바이트            $FE
    $A1 +---------------------------------------+ --+
        |                                       |   |
     상 |                                       |   |
     위 |                                       |   |
     바 |         특수문자 영역(1128자)         |  12개
     이 |                                       |   |
     트 |                                       |   |
        |                                       |   |
    $AC +---------------------------------------+ --+

        |                                       |
        +----------------- 94개 ----------------+

    ----------------------------------------------------------------
    기호1 :
    　、。·‥…¨〃­―∥＼∼‘’“”〔〕〈〉《》「」『』【】±×÷
    ≠≤≥∞∴°′″℃Å￠￡￥♂♀∠⊥⌒∂∇≡≒§※☆★○●◎◇◆□
    ■△▲▽▼→←↑↓↔〓≪≫√∽∝∵∫∬∈∋⊆⊇⊂⊃∪∩∧∨￢
    기호2 :
    ⇒⇔∀∃´～ˇ˘˝˚˙¸˛¡¿ː∮∑∏¤℉‰◁◀▷▶♤♠♡♥♧♣
    ⊙◈▣◐◑▒▤▥▨▧▦▩♨☏☎☜☞¶†‡↕↗↙↖↘♭♩♪♬㉿㈜№
    ㏇™㏂㏘℡€®???????????????????????
    영문자 :
    ！＂＃＄％＆＇（）＊＋，－．／０１２３４５６７８９：；＜＝＞？＠
    ＡＢＣＤＥＦＧＨＩＪＫＬＭＮＯＰＱＲＳＴＵＶＷＸＹＺ［￦］＾＿｀
    ａｂｃｄｅｆｇｈｉｊｋｌｍｎｏｐｑｒｓｔｕｖｗｘｙｚ｛｜｝￣
    한글자모 :
    ㄱㄲㄳㄴㄵㄶㄷㄸㄹㄺㄻㄼㄽㄾㄿㅀㅁㅂㅃㅄㅅㅆㅇㅈㅉㅊㅋㅌㅍㅎㅏㅐ
    ㅑㅒㅓㅔㅕㅖㅗㅘㅙㅚㅛㅜㅝㅞㅟㅠㅡㅢㅣㅤㅥㅦㅧㅨㅩㅪㅫㅬㅭㅮㅯㅰ
    ㅱㅲㅳㅴㅵㅶㅷㅸㅹㅺㅻㅼㅽㅾㅿㆀㆁㆂㆃㆄㆅㆆㆇㆈㆉㆊㆋㆌㆍㆎ
    그리스어 :
    ⅰⅱⅲⅳⅴⅵⅶⅷⅸⅹ?????ⅠⅡⅢⅣⅤⅥⅦⅧⅨⅩ???????
    ΑΒΓΔΕΖΗΘΙΚΛΜΝΞΟΠΡΣΤΥΦΧΨΩ????????
    αβγδεζηθικλμνξοπρστυφχψω??????
    선문자 :
    ─│┌┐┘└├┬┤┴┼━┃┏┓┛┗┣┳┫┻╋┠┯┨┷┿┝┰┥┸╂
    ┒┑┚┙┖┕┎┍┞┟┡┢┦┧┩┪┭┮┱┲┵┶┹┺┽┾╀╁╃╄╅╆
    ╇╈╉╊??????????????????????????
    단위 :
    ㎕㎖㎗ℓ㎘㏄㎣㎤㎥㎦㎙㎚㎛㎜㎝㎞㎟㎠㎡㎢㏊㎍㎎㎏㏏㎈㎉㏈㎧㎨㎰㎱
    ㎲㎳㎴㎵㎶㎷㎸㎹㎀㎁㎂㎃㎄㎺㎻㎼㎽㎾㎿㎐㎑㎒㎓㎔Ω㏀㏁㎊㎋㎌㏖㏅
    ㎭㎮㎯㏛㎩㎪㎫㎬㏝㏐㏓㏃㏉㏜㏆???????????????
    원문자 :
    ÆÐªĦ?Ĳ?ĿŁØŒºÞŦŊ?㉠㉡㉢㉣㉤㉥㉦㉧㉨㉩㉪㉫㉬㉭㉮㉯
    ㉰㉱㉲㉳㉴㉵㉶㉷㉸㉹㉺㉻ⓐⓑⓒⓓⓔⓕⓖⓗⓘⓙⓚⓛⓜⓝⓞⓟⓠⓡⓢⓣ
    ⓤⓥⓦⓧⓨⓩ①②③④⑤⑥⑦⑧⑨⑩⑪⑫⑬⑭⑮½⅓⅔¼¾⅛⅜⅝⅞
    괄호문자 :
    æđðħıĳĸŀłøœßþŧŋŉ㈀㈁㈂㈃㈄㈅㈆㈇㈈㈉㈊㈋㈌㈍㈎㈏
    ㈐㈑㈒㈓㈔㈕㈖㈗㈘㈙㈚㈛⒜⒝⒞⒟⒠⒡⒢⒣⒤⒥⒦⒧⒨⒩⒪⒫⒬⒭⒮⒯
    ⒰⒱⒲⒳⒴⒵⑴⑵⑶⑷⑸⑹⑺⑻⑼⑽⑾⑿⒀⒁⒂¹²³⁴ⁿ₁₂₃₄
    히라가나 :
    ぁあぃいぅうぇえぉおかがきぎくぐけげこごさざしじすずせぜそぞただ
    ちぢっつづてでとどなにぬねのはばぱひびぴふぶぷへべぺほぼぽまみむ
    めもゃやゅゆょよらりるれろゎわゐゑをん???????????
    가타카나 :
    ァアィイゥウェエォオカガキギクグケゲコゴサザシジスズセゼソゾタダ
    チヂッツヅテデトドナニヌネノハバパヒビピフブプヘベペホボポマミム
    メモャヤュユョヨラリルレロヮワヰヱヲンヴヵヶ????????
    러시아어 :
    АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮ
    Я???????????????абвгдеёжзийклмно
    прстуфхцчшщъыьэюя?????????????
    ----------------------------------------------------------------
}

unit KSSpc;

interface

const
  KSSpcTable : array[1..1128] of Integer = (
    // 기호1
	$A1A1, $A1A2, $A1A3, $A1A4, $A1A5, $A1A6, $A1A7, $A1A8,
	$A1A9, $A1AA, $A1AB, $A1AC, $A1AD, $A1AE, $A1AF, $A1B0,
	$A1B1, $A1B2, $A1B3, $A1B4, $A1B5, $A1B6, $A1B7, $A1B8,
	$A1B9, $A1BA, $A1BB, $A1BC, $A1BD, $A1BE, $A1BF, $A1C0,
	$A1C1, $A1C2, $A1C3, $A1C4, $A1C5, $A1C6, $A1C7, $A1C8,
	$A1C9, $A1CA, $A1CB, $A1CC, $A1CD, $A1CE, $A1CF, $A1D0,
	$A1D1, $A1D2, $A1D3, $A1D4, $A1D5, $A1D6, $A1D7, $A1D8,
	$A1D9, $A1DA, $A1DB, $A1DC, $A1DD, $A1DE, $A1DF, $A1E0,
	$A1E1, $A1E2, $A1E3, $A1E4, $A1E5, $A1E6, $A1E7, $A1E8,
	$A1E9, $A1EA, $A1EB, $A1EC, $A1ED, $A1EE, $A1EF, $A1F0,
	$A1F1, $A1F2, $A1F3, $A1F4, $A1F5, $A1F6, $A1F7, $A1F8,
	$A1F9, $A1FA, $A1FB, $A1FC, $A1FD, $A1FE,
    // 기호2
	$A2A1, $A2A2, $A2A3, $A2A4, $A2A5, $A2A6, $A2A7, $A2A8,
	$A2A9, $A2AA, $A2AB, $A2AC, $A2AD, $A2AE, $A2AF, $A2B0,
	$A2B1, $A2B2, $A2B3, $A2B4, $A2B5, $A2B6, $A2B7, $A2B8,
	$A2B9, $A2BA, $A2BB, $A2BC, $A2BD, $A2BE, $A2BF, $A2C0,
	$A2C1, $A2C2, $A2C3, $A2C4, $A2C5, $A2C6, $A2C7, $A2C8,
	$A2C9, $A2CA, $A2CB, $A2CC, $A2CD, $A2CE, $A2CF, $A2D0,
	$A2D1, $A2D2, $A2D3, $A2D4, $A2D5, $A2D6, $A2D7, $A2D8,
	$A2D9, $A2DA, $A2DB, $A2DC, $A2DD, $A2DE, $A2DF, $A2E0,
	$A2E1, $A2E2, $A2E3, $A2E4, $A2E5, $A2E6, $A2E7, $A2E8,
	$A2E9, $A2EA, $A2EB, $A2EC, $A2ED, $A2EE, $A2EF, $A2F0,
	$A2F1, $A2F2, $A2F3, $A2F4, $A2F5, $A2F6, $A2F7, $A2F8,
	$A2F9, $A2FA, $A2FB, $A2FC, $A2FD, $A2FE,
    // 영문자
	$A3A1, $A3A2, $A3A3, $A3A4, $A3A5, $A3A6, $A3A7, $A3A8,
	$A3A9, $A3AA, $A3AB, $A3AC, $A3AD, $A3AE, $A3AF, $A3B0,
	$A3B1, $A3B2, $A3B3, $A3B4, $A3B5, $A3B6, $A3B7, $A3B8,
	$A3B9, $A3BA, $A3BB, $A3BC, $A3BD, $A3BE, $A3BF, $A3C0,
	$A3C1, $A3C2, $A3C3, $A3C4, $A3C5, $A3C6, $A3C7, $A3C8,
	$A3C9, $A3CA, $A3CB, $A3CC, $A3CD, $A3CE, $A3CF, $A3D0,
	$A3D1, $A3D2, $A3D3, $A3D4, $A3D5, $A3D6, $A3D7, $A3D8,
	$A3D9, $A3DA, $A3DB, $A3DC, $A3DD, $A3DE, $A3DF, $A3E0,
	$A3E1, $A3E2, $A3E3, $A3E4, $A3E5, $A3E6, $A3E7, $A3E8,
	$A3E9, $A3EA, $A3EB, $A3EC, $A3ED, $A3EE, $A3EF, $A3F0,
	$A3F1, $A3F2, $A3F3, $A3F4, $A3F5, $A3F6, $A3F7, $A3F8,
	$A3F9, $A3FA, $A3FB, $A3FC, $A3FD, $A3FE,
    // 한글자모
	$A4A1, $A4A2, $A4A3, $A4A4, $A4A5, $A4A6, $A4A7, $A4A8,
	$A4A9, $A4AA, $A4AB, $A4AC, $A4AD, $A4AE, $A4AF, $A4B0,
	$A4B1, $A4B2, $A4B3, $A4B4, $A4B5, $A4B6, $A4B7, $A4B8,
	$A4B9, $A4BA, $A4BB, $A4BC, $A4BD, $A4BE, $A4BF, $A4C0,
	$A4C1, $A4C2, $A4C3, $A4C4, $A4C5, $A4C6, $A4C7, $A4C8,
	$A4C9, $A4CA, $A4CB, $A4CC, $A4CD, $A4CE, $A4CF, $A4D0,
	$A4D1, $A4D2, $A4D3, $A4D4, $A4D5, $A4D6, $A4D7, $A4D8,
	$A4D9, $A4DA, $A4DB, $A4DC, $A4DD, $A4DE, $A4DF, $A4E0,
	$A4E1, $A4E2, $A4E3, $A4E4, $A4E5, $A4E6, $A4E7, $A4E8,
	$A4E9, $A4EA, $A4EB, $A4EC, $A4ED, $A4EE, $A4EF, $A4F0,
	$A4F1, $A4F2, $A4F3, $A4F4, $A4F5, $A4F6, $A4F7, $A4F8,
	$A4F9, $A4FA, $A4FB, $A4FC, $A4FD, $A4FE,
    // 그리스어
	$A5A1, $A5A2, $A5A3, $A5A4, $A5A5, $A5A6, $A5A7, $A5A8,
	$A5A9, $A5AA, $A5AB, $A5AC, $A5AD, $A5AE, $A5AF, $A5B0,
	$A5B1, $A5B2, $A5B3, $A5B4, $A5B5, $A5B6, $A5B7, $A5B8,
	$A5B9, $A5BA, $A5BB, $A5BC, $A5BD, $A5BE, $A5BF, $A5C0,
	$A5C1, $A5C2, $A5C3, $A5C4, $A5C5, $A5C6, $A5C7, $A5C8,
	$A5C9, $A5CA, $A5CB, $A5CC, $A5CD, $A5CE, $A5CF, $A5D0,
	$A5D1, $A5D2, $A5D3, $A5D4, $A5D5, $A5D6, $A5D7, $A5D8,
	$A5D9, $A5DA, $A5DB, $A5DC, $A5DD, $A5DE, $A5DF, $A5E0,
	$A5E1, $A5E2, $A5E3, $A5E4, $A5E5, $A5E6, $A5E7, $A5E8,
	$A5E9, $A5EA, $A5EB, $A5EC, $A5ED, $A5EE, $A5EF, $A5F0,
	$A5F1, $A5F2, $A5F3, $A5F4, $A5F5, $A5F6, $A5F7, $A5F8,
	$A5F9, $A5FA, $A5FB, $A5FC, $A5FD, $A5FE,
    // 선문자
	$A6A1, $A6A2, $A6A3, $A6A4, $A6A5, $A6A6, $A6A7, $A6A8,
	$A6A9, $A6AA, $A6AB, $A6AC, $A6AD, $A6AE, $A6AF, $A6B0,
	$A6B1, $A6B2, $A6B3, $A6B4, $A6B5, $A6B6, $A6B7, $A6B8,
	$A6B9, $A6BA, $A6BB, $A6BC, $A6BD, $A6BE, $A6BF, $A6C0,
	$A6C1, $A6C2, $A6C3, $A6C4, $A6C5, $A6C6, $A6C7, $A6C8,
	$A6C9, $A6CA, $A6CB, $A6CC, $A6CD, $A6CE, $A6CF, $A6D0,
	$A6D1, $A6D2, $A6D3, $A6D4, $A6D5, $A6D6, $A6D7, $A6D8,
	$A6D9, $A6DA, $A6DB, $A6DC, $A6DD, $A6DE, $A6DF, $A6E0,
	$A6E1, $A6E2, $A6E3, $A6E4, $A6E5, $A6E6, $A6E7, $A6E8,
	$A6E9, $A6EA, $A6EB, $A6EC, $A6ED, $A6EE, $A6EF, $A6F0,
	$A6F1, $A6F2, $A6F3, $A6F4, $A6F5, $A6F6, $A6F7, $A6F8,
	$A6F9, $A6FA, $A6FB, $A6FC, $A6FD, $A6FE,
    // 단위
	$A7A1, $A7A2, $A7A3, $A7A4, $A7A5, $A7A6, $A7A7, $A7A8,
	$A7A9, $A7AA, $A7AB, $A7AC, $A7AD, $A7AE, $A7AF, $A7B0,
	$A7B1, $A7B2, $A7B3, $A7B4, $A7B5, $A7B6, $A7B7, $A7B8,
	$A7B9, $A7BA, $A7BB, $A7BC, $A7BD, $A7BE, $A7BF, $A7C0,
	$A7C1, $A7C2, $A7C3, $A7C4, $A7C5, $A7C6, $A7C7, $A7C8,
	$A7C9, $A7CA, $A7CB, $A7CC, $A7CD, $A7CE, $A7CF, $A7D0,
	$A7D1, $A7D2, $A7D3, $A7D4, $A7D5, $A7D6, $A7D7, $A7D8,
	$A7D9, $A7DA, $A7DB, $A7DC, $A7DD, $A7DE, $A7DF, $A7E0,
	$A7E1, $A7E2, $A7E3, $A7E4, $A7E5, $A7E6, $A7E7, $A7E8,
	$A7E9, $A7EA, $A7EB, $A7EC, $A7ED, $A7EE, $A7EF, $A7F0,
	$A7F1, $A7F2, $A7F3, $A7F4, $A7F5, $A7F6, $A7F7, $A7F8,
	$A7F9, $A7FA, $A7FB, $A7FC, $A7FD, $A7FE,
    // 원문자
	$A8A1, $A8A2, $A8A3, $A8A4, $A8A5, $A8A6, $A8A7, $A8A8,
	$A8A9, $A8AA, $A8AB, $A8AC, $A8AD, $A8AE, $A8AF, $A8B0,
	$A8B1, $A8B2, $A8B3, $A8B4, $A8B5, $A8B6, $A8B7, $A8B8,
	$A8B9, $A8BA, $A8BB, $A8BC, $A8BD, $A8BE, $A8BF, $A8C0,
	$A8C1, $A8C2, $A8C3, $A8C4, $A8C5, $A8C6, $A8C7, $A8C8,
	$A8C9, $A8CA, $A8CB, $A8CC, $A8CD, $A8CE, $A8CF, $A8D0,
	$A8D1, $A8D2, $A8D3, $A8D4, $A8D5, $A8D6, $A8D7, $A8D8,
	$A8D9, $A8DA, $A8DB, $A8DC, $A8DD, $A8DE, $A8DF, $A8E0,
	$A8E1, $A8E2, $A8E3, $A8E4, $A8E5, $A8E6, $A8E7, $A8E8,
	$A8E9, $A8EA, $A8EB, $A8EC, $A8ED, $A8EE, $A8EF, $A8F0,
	$A8F1, $A8F2, $A8F3, $A8F4, $A8F5, $A8F6, $A8F7, $A8F8,
	$A8F9, $A8FA, $A8FB, $A8FC, $A8FD, $A8FE,
    // 괄호문자
	$A9A1, $A9A2, $A9A3, $A9A4, $A9A5, $A9A6, $A9A7, $A9A8,
	$A9A9, $A9AA, $A9AB, $A9AC, $A9AD, $A9AE, $A9AF, $A9B0,
	$A9B1, $A9B2, $A9B3, $A9B4, $A9B5, $A9B6, $A9B7, $A9B8,
	$A9B9, $A9BA, $A9BB, $A9BC, $A9BD, $A9BE, $A9BF, $A9C0,
	$A9C1, $A9C2, $A9C3, $A9C4, $A9C5, $A9C6, $A9C7, $A9C8,
	$A9C9, $A9CA, $A9CB, $A9CC, $A9CD, $A9CE, $A9CF, $A9D0,
	$A9D1, $A9D2, $A9D3, $A9D4, $A9D5, $A9D6, $A9D7, $A9D8,
	$A9D9, $A9DA, $A9DB, $A9DC, $A9DD, $A9DE, $A9DF, $A9E0,
	$A9E1, $A9E2, $A9E3, $A9E4, $A9E5, $A9E6, $A9E7, $A9E8,
	$A9E9, $A9EA, $A9EB, $A9EC, $A9ED, $A9EE, $A9EF, $A9F0,
	$A9F1, $A9F2, $A9F3, $A9F4, $A9F5, $A9F6, $A9F7, $A9F8,
	$A9F9, $A9FA, $A9FB, $A9FC, $A9FD, $A9FE,
    // 히리가나
	$AAA1, $AAA2, $AAA3, $AAA4, $AAA5, $AAA6, $AAA7, $AAA8,
	$AAA9, $AAAA, $AAAB, $AAAC, $AAAD, $AAAE, $AAAF, $AAB0,
	$AAB1, $AAB2, $AAB3, $AAB4, $AAB5, $AAB6, $AAB7, $AAB8,
	$AAB9, $AABA, $AABB, $AABC, $AABD, $AABE, $AABF, $AAC0,
	$AAC1, $AAC2, $AAC3, $AAC4, $AAC5, $AAC6, $AAC7, $AAC8,
	$AAC9, $AACA, $AACB, $AACC, $AACD, $AACE, $AACF, $AAD0,
	$AAD1, $AAD2, $AAD3, $AAD4, $AAD5, $AAD6, $AAD7, $AAD8,
	$AAD9, $AADA, $AADB, $AADC, $AADD, $AADE, $AADF, $AAE0,
	$AAE1, $AAE2, $AAE3, $AAE4, $AAE5, $AAE6, $AAE7, $AAE8,
	$AAE9, $AAEA, $AAEB, $AAEC, $AAED, $AAEE, $AAEF, $AAF0,
	$AAF1, $AAF2, $AAF3, $AAF4, $AAF5, $AAF6, $AAF7, $AAF8,
	$AAF9, $AAFA, $AAFB, $AAFC, $AAFD, $AAFE,
    // 가타카나
	$ABA1, $ABA2, $ABA3, $ABA4, $ABA5, $ABA6, $ABA7, $ABA8,
	$ABA9, $ABAA, $ABAB, $ABAC, $ABAD, $ABAE, $ABAF, $ABB0,
	$ABB1, $ABB2, $ABB3, $ABB4, $ABB5, $ABB6, $ABB7, $ABB8,
	$ABB9, $ABBA, $ABBB, $ABBC, $ABBD, $ABBE, $ABBF, $ABC0,
	$ABC1, $ABC2, $ABC3, $ABC4, $ABC5, $ABC6, $ABC7, $ABC8,
	$ABC9, $ABCA, $ABCB, $ABCC, $ABCD, $ABCE, $ABCF, $ABD0,
	$ABD1, $ABD2, $ABD3, $ABD4, $ABD5, $ABD6, $ABD7, $ABD8,
	$ABD9, $ABDA, $ABDB, $ABDC, $ABDD, $ABDE, $ABDF, $ABE0,
	$ABE1, $ABE2, $ABE3, $ABE4, $ABE5, $ABE6, $ABE7, $ABE8,
	$ABE9, $ABEA, $ABEB, $ABEC, $ABED, $ABEE, $ABEF, $ABF0,
	$ABF1, $ABF2, $ABF3, $ABF4, $ABF5, $ABF6, $ABF7, $ABF8,
	$ABF9, $ABFA, $ABFB, $ABFC, $ABFD, $ABFE,
    // 러시아어
	$ACA1, $ACA2, $ACA3, $ACA4, $ACA5, $ACA6, $ACA7, $ACA8,
	$ACA9, $ACAA, $ACAB, $ACAC, $ACAD, $ACAE, $ACAF, $ACB0,
	$ACB1, $ACB2, $ACB3, $ACB4, $ACB5, $ACB6, $ACB7, $ACB8,
	$ACB9, $ACBA, $ACBB, $ACBC, $ACBD, $ACBE, $ACBF, $ACC0,
	$ACC1, $ACC2, $ACC3, $ACC4, $ACC5, $ACC6, $ACC7, $ACC8,
	$ACC9, $ACCA, $ACCB, $ACCC, $ACCD, $ACCE, $ACCF, $ACD0,
	$ACD1, $ACD2, $ACD3, $ACD4, $ACD5, $ACD6, $ACD7, $ACD8,
	$ACD9, $ACDA, $ACDB, $ACDC, $ACDD, $ACDE, $ACDF, $ACE0,
	$ACE1, $ACE2, $ACE3, $ACE4, $ACE5, $ACE6, $ACE7, $ACE8,
	$ACE9, $ACEA, $ACEB, $ACEC, $ACED, $ACEE, $ACEF, $ACF0,
	$ACF1, $ACF2, $ACF3, $ACF4, $ACF5, $ACF6, $ACF7, $ACF8,
	$ACF9, $ACFA, $ACFB, $ACFC, $ACFD, $ACFE
  );

implementation

end.
