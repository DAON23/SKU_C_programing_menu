#include <stdio.h>
#include <string.h>

typedef struct { //메뉴 이름 및 가격 구조체
	char name[50];
	int price;
}Menu_item;

typedef struct { //장바구니 구조체
	Menu_item items[50];
	int item_count;
	int total_price;
}Cart;

int price;

void Main_menu(void); //메인메뉴 출력
void Food_menu(Menu_item menu[]); //음식메뉴
void Initialization_cart(Cart* cart); //장바구니 초기화
void Add_cart(Menu_item menu[], Cart* cart, int choice); //장바구니에 음식 추가
void Veiw_cart(Cart* cart, Menu_item menu[]); //장바구니 출력
void Del_cart(Cart* cart, int choice); //장바구니 취소
void Add_receipt(Cart* cart, Menu_item menu[]); //영수증 입력
void Initialization_receipt(int price); //영수증 초기화

int main(void) //메인함수
{
	int ans;
	char edit;
	Menu_item menu[8];
	Cart cart;
	
	Food_menu(menu); //메뉴 초기화
	Initialization_cart(&cart); //장바구니 초기화
	Initialization_receipt(price); //영수증 초기화

	do {
		Main_menu(); //메인메뉴 출력
		printf("선택: ");
		scanf("%d", &ans);

		switch (ans) {
		case 1:
			for (int i = 0; i < 2; i++)
				printf("%d. %s - %d원\n", i + 1, menu[i].name, menu[i].price);

			printf("음식을 선택하세요: ");
			scanf("%d", &ans);

			Add_cart(menu, &cart, ans - 1);

			break;

		case 2:
			for (int i = 2; i < 4; i++)
				printf("%d. %s - %d원\n", i - 1, menu[i].name, menu[i].price);

			printf("후식을 선택하세요: ");
			scanf("%d", &ans);

			Add_cart(menu, &cart, ans + 1);

			break;

		case 3:
			for (int i = 4; i < 6; i++)
				printf("%d. %s - %d원\n", i - 3, menu[i].name, menu[i].price);

			printf("안주를 선택하세요: ");
			scanf("%d", &ans);

			Add_cart(menu, &cart, ans + 3);

			break;

		case 4:
			for (int i = 6; i < 8; i++)
				printf("%d. %s - %d원\n", i - 5, menu[i].name, menu[i].price);

			printf("음료를 선택하시오: ");
			scanf("%d", &ans);

			Add_cart(menu, &cart, ans + 5);

			break;

		case 5:
			printf("\b직원이 호출되었습니다.\n");

			break;
		case 6:
			Veiw_cart(&cart, menu);
			
			printf("메뉴를 취소하려면 메뉴 번호를 입력하세요(음수는 취소, 0을 누르지 마세요): ");
			scanf("%d", &ans);
			
			if(ans >= 0)
				Del_cart(&cart, menu, ans);
			
			break;

		case 7:
			printf("주문이 완료되었습니다.\n\n");

			Add_receipt(&cart, menu);
			Initialization_cart(&cart);

			break;

		case 0:
			printf("종료 되었습니다. 영수증을 확인하세요.\n");

			break;

		default:
			printf("0부터 7사이의 숫자로 입력해주세요\n\n");

			break;
		}
	} while (ans != 0);

	return 0;
}

void Main_menu(void) //첫 화면
{
	printf("========================\n");
	printf("       라디에이터       \n");
	printf("========================\n");
	printf("1. 식사\n");
	printf("2. 후식\n");
	printf("3. 안주\n");
	printf("4. 음료\n");
	printf("5. 직원호출\n");
	printf("6. 장바구니\n");
	printf("7. 주문\n");
	printf("0. 종료\n");
}

void Food_menu(Menu_item menu[]) //음식 메뉴
{
	strcpy(menu[0].name, "순두부찌개"); 
	menu[0].price = 8000;
	strcpy(menu[1].name, "제육볶음");
	menu[1].price = 5000;
	strcpy(menu[2].name, "과일모듬");
	menu[2].price = 10000;
	strcpy(menu[3].name, "조각케이크");
	menu[3].price = 4000;
	strcpy(menu[4].name, "해물파전");
	menu[4].price = 6000;
	strcpy(menu[5].name, "어묵탕");
	menu[5].price = 11000;
	strcpy(menu[6].name, "소주(참이슬)");
	menu[6].price = 3000;
	strcpy(menu[7].name, "생맥주 1L");
	menu[7].price = 3000;
}

void Initialization_cart(Cart* cart) //장바구니의 아이템 갯수와 총합 가격을 초기화
{
	cart->item_count = 0;
	cart->total_price = 0;
}

void Add_cart(Menu_item menu[], Cart* cart, int choice) //장바구니에 메뉴 추가
{
	if (cart->item_count < 50) {
		cart->items[cart->item_count] = menu[choice];
		cart->total_price += menu[choice].price;
		cart->item_count++;
		
		printf("%s를 장바구니 추가했습니다.\n\n", menu[choice].name);
	}
	else 
		printf("장바구니가 가득 찼습니다.\n\n");
}

void Veiw_cart(Cart* cart, Menu_item menu[]) //장바구니 메뉴 출력
{
	printf("\n장바구니\n");

	for (int i = 0; i < cart->item_count; i++) 
		printf("%d. %s - %d원\n", i + 1, cart->items[i].name, cart->items[i].price);

	printf("총 가격: %d원\n\n", cart->total_price);
}

void Del_cart(Cart* cart, Menu_item menu[], int choice) //장바구니 메뉴 취소
{
	choice--;

	if (0 <= choice < cart->item_count) {
		cart->total_price -= cart->items[choice].price; //장바구니 안에 있는 가격의 총액에서 취소한 메뉴의 가격 빼기
		cart->items[choice] = cart->items[choice + 1]; //한칸 씩 앞으로 당김으로서 선택한 메뉴 삭제
	}

	cart->item_count--;
}

void Initialization_receipt(int price) //영수증 초기화
{
	price = 0; //전에 주문한 음식의 총액을 초기화
	FILE* fp = fopen("영수증.txt", "w+"); //w로 열어서 기존에 있던 내용 초기화

	fprintf(fp, "영수증\n\n"); //내용 초기화를 위해 적음

	fclose(fp);
}

void Add_receipt(Cart* cart, Menu_item menu[]) //영수증 입력(수정)
{
	FILE* fp = fopen("영수증.txt", "a+"); //추가 주문을 하면 적을 수 있게 a를 사용

	if (fp == NULL)
		printf("에러!\n");

	for (int i = 0; i < cart->item_count; i++) {
		fprintf(fp, "%s - %d원\n", cart->items[i].name, cart->items[i].price);
		price += cart->items[i].price; //지금까지 주문한 음식의 총액
	}
	
	fprintf(fp, "\n총액: %d원\n\n", price);
	
	fclose(fp);
}