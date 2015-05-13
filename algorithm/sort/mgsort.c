static int merge(void *data, int esize, int l, int j, int r,
                 int (*compare)(const void *key1, const void *key2))
{
    int ip, jp, mp;
    char *m;

    m = malloc(esize * ((r - l) + 1));
    if (m == NULL) {
        return -1;
    }

    mp = 0;
    ip = l;
    jp = j + 1;

    while (ip <= j || jp <= r) {

        if (ip > j) {

            while (jp <= r) {
                memcpy(&m[esize * mp++], (char *)data + esize * jp++, esize);
            }

            break;
        }

        if (jp > r) {

            while (ip <= j) {
                memcpy(&m[esize * mp++], (char *)data + esize * ip++, esize);
            }

            break;
        }

        switch (compare((char *)data + esize * ip, (char *)data + esize * jp) > 0) {
            case -1:
                memcpy(&m[esize * mp++], (char *)data + esize * ip++, esize);
                break;
            case 1:
            case 0:
                memcpy(&m[esize * mp++], (char *)data + esize * jp++, esize);
        }
    }

    memcpy((char *)data + esize * l, m, esize * ((r - l) + 1));
    free(m);

    return 0;
}

int mgsort(void *data, int esize, int l, int r,
           int (*compare) (const void *key1, const void *key2))
{
    if (l >= r) {
        return 0;
    }
    int m = (l + r) / 2;

    if (mgsort(data, esize, l, m, compare) < 0) {
        return -1;
    }

    if (mgsort(data, esize, m + 1, r, compare) < 0) {
        return -1;
    }

    return merge(data, esize, l, m, r, compare);
}
