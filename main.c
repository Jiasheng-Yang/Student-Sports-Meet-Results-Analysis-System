#include<stdio.h>
#include <string.h>
#include<math.h>
#include <conio.h>
#include <process.h>

// 学校个数
#define n 3
// 男子项目个数
#define m 2
// 女子项目个数
#define w 2
// 项目前三名
#define r 3
// 字符串长度
#define STR_LEN (10)

// 初始化状态
#define INIT_STATUS (-1)

// 积分
int g_sportScore[r+1] = {0, 5, 3, 2};

typedef struct Sport_
{
    // 项目排名
    int rank;
} Sport;

typedef struct School_
{
    // 学校编号
    int no;
    // 学校名称
    char name[STR_LEN];
    // 学校总分
    int sscore;
    // 男团总分
    int mscore;
    // 女团总分
    int wscore;
    // 具体项目
    Sport sports[m+w+1];
} School;

typedef struct Node
{
    School s;
    struct Node *next;
} SNode;

SNode *head = 0;
SNode *end = 0;
// 节点总个数
int NN = 0;

// 添加节点
void addNode(School s)
{
    SNode *temp = (SNode*)malloc(sizeof(SNode));
    temp->s = s;
    temp->next = 0;

    if(head == 0) {
        head = temp;
    } else {
        end->next = temp;
    }
    end = temp;

    ++NN;
}

// 删除节点
void DelNodes()
{
    SNode *temp = head;
    while (temp != NULL) {
        SNode* pt =temp;
        temp = temp->next;
        free(pt);
    }
    head = NULL;
    end = NULL;
}

// 初始化学校
void initSchool(School *s)
{
    int j;
    if (s == 0) return;
    s->no = INIT_STATUS;
    s->name[0] = '\0';
    s->sscore = 0;
    s->mscore = 0;
    s->wscore = 0;
    for(j = 0; j < m+w+1; j++) {
        s->sports[j].rank = INIT_STATUS;
    }
}

// 获取回车换行符
void getN()
{
    char c;
    while((c = getchar()) != '\n' && c != EOF);
}

// 输入学校和项目信息
void input()
{
    int i, j, c;
    School s;

    // 文件读取会导致读满
    if (NN == n) {
        printf("输入已满,退出输入\n");
        return;
    }

    printf("*****学校共有%d个，编号为1~%d*****\n",n,n);
    printf("*****男子项目共有%d个，编号为1~%d*****\n",m,m);
    printf("*****女子项目共有%d个，编号为%d~%d*****\n",w,m+1,m+w);
    printf("*****其中每个项目取1~3名*****\n\n");

    for (i = 0; i < n; i++)
    {
        initSchool(&s);

        printf("请输入学校编号:");
        scanf("%d", &s.no);
        printf("请输入学校名称(英文):");
        scanf("%s", s.name);

        for (j = 1; j < m+w+1; j++)
        {
            printf("请输入项目%d的名次:",j);
            scanf("%d", &s.sports[j].rank);

            // 学校总分
            s.sscore += g_sportScore[s.sports[j].rank];

            // 男团总分
            if (j <= m) {
                s.mscore += g_sportScore[s.sports[j].rank];
            }
        }

        // 女团总分
        s.wscore = s.sscore - s.mscore;

        addNode(s);

        if (NN == n) {
            printf("输入已满,退出输入\n");
            return;
        }

        printf("输入0退出输入,输入1继续:");
        scanf("%d", &c);

        if (c == 0)
            break;
    }
}

// 保存到文件
void save()
{
    FILE *f;
    SNode *temp = head;

    if ((f = fopen("school.txt", "w")) == NULL)
    {
        printf("不能打开文件\n");
        exit(1);
    }

    while (temp != 0) {
        fwrite(&temp->s,sizeof(School),1,f);
        temp = temp->next;
    }
    fclose(f);
}

// 从文件读取
void read()
{
    FILE *f;
    int len = sizeof(School);
    School s;
    if ((f = fopen("school.txt", "r")) == NULL)
    {
        printf("不能打开缓存文件,请检查文件是否存在\n");
        return;
    }

    while (1) {
        len = fread(&s,sizeof(School),1,f);
        if (len == 1) {
            addNode(s);
        } else {
            break;
        }
    }

    fclose(f);
}

// 显示学校整体信息
void output()
{
    int choice;
    int i, j;
    SNode *temp = head;
    SNode *SNS[n];

    if (NN == 0) {
        printf("无学校和项目信息\n");
        return;
    }

    do
    {
        printf("*****1.按学校编号输出.*****\n");
        printf("*****2.按学校名称输出.*****\n");
        printf("*****3.按学校总分输出.*****\n");
        printf("*****4.按男团总分输出.*****\n");
        printf("*****5.按女团总分输出.*****\n");
        printf("*****0.退出.*****\n");
        printf("请选择编号:");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            // 初始化数组
            temp = head;
            for (i = 0; i < NN; ++i) {
                SNS[i] = temp;
                temp = temp->next;
            }
            // 冒泡排序
            for (i = 0; i < NN-1; ++i) {
                for (j = 0; j < NN-1-i; ++j) {
                    if (SNS[j]->s.no > SNS[j+1]->s.no) {
                        temp = SNS[j];
                        SNS[j] = SNS[j+1];
                        SNS[j+1] = temp;
                    }
                }
            }

            for (i = 0; i < NN; ++i) {
                printf("\n学校编号:%d,学校名称:%s,学校总分:%d,男团总分:%d,女团总分:%d\n",
                       SNS[i]->s.no,SNS[i]->s.name,SNS[i]->s.sscore,SNS[i]->s.mscore,SNS[i]->s.wscore);
            }

            break;

        case 2:
            // 初始化数组
            temp = head;
            for (i = 0; i < NN; ++i) {
                SNS[i] = temp;
                temp = temp->next;
            }
            // 冒泡排序
            for (i = 0; i < NN-1; ++i) {
                for (j = 0; j < NN-1-i; ++j) {
                    if (strcmp(SNS[j]->s.name,SNS[j+1]->s.name) > 0) {
                        temp = SNS[j];
                        SNS[j] = SNS[j+1];
                        SNS[j+1] = temp;
                    }
                }
            }

            for (i = 0; i < NN; ++i) {
                printf("\n学校编号:%d,学校名称:%s,学校总分:%d,男团总分:%d,女团总分:%d\n",
                       SNS[i]->s.no,SNS[i]->s.name,SNS[i]->s.sscore,SNS[i]->s.mscore,SNS[i]->s.wscore);
            }

            break;

        case 3:
            // 初始化数组
            temp = head;
            for (i = 0; i < NN; ++i) {
                SNS[i] = temp;
                temp = temp->next;
            }
            for (i = 0; i < NN-1; ++i) {
                for (j = 0; j < NN-1-i; ++j) {
                    if (SNS[j]->s.sscore < SNS[j+1]->s.sscore) {
                        temp = SNS[j];
                        SNS[j] = SNS[j+1];
                        SNS[j+1] = temp;
                    }
                }
            }

            for (i = 0; i < NN; ++i) {
                printf("\n学校编号:%d,学校名称:%s,学校总分:%d,男团总分:%d,女团总分:%d\n",
                       SNS[i]->s.no,SNS[i]->s.name,SNS[i]->s.sscore,SNS[i]->s.mscore,SNS[i]->s.wscore);
            }
            break;

        case 4:
            // 初始化数组
            temp = head;
            for (i = 0; i < NN; ++i) {
                SNS[i] = temp;
                temp = temp->next;
            }
            for (i = 0; i < NN-1; ++i) {
                for (j = 0; j < NN-1-i; ++j) {
                    if (SNS[j]->s.mscore < SNS[j+1]->s.mscore) {
                        temp = SNS[j];
                        SNS[j] = SNS[j+1];
                        SNS[j+1] = temp;
                    }
                }
            }

            for (i = 0; i < NN; ++i) {
                printf("\n学校编号:%d,学校名称:%s,学校总分:%d,男团总分:%d,女团总分:%d\n",
                       SNS[i]->s.no,SNS[i]->s.name,SNS[i]->s.sscore,SNS[i]->s.mscore,SNS[i]->s.wscore);
            }
            break;

        case 5:
            // 初始化数组
            temp = head;
            for (i = 0; i < NN; ++i) {
                SNS[i] = temp;
                temp = temp->next;
            }
            for (i = 0; i < NN-1; ++i) {
                for (j = 0; j < NN-1-i; ++j) {
                    if (SNS[j]->s.wscore < SNS[j+1]->s.wscore) {
                        temp = SNS[j];
                        SNS[j] = SNS[j+1];
                        SNS[j+1] = temp;
                    }
                }
            }

            for (i = 0; i < NN; ++i) {
                printf("\n学校编号:%d,学校名称:%s,学校总分:%d,男团总分:%d,女团总分:%d\n",
                       SNS[i]->s.no,SNS[i]->s.name,SNS[i]->s.sscore,SNS[i]->s.mscore,SNS[i]->s.wscore);
            }
            break;
        default:
            break;
        }

    } while (choice != 0);
}

// 查询
void query()
{
    int choice;
    int i, j, k;
    SNode *temp = head;
    SNode *SNS[n];

    if (NN == 0) {
        printf("无学校和项目信息\n");
        return;
    }

    do
    {
        printf("*****1.按学校编号输出.*****\n");
        printf("*****2.按项目编号输出.*****\n");
        printf("*****0.退出.*****\n");
        printf("请选择编号:");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("请输入学校编号:");
            scanf("%d", &i);
            if (i < 1 || i > n) {
                printf("请选择正确的编号\n");
                break;
            }

            printf("请输入项目编号:");
            scanf("%d", &j);
            if (j < 1 || j > m+w) {
                printf("请选择正确的编号\n");
                break;
            }

            temp = head;
            while (temp != 0) {
                if (temp->s.no == i) {
                    printf("\n学校编号:%d,学校名称:%s,项目编号:%d,得分:%d\n",
                           i, temp->s.name, j, g_sportScore[temp->s.sports[j].rank]);
                    break;
                }
                temp = temp->next;
            }

            break;

        case 2:
            printf("请输入项目编号:");
            scanf("%d", &k);
            if (k < 1 || k > m+w) {
                printf("请选择正确的编号\n");
                break;
            }

            // 初始化数组
            temp = head;
            for (i = 0; i < NN; ++i) {
                SNS[i] = temp;
                temp = temp->next;
            }
            // 冒泡排序
            for (i = 0; i < NN-1; ++i) {
                for (j = 0; j < NN-1-i; ++j) {
                    if (SNS[j]->s.sports[k].rank > SNS[j+1]->s.sports[k].rank) {
                        temp = SNS[j];
                        SNS[j] = SNS[j+1];
                        SNS[j+1] = temp;
                    }
                }
            }

            for (i = 0; i < (3 < n ? 3 : n); ++i) {
                printf("\n学校编号:%d,学校名称:%s,得分:%d\n",
                       SNS[i]->s.no,SNS[i]->s.name,g_sportScore[SNS[i]->s.sports[k].rank]);
            }

            break;
        default:
            break;
        }

    } while (choice != 0);
}

// 显示菜单，获取输入
int showMenu()
{
    int c = 0;
    printf("*****************运动会分数统计系统********************\n");
    printf("********************1.输入信息*************************\n");
    printf("********************2.输出信息*************************\n");
    printf("********************3.查询信息*************************\n");
    printf("********************0.退出系统*************************\n");
    printf("================================================\n");
    printf("********请选择要步骤编号:");
    scanf("%d", &c);
    return c;
}

int main()
{
    int choice;

    // 初始化读取
    read();

    do {
        choice = showMenu();
        switch (choice) {
        case 1:
            input();
            break;
        case 2:
            output();
            break;
        case 3:
            query();
            break;
        case 0:
            break;
        default:
            printf("输入错误,请重新输入\n");
            break;
        }
    } while (choice != 0);

    // 保存结果
    save();

    return 0;
}
