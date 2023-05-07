#import <array>
#import <termios.h>
#import <string.h>
#import <stdio.h>
#import <stdlib.h>
#import <iostream>
#import <unistd.h>

// Коды ошибок
#define GENERAL_ERROR   -1
#define OK               0

class utilites {
public:
    std::string exec(const char *cmd) {
        std::array<char, 128> buff;
        std::string result;

        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);

        if (!pipe) exit(GENERAL_ERROR);

        while (fgets(buff.data(), buff.size(), pipe.get()) != nullptr)
            result += buff.data();

        return result;
    }

    int _getch() {
        struct termios oldt, newt;
        int ch = 0;

        tcgetattr(STDIN_FILENO, &oldt);

        newt = oldt;
        newt.c_lflag &= ~( ICANON | ECHO );

        tcsetattr( STDIN_FILENO, TCSANOW, &newt );

        ch = getchar();

        tcsetattr( STDIN_FILENO, TCSANOW, &oldt );

        return ch;
    }

    std::string cmd(const char *ofr, std::string ret) {
        std::cout << ofr;
        std::cin >> ret;

        return ret;
    }

    void dump(const unsigned char *data_buffer, size_t length) {
        unsigned char byte;
        size_t i, j;

        for(int i = 0; i < length; i++) {
            printf("%02 ", data_buffer[i]);

            if (((i % 16) == 15) || (i == length - 1)) {
                for (j = 0; j < 15 - (i % 16); j++)
                    std::cout << " ";
                std::cout << "| ";

                for (j = (i - (i % 16)); j <= i; j++) {
                    byte = data_buffer[i];
                    if ((byte > 31) && (byte < 127))
                        std::cout << byte;
                    else
                        std::cout << ".";
                }
                std::cout << std::endl;
            }
        }
    }
};