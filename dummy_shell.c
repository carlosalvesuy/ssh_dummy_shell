/*
 * SSH Dummy Shell
 *
 * Copyright (c) 2014, Carlos Alves <carlos@carlosalves.info>
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * 
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<unistd.h>
#include<syslog.h>

#define MOTD "/etc/motd"


int
display_motd(char *filename)
{
    /* 
     * Display the message of the day.
     */
    FILE *file;
    char buf[256];

    file = fopen(filename, "r");
    if ( file == NULL ) {
        perror("Error while opening the motd file.\n");
        return (-1);
    }
    else {
        while (fgets(buf, sizeof(buf), file))
            fputs(buf, stdout);
    }
    fclose(file);
    return 0;
}


void
clear(void)
{
    /* Function to clear the screen
     * based on VT100 ANSI escape sequences
     * More specifically:
     *
     *  * 033 is the octal of ESC
     *  * 2J is for clearing the entire console/terminal screen
     *    (and moves cursor to upper left on DOS ANSI.SYS)
     *  * 1;1H moves the cursor to row 1 and column 1
     */
    fputs("\033[2J\033[1;1H", stdout);
}


void
get_time(void)
{
    time_t now;
    time(&now);

    printf("%s", ctime(&now)); /* Use ctime to format time to a string. */
}


void
log_entry(char *user_name, char *tty, char *ip_addr)
{
    openlog("dummy", LOG_CONS, LOG_AUTH);
    syslog(LOG_CRIT, "Session opened for user %s on %s from %s",
                                    user_name, tty, ip_addr);
    closelog();
}

int
main(void)
{
    char *ssh_connection;
    char *ssh_tty;
    char *ssh_logname;
    char *delimiter = " ";
    char *ip_address;

    ssh_connection = getenv("SSH_CONNECTION");
    ssh_tty = getenv("SSH_TTY");
    ssh_logname = getenv("LOGNAME");
    ip_address = strtok(ssh_connection, delimiter);

    if (ssh_connection) {
        log_entry(ssh_logname, ssh_tty, ip_address);
        while (1) {
           clear();
           get_time();
           display_motd(MOTD);
           sleep(60);
        }    
    }
    else {
        puts("This shell is meant to use only for ssh forward users.");
    }    
}
