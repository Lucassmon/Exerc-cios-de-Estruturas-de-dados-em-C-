#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int id;
    int age;
    float weight;
    float height;
    float SBP;  // Systolic Blood Pressure
    float DBP;  // Diastolic Blood Pressure
    float MAP;  // Mean Arterial Pressure
    float BMI;  // Body Mass Index
} Patient;

// Function to calculate MAP
float calculate_map(float SBP, float DBP) {
    return SBP / 3.0f + 2.0f * DBP / 3.0f;
}

// Function to calculate BMI
float calculate_bmi(float weight, float height) {
    return weight / (height * height);
}
 //Comparatorpatients
int compare_patients(const void* a, const void* b) {
    const Patient* p1 = (const Patient*)a;
    const Patient* p2 = (const Patient*)b;

    if (p1->MAP > p2->MAP) return -1;
    if (p1->MAP < p2->MAP) return 1;

    if (p1->BMI > p2->BMI) return -1;
    if (p1->BMI < p2->BMI) return 1;

    if (p1->age > p2->age) return -1;
    if (p1->age < p2->age) return 1;

    if (p1->id < p2->id) return -1;
    if (p1->id > p2->id) return 1;

    return 0;
}

int main() {
    int n;
    scanf("%d", &n);

    Patient patients[n];

    for (int i = 0; i < n; i++) {
        scanf("%d %d %f %f %f %f",
              &patients[i].id,
              &patients[i].age,
              &patients[i].weight,
              &patients[i].height,
              &patients[i].SBP,
              &patients[i].DBP);

        patients[i].MAP = calculate_map(patients[i].SBP, patients[i].DBP);
        patients[i].BMI = calculate_bmi(patients[i].weight, patients[i].height);
    }
    qsort(patients, n, sizeof(Patient), compare_patients);

    for (int i = 0; i < n; i++) {
        printf("%d %d %.2f %.2f\n",
               patients[i].id,
               patients[i].age,
               patients[i].MAP,
               patients[i].BMI);
    }

    return 0;
}
