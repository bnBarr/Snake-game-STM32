#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "lcd.h"
#include "sdram.h"
#include "adc.h"
#include "stdlib.h"
#define empty 0//���λ��Ϊ��
#define wall 1//���ǽ
#define food 2 //���ʳ��
#define head 3 //�����ͷ
#define body 4 //�������
//��Ϸ����11�� 20��
#define col 11
#define row 20
u16 zone_x[11];
u16 zone_y[20];
u16 flag[11][20];//��־��Ϸ����λ��״̬
//��ͷ
struct Snake
{
	u16 len; //��¼������
	u16 x; //��ͷ������
	u16 y; //��ͷ������
}snake;
//����
struct Body{
	u16 x;
	u16 y;
}bod[row*col];
void snake_init();//��ʼ����Ϸ��������
void drawsnake(u16 mark);//�����ߣ�����mark��������Ƿ���Ҫ���֮ǰ�����ɵ��� 0����Ҫ 1��Ҫ
void createfood(); //����������ʳ��
void move(int x,int y);//����x,y�������ƶ���
int main(void)
{
	u16 adcx;
	float temp;
	HAL_Init();                     //��ʼ��HAL��   
	Stm32_Clock_Init(360,25,2,8);   //����ʱ��,180Mhz
	delay_init(180);                //��ʼ����ʱ����
	uart_init(115200);              //��ʼ��USART
	LED_Init();                     //��ʼ��LED 
	KEY_Init();                     //��ʼ������
	SDRAM_Init();                   //��ʼ��SDRAM
	LCD_Init();                     //��ʼ��LCD   
	MY_ADC_Init();                  //��ʼ��ADC1ͨ��5 	
	while(1)
	{
	} 

}

void snake_init(){
//��ʼ����Ϸ������50*50������ɣ�
	zone_x[0]=25;
	zone_y[0]=25;
	for(int i=1;i<col;i++)zone_x[i]=zone_x[i-1]+50;
	for(int j=1;j<row;j++)zone_y[j]=zone_y[j-1]+50;
	for(int i=1;i<col;i++){
		for(int j=1;j<row;j++)flag[i][j]=empty;
	}
//����ǽ
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
//��ʼ����
	snake.len = 2; //�ߵ����峤�ȳ�ʼ��Ϊ2
	snake.x = zone_x[col / 2]; //��ͷλ�õĺ�����
	snake.y = zone_y[row / 2]; //��ͷλ�õ�������
	//��������ĳ�ʼ��
	bod[0].x = zone_x[col / 2 ];
	bod[0].y = zone_y[row / 2-1];
	bod[1].x = zone_x[col / 2 ];
	bod[1].y = zone_y[row / 2-2];
	//����ͷ������λ�ý��б��
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
		drawblock(snake.x,snake.y,GREEN);//������ͷ
		for(int i=0;i<snake.len;i++)drawblock(bod[i].x,bod[i].y,WHITE);//��������
	}
	else{
		clearblock(bod[snake.len-1].x,bod[snake.len-1].y);//��ÿ���ƶ�һ����ֻ�����βɾ������
	}
}	
void createfood(){
	u16 adcx=Get_Adc(ADC_CHANNEL_5);//��ȡͨ��5��ת��ֵ
	int i,j;
	srand(adcx);//��adc�������Ų�������ֵ��Ϊ���ӣ�ȷ��ʳ�����ɵ������
	do{
		j = rand() % row;
		i = rand() % col;
	}while(flag[i][j] != empty);//ȷ������ʳ���λ��Ϊ��
	POINT_COLOR=RED;
	LCD_Draw_Circle(zone_x[i],zone_y[j],25);//����ʳ��
	flag[i][j]=food;
}
void move(int x,int y){
	drawsnake(0);//�ƶ�ǰ���Ȱ���β���
	flag
}