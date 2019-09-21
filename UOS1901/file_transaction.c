#define _CRT_SECURE_NO_WARNINGS
//Ʈ�����, ������ ȭ�� ���� �ҽ� ( å 11.3) ����

#include <stdio.h>
#include <string.h>

//���ڵ� ����ü ����
typedef struct _Record{
	int key;
	char name[20];
	char address[60];
	char car[20];
	char company[20];
	char phone[20];
	int code;
}Record;

//���Ϻ� ���ڵ� ���� ����
Record master;
Record transaction;
Record newMaster;

//���Ϻ� ������ ����
FILE* masterFile;
FILE* transactionFile;
FILE* newMasterFile;

//���ν��� ����
void Make_Master_FIle();
void Make_Transaction_File();
void Make_NewMaster_File();

void Get_Master_Record();
void Get_Transaction_Record();
void Put_Master_Record();
void Put_Transaction_Record();

void Print_NewMaster_File();

int main(void) {
	Make_Master_FIle();
	Make_Transaction_File();
	Make_NewMaster_File();
	Print_NewMaster_File();

	return 0;
}

void Make_Master_FIle(void) {
	
	if ((masterFile = fopen("masterFile.dat", "w"))==NULL) {
		printf("master file not opened\n");
	}
	else {
		printf("-----------------------------\n");
		printf("Make Master File\n");
		printf("Enter key, name, address, car, company, phone\n");
		printf("Enter EOF to end input \n");
		printf("Record:");
		scanf("%d %s %s %s %s %s", &master.key, master.name, master.address, master.car, master.company, master.phone);

		while (!feof(stdin)) {
			fprintf(masterFile, "%d %s %s %s %s %s\n", master.key, master.name, master.address, master.car, master.company, master.phone);
			printf("Record:");
			scanf("%d %s %s %s %s %s", &master.key, master.name, master.address, master.car, master.company, master.phone);
		}
		fclose(masterFile);
		printf("Make_Master_File() finished\n");
	}
}

void Make_Transaction_File(void) {

	if ((transactionFile = fopen("transactionFile.dat", "w")) == NULL) {
		printf("transaction file not opened\n");
	}
	else {
		printf("-----------------------------\n");
		printf("Make Transaction File\n");
		printf("Enter key, name, address, car, company, phone\n");
		printf("Enter EOF to end input \n");
		printf("Record:");
		scanf("%d %s %s %s %s %s %d", &transaction.key, transaction.name, transaction.address, transaction.car, transaction.company, transaction.phone, &transaction.code);

		while (!feof(stdin)) {
			fprintf(transactionFile, "%d %s %s %s %s %s %d\n", transaction.key, transaction.name, transaction.address, transaction.car, transaction.company, transaction.phone, transaction.code);
			printf("Record:");
			scanf("%d %s %s %s %s %s %d", &transaction.key, transaction.name, transaction.address, transaction.car, transaction.company, transaction.phone, &transaction.code);
		}
		fclose(transactionFile);
		printf("Make_Transaction_File() finished\n");
	}
}

void Get_Master_Record(void) {
	fscanf(masterFile, "%d %s %s %s %s %s", &master.key, master.name, master.address, master.car, master.company, master.phone);
	if (feof(masterFile)) {
		master.key = EOF;
	}
}

void Get_Transaction_Record(void) {
	fscanf(transactionFile, "%d %s %s %s %s %s %d", &transaction.key, transaction.name, transaction.address, transaction.car, transaction.company, transaction.phone, &transaction.code);
	if (feof(transactionFile)) {
		transaction.key = EOF;
	}
}

void Put_Master_Record(void) {
	fprintf(newMasterFile, "%d %s %s %s %s %s\n", master.key, master.name, master.address, master.car, master.company, master.phone);
}

void Put_Transaction_Record(void) {
	fprintf(newMasterFile, "%d %s %s %s %s %s\n", transaction.key, transaction.name, transaction.address, transaction.car, transaction.company, transaction.phone);
}

void Make_NewMaster_File(void) {

	masterFile = fopen("masterFile.dat", "r");
	transactionFile = fopen("transactionFile.dat", "r");
	newMasterFile = fopen("newMasterFile.dat", "w");

	Get_Master_Record();
	Get_Transaction_Record();

	while (1) {
		if (master.key==EOF) {
			if (transaction.key==EOF) {//�Ѵ� EOF �� ���. ��������

				printf("Make_NewMaster_File() finished..\n");
				break;
			}
			else {// transaction�� �������
				while (transaction.key!=EOF) {

					if (transaction.code == 0) { //�Է��ڵ� 0�϶��� ���� �Է�
						Put_Transaction_Record();
					}
					else { // ������ �ڵ��϶��� transaction ������ �����޽��� �߻�
						printf("Transaction error code: %d\n", transaction.code);
					}
					Get_Transaction_Record();
				}
			}
		}
		else {
			if (transaction.key==EOF) {//master�� �������
				while (master.key!=EOF) {
					Put_Master_Record();
					Get_Master_Record();
				}
			}
			else {//�Ѵ� �������
				if (master.key > transaction.key) {
					if (transaction.code == 0) {
						Put_Transaction_Record();
						Get_Transaction_Record();
					}
					else { // master <= transaction
						printf("transaction error code:%d\n", transaction.code);
						Get_Transaction_Record();
					}
				}
				else if (master.key == transaction.key) {
					switch (transaction.code) {
					case 1: // �� ��ȯ
						fprintf(newMasterFile, "%d %s %s %s %s %s\n", master.key, master.name, master.address, transaction.car, master.company, master.phone);
						Get_Master_Record();
						Get_Transaction_Record();
						break;
					case 2: // ���ŵ� ���ڵ�
						Get_Master_Record();
						Get_Transaction_Record();
						break;
					case 3: // �ּ� ����
						fprintf(newMasterFile, "%d %s %s %s %s %s\n", master.key, master.name, transaction.address, master.car, master.company, master.phone);
						Get_Master_Record();
						Get_Transaction_Record();
						break;
					case 4: // ��ȭ ��ȣ ����
						fprintf(newMasterFile, "%d %s %s %s %s %s\n", master.key, master.name, master.address, master.car, master.company, transaction.phone);
						Get_Master_Record();
						Get_Transaction_Record();
						break;
					case 5: // ���� ����
						fprintf(newMasterFile, "%d %s %s %s %s %s\n", master.key, master.name, master.address, master.car, transaction.company, master.phone);
						Get_Master_Record();
						Get_Transaction_Record();
						break;
					default: // case 0�̳� ������ code
						printf("Transaction error code: %d\n", transaction.code);
						printf("Transaction error key: %d \n", transaction.key);
						Get_Transaction_Record();
						break;
					}
				}
				else { // master.key < transaction.key
					Put_Master_Record();
					Get_Master_Record();
				}
			}
		}
	}

	fclose(masterFile);
	fclose(transactionFile);
	fclose(newMasterFile);
}

void Print_NewMaster_File(void) {
	newMasterFile = fopen("newMasterFile.dat", "r");
	while (!feof(newMasterFile)) {
		fscanf(newMasterFile, "%d %s %s %s %s %s \n", &newMaster.key, newMaster.name, newMaster.address, newMaster.car, newMaster.company, newMaster.phone);
		printf("%d %s %s %s %s %s\n", newMaster.key, newMaster.name, newMaster.address, newMaster.car, newMaster.company, newMaster.phone);
	}
	fclose(newMasterFile);
	printf("Print_NewMaster_File() finished..\n");
}