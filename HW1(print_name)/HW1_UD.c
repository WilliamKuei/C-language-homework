#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h> 
#include<limits.h>
#include<math.h>
#include<stdbool.h> 
#include<iso646.h>

void print_word(const char* name[]){
    for(int i=0;i<13;i++){
        printf("%s\n", name[i]);
    }
    printf("\n");
}

int main() {
const char* name1[]= {  " ***      *         ",
                        " * *  * * * * *     ",
                        " **       *         ",
                        " **   * * * * *     ",
                        " * *  * * * * *     ",
                        " * *  * * * * *     ",
                        " **   *   *   *     ",
                        " *    * * * * *     ",
                        " *       ***        ",
                        " *     *  *  *      ",
                        " *    *   *   *     ",
                        " *   *    *    *    ",
                        " *  *     *     *   ",
                    };

const char* name2[]= {  "          *         ",
                        "    * * * * * * *   ",
                        "       *  *  *      ",
                        "       *     *      ",
                        "       *  *  *      ",
                        "                    ",
                        " * * * * * * * * * *",
                        " *     *     *     *",
                        " *     *     *     *",
                        "      *      *      ",
                        "     *       *     *",
                        "  * *        *  * * ",
                        "                    ",
                    };
                    
const char* name3[]= {  "   *         *   *  ",
                        "  *           *  *  ",
                        " * * * * *  *    *  ",
                        " *   *   *   *   *  ",
                        " * * * * *       *  ",
                        " *   *   * * * * * *",
                        " * * * * *       *  ",
                        "     *     *     *  ",
                        "    **    *  *   *  ",
                        "   * *   * * *   *  ",
                        "  *  *        *  * *",
                        " *   *  *  *  *  * *",
                        "                    ",
                    };

print_word(name1);
print_word(name2);
print_word(name3);

}
