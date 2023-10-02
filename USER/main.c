#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "lcd.h"
#include "sdram.h"
#include "adc.h"
#include "stdlib.h"
#define empty 0//标记位置为空
#define wall 1//标记墙
#define food 2 //标记食物
#define head 3 //标记蛇头
#define body 4 //标记蛇身
//游戏区域11列 20行
#define col 11
#define row 20
u16 zone_x[11];
u16 zone_y[20];
u16 flag[11][20];//标志游戏区各位置状态
//蛇头
struct Snake
{
	u16 len; //记录蛇身长度
	u16 x; //蛇头横坐标
	u16 y; //蛇头纵坐标
}snake;
//蛇身
struct Body{
	u16 x;
	u16 y;
}bod[row*col];
void snake_init();//初始化游戏区域与蛇
void drawsnake(u16 mark);//绘制蛇，其中mark用来标记是否需要清除之前已生成的蛇 0不需要 1需要
void createfood(); //产生并绘制食物
void move(int x,int y);//按（x,y）方向移动蛇
int main(void)
{
	u16 adcx;
	float temp;
	HAL_Init();                     //初始化HAL库   
	Stm32_Clock_Init(360,25,2,8);   //设置时钟,180Mhz
	delay_init(180);                //初始化延时函数
	uart_init(115200);              //初始化USART
	LED_Init();                     //初始化LED 
	KEY_Init();                     //初始化按键
	SDRAM_Init();                   //初始化SDRAM
	LCD_Init();                     //初始化LCD   
	MY_ADC_Init();                  //初始化ADC1通道5 	
	while(1)
	{
	} 

}

void snake_init(){
//初始化游戏区域（由50*50方块组成）
	zone_x[0]=25;
	zone_y[0]=25;
	for(int i=1;i<col;i++)zone_x[i]=zone_x[i-1]+50;
	for(int j=1;j<row;j++)zone_y[j]=zone_y[j-1]+50;
	for(int i=1;i<col;i++){
		for(int j=1;j<row;j++)flag[i][j]=empty;
	}
//创建墙
	for(int i=0;i<col;i++){
		drawblock(zone_x[i],zone_y[0],WHITE);
		drawblock(zone_x[i],zone_y[19],WHITE);
		flag[i][0]=wall;
		flag[i][19]=wall;
	}
	for(int j=1;j<row;j++){
		drawblock(zone_x[0],zone_y[j],WHITE);
		drawblock(zone_x[10],zone_y[j],WHITE);
		flag[0][j]=wall;
		flag[10][j]=wall;
	}
//初始化蛇
	snake.len = 2; //蛇的身体长度初始化为2
	snake.x = zone_x[col / 2]; //蛇头位置的横坐标
	snake.y = zone_y[row / 2]; //蛇头位置的纵坐标
	//蛇身坐标的初始化
	bod[0].x = zone_x[col / 2 ];
	bod[0].y = zone_y[row / 2-1];
	bod[1].x = zone_x[col / 2 ];
	bod[1].y = zone_y[row / 2-2];
	//将蛇头和蛇身位置进行标记
	flag[snake.y][snake.x] = head;
	flag[bod[0].y][bod[0].x] = body;
	flag[bod[1].y][bod[1].x] = body;
	

//	u16 xl[20];
//	u16 y[9];
//	u16 COLOR=GREEN;
//	xl[0]=25;
//	y[0]=75;
//	snake_x[0]=25+50*15;
//	snake_y[0]=25+4*50;
//	drawblock(25,25,WHITE);
//	drawblock(525,25,WHITE);
//	for(int i=1;i<20;i++){
//		xl[i]=xl[i-1]+50;
//		drawblock(25,xl[i],WHITE);
//		drawblock(525,xl[i],WHITE);
//	}
//	drawblock(y[0],xl[19],WHITE);
//	drawblock(y[0],xl[0],WHITE);
//	for(int i=1;i<9;i++){
//		y[i]=y[i-1]+50;
//		drawblock(y[i],xl[19],WHITE);
//		drawblock(y[i],xl[0],WHITE);
//	}
//	drawblock(snake_y[0],snake_x[0],WHITE);
//	for(int i=1;i<4;i++){
//		snake_x[i]=snake_x[i-1]-50;
//		drawblock(snake_y[0],snake_x[i],COLOR);
//	}
}

void drawsnake(u16 mark){
	if(mark==0){
		drawblock(snake.x,snake.y,GREEN);//绘制蛇头
		for(int i=0;i<snake.len;i++)drawblock(bod[i].x,bod[i].y,WHITE);//绘制蛇身
	}
	else{
		clearblock(bod[snake.len-1].x,bod[snake.len-1].y);//蛇每次移动一格，则只需把蛇尾删掉就行
	}
}	
void createfood(){
	u16 adcx=Get_Adc(ADC_CHANNEL_5);//获取通道5的转换值
	int i,j;
	srand(adcx);//以adc悬空引脚采样噪声值作为种子，确保食物生成的随机性
	do{
		j = rand() % row;
		i = rand() % col;
	}while(flag[i][j] != empty);//确保生成食物的位置为空
	POINT_COLOR=RED;
	LCD_Draw_Circle(zone_x[i],zone_y[j],25);//绘制食物
	flag[i][j]=food;
}
void move(int x,int y){
	drawsnake(0);//移动前需先把蛇尾清除
	flag
}