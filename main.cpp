#include <QCoreApplication>
#include<memory>
#include<iostream>

int find(char *образец, char *строка)
{

    for (int i=0;строка[i];++i) {
        for (int j=0;;++j) {
            if (!образец[j]) return i;
            if(строка[i+j]!=образец[j]) break;
        }

    }

    return -1;
}

static int suffix_match(const  char *needle, size_t nlen, size_t offset, size_t suffixlen)
{
    if (offset > suffixlen)
        return needle[offset - suffixlen - 1] != needle[nlen - suffixlen - 1] &&
        memcmp(needle + nlen - suffixlen, needle + offset - suffixlen, suffixlen) == 0;
    else
        return memcmp(needle + nlen - offset, needle, offset) == 0;
}

static size_t max(size_t a, size_t b)
{
    return a > b ? a : b;
}


const char* memmem_boyermoore(const  char* strsear, const size_t strsearc, const  char* strpoi, const size_t strpoic)
{
    size_t *skip = new size_t[strpoic];
    size_t occ[UCHAR_MAX + 1];

    if (strpoic > strsearc || strpoic <= 0 || !strsear || !strpoi)
        return NULL;


    for (size_t a = 0; a < UCHAR_MAX + 1; ++a)
        occ[a] = -1;


    for (size_t a = 0; a < strpoic - 1; ++a)
        occ[strpoi[a]] = a;


    for (size_t a = 0; a < strpoic; ++a)
    {
        size_t offs = strpoic;
        while (offs && !suffix_match(strpoi, strpoic, offs, a))
            --offs;
        skip[strpoic - a - 1] = strpoic - offs;
    }


    for (size_t hpos = 0; hpos <= strsearc - strpoic;)
    {
        size_t npos = strpoic - 1;

        while (strpoi[npos] == strsear[npos + hpos])
        {
            if (npos == 0)
                return strsear + hpos;

            --npos;
        }
        hpos += max(skip[npos], npos - occ[strsear[npos + hpos]]);
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    const  char *str1 = "BoyerMoor algo searching algoritm ret";
        const  char *str2 = "algor";
        const char *str3;
        str3 = memmem_boyermoore(str1, strlen(str1), str2, strlen(str2));
        std::cout << (str3) << std::endl;
        system("pause");

    return 0;
}
