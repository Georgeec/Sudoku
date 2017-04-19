#include<iostream>
#include<algorithm>
#include<time.h>
#include<cstdlib>
using namespace std;

class sudoku
{
private:
    int row,col,count;                                 //row:��  col����  count��Ϊ���������ֵΪ81
    int question_array[9][9],answer_array[9][9];       //qustionΪ�û�������������answerΪ���
    void printf(int **a,int n);                        //���9*9����
    bool is_place(int cnt);                            //����count�жϸ�λ���Ƿ��ܹ�����������������
    void creat_partsudoku();                           //���첿�ֵ�����������qustion���飬�����������������Ŀ
    void creat_allsudoku(int cnt);
public:
    sudoku();                                          //���캯����������������г�ʼ�����
    void creat_allsudoku(){ creat_allsudoku(count); }  //�������������������丳��question��answer����
};

sudoku::sudoku()
{
    int temp;
    srand(time(0));

    /*��ʼ��answer����*/
    for(int i=0;i<9;++i)
        for(int j=0;j<9;++j)
            answer_array[i][j]=0;

    /*��һ������������������*/
    for(int i=0;i<9;++i)
    {
        temp=rand()%81;
        answer_array[temp/9][temp%9]=i+1;
    }

    count=0;
}

void sudoku::printf(int **a,int n)
{
    for(int i=0;i<n;++i)
    {
        if(i%3==0)
            cout<<endl;

        for(int j=0;j<n;++j)
        {
            if(j%3==0)
                cout<<" ";

            if(a[i][j]==0)
                cout<<"*"<<" ";
            else
                cout<<a[i][j]<<" ";
        }
        cout<<endl;
    }
}

bool sudoku::is_place(int cnt)
{
    /*count�ı仯��Χ��0~81�����������ȣ��������·�ʽ����ÿһ��λ��*/
    row=cnt/9;
    col=cnt%9;

    /*�������ж�ͬһ��ÿһ���У��Ƿ�����ͬ��Ԫ��*/
    for(int i=0;i<9;++i)
        if(answer_array[row][col]==answer_array[row][i]&&i!=col)
           return false;

    /*�������ж�ͬһ��ÿһ���У��Ƿ�����ͬ��Ԫ��*/
    for(int i=0;i<9;++i)
        if(answer_array[row][col]==answer_array[i][col]&&i!=row)
           return false;

    /*�������ж�ÿһ��3*3��С������Ƿ�����ͬ��Ԫ��*/
    int temprow=row/3*3;
    int tempcol=col/3*3;

    for(int i=temprow;i<temprow+3;++i)
        for(int j=tempcol;j<tempcol+3;++j)
            if(answer_array[row][col]==answer_array[i][j]&&i!=row&&j!=col)
               return false;

    return true;
}

void sudoku::creat_allsudoku(int cnt)
{
    /*count�ı仯��Χ��0~81�����������ȣ��������·�ʽ����ÿһ��λ��*/
    srand(time(0));
    row=cnt/9;
    col=cnt%9;

    /*�ж�cnt�����Ƿ�ﵽ81.����ﵽ��˵���������������Ѿ��������*/
    if(cnt==81)
    {
        /*���Ѿ��������answer����qustion����*/
        for(int i=0;i<9;++i)
            for(int j=0;j<9;++j)
                question_array[i][j]=answer_array[i][j];

        /*��qustion���������������ڶ����γ�������Ŀ*/
        for(int i=0;i<9;++i)
            for(int j=0;j<6;++j)
            {
                int temp=rand()%9;
                question_array[i][temp]=0;
            }

        for(int i=0;i<9;++i)
        {
            for(int j=0;j<9;++j)
                cout<<question_array[i][j]<<" ";
            cout<<endl;
        }

        cout<<endl;

        //printf((int**)answer_array,9);
        return ;
    }

    /*��������cnt==81����ô�жϸ�λ���Ƿ������д���֣�
      ���������ݹ���һ�㣬��������˻ص���ʼ״̬*/
    if(answer_array[row][col]==0)
    {
        for(int i=1;i<=9;++i)
        {
            answer_array[row][col]=i;
            if(is_place(cnt))
               creat_allsudoku(cnt+1);
        }
        answer_array[row][col]=0;
    }
    else
        creat_allsudoku(cnt+1);
}

int main()
{
    sudoku one;
    one.creat_allsudoku();
}

