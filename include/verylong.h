
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;

const int SZ = 1000;

class verylong
{
private:
    wchar_t vlstr[SZ];
    int vlen;
    bool sign;
    verylong natural_addition(const verylong) const;
	verylong natural_subtraction(const verylong) const;
	int cmp(const verylong) const;
	verylong natural_multiplication(const verylong) const;
	verylong natural_division(const verylong, bool) const;
    verylong multdigit(const int) const;
    verylong mult10(const verylong) const;
public:
    verylong() : vlen(0), sign(true)
		{ vlstr[0] = L'\0'; }
    verylong(const wchar_t s[SZ])
		{ wcscpy(vlstr, s); vlen = wcslen(s); sign = true; }
    verylong(const long n)
	{
        if (n < 0)
			sign = false;
		else
            sign = true;
        _ltow(abs(n), vlstr, 10);
        _wcsrev(vlstr);

        vlen = wcslen(vlstr);
	}
    void putvl() const;
    void getvl(wchar_t* temp);
    verylong operator+ (const verylong);
    verylong operator- (const verylong);
    verylong operator* (const verylong);
    verylong operator/ (const verylong);
    verylong operator% (const verylong);
};
