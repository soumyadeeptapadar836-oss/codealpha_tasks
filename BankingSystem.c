#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "accounts.dat"

struct Account {
    int accNo;
    char name[50];
    double balance;
};

void createAccount();
void deposit();
void withdraw();
void balanceEnquiry();

int main() {
    int choice;

    while (1) {
        printf("\n===== Bank Account Management System =====\n");
        printf("1. Create Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Balance Enquiry\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createAccount(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;
            case 4: balanceEnquiry(); break;
            case 5:
                printf("Thank you for using the Bank Management System. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

void createAccount() {
    struct Account acc;
    FILE *fp = fopen(FILENAME, "ab");

    if (fp == NULL) { printf("Error opening file.\n"); return; }

    printf("Enter Account Number: ");
    scanf("%d", &acc.accNo);
    printf("Enter Account Holder Name: ");
    scanf(" %49[^\n]", acc.name);
    printf("Enter Initial Deposit Amount: ");
    scanf("%lf", &acc.balance);

    if (acc.balance < 0) {
        printf("Error: Initial deposit cannot be negative.\n");
        fclose(fp);
        return;
    }

    fwrite(&acc, sizeof(struct Account), 1, fp);
    fclose(fp);
    printf("Account created successfully.\n");
}

void deposit() {
    struct Account acc;
    int accNo;
    double amount;
    int found = 0;

    FILE *fp = fopen(FILENAME, "rb+");
    if (fp == NULL) { printf("No accounts found. Please create an account first.\n"); return; }

    printf("Enter Account Number: ");
    scanf("%d", &accNo);
    printf("Enter Amount to Deposit: ");
    scanf("%lf", &amount);

    if (amount <= 0) {
        printf("Error: Deposit amount must be positive.\n");
        fclose(fp);
        return;
    }

    while (fread(&acc, sizeof(struct Account), 1, fp) == 1) {
        if (acc.accNo == accNo) {
            acc.balance += amount;
            fseek(fp, -(long)sizeof(struct Account), SEEK_CUR);
            fwrite(&acc, sizeof(struct Account), 1, fp);
            found = 1;
            printf("Deposit successful. New balance: %.2f\n", acc.balance);
            break;
        }
    }
    if (!found) printf("Account number %d not found.\n", accNo);
    fclose(fp);
}

void withdraw() {
    struct Account acc;
    int accNo;
    double amount;
    int found = 0;

    FILE *fp = fopen(FILENAME, "rb+");
    if (fp == NULL) { printf("No accounts found. Please create an account first.\n"); return; }

    printf("Enter Account Number: ");
    scanf("%d", &accNo);
    printf("Enter Amount to Withdraw: ");
    scanf("%lf", &amount);

    if (amount <= 0) {
        printf("Error: Withdrawal amount must be positive.\n");
        fclose(fp);
        return;
    }

    while (fread(&acc, sizeof(struct Account), 1, fp) == 1) {
        if (acc.accNo == accNo) {
            found = 1;
            if (amount > acc.balance) {
                printf("Error: Insufficient balance. Current balance: %.2f\n", acc.balance);
                break;
            }
            acc.balance -= amount;
            fseek(fp, -(long)sizeof(struct Account), SEEK_CUR);
            fwrite(&acc, sizeof(struct Account), 1, fp);
            printf("Withdrawal successful. New balance: %.2f\n", acc.balance);
            break;
        }
    }
    if (!found) printf("Account number %d not found.\n", accNo);
    fclose(fp);
}

void balanceEnquiry() {
    struct Account acc;
    int accNo;
    int found = 0;

    FILE *fp = fopen(FILENAME, "rb");
    if (fp == NULL) { printf("No accounts found. Please create an account first.\n"); return; }

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    while (fread(&acc, sizeof(struct Account), 1, fp) == 1) {
        if (acc.accNo == accNo) {
            printf("\nAccount Details:\n");
            printf("Account Number : %d\n", acc.accNo);
            printf("Account Holder : %s\n", acc.name);
            printf("Current Balance: %.2f\n", acc.balance);
            found = 1;
            break;
        }
    }
    if (!found) printf("Account number %d not found.\n", accNo);
    fclose(fp);
}