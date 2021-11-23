
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "internal/macros.h"
#include "internal/utils.h"
#include "asinine/dsl.h"
#include "asinine/x509.h"
#include "certlogic.h"

void uart_tx_message(const char* message) {
    printf("%s", message);
    fflush(stdout);
}

int main(int argc, char** argv) {
    
    int retval = 0;
    if (argc != 2) {
        printf("Please provide the path to a certificate to read.\n");
        retval = -1; goto exit;
    }

    char* filepath = argv[1];
    struct stat filestat;

    printf("Parsing Certificate in %s\n", filepath);
    
    int fd = open(filepath, O_RDONLY);
    if ( fd < 0 ) {
        printf("Unable to open file.\n");
        retval = -2; goto exit;
    }

    if (fstat(fd, &filestat) == -1) {
        printf("fstat error.\n");
        retval = -3; goto exit_close;
    }

    size_t filesize = (size_t) filestat.st_size;
    unsigned char* buffer = calloc(1, filesize);
    printf("File Size: %lu\n", filesize);

    unsigned char* decoded_buffer = calloc(1, filesize);
    if ( buffer == NULL || decoded_buffer == NULL ) {
        printf("allocation failure.\n");
        retval = -4; goto exit_free;
    }

    size_t nread = read(fd, buffer, filesize);
    if ( nread != filesize ) {
        printf("read failure.\n");
        retval = -5; goto exit_free;
    }

    size_t output_length = 0;
    if ( base64_decode(decoded_buffer, buffer, filesize, &output_length) == false ) {
        printf("base64_decode failure.\n");
        retval = -6; goto exit_free;
    }

    echo_certificates(decoded_buffer, output_length);   /* now we can do what the code is supposed to do */

exit_free:
    if (buffer!=NULL) {
        free(buffer);
        buffer = NULL;
    }
    if (decoded_buffer!=NULL) {
        free(decoded_buffer);
        decoded_buffer = NULL;
    }
exit_close:
    close(fd);
exit:
    return retval;
}
