#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void menu(void);
void decimalToBinary(int); 
void decimalToHexadecimal(int);
void decimalToOctal(int);
int binaryToDecimal(long long);

int main(int argc, char const *argv[])
{
	menu();

	return 0;
}

void menu(void) {
	// int decimalNumber;
    // printf("Ingrese un número decimal: ");
    // scanf("%d", &decimalNumber);
    // printf("Representación binaria: ");
    // decimalToBinary(decimalNumber);

    // int decimalNumber;
    // printf("Ingrese un número decimal: ");
    // scanf("%d", &decimalNumber);
    // decimalToHexadecimal(decimalNumber);

    // int decimalNumber;
    // printf("Ingrese un número decimal: ");
    // scanf("%d", &decimalNumber);
    // decimalToOctal(decimalNumber);

    // long long binaryNumber;
    // printf("Ingrese un número binario: ");
    // scanf("%lld", &binaryNumber);
    // int decimalNumber = binaryToDecimal(binaryNumber);
    // printf("Representación decimal: %d\n", decimalNumber);

    // long long binaryNumber;
    // printf("Ingrese un número binario: ");
    // scanf("%lld", &binaryNumber);
    // binaryToHexadecimal(binaryNumber);

    // long long binaryNumber;
    // printf("Ingrese un número binario: ");
    // scanf("%lld", &binaryNumber);
    // binaryToOctal(binaryNumber);

    // char hexadecimalNumber[100];
    // printf("Ingrese un número hexadecimal: ");
    // scanf("%s", hexadecimalNumber);
    // int decimalNumber = hexadecimalToDecimal(hexadecimalNumber);
    // if (decimalNumber == -1) {
    //     printf("Número hexadecimal inválido\n");
    // } else {
    //     printf("Representación decimal: %d\n", decimalNumber);
    // }

	// char hexadecimalNumber[100];
    // printf("Ingrese un número hexadecimal: ");
    // scanf("%s", hexadecimalNumber);
    // hexadecimalToBinary(hexadecimalNumber);

    // char hexadecimalNumber[100];
    // printf("Ingrese un número hexadecimal: ");
    // scanf("%s", hexadecimalNumber);
    // hexadecimalToOctal(hexadecimalNumber);

	// int octalNumber;
    // printf("Ingrese un número octal: ");
    // scanf("%d", &octalNumber);
    // int decimalNumber = octalToDecimal(octalNumber);
    // printf("Representación decimal: %d\n", decimalNumber);

    // int octalNumber;
    // printf("Ingrese un número octal: ");
    // scanf("%d", &octalNumber);
    // octalToBinary(octalNumber);

	// char octalNumber[100];
    // printf("Ingrese un número octal: ");
    // scanf("%s", octalNumber);
    // octalToHexadecimal(octalNumber);
}

// Función para convertir un número decimal a binario
void decimalToBinary(int n) {
    // Caso base: si el número es cero, no hay más divisiones para realizar
    if (n == 0) {
        return;
    } else {
        // Llamada recursiva para dividir el número por 2
        decimalToBinary(n / 2);
        
        // Imprimir el residuo en cada llamada recursiva
        printf("%d", n % 2);
    }
}

// Función para convertir un número decimal en hexadecimal
void decimalToHexadecimal(int decimalNumber) {
    char hexadecimalNumber[100];
    int i = 0;
    
    while (decimalNumber != 0) {
        int remainder = decimalNumber % 16;
        
        if (remainder < 10) {
            hexadecimalNumber[i] = remainder + '0';
        } else {
            hexadecimalNumber[i] = remainder + 'A' - 10;
        }
        
        decimalNumber /= 16;
        i++;
    }
    
    printf("Representación hexadecimal: ");
    
    for (int j = i - 1; j >= 0; j--) {
        printf("%c", hexadecimalNumber[j]);
    }
    
    printf("\n");
}

// Función para convertir un número decimal en octal
void decimalToOctal(int decimalNumber) {
    int octalNumber[100];
    int i = 0;
    
    while (decimalNumber != 0) {
        octalNumber[i] = decimalNumber % 8;
        decimalNumber /= 8;
        i++;
    }
    
    printf("Representación octal: ");
    
    for (int j = i - 1; j >= 0; j--) {
        printf("%d", octalNumber[j]);
    }
    
    printf("\n");
}

// Función para convertir un número binario en decimal
int binaryToDecimal(long long binaryNumber) {
    int decimalNumber = 0, i = 0, remainder;
    
    while (binaryNumber != 0) {
        remainder = binaryNumber % 10;
        binaryNumber /= 10;
        decimalNumber += remainder * pow(2, i);
        ++i;
    }
    
    return decimalNumber;
}

// Función para convertir un número binario en hexadecimal
void binaryToHexadecimal(long long binaryNumber) {
    char hexadecimalNumber[100];
    int i = 0, j;
    long long remainder, decimalNumber = 0;
    
    // Convertir binario a decimal
    while (binaryNumber != 0) {
        remainder = binaryNumber % 10;
        binaryNumber /= 10;
        decimalNumber += remainder * pow(2, i);
        ++i;
    }
    
    i = 0;
    
    // Convertir decimal a hexadecimal
    while (decimalNumber != 0) {
        remainder = decimalNumber % 16;
        
        if (remainder < 10) {
            hexadecimalNumber[i] = remainder + '0';
        } else {
            hexadecimalNumber[i] = remainder + 'A' - 10;
        }
        
        decimalNumber /= 16;
        i++;
    }
    
    printf("Representación hexadecimal: ");
    
    for (j = i - 1; j >= 0; j--) {
        printf("%c", hexadecimalNumber[j]);
    }
    
    printf("\n");
}

// Función para convertir un número binario en octal
void binaryToOctal(long long binaryNumber) {
    int octalNumber = 0, decimalNumber = 0, i = 0;

    // Convertir binario a decimal
    while (binaryNumber != 0) {
        decimalNumber += (binaryNumber % 10) * pow(2, i);
        ++i;
        binaryNumber /= 10;
    }

    i = 1;

    // Convertir decimal a octal
    while (decimalNumber != 0) {
        octalNumber += (decimalNumber % 8) * i;
        decimalNumber /= 8;
        i *= 10;
    }

    printf("Representación octal: %d\n", octalNumber);
}

/****** HEXADECIMAL A DECIMAL ******/
// Función para convertir un dígito hexadecimal en su equivalente decimal
int hexDigitToDecimal(char digit) {
    if (digit >= '0' && digit <= '9') {
        return digit - '0';
    } else if (digit >= 'A' && digit <= 'F') {
        return digit - 'A' + 10;
    } else if (digit >= 'a' && digit <= 'f') {
        return digit - 'a' + 10;
    } else {
        return -1;  // Carácter inválido
    }
}

// Función para convertir un número hexadecimal en decimal
int hexadecimalToDecimal(const char* hexadecimalNumber) {
    int decimalNumber = 0;
    int length = 0;
    
    while (hexadecimalNumber[length] != '\0') {
        length++;
    }
    
    int power = 0;
    
    for (int i = length - 1; i >= 0; i--) {
        int digitValue = hexDigitToDecimal(hexadecimalNumber[i]);
        
        if (digitValue == -1) {
            return -1;  // Carácter inválido encontrado
        }
        
        decimalNumber += digitValue * pow(16, power);
        power++;
    }
    
    return decimalNumber;
}
/****** -------------------- ******/

/****** HEXADECIMAL A BINARIO ******/
// Función para convertir un dígito hexadecimal en su equivalente binario
char* hexDigitToBinary(char digit) {
    switch (digit) {
        case '0':
            return "0000";
        case '1':
            return "0001";
        case '2':
            return "0010";
        case '3':
            return "0011";
        case '4':
            return "0100";
        case '5':
            return "0101";
        case '6':
            return "0110";
        case '7':
            return "0111";
        case '8':
            return "1000";
        case '9':
            return "1001";
        case 'A':
        case 'a':
            return "1010";
        case 'B':
        case 'b':
            return "1011";
        case 'C':
        case 'c':
            return "1100";
        case 'D':
        case 'd':
            return "1101";
        case 'E':
        case 'e':
            return "1110";
        case 'F':
        case 'f':
            return "1111";
        default:
            return "";
    }
}

// Función para convertir un número hexadecimal en binario
void hexadecimalToBinary(const char* hexadecimalNumber) {
    int length = strlen(hexadecimalNumber);
    
    printf("Representación binaria: ");
    
    for (int i = 0; i < length; i++) {
        char* binary = hexDigitToBinary(hexadecimalNumber[i]);
        
        if (strcmp(binary, "") == 0) {
            printf("Número hexadecimal inválido\n");
            return;
        }
        
        printf("%s", binary);
    }
    
    printf("\n");
}
/****** -------------------- ******/

/****** HEXADECIMAL A OCTAL ******/
// Función para convertir un dígito hexadecimal en su equivalente binario
char* hexDigitToBinary(char digit) {
    switch (digit) {
        case '0':
            return "0000";
        case '1':
            return "0001";
        case '2':
            return "0010";
        case '3':
            return "0011";
        case '4':
            return "0100";
        case '5':
            return "0101";
        case '6':
            return "0110";
        case '7':
            return "0111";
        case '8':
            return "1000";
        case '9':
            return "1001";
        case 'A':
        case 'a':
            return "1010";
        case 'B':
        case 'b':
            return "1011";
        case 'C':
        case 'c':
            return "1100";
        case 'D':
        case 'd':
            return "1101";
        case 'E':
        case 'e':
            return "1110";
        case 'F':
        case 'f':
            return "1111";
        default:
            return "";
    }
}

// Función para convertir un número hexadecimal en octal
void hexadecimalToOctal(const char* hexadecimalNumber) {
    int length = strlen(hexadecimalNumber);
    char binaryNumber[100] = "";
    
    // Convertir hexadecimal a binario
    for (int i = 0; i < length; i++) {
        char* binary = hexDigitToBinary(hexadecimalNumber[i]);
        
        if (strcmp(binary, "") == 0) {
            printf("Número hexadecimal inválido\n");
            return;
        }
        
        strcat(binaryNumber, binary);
    }
    
    // Convertir binario a octal
    length = strlen(binaryNumber);
    int padding = 3 - (length % 3);
    
    if (padding == 3) {
        padding = 0;
    }
    
    for (int i = 0; i < padding; i++) {
        printf("0");
    }
    
    for (int i = padding; i < length; i += 3) {
        int digit = (binaryNumber[i] - '0') * 4 + (binaryNumber[i + 1] - '0') * 2 + (binaryNumber[i + 2] - '0');
        printf("%d", digit);
    }
    
    printf("\n");
}
/****** -------------------- ******/

/****** OCTAL A DECIMAL ******/
// Función para convertir un dígito octal en su equivalente decimal
int octalDigitToDecimal(int digit) {
    int decimal = 0, i = 0;
    
    while (digit != 0) {
        decimal += (digit % 10) * pow(8, i);
        ++i;
        digit /= 10;
    }
    
    return decimal;
}

// Función para convertir un número octal en decimal
int octalToDecimal(int octalNumber) {
    int decimalNumber = 0, i = 0;
    
    while (octalNumber != 0) {
        int digit = octalNumber % 10;
        decimalNumber += octalDigitToDecimal(digit) * pow(10, i);
        ++i;
        octalNumber /= 10;
    }
    
    return decimalNumber;
}
/****** -------------------- ******/

/****** OCTAL A DECIMAL ******/
// Función para convertir un dígito octal en su equivalente binario de 3 bits
const char* octalDigitToBinary(int digit) {
    switch (digit) {
        case 0:
            return "000";
        case 1:
            return "001";
        case 2:
            return "010";
        case 3:
            return "011";
        case 4:
            return "100";
        case 5:
            return "101";
        case 6:
            return "110";
        case 7:
            return "111";
        default:
            return "";
    }
}

// Función para convertir un número octal en binario
void octalToBinary(int octalNumber) {
    printf("Representación binaria: ");
    
    while (octalNumber != 0) {
        int digit = octalNumber % 10;
        const char* binary = octalDigitToBinary(digit);
        
        if (binary[0] == '\0') {
            printf("Número octal inválido\n");
            return;
        }
        
        printf("%s", binary);
        octalNumber /= 10;
    }
    
    printf("\n");
}
/****** -------------------- ******/

/****** OCTAL A HEXADECIMAL ******/
// Función para convertir un dígito octal en su equivalente hexadecimal
char octalDigitToHex(char digit) {
    switch (digit) {
        case '0':
            return '0';
        case '1':
            return '1';
        case '2':
            return '2';
        case '3':
            return '3';
        case '4':
            return '4';
        case '5':
            return '5';
        case '6':
            return '6';
        case '7':
            return '7';
        default:
            return '\0';
    }
}

// Función para convertir un número octal en hexadecimal
void octalToHexadecimal(const char* octalNumber) {
    int length = strlen(octalNumber);
    int padding = length % 3;
    
    if (padding > 0) {
        padding = 3 - padding;
    }
    
    for (int i = 0; i < padding; i++) {
        printf("0");
    }
    
    for (int i = 0; i < length; i += 3) {
        char digit1 = octalNumber[i];
        char digit2 = octalNumber[i + 1];
        char digit3 = octalNumber[i + 2];
        
        char hexDigit = octalDigitToHex(digit1);
        
        if (hexDigit == '\0') {
            printf("Número octal inválido\n");
            return;
        }
        
        printf("%c", hexDigit);
        
        hexDigit = octalDigitToHex(digit2);
        
        if (hexDigit == '\0') {
            printf("Número octal inválido\n");
            return;
        }
        
        printf("%c", hexDigit);
        
        hexDigit = octalDigitToHex(digit3);
        
        if (hexDigit == '\0') {
            printf("Número octal inválido\n");
            return;
        }
        
        printf("%c", hexDigit);
    }
    
    printf("\n");
}
/****** -------------------- ******/


