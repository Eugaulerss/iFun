int selectsort(void *data, int size, int esize,
               int (*compare)(const void *key1, const void *key2))
{
    int     i, j, k;
    char   *temp;

    if ((temp = malloc(esize)) == NULL) {
        return -1;
    }

    for (i = 0; i < size - 1; i++) {

        k = i;

        for (j = i + 1; j < size; j++) {

            if (compare((char *)data + k * esize, (char *)data + j * esize) > 0) {
                k = j;
            }
        }

        if (k != i) {
            memcpy(temp, (char *)data + i * esize, esize);
            memcpy((char *)data + esize * i, (char *)data + esize * k, esize);
            memcpy((char *)data + k * esize, temp, esize);
        }
    }

    free(temp);
    return 0;
}
