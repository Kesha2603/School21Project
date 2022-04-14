#include<stdio.h>

int bMove(int x, int y);
int cleanScreen();
int drawScr();
int check_ball();
int rocket_controls();
int score(int a, int b);
int final();

//game settings
int final_score = 21;

//field settings
char f_simb = '|';
char f_fill = ' ';
int f_len = 80;
int f_height = 25;
int net_coor_x = 40;
char net_simb = '|';

//ball settings
int b_coor_x_def = 40; 
int b_coor_y_def = 12;
int bx_def = 1;
int by_def = 1;
int bx = 1;
int by = 1;
int b_coor_x = 40;
int b_coor_y = 12;
char b_simb = 'o';

//rocket settings
int roc_l_coor_x_def = 3;
int roc_l_coor_y_def = 11;
int roc_r_coor_x_def = 75;
int roc_r_coor_y_def = 11;
int roc_l_coor_x = 3;
int roc_l_coor_y = 11;
int roc_r_coor_x = 75;
int roc_r_coor_y = 11;
int roc_len = 2;
char roc_simb = '|';

//score settings

int score_l = 9;
int score_r = 9;


int score_l_coor_x = 38;
int score_l_coor_y = 2;
int score_r_coor_x = 42;
int score_r_coor_y = 2;

int main() {
	while(1){
		cleanScreen();
		drawScr();
		//getchar();
		rocket_controls();
		check_ball();
		if(score_l == final_score || score_r == final_score ){
			final();
			break;
		}
	}	
	return 0;
}

//прорисовка экрана------------------------------------------------------------
int drawScr(){
	//check_ball();

	for (int y = 0 ; y < f_height ; y++) {
		for (int x = 0 ; x < f_len ; x++) {


			if ( y == score_l_coor_y && x == score_l_coor_x ){
				printf("%d", score_l);
			} else if ( y == score_r_coor_y && x == score_r_coor_x ){
				printf("%d", score_r);
			}


			else if (y == 0 || y == f_height-1) {
			   	printf("%c", f_simb);
			} 

/*
			else if ( y == score_l_coor_y && x == score_l_coor_x ){
				printf("%d", score_l);
			} else if ( y == score_r_coor_y && x == score_r_coor_x ){
				printf("%d", score_r);
			} 
*/


			else if (( roc_l_coor_x == x && ( roc_l_coor_y == y || roc_l_coor_y+1 == y || roc_l_coor_y+2 == y )) 
			        || ( roc_r_coor_x == x && ( roc_r_coor_y == y || roc_r_coor_y+1 == y || roc_r_coor_y+2 == y ))){
				printf("%c", roc_simb);
			} else if(b_coor_x == x && b_coor_y == y){
			  	printf("%c", b_simb);
			//}else if(x == net_coor_x){
			//	printf("%c", net_simb);
			} else {
			  	printf("%c", f_fill);
			}
		}
		printf("\n");
	}
	return 0;
}
//-----------------------------------------------------------------------------


//движение мяча
int check_ball(){
	if( b_coor_x == roc_l_coor_x+1 && (b_coor_y == roc_l_coor_y || b_coor_y == roc_l_coor_y+1 || b_coor_y == roc_l_coor_y+2 )){
		bx *= -1;
	}
	if( b_coor_x == roc_r_coor_x-1 && (b_coor_y == roc_r_coor_y || b_coor_y == roc_r_coor_y+1 || b_coor_y == roc_r_coor_y+2 )){
		bx *= -1;
	}
	if(b_coor_y > f_height-3 || b_coor_y < 2 ){
		by *= -1;
	}

	if( b_coor_x < 1){
		score(0, 1);
	}
	if (b_coor_x > f_len-1){
		score(1, 0);
	};

	return 0;
}

//счет 
int score(int a, int b){
	score_l += a;
	score_r += b;

	b_coor_x = b_coor_x_def;
	b_coor_y = b_coor_y_def;
	roc_l_coor_x = roc_l_coor_x_def;
	roc_l_coor_y = roc_l_coor_y_def;
	roc_r_coor_x = roc_r_coor_x_def;
	roc_r_coor_y = roc_r_coor_y_def;
	bx = bx_def;
	by = by_def;

	

	return 0;
}


//финальный штрих
int final(){
	cleanScreen();
	if (score_l>score_r)
		printf("Победил игрок слева!!!\n");
	else 
		printf("Победил игрок справа!!!\n");
	return 0;
}

//сдвиг мяча
int bMove(int x, int y){
	b_coor_x += x;
	b_coor_y += y;

	return 0;
}


//зачистка экрана
int cleanScreen(){
	printf("\33c\e[3J");

	return 0;
}

//управление рокетками
int rocket_controls() {
    char c; 
    char ent;
    scanf("%c%c", &c, &ent); 
    if (c == 'a' || c == ' ' || c == 'z' || c == 'k' || c == 'm') {
        bMove(bx, by);
        if (c == 'a') {
            if (roc_l_coor_y != 1)
                roc_l_coor_y--;
        } else if ( c == 'z') {
            if ( roc_l_coor_y  != f_height-4)
                roc_l_coor_y++;
        } else if (c == 'k') {
            if ( roc_r_coor_y != 1)
                 roc_r_coor_y--;
        } else if (c == 'm') {
            if ( roc_r_coor_y != f_height-4)
                 roc_r_coor_y++;
        } 
    }
    return 0;
}

