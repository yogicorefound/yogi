str a = "Contact me at test@gmail.com"
regex emailPattern = r"/([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})/"

a.replace(emailPattern, "[hidden]")