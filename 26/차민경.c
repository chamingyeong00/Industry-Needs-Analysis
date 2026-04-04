#define STRING_SIZE 12800

// 26진법 문자(A=0, B=1, ..., Z=25)로 변환
int char_to_int(char c) {
    return c - 'A';
}

// 26진법 숫자를 문자(A-Z)로 변환
char int_to_char(int n) {
    return n + 'A';
}

// 두 개의 26진법 숫자 덧셈
void add_26_base_numbers(char* result, const char* num1, const char* num2) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int max_len = (len1 > len2) ? len1 : len2;
    
    int carry = 0;  // 올림 값
    int i = 0;

    // 뒤에서부터 덧셈
    while (i < max_len || carry) {
        int digit1 = (i < len1) ? char_to_int(num1[len1 - 1 - i]) : 0;
        int digit2 = (i < len2) ? char_to_int(num2[len2 - 1 - i]) : 0;

        int sum = digit1 + digit2 + carry;
        carry = sum / 26; // 올림 처리
        result[i] = int_to_char(sum % 26); // 현재 자리의 결과 저장

        i++;
    }
    result[i] = '\0';  // 문자열 끝
    // 뒤집기: 결과는 뒤에서부터 구했으므로 반전시켜야 함
    for (int j = 0; j < i / 2; j++) {
        char temp = result[j];
        result[j] = result[i - 1 - j];
        result[i - 1 - j] = temp;
    }
}

// 두 개의 26진법 숫자 뺄셈
void subtract_26_base_numbers(char* result, const char* num1, const char* num2) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int max_len = (len1 > len2) ? len1 : len2;

    int borrow = 0;  // 차감 값
    int i = 0;

    // 뒤에서부터 뺄셈
    while (i < max_len) {
        int digit1 = (i < len1) ? char_to_int(num1[len1 - 1 - i]) : 0;
        int digit2 = (i < len2) ? char_to_int(num2[len2 - 1 - i]) : 0;

        int diff = digit1 - digit2 - borrow;
        if (diff < 0) {
            diff += 26;  // 26진법에서 음수 처리
            borrow = 1;  // 올림 처리
        } else {
            borrow = 0;
        }

        result[i] = int_to_char(diff);
        i++;
    }
    result[i] = '\0';  // 문자열 끝
    // 뒤집기: 결과는 뒤에서부터 구했으므로 반전시켜야 함
    for (int j = 0; j < i / 2; j++) {
        char temp = result[j];
        result[j] = result[i - 1 - j];
        result[i - 1 - j] = temp;
    }
}

// test_main 함수: question에서 주어진 연산을 수행하여 결과를 answer에 저장
void test_main(char answer[STRING_SIZE], const char question[STRING_SIZE]) {
    int idx = 0;
    char cur[STRING_SIZE] = {0};  // 현재 결과를 저장
    char num[STRING_SIZE] = {0};  // 연산할 숫자를 저장
    char op;  // 연산자: '+' 또는 '-'

    // 첫 번째 숫자 읽기
    int cur_len = 0;
    while (question[idx] != '+' && question[idx] != '-' && question[idx] != '\0') {
        cur[cur_len++] = question[idx++];
    }

    // 이후 연산자와 숫자 처리
    while (question[idx] != '\0') {
        op = question[idx++];  // 연산자 처리

        // 두 번째 숫자 읽기
        int num_len = 0;
        while (question[idx] != '+' && question[idx] != '-' && question[idx] != '\0') {
            num[num_len++] = question[idx++];
        }

        // 덧셈 또는 뺄셈 처리
        if (op == '+') {
            add_26_base_numbers(answer, cur, num);
        } else {
            subtract_26_base_numbers(answer, cur, num);
        }

        // 계산 후 결과를 cur에 저장
        strcpy(cur, answer);
    }
}