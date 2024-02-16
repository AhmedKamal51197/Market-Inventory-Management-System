#include <stdio.h>
#include <stdlib.h>
#include<windows.h>
#include <string.h>
int productSize=1;
int catSize=1;
int catId=1;
int pId=1;
int listSize=1;
int current_indexList=0;
int current_indexCategory=0;
int current_indexProduct=0;
COORD coord={0,0};                   // this is global variable
                                    //center of axis is set to the top left cornor of the screen
typedef struct Category Category;
typedef struct product product;
 struct Category
{
    int ID;
    char Name[50];

};

struct product
{
    int ID;
    char Name[20];
    int quantity;
    int categoryId;
    int cost;
};

int main()
{
     product * arr_product=malloc(productSize*sizeof(product));
    Category * arr_cat=malloc(catSize*sizeof(Category));
    product * sell_list=malloc(listSize*sizeof(product));
    char che;
    int currentChoice=-1;
    mainMenue(arr_cat,arr_product,sell_list);
    system("cls");
    printf("Thanks for visting our Market we hope to see you again\n");
    return 0;
}


 void gotoxy(int x,int y)
 {
   coord.X=x;
   coord.Y=y;
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
 }


void SetColor(int ForgC)
 {
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}




void ExtendCategory(Category **arr) {
    *arr = realloc(*arr, (catSize * 2) * sizeof(Category));
    catSize *= 2;
}

void AddCategory(Category ** arr)
{
    int duplicated=-1;
    char catName[50];
          system("cls");
          SetColor(39);
          if(current_indexCategory==0)
          {
            printf("Enter name of category\n");
            scanf(" ");
            gets((*arr)[current_indexCategory].Name);
            (*arr)[current_indexCategory].ID=catId;
            catId++;
            current_indexCategory++;
          }
          else
          {
           do{
              duplicated=-1;
              printf("Enter name of category\n");
              scanf(" ");
              gets(catName);
              for(int i=0; i<current_indexCategory; i++)
              {
                  if(strcmp((*arr)[i].Name,catName)==0)
                  {
                      duplicated=1;
                      break;
                  }
              }
              if(duplicated==-1)
              {
                  break;
              }
              else
              {

                  printf("This name Exist You must Enter another name\n");
              }

            }while(duplicated==1);
            (*arr)[current_indexCategory].ID=catId;
            strcpy((*arr)[current_indexCategory].Name,catName);
            catId++;
            current_indexCategory++;
          }
          if(current_indexCategory==catSize)
            {
                ExtendCategory(arr);
            }


}
void ExtendProduct(product** arr)
{
    *arr=realloc(*arr,(productSize*2)*sizeof(product));
    productSize*=2;
}
void AddProduct(product** arr,Category* arr_cat)
{
    int testNum;
        system("cls");
         if(current_indexProduct==productSize)
        {
            ExtendProduct(arr);
        }
        (*arr)[current_indexProduct].ID=pId;
        pId++;
        printf("Enter the name of product : ");
        scanf(" %s",(*arr)[current_indexProduct].Name);
        printf("Enter quantity of prodcut : ");
        while(1)
        {

          if(scanf("%d",&testNum)==1 && testNum>0)
          {
              break;
          }
          printf("You must Enter number and more than zero : ");
          while (getchar() != '\n');
        }
        (*arr)[current_indexProduct].quantity=testNum;
        printf("Enter unit price : \n");
         while(1)
        {

          if(scanf("%d",&testNum)==1 && testNum>0)
          {
              break;
          }
          printf("You must Enter number and more than zero : ");
          while (getchar() != '\n');
        }
        (*arr)[current_indexProduct].cost=testNum;
        (*arr)[current_indexProduct].categoryId=choosecategory(arr_cat);
        current_indexProduct++;


}
int choosecategory(Category* arr_cat)
{
    char ch;
    int choice=0;
    int yAxis;
    int id=0;
do{
        system("cls");
        SetColor(19);
        yAxis=10;
        gotoxy(40,yAxis);
        yAxis++;
        printf("<<<<<Choose Category>>>>>\n");
    for(int i=0; i<current_indexCategory; i++)
    {
        if(i==choice)
        {
            SetColor(13);
        }
        else
        {
            SetColor(39);
        }
         gotoxy(40,yAxis);
         printf("%s",arr_cat[i].Name);
         gotoxy(60,yAxis++);
         printf("%d",arr_cat[i].ID);

    }

    ch=getch();
    if(ch==-32)
    {
        ch=getch();
        if(ch==72)
        {
            choice--;
            if(choice<0)
            {
                choice=current_indexCategory-1;
            }
        }
        else if(ch==80)
        {
            choice++;
            if(choice>current_indexCategory-1)
            {
                choice=0;
            }
        }
    }
    else if(ch==13)
    {
      id=arr_cat[choice].ID;
      break;
    }

}while(ch!=13);
return id;

}

void ShowCategory(Category *arr_cat)
{
    system("cls");
    SetColor(39);
    char ch;
    int show_index=0;
    int yAxis=10;

    do{

          system("cls");
         yAxis=10;
         SetColor(2);
        gotoxy(40,yAxis++);
        printf("*********Category list show*********");
        gotoxy(40,yAxis);
        printf("Category Name");
        gotoxy(65,yAxis++);
        printf("Category ID");
        for (int i = 0; i < current_indexCategory; i++)
        {
            if(i==show_index)
            {
                SetColor(13);
            }
            else
            {
                SetColor(39);
            }
            gotoxy(40,yAxis);
            printf("%s",arr_cat[i].Name);
            gotoxy(65,yAxis++);
            printf("%d",arr_cat[i].ID);
        }
        ch=getch();
        if(ch==-32)
        {
            ch=getch();
            if(ch==72)
            {
                show_index--;
                if(show_index<0)
                {
                    show_index=current_indexCategory-1;
                }
            }
            else if(ch==80)
            {
                show_index++;
                if(show_index>current_indexCategory-1)
                {
                    show_index=0;
                }
            }
        }
    }while(ch!=27 && ch!=13);

    SetColor(39);

}

void ShowProduct(Category * arr_cat, product * arr_prod)
{
    char ch;
    int show_indexprod=0;
    int yAxis;
   do{
        system("cls");
        yAxis=10;
        gotoxy(20,yAxis);
        yAxis+=2;
        printf("========================List OF Category Along with it's Products======================");
        gotoxy(20,yAxis);
        printf("Category ID ");
        gotoxy(35,yAxis);
        printf("Category Name ");
        gotoxy(50,yAxis);
        printf("Product ID");
        gotoxy(65,yAxis);
        printf("Product Name");
        gotoxy(80,yAxis);
        printf("P.quantity");
        gotoxy(95,yAxis);
        yAxis++;
        printf("P.Cost");
        for(int i=0; i<current_indexCategory; i++)
        {
            yAxis++;
            if(i==show_indexprod)
            {
                SetColor(13);
            }
            else
            {
                SetColor(39);
            }
            gotoxy(20,yAxis);
            printf("%d",arr_cat[i].ID);
            gotoxy(35,yAxis);
            printf("%s",arr_cat[i].Name);
        for(int j=0; j<current_indexProduct; j++)
        {

            if(arr_cat[i].ID==arr_prod[j].categoryId)
            {

                        gotoxy(50,yAxis);
                    printf("%d",arr_prod[j].ID);
                    gotoxy(65,yAxis);
                    printf("%s",arr_prod[j].Name);
                    gotoxy(80,yAxis);
                    printf("%d",arr_prod[j].quantity);
                    gotoxy(95,yAxis++);
                    printf("%d",arr_prod[j].cost);


            }

        }

    }
    SetColor(39);
    ch=getch();
        if(ch==-32)
        {
            ch=getch();
            if(ch==72)
            {
                show_indexprod--;
                if(show_indexprod<0)
                {
                    show_indexprod=current_indexCategory-1;
                }
            }
            else if(ch==80)
            {
                show_indexprod++;
                if(show_indexprod>current_indexCategory-1)
                {
                    show_indexprod=0;
                }
            }
        }
   }while(ch!=27 && ch!=13);
     SetColor(39);

}

void mainMenue(Category* arr_cat, product* arr_prod, product* sold_list)
{
    int currentChoice=-1;
    char Menue[3][10]={"Category","Product","Buy"};
    char ch;

   do{

        int yAxis=10;
         system("cls");
         gotoxy(40,yAxis++);
         SetColor(9);
    printf("<<<<<<<<Market Elkheer>>>>>>>>");
       for(int i=0; i<3; i++)
        {
            if(i==currentChoice)
            {
              SetColor(13);
            }
            else
            {
                SetColor(39);
            }
            gotoxy(50,yAxis);
            printf("%s",Menue[i]);
            yAxis++;
        }
    ch=getch();
    if(ch==-32)
    {
            ch=getch();
            if(ch==72)
            {
                currentChoice--;
                if(currentChoice<0)
                {
                    currentChoice=2;
                }
            }
            else if(ch==80)
            {
                currentChoice++;
                if(currentChoice>2)
                {
                    currentChoice=0;
                }
            }
    }
    else if(ch==13)
    {
        switch(currentChoice)
        {
        case 0:
           Categorymenu(&arr_cat);
            break;
        case 1:
            if(current_indexCategory==0)
            {
                system("cls");
                SetColor(20);
                printf("There is no Category ,You must Enter the category first\n");
                getch();
            }
            else
            {
                productmenue(&arr_prod,arr_cat);
            }
            break;
        case 2:
            if(current_indexProduct==0)
            {
                system("cls");
                SetColor(20);
                printf("There hasn't  been  Product to sell Yet!\n");
                getch();
            }
            else
            {
                sellmenue(&sold_list,arr_cat,arr_prod);
            }
            break;
        }

    }

   } while(ch!=27);
     SetColor(39);



}
void Categorymenu(Category **arr_cat)
{
    char MenuCat[2][20]={"Add Category","Show Category"};
    int catChoice=0;
    char cch;
do{
        system("cls");
        int yAxis=10;
        gotoxy(40,yAxis++);
        SetColor(9);
    printf("<<<<<<<<Category Menue>>>>>>>>");
    for(int i=0; i<2; i++)
    {
        if(catChoice==i)
        {
            SetColor(13);
        }
        else
        {
            SetColor(39);
        }
        gotoxy(50,yAxis);
        yAxis++;
        printf("%s",MenuCat[i]);
    }
   cch=getch();
   if(cch==-32)
   {
       cch=getch();
       if(cch==72)
       {
            catChoice--;
            if(catChoice<0)
            {
                catChoice=1;
            }
       }
       else if(cch==80)
       {
           catChoice++;
           if(catChoice>1)
           {
               catChoice=0;
           }
       }

   }
   else if(cch==13)
   {
       switch(catChoice)
       {
       case 0:
        AddCategory(arr_cat);
        break;
       case 1:
            if(current_indexCategory==0)
            {
                system("cls");
                SetColor(20);
                printf("No category has been added yet");
                getch();
            }
            else
            {
                ShowCategory(*arr_cat);

            }
        break;
       }
   }



}while(cch!=27);

SetColor(39);
}
void moveproduct(product **arr_product, Category *arr_cat)
{
    char prod_ch;
    int  pchoice=0,yAxis;
do {
    system("cls");
    yAxis=10;
    gotoxy(25,yAxis);
    yAxis++;
    SetColor(17);
    printf("Choose the Product you want to move it ");
    gotoxy(38,yAxis);
    yAxis++;
    SetColor(39);
    printf("Product Name");
    for(int i=0; i<current_indexProduct; i++)
    {
        if(i==pchoice)
        {
            SetColor(13);
        }
        else
        {
            SetColor(39);
        }
        gotoxy(38,yAxis);
        yAxis++;
        printf("%s",(*arr_product)[i].Name);
    }
    prod_ch=getch();
    if(prod_ch==-32)
    {
        prod_ch=getch();
        if(prod_ch==72)
        {
            pchoice--;
            if(pchoice<0)
            {
                pchoice=current_indexProduct-1;
            }
        }
        else if(prod_ch==80)
        {
            pchoice++;
            if(pchoice>current_indexProduct-1)
            {
                pchoice=0;
            }
        }
    }
    else if(prod_ch==13)
    {
        (*arr_product)[pchoice].categoryId=choosecategory(arr_cat);
    }

 } while(prod_ch!=27);

}

 void productmenue(product **arr_product, Category * arr_cat)
{
    char pmenue[3][50]={"Add Product","Show product","move prouct to another category"};
    int product_choice=0;
    char ch;
    int yAxis;
    do{
      system("cls");
       yAxis=10;
       gotoxy(40,yAxis++);
       SetColor(9);
       printf("<<<<<<<<Product Menue>>>>>>>>");
       for(int i=0; i<3; i++)
       {
           if(i==product_choice)
           {
               SetColor(13);
           }
           else
           {
               SetColor(39);
           }
           if(i==2)
           {
            gotoxy(40,yAxis);
            printf("%s",pmenue[i]);
           }
           else
           {
            gotoxy(50,yAxis);
            printf("%s",pmenue[i]);
           }

           yAxis++;
       }
       ch=getch();
       if(ch==-32)
        {
       ch=getch();
       if(ch==72)
        {
                product_choice--;
                if(product_choice<0)
                {
                    product_choice=1;
                }
        }
      else if(ch==80)
        {
            product_choice++;
            if(product_choice>2)
            {
                product_choice=0;
            }
        }

        }
        else if(ch==13)
        {
          switch(product_choice)
          {
          case 0:
              AddProduct(arr_product,arr_cat);
              break;
          case 1:
              system("cls");
              if(current_indexProduct==0)
              {
                  SetColor(20);
                  printf("There is now Product Existing\n");
                  getch();
              }
              else
              {
                ShowProduct(arr_cat,*arr_product);
              }
            break;
          case 2:
              if(current_indexProduct==0)
              {
                  system("cls");
                  SetColor(20);
                  printf("There is now Product Existing\n");
                  getch();
              }
              else
              {
                 moveproduct(arr_product,arr_cat);
              }
              break;

          }
        }
    }while(ch!=27);
    SetColor(39);

}

void makeOrder(product **sold_list,Category *arr_cat, product *arr_prod)
{
      char prod_ch;
    int  pchoice=0,yAxis,soldQuantity;
do {
    system("cls");
    yAxis=10;
    gotoxy(25,yAxis);
    yAxis++;
    SetColor(17);
    printf("Choose the Product you want to buy it and toggle to choose");
    gotoxy(26,yAxis);

    SetColor(39);
    printf("Product Name");
    gotoxy(40,yAxis);

    printf("Product actual quantity");
    gotoxy(65,yAxis);
    printf("Product Cost for one");
    yAxis++;
    for(int i=0; i<current_indexProduct; i++)
    {
        if(i==pchoice)
        {
            SetColor(13);
        }
        else
        {
            SetColor(39);
        }
        gotoxy(26,yAxis);
        printf("%s",arr_prod[i].Name);
        gotoxy(40,yAxis);
        printf("%d",arr_prod[i].quantity);
        gotoxy(65,yAxis);
        printf("%d",arr_prod[i].cost);
        yAxis++;
    }
    prod_ch=getch();
    if(prod_ch==-32)
    {
        prod_ch=getch();
        if(prod_ch==72)
        {
            pchoice--;
            if(pchoice<0)
            {
                pchoice=current_indexProduct-1;
            }
        }
        else if(prod_ch==80)
        {
            pchoice++;
            if(pchoice>current_indexProduct-1)
            {
                pchoice=0;
            }
        }
    }
    else if(prod_ch==13)
    {
         SetColor(39);
         system("cls");
        if(arr_prod[pchoice].quantity==0)
         {
             printf("I'm sorry but the quantity of this product run out \n");
             printf("Press any key to continue\n");
             getch();
         }
         else
         {

            do{
            printf("Enter quantity of %s : ",arr_prod[pchoice].Name);
             while(1){
                if(scanf("%d",&soldQuantity)==1&&soldQuantity>0)
                {
                    break;
                }
                printf("You must Enter number and more than zero : ");
                while(getchar()!='\n');
             }
            if(soldQuantity>arr_prod[pchoice].quantity)
            {
                printf("We don't have the required quantity we only have %d items of product : %s\n",arr_prod[pchoice].quantity,arr_prod[pchoice].Name);
            }

            }while(soldQuantity>arr_prod[pchoice].quantity );

                arr_prod[pchoice].quantity-=soldQuantity;

                if(listSize==current_indexList)
                {
                (*sold_list)=realloc((*sold_list),listSize*2*sizeof(product));
                listSize*=2;
                }

            (*sold_list)[current_indexList].categoryId=arr_prod[pchoice].categoryId;
            (*sold_list)[current_indexList].ID=arr_prod[pchoice].ID;
            strcpy((*sold_list)[current_indexList].Name,arr_prod[pchoice].Name);
            (*sold_list)[current_indexList].cost=arr_prod[pchoice].cost;
            (*sold_list)[current_indexList].quantity=soldQuantity;
            current_indexList++;
         }




    }


}while(prod_ch!=27);
}
void showBill(product *sold_list, Category* arr_cat)
{
    system("cls");
    SetColor(39);
    char ch;
    int show_index=0;
    int yAxis=10;
    int total_cost=0;
    do{
          total_cost=0;
          system("cls");
         yAxis=10;
         SetColor(2);
        gotoxy(40,yAxis);
        printf("*******************Bill list show******************");
        yAxis++;
        gotoxy(40,yAxis);
        printf("Product Name");
        gotoxy(65,yAxis);
        printf("Product quantity");
        gotoxy(85,yAxis);
        printf("Cost");
        yAxis++;
        for (int i = 0; i < current_indexList; i++)
        {
            if(i==show_index)
            {
                SetColor(13);
            }
            else
            {
                SetColor(39);
            }
            gotoxy(40,yAxis);
            printf("%s",sold_list[i].Name);
            gotoxy(65,yAxis);
            printf("%d",sold_list[i].quantity);
            gotoxy(85,yAxis);
            printf("%d",sold_list[i].quantity*sold_list[i].cost);
            total_cost+=sold_list[i].quantity*sold_list[i].cost;
            yAxis++;
        }
          SetColor(39);
        gotoxy(40,yAxis);
        printf("===================================================\n");
        gotoxy(40,++yAxis);
        printf("Total Cost : ");
        gotoxy(85,yAxis);
        printf("%d",total_cost);
        ch=getch();
        if(ch==-32)
        {
            ch=getch();
            if(ch==72)
            {
                show_index--;
                if(show_index<0)
                {
                    show_index=current_indexList-1;
                }
            }
            else if(ch==80)
            {
                show_index++;
                if(show_index>current_indexList-1)
                {
                    show_index=0;
                }
            }
        }

    }while(ch!=27 && ch!=13);

    SetColor(39);
}
void sellmenue(product **sold_list,Category *arr_cat, product *arr_prod)
{
    char s_menue[2][10]={"Order","Show Bill"};
    int choice =0;
    char ch;
    int yAxis;
  do{
      system("cls");
      yAxis=10;
      gotoxy(40,yAxis);
      yAxis++;
      SetColor(17);
      printf("<<<<<Sell Menue>>>>>");
      for(int i=0; i<2; i++)
      {
          if(i==choice)
          {
              SetColor(13);
          }
          else
          {
              SetColor(39);
          }
          gotoxy(46,yAxis);
          printf("%s",s_menue[i]);
          yAxis++;
      }
    ch=getch();
    if(ch==-32)
    {
        ch=getch();
        if(ch==72)
        {
            choice--;
            if(choice<0)
            {
                choice=1;
            }
        }
        else if(ch==80)
        {
            choice++;
            if(choice>1)
            {
                choice=0;
            }
        }
    }
    else if(ch==13)
    {
        switch(choice)
        {
        case 0:
              makeOrder(sold_list,arr_cat,arr_prod);
              break;
        case 1:
            if(current_indexList==0)
            {
                SetColor(39);
                system("cls");
                printf("No product selected press Any Key to continue\n");
                getch();
            }
            else
            {
                showBill(*sold_list,arr_cat);
            }
            break;
        }
    }

 } while(ch!=27);

}
