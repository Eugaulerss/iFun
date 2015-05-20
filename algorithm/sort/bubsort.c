int bubsort(void *data, int size, int esize,
            int (*compare)(const void *key1, const void *key2))
{
    int i, j;
    char *temp;

    if ((temp = malloc(esize)) == NULL) {
        return -1;
    }

    for (i = 0; i < size - 1; i++) {

        for (j = size - 1; j > i; j--) {

            if (compare((char *)data + j * esize, (char *)data + (j - 1) * esize) < 0) {
                memcpy(temp, (char *)data + j * esize, esize);
                memcpy((char *)data + j * esize, (char *)data + (j - 1) * esize, esize);
                memcpy((char *)data + (j - 1) * esize, temp, esize);
            }
        }
    }

    free(temp);
    return 0;
}
