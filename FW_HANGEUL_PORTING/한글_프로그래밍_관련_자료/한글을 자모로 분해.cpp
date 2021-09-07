bool HanDiv(char *Han, char *Han3);
String HanDivPas(String Src);

//---------------------------------------------------------------------------
// HanDivPas, HanDiv
// Programmed by Jounlai Cho (jounlai@yahoo.com)

// function HanDiv: �ѱ��� �ڸ�� ����
// Han: ��ȯ�� ����, PChar Ÿ��
// Han3: ���ص� �ڸ�, PChar Ÿ��
// (Result): �Լ� ȣ�� ����(True), ����(False)
// *����: ���� Han�� Han3�� ����Ű�� �޸� ������ ���� 2, 6����Ʈ��
// �Ҵ�Ǿ� �־�� �Ѵ�. �׸��� Han�� Han3 ��� null-���� ���ڿ��� �ƴϴ�.
bool HanDiv(char *Han, char *Han3)
{
    const char *ChoSungTbl    = "��������������������������������������";
    const char *JungSungTbl	= "�������¤äĤŤƤǤȤɤʤˤ̤ͤΤϤФѤҤ�";
    const char *JongSungTbl	= "  ������������������������������������������������������";
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
// function HanDivPas: �ѱ��� �ڸ�� ����
// Src: ��ȯ�� ����, ��: '��'
// (Result): ���ص� �ڸ�, ��: '������', �Լ� ȣ�� ������ ��� ''�� ��ȯ�Ѵ�.
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


