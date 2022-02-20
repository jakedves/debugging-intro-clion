#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define ASCII_OFFSET 48

char *NUMBERS = "0123456789";
char *HEXNUMBERS = "0123456789abcdef";

/**
 * Stores a number variable and whether or not it
 * represents a hex value.
 */
struct Number {
    int value;
    const char *stringRepresentation;
    bool isHex;
    bool isNegative;
};

/**
 * Takes in a string, and creates a deep copy of it without whitespace.
 * We then return a reference of this new string's address on the heap.
 *
 * @param string : String to remove whitespace of
 * @return : Pointer to the char starting the new string on the heap
 */
char* removeWhiteSpace(const char* string) {
    unsigned long int length = strlen(string);
    int index = 0;

    char *newString = (char*) malloc(length * sizeof(char));

    for (int i = 0; i < length; i++) {
        // must not leave gaps, or forget string terminator
        if (string[i] != ' ') {
            newString[index] = string[i];
            index++;
        }
    }
    newString[index] = '\0';

    return newString;
}

/**
 * Returns num to the power of exp, given that exp >= 0
 * @param num : Number to multiply with itself
 * @param exp : Number to raise the base to
 * @return : The final result
 */
int powInt(int num, int exp) {
    int sum = num;
    if (exp == 0) {
        return 1;
    } else if (exp < 0) {
        return -50000; // So error can be detected easily
    }

    // account for the exp = 1 at the start
    for (int j = 0; j < exp - 1; j++) {
        sum *= num;
    }
    return sum;
}

/**
 * Checks if a character is a numerical character
 * @param c : the character
 * @return : If c is a number between 0-9
 */
bool isNumber(char c) {
    for (int i = 0; i < strlen(NUMBERS); i++) {
        if (c == NUMBERS[i]) {
            return true;
        }
    }
    return false;
}

/**
 * Checks if a character is a numerical hex character
 * @param c : the character
 * @return : If c is a number between 0-F
 */
bool isHexNumber(char c) {
    for (int i = 0; i < strlen(HEXNUMBERS); i++) {
        if (c == HEXNUMBERS[i]) {
            return true;
        }
    }
    return false;
}

/**
 * Checks if a string is valid. An invalid string means that the program
 * should set the error and return 0. The implementation of this function
 * means that negative hex values are not handled.
 *
 * i.e. "0x-AB12" will result in an error
 * @param string : The string to check
 * @param hex : If the string is a hex value
 * @return : Whether or not the string is valid
 */
bool stringIsValid(struct Number num) {
    char first = num.isHex ? num.stringRepresentation[2] : num.stringRepresentation[0];
    return (num.isHex) ? isHexNumber(first) : (first == '-' || isNumber(first));
}

/**
 * This function checks if a string represents a hex value,
 * i.e. it is prefixed with "0x". Here it is safe to check
 * the memory, as C short-circuits boolean expressions, and so
 * the value after the first memory location will only be checked
 * if the first memory location holds a "0".
 * @param string: The string to check against
 * @return : If the string represents a hex number or not
 */
bool isHex(const char *string) {
    return (*string == '0' && string[1] == 'x');
}

/**
 * This function takes a look at the number struct we have,
 * and if it represents a negative number, it adjusts 'num' so that
 * it represents a negative number, and points to the beginning of the
 * number value instead.
 * @param num : The Number struct we are working with
 */
void setNegative(struct Number *num) {
    if (num->stringRepresentation[0] == '-') {
        // If negative, point at the first number instead of '-'
        num->stringRepresentation++;
        num->isNegative = true;
    }
}

/**
 * Takes a pointer to a number, and resets the .stringRepresentation
 * pointer if necessary.
 * @param num : The number pointer
 * @param goBack : How much we initially moved it away
 */
void resetPointer(struct Number *num, int goBack) {
    if (num->isNegative) {
        num->stringRepresentation--;
    }
    num->stringRepresentation = num->stringRepresentation - goBack;
}

/**
 * Takes in an array of values, and sums their value multiplied
 * by the base ^ (length - index - 1). Sets the numbers value to this sum.
 * @param base : Which base we wish to use
 * @param num : The reference to our number
 */
void sumBaseN(int base, int count, struct Number *num, int *numbers) {
    // Calculate sum
    int sum = 0;
    for (int i = 0; i < count; i++) {
        int power = count - 1 - i;
        sum += numbers[i] * powInt(base, power);
        printf("SUM: %d, (ADDED %d x %d^%d)\n", sum, numbers[i], base, power);
    }
    if (num->isNegative) {
        sum = -sum;
    }
    num->value = sum;
}

/**
 * Takes in a Number pointer, and uses the .stringRepresentation to calculate
 * the sum of all the deanery digits (0-9) in that number
 * @param num : The number struct we are using
 */
void calculateBase10Sum(struct Number *num) {
    // Need this variable to compute number at index i, x10 ^ (length of number - 1 - i)
    // i.e. s = "1234" means s[0] = "1" so we do 1 x 10 ^ (4 - 1 - 0) = 1000
    int count = 0;

    // max size is the length of the string
    int numbers[strlen(num->stringRepresentation)];
    while (isNumber(*num->stringRepresentation)) {
        // '0' is 48 in ASCII, so we remove that and C does the char -> int conversion automatically
        // string++ means that the string points at the next index, so we always take string[0]
        numbers[count] = num->stringRepresentation[0] - ASCII_OFFSET;
        num->stringRepresentation++;
        count++;
    }

    // Set the value member of number
    sumBaseN(10, count, num, numbers);

    // We have to reset the pointer so that we can free memory properly, also allows us to use it later
    resetPointer(num, count);
}

/**
 * Takes in a number pointer and calculate the sum of the hexadecimal
 * digits (0-f). Only uses lowercase hex as the examples provided.
 * @param num : The number reference we are using
 */
void calculateBase16Sum(struct Number *num) {
    // Need this variable to compute number at index i, x10 ^ (length of number - 1 - i)
    // i.e. s = "1234" means s[0] = "1" so we do 1 x 10 ^ (4 - 1 - 0) = 1000
    int count = 0;

    // max size is the length of the string
    int numbers[strlen(num->stringRepresentation)];
    num->stringRepresentation += 2; // Account for the "0x"
    while (isHexNumber(*num->stringRepresentation)) {
        // '0' is 48 in ASCII, so we remove that and C does the char -> int conversion automatically
        // 'a' is 97 in ASCII, but represents 10, so we also subtract 87, if in "abcdef"

        // string++ means that the string points at the next index, so we always take string[0]
        int letterOffset = 87;
        int asciiNumber = num->stringRepresentation[0] - ASCII_OFFSET;
        int asciiCharacter = num->stringRepresentation[0] - letterOffset;

        if (asciiNumber > 9) { // If not in 0-9, must be in a-f
            numbers[count] = asciiCharacter;
        } else {
            numbers[count] = asciiNumber;
        }
        num->stringRepresentation++;
        count++;
    }

    // Sets the value member of number
    sumBaseN(16, count, num, numbers);

    // We have to reset the pointer so that we can free memory properly, also allows us to use it later
    resetPointer(num, count + 2); // Account for the "0x" we removed
}

/**
 * Reads an ASCII character string and returns the integer
 * value that this string represents. This function doesn't perform
 * or compute arithmetic, but can read negative numbers. When a conversion
 * cannot be done, this function returns 0.
 *
 * e.g. "-5" will return -5
 * however "---5" will error and return 0
 *
 * @param string : A pointer to the start of the string being read
 * @param error : The reference to the error value (set to -1 on fail)
 * @return : The integer value of the string if possible
 */
int atoi_ex(const char *string, int *error) {
    struct Number number;
    number.isHex = isHex(string);
    number.isNegative = false; // Assume positive, updated later
    number.stringRepresentation = removeWhiteSpace(string);

    // Check if the string is invalid, and free memory, and set error if so
    if (!stringIsValid(number)) {
        *error = -1;
        free((void *)number.stringRepresentation);
        number.stringRepresentation = NULL;
        return 0;
    }

    // Calculate the values
    if (number.isHex) {
        calculateBase16Sum(&number);
    } else {
        setNegative(&number);
        calculateBase10Sum(&number);
    }

    // Free memory we allocated in the heap
    free((void *)number.stringRepresentation);
    number.stringRepresentation = NULL;

    return number.value;
}

/**
 * Tests values against expected values
 * @return : 0 on success
 */
int main() {
    int error_value = 0;
    int *err = &error_value;
    char strings[12][7] = {"123", "-1", "456abc", "abc", "0003", "", "0", "  123",
                           "0x123", "0xabc", "0x456g", "0xghi"};

    for (int i = 0; i < 12; i++) {
        char *string = strings[i];
        int value = atoi_ex(string, err);
        printf("String: %s\nError: %d\nReturn: %d\n\n", string, error_value, value);
        error_value = 0;
    }

    return 0;
}