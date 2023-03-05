#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE (1 << CHAR_BIT) /* normalmente 256 */

/* Préprocessamento de badmatch */
void preBmBc(char* pat, size_t lpat, int bmBc[]) {
    size_t i;
    for (i = 0; i < ALPHABET_SIZE; ++i)
        bmBc[i] = lpat;
    for (i = 0; i < lpat - 1; ++i)
        bmBc[pat[i]] = lpat - i - 1;
}

void RAITA(char* pat, size_t lpat, char* s, size_t n) {
    /* tabela de bad-matches */
    int bmBc[ALPHABET_SIZE];

    /* checando para casos extremos/erros */
    if (lpat == 0 || lpat > n)
        return false;

    if (lpat == 1) {
        char* match_ptr = s;
        while (match_ptr < s + n) {
            match_ptr = (char*)memchr(match_ptr, pat[0], n - (match_ptr - s));
            if (match_ptr != NULL) {
                printf("%d", match_ptr - s);
                match_ptr++;
            }
            else
                return false;
        }
    }

    preBmBc(pat, lpat, bmBc);

    /* caracteres de pré-verificação */
    char firstCh = pat[0];
    char middleCh = pat[lpat / 2];
    char lastCh = pat[lpat - 1];

    /* busca */
    int j = 0;
    while (j <= n - lpat) {
        char c = s[j + lpat - 1];
        /* faz a pré-verificação e compara o padrão e o texto */
        if (lastCh == c && middleCh == s[j + lpat / 2] && firstCh == s[j] && memcmp(&pat[1], &s[j + 1], lpat - 2) == 0)
            printf("%d", j);
        j += bmBc[c];
    }
}

int main()
{
    char txt[] = "ABABDABACDABABCABAB";
    char pat[] = "ABABCABAB";
    RAITA(pat, strlen(pat),  txt, strlen(txt));
    return 0;
}
