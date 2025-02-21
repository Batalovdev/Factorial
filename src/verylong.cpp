
#include "verylong.h"

void verylong::putvl() const
{
	wchar_t temp[SZ];
    wcscpy(temp, vlstr);
    if (!sign && cmp(verylong(0L)) != 2)
        wcout << L'-';
    wcout << _wcsrev(temp);
}


void verylong::getvl(wchar_t* temp)
{

    if (temp[0] == L'-')
		{ sign = false; wcscpy(vlstr, temp + 1); }
	else
		{ sign = true; wcscpy(vlstr, temp); }
	
    vlen = wcslen(vlstr);
    _wcsrev(vlstr);
}


verylong verylong::operator+ (const verylong v)
{
	verylong res;

    if (sign && v.sign)
	{
        res = natural_addition(v);
        res.sign = true;
	}
    else if (!sign && !v.sign)
	{
        res = natural_addition(v);
        res.sign = false;
	}
    else
	{
        if (cmp(v) == 1)
		{
            res = natural_subtraction(v);
            res.sign = sign;
		}
        else if (cmp(v) == 0)
		{
            res = v.natural_subtraction(*this);
            res.sign = v.sign;
		}
        else
            res = verylong(0L);
	}
	
	return res;
}


verylong verylong::operator- (const verylong v)
{
	verylong res;

    if (sign && !v.sign)
    {
        res = natural_addition(v);
        res.sign = true;
	}
    else if (!sign && v.sign)
    {
        res = natural_addition(v);
        res.sign = false;
	}
    else
	{
        if (cmp(v) == 1)
		{
            res = natural_subtraction(v);
            res.sign = sign;

		}
        else if (cmp(v) == 0)
		{
            res = v.natural_subtraction(*this);
            res.sign = !v.sign;

		}
        else
            res = verylong(0L);
	}

	return res;
}


verylong verylong::natural_addition(const verylong v) const
{
	wchar_t temp[SZ];
	int j;

	int maxlen = (vlen > v.vlen) ? vlen : v.vlen;
    int carry = 0;

    for (j = 0; j < maxlen; j++)
	{
        int d1 = (j > vlen - 1) ? 0 : vlstr[j] - L'0';
        int d2 = (j > v.vlen - 1) ? 0 : v.vlstr[j] - L'0';
        int digitsum = d1 + d2 + carry;
        if (digitsum >= 10)
            { digitsum -= 10; carry = 1; }
		else
            carry = 0;
        temp[j] = digitsum + L'0';
	}
    if (carry == 1)
        temp[j++] = L'1';
    temp[j] = L'\0';


	for (j = wcslen(temp) - 1; j > 0; j--)
	{
        if (temp[j] == L'0')
            temp[j] = L'\0';

		else
            break;
	}

    return verylong(temp);
}


verylong verylong::natural_subtraction(const verylong v) const
{
	wchar_t temp[SZ];
	int j;
    int carry = 0;

    for (j = 0; j < vlen; j++)
	{
        int d1 = vlstr[j] - L'0';
        int d2 = (j > v.vlen - 1) ? 0 : v.vlstr[j] - L'0';
        int digitres = d1 - d2 - carry;

        if (digitres < 0)
            { digitres += 10; carry = 1; }
		else
            carry = 0;
        temp[j] = digitres + L'0';
	}
    temp[j] = L'\0';


	for (j = vlen - 1; j > 0; j--)
	{
        if (temp[j] == L'0')
            temp[j] = L'\0';
		else
            break;
	}

    return verylong(temp);
}


int verylong::cmp(const verylong v) const
{
    if (vlen > v.vlen)
		return 1;
    else if (vlen < v.vlen)
		return 0;
    else
        for (int j = vlen - 1; j >= 0; j--)
        {
			if (vlstr[j] - L'0' > v.vlstr[j] - L'0')
				return 1;
			else if (vlstr[j] - L'0' < v.vlstr[j] - L'0')
				return 0;
		}
	return 2;
}


verylong verylong::operator* (const verylong v)
{
	verylong res;

    res = natural_multiplication(v);
    if ((sign && v.sign) || (!sign && !v.sign))
        res.sign = true;
    else
        res.sign = false;

	return res;
}

verylong verylong::natural_multiplication(const verylong v) const
{
    verylong pprod;
    verylong tempsum;
    for (int j = 0; j < v.vlen; j++)
	{
        int digit = v.vlstr[j] - L'0';
        pprod = multdigit(digit);
        for (int k = 0; k < j; k++)
            pprod = mult10(pprod);
        tempsum = tempsum + pprod;
	}
    return tempsum;
}


verylong verylong::operator/ (const verylong v)
{
	verylong res;

    res = natural_division(v, true);
    if ((sign && v.sign) || (!sign && !v.sign))
        res.sign = true;
    else
        res.sign = false;

	return res;
}


verylong verylong::operator% (const verylong v)
{
	verylong res;
	
    if (cmp(verylong(0L)) == 2)
        res = verylong(0L);
	else
    {
        res = natural_division(v, false);
        res.sign = sign;
	}

	return res;
}


verylong verylong::natural_division(const verylong v, bool flag) const
{	
    if (v.cmp(verylong(0L)) == 2)
	{
		wcout << L"\nОшибка! Делитель не может быть равен нулю!" << endl;
        exit(1);
	}

    if (v.cmp(*this) == 1)
        return (flag) ? verylong(0L) : *this;

	wchar_t res[SZ];
	verylong dividend, divider;
	int j = 0;

	dividend = *this;
	divider = v;

    dividend.sign = true;
    divider.sign = true;

    do {

		verylong prevdiv;
		while (divider.cmp(dividend) == 0 || divider.cmp(dividend) == 2)
		{
			prevdiv = divider;
			divider = mult10(divider);
		}
		divider = prevdiv;

		int digit = 1;
		while (divider.cmp(dividend) == 0 || divider.cmp(dividend) == 2)
		{
			digit++;
			divider = prevdiv.multdigit(digit);
		}
		digit--;
		divider = prevdiv.multdigit(digit);


		res[j++] = digit + L'0';


        dividend = dividend - divider;
		

		divider = v;

	} while (divider.cmp(dividend) == 0 || divider.cmp(dividend) == 2);

    res[j] = L'\0';
    _wcsrev(res);
    return (flag) ? verylong(res) : dividend;
}

// умножение аргумента на 10
verylong verylong::mult10(const verylong v) const
{
	wchar_t temp[SZ];
    for (int j = v.vlen - 1; j >= 0; j--)
        temp[j + 1] = v.vlstr[j];
    temp[0] = L'0';
    temp[v.vlen + 1] = L'\0';
    return verylong(temp);
}

verylong verylong::multdigit(const int d2) const
{
	wchar_t temp[SZ];
	int j, carry = 0;
    for (j = 0; j < vlen; j++)
    {
        int d1 = vlstr[j] - L'0';
        int digitprod = d1 * d2;
        digitprod += carry;
        if (digitprod >= 10)
		{
            carry = digitprod / 10;
            digitprod -= carry * 10;
		}
		else
            carry = 0;
        temp[j] = digitprod + L'0';
	}
    if (carry != 0)
        temp[j++] = carry + L'0';
    temp[j] = L'\0';
    return verylong(temp);
}
