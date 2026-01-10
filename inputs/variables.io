// Constants
int MIN_AGE_TO_BE_ADULT = 18

// Normal variables
int born = 1994
int year = 2025
int age = year - born

// check if id adult
bool isAdult = age > MIN_AGE_TO_BE_ADULT

// name and message as string
str name = 'brayhan de aza'
str message = f"{name.title()} is {age << 0} old, so he {!isAdult ? 'is adult' : "is not adult"}"

