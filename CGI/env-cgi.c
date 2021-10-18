#include <stdio.h>
#include <stdlib.h>

#define MAXLEN 80
#define EXTRA 5
/* 4 for field name "data", 1 for "=" */
#define MAXINPUT MAXLEN + EXTRA + 2

void unencode(char *src, char *last, char *dest)
{
    for (; src != last; src++, dest++)
        if (*src == '+')
            *dest = ' ';
        else if (*src == '%')
        {
            int code;
            if (sscanf(src + 1, "%2x", &code) != 1)
                code = '?';
            *dest = code;
            src += 2;
        }
        else
            *dest = *src;
    *dest = '\n';
    *++dest = '\0';
}

int main(void)
{
    char *lenstr;
    char input[MAXINPUT], data[MAXINPUT];
    long len;
    printf("%s%c%c\n", "Content-Type:text/html;charset=iso-8859-1", 13, 10);
    printf("<TITLE>Response</TITLE>\n");
    lenstr = getenv("CONTENT_LENGTH");
    sscanf(lenstr, "%ld", &len) != 1;
    fgets(input, len + 1, stdin);
    unencode(input + EXTRA, input + len, data);
    printf("%s", data);
    return 0;
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <errno.h>
// #include <time.h>

// void url_enc_key_value(char *input, char *key, char *value);
// void add_to_json(char *key, char *value);

// int main()
// {
//     add_to_json("name", "blablabla");
// }

// int main()
// {
//     char *env_value, *content_type, fname[128],
//         *in_line, *out_line, command[128];
//     time_t current_time;
//     int content_length;
//     FILE *tempfile;

//     printf("Content-type: text/html\n\n");
//     printf("<html>\n");
//     printf("<head>\n");
//     /*
//   Handle error conditions or send success message to user
// */
//     content_length = atoi(getenv("CONTENT_LENGTH"));
//     env_value = getenv("CONTENT_TYPE");
//     content_type = malloc(strlen(env_value) + 1);
//     if (content_type == NULL)
//     {
//         printf("<title>Error Occurred</title>\n");
//         printf("</head> <body>\n");
//         printf("<p>Major failure #1; please notify the webmaster\n");
//         printf("</p> </body> </html>\n");
//         fflush(stdout);
//         exit(2);
//     }
//     strcpy(content_type, env_value);
//     if (content_length <= 0)
//     {
//         printf("<title>Error Occurred</title>\n");
//         printf("</head> <body>\n");
//         printf("<p>The form is empty; please enter some data!\n");
//         printf("<br>\n");
//         printf("Press the BACK key to return to the form.\n");
//         printf("</p> </body> </html>\n");
//         fflush(stdout);
//         exit(0);
//     }
//     else if (strcmp(content_type, "application/x-www-form-urlencoded") != 0)
//     {
//         printf("<title>Content Error Occurred</title>\n");
//         printf("</head> <body>\n");
//         printf("<p>Internal error - invalid content type.  Please report\n");
//         printf("<br>\n");
//         printf("Press the BACK key to return to the form.\n");
//         printf("</p> </body> </html>\n");
//         fflush(stdout);
//         exit(0);
//     }
//     /*
//  Create temporary file for mailing
// */
//     strcpy(fname, "/var/www/html/CGIRPI/CGI/output.txt");
//     tempfile = fopen(fname, "w"); /* create temporary file */
//     if (tempfile == NULL)         /* error - didn't create file */
//     {
//         printf("Internal failure #1 please report %d\n", errno);
//         printf("</p> </body> </html>\n");
//         fflush(stdout);
//         exit(1);
//     }

//     in_line = malloc(content_length + 1);
//     if (in_line == NULL)
//     {
//         printf("<title>Error Occurred</title>\n");
//         printf("</head> <body>\n");
//         printf("<p>Major failure #2; please notify the webmaster\n");
//         printf("</p> </body> </html>\n");
//         fflush(stdout);
//         exit(2);
//     }
//     out_line = malloc(content_length + 1);
//     if (out_line == NULL)
//     {
//         printf("<title>Error Occurred</title>\n");
//         printf("</head> <body>\n");
//         printf("<p>Major failure #3; please notify the webmaster\n");
//         printf("</p> </body> </html>\n");
//         fflush(stdout);
//         exit(2);
//     }
//     gets(in_line);             /* read in form data */
//     current_time = time(NULL); /* get current time */
//     fprintf(tempfile, "%s\n", ctime(&current_time));
//     fprintf(tempfile, "\n%s\n", in_line);
//     fprintf(tempfile, "%s\n", out_line);
//     char keyvar[25];
//     char valuevar[25];
//     url_enc_key_value(in_line, keyvar, valuevar);
//     fprintf(tempfile, "key: %s, value: %s", keyvar, valuevar);
//     fclose(tempfile);

//     add_to_json("name", "blablabla");

//     printf("<title>Form Submitted</title>\n");
//     printf("</head> <body>\n");
//     printf("<h1>Your Form Has Been Submitted</h1>\n");
//     printf("<p> Thank you very much for your input, it has been \n");
//     printf("submitted to our people to deal with... \n");
//     printf("<br>\n");
//     printf("Press the BACK key to return to the form.\n");
//     printf("</p> </body> </html>\n");
//     //remove (fname);                                  /* clean up */
//     exit(0);
// }

// void add_to_json(char *key, char *value)
// {
//     FILE *fp;
//     char buff[255];
//     char ch = 'a';

//     time_t curtime;
//     time(&curtime);

//     fp = fopen("/var/www/html/CGIRPI/file.json", "r+");

//     //printf("\nFile content:\n");
//     while ((ch = getc(fp)) != ']')
//         ;

//     fseek(fp, -1, SEEK_CUR);
//     /* Note that we're cutting "now" off after 19 characters to avoid the \n
//         that ctime() appends to the formatted time string.   */
//     sprintf(buff, ",{\"%s\": \"%s\", \"submit_date\": \"%.19s\"}]", key, value, ctime(&curtime));
//     fputs(buff, fp);

//     //printf("\nEnd of file\n");

//     // close file
//     fclose(fp);
// }

// void url_enc_key_value(char *input, char *key, char *value)
// {
//     int loop_index = 0, output_index = 0;

//     while (input[loop_index] != '=')
//     {
//         printf("%c\n", input[loop_index]);
//         if (input[loop_index] == '%') /* needs translation */
//         {
//             /* if your system uses signed characters, use strtol(). */
//             /* You may want to apply validity
//            checking to the individual characters */
//             key[output_index] = strtoul(input + loop_index + 1, NULL, 16);
//             output_index++;
//             loop_index += 2; /* skip rest of hex value */
//         }

//         else if (input[loop_index] == '+') /* make a space */
//         {
//             key[output_index] = ' ';
//             output_index++;
//         }
//         else /* just copy */
//         {
//             key[output_index] = input[loop_index];
//             output_index++;
//         }

//         loop_index++;
//     }
//     loop_index++;             //skip '=' sign
//     key[output_index] = '\0'; /* null terminate string */
//     output_index = 0;

//     while (input[loop_index] != '&')
//     {
//         if (input[loop_index] == '%') /* needs translation */
//         {
//             /* if your system uses signed characters, use strtol(). */
//             /* You may want to apply validity
//            checking to the individual characters */
//             value[output_index] = strtoul(input + loop_index + 1, NULL, 16);
//             output_index++;
//             loop_index += 2; /* skip rest of hex value */
//         }

//         else if (input[loop_index] == '+') /* make a space */
//         {
//             value[output_index] = ' ';
//             output_index++;
//         }
//         else /* just copy */
//         {
//             value[output_index] = input[loop_index];
//             output_index++;
//         }

//         loop_index++;
//     }
//     value[output_index] = '\0'; /* null terminate string */
// }