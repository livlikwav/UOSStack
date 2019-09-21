#define _CRT_SECURE_NO_WARNINGS
//트랜잭션, 마스터 화일 생성 소스 ( 책 11.3) 참고

#include <stdio.h>
#include <string.h>

//레코드 구조체 정의
typedef struct _Record{
	int key;
	char name[20];
	char address[60];
	char car[20];
	char company[20];
	char phone[20];
	int code;
}Record;

//파일별 레코드 버퍼 정의
Record master;
Record transaction;
Record newMaster;

//파일별 포인터 정의
FILE* masterFile;
FILE* transactionFile;
FILE* newMasterFile;

//프로시저 정의
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
			if (transaction.key==EOF) {//둘다 EOF 인 경우. 정상종료

				printf("Make_NewMaster_File() finished..\n");
				break;
			}
			else {// transaction만 남은경우
				while (transaction.key!=EOF) {

					if (transaction.code == 0) { //입력코드 0일때는 정상 입력
						Put_Transaction_Record();
					}
					else { // 나머지 코드일때는 transaction 오류로 오류메시지 발생
						printf("Transaction error code: %d\n", transaction.code);
					}
					Get_Transaction_Record();
				}
			}
		}
		else {
			if (transaction.key==EOF) {//master만 남은경우
				while (master.key!=EOF) {
					Put_Master_Record();
					Get_Master_Record();
				}
			}
			else {//둘다 남은경우
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
					case 1: // 차 교환
						fprintf(newMasterFile, "%d %s %s %s %s %s\n", master.key, master.name, master.address, transaction.car, master.company, master.phone);
						Get_Master_Record();
						Get_Transaction_Record();
						break;
					case 2: // 제거될 레코드
						Get_Master_Record();
						Get_Transaction_Record();
						break;
					case 3: // 주소 변경
						fprintf(newMasterFile, "%d %s %s %s %s %s\n", master.key, master.name, transaction.address, master.car, master.company, master.phone);
						Get_Master_Record();
						Get_Transaction_Record();
						break;
					case 4: // 전화 번호 변경
						fprintf(newMasterFile, "%d %s %s %s %s %s\n", master.key, master.name, master.address, master.car, master.company, transaction.phone);
						Get_Master_Record();
						Get_Transaction_Record();
						break;
					case 5: // 직장 변경
						fprintf(newMasterFile, "%d %s %s %s %s %s\n", master.key, master.name, master.address, master.car, transaction.company, master.phone);
						Get_Master_Record();
						Get_Transaction_Record();
						break;
					default: // case 0이나 오류값 code
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