/***********************************************************************************************
Note: At the computing power IDE gives, my code cracked "ZZZZ" in ~27 seconds.
        It cracked "aZZZZ" in ~52s; "bZZZZ" in ~90; "cZZZZ" in ~125s.
        This gives ~35s for each initial character of a 5-character password.
        Extrapolating, "ZZZZZ" will take 51 * 35 = 1785 seconds longer than "aZZZZ."
        Therefore, the maximum amount of time it should take to crack a password is ~31 minutes.
.
        So you don't have to wait, I am including below the passwords this code ended up finding:

        anushree:50xcIMJ0y.RXo -> YES
        brian:50mjprEcqC/ts -> CA
        bjbrown:50GApilQSG3E2 -> UPenn
        lloyd:50n0AAUD.pL8g -> lloyd
        malan:50CcfIk1QrPr6 -> maybe
        maria:509nVI8B9VfuA -> TF
        natmelo:50JIIyhDORqMU -> nope
        rob:50JGnXUgaafgc -> ROFL
        stelios:51u8F0dkeDSbY -> NO
        zamyla:50cI2vYkF0YU2 -> LOL

*************************************************************************************************/

// Cracks a command-line inputted password of max 5 characters hashed with crypt() function
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <crypt.h>

#define _XOPEN_SOURCE
#define HASH_LENGTH 13
#define MAX_PASSWORD 5
// Strings start off at place 0
#define INITIAL_LETTER 0

// Absolutely necessary to declare global string for recursive function to work
// Otherwise, would need to copy strings 4 times per password, which is VERY computationally expensive
char guessing_password[MAX_PASSWORD + 1];

int crack(int, int, string, string);

int main(int argc, char *argv[])
{
    // Check for hashed password (and only hashed password) in command line
    if (argc != 2)
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }

    // Determine salt
    char salt[2];
    salt[0] = argv[1][0];
    salt[1] = argv[1][1];

    // Check password lengths 1-5
    for (int i = 1; i < 6; i++)
    {
        if (crack(i, INITIAL_LETTER, salt, argv[1]) == 0)
        {
            return 0;
        }
    }
}


// Create and check all passwords of a given length
int crack(int length, int letter_of_password, string salt, string crack_this)
{
    // Check whether reached end of password
    if (letter_of_password != length)
    {
        // Lower case check
        for (int i = 'a'; i <= 'z'; i++)
        {
            // Set letter
            guessing_password[letter_of_password] = i;

            // Set future letters and check whether password cracked
            if (crack(length, letter_of_password + 1, salt, crack_this) == 0)
            {
                return 0;
            }
        }

        // Upper case check
        for (int i = 'A'; i <= 'Z'; i++)
        {
            // Set letter
            guessing_password[letter_of_password] = i;

            // Set future letters and check whether password cracked
            if (crack(length, letter_of_password + 1, salt, crack_this) == 0)
            {
                return 0;
            }
        }
    }

    // At end of password, check whether password cracked
    else
    {
        // Mark end of string
        guessing_password[length] = '\0';

        // Hash password
        char *hash = crypt(guessing_password, salt);

        // Compare hash
        if (strcmp(hash, crack_this) == 0)
        {
            printf("%s\n", guessing_password);
            return 0;
        }
        else
        {
            return 1;
        }
    }

    return 2;
}