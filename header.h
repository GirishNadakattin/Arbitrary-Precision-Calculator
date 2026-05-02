#ifndef APC_L
#define APC_L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SUCCESS 0
#define FAILURE -1
#define LIST_EMPTY -2
#define DATA_NOT_FOUND -3

typedef struct node
{
	int data;
	struct node *prev;
	struct node *next;
}Dlist;

int dl_insert_last(Dlist **head, Dlist **tail, int data);
void print_list(Dlist *head);
int valid_opr(char *op);
int check_sign(char *str);
int create( Dlist **head, Dlist **tail,char *str);
int dl_insert_first(Dlist **head, Dlist **tail, int data);
int addition(Dlist **tail1,Dlist **tail2,Dlist **headR,Dlist **tailR);
int substraction(Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2,Dlist **headR,Dlist **tailR);
int list_comp(Dlist **head1,Dlist **head2);
int multiplication(Dlist **tail1,Dlist **tail2,Dlist **headR,Dlist **tailR);
int delete_list(Dlist **head, Dlist **tail);
void check_zero(Dlist **head, Dlist **tail);
int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);
int check_zero_for_div(Dlist **head, Dlist **tail);
void remove_leading_zeros(Dlist **head, Dlist **tail);
#endif