#include<stdio.h>
#include<graphics.h>
#include"tool.h"
#include<time.h>
#include<Windows.h>
#include<mmsystem.h>
#include <conio.h>
#include <math.h>
#pragma comment(lib,"winmm.lib")

int a = 0, b = 0;
//a表示第几关，b表示是否进行下一关

//玫瑰花
// 定义全局变量
int	rosesize = 500;
int	h = -250;


// 定义结构体
struct DOT
{
	double x;
	double y;
	double z;
	double r;	// 红色
	double g;	// 绿色
	// b(蓝色) 通过 r 计算
};


// 计算点
bool calc(double a, double b, double c, DOT& d)
{
	double j, n, o, w, z;

	if (c > 60)				// 花柄
	{
		d.x = sin(a * 7) * (13 + 5 / (0.2 + pow(b * 4, 4))) - sin(b) * 50;
		d.y = b * rosesize + 50;
		d.z = 625 + cos(a * 7) * (13 + 5 / (0.2 + pow(b * 4, 4))) + b * 400;
		d.r = a * 1 - b / 2;
		d.g = a;
		return true;
	}

	double A = a * 2 - 1;
	double B = b * 2 - 1;
	if (A * A + B * B < 1)
	{
		if (c > 37)			// 叶
		{
			j = (int(c) & 1);
			n = j ? 6 : 4;
			o = 0.5 / (a + 0.01) + cos(b * 125) * 3 - a * 300;
			w = b * h;

			d.x = o * cos(n) + w * sin(n) + j * 610 - 390;
			d.y = o * sin(n) - w * cos(n) + 550 - j * 350;
			d.z = 1180 + cos(B + A) * 99 - j * 300;
			d.r = 0.4 - a * 0.1 + pow(1 - B * B, -h * 6) * 0.15 - a * b * 0.4 + cos(a + b) / 5 + pow(cos((o * (a + 1) + (B > 0 ? w : -w)) / 25), 30) * 0.1 * (1 - B * B);
			d.g = o / 1000 + 0.7 - o * w * 0.000003;
			return true;
		}
		if (c > 32)			// 花萼
		{
			c = c * 1.16 - 0.15;
			o = a * 45 - 20;
			w = b * b * h;
			z = o * sin(c) + w * cos(c) + 620;

			d.x = o * cos(c) - w * sin(c);
			d.y = 28 + cos(B * 0.5) * 99 - b * b * b * 60 - z / 2 - h;
			d.z = z;
			d.r = (b * b * 0.3 + pow((1 - (A * A)), 7) * 0.15 + 0.3) * b;
			d.g = b * 0.7;
			return true;
		}

		// 花
		o = A * (2 - b) * (80 - c * 2);
		w = 99 - cos(A) * 120 - cos(b) * (-h - c * 4.9) + cos(pow(1 - b, 7)) * 50 + c * 2;
		z = o * sin(c) + w * cos(c) + 700;

		d.x = o * cos(c) - w * sin(c);
		d.y = B * 99 - cos(pow(b, 7)) * 50 - c / 3 - z / 1.35 + 450;
		d.z = z;
		d.r = (1 - b / 1.2) * 0.9 + a * 0.1;
		d.g = pow((1 - b), 20) / 4 + 0.05;
		return true;
	}

	return false;
}


void meiguihua()
{
	// 定义变量
	short* zBuffer;
	int		x, y, z, zBufferIndex;
	DOT		dot;

	// 初始化
	initgraph(640, 480);				// 创建绘图窗口
	setbkcolor(RGB(255, 192, 203));					// 设置背景色为粉色
	cleardevice();						// 清屏

	// 初始化 z-buffer
	zBuffer = new short[rosesize * rosesize];
	memset(zBuffer, 0, sizeof(short) * rosesize * rosesize);

	for (int j = 0; j < 2000 && !_kbhit(); j++)	// 按任意键退出
	{
		for (int i = 0; i < 10000; i++)			// 减少是否有按键的判断
			if (calc(double(rand()) / RAND_MAX, double(rand()) / RAND_MAX, rand() % 46 / 0.74, dot))
			{
				z = int(dot.z + 0.5);
				x = int(dot.x * rosesize / z - h + 0.5);
				y = int(dot.y * rosesize / z - h + 0.5);
				if (y >= rosesize) continue;

				zBufferIndex = y * rosesize + x;

				if (!zBuffer[zBufferIndex] || zBuffer[zBufferIndex] > z)
				{
					zBuffer[zBufferIndex] = z;

					// 画点
					int r = ~int((dot.r * h));				if (r < 0) r = 0;	if (r > 255) r = 255;
					int g = ~int((dot.g * h));				if (g < 0) g = 0;	if (g > 255) g = 255;
					int b = ~int((dot.r * dot.r * -80));	if (b < 0) b = 0;	if (b > 255) b = 255;
					putpixel(x + 50, y - 20, RGB(r, g, b));
				}
			}

		Sleep(1);
	}

	// 退出
	delete[]zBuffer;

	//_getch();
	//closegraph();
}

IMAGE imgBg;//定义一个图片变量，用来显示背景
IMAGE img1;
IMAGE img2;
IMAGE img3;
IMAGE img4;
IMAGE img5;

int offX = 50;
int offY = 150;

struct Button
{
	IMAGE button;//按钮的图标
	int width, height;
	int x, y;//按钮左上角在窗口中的位置
	int flag;//按钮的标记
	bool pressed;//是否被按下
};

struct Button2//答案按钮
{
	IMAGE button;
	int width, height;
	int x, y;
	int flag;
	bool pressed;
};

Button btn2;

Button btns[8];//设置8个按钮
int data[3][3];

void initbutton(Button* btn, const char* file, int width, int height, int flag)//按钮的属性
{
	loadimage(&btn->button, file, width, height, true);

	btn->width = width;
	btn->height = height;
	btn->pressed = false;
	btn->flag = flag;
}

void buttonsinit1()//关卡1
{
	//顺序排列
	/*for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			int k = 3 * i + j;//对第k个按钮初始化
			data[i][j] = k + 1;
			if (k == 8)
			{
				data[2][2] = 0;
				return;
			}
		
			char name[64];
			sprintf(name, "set/sz%d.png", k + 1);
			initbutton(&btns[k], name, 100, 100, k + 1);

			btns[k].x = offX + j * (100 + 1);
			btns[k].y = offY + i * (100 + 1);
		}
	}*/

	data[0][0] = 6;
	char name[64];
	sprintf(name, "set/sz6.png");
	initbutton(&btns[5], name, 100, 100, 6);
	btns[5].x = offX + 0 * (100 + 1);
	btns[5].y = offY + 0 * (100 + 1);

	data[0][1] = 7;
	sprintf(name, "set/sz7.png");
	initbutton(&btns[6], name, 100, 100, 7);
	btns[6].x = offX + 1 * (100 + 1);
	btns[6].y = offY + 0 * (100 + 1);

	data[0][2] = 3;
	sprintf(name, "set/sz3.png");
	initbutton(&btns[2], name, 100, 100, 3);
	btns[2].x = offX + 2 * (100 + 1);
	btns[2].y = offY + 0 * (100 + 1);
	
	data[1][0] = 8;
	sprintf(name, "set/sz8.png");
	initbutton(&btns[7], name, 100, 100, 8);
	btns[7].x = offX + 0 * (100 + 1);
	btns[7].y = offY + 1 * (100 + 1);

	data[1][1] = 2;
	sprintf(name, "set/sz2.png");
	initbutton(&btns[1], name, 100, 100, 2);
	btns[1].x = offX + 1 * (100 + 1);
	btns[1].y = offY + 1 * (100 + 1);

	data[1][2] = 5;
	sprintf(name, "set/sz5.png");
	initbutton(&btns[4], name, 100, 100, 5);
	btns[4].x = offX + 2 * (100 + 1);
	btns[4].y = offY + 1 * (100 + 1);

	data[2][0] = 4;
	sprintf(name, "set/sz4.png");
	initbutton(&btns[3], name, 100, 100, 4);
	btns[3].x = offX + 0 * (100 + 1);
	btns[3].y = offY + 2 * (100 + 1);
	
	data[2][1] = 1;
	sprintf(name, "set/sz1.png");
	initbutton(&btns[0], name, 100, 100, 1);
	btns[0].x = offX + 1 * (100 + 1);
	btns[0].y = offY + 2 * (100 + 1);

	data[2][2] = 0;
}

void buttonsinit2()//关卡2
{
	data[0][0] = 4;
	char name2[64];
	sprintf(name2, "set/sz4.png");
	initbutton(&btns[3], name2, 100, 100, 4);
	btns[3].x = offX + 0 * (100 + 1);
	btns[3].y = offY + 0 * (100 + 1);

	data[0][1] = 6;
	sprintf(name2, "set/sz6.png");
	initbutton(&btns[5], name2, 100, 100, 6);
	btns[5].x = offX + 1 * (100 + 1);
	btns[5].y = offY + 0 * (100 + 1);

	data[0][2] = 8;
	sprintf(name2, "set/sz8.png");
	initbutton(&btns[7], name2, 100, 100, 8);
	btns[7].x = offX + 2 * (100 + 1);
	btns[7].y = offY + 0 * (100 + 1);

	data[1][0] = 5;
	sprintf(name2, "set/sz5.png");
	initbutton(&btns[4], name2, 100, 100, 5);
	btns[4].x = offX + 0 * (100 + 1);
	btns[4].y = offY + 1 * (100 + 1);

	data[1][1] = 2;
	sprintf(name2, "set/sz2.png");
	initbutton(&btns[1], name2, 100, 100, 2);
	btns[1].x = offX + 1 * (100 + 1);
	btns[1].y = offY + 1 * (100 + 1);

	data[1][2] = 1;
	sprintf(name2, "set/sz1.png");
	initbutton(&btns[0], name2, 100, 100, 1);
	btns[0].x = offX + 2 * (100 + 1);
	btns[0].y = offY + 1 * (100 + 1);

	data[2][0] = 3;
	sprintf(name2, "set/sz3.png");
	initbutton(&btns[2], name2, 100, 100, 3);
	btns[2].x = offX + 0 * (100 + 1);
	btns[2].y = offY + 2 * (100 + 1);

	data[2][1] = 7;
	sprintf(name2, "set/sz7.png");
	initbutton(&btns[6], name2, 100, 100, 7);
	btns[6].x = offX + 1 * (100 + 1);
	btns[6].y = offY + 2 * (100 + 1);

	data[2][2] = 0;
}

void buttonsinit3()//关卡3
{
	data[0][0] = 6;
	char name3[64];
	sprintf(name3, "set/sz6.png");
	initbutton(&btns[5], name3, 100, 100, 6);
	btns[5].x = offX + 0 * (100 + 1);
	btns[5].y = offY + 0 * (100 + 1);

	data[0][1] = 8;
	sprintf(name3, "set/sz8.png");
	initbutton(&btns[7], name3, 100, 100, 8);
	btns[7].x = offX + 1 * (100 + 1);
	btns[7].y = offY + 0 * (100 + 1);

	data[0][2] = 7;
	sprintf(name3, "set/sz7.png");
	initbutton(&btns[6], name3, 100, 100, 7);
	btns[6].x = offX + 2 * (100 + 1);
	btns[6].y = offY + 0 * (100 + 1);

	data[1][0] = 3;
	sprintf(name3, "set/sz3.png");
	initbutton(&btns[2], name3, 100, 100, 3);
	btns[2].x = offX + 0 * (100 + 1);
	btns[2].y = offY + 1 * (100 + 1);

	data[1][1] = 5;
	sprintf(name3, "set/sz5.png");
	initbutton(&btns[4], name3, 100, 100, 5);
	btns[4].x = offX + 1 * (100 + 1);
	btns[4].y = offY + 1 * (100 + 1);

	data[1][2] = 4;
	sprintf(name3, "set/sz4.png");
	initbutton(&btns[3], name3, 100, 100, 4);
	btns[3].x = offX + 2 * (100 + 1);
	btns[3].y = offY + 1 * (100 + 1);

	data[2][0] = 2;
	sprintf(name3, "set/sz2.png");
	initbutton(&btns[1], name3, 100, 100, 2);
	btns[1].x = offX + 0 * (100 + 1);
	btns[1].y = offY + 2 * (100 + 1);

	data[2][1] = 1;
	sprintf(name3, "set/sz1.png");
	initbutton(&btns[0], name3, 100, 100, 1);
	btns[0].x = offX + 1 * (100 + 1);
	btns[0].y = offY + 2 * (100 + 1);

	data[2][2] = 0;
}

void buttonsinit4()//关卡4
{
	data[0][0] = 8;
	char name4[64];
	sprintf(name4, "set/sz8.png");
	initbutton(&btns[7], name4, 100, 100, 8);
	btns[7].x = offX + 0 * (100 + 1);
	btns[7].y = offY + 0 * (100 + 1);

	data[0][1] = 5;
	sprintf(name4, "set/sz5.png");
	initbutton(&btns[4], name4, 100, 100, 5);
	btns[4].x = offX + 1 * (100 + 1);
	btns[4].y = offY + 0 * (100 + 1);

	data[0][2] = 7;
	sprintf(name4, "set/sz7.png");
	initbutton(&btns[6], name4, 100, 100, 7);
	btns[6].x = offX + 2 * (100 + 1);
	btns[6].y = offY + 0 * (100 + 1);

	data[1][0] = 2;
	sprintf(name4, "set/sz2.png");
	initbutton(&btns[1], name4, 100, 100, 2);
	btns[1].x = offX + 0 * (100 + 1);
	btns[1].y = offY + 1 * (100 + 1);

	data[1][1] = 1;
	sprintf(name4, "set/sz1.png");
	initbutton(&btns[0], name4, 100, 100, 1);
	btns[0].x = offX + 1 * (100 + 1);
	btns[0].y = offY + 1 * (100 + 1);

	data[1][2] = 4;
	sprintf(name4, "set/sz4.png");
	initbutton(&btns[3], name4, 100, 100, 4);
	btns[3].x = offX + 2 * (100 + 1);
	btns[3].y = offY + 1 * (100 + 1);

	data[2][0] = 3;
	sprintf(name4, "set/sz3.png");
	initbutton(&btns[2], name4, 100, 100, 3);
	btns[2].x = offX + 0 * (100 + 1);
	btns[2].y = offY + 2 * (100 + 1);

	data[2][1] = 6;
	sprintf(name4, "set/sz6.png");
	initbutton(&btns[5], name4, 100, 100, 6);
	btns[5].x = offX + 1 * (100 + 1);
	btns[5].y = offY + 2 * (100 + 1);

	data[2][2] = 0;
}

void buttonsinit5()//关卡5
{
	data[0][0] = 5;
	char name5[64];
	sprintf(name5, "set/sz5.png");
	initbutton(&btns[4], name5, 100, 100, 5);
	btns[4].x = offX + 0 * (100 + 1);
	btns[4].y = offY + 0 * (100 + 1);

	data[0][1] = 3;
	sprintf(name5, "set/sz3.png");
	initbutton(&btns[2], name5, 100, 100, 3);
	btns[2].x = offX + 1 * (100 + 1);
	btns[2].y = offY + 0 * (100 + 1);

	data[0][2] = 2;
	sprintf(name5, "set/sz2.png");
	initbutton(&btns[1], name5, 100, 100, 2);
	btns[1].x = offX + 2 * (100 + 1);
	btns[1].y = offY + 0 * (100 + 1);

	data[1][0] = 7;
	sprintf(name5, "set/sz7.png");
	initbutton(&btns[6], name5, 100, 100, 7);
	btns[6].x = offX + 0 * (100 + 1);
	btns[6].y = offY + 1 * (100 + 1);

	data[1][1] = 6;
	sprintf(name5, "set/sz6.png");
	initbutton(&btns[5], name5, 100, 100, 6);
	btns[5].x = offX + 1 * (100 + 1);
	btns[5].y = offY + 1 * (100 + 1);

	data[1][2] = 4;
	sprintf(name5, "set/sz4.png");
	initbutton(&btns[3], name5, 100, 100, 4);
	btns[3].x = offX + 2 * (100 + 1);
	btns[3].y = offY + 1 * (100 + 1);

	data[2][0] = 8;
	sprintf(name5, "set/sz8.png");
	initbutton(&btns[7], name5, 100, 100, 8);
	btns[7].x = offX + 0 * (100 + 1);
	btns[7].y = offY + 2 * (100 + 1);

	data[2][1] = 1;
	sprintf(name5, "set/sz1.png");
	initbutton(&btns[0], name5, 100, 100, 1);
	btns[0].x = offX + 1 * (100 + 1);
	btns[0].y = offY + 2 * (100 + 1);

	data[2][2] = 0;
}

void BGM()//背景音乐
{
	mciSendString("open ./BGM.mp3", 0, 0, 0);
	mciSendString("play ./BGM.mp3 repeat", 0, 0, 0);
}

void buttoninit()//答案按钮
{
	char name0[64];
	sprintf(name0, "set/answer.png");
	initbutton(&btn2, name0, 300, 100, 0);
	btn2.x = offX;
	btn2.y = offY + 320;
}

void drawbutton(Button* btn)
{
	if (!btn)//防御性编程
	{
		return;
	}
	
	drawPNG(btn->x, btn->y, &btn->button);
}

void update()//更新游戏画面
{
	putimage(0, 0, &imgBg);//输出loadimage中的图片
	system("pause");
}

bool checkButtonSelect(Button* btn, MOUSEMSG* msg)//检查指定的按钮是否被选择
{
	if (msg->x >= btn->x &&
		msg->x <= btn->x + btn->width &&
		msg->y >= btn->y &&
		msg->y <= btn->y + btn->height)
		return true;
	else
		return false;
}

Button* checkButtonClick(MOUSEMSG msg)//检查按钮是否被按下
{
	for (int i = 0; i < 8; i++)
	{
		if (checkButtonSelect(&btns[i], &msg))
		{
			btns[i].pressed = true;
			return &btns[i];
		}
	}
	return NULL;
}

bool canMove(int sz,int* x,int* y)//检查按钮是否可以移动
{
	int i = 0, j = 0;
	int flag = 0;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (data[i][j] == sz)
			{
				flag = 1;
				break;
			}
		}
		if (flag) break;
	}

	int i0 = i, j0 = j;
	if (i0 > 0 && data[i0 - 1][j0] == 0)
	{
		*x = 0;
		*y = -1;
		data[i0 - 1][j0] = sz;
		data[i0][j0] = 0;
		return true;
	}
	if (i0 < 2 && data[i0 + 1][j0] == 0)
	{
		*x = 0;
		*y = 1;
		data[i0 + 1][j0] = sz;
		data[i0][j0] = 0;
		return true;
	}
	if (j0 > 0 && data[i0][j0 - 1] == 0)
	{
		*x = -1;
		*y = 0;
		data[i0][j0 - 1] = sz;
		data[i0][j0] = 0;
		return true;
	}
	if (j0 < 2 && data[i0][j0 + 1] == 0)
	{
		*x = 1;
		*y = 0;
		data[i0][j0 + 1] = sz;
		data[i0][j0] = 0;
		return true;
	}

	return false;
}

void moveButton(Button* button)//移动的步骤
{
	int x, y;
	if (canMove(button->flag, &x, &y))
	{
		button->x += x * (100 + 1);
		button->y += y * (100 + 1);
		loadimage(&imgBg, "set/bg2.png", 400, 600, true);//重新渲染
		putimage(0, 0, &imgBg);
		for (int i = 0; i < 8; i++)
		{
			drawbutton(&btns[i]);
		}
	}
}

void init()//初始化
{
	b++;
	initgraph(400, 600);//窗口大小
	loadimage(&imgBg, "set/bg1.jpg", 400, 600, true);//加载初始背景变量,...为图片位置，true等比例缩小
	buttoninit();
	if (b == 1)
		buttonsinit1();
	if (b == 2)
		buttonsinit2();
	if (b == 3)
		buttonsinit3();
	if (b == 4)
		buttonsinit4();
	if (b == 5)
		buttonsinit5();
}

int check = 0;

void checksuccess()
{
	int* p = &data[0][0];//判断是否成功
	for (int i = 1; i <= 8; i++, p++)
	{
		if (*p != i)
			return;
	}
	meiguihua();
	if (b != 5)
	{
		int ret = MessageBox(0, "勇士！你想尝试下一关吗？", " ",  MB_YESNO);
		if (ret == IDYES)
		{
			a = 1;
			check = 1;
		}
	}
	else
	{
		MessageBox(0, "恭喜！你已完成所有挑战！"," ",  MB_OK);
		closegraph();
	}
}

int main()
{
	do
	{
		a = 0;
		check = 0;
		BGM();
		init();
		update();
		loadimage(&imgBg, "set/bg2.png", 400, 600, true);//转入游戏背景
		BeginBatchDraw();//解决背景频闪
		putimage(0, 0, &imgBg);
		loadimage(&img1, "set/g1.png", 100, 100, true);
		loadimage(&img2, "set/g2.png", 100, 100, true);
		loadimage(&img3, "set/g3.png", 100, 100, true);
		loadimage(&img4, "set/g4.png", 100, 100, true);
		loadimage(&img5, "set/g5.png", 100, 100, true);

		for (int i = 0; i < 8; i++)
		{
			drawbutton(&btns[i]);
		}
		drawbutton(&btn2);

		Button* btn = NULL;

		while (1)
		{
			MOUSEMSG m = GetMouseMsg();//获取鼠标信息

			if (b == 1)
				putimage(150, 25, &img1);
			if (b == 2)
				putimage(150, 25, &img2);
			if (b == 3)
				putimage(150, 25, &img3);
			if (b == 4)
				putimage(150, 25, &img4);
			if (b == 5)
				putimage(150, 25, &img5);

			switch (m.uMsg)//uMsg是 鼠标类型
			{
			case WM_LBUTTONDOWN://判断哪个按钮被选择
				if (m.x >= 50 &&
					m.x <= 350 &&
					m.y >= 470 &&
					m.y <= 570)
				{
					ShellExecute(0, "open", ".\\华容道解密.exe", 0, 0, 1);
					break;
				}
				else {
					btn = checkButtonClick(m);
					break;
				}
			case WM_LBUTTONUP://按钮开始移动
				if (btn)
				{
					btn->pressed = false;
					moveButton(btn);
				}
				break;
			}

			if (b == 1)
				putimage(150, 25, &img1);
			if (b == 2)
				putimage(150, 25, &img2);
			if (b == 3)
				putimage(150, 25, &img3);
			if (b == 4)
				putimage(150, 25, &img4);
			if (b == 5)
				putimage(150, 25, &img5);

			drawbutton(btn);
			drawbutton(&btn2);
			EndBatchDraw();
			checksuccess();
			if (check == 1)
				break;
		}
		//system("pause");
	} while (a == 1);

	return 0;
}