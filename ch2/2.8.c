#include <stdio.h>
#include <stdlib.h>

int stoi_rec(char *s) {
	if (*s == '\0')
		return 0;

	int ans = *s - '0';
	return ans + 10 * stoi_rec(s + 1);
}

int len(char *s) {
	int ans = 0;
	if (*s == '\0')
		return ans;
	
	return ++ans + len(s + 1);
}

void reverse(char *s) {
	int n = len(s);

	int f = 0, l = n - 1;
	while(f < l) {
		char tmp = s[f];
		s[f++] = s[l];
		s[l--] = tmp;
	}
}

int main() {
	char *s = malloc(sizeof(char) * 100);

	if (s == NULL) {
		printf("Memory allocation failed\n");
		return 1;
	}

	printf("Enter a number: ");
	scanf("%s", s);

	printf("You entered: %s\n", s);
	
	/*
	 * First reverse the string
	 * then pass it into the function
	 */
	
	reverse(s);
	int res = stoi_rec(s);
	printf("res: %d\n", res);

	// π
	printf("Here's a free pi: π\n");
	
	// Never forget to free the memory
	free(s);

	return 0;
}
