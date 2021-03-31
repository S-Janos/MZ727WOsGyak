//
// Created by Szamurajpalanta on 3/27/2021.
//

#include <stdio.h>
#include <fcntl.h>

int main() {
    int fh = open("MZ727W.txt", O_RDWR);
    if(fh == -1) {
        perror("A fájl megnyitasa sikertelen.\n");
        return 1;
    } else
        printf("A fájl megynitasa sikeres!\n");

    char content[64];
    int readContent = read(fh, content, sizeof(content));
    printf("Beolvasott szoveg:\n%s\nOsszesen %i byte.\n", content, readContent);

    lseek(fh, 0, SEEK_SET);
    char text[] = "teszt";
    int written = write(fh, text, sizeof(text));
    printf("\"%s\" szoveg fajlba irva. Osszesen %i byte.\n", text, written);
    close(fh);
    return 0;
}