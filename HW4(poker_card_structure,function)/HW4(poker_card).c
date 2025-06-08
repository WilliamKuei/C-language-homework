#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef union {
    struct {
        unsigned hand_card_Type : 2;
        unsigned hand_card_Number : 6;
    };
    unsigned char c;
} PKCARD;

int deal_cards(int n, PKCARD *PK){
    int hand_card_Num=0;
    bool draw_Finish=false;
    int rand_Card=0,card_Type=0,card_Number=0,Card=0;

    do{
        do{
            rand_Card=rand()%52;
            card_Type=rand_Card/13;
            card_Number=rand_Card%13+1;
            Card=(card_Number<<2)+card_Type;
            draw_Finish=false;
            for(int i=0;i<hand_card_Num;i++){
                if(PK[i].c==Card){
                    draw_Finish=true;
                    break;
                }
            }
        }while(draw_Finish==true);
        PK[hand_card_Num].c=Card;
        hand_card_Num++;
    }while(hand_card_Num<5);
    return n;
};
void sort_cards(PKCARD *PK, int N){
    int sort_max_value=PK[0].c;
    for(int i=0;i<5;i++){
        for(int k=0;k<4;k++){
            if(PK[k].c>PK[k+1].c){
                sort_max_value=PK[k].c;
                PK[k].c=PK[k+1].c;
                PK[k+1].c=sort_max_value;
            }
        }
    }
};
void print_cards(PKCARD *PK, int N){
    char* hand_card_Type[5];
    for (int i=0;i<5;i++){
        switch (PK[i].hand_card_Type&3)
        {
        case 0:
            hand_card_Type[i]="Spades";
            break;
        case 1:
            hand_card_Type[i]="Diamond";
            break;
        case 2:
            hand_card_Type[i]="Heart";
            break;
        case 3:
            hand_card_Type[i]="Club";
            break;
    
        default:
            break;
        }
        PK[i].hand_card_Number=PK[i].c>>2;
        switch (PK[i].hand_card_Number)
        {
        case 1:
            printf("%s A  ",hand_card_Type[i]);
            break;
        case 11:
            printf("%s J  ",hand_card_Type[i]);
            break;
        case 12:
            printf("%s Q  ",hand_card_Type[i]);
            break;
        case 13:
            printf("%s K  ",hand_card_Type[i]);
            break;
        default:
            printf("%s %d  ",hand_card_Type[i],PK[i].hand_card_Number);
            break;
        }
    }
};
int check_Flush(PKCARD *PK, int i, int N){
    int Flush=0;
    for(int i=1;i<5;i++){
        if (PK[0].hand_card_Type!=PK[i].hand_card_Type){
            Flush=0;
            break;
        }
        else{
            Flush=1;
        }
    }
    return Flush;
};
char check_Straight(PKCARD *PK, int i, int N){
    char straight=1;
    for(int i=0;i<4;i++){
        if(PK[i+1].hand_card_Number!=PK[i].hand_card_Number+1){
            straight=0;
        }
    }
    return straight;
};
char check_Quads(PKCARD *PK, int i){
    int Four_of_kind=0;
    if((PK[0].hand_card_Number==PK[3].hand_card_Number)||(PK[1].hand_card_Number==PK[4].hand_card_Number)){
        Four_of_kind=1;
    }
    else{
        Four_of_kind=0;
    }
    return Four_of_kind;
};
int check_Pairs(PKCARD *PK, int i){
    bool pair=false;
    if((PK[i].hand_card_Number==PK[i+1].hand_card_Number)){
        pair=1;
    }
    return pair;
};
char check_Trips(PKCARD *PK, int i){
    bool Trip = false;
    if ((PK[i].hand_card_Number == PK[i+1].hand_card_Number && PK[i+1].hand_card_Number == PK[i+2].hand_card_Number)) {
        Trip = true;
    }
    else {
        Trip = false;
    }
    return Trip;
};

int main() {
    PKCARD PK[5];
    int N;
    while(1){

        N = deal_cards(5, PK);
        sort_cards(PK, N);
        print_cards(PK, N);
        printf("\n");


        char Flush = 0;
        Flush = check_Flush(PK, 0,N);
        if(Flush){
            printf("Flush\n");
        }
        else{
            printf("No Flush\n");
        }
        
        if (check_Straight(PK, 0,N)) {
            printf("Straight\n");
        }
        else{
            printf("No Straight\n");
        }

        if (check_Quads(PK, 0)||check_Quads(PK, 1)) {
            printf("Four of kind\n");
        }
        else {
            printf("No Four of kind\n");
        }

        char FH = 0;
        if (check_Trips(PK, 0) && check_Pairs(PK, 3)) {
        FH = 1;
        }
        if (check_Trips(PK, 2) && check_Pairs(PK, 0)) {
        FH = 1;
        }
        if (FH) {
            printf("Full house\n");
        }
        else{
            printf("No Full house\n");
        }

        char PRcount = 0;
        for (int i = 0;i < 4;i++)
        if (check_Pairs(PK, i)) {
            PRcount++;i++;
        }
        if (PRcount > 0) {
            printf("%d pairs ", PRcount);
        }
        else{
            printf("No pair");
        }

        getchar();
        printf("\n");


    }
    return 0;
}
