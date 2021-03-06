#include <stdio.h>
#include <stdlib.h>
#include "head.h"

int is_true_ballqueue(LinkQueue *q)
{
    int i = 1;
    LinkNode *p = q->front->next;

    for(i = 1;i <= 27;i ++)
    {
        if(p->data != i)
            return 0;
        p = p->next;
    }

    return 1;
}

int main(int argc, const char *argv[])
{
    int i;
    int day;
    int ball;
    int ball_last;
    LinkQueue *ball_Lq;
    LinkStack *ball_1_mLs;
    LinkStack *ball_5_mLs;
    LinkStack *ball_1_hLs;

    ball_Lq = create_linkqueue();
    ball_1_mLs = create_empty_linkstack();
    ball_5_mLs = create_empty_linkstack();
    ball_1_hLs = create_empty_linkstack();


    //队列ball_Lq初始化
    for (i = 1; i <= 27; i++)
    {
        enter_linkqueue(ball_Lq,i);
    }

    day = 0;
    //当ball_Lq顺序不为1-27时，则循环end
    while (1)
    {
        if (ball_1_mLs->n < 4)
        {
            ball = delete_linkqueue(ball_Lq);
            push_linkstack(ball_1_mLs,ball);
        }
        else if (ball_1_mLs->n == 4 && ball_5_mLs->n < 11)
        {
            while (!is_empty_linkstack(ball_1_mLs))
            {
                ball = pop_linkstack(ball_1_mLs);
                enter_linkqueue(ball_Lq,ball);
            }

            ball = delete_linkqueue(ball_Lq);
            push_linkstack(ball_5_mLs,ball);
        }
        else if (ball_1_mLs->n == 4 && ball_5_mLs->n == 11 && ball_1_hLs->n <= 11)
        {
            while (!is_empty_linkstack(ball_5_mLs))
            {
                ball = pop_linkstack(ball_5_mLs);
                enter_linkqueue(ball_Lq,ball);
            }
            while (!is_empty_linkstack(ball_1_mLs))
            {
                ball = pop_linkstack(ball_1_mLs);
                enter_linkqueue(ball_Lq,ball);
            }

            ball = delete_linkqueue(ball_Lq);
            push_linkstack(ball_1_hLs,ball);
            if (ball_1_hLs->n == 12)
            {
                ball_last = pop_linkstack(ball_1_hLs);
                while (!is_empty_linkstack(ball_1_hLs))
                {
                    ball = pop_linkstack(ball_1_hLs);
                    enter_linkqueue(ball_Lq,ball);
                }
                enter_linkqueue(ball_Lq,ball_last);
                ++day;

                if (is_true_ballqueue(ball_Lq))
                {
                    printf("day = %d\n",day/2);
                    return 1;
                }
            }
        }
        //////////////////////////////
#if 0/*{{{*/
        if (ball_1_mLs->n == 4 && ball_5_mLs->n == 11 && ball_1_hLs->n == 11)
        {
            while (!is_empty_linkstack(ball_1_hLs))
            {
                ball = pop_linkstack(ball_1_hLs);
                enter_linkqueue(ball_Lq,ball);
            }
            ball = delete_linkqueue(ball_Lq);
            enter_linkqueue(ball_Lq,ball);
            while (!is_empty_linkstack(ball_5_mLs))
            {
                ball = pop_linkstack(ball_5_mLs);
                enter_linkqueue(ball_Lq,ball);
            }
            while (!is_empty_linkstack(ball_1_mLs))
            {
                ball = pop_linkstack(ball_1_mLs);
                enter_linkqueue(ball_Lq,ball);
            }

            ++day;

            if (is_true_ballqueue(ball_Lq))
            {
                printf("day = %d\n",day/2);
                return 1;
            }
        }
#endif/*}}}*/
    }
    return 0;
}
