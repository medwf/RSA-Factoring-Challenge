#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

void calc_factorise(mpz_t number, mpz_t result)
{
    mpz_t div;
    mpz_init_set_ui(div, 2);

    while (1)
    {
        mpz_t remainder;
        mpz_init(remainder);
        mpz_mod(remainder, number, div);

        if (mpz_cmp_ui(remainder, 0) == 0)
        {
            mpz_div(result, number, div);
            break;
        }

        mpz_add_ui(div, div, 1);
        mpz_clear(remainder);
    }

    mpz_clear(div);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(1);
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(1);
    }

    char line[256]; // Assuming a maximum line length of 256 characters
    mpz_t number, result, res;
    mpz_init(number);
    mpz_init(result);
    mpz_init(res);

    while (fgets(line, sizeof(line), file))
    {
        mpz_set_str(number, line, 10);
        calc_factorise(number, result);
        mpz_div(res, number, result);
        gmp_printf("%Zd=%Zd*%Zd\n", number, result, res);
    }

    mpz_clear(number);
    mpz_clear(result);
    mpz_clear(res);
    fclose(file);
    return 0;
}
