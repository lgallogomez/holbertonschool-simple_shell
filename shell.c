#include "main.h"

/**
 * main - simple shell
 *
 * Return: 0 when exiting
 */
/*falta impresion de errores, 
status de salida : leer WEXITSTATUS
poner error cuando le pasemos echo en modo no interactivo. si corre echo "ëcho hola" | ./hsh 

*/
#include "main.h"

int main(void)
{
    ssize_t line_len = 0;
    size_t arg_line_len = 0;
    char *line = NULL, *token, *str[5];
    const char delimiter[] = " \n\t\0";
    int i = 1;
    int j = 0;

    while (1)
    {
        line = NULL;
        i = 1;
        if (isatty(STDIN_FILENO))
            write(1, "($) ", 5);

        /* Read input line*/
        line_len = getline(&line, &arg_line_len, stdin);

        /* Print the read input line for debugging*/
        printf("[DEBUG] Input Line: %s", line);

        if (line_len == EOF || (strcmp(line, "exit\n") == 0))
        {
            free(line);
            exit(0);
        }

        token = strtok(line, delimiter);
        str[0] = token;

        if (strcmp(str[0], "env") == 0)
            printenv(line);
        else if (token != NULL)
        {
            while (token != NULL)
            {
                token = strtok(NULL, delimiter);
                str[i] = token;
                i++;
            }
            str[i] = NULL;

            /*Print tokenized strings for debugging*/
            printf("[DEBUG] Tokenized Strings: ");
            for (j = 0; str[j] != NULL; j++)
            {
                printf("[%s] ", str[j]);
            }
            printf("\n");

            checkdir(str);
            free(line);
        }
        else
            free(line);
    }
    return (0);
}
