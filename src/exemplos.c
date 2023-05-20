#include "thw/bitfields.h"
#include "thw/bstree.h"
#include "thw/file.h"
#include "thw/sstack.h"
#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_BUFFER 128
#define MAX_LINHAS 16

// Defining bstree functions
struct treePair
{
    int key; // treeValueKey
    char str[32];
}; // treeValue
#define mkPair(k, v)                                                           \
    (struct treePair)                                                          \
    {                                                                          \
        k, v                                                                   \
    }

treeValueKey bst_getKeyByValue(treeValue value)
{
    return value->key;
}

int bst_compare(treeValueKey a, treeValueKey b)
{
    return a == b ? 0 : a < b ? -1 : 1;
}

void bst_printValue(treeValue value)
{
    printf("%d,%s", value->key, value->str);
}

int main()
{
    { // Sequential Stack
        puts("\n=== Stack ===");
        Stack myStack = newStack();
        for (int i = 1; i <= 5; ++i)
            stack_push(myStack, i);
        for (int i = 1; i <= 5; ++i)
            printf("%d\n", stack_pop(myStack));
        delStack(myStack);
    }

    { // Binary search tree
        puts("\n=== Binary search tree ===");
        BSTree myTree = newBSTree(&(struct treePair){ 1, "First" });

        bst_insert(&myTree, &mkPair(35, "Second"));
        bst_insert(&myTree, &mkPair(21, "Third"));
        bst_insert(&myTree, &mkPair(5, "Fourth"));
        bst_insert(&myTree, &mkPair(6, "Sixth"));
        bst_insert(&myTree, &mkPair(7, "Seventh"));
        bst_insert(&myTree, &mkPair(8, "Eighth"));

        bst_printTree(myTree);
        printf("Height of the tree: %ld\n", bst_height(myTree));
        treeValue ret;
        if (bst_find(myTree, 35, &ret))
            printf("The value \"%s\" was found!\n", ret->str);
        else
            puts("Key not found in the tree");

        bst_remove(&myTree, 21);
        bst_printTree(myTree);

        delBSTree(&myTree);
        return 0;
    }

    { // bitfields
        uint8_t myBitF = 0;

        printb(myBitF, 0);
        printf("<- No newline character\n");
        myBitF = 0x80; // 0b10000000
        printb(myBitF, Printb.nl);

        // printb assumes the bitfield is sizeof(int) bits long
        printb(myBitF, Printb.fill_zero | Printb.nl);

        unsigned int myIntBitF = myBitF;
        // Setting the first bit (from left to right) to 1
        // Since this is 0 indexed, we need to subtract 1
        SET_BIT(myIntBitF, (sizeof(int) * 8 - 1));
        printb(myIntBitF, Printb.fill_zero | Printb.prefix | Printb.nl);

        TOGGLE_BIT(myIntBitF, (sizeof(int) * 8 - 1));
        TOGGLE_BIT(myIntBitF, 10);
        TOGGLE_BIT(myIntBitF, 0);
        printb(myIntBitF, Printb.prefix | Printb.nl);
    }

    { // del_linhas
        char linha[TAMANHO_BUFFER];
        FILE *arquivo = fopen("dlarquivo.txt", "w");
        fprintf(arquivo,
                "Esta é a primeira linha do arquivo\nO arquivo tem algumas "
                "linhas para que o teste seja demonstrado de maneira "
                "adequada.\nVocê pode estar confuso se estiver lendo isto "
                "dentro do código em C,\nJá que as quebras de linha não são "
                "demonstradas assim.\nEu realmente recomendo que tu leias isto "
                "dentro do arquivo de texto propriamente dito.\nEnfim, esta "
                "aqui é a última linha do arquivo...\nOu será que não?\n");
        del_linhas_ram(2, 4, arquivo, "r", TAMANHO_BUFFER * MAX_LINHAS);
        while (fgets(linha, TAMANHO_BUFFER, arquivo) != NULL)
            printf("%s", linha);
        fclose(arquivo);
    }

    { // del_linhas_disk
        FILE *arquivo = fopen("arquivo grande.txt", "w");
        fprintf(
          arquivo,
          "1- Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do "
          "eiusmod tempor incididunt ut labore et dolore magna "
          "aliqua.\nCommodo nulla facilisi nullam vehicula ipsum a arcu "
          "cursus.\nNon curabitur gravida arcu ac.\nPretium viverra "
          "suspendisse potenti nullam.\nTempus urna et pharetra pharetra massa "
          "massa ultricies mi.\nVel eros donec ac odio.\nUllamcorper a lacus "
          "vestibulum sed arcu non odio euismod lacinia.\nProin sagittis nisl "
          "rhoncus mattis.\nSem integer vitae justo eget magna fermentum "
          "iaculis eu non.\nEleifend mi in nulla posuere.\n2- Quisque id diam "
          "vel quam elementum pulvinar etiam non.\nTellus rutrum tellus "
          "pellentesque eu tincidunt tortor aliquam.\nCommodo odio aenean sed "
          "adipiscing diam donec.\nCras sed felis eget velit aliquet "
          "sagittis.\nCum sociis natoque penatibus et magnis.\nAmet risus "
          "nullam eget felis eget nunc lobortis mattis.\nAccumsan lacus vel "
          "facilisis volutpat est velit egestas.\nUt sem viverra aliquet eget "
          "sit amet tellus cras adipiscing.\nCommodo elit at imperdiet dui "
          "accumsan.\nVel eros donec ac odio tempor orci dapibus ultrices "
          "in.\nVestibulum morbi blandit cursus risus at.\nAliquam faucibus "
          "purus in massa.\n3- \n4- Posuere ac ut consequat semper "
          "viverra.\nTristique nulla aliquet enim tortor at auctor urna nunc "
          "id.\nLectus mauris ultrices eros in cursus turpis massa "
          "tincidunt.\nEnim lobortis scelerisque fermentum dui faucibus "
          "in.\nPellentesque adipiscing commodo elit at imperdiet "
          "dui.\nElementum curabitur vitae nunc sed velit dignissim sodales ut "
          "eu.\nUltricies mi eget mauris pharetra.\nA pellentesque sit amet "
          "porttitor eget.\nFacilisis gravida neque convallis a cras.\nLectus "
          "mauris ultrices eros in cursus turpis massa tincidunt dui.\n5- "
          "Aliquam malesuada bibendum arcu vitae.\nQuis hendrerit dolor magna "
          "eget est.\nNon nisi est sit amet.\nBibendum est ultricies integer "
          "quis.\nIn vitae turpis massa sed elementum tempus egestas sed.\nSed "
          "euismod nisi porta lorem mollis aliquam.\nUrna duis convallis "
          "convallis tellus id interdum.\nSapien nec sagittis aliquam "
          "malesuada bibendum.\nIn nibh mauris cursus mattis molestie.\nEt "
          "egestas quis ipsum suspendisse ultrices gravida.\nConvallis tellus "
          "id interdum velit.\nDuis ut diam quam nulla porttitor massa id "
          "neque aliquam.\nVitae tempus quam pellentesque nec nam "
          "aliquam.\nImperdiet proin fermentum leo vel orci porta "
          "non.\nVolutpat odio facilisis mauris sit.\nBlandit aliquam etiam "
          "erat velit scelerisque in dictum.\nMauris in aliquam sem fringilla "
          "ut morbi.\nEu scelerisque felis imperdiet proin fermentum leo vel "
          "orci porta.\nNon quam lacus suspendisse faucibus interdum posuere "
          "lorem ipsum dolor.\nNetus et malesuada fames ac turpis egestas.\n6- "
          "Non quam lacus suspendisse faucibus.\nIpsum nunc aliquet bibendum "
          "enim facilisis gravida.\nAc auctor augue mauris augue neque gravida "
          "in.\nNeque egestas congue quisque egestas.\nLacus sed viverra "
          "tellus in hac habitasse.\nSemper viverra nam libero justo laoreet "
          "sit amet cursus sit.\nScelerisque mauris pellentesque pulvinar "
          "pellentesque.\nFringilla phasellus faucibus scelerisque "
          "eleifend.\nQuam id leo in vitae turpis massa sed elementum.\nOrnare "
          "aenean euismod elementum nisi quis eleifend quam.\nTortor vitae "
          "purus faucibus ornare suspendisse sed nisi.\nFaucibus scelerisque "
          "eleifend donec pretium vulputate sapien.\nSemper quis lectus nulla "
          "at volutpat diam.\n");
        del_linhas(20, 45, arquivo, "r");
        fclose(arquivo);
    }

    return 0;
}
