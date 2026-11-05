#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "DatosMemCompartida.h"
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char* argv[])
{
	int i;
	DatosMemCompartida* dat;
	char *direccion;
	int fd;
	
	// X1: Abrir el fichero creado en tenis
	fd = open("/tmp/memoria_tenis", O_RDWR);
	if (fd == -1)
	{
		perror("Error al abrir el archivo"); 
		return 1;
	}

	// X2: Proyectar la memoria
	direccion = (char*) mmap(NULL, sizeof(DatosMemCompartida), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (direccion == MAP_FAILED)
	{
		perror("Error en la proyeccion mmap"); 
		return 1;
	}
	close(fd);
	dat = (DatosMemCompartida*) direccion;

	printf("Bot conectado con éxito a la memoria compartida.\n");

	while(1)
	{
		usleep(25000); // 25 milisegundos

		// X3: Lógica del bot (1 arriba, -1 abajo, 0 nada)
		float y_pelota = dat->esfera.centro.y;
		float y_raqueta = (dat->raqueta1.y1 + dat->raqueta1.y2) / 2.0f;

		if (y_pelota > y_raqueta + 0.2f) {
			dat->accion = 1;  // Pelota por encima -> Subir
		} else if (y_pelota < y_raqueta - 0.2f) {
			dat->accion = -1; // Pelota por debajo -> Bajar
		} else {
			dat->accion = 0;  // Alineada -> Nada
		}
	}
	return 0;
}
