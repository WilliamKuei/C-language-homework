#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef union{
    struct {
        unsigned hand_card_Type:2;
        unsigned hand_card_Number:6;
    };
    unsigned char c;
}hand;

void check_card(hand a[]){
    for(int i=0;i<5;i++){
        printf("%d  ",a[i].c);
    }
    printf("\n\n");
}
void test_card(int rd, int test_card[], const char *test_name) {
    printf("\n============== %s ==============\n", test_name);
    int hand_card_Num=0;
    bool draw_Finish=false;
    hand hand_Card[5]={0,0,0,0,0};
    int rand_Card=0,card_Type=0,card_Number=0,Card=0;


    if(rd==1){
        do{
            do{
    
                rand_Card=rand()%52;
                card_Type=rand_Card/13;
                card_Number=rand_Card%13+1;
                Card=(card_Number<<2)+card_Type;
                draw_Finish=false;
                for(int i=0;i<hand_card_Num;i++){
                    if(hand_Card[i].c==Card){
                        draw_Finish=true;
                        break;
                    }
                }
            }while(draw_Finish==true);
            hand_Card[hand_card_Num].c=Card;
            hand_card_Num++;
        }while(hand_card_Num<5);
    }
    else{
        for(int i=0;i<5;i++){
            hand_Card[i].c=test_card[i]; 
        }
    }
    
    printf("check draw card.\n");
    check_card(hand_Card);


    int sort_max_value=hand_Card[0].c;
    for(int i=0;i<5;i++){
        for(int k=0;k<4;k++){
            if(hand_Card[k].c>hand_Card[k+1].c){
                sort_max_value=hand_Card[k].c;
                hand_Card[k].c=hand_Card[k+1].c;
                hand_Card[k+1].c=sort_max_value;
            }
        }

    }
    printf("check bubble sort.\n");
    check_card(hand_Card);
/*-----------------------------------------------------*/
/*-----------------check card colar--------------------*/
    printf("check card colar.\n");
    char* hand_card_Type[5];
    for (int i=0;i<5;i++){
        switch (hand_Card[i].hand_card_Type&3)
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
        hand_Card[i].hand_card_Number=hand_Card[i].c>>2;
        switch (hand_Card[i].hand_card_Number)
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
            printf("%s %d  ",hand_card_Type[i],hand_Card[i].hand_card_Number);
            break;
        }

    }
/*-----------------------------------------------------*/
/*---------------------Flush---------------------------*/
    printf("\n\n");
    bool Flush=false;
    for(int i=1;i<5;i++){
        if (hand_Card[0].hand_card_Type!=hand_Card[i].hand_card_Type){
            Flush=false;
            break;
        }
        else{
            Flush=true;
        }
    }
    if(Flush){
        printf("Flush\n");
    }
    else{
        printf("No Flush\n");
    }
/*-----------------------------------------------------*/
/*--------------------Straight-------------------------*/
    bool straight=true;
    for(int i=0;i<4;i++){
        if(hand_Card[i+1].hand_card_Number!=hand_Card[i].hand_card_Number+1){
            straight=false;
        }
    }
    if(straight){
        printf("Straight\n");
    }
    else{
        printf("No Straight\n");
    }
/*-----------------------------------------------------*/
/*--------------------Full House-----------------------*/
    bool Full_house = false;
    if ((hand_Card[0].hand_card_Number == hand_Card[1].hand_card_Number && hand_Card[1].hand_card_Number == hand_Card[2].hand_card_Number) &&
        (hand_Card[3].hand_card_Number == hand_Card[4].hand_card_Number)) {
        Full_house = true;
    }
    else if ((hand_Card[2].hand_card_Number == hand_Card[3].hand_card_Number && hand_Card[3].hand_card_Number == hand_Card[4].hand_card_Number) &&
            (hand_Card[0].hand_card_Number == hand_Card[1].hand_card_Number)) {
        Full_house = true;
    }
    else {
        Full_house = false;
    }

    if (Full_house) {
        printf("Full house\n");
    }
    else {
        printf("No Full house\n");
    }
/*-----------------------------------------------------*/
/*--------------------Four of a kind-------------------*/
    bool Four_of_kind=false;
    if((hand_Card[0].hand_card_Number==hand_Card[3].hand_card_Number)||(hand_Card[1].hand_card_Number==hand_Card[4].hand_card_Number)){
        Four_of_kind=true;
    }
    else{
        Four_of_kind=false;
    }
    if (Four_of_kind) {
        printf("Four of kind\n");
    }
    else {
        printf("No Four of kind\n");
    }
/*-----------------------------------------------------*/
/*--------------------pair-----------------------------*/
    bool pair_con=false;
    int pair_num=0;
    for(int i=0;i<4;i++){
        if((hand_Card[i].hand_card_Number==hand_Card[i+1].hand_card_Number)&&!pair_con){
            pair_con=true;
            pair_num++;
        }
        else{
            pair_con=false;
        }
     }
    if (pair_num) {
        printf("%d Pair\n",pair_num);
    }
    else {
        printf("No Pair\n");
    }
    printf("\n============== End of %s ==============\n", test_name);
}
int main() {
    srand(time(NULL));  
    // ================================================
    // Four of a Kind
    int Four_of_a_Kind_hand[5] = {43, 41, 40, 42, 35};
    test_card(0, Four_of_a_Kind_hand, "Four of a Kind");

    // ================================================
    // Full House
    int Full_House_hand[5] = {13, 12, 15, 37, 36};
    test_card(0, Full_House_hand, "Full House");

    // ================================================
    // Flush
    int Flush_hand[5] = {32, 4, 40, 48, 8};
    test_card(0, Flush_hand, "Flush");

    // ================================================
    // Straight Flush
    int Straight_Flush_hand[5] = {11, 15, 19, 23, 27};
    test_card(0, Straight_Flush_hand, "Straight Flush");

    // ================================================
    // Two Pairs
    int Two_Pairs_hand[5] = {5, 6, 52, 55, 15};
    test_card(0, Two_Pairs_hand, "Two Pairs");

    char name[20];
    int rand_arr[]={0,0,0,0,0};
    for(int i = 1; i <= 10; i++) {
        sprintf(name, "rand[%d]", i);  
        test_card(1,rand_arr, name);
    }


    return 0;
}

