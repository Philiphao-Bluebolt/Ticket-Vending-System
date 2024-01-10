#include <stdio.h>//头文件
#include <stdlib.h>
#include <string.h>
#include <graphics.h>
#include <math.h>

#define ArraySize 50//注意数组编号从0开始（0~stationnumber-1）

typedef struct Line//储存各线路信息
{
    char station[ArraySize][ArraySize];//储存各站名称，（0~stationnumber-1）
    int stationnumber;//储存该线路总站数
    int interchange[ArraySize][3];//储存该线路的换乘站，0列存站编号，1列存换乘另一线路编号，2列存该换乘站在另一线路的编号，同站多换乘会储存在不同行
    int internumber;//储存换乘站数，多换乘站会重复
}LINE;

void Welcome()//欢迎界面
{
    int height = 0, width = 0;//字符串的绘制长宽

    setbkcolor(LIGHTBLUE);//设置背景色
    setlinecolor(LIGHTBLUE);
    setfillcolor(LIGHTBLUE);
    cleardevice();

    LPCSTR string;//字符串

    string = "---Welcome to the subway automatic ticket system---";//欢迎信息

    height = textheight(string);
    width = textwidth(string);

    outtextxy(320 - width / 2, 200 - height / 2, string);

    string = "@Copyright Matrix Inc -- All rights reserved";//版权信息
 
    height = textheight(string);
    width = textwidth(string);

    outtextxy(640 - width, 480 - height, string);

    string = "Loading . . .";//模拟加载

    height = textheight(string);
    width = textwidth(string);

    outtextxy(320 - width / 2, 300 - height / 2, string);

    Sleep(3000);//延时

    printf("---Welcome to the subway automatic ticket system---\n\n");
    printf("@Copyright Matrix Inc.\nAll rights reserved\n\n");
}

int Menu()//主菜单选项
{
    int selection = 0;

    int height = 0, width = 0;//字符串的绘制长宽

    LPCSTR string;//字符串

    cleardevice();//清屏
    string = "---Main menu---";//欢迎信息

    height = textheight(string);
    width = textwidth(string);

    outtextxy(320 - width / 2, 160 - height / 2, string);

    string = "@Copyright Matrix Inc -- All rights reserved";//版权信息

    height = textheight(string);
    width = textwidth(string);

    outtextxy(640 - width, 480 - height, string);

    string = "1-Buy a ticket";

    height = textheight(string);
    width = textwidth(string);

    outtextxy(320 - width / 2, 250 - height / 2, string);

    string = "2-View the map";

    height = textheight(string);
    width = textwidth(string);

    outtextxy(320 - width / 2, 280 - height / 2, string);

    string = "3-Quit";

    height = textheight(string);
    width = textwidth(string);

    outtextxy(320 - width / 2, 310 - height / 2, string);

    printf("\n\n--Main menu--");
    printf("\n1-Buy a ticket\n2-View the map\n3-Quit");
    while (1)
    {
        printf("\n\nPlease select an option:");
        scanf_s("%d", &selection);
        getchar();

        if (selection >= 1 && selection <= 3)
        {
            break;
        }

        else
        {
            printf("\n\nInvalid Number! Please try again!\a\n\n");

            string = "Invalid Number! Please try again!";

            height = textheight(string);
            width = textwidth(string);

            outtextxy(320 - width / 2, 450 - height / 2, string);
            Sleep(2000);

            fillrectangle(320 - width / 2, 450 - height / 2, 320 + width / 2, 450 + height / 2);
        }
    }

    return selection;
}

int Map(LINE StationLine[ArraySize],int linenumber)//地图查询函数
{
    int number = 0, charac = 0, line = 0, selection = 0, temp = 0;

    int height = 0, width = 0;
    LPCSTR string;
    cleardevice();

    IMAGE pic = NULL;//读取地图
    loadimage(&pic, "D:\\VSproject\\TicketDemo\\Map.jpg", 320, 240);
    putimage(160, 80, &pic);

    string = "@Copyright Matrix Inc -- All rights reserved";//版权信息

    height = textheight(string);
    width = textwidth(string);

    outtextxy(640 - width, 480 - height, string);

    string = "---Map---";

    height = textheight(string);
    width = textwidth(string);

    outtextxy(320 - width / 2, 50 - height / 2, string);

    printf("\n\n--Map--\n");

    for (line = 0;line <= linenumber-1;line++)//输出所有线路的站点
    {
        printf("\n\n--Line %d Stations:", line + 1);

        for (number = 0;number <= StationLine[line].stationnumber - 1;number++)
        {
            printf("\n\n%d.", number + 1);
            for (charac = 0;StationLine[line].station[number][charac] != '\0';charac++)
            {
                printf("%c", StationLine[line].station[number][charac]);
            }

            for (temp = 0;temp <= StationLine[line].internumber - 1;temp++)//检测该站是否为换乘站，若是则显示换乘线路
            {
                if (StationLine[line].interchange[temp][0] == number)
                {
                    printf(" #Interchange with Line %d", StationLine[line].interchange[temp][1] + 1);
                }
            }
        }
    }

    printf("\n\n-----\n0-Main menu\n1-Buy a ticket\n2-Quit\n3-Search for a station");

    {
        string = "0-Main menu";
        outtextxy(160, 360, string);

        string = "1-Buy a ticket";
        outtextxy(320, 360, string);

        string = "2-Quit";
        outtextxy(160, 420, string);

        string = "3-Search for a station";
        outtextxy(320, 420, string);
    }

    while (1)
    {
        printf("\n\nPlease select an option:");
        scanf_s("%d", &selection);
        getchar();

        if (selection >= 0 && selection <= 4)
        {
            if (selection == 2 || selection == 3)//选项编号一致化
            {
                selection++;
            }

            break;
        }

        else
        {
            printf("\n\nInvalid Number! Please try again!\a\n\n");

            string = "Invalid Number! Please try again!";

            height = textheight(string);
            width = textwidth(string);

            outtextxy(320 - width / 2, 450 - height / 2, string);
            Sleep(2000);

            fillrectangle(320 - width / 2, 450 - height / 2, 320 + width / 2, 450 + height / 2);
        }
    }

    return selection;
}

int Search(LINE StationLine[ArraySize],int linenumber)//站点查找函数
{
    int find = 0, number = 0, line = 0, temp = 0, selection = 0;
    int lines[ArraySize] = {0};//搜索站名所在线路（换乘站会多于一个）

    char search[ArraySize];//储存输入待搜索的站名

    int height = 0, width = 0;
    LPCSTR string;
    char strtemp[ArraySize];
    cleardevice();

    string = "@Copyright Matrix Inc -- All rights reserved";//版权信息

    height = textheight(string);
    width = textwidth(string);

    outtextxy(640 - width, 480 - height, string);

    string = "---Search for a station---";

    height = textheight(string);
    width = textwidth(string);

    outtextxy(320 - width / 2, 50 - height / 2, string);

    string = "Input:";
    outtextxy(220, 240, string);

    printf("\n\n--Station Search--");
    printf("\n\nPlease input a station by name:");
    fgets(search, ArraySize, stdin);//输入搜索的站名
    fflush(stdin);

    for (temp = 0;temp <= ArraySize;temp++)
    {
        if (search[temp] == '\n')
        {
            search[temp] = '\0';//去除回车符
            break;
        }
    }

    string = search;
    outtextxy(280, 240, string);

    for (line = 0;line <= linenumber - 1;line++)//搜寻站点所在线路
    {
        for (number = 0;number <= StationLine[line].stationnumber - 1;number++)
        {
            if (strcmp(search, StationLine[line].station[number]) == 0)
            {
                lines[find] = line;
                find++;
            }
        }
    }

    if (find == 0)//搜索无结果
    {
        string = "Station Not found!";

        height = textheight(string);
        width = textwidth(string);

        outtextxy(320 - width / 2, 280 - height / 2, string);

        printf("\nStation Not found!\a\n");
    }

    if (find == 1)//非换乘站
    {
        sprintf_s(strtemp, "Found this station in Line %d", lines[find - 1] + 1);
        string = strtemp;

        height = textheight(string);
        width = textwidth(string);

        outtextxy(320 - width / 2, 280 - height / 2, string);

        printf("\nFound this station in Line %d\n", lines[find - 1] + 1);
    }

    if (find > 1)//换乘站
    {
        string = "This station is the interchange of Line ";

        height = textheight(string);
        width = textwidth(string);

        outtextxy(320 - width / 2, 280 - height / 2, string);

        printf("\nThis station is the interchange of Line ");

        for (number = 0;number <= find - 1;number++)
        {
            printf("%d", lines[number] + 1);

            sprintf_s(strtemp, "%d", lines[number] + 1);
            string = strtemp;

            outtextxy(442 + number * 16, 280 - height / 2, string);

            if (number < find - 1)
            {
                sprintf_s(strtemp, ", ");
                string = strtemp;

                outtextxy(442 + number * 16 + 16, 280 - height / 2, string);

                printf(", ");
            }
            else
            {
                putchar('\n');
            }
        }
    }
    
    string = "1-Retry";
    outtextxy(160, 360, string);

    string = "0-Main menu";
    outtextxy(320, 360, string);

    printf("\n0-Main menu\n1-Retry");
    while (1)
    {
        printf("\nPlease select an option:");//提示重新输入或回到主菜单
        scanf_s("%d", &selection);
        getchar();

        if (selection == 0)
        {
            return 0;
        }

        else if (selection == 1)
        {
            return 4;
        }

        else
        {
            printf("\n\nInvalid Number! Please try again!\a\n\n");

            string = "Invalid Number! Please try again!";

            height = textheight(string);
            width = textwidth(string);

            outtextxy(320 - width / 2, 450 - height / 2, string);
            Sleep(2000);

            fillrectangle(320 - width / 2, 450 - height / 2, 320 + width / 2, 450 + height / 2);
        }
    }
    
    return 0;//跳回主菜单
}

void ComplexRoute(LINE StationLine[ArraySize], int Terln[ArraySize][3], int Avoid[ArraySize], int selectline, int prinum, int pass, int flagsolution, int *solutionA, int *solutionB)
                 //线路相关信息                   终到站所在线路          递归已经过的线路      本次递归线路    初始站号   已经过线路数  目前经过总站数            方案指针                              
{
    int inter = 0, temp = 0, tempsolution = 0, endline = 0;
                                                                                                    //printf("\n\n Line %d", selectline+1);
    Avoid[pass] = selectline;//新输入现在处于的线路
    pass++;//已经过线路数加一，注意此时pass-1才指向当前线路
                                                                                                    //printf("\n\nPass=%d", pass);//调试用：输出换乘
    for (endline = 0;endline <= Terln[0][2] - 1;endline++)//递归终点
    {
        if (selectline == Terln[endline][0])//一但当前线路位于目标线路之内
        {
            tempsolution = flagsolution + abs(prinum - Terln[endline][1]);                                           
                                                                                                    //printf("\n\n\t\t\t\tPrinum:%d,Last PASS:%d,Since PASS:%d,FINAL:%d!",prinum, prinum - Terln[endline][1],flagsolution ,tempsolution);
            if (*solutionA == 0)//方案A赋值
            {
                *solutionA = tempsolution;
            }

            if (*solutionB == 0)//方案B赋值
            {
                *solutionB = tempsolution;
            }

            if (*solutionA != 0 && *solutionB != 0)//清空较差方案，为后面的方案空出位置
            {
                if (*solutionA >= *solutionB)
                {
                    *solutionA = 0;
                }
                else
                {
                    *solutionB = 0;
                }
            }

            return;
        }
    }

    for (inter = 0; inter <= StationLine[selectline].internumber - 1; inter ++)//在现有线路选定一个换乘站
    {
        for (temp = 0;temp <= pass - 2;temp++)//避开曾经过的线路，-2是因为pass-1指向当前线路
        {
            if (StationLine[selectline].interchange[inter][1] == Avoid[temp])
            {
                inter ++;
                if (inter > StationLine[selectline].internumber - 1)
                {
                    return;
                }

                else
                {
                    temp = -1;
                }
            }
        }

        tempsolution = flagsolution + abs(prinum - StationLine[selectline].interchange[inter][0]);//计算该段线路过站数（截至目前）  
                                                                                                                                                          //printf("\n\n\t\tChosen Inter:%d,Since PASS:%d",StationLine[selectline].interchange[inter],tempsolution);
        ComplexRoute(StationLine, Terln, Avoid, StationLine[selectline].interchange[inter][1], StationLine[selectline].interchange[inter][2], pass, tempsolution, solutionA, solutionB);

    }

    return;
}

int Ticket(int totalpass)
{
    int ferror = 0;
    int temp = 0;//临时计数变量
    int singleprice = 0;//最终价格（一张票）
    int price = 0;//总价格
    int ticketnum = 0;//票数
    int inserted = 0;//本次投入金额
    int paid = 0;//已投入总金额

    int stairprice[ArraySize][3];//0列存价格，1列存此级价格的最远站数，[0][2]存阶梯级数

    int height = 0, width = 0;
    LPCSTR string;
    char strtemp[ArraySize];
    cleardevice();

    string = "@Copyright Matrix Inc -- All rights reserved";//版权信息

    height = textheight(string);
    width = textwidth(string);

    outtextxy(640 - width, 480 - height, string);

    string = "---Payment---";

    height = textheight(string);
    width = textwidth(string);

    outtextxy(320 - width / 2, 50 - height / 2, string);

    FILE* fp = NULL;//文件编写格式：阶梯级数，（间两行），价格1，（间一行），价格最远站数1，（间两行）...
    ferror = fopen_s(&fp, "D:\\VSproject\\TicketDemo\\Price.txt", "r");//打开文件

    if (ferror != NULL)//读取文件失败，退回主菜单
    {
        printf("File opening failed!\a");
        return 0;
    }

    fscanf_s(fp, "%d", &stairprice[0][2]);//读取阶梯级数

    for (temp = 0;temp <= stairprice[0][2] - 1;temp++)//读取各阶梯价格及最远站数
    {
        fgetc(fp);
        fgetc(fp);
        fgetc(fp);
        fscanf_s(fp, "%d", &stairprice[temp][0]);
        fgetc(fp);
        fgetc(fp);
        fscanf_s(fp, "%d", &stairprice[temp][1]);
    }

    ferror = fclose(fp);//关闭文件
    if (ferror != NULL)//文件关闭失败，退回主菜单
    {
        printf("File closing failed!\a");
        return 0;
    }

    for (temp = 0;temp <= stairprice[0][2] - 1;temp++)//检测所选路线的价格区间，确定最终价格
    {
        if (totalpass <= stairprice[temp][1])
        {
            singleprice = stairprice[temp][0];
        }

        if (temp == stairprice[0][2] - 1)//防止未考虑最高票价的情况（所选线路超过了定义的最大票价站数），按定义最高区间收取
        {
            singleprice = stairprice[temp][0];
        }
    }

    string = "Please input number of tickets to buy:";

    height = textheight(string);
    width = textwidth(string);

    outtextxy(320 - width / 2, 120 - height / 2, string);

    while (1)
    {
        printf("\n\nPlease input number of tickets to buy:");//购票数
        scanf_s("%d", &ticketnum);
        getchar();

        sprintf_s(strtemp, "%d", ticketnum);
        string = strtemp;

        height = textheight(string);
        width = textwidth(string);

        outtextxy(450 - width / 2, 120 - height / 2, string);

        if (ticketnum >= 1 && ticketnum <= 1000)//不可买超过一千张
        {
            price = ticketnum * singleprice;//总价格
            break;
        }

        else
        {
            fillrectangle(450 - width / 2, 120 - height / 2, 450 + width / 2, 120 + height / 2);//覆盖输入数字

            string = "Invalid Number! Please try again!";

            height = textheight(string);
            width = textwidth(string);

            outtextxy(320 - width / 2, 450 - height / 2, string);
            Sleep(2000);
            
            fillrectangle(320 - width / 2, 450 - height / 2, 320 + width / 2, 450 + height / 2);

            printf("\n\nInvalid Number! Please try again!\a\n\n");
        }
    }

    sprintf_s(strtemp, "The total price is $%d", price);
    string = strtemp;

    height = textheight(string);
    width = textwidth(string);

    outtextxy(320 - width / 2, 150 - height / 2, string);

    printf("\n\n---The total price is $%d", price);

    string = "Please insert your cash ($1,$2,$10):";

    height = textheight(string);
    width = textwidth(string);

    outtextxy(320 - width / 2, 240 - height / 2, string);

    while (1)
    {
        inserted = 0;
        printf("\n\nPlease insert your cash($1,$2,$10):");//模拟投币
        scanf_s("%d", &inserted);
        getchar();

        sprintf_s(strtemp, "%d", inserted);
        string = strtemp;

        height = textheight(string);
        width = textwidth(string);

        outtextxy(448 - width / 2, 240 - height / 2, string);

        if (inserted == 1 || inserted == 2 || inserted == 10)
        {
            paid = paid + inserted;

            if (paid >= price)
            {
                sprintf_s(strtemp, "Here is your change $%d", paid - price);
                string = strtemp;

                height = textheight(string);
                width = textwidth(string);

                outtextxy(320 - width / 2, 400 - height / 2, string);

                string = "Have a nice trip!";

                height = textheight(string);
                width = textwidth(string);

                outtextxy(320 - width / 2, 420 - height / 2, string);

                printf("\n\nHere is your change $%d", paid - price);
                printf("\n\nHave a nice trip!");

                Sleep(5000);
                break;
            }

            else
            {
                Sleep(500);
                fillrectangle(448 - width / 2, 240 - height / 2, 448 + width / 2, 240 + height / 2);//清除输入数字

                printf("\n\n$%d to be paid!\nPlease continue to insert.\a", price - paid);

                sprintf_s(strtemp, "$%d to be paid! Please continue to insert.", price - paid);
                string = strtemp;

                height = textheight(string);
                width = textwidth(string);

                outtextxy(320 - width / 2, 450 - height / 2, string);
                Sleep(2000);

                fillrectangle(320 - width / 2, 450 - height / 2, 320 + width / 2, 450 + height / 2);

            }
        }
        
        else
        {
            printf("\n\nInvalid Number! Please try again!\a\n\n");

            string = "Invalid Number! Please try again!";

            height = textheight(string);
            width = textwidth(string);

            outtextxy(320 - width / 2, 450 - height / 2, string);
            Sleep(2000);

            fillrectangle(320 - width / 2, 450 - height / 2, 320 + width / 2, 450 + height / 2);
        }
    }

    return 0;
}

int Path(LINE StationLine[ArraySize], int linenumber)
{
    int temp1 = 0, temp2 = 0, temp3 = 0, selection = 0;//临时计数变量
    int situation = 0;//三种不同的情况
    int line = 0;//当前循环线路
    int number = 0;//当前循环站数
    int solutionA = 0, solutionB = 0, finalsolution = 0;//两种解决方案（经过总站数）及最优解
    int tempsolution = 0;//临时方案储存

    char Departure[ArraySize];//起始站名
    char Terminal[ArraySize];//终到站名

    int Depln[ArraySize][3];//0列为可能起始线路，1列为该站编号（换乘站会有多个），可能线路数存到[0][2]
    int Terln[ArraySize][3];//0列为可能终到线路，1列为该站编号（换乘站会有多个），可能线路数存到[0][2]

    int Avoid[ArraySize];//循迹规避线路号
    int pass = 0;//pass+1表示已经可以回避的线路数

    int height = 0, width = 0;
    LPCSTR string;
    char strtemp[ArraySize];
    cleardevice();

    string = "@Copyright Matrix Inc -- All rights reserved";//版权信息

    height = textheight(string);
    width = textwidth(string);

    outtextxy(640 - width, 480 - height, string);

    string = "---Ticket---";

    height = textheight(string);
    width = textwidth(string);

    outtextxy(320 - width / 2, 50 - height / 2, string);

    string = "Departure Input:";
    outtextxy(220, 200, string);

    string = "Terminal Input:";
    outtextxy(220, 240, string);

    printf("\n\n--Ticket--");
    printf("\n\nPlease input a departure station by name:");
    fgets(Departure, ArraySize, stdin);//输入起始站名

    for (temp1 = 0;temp1 <= ArraySize;temp1++)//去除回车符
    {
        if (Departure[temp1] == '\n')
        {
            Departure[temp1] = '\0';
            break;
        }
    }

    string = Departure;
    outtextxy(340, 200, string);

    printf("\n\nPlease input a terminal station by name:");
    fgets(Terminal, ArraySize, stdin);//输入终到站名
    fflush(stdin);

    for (temp1 = 0;temp1 <= ArraySize;temp1++)//去除回车符
    {
        if (Terminal[temp1] == '\n')
        {
            Terminal[temp1] = '\0';
            break;
        }
    }

    string = Terminal;
    outtextxy(338, 240, string);

    temp1 = 0, temp2 = 0;
    for (line = 0;line <= linenumber - 1;line++)//检测输入车站所在线路及站号
    {
        for (number = 0;number <= StationLine[line].stationnumber - 1;number++)
        {
            if (strcmp(Departure, StationLine[line].station[number]) == 0)
            {
                Depln[temp1][0] = line;
                Depln[temp1][1] = number;
                temp1++;
            }

            if (strcmp(Terminal, StationLine[line].station[number]) == 0)
            {
                Terln[temp2][0] = line;
                Terln[temp2][1] = number;
                temp2++;
            }
        }
    }
    Depln[0][2] = temp1;//写入起始终到站的可能线路数
    Terln[0][2] = temp2;

    if (Depln[0][2] == 0 || Terln[0][2] == 0 || strcmp(Departure, Terminal) == 0)//三种出错情况
    {
        if (Depln[0][2] == 0)//起始站未找到
        {
            string = "Departure station was not found!";

            height = textheight(string);
            width = textwidth(string);

            outtextxy(320 - width / 2, 280 - height / 2, string);

            printf("\n\nDeparture station was not found!");
        }

        if (Terln[0][2] == 0)//终点站未找到
        {
            string = "Terminal station was not found!";

            height = textheight(string);
            width = textwidth(string);

            outtextxy(320 - width / 2, 300 - height / 2, string);

            printf("\n\nTerminal station was not found!");
        }

        if (strcmp(Departure, Terminal) == 0)//输入两站为同一站
        {
            string = "This is your terminal station. Turn around and find an exit!";

            height = textheight(string);
            width = textwidth(string);

            outtextxy(320 - width / 2, 320 - height / 2, string);

            printf("\n\nThis is your terminal station. Turn around and find an exit!");
        }

        string = "1-Retry";
        outtextxy(160, 360, string);

        string = "0-Main menu";
        outtextxy(320, 360, string);
         
        printf("\n\n0-Main menu\n1-Retry");

        while (1)
        {
            printf("\nPlease select an option:");//提示重新输入或回到主菜单
            scanf_s("%d", &selection);
            getchar();

            if (selection == 0)
            {
                return 0;//表示退回主菜单
            }

            else if (selection == 1)
            {
                return 1;//表示重试（退出重新加载函数）
            }

            else
            {
                printf("\n\nInvalid Number! Please try again!\a\n\n");

                string = "Invalid Number! Please try again!";

                height = textheight(string);
                width = textwidth(string);

                outtextxy(320 - width / 2, 450 - height / 2, string);
                Sleep(2000);

                fillrectangle(320 - width / 2, 450 - height / 2, 320 + width / 2, 450 + height / 2);
            }
        }
    }

    if (situation == 0)
    {
        for (temp1 = 0;temp1 <= Depln[0][2] - 1;temp1++)//第一种情况，起始终点站在同一线路，一层循环检验起始线路，二层循环检验终到线路
        {
            for (temp2 = 0;temp2 <= Terln[0][2] - 1;temp2++)
            {
                if (Depln[temp1][0] == Terln[temp2][0])
                {
                    situation = 1;//第一种情况成立
                    tempsolution = abs(Terln[temp2][1] - Depln[temp1][1]);//方案

                    if (solutionA == 0)//方案A赋值
                    {
                        solutionA = tempsolution;
                    }

                    if (solutionB == 0)//方案B赋值
                    {
                        solutionB = tempsolution;
                    }

                    if (solutionA != 0 && solutionB != 0)//清空较差方案，为后面的方案空出位置
                    {
                        if (solutionA >= solutionB)
                        {
                            solutionA = 0;
                        }
                        else
                        {
                            solutionB = 0;
                        }
                    }
                }
            }
        }
    }

    if (situation == 0)
    {
        for (temp1 = 0;temp1 <= Depln[0][2] - 1;temp1++)//temp1循环选定起始线路
        {
            for (pass = 0;pass <= Depln[0][2] - 2;pass++)//pass+1表示已经可以回避的线路数，当前选定的线路留到子函数再输入，-2是因为从0开始且跳过当前线路
            {
                temp2 = 0;//temp2指向可能起始线路在原数组的序号

                if (Depln[temp2][0] != Depln[temp1][0])//暂时跳开当前线路录入
                {
                    Avoid[pass] = Depln[temp2][0];//首先回避可能起初线路
                }
                
                temp2 ++;
            }

            ComplexRoute(StationLine, Terln, Avoid, Depln[temp1][0], Depln[temp1][1], pass, tempsolution, &solutionA, &solutionB);
        }

    }

    if (solutionA != 0 || solutionB != 0)//最后输出决定最优解
    {
        if (solutionA >= solutionB)
        {
            printf("\n\nThere are %d stations on your way", solutionA);
            finalsolution = solutionA;
        }
        else
        {
            printf("\n\nThere are %d stations on your way", solutionB);
            finalsolution = solutionB;
        }
    }

    sprintf_s(strtemp, "There are %d stations on your way", finalsolution);
    string = strtemp;

    height = textheight(string);
    width = textwidth(string);

    outtextxy(320 - width / 2, 280 - height / 2, string);

    if (situation == 0 || 1)//准备购票
    {
        string = "Buy a ticket now?";

        height = textheight(string);
        width = textwidth(string);

        outtextxy(320 - width / 2, 300 - height / 2, string);
        
        string = "0-Yes";
        outtextxy(160, 360, string);

        string = "1-No";
        outtextxy(320, 360, string);

        printf("\n\nBuy a ticket now?");
        printf("\n\n0-Yes\n1-No");

        while (1)
        {
            printf("\nPlease select an option:");//提示立即购票或回到主菜单
            scanf_s("%d", &selection);
            getchar();

            if (selection == 0)
            {
                Ticket(finalsolution);
                break;
            }

            else if (selection == 1)
            {
                return 0;//表示退回主菜单
            }

            else
            {
                printf("\n\nInvalid Number! Please try again!\a\n\n");

                string = "Invalid Number! Please try again!";

                height = textheight(string);
                width = textwidth(string);

                outtextxy(320 - width / 2, 450 - height / 2, string);
                Sleep(2000);

                fillrectangle(320 - width / 2, 450 - height / 2, 320 + width / 2, 450 + height / 2);
            }
        }
    }

    return 0;
}

void Quit()
{
    int height = 0, width = 0;//字符串的绘制长宽

    LPCSTR string;//字符串

    cleardevice();//清屏
    string = "---Thank you for using!---";//感谢使用

    height = textheight(string);
    width = textwidth(string);

    outtextxy(320 - width / 2, 200 - height / 2, string);

    string = "@Copyright Matrix Inc -- All rights reserved";//版权信息

    height = textheight(string);
    width = textwidth(string);

    outtextxy(640 - width, 480 - height, string);

    string = "Loading . . .";//模拟加载

    height = textheight(string);
    width = textwidth(string);

    outtextxy(320 - width / 2, 300 - height / 2, string);

    Sleep(3000);//延时
    
    return;
}

int main()
{
    int numbera = 0, numberb = 0, charac = 0, linea = 0, lineb = 0, temp = 0, selection = 0, ferror = 0;
    int linenumber = 2;//线路总数

    initgraph(640, 480);

    LINE StationLine[ArraySize] = {0};//定义结构体数组时元素初始化，否则计算容易出错

    FILE* fp=NULL;//文件编写格式如下：总线路数，线路1总站数，线路1站名1，...（数据之间空出一行）
    ferror = fopen_s(&fp, "Stations.txt", "r");//打开文件

    if (ferror!=NULL)//读取文件失败，退出程序
    {
        printf("File opening failed!\a");
        return 0;
    }

    fscanf_s(fp, "%d", &linenumber);//读取线路总数
    fgetc(fp);

    for (linea = 0;linea <= linenumber - 1;linea++)//分线路读取站数及各站名
    {      
        fgetc(fp);
        fscanf_s(fp, "%d", &StationLine[linea].stationnumber);//站数
        fgetc(fp);

        for (numbera = 0;numbera <= StationLine[linea].stationnumber - 1;numbera++)//站名
        {
            fgetc(fp);
            fgets(StationLine[linea].station[numbera], ArraySize, fp);

            for (charac = 0;charac <= ArraySize; charac++)
            {
                if (StationLine[linea].station[numbera][charac] == '\n')
                {
                    StationLine[linea].station[numbera][charac] = '\0';//去除回车符
                    break;
                }
            }
        }
    }

    ferror=fclose(fp);//关闭文件
    if (ferror != NULL)//文件关闭失败，结束程序
    {
        printf("File closing failed!\a");
        return 0;
    }

    for (linea = 0;linea <= linenumber - 1;linea++)//换乘站检测
    {
        for (lineb = linea + 1;lineb <= linenumber - 1;lineb++)
        {
            for (numbera = 0;numbera <= StationLine[linea].stationnumber - 1;numbera++)
            {
                for (numberb = 0;numberb <= StationLine[lineb].stationnumber - 1;numberb++)
                {
                    if (strcmp(StationLine[linea].station[numbera], StationLine[lineb].station[numberb]) == 0)//记录换乘站
                    {
                        StationLine[linea].interchange[StationLine[linea].internumber][0] = numbera;
                        StationLine[linea].interchange[StationLine[linea].internumber][1] = lineb;
                        StationLine[linea].interchange[StationLine[linea].internumber][2] = numberb;
                        StationLine[linea].internumber++;

                        StationLine[lineb].interchange[StationLine[lineb].internumber][0] = numberb;
                        StationLine[lineb].interchange[StationLine[lineb].internumber][1] = linea;
                        StationLine[lineb].interchange[StationLine[lineb].internumber][2] = numbera;
                        StationLine[lineb].internumber++;
                    }
                }
            }
        }
    }

    Welcome();//欢迎界面显示

    while (1)
    {
        switch (selection)
        {
            case 0://进入菜单
            {
                selection = Menu();
                break;
            }

            case 1://进入购票页面
            {
                selection = Path(StationLine, linenumber);
                break;
            }

            case 2://进入地图页面
            {
                selection = Map(StationLine,linenumber);
                break;
            }

            case 3://退出系统
            {
                Quit();
                return 0;
            }

            case 4://站名搜索
            {
                selection = Search(StationLine,linenumber);
                break;
            }
        }
    }

    return 0;
}
