#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "stats.h"

#pragma warning(disable:4996)

#define NotNull(ptr) notNull(ptr, __LINE__)
#define SafeMalloc(size) safeMalloc(size, __LINE__)

/*typedef struct {
	unsigned int day;
	unsigned int month;
	unsigned int year;
} Date;

typedef struct Stats {
	Date* date;
	float temp;
	struct Stats* next;
} Stats;*/

void* notNull(void* ptr, int line) {
	if (ptr == NULL) {
		printf("Null pointer at %i\n", line);
		exit(1);
	}
	return ptr;
}

void* safeMalloc(int size, int line) {
	return notNull(malloc(size), line);
}

FILE* fileOpen(char* name, char* mode) {
	return (FILE*)NotNull(fopen(name, mode));
}

void fileClose(FILE* file) {
	fclose(file);
}

Date* newDate(unsigned char day, unsigned char month, unsigned int year) {
	Date* date = (Date*)SafeMalloc(sizeof(Date));
	date->day = day;
	date->month = month;
	date->year = year;
	return date;
}

void destroyDate(Date* date) {
	free(date);
}

Stats* newStats(Date* date, float temp) {
	Stats* stats = (Stats*)SafeMalloc(sizeof(Stats));
	stats->date = date;
	stats->temp = temp;
	stats->next = NULL;
	return stats;
}

void destroyStats(Stats* stats) {
	destroyDate(stats->date);
	free(stats);
}

void destroyStatsList(Stats* head) {
	Stats* prev = head, * cur = prev->next;
	destroyStats(prev);
	while (cur != NULL) {
		prev = cur;
		cur = cur->next;
		destroyStats(prev);
	}
}

int sign(int num) {
	return (num > 0) - (num < 0);
}

int compareInts(int left, int right) {
	//printf("compare %i and %i res: %i\n", left, right, sign(right - left));
	return sign(right - left);
}

int compareDates(Date* left, Date* right) {
	int year = compareInts(left->year, right->year);
	if (year) return year;
	int month = compareInts(left->month, right->month);
	if (month) return month;
	return compareInts(left->day, right->day);
	//printf("comparing dates left: %d.%d.%d right: %d.%d.%d\n", left->day, left->month, left->year, right->day, right->month, right->year);
	//return compareInts(left->year, right->year)
		//|| compareInts(left->month, right->month)
		//|| compareInts(left->day, right->day);
}

Stats* insertStats(Stats* head, Stats* stats) {
	//printf("Inserting %d.%d.%d %.1f\n", stats->date->day, stats->date->month, stats->date->year, stats->temp);
	Stats* ptr = head;
	if (stats->temp < ptr->temp) {
		stats->next = ptr;
		return stats;
	}
	while (ptr != NULL) {
		//printf("ptr is %d.%d.%d %.1f\n", ptr->date->day, ptr->date->month, ptr->date->year, ptr->temp);
		if (ptr->next == NULL) {
			ptr->next = stats;
			break;
		}
		else {
			if (stats->temp < ptr->next->temp) {
				stats->next = ptr->next;
				ptr->next = stats;
				break;
			}
			else if (stats->temp == ptr->next->temp) {
				int compared = compareDates(stats->date, ptr->next->date);
				//printf("here %i\n", compared);
				if (compared > -1) {
					//printf("inserting before next with the same temp %.1f\n", ptr->next->temp);
					stats->next = ptr->next;
					ptr->next = stats;
					break;
				}
			}
			ptr = ptr->next;
		}
	}
	//printf("--------\n");
	return head;
}

void printStats(Stats* stats) {
	printf(
		"%i.%i.%i %.1f\n",
		stats->date->day,
		stats->date->month,
		stats->date->year,
		stats->temp
	);
}

Stats* newStatsFromFile(FILE* file, char* format) {
	int day, month, year;
	float temp;
	if ((fscanf(file, format, &day, &month, &year, &temp)) != EOF) {
		return newStats(
			newDate(day, month, year),
			temp
		);
	};
	return NULL;
}

void printMatchingTemp(Stats* head, float input) {
	Stats* ptr = head;
	while (ptr != NULL) {
		if (ptr->temp == input) {
			printStats(ptr);
			return;
		}
		ptr = ptr->next;
	}
	printf("No dates with temperature %.1f were found.\n", input);
}

Stats* statsListFromFile(char* name) {
	FILE* file = fopen(name, "r");
	Stats* head, * cur = NULL;
	char* format = "%i.%i.%i %f";
	head = newStatsFromFile(file, format);
	cur = newStatsFromFile(file, format);
	while (cur != NULL) {
		head = insertStats(head, cur);
		cur = newStatsFromFile(file, format);
	}
	fclose(file);
	return head;
}

void printIfLessThan(Stats* head, int temp) {
	Stats* ptr = head;
	while (ptr != NULL) {
		if (ptr->temp >= temp) {
			break;
		}
		printStats(ptr);
		ptr = ptr->next;
	}
}

void printMatchingTempPrompted(Stats* head) {
	float input;
	printf("Type a temperature to be found: \n");
	scanf("%f", &input);
	printMatchingTemp(head, input);
}

void actionOnFile(char* name) {
	Stats* head = statsListFromFile(name);
	printIfLessThan(head, 0);
	printMatchingTempPrompted(head);
}