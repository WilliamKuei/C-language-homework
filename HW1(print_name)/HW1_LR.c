#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h> 
#include<limits.h>
#include<math.h>
#include<stdbool.h> 
#include<iso646.h> 
void print_word(const char* name1[],const char* name2[],const char* name3[]){
    for(int i=0;i<13;i++){
        printf("%s  ", name1[i]);
        printf("%s  ", name2[i]);
        printf("%s  \n", name3[i]);
    }
    printf("\n");
}
int main() {
const char* name1[]= {  " ***      *         ",
                        " * *  * * * * *     ",
                        "  *       *        ",
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
print_word(name1,name2,name3);


}
