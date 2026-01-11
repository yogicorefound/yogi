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
if(isAdult) {
    name = name.title() + f" is {age} old, so he is adult"
    name = f" is {age} old, so he is adult"
    name = f" is {age} old, so he is adult"

    if (true) {
        name = f" is {age} old, so he is adult"
    }

} else {
    name = name + f" is {age} old, so he is not adult"
}

name
