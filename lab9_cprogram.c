#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct MonthlySales {
    char month[20];
    double sales;
};

void readSalesData(const char *filename, double *salesData, int size) {
    FILE *inputFile = fopen(filename, "r");
    if (inputFile == NULL) {
        printf("Error opening the file.\n");
        exit(1);
    }

    for (int i = 0; i < size; i++) {
        fscanf(inputFile, "%lf", &salesData[i]);
    }

    fclose(inputFile);
}

char* getMonth(int index) {
    char* months[12] = {"January", "February", "March", "April", "May", "June",
                        "July", "August", "September", "October", "November", "December"};
    return months[index];
}

void generateSalesReport(struct MonthlySales *monthlySales, int size) {
    printf("Monthly sales report for 2022:\n");
    printf("Month\tSales\n");
    for (int i = 0; i < size; i++) {
        printf("%s\t$%.2f\n", monthlySales[i].month, monthlySales[i].sales);
    }
}

void generateSalesSummary(struct MonthlySales *monthlySales, int size) {
    double sum = 0, average;
    double minimum = monthlySales[0].sales, maximum = monthlySales[0].sales;
    for (int i = 0; i < size; i++) {
        sum += monthlySales[i].sales;
        if (monthlySales[i].sales < minimum) {
            minimum = monthlySales[i].sales;
        }
        if (monthlySales[i].sales > maximum) {
            maximum = monthlySales[i].sales;
        }
    }
    average = sum / size;

    printf("Sales summary:\n");
    printf("Minimum sales: $%.2f (%s)\n", minimum, monthlySales[0].month);
    printf("Maximum sales: $%.2f (%s)\n", maximum, monthlySales[size - 1].month);
    printf("Average sales: $%.2f\n", average);
}

void generateMovingAverage(struct MonthlySales *monthlySales, int size) {
    printf("Six-Month Moving Average Report:\n");
    for (int i = 0; i <= 6; i++) {
        if (i + 6 <= size) {
            double sum = 0;
            for (int j = i; j < i + 6; j++) {
                sum += monthlySales[j].sales;
            }
            double average = sum / 6;
            printf("%s - %s $%.2f\n", monthlySales[i].month, monthlySales[i + 5].month, average);
        }
    }
}

void generateSalesReportHighToLow(struct MonthlySales *monthlySales, int size) {
    printf("Sales Report (Highest to Lowest):\n");
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (monthlySales[i].sales < monthlySales[j].sales) {
                struct MonthlySales temp = monthlySales[i];
                monthlySales[i] = monthlySales[j];
                monthlySales[j] = temp;
            }
        }
    }

    printf("Month\tSales\n");
    for (int i = 0; i < size; i++) {
        printf("%s\t$%.2f\n", monthlySales[i].month, monthlySales[i].sales);
    }
}

int main() {
    struct MonthlySales monthlySales[12];
    double salesData[12];
    readSalesData("input.txt", salesData, 12);

    for (int i = 0; i < 12; i++) {
        strcpy(monthlySales[i].month, getMonth(i));
        monthlySales[i].sales = salesData[i];
    }

    generateSalesReport(monthlySales, 12);
    printf("\n");
    generateSalesSummary(monthlySales, 12);
    printf("\n");
    generateMovingAverage(monthlySales, 12);
    printf("\n");
    generateSalesReportHighToLow(monthlySales, 12);

    return 0;
}
