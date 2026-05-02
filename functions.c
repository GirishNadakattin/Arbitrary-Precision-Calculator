#include "header.h"

int create(Dlist **head, Dlist **tail,char *str)
{
    int i = 0;

    while(str[i] != '\0')
    {
        if(str[i] < '0' || str[i] > '9')
            return FAILURE;

        int data = str[i] - '0';
        dl_insert_last(head, tail, data);
        i++;
    }
	return 	SUCCESS;
}

int valid_opr(char *op)
{
    if(strlen(op) != 1)
    {
        return FAILURE;
    }

    if(op[0] == '+' || op[0] == '-' || op[0] == '*' || op[0] == '/')
    {
        return SUCCESS;
    }

    return FAILURE;
}

int check_sign(char *str)
{
    int i = 0;
    int sign = 0;   // Store sign (0 = + , 1 = -)

    // Check for '+' sign
    if(str[i] == '+')
    {
        sign = 0;
        i++;
    }
    // Check for '-' sign
    else if(str[i] == '-')
    {
        sign = 1;
        i++;
    }

    // Ensure first character after sign is digit
    if(!(str[i] >= '0' && str[i] <= '9'))
    {
        printf("Invalid operands!\n");
        return -1;
    }

    // Store starting index of digits
    int start = i;

    // Validate remaining characters are digits
    while(str[i])
    {
        if(!(str[i] >= '0' && str[i] <= '9'))
        {
            printf("Invalid operands!\n");
            return -1;
        }
        i++;
    }

    // Remove sign and shift digits
    int j = 0;
    while(str[start])
    {
        str[j++] = str[start++];
    }
    str[j] = '\0';

    return sign;
}

int dl_insert_last(Dlist **head, Dlist **tail, int data)
{
    Dlist *new = malloc(sizeof(Dlist));
    if(!new)
    return FAILURE;
    
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    
    if(*head == NULL)
    {
        (*head) = (*tail) = new;
        return SUCCESS;
    }
    new->prev = (*tail);
    (*tail)->next = new;
    (*tail) = new;
	return SUCCESS;
}

int dl_insert_first(Dlist **head, Dlist **tail, int data)
{
    Dlist *new = malloc(sizeof(Dlist));
    if(!new)
    return FAILURE;
    
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    
    if(*head == NULL)
    {
        (*head) = (*tail) = new;
        return SUCCESS;
    }
    new->next = *head;
    (*head)->prev = new;
    *head = new;
    return SUCCESS;
}
int list_comp(Dlist **head1,Dlist **head2)
{
    int list1_count = 0;
    int list2_count = 0;
    Dlist *temp1 = *head1;
    Dlist *temp2 = *head2;
    while(temp1)
    {
        list1_count++;
        temp1 = temp1->next;
    }
    while(temp2)
    {
        list2_count++;
        temp2 = temp2->next;
    }
    temp1 = *head1;
    temp2 = *head2;
    if(list1_count > list2_count)
        return 1;
    else if(list1_count < list2_count)
        return 0;
    else
    {
        while(temp1 && temp2)
        {
            if(temp1->data > temp2->data)
            {
                return 1;
            }
            else if(temp1->data < temp2->data)
            {
                return 0;
            }
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
    }
    return -1;
}

int delete_list(Dlist **head, Dlist **tail)
{
    // Check list empty
    if((*head) == NULL)
    {
        return FAILURE;
    }
    
    Dlist *temp = (*head);
    
    while(temp != NULL)
    {
        (*head) = temp -> next;
        free(temp);
        temp = (*head);
    }
    
    (*head) = (*tail) = NULL;
    return SUCCESS;
}

void check_zero(Dlist **head, Dlist **tail)
{
  while(*head && (*head)->data == 0 && (*head)->next)
  {
    Dlist *temp = *head;
    *head = (*head)->next;
    (*head)->prev = NULL;
    free(temp);
  }
}

int check_zero_for_div(Dlist **head, Dlist **tail)
{
    // If list empty treat as zero
    if(*head == NULL)
    {
        return 1;
    }

    Dlist *temp = *head;

    // Traverse entire list
    while(temp != NULL)
    {
        if(temp->data != 0)
        {
            // Found non-zero digit
            return 0;
        }
        temp = temp->next;
    }

    // All digits are zero 
    return 1;
}
void remove_leading_zeros(Dlist **head, Dlist **tail)
{
    while(*head && (*head)->data == 0 && (*head)->next != NULL)
    {
        Dlist *temp = *head;
        *head = (*head)->next;
        (*head)->prev = NULL;
        free(temp);
    }
}

