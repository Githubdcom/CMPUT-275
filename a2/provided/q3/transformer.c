#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int r, g, b;
} Pixel;

static void die(void) {
    /* spec says we don't need to replicate error messages */
    exit(1);
}

static Pixel *read_ppm_p3(int *w, int *h) {
    char magic[3];
    int maxv;

    if (scanf("%2s", magic) != 1) die();
    if (!(magic[0] == 'P' && magic[1] == '3' && magic[2] == '\0')) die();

    if (scanf("%d %d", w, h) != 2) die();
    if (*w < 0 || *h < 0) die();

    if (scanf("%d", &maxv) != 1) die();
    /* assignment says assume it's always 255 */
    if (maxv != 255) die();

    long long n = (long long)(*w) * (long long)(*h);
    if (n < 0) die();

    Pixel *pix = (Pixel *)malloc((size_t)n * sizeof(Pixel));
    if (pix == NULL) die();

    for (long long i = 0; i < n; i++) {
        if (scanf("%d %d %d", &pix[i].r, &pix[i].g, &pix[i].b) != 3) {
            free(pix);
            die();
        }
    }

    return pix;
}

static void write_ppm_p3(int w, int h, const Pixel *pix) {
    printf("P3\n");
    printf("%d %d\n", w, h);
    printf("255\n");

    long long n = (long long)w * (long long)h;
    for (long long i = 0; i < n; i++) {
        printf("%d %d %d", pix[i].r, pix[i].g, pix[i].b);
        if ((i + 1) % w == 0) {
            putchar('\n');
        } else {
            putchar(' ');
        }
    }
}

static void flip_horizontal(int w, int h, Pixel *pix) {
    for (int row = 0; row < h; row++) {
        int left = 0;
        int right = w - 1;
        while (left < right) {
            Pixel tmp = pix[row * w + left];
            pix[row * w + left] = pix[row * w + right];
            pix[row * w + right] = tmp;
            left++;
            right--;
        }
    }
}

static int clamp255(int x) {
    if (x < 0) return 0;
    if (x > 255) return 255;
    return x;
}

static void apply_sepia(int w, int h, Pixel *pix) {
    long long n = (long long)w * (long long)h;
    for (long long i = 0; i < n; i++) {
        int R = pix[i].r;
        int G = pix[i].g;
        int B = pix[i].b;

        /* use scaled integers to avoid math.h:
           floor(R*0.393 + G*0.769 + B*0.189)
           = floor((393R + 769G + 189B) / 1000)
        */
        int newR = (393 * R + 769 * G + 189 * B) / 1000;
        int newG = (349 * R + 686 * G + 168 * B) / 1000;
        int newB = (272 * R + 534 * G + 131 * B) / 1000;

        pix[i].r = clamp255(newR);
        pix[i].g = clamp255(newG);
        pix[i].b = clamp255(newB);
    }
}

int main(int argc, char **argv) {
    int do_flip = 0;
    int do_sepia = 0;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-' && argv[i][1] == 'f' && argv[i][2] == '\0') {
            do_flip = 1;
        } else if (argv[i][0] == '-' && argv[i][1] == 's' && argv[i][2] == '\0') {
            do_sepia = 1;
        } else {
            /* ignore unknown flags or treat as error; sample will define */
            die();
        }
    }

    int w, h;
    Pixel *pix = read_ppm_p3(&w, &h);

    if (do_flip) flip_horizontal(w, h, pix);
    if (do_sepia) apply_sepia(w, h, pix);

    write_ppm_p3(w, h, pix);

    free(pix);
    return 0;
}