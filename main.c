// biblioteca que lida com input e output
#include <stdio.h>
#include <locale.h>
#include <string.h>

//printf("\n%d", strlen(name));
//printf("\n%c", name[4]);
//printf("\n%d", strlen(fileText));
//printf("\n%c\n", fileText[5]);


void printUsers(FILE* users){
    char fileText[100];
    while(fgets(fileText, sizeof(fileText), users)){
        printf("%s", fileText);
    }
}

void changeHobbie(int lineCounter, char newHobbie[]){
    FILE *users = fopen("users.txt", "r");

    char fileText[1000];
    char newText[1000];
    int i = 0;
    while(fgets(fileText, sizeof(fileText), users)){
        if(i != lineCounter + 1){
            strcat(newText, fileText);
        }
        else{
            strcat(newHobbie, "\n");
            strcat(newText, newHobbie);
        }
        i++;
    }
    fclose(users);
    users = fopen("users.txt", "w");
    fputs(newText, users);
    fclose(users);
}

int checkUsernameAndPassword(FILE* users, char username[], char password[]){
    char fileText[100];
    int lineCounter = 1;
    strcat(username, "\n");
    strcat(password, "\n");

    while(fgets(fileText, sizeof(fileText), users)){

        if(strcmp(username, fileText) == 0){
            break;
        }

        lineCounter++;
    }

    if(strlen(fileText) < lineCounter){
        printf("Nome não encontrado." );
        return 0;
    }


    char filePassword[100];

    fgets(filePassword, sizeof(fileText), users);

    if(strcmp(filePassword, password) == 0){
        return lineCounter;
    }

    return 0;
}

int menu(){
    int opc;
    do{
        printf("\n---------------\n");
        printf("O que deseja fazer?\n");
        printf("1 - Ver a lista de cadastrados.\n");
        printf("2 - Me cadastrar.\n");
        printf("3 - Ja sou cadastrado, quero modificar meu hobbie.\n");
        printf("4 - Sair.\n");
        printf("\n");

        scanf("%d", &opc);
        printf("\n---------------\n");

    }while(opc < 1 || opc > 4);

    return opc;
}

int verifyName(char username[]){
    strcat(username, "\n");

    if(strlen(username) < 3){
        return 1;
    }

    FILE *users = fopen("users.txt", "r");

    char fileText[100];
    while(fgets(fileText, sizeof(fileText), users)){

        if(strcmp(username, fileText) == 0){
            printf("Nome ja existente nos cadastros.");
            fclose(users);
            return 1;
        }
    }

    fclose(users);
    return 0;
}

int main() {
    setlocale(LC_ALL, "PT-BR");
    printf("Oi, seja bem vindo!\n\n");
    printf("Neste programa voce pode se cadastrar informando seu nome, uma senha e um hobbie.\n");
    printf("Alem disso, pode ver a lista de cadastrados e seus respectivos hobbies.\n");

    int opc = menu();

    if(opc == 1 ){
        printf("Lista de Pessoas Cadastradas:\n");
        FILE *users = fopen("users.txt", "r");
        printUsers(users);
        fclose(users);
    }

    if(opc == 2){
        char name[100] = {0};
        char hobbie[100] = {0};
        char password[100] = {0};

        printf("Bem Vindo ao cadastramento!\n");

        do{
            printf("Qual seu nome?\n");
            scanf("%s", name);
        }while(verifyName(name));

        printf("\nQual seu hobbie?\n");
        scanf("%s", hobbie);

        printf("\nInsira a senha:\n");
        scanf("%s", password);

        printf("\n---------------\n");

        printf("Cadastrando...");

        FILE *users = fopen("users.txt", "a");
//        strcat(name, "\n");
        strcat(password, "\n");
        strcat(hobbie, "\n");

        if(users){
            fputs( "-----------\n", users);
            fputs( name, users);
            fputs( password, users);
            fputs( hobbie, users);


            printf("Sucesso!\n");
            printf("\n---------------\n");
        }
        else{
            printf("erro na abertura do arquivo.");
        }

        fclose(users);
    }

    if(opc == 3){
        char name[100] = {0};
        char hobbie[100] = {0};
        char password[100] = {0};

        int opc2 = 1;
        int check;

        do{
            FILE *users = fopen("users.txt", "r");

            printf("Insira seu nome e senha.\n");
            scanf("%s", name);
            scanf("%s", password);


            check = checkUsernameAndPassword(users, name, password);

            if(check){
                opc2 = 0;
            }else{
                printf("\nUsuario e senha nao coincide.\n");
            }

            fclose(users);

        }while(opc2);

        printf("\nTudo certo! Qual seu novo hobbie?\n");
        scanf("%s", hobbie);
        printf("alterando..");

        changeHobbie(check, hobbie);

        printf("pronto!\n");
    }

    // finalizando o programa

    return 0;
}
