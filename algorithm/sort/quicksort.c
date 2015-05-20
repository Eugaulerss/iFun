static int init_compare(const void *key1, const void *key2, int esize)
{
    return strncmp(*(char **)key1, *(char **)key2, esize);
}

static int init_compare2(const void *key1, const void *key2)
{
    return strcmp(*(char **)key1, *(char **)key2);
}

int partition(void *data, int esize, int l, int r,
              int (*compare)(const void *key1, const void *key2))
{
    int     i, j, k, size;
    char   *temp;

    if ((temp = malloc(esize)) == NULL) {
        return -1;
    }

    size = r - l + 1;
    srandom(2);

    i = random() % size;
    j = random() % size;
    k = random() % size;

    /* find the median from i j k*/

    if (i < j) {
        if (j < k) {
            k = j;
        } else if (k < i) {
            k = i;
        }

    } else /* i >= j */ {
        if (j > k) {
            k = j;
        } else if (k > i) {
            k = i;
        }
    }

    k += l;
    i = l;
    j = r;

    while (i < j) {

        while(compare((char *)data + j * esize, (char *)data + k * esize) >= 0 && i < j)
            j--;

        while(compare((char *)data + i * esize, (char *)data + k * esize) <= 0 && i < j)
            i++;

        if (i >= j) {
            break;
        }

        memcpy(temp, (char *)data + j * esize, esize);
        memcpy((char *)data + j * esize, (char *)data + i * esize, esize);
        memcpy((char *)data + i * esize, temp, esize);
    }

    if (i != k) {
        memcpy(temp, (char *)data + i * esize, esize);
        memcpy((char *)data + i * esize, (char *)data + k * esize, esize);
        memcpy((char *)data + k * esize, temp, esize);
    }

    free(temp);
    return j;
}

int qsort(void *data, int esize, int l, int r,
          int (*compare)(const void *key1, const void *key2))
{
    int m;

    if (l >= r) {
        return 0;
    }

    if ((m = partition(data, esize, l, r, compare)) < 0) {
        return -1;
    }

    if ((qsort(data, esize, l, m - 1, compare)) < 0) {
        return -1;
    }

    if ((qsort(data, esize, m + 1, r, compare)) < 0) {
        return -1;
    }

    return 0;
}

#if 0
{
    int m;

    while (l < r) {

        if ((m = partition(data, esize, l, r, compare)) < 0) {
            return -1;
        }

        if (qsort(data, esize, l, m, compare) < 0) {
            return -1;
        }

        l = m + 1;
    }

    return 0;
}
#endif
