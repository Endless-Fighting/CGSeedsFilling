/*
二维题目 - 1
用第三方工具生成一个400×300分辨率的位图，灰度彩色均可，位图中包含一个背景为白色，前景为任意颜色的多边形。
然后，利用种子点填充算法，在位图中间任意位置用鼠标单击后设置种子点，实现空白位置的填充。
要求：
	采用4连通算法，简单种子点计算；
	设置一个定时器，使得填充计算每隔一小段时间计算一次，实现动画效果；
*/

#include <iostream>
#include <graphics.h>  
#include<windows.h>
#include<conio.h>
#include <time.h>
#include <queue>
using namespace std;

#define WIDTH 400
#define HEIGHT 300

//递归的种子填充算法，由于会导致栈溢出，舍弃
/*
void seedsFilling(int x, int y)
{
int color = getpixel(x, y);
if (color != WHITE)
putpixel(x, y, WHITE);
if (color == WHITE)
return;


seedsFilling(x + 1, y);
seedsFilling(x - 1, y);
seedsFilling(x, y + 1);
seedsFilling(x, y - 1);
}
*/

//非递归的种子填充算法
void seedsFilling(int x, int y)
{
	//若种子点已被填充或是边界则不做处理
	if (getpixel(x, y) == WHITE)
		return;

	pair<int, int> currentPoint;
	queue<pair<int, int>> pointsQueue;
	pointsQueue.push(pair<int, int>(x, y));	//将种子点推入队列

	while (!pointsQueue.empty())
	{
		Sleep(1);	//为每次循环设置间隔，实现动画效果
		currentPoint = pointsQueue.front();
		pointsQueue.pop();
		//若该点已被填充或是边界则不做处理
		if (getpixel(currentPoint.first, currentPoint.second) == WHITE)
			continue;
		else
		{	//否则将其填充并将四连通方向上的像素点加入队列
			putpixel(currentPoint.first, currentPoint.second, WHITE);
			pointsQueue.push(pair<int, int>(currentPoint.first - 1, currentPoint.second));
			pointsQueue.push(pair<int, int>(currentPoint.first + 1, currentPoint.second));
			pointsQueue.push(pair<int, int>(currentPoint.first, currentPoint.second - 1));
			pointsQueue.push(pair<int, int>(currentPoint.first, currentPoint.second + 1));
		}
	}
}

//随机生成点的个数，随机生成相应位置并连线
void drawPolygon()
{
	srand((unsigned)time(NULL));
	rectangle(0, 0, WIDTH - 1, HEIGHT - 1);

	int numOfPoints = rand() % 8 + 3;
	int *points = new int(numOfPoints * 2);
	for (int i = 0; i < numOfPoints; i++)
	{
		points[2 * i] = rand() % WIDTH;
		points[2 * i + 1] = rand() % HEIGHT;
	}
	drawpoly(numOfPoints, points);
}

//单击填充响应
void clickToFill()
{
	MOUSEMSG  m = GetMouseMsg();
	//等待鼠标事件，直到获得单击事件，
	while (m.uMsg != WM_LBUTTONDOWN)
	{
		m = GetMouseMsg();
	}
	seedsFilling(m.x, m.y);	//以点击位置为种子点进行填充
}


int main()
{
	initgraph(WIDTH, HEIGHT);

	drawPolygon();
	while (true)
	{
		clickToFill();
	}

	closegraph();
	return 0;
}

