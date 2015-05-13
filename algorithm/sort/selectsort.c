int selectsort(void *data, int size, int esize,
               int (*compare)(const void *key1, const void *key2))
{
    int i, j, k;
    char *least;

    if ((least = malloc(esize)) == NULL) {
        return -1;
    }

    for (i = 0; i < size - 1; i++) {

        k = i;
        memcpy(least, (char *)data + i * esize, esize);

        for (j = i + 1; j < size; j++) {

            if (compare(least, (char *)data + j * esize) > 0) {
                k = j;
                memcpy(least, (char *)data + j * esize, esize);
            }
        }

        if (k != i) {
            memcpy((char *)data + esize * k, (char *)data + esize * i, esize);
            memcpy((char *)data + i * esize, least, esize);
        }
    }

    free(least);
    return 0;
}
