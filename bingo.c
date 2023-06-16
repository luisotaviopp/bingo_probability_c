#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CARD_ROWS 5
#define CARD_COLUMNS 5
#define NUM_CARDS 75
#define MAX_NUM 99

// Check if a number already exists in the card
int existsInCard(int card[CARD_ROWS][CARD_COLUMNS], int number) {
    int i, j;
    for (i = 0; i < CARD_ROWS; i++) {
        for (j = 0; j < CARD_COLUMNS; j++) {
            if (card[i][j] == number) {
                return 1; // Number already exists in the card
            }
        }
    }
    return 0; // Number does not exist in the card
}

// Generate a random combination of numbers for a card
void generateCard(int card[CARD_ROWS][CARD_COLUMNS]) {
    int i, j;
    int numbersRemaining = CARD_ROWS * CARD_COLUMNS;
    int availableNumbers[MAX_NUM] = {0};

    for (i = 0; i < CARD_ROWS; i++) {
        for (j = 0; j < CARD_COLUMNS; j++) {
            int number;
            do {
                number = rand() % MAX_NUM + 1;
            } while (existsInCard(card, number) || availableNumbers[number - 1]);
            
            card[i][j] = number;
            availableNumbers[number - 1] = 1;
            numbersRemaining--;
            
            if (numbersRemaining == 0)
                return; // All numbers have been placed in the card
        }
    }
}

// Print a card
void printCard(int card[CARD_ROWS][CARD_COLUMNS]) {
    int i, j;

    for (i = 0; i < CARD_ROWS; i++) {
        for (j = 0; j < CARD_COLUMNS; j++) {
            printf("%3d ", card[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Compare probabilities for qsort
int compareProbabilities(const void* a, const void* b) {
    float probA = *((float*)a);
    float probB = *((float*)b);

    if (probA < probB) {
        return 1;
    } else if (probA > probB) {
        return -1;
    } else {
        return 0;
    }
}

int main() {
    int cards[NUM_CARDS][CARD_ROWS][CARD_COLUMNS];
    int i, j, k;
    int count[NUM_CARDS] = {0};  // Array to count the occurrences of each card
    float probabilities[NUM_CARDS] = {0};  // Array to store the probabilities of each card combination
    float highestProbability = 0;
    float lowestProbability = 1;
    float averageProbability = 0;

    srand(time(NULL)); // Initialize random number generator

    // Generate the cards
    for (i = 0; i < NUM_CARDS; i++) {
        generateCard(cards[i]);

        // Count the occurrences of each card
        for (j = 0; j < CARD_ROWS; j++) {
            for (k = 0; k < CARD_COLUMNS; k++) {
                count[cards[i][j][k] - 1]++;
            }
        }
    }

    // Calculate the probability of each card combination
    for (i = 0; i < NUM_CARDS; i++) {
        probabilities[i] = (float)count[i] / (NUM_CARDS * (CARD_ROWS * CARD_COLUMNS));

        // Update highest and lowest probabilities
        if (probabilities[i] > highestProbability) {
            highestProbability = probabilities[i];
        }
        
        if (probabilities[i] < lowestProbability) {
            lowestProbability = probabilities[i];
        }

        // Calculate running total for average probability
        averageProbability += probabilities[i];
    }

    // Sort the probabilities in descending order
    qsort(probabilities, NUM_CARDS, sizeof(float), compareProbabilities);

    // Print the cards and card combination probabilities in descending order
    printf("Card Combination Probabilities (High to Low):\n");
    for (i = 0; i < NUM_CARDS; i++) {
        int cardNumber = i + 1;
        float probability = probabilities[i];

        printf("Card %d:\n\n", cardNumber);
        printCard(cards[cardNumber - 1]);

        printf("Probability: %.5f%%\n", probability * 100);
        printf("\n");
    }

    // Print statistics
    printf("Number of Cards: %d\n", NUM_CARDS);
    printf("Highest Probability: %.5f%%\n", highestProbability * 100);
    printf("Lowest Probability: %.5f%%\n", lowestProbability * 100);
    printf("Average Probability: %.5f%%\n", (averageProbability / NUM_CARDS) * 100);

    return 0;
}
