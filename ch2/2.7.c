#include <stdio.h>
#include <stdlib.h>

int len(char *s) {
	int ans = 0;
	
	/*
	 * If it is the termination character	 
	 * just return the ans
	 */
	if(*s == '\0') 
		return ans;
	
	/*
	 * Else increase the ans by one and add the len of the remaining string
	 */
	return ++ans + len(s + 1);
}

int main() {
	char *s = malloc(sizeof(char) * 100);

	if (s==NULL) {
		printf("Memory allocation failed\n");
		return 1;
	}
	
	/*
	 * This will only store the string upto first whitespace.
	 */
	printf("enter a string: ");
	scanf("%s", s);

	// Check that it is infact storing first word only.
	printf("The input is: %s\n", s);

	printf("Length of the input is: %d\n", len(s));

	return 0;
}
