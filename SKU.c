#include <stdio.h>
#include <string.h>

typedef struct { //�޴� �̸� �� ���� ����ü
	char name[50];
	int price;
}Menu_item;

typedef struct { //��ٱ��� ����ü
	Menu_item items[50];
	int item_count;
	int total_price;
}Cart;

int price;

void Main_menu(void); //���θ޴� ���
void Food_menu(Menu_item menu[]); //���ĸ޴�
void Initialization_cart(Cart* cart); //��ٱ��� �ʱ�ȭ
void Add_cart(Menu_item menu[], Cart* cart, int choice); //��ٱ��Ͽ� ���� �߰�
void Veiw_cart(Cart* cart, Menu_item menu[]); //��ٱ��� ���
void Del_cart(Cart* cart, int choice); //��ٱ��� ���
void Add_receipt(Cart* cart, Menu_item menu[]); //������ �Է�
void Initialization_receipt(int price); //������ �ʱ�ȭ

int main(void) //�����Լ�
{
	int ans;
	char edit;
	Menu_item menu[8];
	Cart cart;
	
	Food_menu(menu); //�޴� �ʱ�ȭ
	Initialization_cart(&cart); //��ٱ��� �ʱ�ȭ
	Initialization_receipt(price); //������ �ʱ�ȭ

	do {
		Main_menu(); //���θ޴� ���
		printf("����: ");
		scanf("%d", &ans);

		switch (ans) {
		case 1:
			for (int i = 0; i < 2; i++)
				printf("%d. %s - %d��\n", i + 1, menu[i].name, menu[i].price);

			printf("������ �����ϼ���: ");
			scanf("%d", &ans);

			Add_cart(menu, &cart, ans - 1);

			break;

		case 2:
			for (int i = 2; i < 4; i++)
				printf("%d. %s - %d��\n", i - 1, menu[i].name, menu[i].price);

			printf("�Ľ��� �����ϼ���: ");
			scanf("%d", &ans);

			Add_cart(menu, &cart, ans + 1);

			break;

		case 3:
			for (int i = 4; i < 6; i++)
				printf("%d. %s - %d��\n", i - 3, menu[i].name, menu[i].price);

			printf("���ָ� �����ϼ���: ");
			scanf("%d", &ans);

			Add_cart(menu, &cart, ans + 3);

			break;

		case 4:
			for (int i = 6; i < 8; i++)
				printf("%d. %s - %d��\n", i - 5, menu[i].name, menu[i].price);

			printf("���Ḧ �����Ͻÿ�: ");
			scanf("%d", &ans);

			Add_cart(menu, &cart, ans + 5);

			break;

		case 5:
			printf("\b������ ȣ��Ǿ����ϴ�.\n");

			break;
		case 6:
			Veiw_cart(&cart, menu);
			
			printf("�޴��� ����Ϸ��� �޴� ��ȣ�� �Է��ϼ���(������ ���, 0�� ������ ������): ");
			scanf("%d", &ans);
			
			if(ans >= 0)
				Del_cart(&cart, menu, ans);
			
			break;

		case 7:
			printf("�ֹ��� �Ϸ�Ǿ����ϴ�.\n\n");

			Add_receipt(&cart, menu);
			Initialization_cart(&cart);

			break;

		case 0:
			printf("���� �Ǿ����ϴ�. �������� Ȯ���ϼ���.\n");

			break;

		default:
			printf("0���� 7������ ���ڷ� �Է����ּ���\n\n");

			break;
		}
	} while (ans != 0);

	return 0;
}

void Main_menu(void) //ù ȭ��
{
	printf("========================\n");
	printf("       �������       \n");
	printf("========================\n");
	printf("1. �Ļ�\n");
	printf("2. �Ľ�\n");
	printf("3. ����\n");
	printf("4. ����\n");
	printf("5. ����ȣ��\n");
	printf("6. ��ٱ���\n");
	printf("7. �ֹ�\n");
	printf("0. ����\n");
}

void Food_menu(Menu_item menu[]) //���� �޴�
{
	strcpy(menu[0].name, "���κ��"); 
	menu[0].price = 8000;
	strcpy(menu[1].name, "��������");
	menu[1].price = 5000;
	strcpy(menu[2].name, "���ϸ��");
	menu[2].price = 10000;
	strcpy(menu[3].name, "��������ũ");
	menu[3].price = 4000;
	strcpy(menu[4].name, "�ع�����");
	menu[4].price = 6000;
	strcpy(menu[5].name, "���");
	menu[5].price = 11000;
	strcpy(menu[6].name, "����(���̽�)");
	menu[6].price = 3000;
	strcpy(menu[7].name, "������ 1L");
	menu[7].price = 3000;
}

void Initialization_cart(Cart* cart) //��ٱ����� ������ ������ ���� ������ �ʱ�ȭ
{
	cart->item_count = 0;
	cart->total_price = 0;
}

void Add_cart(Menu_item menu[], Cart* cart, int choice) //��ٱ��Ͽ� �޴� �߰�
{
	if (cart->item_count < 50) {
		cart->items[cart->item_count] = menu[choice];
		cart->total_price += menu[choice].price;
		cart->item_count++;
		
		printf("%s�� ��ٱ��� �߰��߽��ϴ�.\n\n", menu[choice].name);
	}
	else 
		printf("��ٱ��ϰ� ���� á���ϴ�.\n\n");
}

void Veiw_cart(Cart* cart, Menu_item menu[]) //��ٱ��� �޴� ���
{
	printf("\n��ٱ���\n");

	for (int i = 0; i < cart->item_count; i++) 
		printf("%d. %s - %d��\n", i + 1, cart->items[i].name, cart->items[i].price);

	printf("�� ����: %d��\n\n", cart->total_price);
}

void Del_cart(Cart* cart, Menu_item menu[], int choice) //��ٱ��� �޴� ���
{
	choice--;

	if (0 <= choice < cart->item_count) {
		cart->total_price -= cart->items[choice].price; //��ٱ��� �ȿ� �ִ� ������ �Ѿ׿��� ����� �޴��� ���� ����
		cart->items[choice] = cart->items[choice + 1]; //��ĭ �� ������ ������μ� ������ �޴� ����
	}

	cart->item_count--;
}

void Initialization_receipt(int price) //������ �ʱ�ȭ
{
	price = 0; //���� �ֹ��� ������ �Ѿ��� �ʱ�ȭ
	FILE* fp = fopen("������.txt", "w+"); //w�� ��� ������ �ִ� ���� �ʱ�ȭ

	fprintf(fp, "������\n\n"); //���� �ʱ�ȭ�� ���� ����

	fclose(fp);
}

void Add_receipt(Cart* cart, Menu_item menu[]) //������ �Է�(����)
{
	FILE* fp = fopen("������.txt", "a+"); //�߰� �ֹ��� �ϸ� ���� �� �ְ� a�� ���

	if (fp == NULL)
		printf("����!\n");

	for (int i = 0; i < cart->item_count; i++) {
		fprintf(fp, "%s - %d��\n", cart->items[i].name, cart->items[i].price);
		price += cart->items[i].price; //���ݱ��� �ֹ��� ������ �Ѿ�
	}
	
	fprintf(fp, "\n�Ѿ�: %d��\n\n", price);
	
	fclose(fp);
}