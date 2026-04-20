/*
 * Project: CDataFrame
 * Authors: Alban Pascal and Maxime Colin
 * Role: This file contains the menu functions for the CDataFrame Management System.
 * It provides options for filling, displaying, and performing usual operations on the CDataFrame.
 */

#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include "column.h"
#include "main.h"
#include "cdataframe.h"
#include "double-linked-list.h"
#include "utils.h"

void MenuFilling(CDATAFRAME *cdf, list *cdfs, int nb_cdf, COLUMN *col, list *cols, int nb_col) {
    int choice;
    do {
        printf(
                "     #########################################################################\n"
                "     #                              Filling Menu                             #\n"
                "     #  CDataFrame selected : CDataFrame %d                                  #\n"
                "     #                                                                       #\n"
                "     #  1- Create an empty CDataFrame                                        #\n"
                "     #  2- Fill the CDataframe with input (new column)                       #\n"
                "     #  3- Hard fill the CDataframe with an array (new column)               #\n"
                "     #  4- Load from CSV                                                     #\n"
                "     #  5- Save into CSV                                                     #\n"
                "     #  6- Back                                                              #\n"
                "     #########################################################################\n", nb_cdf
        );
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                printf("Enter the size of the CDataFrame :");
                int new_cdf_size;
                scanf("%d", &new_cdf_size);
                CDATAFRAME* new_cdf = create_cdataframe(new_cdf_size);
                lnode* cdf_create = lst_create_lnode(new_cdf);

                if (get_first_node(cdfs) == NULL){
                    lst_insert_head(cdfs, cdf_create);
                }else{
                    lst_insert_tail(cdfs, cdf_create);
                }

                printf("A new empty CDataFrame has been created.\n");
                if (nb_cdf == -1)
                    nb_cdf = 1;
                else
                    nb_cdf++;
                cdf = new_cdf;
                MenuFilling(cdf, cdfs, nb_cdf, col, cols, nb_col);
                break;
            case 2:
                fill_user(cdf);
                printf("\n");
                MenuFilling(cdf, cdfs, nb_cdf, col, cols, nb_col);
                break;
            case 3:
                printf("Enter the array wanted (123456) then the size (6) :");
                char array_str[100];
                int size;
                scanf("%99s", array_str);
                scanf("%d", &size);
                int* array = string_to_int_array(array_str, &size);
                fill_hard(cdf, size, array);
                MenuFilling(cdf, cdfs, nb_cdf, col, cols, nb_col);
                break;
            case 4:
                printf("Enter the path to the csv file :");
                char file_name[200];
                scanf("%199s", file_name);
                printf("Enter the number of column of your csv file :");
                int nbr_col = 0;
                scanf("%d", &nbr_col);
                CDATAFRAME* cdf_csv = load_from_csv(file_name, nbr_col);
                lst_insert_tail(cdfs, lst_create_lnode(cdf_csv));
                if (nb_cdf == -1)
                    nb_cdf = 1;
                else
                    nb_cdf++;
                cdf = cdf_csv;
                MenuFilling(cdf, cdfs, nb_cdf, col, cols, nb_col);
                break;
            case 5:
                printf("Enter name of the csv file :");
                char file_name2[200];
                scanf("%199s", file_name2);
                save_into_csv(cdf, file_name2);
                printf("The csv file has been created, please stop the program to find it in your directory.\n");
                MenuFilling(cdf, cdfs, nb_cdf, col, cols, nb_col);
            case 6:
                printf("Going back...\n");
                MenuSection(cdf, cdfs, nb_cdf, col, cols, nb_col);
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 6.\n");
        }
    } while (choice < 1 || choice > 6);
}

void MenuDisplaying(CDATAFRAME *cdf, list *cdfs, int nb_cdf, COLUMN *col, list *cols, int nb_col) {
    int choice;
    do {
        printf(
                "     #########################################################################\n"
                "     #                           Displaying Menu                             #\n"
                "     #  CDataFrame selected : CDataFrame %d                                  #\n"
                "     #                                                                       #\n"
                "     #  1- Print DataFrame                                                   #\n"
                "     #  2- Print Rows                                                        #\n"
                "     #  3- Print Columns                                                     #\n"
                "     #  4- Print Column Titles                                               #\n"
                "     #  5- Back                                                              #\n"
                "     #########################################################################\n", nb_cdf
        );
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                print_cdf(cdf);
                MenuDisplaying(cdf, cdfs, nb_cdf, col, cols, nb_col);
                break;
            case 2:
                printf("Enter the first row to display :");
                int first, last;
                scanf("%d", &first);
                printf("Enter the last row to display :");
                scanf("%d", &last);
                print_rows_cdf(cdf, first, last);
                MenuDisplaying(cdf, cdfs, nb_cdf, col, cols, nb_col);
                break;
            case 3:
                printf("Enter the first column to display :");
                int first_col, last_col;
                scanf("%d", &first_col);
                printf("Enter the last column to display :");
                scanf("%d", &last_col);
                print_cols_cdf(cdf, first_col, last_col);
                MenuDisplaying(cdf, cdfs, nb_cdf, col, cols, nb_col);
                break;
            case 4:
                print_columns_title(cdf);
                MenuDisplaying(cdf, cdfs, nb_cdf, col, cols, nb_col);
                break;
            case 5:
                printf("Going back...\n");
                MenuSection(cdf, cdfs, nb_cdf, col, cols, nb_col);
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 5.\n");
        }
    } while (choice < 1 || choice > 5);
}

void MenuUsualOperations(CDATAFRAME *cdf, list *cdfs, int nb_cdf, COLUMN *col, list *cols, int nb_col) {
    int choice;
    do {
        printf(
                "     #########################################################################\n"
                "     #                      Usual Operations Menu                            #\n"
                "     #  CDataFrame selected : CDataFrame %d                                  #\n"
                "     #                                                                       #\n"
                "     #  1- Add a row of values to the CDataframe                             #\n"
                "     #  2- Delete a row of values from the CDataframe                        #\n"
                "     #  3- Delete a column from the CDataframe                               #\n"
                "     #  4- Rename the title of a column in the CDataframe                    #\n"
                "     #  5- Access/replace value in a cell of the CDataframe using its pos    #\n"
                "     #  6- Back                                                              #\n"
                "     #########################################################################\n", nb_cdf
        );
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                printf("Enter the array wanted (123456) then the size (6) then the position (3):");
                char array_str[100];
                int size, position;
                scanf("%99s", array_str);
                scanf("%d", &size);
                scanf("%d", &position);
                int* array = string_to_int_array(array_str, &size);
                add_row_cdf(cdf, array, position);
                MenuUsualOperations(cdf, cdfs, nb_cdf, col, cols, nb_col);
                break;
            case 2:
                printf("Enter position of the row:");
                int pos;
                scanf("%d", &pos);
                delete_row_cdf(cdf, pos);
                MenuUsualOperations(cdf, cdfs, nb_cdf, col, cols, nb_col);
                break;
            case 3:
                printf("Enter name of the column:");
                char name[100];
                scanf("%99s", name);
                delete_column_cdf(cdf, name);
                MenuUsualOperations(cdf, cdfs, nb_cdf, col, cols, nb_col);
                break;
            case 4:
                printf("Enter new name of the column:");
                char name2[100];
                int pos2;
                scanf("%99s", name);
                printf("Enter the position of column to rename :");
                scanf("%d", &pos2);
                rename_column_cdf(cdf,pos2,name2);
                MenuUsualOperations(cdf, cdfs, nb_cdf, col, cols, nb_col);
                break;
            case 5:
                printf("Enter the new value then the row and the col :");
                int new_value, row, col1;
                scanf("%d", &new_value);
                scanf("%d", &row);
                scanf("%d", &col1);
                access_and_replace_value_by_pos(cdf, new_value, row, col1);
                MenuUsualOperations(cdf, cdfs, nb_cdf, col, cols, nb_col);
                break;
            case 6:
                printf("Going back...\n");
                MenuSection(cdf, cdfs, nb_cdf, col, cols, nb_col);
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 6.\n");
        }
    } while (choice < 1 || choice > 6);
}

void MenuAnalysisStatistics(CDATAFRAME *cdf, list *cdfs, int nb_cdf, COLUMN *col, list *cols, int nb_col) {
    int choice;
    do {
        printf(
                "     #########################################################################\n"
                "     #                   Analysis and Statistics Menu                         #\n"
                "     #  CDataFrame selected : CDataFrame %d                                   #\n"
                "     #                                                                        #\n"
                "     #  1- Display the number of rows                                         #\n"
                "     #  2- Display the number of columns                                      #\n"
                "     #  3- Display number of cells equal to x (x given as a parameter)        #\n"
                "     #  4- Display number of cells containing a value greater than x          #\n"
                "     #  5- Display number of cells containing a value less than x             #\n"
                "     #  6- Search a value in the CDF and return its position if existing      #\n"
                "     #  7- Back                                                               #\n"
                "     #########################################################################\n", nb_cdf
        );
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                printf("Number of row(s) of CDataFrame %d : %d", nb_cdf, get_rows_number_cdf(cdf));
                MenuAnalysisStatistics(cdf, cdfs, nb_cdf, col, cols, nb_col);
                break;
            case 2:
                printf("Number of column(s) of CDataFrame %d : %d", nb_cdf, get_cols_number_cdf(cdf));
                MenuAnalysisStatistics(cdf, cdfs, nb_cdf, col, cols, nb_col);
                break;
            case 3:
                printf("Enter the value x:");
                int value;
                scanf("%d", &value);
                cells_equal(cdf, value);
                MenuAnalysisStatistics(cdf, cdfs, nb_cdf, col, cols, nb_col);
                break;
            case 4:
                printf("Enter the value x:");
                int value2;
                scanf("%d", &value2);
                cells_greater(cdf, value2);
                MenuAnalysisStatistics(cdf, cdfs, nb_cdf, col, cols, nb_col);
                break;
            case 5:
                printf("Enter the value x:");
                int value3;
                scanf("%d", &value3);
                cells_lesser(cdf, value3);
                MenuAnalysisStatistics(cdf, cdfs, nb_cdf, col, cols, nb_col);
                break;
            case 6:
                printf("Enter the value :");
                int value4;
                scanf("%d", &value4);
                search_value_cdf(cdf, value4);
                MenuAnalysisStatistics(cdf, cdfs, nb_cdf, col, cols, nb_col);
                break;
            case 7:
                printf("Going back...\n");
                MenuSection(cdf, cdfs, nb_cdf, col, cols, nb_col);
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 7.\n");
        }
    } while (choice < 1 || choice > 7);
}

void MenuOperationColumn(CDATAFRAME *cdf, list *cdfs, int nb_cdf, COLUMN *col, list *cols, int nb_col){
    int choice;
    do {
        printf(
                "     #########################################################################\n"
                "     #                   Operations on Columns Menu                           #\n"
                "     #  Column selected : Column %d - %s                                      #\n"
                "     #                                                                        #\n"
                "     #  1- Create a column                                                    #\n"
                "     #  2- Insert a value in a column                                         #\n"
                "     #  3- Insert a value in a column at a given position                     #\n"
                "     #  4- Free the memory allocated to a column                              #\n"
                "     #  5- Display the contents of a column                                   #\n"
                "     #  6- Sort a column                                                      #\n"
                "     #  7- Display the contents of a sorted column                            #\n"
                "     #  8- Delete the index of a column                                       #\n"
                "     #  9- Check if a column has an index                                     #\n"
                "     #  10- Update an index                                                   #\n"
                "     #  11- Back                                                              #\n"
                "     #########################################################################\n", nb_col, col->title
        );
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                printf("Enter the title of the new column :");
                char title[100];
                scanf("%s", title);
                COLUMN* new_col = create_column(title);
                lst_insert_tail(cols, new_col);
                col = new_col;
                if (nb_col == -1)
                    nb_col = 1;
                else
                    nb_col++;
                MenuOperationColumn(cdf, cdfs, nb_cdf, col, cols, nb_col);
                break;
            case 2:
                printf("Enter a value :");
                int value;
                scanf("%d", &value);
                insert_value(col, value);
                MenuOperationColumn(cdf, cdfs, nb_cdf, col, cols, nb_col);
                break;
            case 3:
                printf("Enter a value :");
                int value1, pos;
                scanf("%d", &value1);
                printf("Enter a position :");
                scanf("%d", &pos);
                insert_value_at_position(col, value1, pos);
                MenuOperationColumn(cdf, cdfs, nb_cdf, col, cols, nb_col);
                break;
            case 4:
                delete_column(&col);
                MenuOperationColumn(cdf, cdfs, nb_cdf, col, cols, nb_col);
                break;
            case 5:
                print_col(col);
                MenuOperationColumn(cdf, cdfs, nb_cdf, col, cols, nb_col);
                break;
            case 6:
                printf("Enter 0 for ascendent sort and 1 for an descendent sort :");
                int sort_value;
                scanf("%d", &sort_value);
                sort(col, sort_value);
                MenuOperationColumn(cdf, cdfs, nb_cdf, col, cols, nb_col);
                break;
            case 7:
                print_col_by_index(col);
                MenuOperationColumn(cdf, cdfs, nb_cdf, col, cols, nb_col);
                break;
            case 8:
                erase_index(col);
                MenuOperationColumn(cdf, cdfs, nb_cdf, col, cols, nb_col);
                break;
            case 9:
                printf("Index of the column : %d", check_index(col));
                MenuOperationColumn(cdf, cdfs, nb_cdf, col, cols, nb_col);
                break;
            case 10:
                update_index(col);
                MenuOperationColumn(cdf, cdfs, nb_cdf, col, cols, nb_col);
                break;
            case 11:
                printf("Going back...\n");
                MenuSection(cdf, cdfs, nb_cdf, col, cols, nb_col);
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 11.\n");
        }
    } while (choice < 1 || choice > 11);
}

void MenuSearching(CDATAFRAME *cdf, list *cdfs, int nb_cdf, COLUMN *col, list *cols, int nb_col){
    int choice;
    do {
        printf(
                "     #########################################################################\n"
                "     #                   Searching Menu                                       #\n"
                "     #  Column selected : Column %d - %s                                      #\n"
                "     #                                                                        #\n"
                "     #  1- Return the number of occurrences of a value x in a column          #\n"
                "     #  2- Return the value present at position x in a column                 #\n"
                "     #  3- Return the number of values greater than x in a column             #\n"
                "     #  4- Return the number of values less than x in a column                #\n"
                "     #  5- Return the number of values equal to x in a column                 #\n"
                "     #  6- Perform a binary search in a column                                #\n"
                "     #  7- Back                                                               #\n"
                "     #########################################################################\n", nb_col, col->title
        );
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                printf("Enter the value :");
                int value;
                scanf("%d", &value);
                printf("%d appears %d time(s) in this column.", value, count_occ(col, value));
                MenuSearching(cdf, cdfs, nb_cdf, col, cols, nb_col);
                break;
            case 2:
                printf("Enter the position :");
                int pos;
                scanf("%d", &pos);
                printf("%d appears %d time(s) in this column.", pos, positionval(col, pos));
                MenuSearching(cdf, cdfs, nb_cdf, col, cols, nb_col);
                break;
            case 3:
                printf("Enter the value :");
                int x;
                scanf("%d", &x);
                printf("Number of value greater than %d : %d",x , valuegreater(col, x));
                MenuSearching(cdf, cdfs, nb_cdf, col, cols, nb_col);
                break;
            case 4:
                printf("Enter the value :");
                int x1;
                scanf("%d", &x1);
                printf("Number of value less than %d : %d",x1 , valueless(col, x1));
                MenuSearching(cdf, cdfs, nb_cdf, col, cols, nb_col);
                break;
            case 5:
                printf("Enter the value :");
                int x2;
                scanf("%d", &x2);
                printf("Number of value equal to %d : %d",x2 , valuequal(col, x2));
                MenuSearching(cdf, cdfs, nb_cdf, col, cols, nb_col);
                break;
            case 6:
                printf("Enter the value :");
                int x3;
                scanf("%d", &x3);
                search_value_in_column(col, x3);
                MenuSearching(cdf, cdfs, nb_cdf, col, cols, nb_col);
                break;
            case 7:
                printf("Going back...\n");
                MenuSection(cdf, cdfs, nb_cdf, col, cols, nb_col);
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 7.\n");
        }
    } while (choice < 1 || choice > 7);
}

void MenuSection(CDATAFRAME *cdf, list *cdfs, int nb_cdf, COLUMN *col, list *cols, int nb_col) {
    int choice;
    do {
        printf(
                "     #########################################################################\n"
                "     #                               Sections                                #\n"
                "     #  CDataFrame selected : CDataFrame %d                                  #\n"
                "     #  Column selected : Column %d                                          #\n"
                "     #                                                                       #\n"
                "     #  1- Creation and Filling:                                             #\n"
                "     #  Functions for creating and filling CdataFrame.                       #\n"
                "     #                                                                       #\n"
                "     #  2- Displaying:                                                       #\n"
                "     #  Functions to display data from the CdataFrame.                       #\n"
                "     #                                                                       #\n"
                "     #  3- Usual Operations:                                                 #\n"
                "     #  Operations like adding or deleting rows or columns but also          #\n"
                "     #  looking for values, and accessing cells.                             #\n"
                "     #                                                                       #\n"
                "     #  4- Analysis and statistics:                                          #\n"
                "     #  Functions for analyzing data.                                        #\n"
                "     #                                                                       #\n"
                "     #  5- Operations on column:                                             #\n"
                "     #  Functions for work with columns                                      #\n"
                "     #                                                                       #\n"
                "     #  6- Searching:                                                        #\n"
                "     #  Functions for searching data in our dataframe.                       #\n"
                "     #                                                                       #\n"
                "     #  7- Change CDataframe                                                 #\n"
                "     #                                                                       #\n"
                "     #  8- Change Column                                                     #\n"
                "     #                                                                       #\n"
                "     #  9- Exit                                                              #\n"
                "     #                                                                       #\n"
                "     #########################################################################\n", nb_cdf, nb_col
        );
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                MenuFilling(cdf, cdfs, nb_cdf, col, cols, nb_col);
                break;
            case 2:
                MenuDisplaying(cdf, cdfs, nb_cdf, col, cols, nb_col);
                break;
            case 3:
                MenuUsualOperations(cdf, cdfs, nb_cdf, col, cols, nb_col);
                break;
            case 4:
                MenuAnalysisStatistics(cdf, cdfs, nb_cdf, col, cols, nb_col);
                break;
            case 5:
                MenuOperationColumn(cdf, cdfs, nb_cdf, col, cols, nb_col);
                break;
            case 6:
                MenuSearching(cdf, cdfs, nb_cdf, col, cols, nb_col);
                break;
            case 7:
                if (cdfs->head == NULL){
                    printf("There is no CDataFrame created, please go to the Section 1 - Creation and Filling\n");
                    MenuSection(cdf, cdfs, nb_cdf, col, cols, nb_col);
                } else {
                    lnode* cdf_choice = get_first_node(cdfs);
                    int number_cdf = -1;
                    int i = 1;
                    printf("List of CDataFrame\n");
                    printf("%d - CDataFrame %d\n", 1, 1);
                    while (cdf_choice != cdfs->tail){
                        i++;
                        printf("%d - CDataFrame %d\n", i, i);
                        cdf_choice = get_next_node(cdfs, cdf_choice);
                    }
                    do{
                        printf("Enter the number of the CDataFrame :");
                        scanf("%d", &number_cdf);
                        if (number_cdf < 1 || number_cdf > i){
                            printf("Invalid choice! Please enter a number between 1 and %d.\n", i);
                        }
                    }while (number_cdf < 1 || number_cdf > i);
                    cdf_choice = get_first_node(cdfs);
                    for (int k = 0; k < number_cdf - 1; k++){
                        cdf_choice = get_next_node(cdfs, cdf_choice);
                    }
                    cdf = cdf_choice->data;
                    nb_cdf = number_cdf;
                    MenuSection(cdf, cdfs, nb_cdf, col, cols, nb_col);
                }
                break;
            case 8:
                if (cols->head == NULL){
                    printf("There is no Column created, please go to the Section 5 - Operations on Column\n");
                    MenuSection(cdf, cdfs, nb_cdf, col, cols, nb_col);
                } else {
                    lnode* col_choice = get_first_node(cols);
                    int number_col = -1;
                    int i = 1;
                    printf("List of Columns\n");
                    printf("%d - Column %d\n", 1, 1);
                    while (col_choice != cdfs->tail){
                        i++;
                        printf("%d - Column %d\n", i, i);
                        col_choice = get_next_node(cols, col_choice);
                    }
                    do{
                        printf("Enter the number of the Column :");
                        scanf("%d", &number_col);
                        if (number_col < 1 || number_col > i){
                            printf("Invalid choice! Please enter a number between 1 and %d.\n", i);
                        }
                    }while (number_col < 1 || number_col > i);
                    col_choice = get_first_node(cols);
                    for (int k = 0; k < number_col - 1; k++){
                        col_choice = get_next_node(cols, col_choice);
                    }
                    cdf = col_choice->data;
                    nb_col = number_col;
                    MenuSection(cdf, cdfs, nb_cdf, col, cols, nb_col);
                }
                break;
            case 9:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Please enter a number between 1 and 9.\n");
        }
    } while (choice < 1 || choice > 9);
}
