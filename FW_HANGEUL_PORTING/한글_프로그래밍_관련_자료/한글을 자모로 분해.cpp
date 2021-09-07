bool HanDiv(char *Han, char *Han3);
String HanDivPas(String Src);

//---------------------------------------------------------------------------
// HanDivPas, HanDiv
// Programmed by Jounlai Cho (jounlai@yahoo.com)

// function HanDiv: 한글을 자모로 분해
// Han: 변환할 글자, PChar 타입
// Han3: 분해된 자모, PChar 타입
// (Result): 함수 호출 성공(True), 실패(False)
// *주의: 변수 Han과 Han3이 가리키는 메모리 공간은 각각 2, 6바이트가
// 할당되어 있어야 한다. 그리고 Han과 Han3 모두 null-종료 문자열이 아니다.
bool HanDiv(char *Han, char *Han3)
{
    const char *ChoSungTbl    = "ㄱㄲㄴㄷㄸㄹㅁㅂㅃㅅㅆㅇㅈㅉㅊㅋㅌㅍㅎ";
    const char *JungSungTbl	= "ㅏㅐㅑㅒㅓㅔㅕㅖㅗㅘㅙㅚㅛㅜㅝㅞㅟㅠㅡㅢㅣ";
    const char *JongSungTbl	= "  ㄱㄲㄳㄴㄵㄶㄷㄹㄺㄻㄼㄽㄾㄿㅀㅁㅂㅄㅅㅆㅇㅈㅊㅋㅌㅍㅎ";
    const WORD UniCodeHangeulBase = 0xAC00;
    const WORD UniCodeHangeulLast = 0xD79F;

	wchar_t UniCode;
	int ChoSung, JungSung, JongSung;

	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, Han, 2, &UniCode, 1);

	if ((UniCode < UniCodeHangeulBase) ||
     (UniCode > UniCodeHangeulLast)) return false;

	UniCode = UniCode - UniCodeHangeulBase;
	ChoSung = UniCode / (21 * 28);
	UniCode = UniCode % (21 * 28);
	JungSung = UniCode / 28;
	UniCode = UniCode % 28;
	JongSung = UniCode;

	StrLCopy(Han3, ChoSungTbl + ChoSung * 2, 2);
	StrLCopy(Han3 + 2, JungSungTbl + JungSung * 2, 2);
	StrLCopy(Han3 + 4, JongSungTbl + JongSung * 2, 2);

    return true;
}
//---------------------------------------------------------------------------
// function HanDivPas: 한글을 자모로 분해
// Src: 변환할 글자, 예: '갈'
// (Result): 분해된 자모, 예: 'ㄱㅏㄹ', 함수 호출 실패의 경우 ''을 반환한다.
String HanDivPas(String Src)
{
	char Buff[7];

	String Result = "";
    if (Src.Length() == 2) {
		if (HanDiv(Src.c_str(), Buff)) {
        	Buff[6] = NULL;
            Result = String(Buff);
        }
    }

    return Result;
}
//---------------------------------------------------------------------------


