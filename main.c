#include<stdio.h>
#include"header.h"
int main(int argc, char *argv[])
{
    if(argc != 4)
    {
        printf("INFO : give commands correctly\n");
        printf("USAGE : ./output.exe <Operand 1> <Operator> <Operand 2>\n");
        return 0;
    }

    if(valid_opr(argv[2]) == FAILURE)
    {
        printf("Error: Invalid operator\n");
        return FAILURE;
    }

    char *op1 = argv[1];
    char *opr = argv[2];
    char *op2 = argv[3];

    int i=1,data;
    Dlist *head1 = NULL,*tail1= NULL;
    Dlist *head2 = NULL,*tail2= NULL;
    Dlist *headR = NULL, *tailR= NULL;

    // Extract signs
    int sign1 = check_sign(op1);

    if(sign1 == -1)
    {
        return 0;   // Stop program
    }

    int sign2 = check_sign(op2);

    if(sign2 == -1)
    {
        return 0;
    }
    create(&head1,&tail1,argv[1]);
    create(&head2,&tail2,argv[3]);
    

    printf("Operand1 : ");
    print_list(head1);
    printf("\n");

    printf("Operand2 : ");
    print_list(head2);
    printf("\n");
    // Remove leading zeros from operands
    check_zero(&head1,&tail1);
    check_zero(&head2,&tail2);

    switch(opr[0])
    {
        case '+':
        {// If both signs same → perform addition
            if(sign1 == sign2)
            {
                addition(&tail1, &tail2, &headR, &tailR);

                // Print sign if negative
                if(sign1 == 1)
                {
                    printf("Result: -");
                }
                else
                {
                    printf("Result: ");
                }
            }
            // Signs different → perform subtraction
            else
            {
                    int cmp = list_comp(&head1,&head2);

                    // if equal
                    if(cmp == -1)
                    {
                        dl_insert_first(&headR,&tailR,0);
                        printf("Result: ");
                    }
                    // If operand1 bigger
                    else if(cmp == 1)   
                    {
                        substraction(&head1,&tail1,&head2,&tail2,&headR,&tailR);

                        if(sign1 == 1)
                            printf("Result: -");
                        else
                            printf("Result: ");
                    }
                    // If operand2 bigger
                    else           
                    {
                        substraction(&head2,&tail2,&head1,&tail1,&headR,&tailR);

                        if(sign2 == 1)
                        {
                            printf("Result: -");
                        }
                        else
                        {
                            printf("Result: ");
                        }
                    }
                }
                   
                // Print addition result
                print_list(headR);
                break;
            }
        case '-':
        { // Flip sign of operand2
            sign2 = (!sign2);

            // If signs same → perform addition
            if(sign1 == sign2)
            {
                addition(&tail1, &tail2, &headR, &tailR);

                if(sign1 == 1)
                    printf("Result: -");
                else
                    printf("Result: ");
            }
            // Signs different → perform subtraction
            else
            {
                int cmp = list_comp(&head1,&head2);

                // If equal → result zero
                if(cmp == -1)
                {
                    dl_insert_first(&headR,&tailR,0);
                    printf("Result: ");
                }
                // operand1 bigger
                else if(cmp == 1)
                {
                    substraction(&head1,&tail1,&head2,&tail2,&headR,&tailR);

                    if(sign1 == 1)
                        printf("Result: -");
                    else
                        printf("Result: ");
                }
                // operand2 bigger
                else
                {
                    substraction(&head2,&tail2,&head1,&tail1,&headR,&tailR);

                    if(sign2 == 1)
                        printf("Result: -");
                    else
                        printf("Result: ");
                }
            }

            // Print subtraction result
            print_list(headR);
            break;
        }
        case '*':
        { // Perform multiplication 
            multiplication(&tail1,&tail2,&headR,&tailR);

            // If result = 0 → no sign
            if(headR->data == 0 && headR->next == NULL)
            {
                printf("Result: ");
            }
            else
            {
                // Sign negative if operands signs differ
                if(sign1 != sign2)
                {
                    printf("Result: -");
                }
                else
                {
                    printf("Result: ");
                }
            }

            // Print multiplication result
            print_list(headR);
            break;
        }
        case '/':
        {
                division(&head1,&tail1,&head2,&tail2,&headR,&tailR);

                //stop if division failed
                 if(headR == NULL)
                 {
                    return 0;   
                }

                // If result = 0 → no sign
                if(headR->data == 0 && headR->next == NULL)
                {
                    printf("Result: ");
                }
                else
                {
                    // Sign negative if operands signs differ
                    if(sign1 != sign2)
                    {
                        printf("Result: -");
                    }
                    else
                    {
                        printf("Result: ");
                    }
                }
                //print division result

                print_list(headR);
                break;
        }
        default :
        {
            printf("Invalid operator\n");
            break;
        }
    }
    printf("\n");
}