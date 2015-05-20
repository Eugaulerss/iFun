static int merge(void *data, int esize, int l, int j, int r,
                 int (*compare)(const void *key1, const void *key2))
{
    int   ip, jp, mp;
    char *m, *d;

    m = malloc(esize * ((r - l) + 1));
    if (m == NULL) {
        return -1;
    }

    d = (char *)data;
    mp = 0;
    ip = l;
    jp = j + 1;

    while (ip <= j || jp <= r) {

        if (ip > j) {
            while (jp <= r) {
                memcpy(&m[esize * mp++], &d[esize * jp++], esize);
            }
            continue;
        }

        if (jp > r) {
            while (ip <= j) {
                memcpy(&m[esize * mp++], &d[esize * ip++], esize);
            }
            continue;
        }

        if (compare(&d[esize * ip], &d[esize * jp]) < 0) {
            memcpy(&m[esize * mp++], &d[esize * ip++], esize);
        } else {
            memcpy(&m[esize * mp++], &d[esize * jp++], esize);
        }
    }

    memcpy(&d[esize * l], m, esize * (r - l + 1));
    free(m);

    return 0;
}

int mgsort(void *data, int esize, int l, int r,
           int (*compare) (const void *key1, const void *key2))
{
    if (l < r) {
        int m = (l + r) / 2;

        if (mgsort(data, esize, l, m, compare) < 0) {
            return -1;
        }

        if (mgsort(data, esize, m + 1, r, compare) < 0) {
            return -1;
        }

        if (merge(data, esize, l, m, r, compare) < 0) {
            return -1;
        }
    }

    return 0;
}
