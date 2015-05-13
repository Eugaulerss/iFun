int insort(void *data, int size, int esize,
           int (*compare)(const void *key1, const void *key2))
{
    int i, j;
    char *temp;

    if ((temp = malloc(esize)) == NULL) {
        return -1;
    }

    for (j = 1, j < size, j++) {

        memcpy(temp, (char *)data + j * esize, esize);
        i = j - 1;

        while(i >= 0 && compare((char *)data + i * esize, temp) > 0) {
            memcpy((char *)data + (i + 1) * esize, (char *)data + i * esize, esize);
            i--;
        }

        memcpy((char *)data + (i + 1) * esize, temp, esize);
    }

    free(temp);
    return 0;
}
