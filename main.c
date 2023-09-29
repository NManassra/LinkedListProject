#include <stdio.h>
#include <stdlib.h>
/// Name : Noura Awni Manassra
/// ID   : 1212359
/// Instructor : Anas Arram
/// Section : 5
typedef struct node
{
    int data;
    struct node *next;
    struct node *prev; //since it's double linked list
} Node;
struct node* createNode(int data);
Node *createList(FILE *ptr);
int isLast (struct node* P,struct node* L );
struct node* findPrevious (int x, struct node* L );
void printList(struct node* L);
struct node* makeEmpty (struct node* L);
int getCount(struct node* head);
struct node* extraZeros(struct node* head, int length);
void reverse(struct node* L);
struct node *copyList(Node *head);
int isLastNode(Node *node);
void insertAtEnd(int value, struct node* head);
Node* getLastNode(Node* head);
struct node* sum(struct node* ll1, struct node* ll2);
int compareLists(struct node* list1, struct node* list2);
void Delete(struct node**  headRef);
void getAbsolute(struct node* head);
struct node* sumFinish(struct node* list1,struct node* list2 );
struct node*  mult(struct node* ll1,struct node* ll2);
int ZeroLinkedList(struct node* l1);
void resizeLinkedList(struct node** head, int desiredSize) ;
struct node* division(struct node* ll1, struct node* ll2);
struct node* MainLinked (int x,struct node* ll1,struct node* ll2,struct node* ll3,struct node* ll4,struct node* ll5 );
void printLinkedListToFile(struct node* head, const char* file_name);

struct node* createNode(int data) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}
Node *createList(FILE *ptr)   // since all the linked lists we need we gonna take them from the file{
{
    char numbers[1000];// here we gonna store the numbers as a string and then, convet them into numbers
    fgets(numbers, sizeof(numbers), ptr);//real the strings from the file
    Node *head = NULL;
    Node *tail = NULL;
    int sign = 1; // initialize to positive
    for (int i = 0; numbers[i] != '\0'; i++)  //signifies the end of the string
    {
        if (numbers[i] == '\n')  //checks if the current character is a newline character
        {
            continue;
        }
        if (numbers[i] == '-')   // check for negative sign
        {
            sign = -1;
            continue;
        }
        int num = numbers[i] - '0'; // convert char to signed int
        num =num * sign; // multiply by sign to get the correct value
        Node *newNode = malloc(sizeof(Node));//reserve size for the new node
        newNode->data = num;//add the number inside a node
        newNode->next = NULL;
        newNode->prev = tail;//to connect the linked list together
        if (head == NULL)  //in case it's the first number
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
        sign = 1; // reset sign to positive
    }
    return head;
}
int isLast (struct node* P,struct node* L )
{
// P is the position of the needed node,L is the head of the linked list
//is't important to make sure which linked list we are pointing to hence we sent the head as a parameter
    return P->next==NULL; //SINCE THE LAST NODE IS POINTING TO NULL
}
struct node* findPrevious (int x, struct node* L )
{
    struct node* P; //this pointer which will be pointing to the result
    P = L->next;
    if (P->next!=NULL && P->next->data!=x) P=P->next; //this which checking if it's the needed or not
    return P;
};
void printList(struct node* L)
{
    Node *temp= L;//i created this so i can reach each node at the linked list
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}
struct node* makeEmpty (struct node* L)
{
    L = (struct node*) malloc (sizeof(struct node)); //I reserved place at the memory for the full node which have pointer and data in, so i used malloc
    //to make sure that malloc won't point to void data, we use casting as struct data type
    if (L==NULL) printf("OutOfMemo!!\n");//to make sure we won't have null pointer exception
    L->prev = NULL;
    L->next = NULL;//we created the head, which is at the beggining don't point to ant thing just NULL
    return L;//return the head
}
int getCount(struct node* head)
{
    int count = 0; // Initialize count
    struct node* current = head; // Initialize current
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
}
struct node* extraZeros(struct node* head, int length)
{
    while (length > 0)
    {
        struct node* node = makeEmpty(NULL);
        node->data = 0;
        node->next = head;
        head = node;
        length--;
    }
    return head;
}
void reverse(struct node* L)
{
    struct node* curr = L->next;
    struct node* prev = NULL;
    struct node* nextt = NULL;

    while (curr != NULL)
    {
        nextt = curr->next;
        curr->next = prev;
        curr->prev = nextt; // Update the prev pointer for the reversed list
        prev = curr;
        curr = nextt;
    }
    L->next = prev;
    if (prev != NULL)
    {
        prev->prev = L;
    }
}
struct node *copyList(Node *head)  // i used recursion technique so it will creat a linked list using the linked list i have
{
    if (head == NULL)
    {
        return NULL;
    }
    Node *newHead = malloc(sizeof(Node));
    newHead->data = head->data;
    newHead->next = copyList(head->next);
    if (newHead->next != NULL)
    {
        newHead->next->prev = newHead;
    }
    return newHead;
}
int isLastNode(Node *node)
{
    return node->next == NULL;
}
void insertAtEnd(int value, struct node* head)
{
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = value;
    newNode->next = NULL;

    // handle empty list
    if (head == NULL)
    {
        newNode->prev = NULL;
    }

    // traverse the list to find the last node
    Node* lastNode = head;
    while (lastNode->next != NULL)
    {
        lastNode = lastNode->next;
    }

    // insert the new node at the end of the list
    lastNode->next = newNode;
    newNode->prev = lastNode;
}
Node* getLastNode(Node* head)
{
    // handle empty list
    if (head == NULL)
    {
        return NULL;
    }

    // traverse the list to find the last node
    Node* current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    return current;
}
void Delete(struct node**  headRef)
{
    // handle empty list
    if (*headRef == NULL)
    {
        return;
    }

    // handle list with only one node
    if ((*headRef)->next == NULL)
    {
        free(*headRef);
        *headRef = NULL;
        return;
    }

    // delete the head node and update the new head
    Node* temp = *headRef;
    *headRef = (*headRef)->next;
    (*headRef)->prev = NULL;
    free(temp);
}
struct node* sum(struct node* ll1, struct node* ll2)
{
    // note that all operation i am creting are on a copy of the original ones.
    struct node* l1 = copyList(ll1);
    struct node* l2 = copyList(ll2);
    // get the length of both lists
    int length1 = getCount(l1);
    int length2 = getCount(l2);
    // i need to check the sign for each linked list

    if (length1 > length2)  //the idea here to get the number with less digits, to put zeros so i can make the operation truly
    {
        l2 = extraZeros(l2, length1 - length2);
    }
    else if (length2 > length1)
    {
        l1 = extraZeros(l1, length2 - length1);
    }
    int b = l2->data;
    reverse(l2);
    Delete(&l2);
    insertAtEnd(b,l2);
    int a = l1->data;
    reverse(l1);
    Delete(&l1);
    insertAtEnd(a,l1);
    struct node* ptr = makeEmpty(NULL);//the node gonna be pointing to the resutlt linked list
    struct node* temp = ptr;
    int carry = 0;// it's important since it's gonna be added to the nodes if it exists
    while ((l1 != NULL || l2 != NULL || carry != 0))
    {
        int sum = carry;
        if (l1 != NULL)
        {
            sum += l1->data;
            l1 = l1->next;
        }
        if (l2 != NULL)
        {
            sum += l2->data;
            l2 = l2->next;
        }
        carry = sum / 10;
        sum = sum % 10;
        struct node* node = makeEmpty(NULL);
        node->data = sum;
        node->next = NULL;
        temp->next = node;
        temp = temp->next;
    }
    return ptr->next;
}
int compareLists(struct node* list1, struct node* list2)
{
    int length1 = getCount(list1);
    int length2 = getCount(list2);
    if (length1>length2) return 1;
    if (length2>length1) return -1;
    while (list1 != NULL && list2 != NULL)
    {
        if (list1->data > list2->data)
        {
            return 1; // list1 is greater
        }
        else if (list1->data < list2->data)
        {
            return -1; // list2 is greater
        }

        list1 = list1->next;
        list2 = list2->next;
    }

    // Both lists are equal
    return 0;
}
void getAbsolute(struct node* head)
{
    struct node* current = head;

    while (current != NULL)
    {
        // Change the sign of the data to positive
        current->data = abs(current->data);
        current = current->next;
    }
}
struct node* sub(struct node* ll1, struct node* ll2)
{
    int bigger = compareLists(ll1,ll2);
    if (bigger == 0 ) return 0;
    struct node* l1=makeEmpty(NULL);
    struct node* l2=makeEmpty(NULL);
    // Get the length of both lists
    int length1 = getCount(ll1);
    int length2 = getCount(ll2);
    if (length1 > length2)
    {
        // Add extra zeros to l2 to make it the same length as l1
        ll2 = extraZeros(ll2, length1 - length2);
    }
    else if (length2 > length1)
    {
        // Add extra zeros to l1 to make it the same length as l2
        ll1 = extraZeros(ll1, length2 - length1);
    }
    // i need to check the sign for each linked list

    if (bigger==-1)
    {
        l1 = copyList(ll2);
        l2 = copyList(ll1);
    }
    else
    {
        l1 = copyList(ll1);
        l2 = copyList(ll2);
    }
    while(ll1->data==0)
    {
        Delete(&ll1);
    }
    while(ll2->data==0)
    {
        Delete(&ll2);
    }
    // Check the sign for each linked list
    int l1flag = 0, l2flag = 0;
    if (ll1->data < 0) l1flag = 1;
    if (ll2->data < 0) l2flag = 1;

    if (l1flag == 0 && l2flag == 0) // if both positives
    {

        reverse(l1);
        int v1 = l1->data;
        Delete(&l1);
        insertAtEnd(v1,l1);
        reverse(l2);
        int v2 = l2->data;
        Delete(&l2);
        insertAtEnd(v2,l2);
        struct node* ptr = NULL;  // Pointer to the result linked list
        struct node* temp = NULL; // Current node in the result linked list
        int carry = 0;            // Carry value for subtraction
        while (l1 != NULL)
        {
            struct node* node = (struct node*)malloc(sizeof(struct node));

            // Perform subtraction
            int sub = l1->data - l2->data - carry;
            if (sub < 0)
            {
                sub =sub + 10;
                carry = 1;
            }
            else
            {
                carry = 0;
            }

            node->data = sub;
            node->next = NULL;

            if (ptr == NULL)
            {
                ptr = node;
                temp = ptr;
            }
            else
            {
                temp->next = node;
                temp = temp->next;
            }

            l1 = l1->next;
            l2 = l2->next;
        }
        // Reverse the result linked list back to the original order
        reverse(ptr);
        int vptr = ptr->data;
        Delete(&ptr);
        insertAtEnd(vptr,ptr);
        while(ptr->data==0)
        {
            Delete(&ptr);
        }
        if (bigger==1)
        {
            return ptr;
        }
        if (bigger==-1)
        {
            ptr->data=-1*ptr->data;
            return ptr;
        }

        return ptr;
    }
    else if ((l1flag == 0 && l2flag == 1)) // if one is positive and second negative, it turns to summation
    {
        getAbsolute(l1);
        getAbsolute(l2);
        l2->data = -l2->data; // Make the second number positive
        struct node* ptr = sumFinish(l1, l2); // Use the sum function to add both positive numbers
        while(ptr->data==0)
        {
            Delete(&ptr);
        }
        if (bigger==1)
        {
            return ptr;
        }
        if (bigger==-1)
        {
            ptr->data=-1*ptr->data;
            return ptr;
        }
        return ptr;
    }
    else if ((l1flag == 1 && l2flag == 0))
    {
        getAbsolute(l1);
        getAbsolute(l2);
        l2->data = -l2->data; // Make the second number positive
        struct node* ptr = sumFinish(l1, l2); // Use the sum function to add both positive numbers
        while(ptr->data==0)
        {
            Delete(&ptr);
        }
        if (bigger==1)
        {
            return ptr;
        }
        if (bigger==-1)
        {
            ptr->data=-1*ptr->data;
            return ptr;
        }
        return ptr;
    }
    else if (l1flag == 1 && l2flag == 1) // -l1+l2 == l2 - l1
    {
        getAbsolute(l1);
        getAbsolute(l2);
        struct node* ptre = sub(l2, l1);

        while(ptre->data==0)
        {
            Delete(&ptre);
        }
        if (bigger == 1 ) return ptre;
        if (bigger ==  -1)
        {
            ptre->data = -ptre -> data;
            return ptre;
        }
        return ptre;
    }
    return NULL;
}
struct node* sumFinish(struct node* list1,struct node* list2 )
{
     struct node* l1= copyList(list1);
    struct node* l2=copyList(list2);
    int l1flag=0,l2flag=0;
    if (list1->data <0) l1flag=1;
    if (list2->data <0) l2flag=1;
    struct node *sumList = makeEmpty(NULL);
    if(l1flag==0 && l2flag==0)
    {
        sumList = sum(l1, l2);
        reverse(sumList);
        int v = sumList->data;
        Delete(&sumList);
        insertAtEnd(v,sumList);
        sumList->data = (sumList->data);
        return sumList;
    }
    if (l1flag==1 && l2flag==1)
    {
        getAbsolute(l1);
        getAbsolute(l2);
        sumList = sum(l1, l2);
        reverse(sumList);
        int v = sumList->data;
        Delete(&sumList);
        insertAtEnd(v,sumList);
        sumList->data = -1*(sumList->data);
        return sumList;
    }
    if((l1flag==1 && l2flag==0)) //-l1 + l2 == l2 - l1
    {
        getAbsolute(l1);
        getAbsolute(l2);
        sumList=sub(l2,l1);
        return sumList;
    }
    if((l1flag==0 && l2flag==1)) //l1 + -l2 == l1 - l2
    {
        getAbsolute(l1);
        getAbsolute(l2);
        sumList=sub(l1,l2);
        return sumList;
    }
    return sumList;
};
int ZeroLinkedList(struct node* l1)
{
    struct node* head = l1;
    int flag = 1; // Assume all values are zero initially

    while (head != NULL)
    {
        if (head->data != 0)
        {
            flag = 0; // Found a non-zero value, update the flag and break the loop
            break;
        }
        head = head->next; // Move to the next node
    }
    return flag;
}
void resizeLinkedList(struct node** head, int desiredSize)
{
    int currentSize = getCount(*head);

    if (desiredSize < currentSize)
    {
        // Remove nodes from the end of the linked list
        int nodesToRemove = currentSize - desiredSize;

        struct node* current = *head;
        struct node* previous = NULL;

        // Traverse to the node that should be the new tail
        while (current != NULL && current->next != NULL)
        {
            previous = current;
            current = current->next;
        }

        // Remove nodes from the end
        while (nodesToRemove > 0 && current != NULL)
        {
            struct node* nodeToRemove = current;
            if (previous != NULL)
            {
                previous->next = NULL;  // Update the new tail's next pointer
            }
            else
            {
                *head = NULL;  // The list becomes empty
            }
            current = previous;  // Move the previous pointer one step back
            previous = current->prev;  // Get the previous node
            free(nodeToRemove);
            nodesToRemove--;
        }
    }
}
void deleteLinkedList(Node** head)
{
    Node* current = *head;
    Node* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}
struct node*  mult(struct node* ll1, struct node* ll2)
{
    struct node* l1 = makeEmpty(NULL);
    struct node* l2 = makeEmpty(NULL);
    l1 = copyList(ll1);

    l2 = copyList(ll2);

    int length1 = getCount(ll1);
    int length2 = getCount(ll2);
    if (l1->data ==0 && length1==1) return l1;
    if (l2->data ==0 && length2==1) return l2;
    if (l1->data==1 && length1==1) return l2;
    if (l2->data ==1 && length2==1) return l1;
    getAbsolute(l1);
    getAbsolute(l2) ;
    if (length1 > length2)
    {
        // Add extra zeros to l2 to make it the same length as l1
        l2 = extraZeros(l2, length1 - length2);
    }
    else if (length2 > length1)
    {
        // Add extra zeros to l1 to make it the same length as l2
        l1 = extraZeros(l1, length2 - length1);
    }
    struct node* result = makeEmpty(NULL);
    result->data=0;
    if (length1 == 1 && length2==1)
    {
        int multuu = ll1->data*ll2->data;
        result->data = multuu;
        return result;
    }
    // I need to check the sign for each linked list
    int l1flag = 0, l2flag = 0;
    if (ll1->data < 0) l1flag = 1;
    if (ll2->data < 0) l2flag = 1;
    reverse(l1);
    int v1 = l1->data;
    Delete(&l1);
    insertAtEnd(v1, l1);
    reverse(l2);
    int v2 = l2->data;
    Delete(&l2);
    insertAtEnd(v2, l2);
    struct node* temp = makeEmpty(NULL);
     if (length1 > length2)
    {
        temp = copyList(l2);
        l2=copyList(l1);
        l1 = copyList(temp);
        int zz = length1;
        length1 = length2;
        length2 = zz;
    }
    struct node* resultpro = makeEmpty(NULL);
    resultpro->data = 0;
    resultpro=extraZeros(resultpro,length1+length2-1);
    struct node* ll2ptr = l2;
    struct node* resptr2 = result;
    struct node* ll1ptr = l1;
   // int doublee = 1;
    // Multiply each Node of the second list with the first
    int x = length1+1;
    int dbl=0;
    for(int i=0; i<length2; i++)
    {
        int carry = 0;
        // Each time we start from the next Node from which we started last time
        ll1ptr = l1;
          for (int k=0; k<dbl-1; k++)
        {
            insertAtEnd(0,result);
        }
        for(int j=0; j<length1; j++)
        {

            int yy = length1;
            int mul = ll1ptr->data * ll2ptr->data + carry;
            // Now the resultant Node itself can have more than 1 digit
            carry = mul / 10;
            if (i==0 && j==0) result->data = mul % 10;
            else
                insertAtEnd(mul % 10, result);
            ll1ptr = ll1ptr->next;
            carry=carry%10;
        }
        if (carry>0)
        {
            insertAtEnd(carry,result);
        }
        ++dbl;
        ++x;
        resizeLinkedList(&result,x);
        if(ZeroLinkedList(result)==1)
        {
            ll2ptr = ll2ptr->next;
        }
        else
        {
            reverse(result);
            int vres = result->data;
            Delete(&result);
            insertAtEnd(vres, result);
            int z = getCount(result);
            result=extraZeros(result,length1+length2-z);
            resultpro = sum(resultpro, result);
            reverse(resultpro);
            int vrespro = resultpro->data;
            Delete(&resultpro);
            insertAtEnd(vrespro, resultpro);
            if (i==length2-1)
            {
                while (resultpro->data == 0)
                {
                   // Delete(&resultpro);
                    resultpro=resultpro->next;

                }
                if ((l1flag == 0 && l2flag ==0) || (l2flag==1 && l1flag==1))
                    return resultpro ;
                if (l1flag == 1 || l2flag == 1)
                    resultpro->data=-resultpro->data;

                return resultpro;
            }
           // resultpro->data = 0;
            ll2ptr = ll2ptr->next;
        }
        if (i<length2-1)
        {
            result = makeEmpty(result);
        }
    }
//    while (resultpro->data == 0)
//    {
//        Delete(&resultpro);
//        resultpro=resultpro->next;
//    }
    if ((l1flag == 0 && l2flag ==0) || (l2flag==1 && l1flag==1))
        return resultpro ;
    if (l1flag == 1 || l2flag == 1)
        resultpro->data=-resultpro->data;
    return resultpro;

}
struct node* RemoveFirstDigit(struct node* head)
{
    struct node* l = head;
    if (head->next != NULL) {
       l=l->next;
       Delete(&head);
    }
    return l;
}
struct node* division(struct node* ll1, struct node* ll2)
{
    if (ll2 == NULL || ll2->data == 0 || ll1 == NULL)
    {
        printf("Impossible!! You can't divide by nothing or by zero!!\n");
        return NULL;
    }
    struct node* l1 = copyList(ll1);
    struct node* l2 = copyList(ll2);
    getAbsolute(l1);
    getAbsolute(l2);
    struct node* result = makeEmpty(NULL);
    struct node* temp = makeEmpty(NULL);
    struct node* nextDigit = makeEmpty(NULL);
    struct node* l1temp = copyList(l1);
    result->data = 0;
    nextDigit->data = 0;
    temp->data = l1temp->data;
    int l1flag = 0, l2flag = 0;
    if (ll1->data < 0) l1flag = 1;
    if (ll2->data < 0) l2flag = 1;

    if (compareLists(l1, l2) == 0)
    {
        insertAtEnd(1,result);
        return result;
    }
    if (compareLists(l1, l2) == -1)
    {
        printf("The second linked list is greater than the first one, so the answer is 0\n");
        return NULL;
    }

    struct node* l2copy = copyList(l2);

    int counter = 0;
    while (1)
    {

        struct node* temp22 = makeEmpty(NULL);
        struct node* temp33 = makeEmpty(NULL);
        struct node* counterr = makeEmpty(NULL);
        temp22->data = 0;
        temp33->data = 0;
        counterr->data = 0;
        int gg=0;
        while (compareLists(temp, l2) <= 0 && l1temp->next != NULL)
        {
            ++gg;
            l1temp = l1temp->next;
            insertAtEnd(l1temp->data, temp);
            if (gg>1)insertAtEnd(0,result);
        }
        struct node* lasttemp = copyList(temp);
        counter = 0;
        while (compareLists(temp, l2) == 1)
        {
            temp = sub(temp, l2);
            counter++;
            while (temp->data == 0) temp = temp->next;
        }
        insertAtEnd(counter, result);
        insertAtEnd(counter, counterr);
        temp22 = mult(counterr, l2);
        temp33 = sub(lasttemp , temp22);
        nextDigit = copyList(temp33);
        temp = copyList(nextDigit);
        if (isLast(l1temp,l1temp)) break;
    }

    while (result->data == 0) result = result->next;
    if ((l1flag == 0 && l2flag == 0) || (l2flag == 1 && l1flag == 1))
        return result;
    if (l1flag == 1 || l2flag == 1)
    {
         result->data = -1* result->data ;
         return result;
    }

    return result;
}

struct node* MainLinked (int x,struct node* ll1,struct node* ll2,struct node* ll3,struct node* ll4,struct node* ll5 )
{
if (x==1) return ll1;
if (x==2) return ll2;
if (x==3) return ll3;
if (x==4) return ll4;
if (x==5) return ll5;
};
void printLinkedListToFile(struct node* head, const char* file_name)
{
    FILE* file = fopen(file_name, "w");
    if (file == NULL) {
        printf("Failed to create/open the file.\n");
        return;
    }

    struct node* current = head;
    while (current != NULL) {
        fprintf(file, "%d ", current->data);
        current = current->next;
    }

    fclose(file);
}
int main()
{
    FILE *ptr = fopen("input.txt", "r"); // ptr gonna point to the file
    int z = 0, x = 0, y = 0;
    int b = 0;

    Node *sumList = makeEmpty(NULL);
    Node *multi = makeEmpty(NULL);
    Node *divi = makeEmpty(NULL);
    Node *subList = makeEmpty(NULL);
    Node *l1 = NULL;
    Node *l2 = NULL;
    Node *l3 = NULL;
    Node *l4 = NULL;
    Node *l5 = NULL;

    while (1)
    {
        int flag = 0; // to choose which linked list to print
        printf("Selam, choose what you need to do? \n1.Read from File\n2.Make Operations on two Numbers \n3.Print on File \n4.Exit\n");
        scanf("%d", &b);

        if (b == 1)
        {
            if (ptr == NULL)
            {
                printf("File is empty.\n");
                exit(0);
            }

            l1 = createList(ptr);
            l2 = createList(ptr);
            l3 = createList(ptr);
            l4 = createList(ptr);
            l5 = createList(ptr);

            fclose(ptr);
        }
        else if (b == 2)
        {
            printf("Choose which numbers you want to deal with:\n");
            printf("l1: ");
            printList(l1);

            printf("l2: ");
            printList(l2);

            printf("l3: ");
            printList(l3);

            printf("l4: ");
            printList(l4);

            printf("l5: ");
            printList(l5);

            scanf("%d%d", &x, &y);

            struct node *temp1 = MainLinked(x, l1, l2, l3, l4, l5);
            struct node *temp2 = MainLinked(y, l1, l2, l3, l4, l5);


            printf("Choose the operation you want to perform:\n");
            printf("1. Addition  + \n");
            printf("2. Multiplication  * \n");
            printf("3. Subtraction  - \n");
            printf("4. Division  /  \n");
            scanf("%d", &z);
            switch (z)
            {
            case 1:
                sumList = sumFinish(temp1, temp2);
                printf("Sum : ");
                printList(sumList);
                flag = 1;
                break;
            case 2:
                multi = mult(temp1, temp2);
                printf("Mult: ");
                printList(multi);
                flag = 2;
                break;
            case 3:
                subList = sub(temp1, temp2);
                printf("Sub: ");
                if (subList== NULL) printf ("0\n");
                else printList(subList);
                flag = 4;
                break;
            case 4:
                divi = division(temp1, temp2);
                printf("Div: ");
                if (divi== NULL) printf ("0\n");
                else printList(divi);
                flag = 3;
                break;
            }
        }
        else if (b == 3)
        {
            if (z== 1)
                printLinkedListToFile(sumList,"output.txt");
            else if (z == 2)
                printLinkedListToFile(multi,"output.txt");
            else if (z == 3)
                printLinkedListToFile(subList,"output.txt");
            else if (z == 4)
                printLinkedListToFile(divi,"output.txt");
                printf("done\n");
           //     continue;
        }
        else if (b == 4)
        {
            exit(0);
        }
        else
        {
            printf("You entered a wrong number.\n");
        }
    }
}
