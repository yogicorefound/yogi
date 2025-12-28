str a = "  Found FFI  "

regex b = r"/F/"
str c = a.trim().replace(b, "-")
