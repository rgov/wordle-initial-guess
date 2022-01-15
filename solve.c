#include <math.h>
#include <stdint.h>
#include <stdio.h>

#include "words.h"


int compare(const char *target, const char *guess) {
    int counts[26] = { 0 };
    for (int i = 0; i < WORD_LEN; i ++) {
        counts[target[i] - 'a'] ++;
    }

    int result = 0;
    for (int i = 0; i < WORD_LEN; i ++) {
        result *= 3;  // shift

        if (target[i] == guess[i]) {
            result += 2;  // correct guess
            counts[guess[i] - 'a'] --;
        } else if (counts[guess[i] - 'a'] > 0) {
            result += 1;  // wrong place
            counts[guess[i] - 'a'] --;
        }
    }

    return result;
}


int main() {
    int bestguessi = 0;
    float bestsd = 0.0;

    for (int guessi = 0; guessi < NUM_WORDS; guessi ++) {
        int hist[3*3*3*3*3 /*3^WORD_LEN*/] = { 0 };

        for (int targeti = 0; targeti < NUM_TARGETS; targeti ++) {
            hist[compare(TARGET_WORDS[targeti], ALL_WORDS[guessi])] ++;
        }

        // compute average
        float mean = 0.0;
        for (int i = 0; i < (sizeof(hist) / sizeof(hist[0])); i ++) {
            mean += hist[i];
        }
        mean /= (sizeof(hist) / sizeof(hist[0]));

        // compute standard deviation
        float sd = 0.0;
        for (int i = 0; i < (sizeof(hist) / sizeof(hist[0])); i ++) {
            sd += (hist[i] - mean) * (hist[i] - mean);
        }
        sd /= (sizeof(hist) / sizeof(hist[0]));
        sd = sqrt(sd);

        if (guessi == 0 || sd < bestsd) {
            bestguessi = guessi;
            bestsd = sd;

            printf("Best guess so far is %s with sd %.3f\n",
                ALL_WORDS[bestguessi], bestsd);
        }
    }
    
    printf("Done.\n");
    return 0;
}