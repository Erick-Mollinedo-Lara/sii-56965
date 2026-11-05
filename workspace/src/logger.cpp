#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <fcntl.h>     // Importante para O_RDONLY
#include <sys/stat.h>  // Importante para mkfifo

int main(int argc, char **argv) {
    int fd;
    char buffer[1024];
    
    // Guardamos la ruta en una variable para no escribirla todo el rato
    const char * ruta_fifo = "/tmp/fifo_tenis";

    // borrar FIFO por si existiera previamente
    unlink(ruta_fifo);

    /* crear el FIFO */
    if (mkfifo(ruta_fifo, 0666) < 0) {
        perror("No puede crearse el FIFO");
        return(1);
    }

    /* Abrir el FIFO */
    if ((fd = open(ruta_fifo, O_RDONLY)) < 0) {
        perror("No puede abrirse el FIFO");
        return(1);
    }

    printf("Logger iniciado. Esperando datos...\n");

    /* Leer de la FIFO */
    while (read(fd, buffer, sizeof(buffer)) > 0) {
        // Imprimir el texto en la pantalla
        printf("%s\n", buffer);
    }

    close(fd);
    unlink(ruta_fifo);
    
    return(0);
}
