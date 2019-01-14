#ifdef _WIN32
#include <conio.h>
#else
#include <curses.h>
#endif

#include <cstdio>
#include <iostream>
#include <math.h>

using namespace std;

#ifdef _WIN32
static int __BACKGROUND = BLACK;
static int __FOREGROUND = WHITE;

void SetForegroundColor(int color) {
      __FOREGROUND = color;
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color + (__BACKGROUND << 4));
}

void SetBackgroundColor(int color) {
     __BACKGROUND = color;
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), __FOREGROUND + (color << 4));
}
#endif

#ifdef _WIN32
enum Color {
    NONE = 0,
    BLACK,
    RED = 12,
    GREEN = 10,
    YELLOW = 14,
    BLUE = 9,
    MAGENTA = 13,
    CYAN = 11,
    WHITE = 15
};
#else
enum Color {
  	NONE = 0,
  	BLACK,
  	RED,
  	GREEN,
  	YELLOW,
  	BLUE,
  	MAGENTA,
  	CYAN,
  	WHITE
};
#endif

void Write(Color foreground, Color background, string text) {
#ifdef _WIN32
    SetForegroundColor(foreground);
    SetBackgroundColor(background);
#else
    init_pair(1, foreground, background);
    attron(COLOR_PAIR(1));
#endif

    cout << text << "\n";

#ifdef _WIN32
    SetForegroundColor(WHITE);
    SetBackgroundColor(BLACK);
#else
    attroff(COLOR_PAIR(1));
#endif
}

void ShowMenu(int extra = 2) {
    Write(WHITE, BLACK,       "0 - BLACK      (0%)");
    Write(BLACK, RED,         "1 - BROWN      (1%)");
    Write(BLACK, RED,         "2 - RED        (2%)");
    if (extra <= 2) {
        Write(BLACK, YELLOW,  "3 - ORANGE         ");
        Write(BLACK, YELLOW,  "4 - YELLOW         ");
    }
    Write(BLACK, GREEN,       "5 - GREEN    (0.5%)");
    Write(BLACK, BLUE,        "6 - BLUE    (0.25%)");
    Write(BLACK, MAGENTA,     "7 - MAGENTA  (0.1%)");
    Write(BLACK, WHITE,       "8 - GREY    (0.05%)");
    if (extra <= 2) {
        Write(BLACK, WHITE,   "9 - WHITE          ");
    }
    if (extra >= 2) {
        Write(BLACK, YELLOW,  "10 - GOLD      (5%)");
        Write(BLACK, WHITE,   "11 - SILVER   (10%)");
    }
    if (extra >= 3) {
        Write(WHITE, BLACK,   "12 - NO COLOR (20%)");
    }
}

char GetUoM(int uni) {
    switch(uni) {
        case 0:
            return NULL;
            break;
        case 1:
            return 'K';
            break;
        case 2:
            return 'M';
            break;
        default:
            break;
    }
}

int ConvertColor(int color) {
    switch(color) {
        case 0: return 0; break;
        case 1: return 6; break;
        case 2: return 12; break;
        case 3: return 4; break;
        case 4: return 14; break;
        case 5: return 10; break;
        case 6: return 9; break;
        case 7: return 13; break;
        case 8: return 7; break;
        case 9: return 15; break;
    }
}

int main() {
    int v;
    double r;
    int mode;
    int uni = 0;

#ifndef _WIN32
    start_color();
#endif

    printf("1-Colors -> Value\n");
    printf("2-Value -> Colors\n");
    scanf("%i", &v);

    if (v == 1) {
        printf("1 - 4 colors resistor\n");
        printf("2 - 5 colors resistor\n");
        scanf("%i", &mode);

        printf("Choose the first color of the resistor:\n");
        ShowMenu(1);
        scanf("%i", &v);

        r = v*10;

        printf("Choose the second color of the resistor:\n");
        ShowMenu(1);
        scanf("%i", &v);

        r += v;

        if (mode == 2) {
            printf("Choose the third color of the resistor:\n");
            ShowMenu(1);
            scanf("%i", &v);

            r *= 10;
            r += v;
        }

        printf("Choose the value of the multiplier color of the resistor:\n");
        ShowMenu(2);
        scanf("%i", &v);

        if (v >= 10) {
            v -= 9;
            v *= -1;
        }

        r *= pow(10, v);

        printf("Choose the value of the tolerance color of the resistor:\n");
        ShowMenu(3);
        scanf("%i", &v);

        float p;

        switch(v) {
            case 0:
                p = 0;
                break;
            case 1:
                p = 1;
                break;
            case 2:
                p = 2;
                break;
            case 5:
                p = 0.5;
                break;
            case 6:
                p = 0.25;
                break;
            case 7:
                p = 0.1;
                break;
            case 8:
                p = 0.05;
                break;
            case 10:
                p = 5;
                break;
            case 11:
                p = 10;
                break;
            case 12:
                p = 20;
                break;
            default:
                break;
        }

        while(fmod(r, 1000) == 0) {
            r /= 1000;
            uni++;
        }

        printf("Nominal Value:%.2lf %c ohms\n", r, GetUoM(uni));
        printf("Minimum Value:%.2lf %c ohms\n", r-r*(p/100), GetUoM(uni));
        printf("Maximum Value:%.2lf %c ohms\n", r+r*(p/100), GetUoM(uni));
    } else if (v == 2) {
        printf("Choose the resistor value in ohms:\n");
        scanf("%lf", &r);

        while(fmod(r, 10) == 0) {
            r /= 10;
            uni++;
        }

        if (r >= 100) {
            cout << 5 << endl;
            Write(BLACK, (Color)ConvertColor((int)((r - fmod(r, 100)) / 100)),          "           ");
            Write(BLACK, (Color)ConvertColor((int)((fmod(r, 100) - fmod(r, 10)) / 10)), "           ");
            Write(BLACK, (Color)ConvertColor(fmod(r, 10)),                              "           ");
            Write(BLACK, (Color)ConvertColor(uni),                                      "           ");
        } else {
            Write(BLACK, (Color)ConvertColor(((r - fmod(r, 10)) / 10)),                 "           ");
            Write(BLACK, (Color)ConvertColor(fmod(r, 10)),                              "           ");
            Write(BLACK, (Color)ConvertColor(uni),                                      "           ");
        }
    }

    getch();
    return 0;
}
