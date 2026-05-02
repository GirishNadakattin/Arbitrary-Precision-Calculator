#include "header.h"

int addition(Dlist **tail1,Dlist **tail2,Dlist **headR,Dlist **tailR)
{
    Dlist *temp1 = *tail1;
    Dlist *temp2 = *tail2;
    int data,carry=0;
    while(temp1 || temp2)
    {
        if(temp1 && temp2)
        {
            data = temp1->data + temp2->data + carry;
            carry = 0;
            if(data>9)
            {
                dl_insert_first(headR,tailR,data%10);
                carry=1;
            }
            else
            {
                dl_insert_first(headR,tailR,data);
            }
            temp1 = temp1->prev;
            temp2 = temp2->prev;
        }
        else if(temp1 !=NULL && temp2 == NULL)
        {
            data = temp1->data + carry;

            carry = 0;

            if(data > 9)
            {
                dl_insert_first(headR, tailR, (data % 10));
                carry = 1;
            }
            else
            {
                dl_insert_first(headR, tailR, data);
            }
            temp1 = temp1->prev;
        }
        else if(temp1 == NULL && temp2 != NULL)
        {
            data = temp2->data + carry;

            carry = 0;

            if(data > 9)
            {
                dl_insert_first(headR, tailR, (data % 10));
                carry = 1;
            }
            else
            {
                dl_insert_first(headR, tailR, data);
            }

            temp2 = temp2->prev;
        }
    }

    if(carry==1)
    {
        dl_insert_first(headR,tailR,carry);
        carry=0;
    }
  

    return SUCCESS;
}

int substraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    if((*tail1) == NULL && (*tail2) == NULL)
    {
        return FAILURE;
    }

    //take two temprory pointer to traverse backword
    Dlist *temp1 = (*tail1);
    Dlist *temp2 = (*tail2);

    int data = 0, borrow = 0;
    while(temp1 || temp2)
    {
        if(temp1 && temp2)
        {
            data = temp1->data - borrow - temp2->data;

            if(data < 0)
            {
                data += 10;
                borrow = 1;
            }
            else
            {
                borrow = 0;
            }

            dl_insert_first(headR,tailR,data);

            temp1  = temp1->prev;
            temp2 = temp2->prev;
        }
        else if(temp1 != NULL && temp2 == NULL)
        {
            data = temp1->data - borrow;

            if(data < 0)
            {
                data += 10;
                borrow = 1;
            }
            else
            {
                borrow = 0;
            }

            temp1 = temp1->prev;
            dl_insert_first(headR,tailR,data);
        }
        else if(temp1 == NULL && temp2 != NULL)
        {
            data = temp2->data - borrow;

            if(data < 0)
            {
                data += 10;
                borrow = 1;
            }
            else
            {
                borrow = 0;
            }

            temp2 = temp2->prev;
            dl_insert_first(headR,tailR,data);
            borrow = 0;
        }
    }

    //remove Leading zeros
    while(*headR && (*headR)->data == 0 && (*headR)->next)
    {
        Dlist *temp = *headR;
        *headR = (*headR)->next;
        (*headR)->prev = NULL;
        free(temp);
    }

    return SUCCESS;
}

int multiplication(Dlist **tail1,Dlist **tail2,Dlist **headR,Dlist **tailR)
{
    if((*tail1)==NULL && (*tail2) == NULL)
    {
        return FAILURE;
    }
    Dlist *temp2 = *tail2;
    Dlist *headT2 = NULL;
    Dlist *tailT2 = NULL;

    int flag = 0;
    while(temp2)
    {
        int carry = 0;
        Dlist *temp1 = (*tail1);

        // Extra list for storing one - one digit multiplication result
        Dlist *headT1 = NULL;
        Dlist *tailT1 = NULL;

        // case1: Multiply entire list1 with one digit of list2
        while(temp1)
        {
            int data = (temp1 -> data * temp2 -> data) + carry;

            dl_insert_first(&headT1, &tailT1, (data%10));
            carry = (data/10);
         
            temp1 = temp1 -> prev;
        }
        if(carry > 0)
        {
            dl_insert_first(&headT1, &tailT1,carry);
        }

        // Add zeros at last
        for(int i = 0; i < flag; i++)
        {
            dl_insert_last(&headT1, &tailT1, 0);
        }

        // store temp1 list (headt1 & tailt1) into temp2 list
        if(headT2 == NULL)
        {
            headT2 = headT1;
            tailT2 = tailT1;
        }
        else
        {
            // Reset result list
            *headR = NULL;
            *tailR = NULL;

            //add T1 + T2
            addition(&tailT1, &tailT2, headR, tailR);

            //delete T1
            delete_list(&headT1, &tailT1);

            //delete T2
            delete_list(&headT2, &tailT2);

            //store addition result into T2
            Dlist *tempR = *headR;
            while(tempR != NULL)
            {
                dl_insert_last(&headT2, &tailT2, tempR->data);
                tempR = tempR->next;
            }
        }

        flag++;
        temp2 = temp2 -> prev;
    }

    // clear result before final copy
    *headR = NULL;
    *tailR = NULL;

    //copy T2 into result list
    Dlist *temp = headT2;

    while(temp != NULL)
    {
        dl_insert_last(headR, tailR, temp -> data);
        temp = temp -> next;
    }

    // Delete temp list 
    delete_list(&headT2, &tailT2);

    check_zero(headR,tailR);
    return SUCCESS;
}

int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    if((*tail1) == NULL && (*tail2) == NULL)
    {
        return FAILURE;
    }

    if(check_zero_for_div(head2, tail2))
    {
        printf("Division by zero not possible\n");
        return FAILURE;
    }

    // If operand2 > operand1 quotient = 0 */
    if(list_comp(head1, head2) == 0)
    {
        dl_insert_first(headR, tailR, 0);
        return SUCCESS;
    }

    Dlist *count_H1 = NULL;
    Dlist *count_T1 = NULL;

    //initially count1 list initialize with 0
    dl_insert_first(&count_H1, &count_T1,0);

    Dlist *count_H2 = NULL;
    Dlist *count_T2 = NULL;

    //initially count2 list initialize with 1
    dl_insert_first(&count_H2, &count_T2,1);

    while(list_comp(head1,head2))
    {
        substraction(head1, tail1, head2, tail2, headR, tailR);

        // Delete old node
        delete_list(head1, tail1);

        //copy headR into head1 (new node)
        Dlist *temp = (*headR);

        while(temp != NULL)
        {
            dl_insert_last(head1, tail1, temp -> data);
            temp = temp -> next;
        }

        //delete / reset result list
        delete_list(headR, tailR);

        //create one more list to perform count
        Dlist *res_countH = NULL;
        Dlist *res_countT = NULL;

        //add count lists
        addition(&count_T1, &count_T2, &res_countH, &res_countT);

        //delete count_list 1
        delete_list(&count_H1, &count_T1);

        //reset count 1 with result count
        count_H1 = res_countH;
        count_T1 = res_countT;
    }

    //copy final aswer into result list

    Dlist *t = count_H1;
    while(t != NULL)
    {
        dl_insert_last(headR, tailR, t->data);
        t = t->next;
    }

    delete_list(&count_H1, &count_T1);
    delete_list(&count_H2, &count_T2);

    return SUCCESS;
}