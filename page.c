#include <stdio.h>
#include <stdbool.h>

#define N_PAGES 12
#define N_FRAMES 3

void printFrames(int frames[], int n_frames) {
    for (int i = 0; i < n_frames; i++) {
        if (frames[i] == -1)
            printf(" - ");
        else
            printf(" %d ", frames[i]);
    }
    printf("\n");
}

bool isPageInFrames(int page, int frames[], int n_frames) {
    for (int i = 0; i < n_frames; i++) {
        if (frames[i] == page)
            return true;
    }
    return false;
}

void calculateRatios(int hits, int n_pages) {
    float hit_ratio = (float)hits / n_pages;
    float miss_ratio = 1 - hit_ratio;
    printf("Hit Ratio: %.2f\n", hit_ratio);
    printf("Miss Ratio: %.2f\n", miss_ratio);
}

void FIFO(int pages[], int n_pages, int frames[], int n_frames) {
    int page_faults = 0, hits = 0;
    int index = 0;

    for (int i = 0; i < n_pages; i++) {
        if (isPageInFrames(pages[i], frames, n_frames)) {
            hits++;
        } else {
            frames[index] = pages[i];
            index = (index + 1) % n_frames;
            page_faults++;
            printFrames(frames, n_frames);
        }
    }

    printf("Total Page Faults: %d\n", page_faults);
    calculateRatios(hits, n_pages);
}

void LRU(int pages[], int n_pages, int frames[], int n_frames) {
    int page_faults = 0, hits = 0;
    int counter = 0;
    int used[n_frames];
    int index;

    for (int i = 0; i < n_frames; i++) {
        frames[i] = -1;
        used[i] = 0;
    }

    for (int i = 0; i < n_pages; i++) {
        index = -1;
        if (isPageInFrames(pages[i], frames, n_frames)) {
            hits++;
            // Find the index of the current page in frames
            for (int j = 0; j < n_frames; j++) {
                if (frames[j] == pages[i]) {
                    index = j;
                    break;
                }
            }
        } else {
            // Page fault handling: find the least recently used frame
            int min = used[0], pos = 0;
            for (int j = 1; j < n_frames; j++) {
                if (used[j] < min) {
                    min = used[j];
                    pos = j;
                }
            }
            frames[pos] = pages[i];
            index = pos;  // Update the frame position to the newly used frame
            page_faults++;
        }
        // Update the usage of the current frame
        used[index] = ++counter;
        printFrames(frames, n_frames);
    }

    printf("Total Page Faults: %d\n", page_faults);
    calculateRatios(hits, n_pages);
}


void Optimal(int pages[], int n_pages, int frames[], int n_frames) {
    int page_faults = 0, hits = 0;
    int index;

    for (int i = 0; i < n_frames; i++) {
        frames[i] = -1;
    }

    for (int i = 0; i < n_pages; i++) {
        if (isPageInFrames(pages[i], frames, n_frames)) {
            hits++;
        } else {
            int pos = -1, farthest = i + 1;
            for (int j = 0; j < n_frames; j++) {
                int k;
                for (k = i + 1; k < n_pages; k++) {
                    if (frames[j] == pages[k]) {
                        if (k > farthest) {
                            farthest = k;
                            pos = j;
                        }
                        break;
                    }
                }
                if (k == n_pages) {
                    pos = j;
                    break;
                }
            }
            if (pos == -1) pos = 0;
            frames[pos] = pages[i];
            page_faults++;
            printFrames(frames, n_frames);
        }
    }

    printf("Total Page Faults: %d\n", page_faults);
    calculateRatios(hits, n_pages);
}

int main() {
    int pages[N_PAGES] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3}; // Example page sequence
    int frames[N_FRAMES];

    printf("FIFO Algorithm:\n");
    FIFO(pages, N_PAGES, frames, N_FRAMES);
    printf("\nLRU Algorithm:\n");
    LRU(pages, N_PAGES, frames, N_FRAMES);
    printf("\nOptimal Algorithm:\n");
    Optimal(pages, N_PAGES, frames, N_FRAMES);

    return 0;
}
